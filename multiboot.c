#include "multiboot.h"
#include "vga.h"

typedef struct
{
  uint32_t flags;
  uint32_t mem_lower;
  uint32_t mem_upper;
  uint32_t boot_device;
  char *cmd_line;
  uint32_t mods_count;
  uint32_t mods_addr;
  uint8_t syms[16];
  uint32_t mmap_length;
  uint32_t mmap_addr;
  uint32_t drives_length;
  uint32_t drives_addr;
  uint32_t config_table;
  char *boot_loader_name;
  // a few rest: apm_table, vbe, framebuffer
} multiboot_t;

extern multiboot_t *multiboot_info;

static void
_print_row_num(const char *header, uint32_t value)
{
  vga_print(header);
  vga_print(": ");
  vga_print_hexa(value);
  vga_print("\n");
};

static void
_print_row_str(const char *header, const char *value)
{
  vga_print(header);
  vga_print(": ");
  vga_print(value);
  vga_print("\n");
};

#define print_row_num(header) _print_row_num(#header, multiboot_info->header)
#define print_row_str(header) _print_row_str(#header, multiboot_info->header)

void dump_multiboot_info()
{
  if (multiboot_info->flags & 1 << 0)
    {
      print_row_num(mem_lower);
      print_row_num(mem_upper);
    }

  if (multiboot_info->flags & 1 << 1)
    print_row_num(boot_device);

  if (multiboot_info->flags & 1 << 2)
    print_row_str(cmd_line);

  if (multiboot_info->flags & 1 << 3)
    {
      print_row_num(mods_count);
      print_row_num(mods_addr);
    }

  // syms???

  if (multiboot_info->flags & 1 << 6)
    {
      print_row_num(mmap_length);
      print_row_num(mmap_addr);
    }

  if (multiboot_info->flags & 1 << 7)
    {
      print_row_num(drives_length);
      print_row_num(drives_addr);
    }

  if (multiboot_info->flags & 1 << 8)
    print_row_num(config_table);

  if (multiboot_info->flags & 1 << 9)
      print_row_str(boot_loader_name);
}
