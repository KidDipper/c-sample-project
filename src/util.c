#include "util.h"
#include <string.h>

int add_int(int a, int b) { return a + b; }
int sub_int(int a, int b) { return a - b; }

int clamp_int(int v, int lo, int hi) {
  if (lo > hi) { int t = lo; lo = hi; hi = t; }
  if (v < lo) return lo;
  if (v > hi) return hi;
  return v;
}

bool str_empty(const char* s) {
  return (s == NULL) || (*s == '\0');
}

size_t str_copy(char* dst, size_t dst_size, const char* src) {
  if (!dst || dst_size == 0) return 0;
  if (!src) { dst[0] = '\0'; return 0; }
  size_t n = strlen(src);
  size_t c = (n < (dst_size - 1)) ? n : (dst_size - 1);
  memcpy(dst, src, c);
  dst[c] = '\0';
  return c;
}
