int as_strlen(char* str)
{
  int len = 0;
  while (*str) {
    ++str;
    ++len;
  }
  return len;
}
