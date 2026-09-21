#!/bin/sh

cd src

rm ../blinkos.iso ../root/boot/kernel.bin boot.o kernel_c.o kernel.bin
i686-elf-as --32 boot.s -o boot.o
i686-elf-gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -c kernel.c -o kernel_c.o
i686-elf-gcc -m32 -T linker.ld -ffreestanding -nostdlib -o kernel.bin boot.o kernel_c.o -lgcc

cp kernel.bin ../root/boot
cd ..

grub-mkrescue -o blinkos.iso root
echo "Success!"