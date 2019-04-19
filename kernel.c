#include "vga.h"

void kernel_main(void)
{
  clear_screen();
  vga_print("Hello world\n");
}
