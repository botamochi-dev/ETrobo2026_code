# ET ロボコン 2026 走行体プログラムリポジトリ

本リポジトリは、ETロボコン2026で実装するプログラムを、チームで効率よく開発・管理するためのものです。

## 📦 開発環境 (Requirements)

開発を開始する前に、必ず以下の環境を揃えてください。

| カテゴリ | 項目 | 推奨バージョン / 設定値 |
|---|---:|---|
| OS (Windows) | Windows バージョン | Windows 11 version 25H2 |
|  | OS ビルド | 26100.2605 (December 2024 Update) 以降 |
| 仮想環境 | WSL バージョン | WSL2 |
|  | Linux ディストリビューション | Ubuntu 24.04 LTS |
| 開発エディタ | 本体 | Visual Studio Code |
|  | 必須拡張機能 | WSL 拡張機能(ms-vscode-remote.remote-wsl) |
| プラットフォーム | 実行基盤 | SPIKE-RT (spike-rt) |


---

## 📖 開発・運用ルール (Documentation)

開発・運用に関する詳細なドキュメントは [`Docs/`](./Docs) フォルダを参照してください。

### 1. [🌿 Git / GitHub 運用フロー](Docs/GIT_WORKFLOW.md)
*   本リポジトリでは**GitHub Flow** (main + feature branch) を採用しています。
*   コミットメッセージのプレフィックス規則（`feat:`, `fix:` など）や、ブランチ戦略、PRの作成ルールについて記述しています。

### 2. [📝 コーディング & コメント規約](Docs/CODING_COMMENTS.md)
*   コーディングスタイル、命名規則について記述しています。

---

## 🚀 セットアップ手順 (Getting Started)

### 1. リポジトリのクローン
Git LFS がインストールされていることを確認し、リポジトリをクローンします。

```bash
# LFSの確認
git lfs install

# クローン
git clone [Repository URL]
```

### 2. Unity プロジェクトを開く
*   Unity Hub から対象のフォルダを開きます。
*   初回起動時はライブラリのインポートに時間がかかります。

### 3. Visual Studio の設定
1.  Unity エディタメニュー: `Edit > Preferences > External Tools` を開く。
2.  `External Script Editor` が **"Visual Studio 2022"** になっているか確認。
3.  `Generate .csproj files` のチェックボックス（Embedded packages等）を確認し、`Regenerate project files` をクリック。

### 4. 動作確認
1.  `Assets/_Project/Scenes/Main/` 以下のマスターシーンを開く。
2.  再生ボタンを押し、エラーが出ないことを確認する。