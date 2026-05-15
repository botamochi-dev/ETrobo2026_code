# Git / GitHub 運用フロー

このドキュメントでは、本プロジェクトにおけるGit/GitHubの運用フローとルールについて説明します。

## 目次

- [ブランチ戦略](#ブランチ戦略)
- [コミットフロー](#コミットフロー)
- [よくある質問](#よくある質問)

## ブランチ戦略

### メインブランチ

- **`main`** - 本番環境にデプロイされるブランチ
  - 常にデプロイ可能な状態を保つ
  - 直接プッシュは禁止
  - プルリクエスト経由でマージ

### 作業ブランチ

作業用のブランチは以下の命名規則に従って作成します：

```
<type>/<description>
```

**Type の種類:**

(一般的なものをとりあえず並べただけなので開発を進めていくうちに追加や削除を行いましょう)
- `feat/` - 新機能の追加
- `fix/` - バグ修正
- `docs/` - ドキュメントの変更
- `style/` - コードスタイルの変更（フォーマット、セミコロンなど）
- `refactor/` - リファクタリング
- `test/` - テストの追加・修正
- `chore/` - ビルドプロセスやツールの変更

**例:**

```bash
feat/add-blog-search
fix/header-responsive-issue
docs/update-readme
```

## コミットフロー

### コミットメッセージ規約

本プロジェクトでは **Conventional Commits** に従います。

**フォーマット:**

```
<type>: <body>
```

**Type:**

- `feat`: 新機能
- `fix`: バグ修正
- `docs`: ドキュメントのみの変更
- `style`: コードの意味に影響を与えない変更（空白、フォーマットなど）
- `refactor`: バグ修正でも機能追加でもないコード変更
- `test`: テストの追加や修正
- `chore`: ビルドプロセスやツールの変更

**例:**

```bash
git commit -m "feat: ブログ検索機能を追加"
git commit -m "fix: レスポンシブ表示の不具合を修正"
git commit -m "docs: READMEに環境構築手順を追加"
```


### マージ

- **マージ方法**: Squash and merge を推奨
- **マージ後**: ローカルのmainブランチを更新

```bash
git checkout main
git pull origin main
git branch -d feat/your-feature-name
```

## よくある質問

### Q: コミットメッセージを間違えた場合は？

```bash
# 直前のコミットメッセージを修正
git commit --amend -m "正しいメッセージ"

# すでにプッシュ済みの場合（注意: 強制プッシュ）
git push --force-with-lease origin your-branch-name
```

### Q: コミットを取り消したい場合は？

```bash
# 直前のコミットを取り消し（変更は残る）
git reset --soft HEAD~1

# 直前のコミットを完全に取り消し（変更も削除）
git reset --hard HEAD~1
```

## 参考資料

- [Conventional Commits](https://www.conventionalcommits.org/ja/)
- [GitHub Flow](https://docs.github.com/ja/get-started/quickstart/github-flow)
- [Semantic Versioning](https://semver.org/lang/ja/)