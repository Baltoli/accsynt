#include <string.h>

void as_memmove(char* dest, char* src, int n)
{
  memmove((void*)dest, (void*)src, n);
}
