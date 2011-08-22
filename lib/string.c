#include <string.h>

void* memset(void* ptr, int value, size_t num) {
  unsigned int* dest = ptr;

  while (num--) {
    *(dest++) = value;
  }

  return ptr;
}
