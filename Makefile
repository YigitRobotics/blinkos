CC      = i686-elf-gcc
AS      = i686-elf-as

CFLAGS  = -m32 -ffreestanding -fno-pie -fno-stack-protector
LDFLAGS = -m32 -T src/linker.ld -ffreestanding -nostdlib

ISO     = blinkos.iso
ROOT    = root

C_SRCS := $(shell find src -name '*.c')
S_SRCS := $(shell find src -name '*.s')

C_OBJS := $(C_SRCS:.c=.o)
S_OBJS := $(S_SRCS:.s=.o)

OBJS := $(C_OBJS) $(S_OBJS)

all: $(ISO)

$(ISO): kernel.bin
	cp kernel.bin $(ROOT)/boot/kernel.bin
	grub-mkrescue -o $(ISO) $(ROOT)
	@echo "Success!"

kernel.bin: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lgcc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) --32 $< -o $@

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO) -display sdl

clean:
	find src -name '*.o' -delete
	rm -f kernel.bin $(ISO) $(ROOT)/boot/kernel.bin

.PHONY: all run clean