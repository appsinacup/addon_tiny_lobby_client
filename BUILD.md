# Build

In order to build, simply run:

```sh
scons
```

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

## Build module

To build module lib, do:

```sh
git clone https://github.com/godotengine/godot
git submodule add -- https://github.com/appsinacup/addon_tiny_lobby_client modules/tiny_lobby
scons
```
