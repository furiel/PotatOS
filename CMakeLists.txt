cmake_minimum_required(VERSION 3.5)
set(CMAKE_C_COMPILER_WORKS 1)

project(PotatOS C ASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Werror")

set (SOURCES
  linker.ld
  boot.s
  kernel.c
  vga.c)

add_executable(potatos.bin ${SOURCES})
set_target_properties(potatos.bin
  PROPERTIES LINK_FLAGS "-T ${CMAKE_SOURCE_DIR}/linker.ld -nostdlib -lgcc")
