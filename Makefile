# project name
PRJNAME = mod-controller

# toolchain configuration
PATH := ${PATH}:/opt/toolchain/arm-bare_newlib_cortex_m3_nommu-eabi/bin/
TOOLCHAIN_PREFIX = arm-cortexm3-bare-

# cpu configuration
THUMB = -mthumb
MCU = cortex-m3

# build configuration
ifeq ($(mod),duo)
CPU = LPC1759
CPU_SERIE = LPC17xx
else
mod = quadra
CPU = LPC1788
CPU_SERIE = LPC177x_8x
endif

# project directories
DEVICE_INC	= ./nxp-lpc
CMSIS_INC	= ./nxp-lpc/CMSISv2p00_$(CPU_SERIE)/inc
CMSIS_SRC	= ./nxp-lpc/CMSISv2p00_$(CPU_SERIE)/src
CDL_INC 	= ./nxp-lpc/$(CPU_SERIE)Lib/inc
CDL_SRC 	= ./nxp-lpc/$(CPU_SERIE)Lib/src
APP_INC 	= ./app/inc
APP_SRC 	= ./app/src
RTOS_SRC	= ./freertos/src
RTOS_INC	= ./freertos/inc
DRIVERS_INC	= ./drivers/inc
DRIVERS_SRC	= ./drivers/src
USB_INC 	= ./usb/inc
USB_SRC 	= ./usb/src
OUT_DIR		= ./out

SRC = $(wildcard $(CMSIS_SRC)/*.c) $(wildcard $(CDL_SRC)/*.c) $(wildcard $(RTOS_SRC)/*.c) \
	  $(wildcard $(DRIVERS_SRC)/*.c) $(wildcard $(APP_SRC)/*.c) $(wildcard $(USB_SRC)/*.c)

# Object files
OBJ = $(SRC:.c=.o)
ALL_OBJ = `find -name "*.o"`

# include directories
INC = $(DEVICE_INC) $(CMSIS_INC) $(CDL_INC) $(RTOS_INC) $(DRIVERS_INC) $(APP_INC) $(USB_INC)

# build again when changes this files
BUILD_ON_CHANGE = Makefile $(APP_INC)/config.h

# C flags
CFLAGS += -mcpu=$(MCU)
CFLAGS += -Wall -Wextra -Werror -Wpointer-arith -Wredundant-decls
#CFLAGS += -Wcast-align -Wcast-qual
CFLAGS += -Wa,-adhlns=$(addprefix $(OUT_DIR)/, $(notdir $(addsuffix .lst, $(basename $<))))
CFLAGS += -MMD -MP -MF $(OUT_DIR)/dep/$(@F).d
CFLAGS += -I. $(patsubst %,-I%,$(INC))
CFLAGS += -D$(CPU_SERIE)
CFLAGS += -DCONTROLLER_HASH_COMMIT=`git log -1 --pretty=format:\"%h\"`

# Linker flags
LDFLAGS = -Wl,-Map=$(OUT_DIR)/$(PRJNAME).map,--cref
LDFLAGS += -L. $(patsubst %,-L%,$(LIBDIR))
LDFLAGS += -lc -lgcc -lm
LDFLAGS += -T./link/LPC.ld

# Define programs and commands.
CC      = $(TOOLCHAIN_PREFIX)gcc
OBJCOPY = $(TOOLCHAIN_PREFIX)objcopy
OBJDUMP = $(TOOLCHAIN_PREFIX)objdump
NM      = $(TOOLCHAIN_PREFIX)nm
SIZE    = $(TOOLCHAIN_PREFIX)size

# Colors definitions
GREEN 	= '\e[0;32m'
NOCOLOR	= '\e[0m'

all: prebuild build

build: elf lss sym hex bin

# output files
elf: $(OUT_DIR)/$(PRJNAME).elf
lss: $(OUT_DIR)/$(PRJNAME).lss
sym: $(OUT_DIR)/$(PRJNAME).sym
hex: $(OUT_DIR)/$(PRJNAME).hex
bin: $(OUT_DIR)/$(PRJNAME).bin

prebuild:
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OUT_DIR)/dep
	@ln -fs ./$(CPU).ld ./link/LPCmem.ld
	@ln -fs ./config-$(mod).h ./app/inc/config.h

# Create final output file in ihex format from ELF output file (.hex).
%.hex: %.elf
	@echo -e ${GREEN}Creating HEX${NOCOLOR}
	@$(OBJCOPY) -O ihex $< $@

# Create final output file in raw binary format from ELF output file (.bin)
%.bin: %.elf
	@echo -e ${GREEN}Creating BIN${NOCOLOR}
	@$(OBJCOPY) -O binary $< $@

# Create extended listing file/disassambly from ELF output file.
# using objdump (testing: option -C)
%.lss: %.elf
	@echo -e ${GREEN}Creating listing file/disassambly${NOCOLOR}
	@$(OBJDUMP) -h -S -C -r $< > $@

# Create a symbols table from ELF output file.
%.sym: %.elf
	@echo -e ${GREEN}Creating symbols table${NOCOLOR}
	@$(NM) -n $< > $@

# Link: create ELF output file from object files.
%.elf: $(OBJ) $(BUILD_ON_CHANGE)
	@echo -e ${GREEN}Linking objects: generating ELF${NOCOLOR}
	@$(CC) $(THUMB) $(CFLAGS) $(OBJ) --output $@ -nostartfiles $(LDFLAGS)

%.o: %.c
	@echo -e ${GREEN}Building $<${NOCOLOR}
	@$(CC) $(THUMB) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(ALL_OBJ) $(OUT_DIR)

size:
	@$(SIZE) out/mod-controller.elf