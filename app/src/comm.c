
/*
************************************************************************************************************************
*           INCLUDE FILES
************************************************************************************************************************
*/

#include "comm.h"
#include "config.h"
#include "cdcuser.h"
#include "serial.h"

#include <string.h>


/*
************************************************************************************************************************
*           LOCAL DEFINES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           LOCAL CONSTANTS
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           LOCAL DATA TYPES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           LOCAL MACROS
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           LOCAL GLOBAL VARIABLES
************************************************************************************************************************
*/

static void (*g_webgui_response_cb)(void *data) = NULL;
static uint8_t g_webgui_blocked;


/*
************************************************************************************************************************
*           LOCAL FUNCTION PROTOTYPES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           LOCAL CONFIGURATION ERRORS
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           LOCAL FUNCTIONS
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           GLOBAL FUNCTIONS
************************************************************************************************************************
*/

void comm_linux_send(const char *msg)
{
    serial_send(CLI_SERIAL, (uint8_t*)msg, strlen(msg));
}

void comm_webgui_send(const char *data, uint32_t data_size)
{
    static const uint8_t end_msg = 0;
    CDC_Send((uint8_t*)data, data_size);
    CDC_Send(&end_msg, sizeof(end_msg));
}

void comm_webgui_set_response_cb(void (*resp_cb)(void *data))
{
    g_webgui_response_cb = resp_cb;
}

void comm_webgui_response_cb(void *data)
{
    if (g_webgui_response_cb)
    {
        g_webgui_response_cb(data);
        g_webgui_response_cb = NULL;
        g_webgui_blocked = 0;
    }
}

void comm_webgui_wait_response(void)
{
    g_webgui_blocked = 1;
    while (g_webgui_blocked);
}

void comm_control_chain_send(const uint8_t *data, uint32_t data_size)
{
    serial_send(CONTROL_CHAIN_SERIAL, data, data_size);
}
