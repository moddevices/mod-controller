# project name
PRJNAME = mod-controller

# toolchain configuration
PATH := ${PATH}:/opt/toolchain/arm-bare_newlib_cortex_m3_nommu-eabi/bin/
TOOLCHAIN_PREFIX = arm-cortexm3-bare-

# cpu configuration
THUMB = -mthumb
MCU   = cortex-m3

# project directories
APP_INC 	= ./app/inc
APP_SRC 	= ./app/src
CMSIS_INC 	= ./cmsis/inc
CMSIS_SRC	= ./cmsis/src
RTOS_SRC	= ./freertos/src
RTOS_INC	= ./freertos/inc
PDL_INC 	= ./pdl/inc
PDL_SRC 	= ./pdl/src
DRIVERS_INC	= ./drivers/inc
DRIVERS_SRC	= ./drivers/src
USB_INC 	= ./usb/inc
USB_SRC 	= ./usb/src
OUT_DIR		= ./out
TESTS_SRC	= ./tests

# Used PDL drivers
PDL = lpc177x_8x_gpio.c lpc177x_8x_pinsel.c lpc177x_8x_clkpwr.c lpc177x_8x_uart.c lpc177x_8x_timer.c lpc177x_8x_adc.c

# C source files
SRC = $(wildcard $(APP_SRC)/*.c) $(wildcard $(CMSIS_SRC)/*.c) $(wildcard $(RTOS_SRC)/*.c) \
	  $(addprefix $(PDL_SRC)/,$(PDL)) $(wildcard $(DRIVERS_SRC)/*.c) $(wildcard $(USB_SRC)/*.c)

# Build tests?
ifdef TESTS
SRC += $(wildcard $(TESTS_SRC)/*.c)
endif

# Object files
OBJ = $(SRC:.c=.o)

# include directories
INC = $(APP_INC) $(CMSIS_INC) $(RTOS_INC) $(PDL_INC) $(DRIVERS_INC) $(USB_INC) $(TESTS_SRC)

# build again when changes this files
BUILD_ON_CHANGE = Makefile $(APP_INC)/config.h

# C flags
CFLAGS += -mcpu=$(MCU)
CFLAGS += -Wall -Wextra -Werror -Wpointer-arith -Wredundant-decls
#CFLAGS += -Wcast-align -Wcast-qual
CFLAGS += -Wa,-adhlns=$(addprefix $(OUT_DIR)/, $(notdir $(addsuffix .lst, $(basename $<))))
CFLAGS += -MMD -MP -MF $(OUT_DIR)/dep/$(@F).d
CFLAGS += -I. $(patsubst %,-I%,$(INC))
CFLAGS += -DCONTROLLER_HASH_COMMIT=`git log -1 --pretty=format:\"%h\"`

# Linker flags
LDFLAGS = -Wl,-Map=$(OUT_DIR)/$(PRJNAME).map,--cref
LDFLAGS += -L. $(patsubst %,-L%,$(LIBDIR))
LDFLAGS += -lc -lgcc -lm
LDFLAGS += -T./lpc1788.ld

# Define programs and commands.
CC      = $(TOOLCHAIN_PREFIX)gcc
OBJCOPY = $(TOOLCHAIN_PREFIX)objcopy
OBJDUMP = $(TOOLCHAIN_PREFIX)objdump
NM      = $(TOOLCHAIN_PREFIX)nm

all: createdirs build

build: elf lss sym hex bin

# output files
elf: $(OUT_DIR)/$(PRJNAME).elf
lss: $(OUT_DIR)/$(PRJNAME).lss
sym: $(OUT_DIR)/$(PRJNAME).sym
hex: $(OUT_DIR)/$(PRJNAME).hex
bin: $(OUT_DIR)/$(PRJNAME).bin

createdirs:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OUT_DIR)/dep

# Create final output file in ihex format from ELF output file (.hex).
%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

# Create final output file in raw binary format from ELF output file (.bin)
%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

# Create extended listing file/disassambly from ELF output file.
# using objdump (testing: option -C)
%.lss: %.elf
	$(OBJDUMP) -h -S -C -r $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	$(NM) -n $< > $@

# Link: create ELF output file from object files.
%.elf: $(OBJ) $(BUILD_ON_CHANGE)
	$(CC) $(THUMB) $(CFLAGS) $(OBJ) --output $@ -nostartfiles $(LDFLAGS)

%.o: %.c
	$(CC) $(THUMB) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OUT_DIR)
