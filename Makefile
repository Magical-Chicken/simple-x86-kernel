CWD 	= $(shell pwd)
BUILD_D = $(CWD)/build
SRC_D 	= $(CWD)/src
TARGET 	= $(CWD)/kernel
LCONF 	= link.ld

CC 		= gcc
ASM 	= as
LL 		= ld
CFLAGS 	= -m32 -nostdlib -nodefaultlibs -fno-builtin -Wextra -O2 -std=gnu11

INC 	= $(shell find | grep '\.h')
OBJ 	= $(shell find | grep '\.c' | sed -e 's/\.c/\.o/' | sed -e 's/src/build/')

kernel: $(OBJ) $(INC)
	$(LL) -m elf_i386 -T $(LCONF) -o $(TARGET) $^

build/load.o: load.asm
	$(ASM) -f elf32 -o $@ $^

build/%.o: src/%.c $(INC)
	$(CC) $(CFLAGS) -c -o $@ $<

test: kernel
	qemu-system-i386 --kernel $(TARGET)

clean:
	rm -rf $(BUILD_D)/*
