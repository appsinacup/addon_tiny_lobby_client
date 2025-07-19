/**************************************************************************/
/*  register_types.cpp                                                    */
/**************************************************************************/
/*                         This file is part of:                          */
/*                            BLAZIUM ENGINE                              */
/*                        https://blazium.app                             */
/**************************************************************************/
/* Copyright (c) 2024-present Blazium Engine contributors.                */
/* Copyright (c) 2024 Dragos Daian, Randolph William Aarseth II.          */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "register_types.h"
#include "discord/discord_embedded_app_client.h"
#include "discord/discord_embedded_app_response.h"
#include "lobby/lobby_client.h"
#include "lobby/lobby_info.h"
#include "lobby/lobby_peer.h"
#include "lobby/lobby_response.h"
#include "lobby/scripted_lobby_client.h"
#include "lobby/scripted_lobby_response.h"
#include "login/login_client.h"
#include "network_client.h"
#include "third_party_client.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_importer.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

void initialize_tiny_lobby(ModuleInitializationLevel p_level) {
  if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
    // Network clients
    GDREGISTER_ABSTRACT_CLASS(NetworkClient);
    GDREGISTER_CLASS(LobbyInfo);
    GDREGISTER_CLASS(LobbyPeer);
    GDREGISTER_CLASS(LobbyClient);
    GDREGISTER_CLASS(LobbyResponse::LobbyResult);
    GDREGISTER_CLASS(LobbyResponse);
    GDREGISTER_CLASS(ViewLobbyResponse::ViewLobbyResult);
    GDREGISTER_CLASS(ViewLobbyResponse);
    GDREGISTER_CLASS(ScriptedLobbyClient);
    GDREGISTER_CLASS(ScriptedLobbyResponse);
    GDREGISTER_CLASS(ScriptedLobbyResponse::ScriptedLobbyResult);
    GDREGISTER_CLASS(LoginClient);
    GDREGISTER_CLASS(LoginClient::LoginConnectResponse);
    GDREGISTER_CLASS(LoginClient::LoginConnectResponse::LoginConnectResult);
    GDREGISTER_CLASS(LoginClient::LoginURLResponse);
    GDREGISTER_CLASS(LoginClient::LoginURLResponse::LoginURLResult);
    GDREGISTER_CLASS(LoginClient::LoginVerifyTokenResponse);
    GDREGISTER_CLASS(
        LoginClient::LoginVerifyTokenResponse::LoginVerifyTokenResult);
    GDREGISTER_CLASS(LoginClient::LoginIDResponse);
    GDREGISTER_CLASS(LoginClient::LoginIDResponse::LoginIDResult);
    GDREGISTER_CLASS(LoginClient::LoginAuthResponse);
    GDREGISTER_CLASS(LoginClient::LoginAuthResponse::LoginAuthResult);
    // Third party clients
    GDREGISTER_ABSTRACT_CLASS(ThirdPartyClient);
    GDREGISTER_CLASS(DiscordEmbeddedAppClient);
    GDREGISTER_CLASS(DiscordEmbeddedAppResponse);
    GDREGISTER_CLASS(DiscordEmbeddedAppResponse::DiscordEmbeddedAppResult);
  }
}

void uninitialize_tiny_lobby(ModuleInitializationLevel p_level) {
  // No-op for GDExtension
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT
tiny_lobby_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
                const GDExtensionClassLibraryPtr p_library,
                GDExtensionInitialization *r_initialization) {
  godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library,
                                                 r_initialization);

  init_obj.register_initializer(initialize_tiny_lobby);
  init_obj.register_terminator(uninitialize_tiny_lobby);
  init_obj.set_minimum_library_initialization_level(
      MODULE_INITIALIZATION_LEVEL_SCENE);

  return init_obj.init();
}
}
