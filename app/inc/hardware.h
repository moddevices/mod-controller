
/*
************************************************************************************************************************
*
************************************************************************************************************************
*/

#ifndef HARDWARE_H
#define HARDWARE_H


/*
************************************************************************************************************************
*           INCLUDE FILES
************************************************************************************************************************
*/

#include <stdint.h>

#include "glcd.h"
#include "led.h"


/*
************************************************************************************************************************
*           DO NOT CHANGE THESE DEFINES
************************************************************************************************************************
*/

enum {PROCESS, BYPASS};
enum {BLOCK, UNBLOCK};
enum {RECEPTION, TRANSMISSION};
enum {CPU_TURN_OFF, CPU_TURN_ON, CPU_REBOOT};
enum {CPU_OFF, CPU_ON};


/*
************************************************************************************************************************
*           CONFIGURATION DEFINES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           DATA TYPES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           GLOBAL VARIABLES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           MACRO'S
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           FUNCTION PROTOTYPES
************************************************************************************************************************
*/

// does the hardware setup
void hardware_setup(void);
// returns the glcd object relative to glcd id
glcd_t *hardware_glcds(uint8_t glcd_id);
// returns the led object relative to led id
led_t *hardware_leds(uint8_t led_id);
// returns the actuator object relative to actuator id
void *hardware_actuators(uint8_t actuator_id);
// returns the timestamp (a variable increment in each millisecond)
uint32_t hardware_timestamp(void);


/*
************************************************************************************************************************
*           CONFIGURATION ERRORS
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           END HEADER
************************************************************************************************************************
*/

#endif
