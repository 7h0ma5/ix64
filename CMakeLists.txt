project(ix)
cmake_minimum_required(VERSION 2.6)

find_program(NASM NAMES nasm HINTS ${C_COMPILER_DIR} PATHS ${C_COMPILER_DIR})
if(NASM STREQUAL "NASM-NOTFOUND")
  message(FATAL_ERROR "nasm not found.")
endif(NASM STREQUAL "NASM-NOTFOUND")

if(CROSS)
  set(CMAKE_C_COMPILER "x86_64-elf-gcc")
  set(CMAKE_C_LINK_EXECUTABLE "x86_64-elf-ld <LINK_FLAGS> <OBJECTS> -o <TARGET>")
endif(CROSS)

set(CMAKE_ASM_COMPILER NASM)
enable_language(ASM)

set(CMAKE_C_FLAGS "-Wall -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -fno-stack-protector")
set(CMAKE_ASM_FLAGS "-f elf64")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -T ${PROJECT_SOURCE_DIR}/tools/link.ld")

include_directories(include)

add_executable(kernel.elf
    asm/init.s
    asm/interrupts.s
    kernel/interrupts.c
    kernel/kprint.c
    kernel/video.c
    kernel/main.c
)

add_custom_target(kernel.bin ALL x86_64-elf-objcopy -O binary ${CMAKE_BINARY_DIR}/kernel.elf ${CMAKE_BINARY_DIR}/kernel.bin
                  DEPENDS kernel.elf
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_target(iso ALL bash tools/iso.sh ${CMAKE_BINARY_DIR}/kernel.bin ${CMAKE_BINARY_DIR}/ix.iso
                  DEPENDS kernel.bin
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})