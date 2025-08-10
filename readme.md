<p align="center">
	<img width="512px" src="tiny_lobby_banner.png"/> 
	<h1 align="center">Tiny Lobby Godot Client</h1> 
</p>

|[Website](https://appsinacup.com)|[Discord](https://discord.gg/56dMud8HYn)|[Build Locally](./BUILD.md)|[tiny_lobby Server](https://github.com/appsinacup/tiny_lobby)|[Starter Project](https://github.com/appsinacup/tiny_lobby_starter)
|-|-|-|-|-|

<p align="center">
		<img src="https://img.shields.io/badge/Godot-4.4.1-%23478cbf?logo=godot-engine&logoColor=white" />
</p>

-----

<p align = "center">
<b>Multiplayer lobbies</b> with real-time Lua-powered logic <i>for the Godot game engine.</i>
</p>

-----

Tiny Lobby is a lightweight multiplayer lobby system for WebSocket-based games, allowing peers to create, join, and manage lobbies, exchange data, and communicate in real time. It also supports backend scripting in Lua, enabling custom game logic directly on the server.

## Video Tutorial

[![Video Tutorial](https://img.youtube.com/vi/I9v_qkCa08Y/0.jpg)](https://www.youtube.com/watch?v=I9v_qkCa08Y)

## Features

- Write backend game logic in Lua that runs directly on the lobby server.
- Create, join, or leave a lobby.
- Get lobby public data, tags, and a list of lobbies.
- Receive the lobby state and notifications for peer join/leave/kick events.
- Call lobby scripted functions.
- Lock/unlock the lobby.
- Change max players, title, password, or tags.
- Set ready state and update user data.
- Send/receive chat messages.
- Get notifications for peer reconnect/disconnect, user data changes, and public/private data updates.

## Install from Godot Asset Library

Go to Godot `AssetLib` tab and download [Tiny Lobby Client](https://godotengine.org/asset-library/asset/4200).

## Install from GitHub Releases

In order to install, download from latest [GitHub Releases](https://github.com/appsinacup/addon_tiny_lobby_client/releases) the `GDExtension.zip` and place the `addons` folder inside your project.

## Module Build

In order to build module, add it to a godot repo:

```
git submodule add https://github.com/appsinacup/addon_tiny_lobby_client modules/tiny_lobby
cd modules/tiny_lobby
git submodule update --init --recursive
```
