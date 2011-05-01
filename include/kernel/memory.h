#ifndef IX_MEMORY_H
#define IX_MEMORY_H

int memory_init();

unsigned long kmalloc(unsigned int);
void kfree(unsigned long);

#endif
