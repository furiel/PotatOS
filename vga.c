#include "vga.h"

#include <stddef.h>
#include <stdint.h>

const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 20;

uint16_t *vga_buffer = (uint16_t *)0xB8000;
int cursor = 0;

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

void
clear_screen(void)
{
  for (unsigned int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    vga_buffer[i] = (uint16_t)' ' | (uint16_t)(VGA_COLOR_BLACK << 8);
}

void
vga_write(const char *text)
{
  char c;
  for (char *p = text; *p; p++)
    {
      c = *p;
      vga_buffer[cursor] = (uint16_t)c | (uint16_t)(VGA_COLOR_LIGHT_GREY << 8);
      cursor++;
    }
}
