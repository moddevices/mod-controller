
/*
************************************************************************************************************************
*
************************************************************************************************************************
*/

#ifndef SCREEN_H
#define SCREEN_H


/*
************************************************************************************************************************
*           INCLUDE FILES
************************************************************************************************************************
*/

#include <stdint.h>
#include "config.h"
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

void screen_clear(uint8_t display_id);
void screen_control(uint8_t display_id, control_t *control);
void screen_controls_index(uint8_t display_id, uint8_t current, uint8_t max);
void screen_encoder_box(uint8_t display_id, control_t *control);
void screen_control_pot(uint8_t id, uint8_t display, control_t *control);
void screen_pot_box_left(uint8_t display_id, control_t *control);
void screen_pot_box_right(uint8_t display_id, control_t *control);
void screen_footer(uint8_t display_id, const char *name, const char *value);
void screen_footer_pot_left(uint8_t display_id, control_t *control);
void screen_footer_pot_right(uint8_t display_id, control_t *control);
void screen_footer_button_left(uint8_t display_id, const char *name, const char *value);
void screen_footer_button_right(uint8_t display_id, const char *name, const char *value);
void screen_tool(uint8_t tool, uint8_t display_id);
void screen_bp_list(const char *title, bp_list_t *list);
void screen_system_menu(menu_item_t *item);
void screen_tuner(float frequency, char *note, int8_t cents);
void screen_tuner_input(uint8_t input);
void screen_image(uint8_t display, const uint8_t *image);



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
