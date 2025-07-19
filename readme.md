# Tiny Lobby Client Addon

|[Website](https://appsinacup.com)|[Discord](https://discord.gg/56dMud8HYn)|
|-|-|

Addon that adds nodes that can connect to [Tiny Lobby](https://github.com/appsinacup/tiny_lobby).

## Lint

This repository uses a [pre-commit](https://pre-commit.com/) hook to automatically lint and format code before each commit.

To set up the pre-commit hook, run:

```sh
pip install pre-commit
pre-commit install
```

This will ensure that `clang-format` is run on all staged C/C++ files before committing. You can also manually run the checks on all files with:

```sh
pre-commit run --all-files
```

