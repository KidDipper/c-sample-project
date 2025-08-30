#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H
#include <stdio.h>
static int g_failures = 0;

#define EXPECT_TRUE(cond) do { \
  if (!(cond)) { \
    fprintf(stderr, "[FAIL] %s:%d: %s\n", __FILE__, __LINE__, #cond); \
    g_failures++; \
  } \
} while (0)

#define EXPECT_EQ_INT(a,b) do { \
  if ((a)!=(b)) { \
    fprintf(stderr, "[FAIL] %s:%d: %s != %s (%d vs %d)\n", \
      __FILE__, __LINE__, #a, #b, (int)(a), (int)(b)); \
    g_failures++; \
  } \
} while (0)

#define RUN_TESTS() do { \
  if (g_failures) { fprintf(stderr, "TESTS: FAIL=%d\n", g_failures); return 1; } \
  printf("TESTS: PASS\n"); return 0; \
} while (0)
#endif
