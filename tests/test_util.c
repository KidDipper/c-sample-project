#include "../src/util.h"
#include "test_framework.h"
#include <string.h>

int main(void) {
  EXPECT_EQ_INT(5, add_int(2,3));
  EXPECT_EQ_INT(-1, sub_int(2,3));

  EXPECT_EQ_INT(10, clamp_int(5,10,20));
  EXPECT_EQ_INT(20, clamp_int(25,10,20));
  EXPECT_EQ_INT(15, clamp_int(15,20,10)); // lo>hi 入れ替え対応

  EXPECT_TRUE(str_empty(""));
  EXPECT_TRUE(str_empty(NULL));
  EXPECT_TRUE(!str_empty("a"));

  char buf[4];
  size_t w = str_copy(buf, sizeof(buf), "hello");
  EXPECT_EQ_INT(3, (int)w);
  EXPECT_TRUE(strcmp(buf, "hel") == 0);

  RUN_TESTS();
}
