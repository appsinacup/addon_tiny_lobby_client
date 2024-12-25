#include "lobby_peer.h"

void LobbyPeer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &LobbyPeer::get_id);
	ClassDB::bind_method(D_METHOD("get_user_data"), &LobbyPeer::get_user_data);
	ClassDB::bind_method(D_METHOD("is_ready"), &LobbyPeer::is_ready);
	ClassDB::bind_method(D_METHOD("get_data"), &LobbyPeer::get_data);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "id"), "", "get_id");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "user_data"), "", "get_user_data");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "ready"), "", "is_ready");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "data"), "", "get_data");
}

void LobbyPeer::set_id(const String &p_id) { id = p_id; }
void LobbyPeer::set_user_data(const Dictionary &p_user_data) { user_data = p_user_data; }
void LobbyPeer::set_ready(bool p_ready) { ready = p_ready; }
void LobbyPeer::set_data(const Dictionary &p_data) { data = p_data; }
void LobbyPeer::set_dict(const Dictionary &p_dict) {
	set_id(p_dict.get("id", ""));
	set_user_data(p_dict.get("user_data", ""));
	set_ready(p_dict.get("ready", ""));
	set_data(p_dict.get("public_data", Dictionary()));
}
Dictionary LobbyPeer::get_dict() const {
	Dictionary dict;
	dict["id"] = get_id();
	dict["user_data"] = get_user_data();
	dict["ready"] = is_ready();
	dict["public_data"] = get_data();
	return dict;
}

Dictionary LobbyPeer::get_data() const { return data; }
String LobbyPeer::get_id() const { return id; }
Dictionary LobbyPeer::get_user_data() const { return user_data; }
bool LobbyPeer::is_ready() const { return ready; }
