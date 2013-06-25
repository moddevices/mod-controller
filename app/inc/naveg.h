
/*
************************************************************************************************************************
*
************************************************************************************************************************
*/

#ifndef NAVEG_H
#define NAVEG_H


/*
************************************************************************************************************************
*           INCLUDE FILES
************************************************************************************************************************
*/

#include <stdint.h>
#include "data.h"


/*
************************************************************************************************************************
*           DO NOT CHANGE THESE DEFINES
************************************************************************************************************************
*/


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

// initialize the navigation nodes and structs
void naveg_init(void);
// adds the control to end of the controls list
void naveg_add_control(control_t *control);
// removes the control from controls list
void naveg_remove_control(uint8_t effect_instance, const char *symbol);
// increment the control value
void naveg_inc_control(uint8_t display);
// decrement the control value
void naveg_dec_control(uint8_t display);
// sets the control value
void naveg_set_control(uint8_t effect_instance, const char *symbol, float value);
// gets the control value
float naveg_get_control(uint8_t effect_instance, const char *symbol);
// goes to the next control of the controls list
control_t *naveg_next_control(uint8_t display);
// change the foot value
void naveg_foot_change(uint8_t foot);
// toggle between control and tool
void naveg_toggle_tool(uint8_t display);
// returns if display is in tool mode
uint8_t naveg_is_tool_mode(uint8_t display);
// stores the banks/pedalbords list
void naveg_save_bp_list(bp_list_t *bp_list);
// returns the banks/pedalbords list like
bp_list_t *naveg_get_bp_list(void);
// runs the enter action on banks/pedalbords navegation
void naveg_bp_enter(void);
// goes one step up on list
void naveg_bp_up(void);
// goes one step down on list
void naveg_bp_down(void);


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
