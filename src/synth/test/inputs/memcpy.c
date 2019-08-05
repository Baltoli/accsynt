#include <string.h>

void as_memcpy(char* dest, char* src, int n)
{
  memcpy((void*)dest, (void*)src, n);
}
