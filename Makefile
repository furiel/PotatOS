TARGET=i686-elf

AS=$(TARGET)-as
CC=$(TARGET)-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

all: boot.o kernel.o vga.o potatos.bin

vga.o: vga.h
kernel.o: vga.h

%.o: %.s
	$(AS) $< -o $@

potatos.bin: linker.ld vga.o kernel.o boot.o
	$(CC) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib vga.o kernel.o boot.o -lgcc

clean:
	rm -f *.o *.bin

.PHONY: clean
