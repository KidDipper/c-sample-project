// わざと問題のあるコード例（clang-tidy / clang-analyzer に怒らせる用）
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1) if 条件式の中で代入をしてしまう（== のつもりが = になっている）
int bad_compare(int x) {
  if (x = 0) {  // bugprone-assignment-in-if を想定
    return 1;
  }
  return 0;
}

// 2) NULL 参照の可能性（cond が 10 以下なら p は NULL のまま）
int null_deref_example(int cond) {
  char *p = NULL;
  if (cond > 10) {
    p = "ok";
  }
  return p[0];  // clang-analyzer-core.NullDereference を想定
}

// 3) ヒープ確保して解放しない（リーク）＋ strcpy の不安全 API 使用
void leak_and_unsafe_copy(void) {
  char *m = (char *)malloc(16);
  if (!m)
    return;
  strcpy(m, "this string is definitely longer than 16 bytes");  // insecure API 使用
  // free(m);  // 敢えて解放しない → clang-analyzer-unix.Malloc / insecureAPI.strcpy を想定
}

// 4) ローカル変数のアドレスを返す（スコープ外参照の危険）
int *return_address_of_local(void) {
  int local = 42;
  return &local;  // clang-analyzer-core.StackAddressEscape を想定
}

// 5) 変数のシャドーイング＋未使用変数
void shadow_and_unused(int value) {
  int value_shadow = 42;  // 引数名に似た名前で紛らわしい（※Cだと shadowing 検出は限定的）
  int unused_local;       // 未使用（unused-parameter/unused-variable）
  if (value_shadow) {
    printf("val=%d\n", value_shadow);
  }
}
