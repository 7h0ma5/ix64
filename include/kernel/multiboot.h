#ifndef IX_MULTIBOOT_H
#define IX_MULTIBOOT_H

typedef struct multiboot_info {
    unsigned int flags;

    unsigned int mem_lower;
    unsigned int mem_upper;

    unsigned int boot_device;

    unsigned int cmdline;

    unsigned int mods_count;
    unsigned int mods_addr;

    unsigned int tabsize;
    unsigned int strsize;
    unsigned int addr;
    unsigned int reserved;

    unsigned int mmap_length;
    unsigned int mmap_addr;

    unsigned int drives_length;
    unsigned int drives_addr;

    unsigned int config_table;

    unsigned int boot_loader_name;

    unsigned int apm_table;

    unsigned int vbe_control_info;
    unsigned int vbe_mode_info;
    unsigned short vbe_mode;
    unsigned short vbe_interface_seg;
    unsigned short vbe_interface_off;
    unsigned short vbe_interface_len;
} multiboot_info;

typedef struct multiboot_mmap_entry {
    unsigned int size;
    unsigned long addr;
    unsigned long len;
    unsigned short type;
} multiboot_mmap_entry;

#endif