project(ix)
cmake_minimum_required(VERSION 2.6)

if(CROSS)
  set(CMAKE_C_COMPILER "x86_64-elf-gcc")
  set(CMAKE_C_LINK_EXECUTABLE "x86_64-elf-ld <LINK_FLAGS> <OBJECTS> -o <TARGET>")
  set(OBJCOPY "x86_64-elf-objcopy")
else(NOT CROSS)
  set(OBJCOPY "objcopy")
endif(CROSS)

find_program(NASM NAMES nasm PATHS /usr/bin/)
set(CMAKE_ASM_COMPILER ${NASM})
enable_language(ASM)

set(CMAKE_C_FLAGS "-Wall -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -fno-stack-protector")
set(CMAKE_ASM_FLAGS "-f elf64")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -T ${PROJECT_SOURCE_DIR}/tools/link.ld")

include_directories(include)

add_executable(kernel.elf
    asm/init.s
    asm/interrupts.s
    asm/isr.s
    asm/irq.s
    asm/io.s
    kernel/interrupts.c
    kernel/kprint.c
	kernel/memory.c
    kernel/paging.c
    kernel/main.c
    drivers/keyboard.c
    drivers/video.c
)

add_custom_target(kernel.bin ALL ${OBJCOPY} -O binary ${CMAKE_BINARY_DIR}/kernel.elf ${CMAKE_BINARY_DIR}/kernel.bin
                  DEPENDS kernel.elf
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_target(iso ALL bash tools/iso.sh ${CMAKE_BINARY_DIR}/kernel.bin ${CMAKE_BINARY_DIR}/ix.iso
                  DEPENDS kernel.bin
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
