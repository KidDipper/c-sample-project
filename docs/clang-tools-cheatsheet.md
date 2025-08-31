# clang-format / clang-tidy チートシート

C/C++ プロジェクトでよく使う整形ルール（clang-format）と  
静的解析・コーディング規約（clang-tidy）のまとめ。

---

## 🖊 clang-format（整形）

### よく使う `.clang-format` 設定例
```yaml
BasedOnStyle: Google     # LLVM, Google, Chromium, Mozilla, WebKit など
IndentWidth: 2           # インデント幅
TabWidth: 2
UseTab: Never            # Tab を使わずスペース
ColumnLimit: 100         # 1行の最大文字数（0で無制限）
PointerAlignment: Left   # int* p → int *p
BreakBeforeBraces: Allman   # { の位置: Attach/K&R/Allman/Stroustrup など
AllowShortIfStatementsOnASingleLine: false
SortIncludes: true       # #include 並び替え
IncludeBlocks: Regroup
SpaceBeforeParens: ControlStatements
````

### コマンド例

```bash
# 差分チェック（CI向け）
clang-format -n --Werror src/*.c

# 実ファイルを書き換え（開発用）
clang-format -i src/util.c tests/test_util.c

# ディレクトリ再帰
find src tests -name "*.[ch]" -print0 | xargs -0 clang-format -i
```

### VS Code 設定例

```json
"editor.formatOnSave": true,
"clang-format.style": "file",
"clang-format.executable": "C:\\msys64\\mingw64\\bin\\clang-format.exe"
```

---

## 🔍 clang-tidy（静的解析・コーディング規約）

### よく使う `.clang-tidy` 設定例

```yaml
Checks: >
  clang-analyzer-*,
  bugprone-*,
  readability-*,
  portability-*,
  performance-*,
  readability-identifier-naming

WarningsAsErrors: '*'
HeaderFilterRegex: 'src/.*'
FormatStyle: none

CheckOptions:
  - key: readability-identifier-naming.FunctionCase
    value: lower_case
  - key: readability-identifier-naming.VariableCase
    value: lower_case
  - key: readability-identifier-naming.ConstantCase
    value: UPPER_CASE
  - key: readability-identifier-naming.MacroDefinitionCase
    value: UPPER_CASE
  - key: readability-identifier-naming.EnumConstantCase
    value: UPPER_CASE
```

### コマンド例

```bash
# 単一ファイル解析
clang-tidy src/util.c -- -std=c11

# 複数ファイル
clang-tidy src/util.c src/static-check.c -- -std=c11

# 一時的にチェック上書き
clang-tidy src/util.c -checks=bugprone-*,readability-* -- -std=c11

# 特定行だけチェック
clang-tidy src/util.c -line-filter='[{"name":"src/util.c","lines":[[10,80]]}]' -- -std=c11

# ヘッダ解析を抑制
clang-tidy src/util.c --header-filter='' -- -std=c11
```

### Makefile の柔軟ターゲット例

```make
# 任意ファイルだけ tidy
FILES ?= src/*.c

tidy:
	@clang-tidy $(FILES) -- -std=c11

format-check:
	@clang-format -n --Werror $(FILES)
```

### NOLINT で例外指定

```c
int x = 42; // NOLINT(readability-magic-numbers)

int f() {
  // NOLINTNEXTLINE(bugprone-branch-clone)
  if (x == 42) { /* ... */ }
}
```

---

## ✅ ベストプラクティス

* **format は自動、tidy は PR 時に厳格**

  * ローカル：保存時に `clang-format` 自動整形
  * CI/PR：`clang-format -n --Werror` & `clang-tidy` 実行

* **まずは解析系チェックから**

  * `clang-analyzer-*`, `bugprone-*` を優先
  * 誤検知が少なく導入しやすい

* **命名規則は段階的に導入**

  * 既存コードに一気に適用すると大量警告
  * 新規コードや PR だけに適用して少しずつ浸透

* **差分のみチェック（上級）**

  ```bash
  git diff --name-only origin/main... | grep -E '\.(c|h)$' | xargs clang-format -n --Werror
  ```

