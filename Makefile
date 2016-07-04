# build dirs
CWD 	= $(shell pwd)
BUILD_D = $(CWD)/build
SRC_D 	= $(CWD)/src
TARGETK	= $(CWD)/kernel
TARGETI	= $(CWD)/boot.iso

# executables
CC 		= gcc
ASM 	= as
LL 		= ld
QEMU 	= qemu-system-x86_64

# build flags
CFLAGS 	= -m32 -ffreestanding -Wextra -Wpedantic -O2 -std=gnu11
ASFLAGS = --32
LCONF 	= link.ld

# feature flags
VGAFLAGS= -DVGA_WIDTH=80 -DVGA_HEIGHT=8
FFLAGS  = $(VGAFLAGS)

# emulation options
GRUB_C  = $(CWD)/grub/menu.cfg
EMUFLAG	= -cpu core2duo -m 1024

# code ident
INC 	= $(shell find $(CWD) -name '*.h')
COBJ 	= $(shell find $(CWD) -name '*.c' | sed -e 's/\.c/\.o/' | sed -e 's/src/build/')
ASMOBJ 	= $(shell find $(CWD) -name '*.asm' | sed -e 's/\.asm/\.o/' | sed -e 's/src/build/')

kernel: $(COBJ) $(ASMOBJ)
	$(LL) -m elf_i386 -T $(LCONF) -o $(TARGETK) $^

$(BUILD_D)/%.o: $(SRC_D)/%.asm
	@mkdir -p $(@D)
	$(ASM) $(ASFLAGS) -o $@ $^

$(BUILD_D)/%.o: $(SRC_D)/%.c $(INC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(FFLAGS) -c -o $@ $<

grub_image: kernel
	@$(CWD)/tools/build_grub_img.sh $(TARGETI) $(TARGETK) $(GRUB_C)

test: grub_image
	$(QEMU) $(EMUFLAG) -cdrom $(TARGETI)

ctest: grub_image
	$(QEMU) $(EMUFLAG) -curses -cdrom $(TARGETI)

clean:
	rm -rf $(BUILD_D) $(TARGETK) $(TARGETI)
