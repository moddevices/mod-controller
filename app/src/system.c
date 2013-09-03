
/*
************************************************************************************************************************
*           INCLUDE FILES
************************************************************************************************************************
*/

#include "system.h"
#include "config.h"
#include "data.h"
#include "naveg.h"
#include "hardware.h"
#include "actuator.h"
#include "comm.h"
#include "cli.h"
#include "screen.h"
#include "glcd_widget.h"
#include "glcd.h"

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

#define UNUSED_PARAM(var)   do { (void)(var); } while (0)


/*
************************************************************************************************************************
*           LOCAL GLOBAL VARIABLES
************************************************************************************************************************
*/


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

void system_check_boot(void)
{
    uint8_t i;
    button_t *foots[4];
    encoder_t *encoder;

    // gets the footswitches objects
    for (i = 0; i < FOOTSWITCHES_COUNT; i++)
    {
        foots[i] = (button_t *) hardware_actuators(FOOTSWITCH0 + i);
    }

    // gets the encoder objects
    encoder = hardware_actuators(ENCODER0 + PENDRIVE_RESTORE_DISPLAY);

    uint8_t status1, status2, button_status = 0;
    popup_t popup;

    // delay to wait read the actuators
    delay_ms(10);

    // gets the footswitches status
    status1 = BUTTON_PRESSED(actuator_get_status(foots[0]) & actuator_get_status(foots[2]));
    status2 = BUTTON_PRESSED(actuator_get_status(foots[1]) | actuator_get_status(foots[3]));

    // checks if footswitches combination is ok
    if (status1 && !status2)
    {
        // stop grub timeout
        cli_grub_select(STOP_TIMEOUT);

        popup.x = 0;
        popup.y = 0;
        popup.width = DISPLAY_WIDTH;
        popup.height = DISPLAY_HEIGHT - 1;
        popup.font = alterebro15;
        popup.type = YES_NO;
        popup.title = PENDRIVE_RESTORE_TITLE;
        popup.content = PENDRIVE_RESTORE_CONTENT;
        popup.button_selected = 1;
        widget_popup(PENDRIVE_RESTORE_DISPLAY, &popup);

        // waits the user response or timeout
        uint32_t timeout, inital_time = hardware_timestamp();
        while (1)
        {
            timeout = (hardware_timestamp() - inital_time) / 1000;
            if (timeout >= PENDRIVE_RESTORE_TIMEOUT) break;

            // check the encoder status
            button_status = actuator_get_status(encoder);
            if (BUTTON_CLICKED(button_status)) break;
            if (ENCODER_TURNED_ACW(button_status) && popup.button_selected == 1)
            {
                popup.button_selected = 0;
                widget_popup(PENDRIVE_RESTORE_DISPLAY, &popup);
            }
            else if (ENCODER_TURNED_CW(button_status) && popup.button_selected == 0)
            {
                popup.button_selected = 1;
                widget_popup(PENDRIVE_RESTORE_DISPLAY, &popup);
            }
        }
    }

    // checks if the YES button was pressed
    if (button_status && popup.button_selected == 0)
    {
        // gets the footswitches status
        status1 = BUTTON_PRESSED(actuator_get_status(foots[0]) | actuator_get_status(foots[2]));
        status2 = BUTTON_PRESSED(actuator_get_status(foots[1]) & actuator_get_status(foots[3]));

        // checks if footswitches combination is ok
        if (!status1 && status2)
        {
            // selects the grub pendrive entry
            cli_grub_select(PENDRIVE_ENTRY);
        }
    }
}

void system_true_bypass_cb(void *arg)
{
    menu_item_t *item = arg;
    item->data.hover = 1 - hardware_get_true_bypass();
    hardware_set_true_bypass(item->data.hover);
}

void system_reset_pedalboard_cb(void *arg)
{
    menu_item_t *item = arg;

    // checks if is the YES button
    if (item->data.hover == 0)
        comm_webgui_send(PEDALBOARD_RESET_CMD, strlen(PEDALBOARD_RESET_CMD));
}

void system_save_pedalboard_cb(void *arg)
{
    menu_item_t *item = arg;

    // checks if is the YES button
    if (item->data.hover == 0)
        comm_webgui_send(PEDALBOARD_SAVE_CMD, strlen(PEDALBOARD_SAVE_CMD));
}

void system_jack_quality_cb(void *arg)
{
    UNUSED_PARAM(arg);
    cli_jack_set_bufsize(JACK_BUF_SIZE_QUALITY);
}

void system_jack_normal_cb(void *arg)
{
    UNUSED_PARAM(arg);
    cli_jack_set_bufsize(JACK_BUF_SIZE_NORMAL);
}

void system_jack_performance_cb(void *arg)
{
    UNUSED_PARAM(arg);
    cli_jack_set_bufsize(JACK_BUF_SIZE_PERFORMANCE);
}

void system_services_cb(void *arg)
{
    menu_item_t *item = arg;
    const char *response;
    char *pstr;
    const char *services[] = {"is-active jackd",
                              "is-active mod-host",
                              "is-active mod-ui",
                              "is-active mod-bluez",
                              NULL};

    uint8_t i = 0;
    while (services[i])
    {
        cli_systemctl(services[i]);
        response = cli_get_response();

        pstr = strstr(item->data.list[i+1], ":");
        if (pstr && response)
        {
            pstr++;
            *pstr++ = ' ';
            strcpy(pstr, response);
            screen_system_menu(item);
        }

        i++;
    }
}

void system_versions_cb(void *arg)
{
    menu_item_t *item = arg;
    const char *response;
    char *pstr;
    const char *versions[] = {"jack2-mod",
                              "mod-host",
                              "mod-ui",
                              "mod-controller",
                              "mod-python",
                              "mod-resources",
                              "mod-bluez",
                              NULL};

    uint8_t i = 0;
    while (versions[i])
    {
        cli_package_version(versions[i]);
        response = cli_get_response();

        pstr = strstr(item->data.list[i+1], ":");
        if (pstr && response)
        {
            pstr++;
            *pstr++ = ' ';
            strcpy(pstr, response);
            screen_system_menu(item);
        }

        i++;
    }
}

void system_restore_cb(void *arg)
{
    menu_item_t *item = arg;
    button_t *foot = (button_t *) hardware_actuators(FOOTSWITCH3);

    // checks if is the YES button
    if (item->data.hover == 0)
    {
        uint8_t status = actuator_get_status(foot);

        // checks the if the footswitch is pressed
        if (BUTTON_PRESSED(status))
        {
            // removes all controls
            naveg_remove_control(ALL_EFFECTS, ALL_CONTROLS);

            // selects the grub restore entry and reboot
            cli_grub_select(RESTORE_ENTRY);
            cli_reboot_cpu();
        }
    }
}

