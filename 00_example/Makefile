################################################################################
# 
# The MIT License (MIT)
# Copyright (c) 2019 STMicroelectronics
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# 
################################################################################

# System configuration
CC = arm-atollic-eabi-gcc
RM=rm -rf

WD = $(shell pwd)
PARWD = $(shell dirname $(WD))/
PROJ_NAME = $(shell echo $(WD) | sed "s|$(PARWD)||g")

# Assembler, Compiler and Linker flags and linker script settings
LINKER_FLAGS=-lm -mthumb -mhard-float -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -Wl,--gc-sections -T$(LINK_SCRIPT) -static  -Wl,--start-group -lc -lm -Wl,--end-group -specs=nano.specs -specs=nosys.specs  -Wl,-cref "-Wl,-Map=$(BIN_DIR)/$(PROJ_NAME).map" -Wl,--defsym=malloc_getpagesize_P=0x1000
LINK_SCRIPT="stm32f4_flash.ld"
ASSEMBLER_FLAGS=-c -g -O0 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mhard-float -specs=nano.specs -D"STM32F4XX" -D"STM32F40XX" -D"USE_STDPERIPH_DRIVER" -D"HSE_VALUE=8000000" -x assembler-with-cpp  -Isrc -ILibraries/CMSIS/Include -ILibraries/Device/STM32F4xx/Include -ILibraries/STM32F4xx_StdPeriph_Driver/inc -ILibraries/glesk/inc
COMPILER_FLAGS=-c -g -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -O0 -Wall -ffunction-sections -fdata-sections -mthumb -mhard-float -specs=nano.specs -D"STM32F4XX" -D"STM32F40XX" -D"USE_STDPERIPH_DRIVER" -D"HSE_VALUE=8000000"  -Isrc -ILibraries/CMSIS/Include -ILibraries/Device/STM32F4xx/Include -ILibraries/STM32F4xx_StdPeriph_Driver/inc -ILibraries/glesk/inc

# Define output directory
OBJECT_DIR = Debug
BIN_DIR = $(OBJECT_DIR)

# Define sources and objects
SRC := $(wildcard */*/*/*/*/*/*/*.c) \
	$(wildcard */*/*/*/*/*/*.c) \
	$(wildcard */*/*/*/*/*.c) \
	$(wildcard */*/*/*/*.c) \
	$(wildcard */*/*/*.c) \
	$(wildcard */*/*.c) \
	$(wildcard */*.c)
SRCSASM := 	$(wildcard */*/*/*/*/*/*/*/*.s) \
	$(wildcard */*/*/*/*/*/*/*.s) \
	$(wildcard */*/*/*/*/*/*.s) \
	$(wildcard */*/*/*/*/*.s) \
	$(wildcard */*/*/*/*.s) \
	$(wildcard */*/*/*.s) \
	$(wildcard */*/*.s) \
	$(wildcard */*.s)
OBJS := $(SRC:%.c=$(OBJECT_DIR)/%.o) $(SRCSASM:%.s=$(OBJECT_DIR)/%.o)
OBJS := $(OBJS:%.S=$(OBJECT_DIR)/%.o)  

###############
# Build project
# Major targets
###############
all: buildelf

buildelf: $(OBJS) 
	$(CC) -o "$(BIN_DIR)/$(PROJ_NAME).elf" $(OBJS) $(LINKER_FLAGS)

clean:
	$(RM) $(OBJS) "$(BIN_DIR)/$(PROJ_NAME).elf" "$(BIN_DIR)/$(PROJ_NAME).map"


##################
# Specific targets
##################
$(OBJECT_DIR)/src/main.o: src/main.c
	@mkdir -p $(dir $@) 2> /dev/null
	$(CC) $(COMPILER_FLAGS) src/main.c -o $(OBJECT_DIR)/src/main.o 


##################
# Implicit targets
##################
$(OBJECT_DIR)/%.o: %.c
	@mkdir -p $(dir $@) 2> /dev/null
	$(CC) $(COMPILER_FLAGS) $< -o $@

$(OBJECT_DIR)/%.o: %.s
	@mkdir -p $(dir $@) 2> /dev/null
	$(CC) $(ASSEMBLER_FLAGS) $< -o $@
	
$(OBJECT_DIR)/%.o: %.S
	@mkdir -p $(dir $@) 2> /dev/null
	$(CC) $(ASSEMBLER_FLAGS) $< -o $@
