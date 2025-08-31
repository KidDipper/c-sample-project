# C Sample (C + Azure DevOps)

最小構成の C ライブラリ＋ユニットテスト。  
Azure DevOps で **ビルド / テスト / フォーマット差分 / 静的解析** を実行。

---

## 🛠 環境構築手順（Windows + MSYS2）

1. **MSYS2 をインストール**  
   - [公式サイト](https://www.msys2.org/) からダウンロード & インストール  
   - **MSYS2 MinGW64** ターミナルを開いて更新  
     ```bash
     pacman -Syu
     ```
   - ターミナルを閉じて再度 **MinGW64** を開く

2. **必要ツールの導入**  
   ```bash
   pacman -S --needed mingw-w64-x86_64-gcc make mingw-w64-x86_64-clang-tools-extra

※もし `clang-tools-extra` が見つからなければ：

```bash
pacman -S mingw-w64-x86_64-clang-format mingw-w64-x86_64-clang-tidy
```

3. **VS Code 設定**

   * `.vscode/settings.json` に以下を追加

     ```json
     "terminal.integrated.profiles.windows": {
       "MSYS2 MinGW64": { "path": "C:\\\\msys64\\\\mingw64.exe", "args": [] }
     },
     "terminal.integrated.defaultProfile.windows": "MSYS2 MinGW64",
     "C_Cpp.default.compilerPath": "C:\\\\msys64\\\\mingw64\\\\bin\\\\gcc.exe"
     ```
   * 推奨拡張: `ms-vscode.cpptools`, `xaver.clang-format`

4. **動作確認**
   VS Code のターミナル（MSYS2 MinGW64）で：

   ```bash
   gcc --version
   clang-format --version
   make --version
   ```

---

## 🚀 ローカルでの使い方

```bash
make clean
make -j
make test          # => TESTS: PASS が出ればOK
make format-check
make tidy
```

---

## 🔄 CI (Azure DevOps)

* ルートに `azure-pipelines.yml` を配置
* `main` / `develop` への push / PR で自動実行
* 実行内容：Build / Test / Format Check / Tidy / Artifacts publish

---

## 📂 プロジェクト構成と役割

```
c-min-sample/
├─ src/
│  ├─ util.h        # 関数宣言（ヘッダ）
│  ├─ util.c        # 実装（足し算/引き算/クランプ/文字列処理）
│  └─ main.c        # ダミーmain (リンク確認用)
├─ tests/
│  ├─ test_framework.h # 簡易テストマクロ
│  └─ test_util.c      # ユニットテスト
├─ .vscode/         # VS Code 設定
│  ├─ settings.json
│  ├─ extensions.json
│  └─ tasks.json
├─ .clang-format    # コードフォーマットルール
├─ .clang-tidy      # 静的解析ルール
├─ .editorconfig    # 改行・インデントルール
├─ Makefile         # ビルド/テスト/チェック定義
├─ azure-pipelines.yml # CI 設定
└─ README.md
```

---

## 🔍 各ファイルの詳細

### `src/`

* **`util.h`** : 関数宣言

  * `add_int`, `sub_int` → 算術
  * `clamp_int` → 範囲制限 (`lo>hi` も対応)
  * `str_empty` → NULL/空文字判定
  * `str_copy` → 安全コピー（NUL終端保証）
* **`util.c`** : 実装
* **`main.c`** : `add_int(2,3)` を呼ぶだけ → ライブラリがリンクできるか確認

### `tests/`

* **`test_framework.h`** : 簡易テストマクロ

  * `EXPECT_TRUE`, `EXPECT_EQ_INT`, `RUN_TESTS()`
* **`test_util.c`** : ユニットテスト本体

  * 算術/クランプ/文字列/コピーのテスト
  * 最後に `RUN_TESTS();` で結果表示（`TESTS: PASS`）

### `Makefile`

* `make` → ビルド（`libutil.a` + `app`）
* `make test` → テスト実行
* `make clean` → 生成物削除
* `make format-check` → `clang-format -n --Werror`
* `make tidy` → `clang-tidy`

### `.vscode/`

* **settings.json** : MinGW64 を使うように設定済み
* **tasks.json** : Ctrl+Shift+B で `make` 実行可
* **extensions.json** : 推奨拡張

### `.clang-format`

* Google ベース、幅100、ポインタ左寄せ

### `.clang-tidy`

* bugprone, readability, analyzer 系チェック有効
* 警告はすべてエラー扱い

### `.editorconfig`

* 改行 LF、末尾改行あり、インデント2スペース

### `azure-pipelines.yml`

* Ubuntu ホストで build/test/format/tidy
* 成果物 `libutil.a` を公開

---

## ✅ 動作ログの意味（例）

```
gcc -c -o src/util.o src/util.c     # コンパイル
ar rcs libutil.a src/util.o         # 静的ライブラリ作成
gcc -o tests/test_util ... -lutil   # テストリンク
RUN tests/test_util                  # テスト実行
TESTS: PASS                          # 成功
```

---

## 🌱 拡張のアイデア

* PR 時だけ clang-tidy を厳格化
* gcov/llvm-cov によるカバレッジ収集
* pre-commit で clang-format を強制


