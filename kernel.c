#include "vga.h"
#include "multiboot.h"

void kernel_main(void)
{
  clear_screen();
  vga_print("Hello world\n");
  dump_multiboot_info();
}
