#include "authoritative_client.h"

Ref<AuthoritativeClient::LobbyCallResponse> AuthoritativeClient::lobby_call(const String &p_method, const Array &p_args) {
	String id = _increment_counter();
	Dictionary command;
	command["command"] = "lobby_call";
	Dictionary data_dict;
	data_dict["function"] = p_method;
	data_dict["inputs"] = p_args;
	command["data"] = data_dict;
	Array command_array;
	Ref<LobbyCallResponse> response;
	response.instantiate();
	command_array.push_back(LobbyClient::LOBBY_CALL);
	command_array.push_back(response);
	_commands[id] = command_array;
	_send_data(command);
	return response;
}

void AuthoritativeClient::_bind_methods() {
	ClassDB::bind_method(D_METHOD("lobby_call", "method", "args"), &AuthoritativeClient::lobby_call);
	ADD_PROPERTY_DEFAULT("peers", TypedArray<LobbyPeer>());
	ADD_PROPERTY_DEFAULT("peer", Ref<LobbyPeer>());
	ADD_PROPERTY_DEFAULT("lobby", Ref<LobbyInfo>());
}
