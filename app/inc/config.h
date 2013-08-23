
#ifndef CONFIG_H
#define CONFIG_H


////////////////////////////////////////////////////////////////
////// SETTINGS RELATED TO HARDWARE

//// Hardwares types (device identification)
#define QUADRA_HW       0
#define EXP_PEDAL_HW    1
#define XY_TABLET_HW    2

//// Actuators types
#define NONE            0
#define FOOT            1
#define KNOB            2
#define PEDAL           3

//// Slots count
// One slot is a set of display, knob, footswitch and led
#define SLOTS_COUNT         4

//// CPU pins
// defines the port and of CPU power button
#define CPU_BUTTON_PORT     1
#define CPU_BUTTON_PIN      23

// defines the port and of CPU power status
#define CPU_STATUS_PORT     1
#define CPU_STATUS_PIN      24

//// Cooler pins
#define COOLER_PORT         1
#define COOLER_PIN          22

//// ARM reset pin
// this pin is used to block/unblock the ARM reset
// to block the pin must be set to 0
// to unblock the pin must be configured to input
#define ARM_RESET_PORT      2
#define ARM_RESET_PIN       24

//// LEDs configuration
// Amount of LEDS
#define LEDS_COUNT          SLOTS_COUNT

// LEDs ports and pins definitions
// format definition: {R_PORT, R_PIN, G_PORT, G_PIN, B_PORT, B_PIN}
#define LED0_PINS           {3, 30, 3, 31, 3, 29}
#define LED1_PINS           {3, 27, 3, 28, 3, 26}
#define LED2_PINS           {3, 24, 3, 25, 3, 23}
#define LED3_PINS           {3, 21, 3, 22, 3, 20}

//// GLCDs configurations
// Amount of displays
#define GLCD_COUNT          SLOTS_COUNT

//// Actuators configuration
// Actuators IDs
enum {ENCODER0, ENCODER1, ENCODER2, ENCODER3, FOOTSWITCH0, FOOTSWITCH1, FOOTSWITCH2, FOOTSWITCH3};

// Amount of footswitches
#define FOOTSWITCHES_COUNT  SLOTS_COUNT

// Footswitches ports and pins definitions
// button definition: {BUTTON_PORT, BUTTON_PIN}
#define FOOTSWITCH0_PINS    {2, 17}
#define FOOTSWITCH1_PINS    {2, 16}
#define FOOTSWITCH2_PINS    {2, 15}
#define FOOTSWITCH3_PINS    {2, 14}

// Amount of encoders
#define ENCODERS_COUNT      SLOTS_COUNT

// Encoders ports and pins definitions
// encoder definition: {ENC_BUTTON_PORT, ENC_BUTTON_PIN, ENC_CHA_PORT, ENC_CHA_PIN, ENC_CHB_PORT, ENC4_CH_PIN}
#define ENCODER0_PINS       {0, 8, 2, 28, 2, 3}
#define ENCODER1_PINS       {0, 4, 2, 25, 2, 0}
#define ENCODER2_PINS       {0, 5, 2, 26, 2, 1}
#define ENCODER3_PINS       {0, 7, 2, 27, 2, 2}

//// True bypass configuration
#define TRUE_BYPASS_PORT        3
#define TRUE_BYPASS_PIN         19

//// Headphone configuration
// headphone controller ports and pins definition
#define HEADPHONE_SDA_PORT      0
#define HEADPHONE_SDA_PIN       9
#define HEADPHONE_SCL_PORT      4
#define HEADPHONE_SCL_PIN       29
// ADC port and pin definition
#define HEADPHONE_ADC_PORT      0
#define HEADPHONE_ADC_PIN       24
// ADC pin configuration, defines the ADC function number
#define HEADPHONE_ADC_PIN_CONF  1
// ADC headphone clock convertion in Hz
#define HEADPHONE_ADC_CLOCK     1000
// ADC headphone channel
#define HEADPHONE_ADC_CHANNEL   1


////////////////////////////////////////////////////////////////
////// SETTINGS RELATED TO FIRMWARE
//// Protocol commands configuration
// ping
#define PING_CMD                "ping"
// say <message>
#define SAY_CMD                 "say %s ..."
// led <led_id> <red> <green> <blue>
#define LED_CMD                 "led %i %i %i %i ..."
// ui_con
#define GUI_CONNECTED_CMD       "ui_con"
// ui_dis
#define GUI_DISCONNECTED_CMD    "ui_dis"
// control_add <effect_instance> <symbol> <label> <control_prop> <unit> <value> <max> <min>
//             <steps> <hw_type> <hw_id> <actuator_type> <actuator_id> [scale_point_count] {[scale_point1_label] [scale_point1_value]}...
#define CONTROL_ADD_CMD         "control_add %i %s %s %i %s %f %f %f %i %i %i %i %i ..."
// control_rm <effect_instance> <symbol>
#define CONTROL_REMOVE_CMD      "control_rm %i %s"
// control_get <effect_instance> <symbol>
#define CONTROL_GET_CMD         "control_get %i %s"
// control_set <effect_instance> <symbol> <value>
#define CONTROL_SET_CMD         "control_set %i %s %f"
// banks
#define BANKS_CMD               "banks"
// bank_config <hw_type> <hw_id> <actuator_type> <actuator_id> <function>
#define BANK_CONFIG_CMD         "bank_config %i %i %i %i %i"
// pedalboards <bank_uid>
#define PEDALBOARDS_CMD         "pedalboards %s"
// pedalboard <bank_id> <pedalboard_uid>
#define PEDALBOARD_CMD          "pedalboard %i %s"
// pedalboard_reset
#define PEDALBOARD_RESET_CMD    "pedalboard_reset"
// pedalboard_save
#define PEDALBOARD_SAVE_CMD     "pedalboard_save"
// clipmeter <clipmeter_id>
#define CLIPMETER_CMD           "clipmeter %i"
// peakmeter <peakmeter_number> <peakmeter_value>
#define PEAKMETER_CMD           "peakmeter %i %f"
// tuner <frequency> <note> <cents>
#define TUNER_CMD               "tuner %f %s %i"
// xrun
#define XRUN_CMD                "xrun"
// hw_con <hw_type> <hw_id>
#define HW_CONNECTED_CMD        "hw_con %i %i"
// hw_dis <hw_type> <hw_id>
#define HW_DISCONNECTED_CMD     "hw_dis %i %i"
// resp <status> ...
#define RESPONSE_CMD            "resp %i ..."

//// Control propertires definitions
#define CONTROL_PROP_LINEAR         0
#define CONTROL_PROP_LOGARITHMIC    1
#define CONTROL_PROP_ENUMERATION    2
#define CONTROL_PROP_TOGGLED        3
#define CONTROL_PROP_TRIGGER        4
#define CONTROL_PROP_TAP_TEMPO      5
#define CONTROL_PROP_BYPASS         6
#define CONTROL_PROP_INTEGER        7

//// Banks functions definition
#define BANK_FUNC_NONE              0
#define BANK_FUNC_TRUE_BYPASS       1
#define BANK_FUNC_PEDALBOARD_NEXT   2
#define BANK_FUNC_PEDALBOARD_PREV   3
#define BANK_FUNC_AMOUNT            4

//// Tools configuration
// tools identification (don't change)
#define TOOL_SYSTEM         0
#define TOOL_TUNER          1
#define TOOL_PEAKMETER      2
#define TOOL_NAVEG          3

// time in milliseconds to enter in tool mode (hold rotary encoder button)
#define TOOL_MODE_TIME      2000

// setup of tools on displays
#define TOOL_DISPLAY0       TOOL_SYSTEM
#define TOOL_DISPLAY1       TOOL_TUNER
#define TOOL_DISPLAY2       TOOL_PEAKMETER
#define TOOL_DISPLAY3       TOOL_NAVEG

// peakmeter tool display definition (don't change)
#if (TOOL_PEAKMETER == TOOL_DISPLAY0)
#define PEAKMETER_DISPLAY   TOOL_DISPLAY0
#elif (TOOL_PEAKMETER == TOOL_DISPLAY1)
#define PEAKMETER_DISPLAY   TOOL_DISPLAY1
#elif (TOOL_PEAKMETER == TOOL_DISPLAY2)
#define PEAKMETER_DISPLAY   TOOL_DISPLAY2
#elif (TOOL_PEAKMETER == TOOL_DISPLAY3)
#define PEAKMETER_DISPLAY   TOOL_DISPLAY3
#endif

// tuner tool display definition (don't change)
#if (TOOL_TUNER == TOOL_DISPLAY0)
#define TUNER_DISPLAY   TOOL_DISPLAY0
#elif (TOOL_TUNER == TOOL_DISPLAY1)
#define TUNER_DISPLAY   TOOL_DISPLAY1
#elif (TOOL_TUNER == TOOL_DISPLAY2)
#define TUNER_DISPLAY   TOOL_DISPLAY2
#elif (TOOL_TUNER == TOOL_DISPLAY3)
#define TUNER_DISPLAY   TOOL_DISPLAY3
#endif

// banks/pedalboards navegation display definition (don't change)
#if (TOOL_NAVEG == TOOL_DISPLAY0)
#define NAVEG_DISPLAY   TOOL_DISPLAY0
#elif (TOOL_NAVEG == TOOL_DISPLAY1)
#define NAVEG_DISPLAY   TOOL_DISPLAY1
#elif (TOOL_NAVEG == TOOL_DISPLAY2)
#define NAVEG_DISPLAY   TOOL_DISPLAY2
#elif (TOOL_NAVEG == TOOL_DISPLAY3)
#define NAVEG_DISPLAY   TOOL_DISPLAY3
#endif

// system menu display definition (don't change)
#if (TOOL_SYSTEM == TOOL_DISPLAY0)
#define SYSTEM_DISPLAY   TOOL_DISPLAY0
#elif (TOOL_SYSTEM == TOOL_DISPLAY1)
#define SYSTEM_DISPLAY   TOOL_DISPLAY1
#elif (TOOL_SYSTEM == TOOL_DISPLAY2)
#define SYSTEM_DISPLAY   TOOL_DISPLAY2
#elif (TOOL_SYSTEM == TOOL_DISPLAY3)
#define SYSTEM_DISPLAY   TOOL_DISPLAY3
#endif

//// System menu configuration
// includes the system menu callbacks
#include "system.h"
// menu definition, format: {name, type, id, parent_id, action_callback}
#define SYSTEM_MENU     \
    {"SETTINGS",                            MENU_LIST,       0,     -1,     NULL},    \
    {"True Bypass                   ",      MENU_ON_OFF,     1,      0,     system_true_bypass_cb}, \
    {"Pedalboard",                          MENU_LIST,       2,      0,     NULL},    \
    {"< Back to SETTINGS",                  MENU_RETURN,     3,      2,     NULL},    \
    {"Reset State",                         MENU_CONFIRM,    4,      2,     NULL},    \
    {"Save State",                          MENU_CONFIRM,    5,      2,     NULL},    \
    {"Expression Pedal",                    MENU_LIST,       6,      2,     NULL},    \
    {"< Back to Pedalboard",                MENU_RETURN,     7,      6,     NULL},    \
    {"Bluetooth",                           MENU_LIST,       8,      0,     NULL},    \
    {"< Back to SETTINGS",                  MENU_RETURN,     9,      8,     NULL},    \
    {"Status                           ",   MENU_ON_OFF,    10,      8,     NULL},    \
    {"Name",                                MENU_NONE,      11,      8,     NULL},    \
    {"Address",                             MENU_NONE,      12,      8,     NULL},    \
    {"PIN",                                 MENU_NONE,      13,      8,     NULL},    \
    {"Reset PIN",                           MENU_CONFIRM,   14,      8,     NULL},    \
    {"Jack",                                MENU_LIST,      15,      0,     NULL},    \
    {"< Back to SETTINGS",                  MENU_RETURN,    16,     15,     NULL},    \
    {"Quality",                             MENU_NONE,      17,     15,     NULL},    \
    {"Normal",                              MENU_NONE,      18,     15,     NULL},    \
    {"Performance",                         MENU_NONE,      19,     15,     NULL},    \
    {"Info",                                MENU_LIST,      20,      0,     NULL},    \
    {"< Back to SETTINGS",                  MENU_RETURN,    21,     20,     NULL},    \
    {"CPU",                                 MENU_LIST,      22,     20,     NULL},    \
    {"< Back to Info",                      MENU_RETURN,    23,     22,     NULL},    \
    {"Services",                            MENU_LIST,      24,     20,     NULL},    \
    {"< Back to Info",                      MENU_RETURN,    25,     24,     NULL},    \
    {"Versions",                            MENU_LIST,      26,     20,     NULL},    \
    {"< Back to Info",                      MENU_RETURN,    27,     26,     NULL},    \
    {"Factory Restore",                     MENU_CONFIRM,   28,      0,     system_restore_cb},

// popups text content, format : {menu_id, text_content}
#define POPUP_CONTENT   \
    {28, "To proceed with Factory Restore you need to hold the last footswitch and click YES."},


//// Icons configuration
// xrun display
#define XRUN_ICON_DISPLAY       0
// xrun timeout (in milliseconds)
#define XRUN_TIMEOUT            1000
// clipmeter timeout (in milliseconds)
#define CLIPMETER_TIMEOUT       100

//// Serial Configurations
// serial baudrates
#define SERIAL0_BAUDRATE        115200
#define SERIAL1_BAUDRATE        115200
// If the serial ISR uses freeRTOS API, the priorities values must be
// equal or greater than configMAX_SYSCALL_INTERRUPT_PRIORITY
#define SERIAL0_PRIORITY        6
#define SERIAL1_PRIORITY        6

//// Communication definitions
// defines the UART port used to communication between HMI and linux serial console
#define LINUX_SERIAL            1

//// Foot functions leds colors
#define TOGGLED_COLOR           GREEN
#define TRIGGER_COLOR           GREEN
#define TAP_TEMPO_COLOR         GREEN
#define ENUMERATED_COLOR        GREEN
#define BYPASS_COLOR            RED
#define TRUE_BYPASS_COLOR       WHITE
#define PEDALBOARD_NEXT_COLOR   WHITE
#define PEDALBOARD_PREV_COLOR   WHITE

//// Tap Tempo
// defines the time that the led will stay turned on (in milliseconds)
#define TAP_TEMPO_TIME_ON       20

//// Toggled
// defines the toggled footer text
#define TOGGLED_ON_FOOTER_TEXT      "ON"
#define TOGGLED_OFF_FOOTER_TEXT     "OFF"

//// Bypass
// defines the bypass footer text
#define BYPASS_ON_FOOTER_TEXT       "BYP"
#define BYPASS_OFF_FOOTER_TEXT      "PROC"

//// Bank configuration functions
// defines the true bypass footer text
#define TRUE_BYPASS_FOOTER_TEXT     "TRUE BYPASS"
// defines the next pedalboard footer text
#define PEDALBOARD_NEXT_FOOTER_TEXT "+"
// defines the previous pedalboard footer text
#define PEDALBOARD_PREV_FOOTER_TEXT "-"

//// Jack buffer size configuration
#define JACK_BUF_SIZE_QUALITY       128
#define JACK_BUF_SIZE_NORMAL        256
#define JACK_BUF_SIZE_PERFORMANCE   512

//// Pendrive restore definitions
// defines the display where the popup will be showed
#define PENDRIVE_RESTORE_DISPLAY    0
// defines the popup title when the pendrive restore is invoked
#define PENDRIVE_RESTORE_TITLE      "Pendrive Restore"
// defines the popup title when the pendrive restore is invoked
#define PENDRIVE_RESTORE_CONTENT    "To proceed with Pendrive Restore you need to hold the footswitches 2 and 4 and click YES."
// defines the timeout for wait the user response (in seconds)
#define PENDRIVE_RESTORE_TIMEOUT    30

//// Dynamic menory allocation
// these macros should be used in replacement to default malloc and free functions of stdlib.h
#include "FreeRTOS.h"
#define MALLOC(n)       pvPortMalloc(n)
#define FREE(pv)        vPortFree(pv)

#endif
