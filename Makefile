CWD 	= $(shell pwd)
BUILD_D = $(CWD)/build
SRC_D 	= $(CWD)/src
TARGET 	= $(CWD)/kernel
LCONF 	= link.ld
LOADER	= load.asm

CC 		= gcc
ASM 	= nasm
LL 		= ld
CFLAGS 	= -m32 -nostdlib -nodefaultlibs -fno-builtin -Wextra -O2 -std=gnu11

INC 	= $(shell find $(CWD) -name '*.h')
OBJ 	= $(shell find $(CWD) -name '*.c' | sed -e 's/\.c/\.o/' | sed -e 's/src/build/')

kernel: $(OBJ) $(BUILD_D)/load.o
	$(LL) -m elf_i386 -T $(LCONF) -o $(TARGET) $^

$(BUILD_D)/load.o: $(LOADER)
	nasm -f elf32 -o $@ $^

$(BUILD_D)/%.o: src/%.c $(INC)
	$(CC) $(CFLAGS) -c -o $@ $<

test: kernel
	qemu-system-i386 --kernel $(TARGET)

clean:
	rm -rf $(BUILD_D)/*
