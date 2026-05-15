# コーディング & コメント規約

## `clang-format` のスタイル

本リポジトリはルートの ` .clang-format ` に基づく自動整形を採用しています。主な設定は以下のとおりです。

- `BasedOnStyle`: LLVM
- `IndentWidth`: 4
- `UseTab`: Never
- `BreakBeforeBraces`: Attach
- `AllowShortIfStatementsOnASingleLine`: false
- `IndentCaseLabels`: true
- `ColumnLimit`: 0
- `AccessModifierOffset`: -4

ソースコードは保存時に自動で整形されます。

## 推奨拡張機能

開発に便利な VS Code 拡張機能（推奨）を以下に示します。

| 拡張機能 (ID) | 用途 |
|---|---|
| `ms-vscode.cpptools` | C/C++ の IntelliSense とデバッグサポート |
| `twxs.cmake` | CMake ファイルの構文ハイライト |
| `ms-vscode.cmake-tools` | CMake ビルド/構成の統合サポート |
| `xaver.clang-format` | `clang-format` を利用した整形サポート |

# コーディング

TODO