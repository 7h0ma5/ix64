#include <ix/pmm.h>
#include <string.h>

#define BITMAP_SIZE 1024

static unsigned int bitmap[BITMAP_SIZE];

int pmm_init() {
  memset(&bitmap[16], 0xff, (BITMAP_SIZE-16) * sizeof(unsigned));
  return 0;
}

void* pmm_alloc() {
  for (unsigned i = 0; i < BITMAP_SIZE; i++) {
    if (bitmap[i]) {
      for (unsigned j = 0; j < sizeof(bitmap[i])*8; j++) {
        if (bitmap[i] & (1 << j)) {
          bitmap[i] &= ~(1 << j);
          return (void*)((i*sizeof(bitmap[i]) * 8 + j) * 4096);
        }
      }
    }
  }
  return 0;
}
