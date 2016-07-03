# build dirs
CWD 	= $(shell pwd)
BUILD_D = $(CWD)/build
SRC_D 	= $(CWD)/src
TARGET 	= $(CWD)/kernel

# executables
CC 		= gcc
ASM 	= nasm
LL 		= ld
QEMU 	= qemu-system-x86_64

# loader conf
LCONF 	= link.ld
LOADER	= load.asm

# build flags
CFLAGS 	= -m32 -ffreestanding -Wextra -Wpedantic -O2 -std=gnu11

# feature flags
VGAFLAGS= -DVGA_WIDTH=80 -DVGA_HEIGHT=8
FFLAGS  = $(VGAFLAGS)

# emulation options
EMUFLAG	= -cpu core2duo -m 1024

# code ident
INC 	= $(shell find $(CWD) -name '*.h')
OBJ 	= $(shell find $(CWD) -name '*.c' | sed -e 's/\.c/\.o/' | sed -e 's/src/build/')

kernel: $(OBJ) $(BUILD_D)/load.o
	$(LL) -m elf_i386 -T $(LCONF) -o $(TARGET) $^

$(BUILD_D)/load.o: $(LOADER)
	nasm -f elf32 -o $@ $^

$(BUILD_D)/%.o: src/%.c $(INC) init
	$(CC) $(CFLAGS) $(FFLAGS) -c -o $@ $<

init:
	mkdir -p $(BUILD_D)

test: kernel
	$(QEMU) $(EMUFLAG) -kernel $(TARGET)

ctest: kernel
	$(QEMU) $(EMUFLAG) -curses -kernel $(TARGET)

clean:
	rm -rf $(BUILD_D)/*
