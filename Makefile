CC      = i686-elf-gcc
AS      = i686-elf-as
NASM    = nasm

CFLAGS  = -m32 -ffreestanding -fno-pie -fno-stack-protector
LDFLAGS = -m32 -T src/linker.ld -ffreestanding -nostdlib
NASMFLAGS = -f elf32

ISO     = blinkos.iso
ROOT    = root

# C, GAS (.s) ve NASM (.asm) kaynak dosyalarını otomatik bul
C_SRCS    := $(shell find src -name '*.c')
GAS_SRCS  := $(shell find src -name '*.s')
NASM_SRCS := $(shell find src -name '*.asm')

# Obje dosyaları dönüştürme
C_OBJS    := $(C_SRCS:.c=.o)
GAS_OBJS  := $(GAS_SRCS:.s=.o)
NASM_OBJS := $(NASM_SRCS:.asm=.o)

# Hepsini tek bir OBJS listesinde birleştir
OBJS := $(C_OBJS) $(GAS_OBJS) $(NASM_OBJS)

all: $(ISO)

$(ISO): kernel.bin
	mkdir -p $(ROOT)/boot
	cp kernel.bin $(ROOT)/boot/kernel.bin
	grub-mkrescue -o $(ISO) $(ROOT)
	@echo "Success!"

kernel.bin: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lgcc

# C dosyalarını derleme kuralı
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# GAS (.s) assembly dosyalarını derleme kuralı
%.o: %.s
	$(AS) --32 $< -o $@

# NASM (.asm) assembly dosyalarını derleme kuralı
%.o: %.asm
	$(NASM) $(NASMFLAGS) $< -o $@

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO) -display sdl

clean:
	find src \( -name '*.o' \) -delete
	rm -f kernel.bin $(ISO) $(ROOT)/boot/kernel.bin

.PHONY: all run clean

