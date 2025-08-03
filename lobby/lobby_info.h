/**************************************************************************/
/*  lobby_info.h                                                          */
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

#ifndef LOBBY_INFO_H
#define LOBBY_INFO_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

const int COMMAND_ERROR = 0;
const int COMMAND_LOBBY_HOSTED = 1;
const int COMMAND_LOBBY_CREATED = 2;
const int COMMAND_LOBBY_UNSEALED = 3;
const int COMMAND_LOBBY_SEALED = 4;
const int COMMAND_LOBBY_RESIZED = 5;
const int COMMAND_LOBBY_PASSWORDED = 6;
const int COMMAND_LOBBY_TITLED = 7;
const int COMMAND_PEER_READY = 8;
const int COMMAND_PEER_UNREADY = 9;
const int COMMAND_LOBBY_LEFT = 10;
const int COMMAND_PEER_LEFT = 11;
const int COMMAND_LOBBY_KICKED = 12;
const int COMMAND_PEER_STATE = 13;
const int COMMAND_LOBBY_CALL = 14;
const int COMMAND_PEER_USER_DATA = 15;
const int COMMAND_LOBBY_TAGS = 16;
const int COMMAND_PEER_CHAT = 17;
const int COMMAND_PEER_RECONNECTED = 18;
const int COMMAND_JOINED_LOBBY = 19;
const int COMMAND_PEER_JOINED = 20;
const int COMMAND_PEER_DISCONNECTED = 21;
const int COMMAND_LOBBY_LIST = 22;
const int COMMAND_LOBBY_DATA = 23;
const int COMMAND_PEER_NOTIFY = 24;
const int COMMAND_DATA_TO = 25;
const int COMMAND_DATA_TO_SENT = 26;
const int COMMAND_NOTIFY_TO_SENT = 27;

godot::String command_to_message(int command) {
  switch (command) {
  case COMMAND_ERROR:
    return "error";
  case COMMAND_LOBBY_HOSTED:
    return "lobby_hosted";
  case COMMAND_LOBBY_CREATED:
    return "lobby_created";
  case COMMAND_LOBBY_UNSEALED:
    return "lobby_unsealed";
  case COMMAND_LOBBY_SEALED:
    return "lobby_sealed";
  case COMMAND_LOBBY_RESIZED:
    return "lobby_resized";
  case COMMAND_LOBBY_PASSWORDED:
    return "lobby_passworded";
  case COMMAND_LOBBY_TITLED:
    return "lobby_titled";
  case COMMAND_PEER_READY:
    return "peer_ready";
  case COMMAND_PEER_UNREADY:
    return "peer_unready";
  case COMMAND_LOBBY_LEFT:
    return "lobby_left";
  case COMMAND_PEER_LEFT:
    return "peer_left";
  case COMMAND_LOBBY_KICKED:
    return "lobby_kicked";
  case COMMAND_PEER_STATE:
    return "peer_state";
  case COMMAND_LOBBY_CALL:
    return "lobby_call";
  case COMMAND_PEER_USER_DATA:
    return "peer_user_data";
  case COMMAND_LOBBY_TAGS:
    return "lobby_tags";
  case COMMAND_PEER_CHAT:
    return "peer_chat";
  case COMMAND_PEER_RECONNECTED:
    return "peer_reconnected";
  case COMMAND_JOINED_LOBBY:
    return "joined_lobby";
  case COMMAND_PEER_JOINED:
    return "peer_joined";
  case COMMAND_PEER_DISCONNECTED:
    return "peer_disconnected";
  case COMMAND_LOBBY_LIST:
    return "lobby_list";
  case COMMAND_LOBBY_DATA:
    return "lobby_data";
  case COMMAND_PEER_NOTIFY:
    return "peer_notify";
  case COMMAND_DATA_TO:
    return "data_to";
  case COMMAND_DATA_TO_SENT:
    return "data_to_sent";
  case COMMAND_NOTIFY_TO_SENT:
    return "notify_to_sent";
  }
  return "";
}

class LobbyInfo : public Resource {
  GDCLASS(LobbyInfo, Resource);
  String id = "";
  String lobby_name = "";
  String host = "";
  Dictionary tags = Dictionary();
  Dictionary data = Dictionary();
  int max_players = 0;
  int players = 0;
  bool sealed = false;
  bool password_protected = false;

protected:
  static void _bind_methods();

public:
  void set_id(const String &p_id);
  void set_lobby_name(const String &p_lobby_name);
  void set_host(const String &p_host);
  void set_max_players(int p_max_players);
  void set_players(int p_players);
  void set_sealed(bool p_sealed);
  void set_password_protected(bool p_password_protected);
  void set_tags(const Dictionary &p_tags);
  void set_delta_tags(const Dictionary &p_delta_tags);
  void set_data(const Dictionary &p_data);
  void set_delta_data(const Dictionary &p_delta_data);

  void set_dict(const Dictionary &p_dict, bool p_delta_update);
  Dictionary get_dict() const;

  Dictionary get_data() const;
  Dictionary get_tags() const;
  String get_id() const;
  String get_lobby_name() const;
  String get_host() const;
  int get_max_players() const;
  int get_players() const;
  bool is_sealed() const;
  bool is_password_protected() const;
};

#endif // LOBBY_INFO_H
