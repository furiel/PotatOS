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

static void
skip_rest_line()
{
  int column = (cursor % VGA_WIDTH);
  int missing_spaces = VGA_WIDTH - column;
  while (missing_spaces--)
    vga_write(" ", 1);
}

void
vga_write(const char *text, size_t len)
{
  char c;
  for (size_t i = 0; i < len; i++)
    {
      c = text[i];
      if (c == '\n')
        skip_rest_line();
      else
        {
          vga_buffer[cursor] = (uint16_t)c | (uint16_t)(VGA_COLOR_LIGHT_GREY << 8);
          cursor++;
        }
    }
}

static size_t
strlen(const char *text)
{
  int i = 0;
  while(text[i++]);
  return i-1;
}

void
vga_print(const char *text)
{
  vga_write(text, strlen(text));
}

void
vga_print_hexa(uint32_t num)
{
  const char *digits = "0123456789ABCDEFabcdefghijklm";

  char result[8];

  for (int i = 7; i >= 0; i--)
    {
      result[i] = digits[num & 0xF];
      num >>= 4;
    }
  vga_write(result, 8);
}
