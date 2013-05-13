/**********************************************************************
* $Id$		lpc177x_8x_eeprom.c			2011-06-02
*//**
* @file		lpc177x_8x_eeprom.c
* @brief	Contains all functions support for EEPROM firmware library on
*			LPC177x_8x
* @version	1.0
* @date		02. June. 2011
* @author	NXP MCU SW Application Team
*
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup EEPROM
 * @{
 */

/* Includes ------------------------------------------------------------------- */
#include "lpc177x_8x_eeprom.h"
#include "lpc177x_8x_clkpwr.h"

/* Public Functions ----------------------------------------------------------- */

/*********************************************************************//**
 * @brief 		Initial EEPROM
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void EEPROM_Init(void)
{
	uint32_t val, cclk;
	LPC_EEPROM->PWRDWN = 0x0;
	/* EEPROM is automate turn on after reset */
	/* Setting clock:
	 * EEPROM required a 375kHz. This clock is generated by dividing the
	 * system bus clock.
	 */
   	cclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_CPU);
	val = (cclk/375000)-1;
	LPC_EEPROM->CLKDIV = val;

	/* Setting wait state */
	val  = ((((cclk / 1000000) * 15) / 1000) + 1);
	val |= (((((cclk / 1000000) * 55) / 1000) + 1) << 8);
	val |= (((((cclk / 1000000) * 35) / 1000) + 1) << 16);
	LPC_EEPROM->WSTATE = val;
}

/*********************************************************************//**
 * @brief 		Write data to EEPROM at specific address
 * @param[in]	address EEPROM address that start to write data, it must be
 * 				in range 0..0x1000
 * 				mode	Write mode, should be:
 * 					- MODE_8_BIT	: write 8 bit mode
 * 					- MODE_16_BIT	: write 16 bit mode
 * 					- MODE_32_BIT	: write 32 bit mode
 * 				data	buffer that contain data that will be written to buffer
 * 				count	number written data
 * @return 		None
 * @note		This function actually write data into EEPROM memory and automatically
 * 				write into next page if current page is overflowed
 **********************************************************************/
void EEPROM_Write(uint16_t page_offset, uint16_t page_address, void* data, EEPROM_Mode_Type mode, uint32_t count)
{
	uint32_t i;
    uint8_t *data8 = data;
    uint16_t *data16 = data;
    uint32_t *data32 = data;

#ifdef __IAR_SYSTEMS_ICC__
#if (mode == MODE_8_BIT)
        uint8_t *tmp = (uint8_t *)data;
#elif (mode == MODE_16_BIT)
        uint16_t *tmp = (uint16_t *)data;
#else
        uint32_t *tmp = (uint32_t *)data;
#endif
#endif

	LPC_EEPROM->INT_CLR_STATUS = ((1 << EEPROM_ENDOF_RW)|(1 << EEPROM_ENDOF_PROG));
	//check page_offset
	if(mode == MODE_16_BIT){
		if((page_offset & 0x01)!=0) while(1);
	}
	else if(mode == MODE_32_BIT){
	 	if((page_offset & 0x03)!=0) while(1);
	}
	LPC_EEPROM->ADDR = EEPROM_PAGE_OFFSET(page_offset);
	LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_RW);
	for(i=0;i<count;i++)
	{
		//update data to page register
		if(mode == MODE_8_BIT){
			LPC_EEPROM->CMD = EEPROM_CMD_8_BIT_WRITE;
#ifdef __IAR_SYSTEMS_ICC__
                        LPC_EEPROM -> WDATA = *tmp;
                        tmp++;
#else
			LPC_EEPROM -> WDATA = *data8;
            data8++;
#endif
			page_offset +=1;
		}
		else if(mode == MODE_16_BIT){
			LPC_EEPROM->CMD = EEPROM_CMD_16_BIT_WRITE;
#ifdef __IAR_SYSTEMS_ICC__
                        LPC_EEPROM -> WDATA = *tmp;
                        tmp++;
#else
			LPC_EEPROM -> WDATA = *data16;
            data16++;
#endif
			page_offset +=2;
		}
		else{
			LPC_EEPROM->CMD = EEPROM_CMD_32_BIT_WRITE;
#ifdef __IAR_SYSTEMS_ICC__
                        LPC_EEPROM -> WDATA = *tmp;
                        tmp++;
#else
			LPC_EEPROM -> WDATA = *data32;
            data32++;
#endif
			page_offset +=4;
		}
		if((page_offset >= EEPROM_PAGE_NUM)|(i==count-1)){
			//update to EEPROM memory
			LPC_EEPROM->INT_CLR_STATUS = (0x1 << EEPROM_ENDOF_PROG);
			LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address);
			LPC_EEPROM->CMD = EEPROM_CMD_ERASE_PRG_PAGE;
			while(!((LPC_EEPROM->INT_STATUS >> 28)&0x01));
		}
		if(page_offset >= EEPROM_PAGE_NUM)
		{
			page_offset = 0;
			page_address +=1;
			LPC_EEPROM->ADDR =0;
			if(page_address > EEPROM_PAGE_NUM - 1) page_address = 0;
		}
	}
}

/*********************************************************************//**
 * @brief 		Read data to EEPROM at specific address
 * @param[in]
 * 				data	buffer that contain data that will be written to buffer
 * 				mode	Read mode, should be:
 * 					- MODE_8_BIT	: write 8 bit mode
 * 					- MODE_16_BIT	: write 16 bit mode
 * 					- MODE_32_BIT	: write 32 bit mode
 * 				size	number read data (bytes)
 * @return 		data	buffer that contain data that will be read to buffer
 **********************************************************************/
void EEPROM_Read(uint16_t page_offset, uint16_t page_address, void* data, EEPROM_Mode_Type mode, uint32_t count)
{
    uint32_t i;
    uint8_t *data8 = data;
    uint16_t *data16 = data;
    uint32_t *data32 = data;

#ifdef __IAR_SYSTEMS_ICC__
#if (mode == MODE_8_BIT)
        uint8_t *tmp = (uint8_t *)data;
#elif (mode == MODE_16_BIT)
        uint16_t *tmp = (uint16_t *)data;
#else
        uint32_t *tmp = (uint32_t *)data;
#endif
#endif
	LPC_EEPROM->INT_CLR_STATUS = ((1 << EEPROM_ENDOF_RW)|(1 << EEPROM_ENDOF_PROG));
	LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address)|EEPROM_PAGE_OFFSET(page_offset);
	if(mode == MODE_8_BIT)
		LPC_EEPROM->CMD = EEPROM_CMD_8_BIT_READ|EEPROM_CMD_RDPREFETCH;
	else if(mode == MODE_16_BIT){
		LPC_EEPROM->CMD = EEPROM_CMD_16_BIT_READ|EEPROM_CMD_RDPREFETCH;
		//check page_offset
		if((page_offset &0x01)!=0)
			while(1);
	}
	else{
		LPC_EEPROM->CMD = EEPROM_CMD_32_BIT_READ|EEPROM_CMD_RDPREFETCH;
		//page_offset must be a multiple of 0x04
		if((page_offset & 0x03)!=0)
			while(1);
	}

	//read and store data in buffer
	for(i=0;i<count;i++){
		 LPC_EEPROM->INT_CLR_STATUS = (1 << EEPROM_ENDOF_RW);
		 if(mode == MODE_8_BIT){
#ifdef __IAR_SYSTEMS_ICC__
                    *tmp = (uint8_t)(LPC_EEPROM -> RDATA);
                    tmp++;
#else
			 *data8 = (uint8_t)(LPC_EEPROM -> RDATA);
             data8++;
#endif
			 page_offset +=1;
		 }
		 else if (mode == MODE_16_BIT)
		 {
#ifdef __IAR_SYSTEMS_ICC__
                      *tmp =  (uint16_t)(LPC_EEPROM -> RDATA);
                      tmp++;
#else
			 *data16 = (uint16_t)(LPC_EEPROM -> RDATA);
             data16++;
#endif
			 page_offset +=2;
		 }
		 else{
#ifdef __IAR_SYSTEMS_ICC__
                   *tmp = (uint32_t)(LPC_EEPROM ->RDATA);
                   tmp++;
#else
			 *data32 = (uint32_t)(LPC_EEPROM -> RDATA);
             data32++;
#endif
			 page_offset +=4;
		 }
		 while(!((LPC_EEPROM->INT_STATUS >> 26)&0x01));
		 if(page_offset >= EEPROM_PAGE_SIZE) {
			 page_offset = 0;
			 page_address++;
			 LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(page_address)|EEPROM_PAGE_OFFSET(page_offset);
			 if(mode == MODE_8_BIT)
			 	LPC_EEPROM->CMD = EEPROM_CMD_8_BIT_READ|EEPROM_CMD_RDPREFETCH;
			 else if(mode == MODE_16_BIT)
				LPC_EEPROM->CMD = EEPROM_CMD_16_BIT_READ|EEPROM_CMD_RDPREFETCH;
			 else
			 	LPC_EEPROM->CMD = EEPROM_CMD_32_BIT_READ|EEPROM_CMD_RDPREFETCH;
		 }
	}
}

/*********************************************************************//**
 * @brief 		Erase to EEPROM at specific address
 * @param[in]	address EEPROM address that start to read data, should be
 * 				in range: 0..4096
 * 				mode	Read mode, should be:
 * 					- MODE_8_BIT	: write 8 bit mode
 * 					- MODE_16_BIT	: write 16 bit mode
 * 					- MODE_32_BIT	: write 32 bit mode
 * 				size	number read data
 * 					- byte unit in MODE_8_BIT
 * 					- word unit in MODE_16_BIT
 * 					- double word unit in MODE_32_BIT
 * @return 		data	buffer that contain data that will be read to buffer
 **********************************************************************/
void EEPROM_Erase(uint32_t address)
{
	uint32_t i;
	//clear page register
	LPC_EEPROM->CMD = EEPROM_CMD_8_BIT_WRITE;
	for(i=0;i<64;i++)
	{
		LPC_EEPROM -> WDATA = 0;
		while(!((LPC_EEPROM->INT_STATUS >> 26)&0x01));
	}

	LPC_EEPROM->INT_CLR_STATUS = (0x1 << EEPROM_ENDOF_PROG);
	LPC_EEPROM->ADDR = EEPROM_PAGE_ADRESS(address);
	LPC_EEPROM->CMD = EEPROM_CMD_ERASE_PRG_PAGE;
	while(!((LPC_EEPROM->INT_STATUS >> 28)&0x01));
}

/*********************************************************************//**
 * @brief 		Enable/Disable EEPROM power down mdoe
 * @param[in]	NewState	PowerDown mode state, should be:
 * 					- ENABLE: Enable power down mode
 * 					- DISABLE: Disable power down mode
 * @return 		None
 **********************************************************************/
void EEPROM_PowerDown(FunctionalState NewState)
{
	if(NewState == ENABLE)
		LPC_EEPROM->PWRDWN = 0x1;
	else
		LPC_EEPROM->PWRDWN = 0x0;
}


/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */

