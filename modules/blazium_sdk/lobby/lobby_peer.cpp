#include "lobby_peer.h"

void LobbyPeer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &LobbyPeer::get_id);
	ClassDB::bind_method(D_METHOD("get_peer_name"), &LobbyPeer::get_peer_name);
	ClassDB::bind_method(D_METHOD("is_ready"), &LobbyPeer::is_ready);
	ClassDB::bind_method(D_METHOD("get_data"), &LobbyPeer::get_data);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "id"), "", "get_id");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "peer_name"), "", "get_peer_name");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "ready"), "", "is_ready");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "data"), "", "get_data");
}

void LobbyPeer::set_id(const String &p_id) { id = p_id; }
void LobbyPeer::set_peer_name(const String &p_peer_name) { peer_name = p_peer_name; }
void LobbyPeer::set_ready(bool p_ready) { ready = p_ready; }
void LobbyPeer::set_data(const Dictionary &p_data) { data = p_data; }
void LobbyPeer::set_dict(const Dictionary &p_dict) {
	set_id(p_dict.get("id", ""));
	set_peer_name(p_dict.get("name", ""));
	set_ready(p_dict.get("ready", ""));
	set_data(p_dict.get("public_data", Dictionary()));
}
Dictionary LobbyPeer::get_dict() const {
	Dictionary dict;
	dict["id"] = get_id();
	dict["name"] = get_peer_name();
	dict["ready"] = is_ready();
	dict["public_data"] = get_data();
	return dict;
}

Dictionary LobbyPeer::get_data() const { return data; }
String LobbyPeer::get_id() const { return id; }
String LobbyPeer::get_peer_name() const { return peer_name; }
bool LobbyPeer::is_ready() const { return ready; }
