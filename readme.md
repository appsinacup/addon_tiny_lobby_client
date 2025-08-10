<p align="center">
	<img width="256px" src="tiny_lobby_banner.png"/> 
	<h1 align="center">Tiny Lobby Godot Client</h1> 
</p>

|[Website](https://appsinacup.com)|[Discord](https://discord.gg/56dMud8HYn)|[Build](./BUILD.md)|[Startup Project](https://github.com/appsinacup/tiny_lobby_starter)
|-|-|-|-|

<p align="center">
		<img src="https://img.shields.io/badge/Godot-4.4.1-%23478cbf?logo=godot-engine&logoColor=white" />
</p>

Addon that adds nodes that can connect to [Tiny Lobby](https://github.com/appsinacup/tiny_lobby).

![example](https://github.com/appsinacup/tiny_lobby/blob/main/docs/example.gif?raw=true)

## Install

In order to install, download from latest [GitHub Releases](https://github.com/appsinacup/addon_tiny_lobby_client/releases) the `GDExtension.zip` and place the `addons` folder inside your project.

## Module Build

In order to build module, add it to a godot repo:

```
git submodule add https://github.com/appsinacup/addon_tiny_lobby_client modules/tiny_lobby
cd modules/tiny_lobby
git submodule update --init --recursive
```
