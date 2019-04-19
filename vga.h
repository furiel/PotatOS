#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>

void clear_screen(void);
void vga_write(const char *, size_t len);
void vga_print(const char *);
void vga_print_hexa(uint32_t num);

#endif
