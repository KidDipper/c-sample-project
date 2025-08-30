#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int add_int(int a, int b);
int sub_int(int a, int b);
int clamp_int(int v, int lo, int hi);

// 文字列が NULL/長さ0 なら true
bool str_empty(const char* s);

// 安全なコピー：dst_size が 0 の場合は何もしない（戻り値はコピー後の長さ）
size_t str_copy(char* dst, size_t dst_size, const char* src);

#ifdef __cplusplus
}
#endif
#endif
