# clang-tidy（静的解析）：指定したファイルだけ
```
clang-tidy src/static-check.c -- -std=c11
```
複数なら空白区切りで：
```
clang-tidy src/foo.c src/bar.c -- -std=c11
```
さらに 一時的にチェック内容を上書きしたい場合：
```
clang-tidy src/static-check.c -checks=bugprone-*,readability-* -- -std=c11

```
ヘッダ解析を抑えたい場合（そのファイル“だけ”を厳密に）：
```
clang-tidy src/static-check.c --header-filter='' -- -std=c11
```
clang-tidyの結果をファイルに保存する方法：標準出力とエラー出力（2>&1）をまとめて tidy_result.txt に保存
```
make tidy > tidy_result.txt 2>&1
```


# clang-format（整形）：指定したファイルだけ
```
clang-format -n --Werror src/util.c         # 差分チェックのみ
clang-format -i src/util.c                  # その場で書き換え
```