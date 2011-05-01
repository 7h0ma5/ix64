#ifndef IX_PAGING_H
#define IX_PAGING_H

int paging_init();

typedef struct {
  unsigned int exists : 1;
  unsigned int writable : 1;
  unsigned int user : 1;
  unsigned int write_through : 1;
  unsigned int no_cache : 1;
  unsigned int accessed : 1;
  unsigned int zero : 3;
  unsigned int custom1 : 3;
  unsigned long pdpt_addr : 40;
  unsigned int custom2: 11;
  unsigned int executable : 1;
} pml4;

typedef struct {
  unsigned int exists : 1;
  unsigned int writable : 1;
  unsigned int user : 1;
  unsigned int write_through : 1;
  unsigned int no_cache : 1;
  unsigned int accessed : 1;
  unsigned int zero : 1;
  unsigned int size : 1;
  unsigned int global : 1;
  unsigned int custom1 : 3;
  unsigned long pdt_addr : 40;
  unsigned int custom2: 11;
  unsigned int executable : 1;
} pdp;

typedef struct {
  unsigned int exists : 1;
  unsigned int writable : 1;
  unsigned int user : 1;
  unsigned int write_through : 1;
  unsigned int no_cache : 1;
  unsigned int accessed : 1;
  unsigned int zero : 1;
  unsigned int size : 1;
  unsigned int global : 1;
  unsigned int custom1 : 3;
  unsigned long pt_addr : 40;
  unsigned int custom2: 11;
  unsigned int executable : 1;
} pd_entry;

typedef struct {
  unsigned int exists : 1;
  unsigned int writable : 1;
  unsigned int user : 1;
  unsigned int write_through : 1;
  unsigned int no_cache : 1;
  unsigned int accessed : 1;
  unsigned int zero : 2;
  unsigned int global : 1;
  unsigned int custom1 : 3;
  unsigned long mem_addr : 40;
  unsigned int custom2: 11;
  unsigned int executable : 1;
} pt_entry;


#endif
