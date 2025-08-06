def can_build(env, platform):
	# TODO re-enable this when godot-cpp 4.5 is released
	if platform == "android" and eng.get("target") == "editor":
		return False
	return True


def configure(env):
	return True


def get_doc_classes():
	return [
		"LeaderboardsClient",
		"LeaderboardResponse",
		"LeaderboardResult",
		"LeaderboardData",
		"LobbyClient",
		"NetworkClient",
		"LobbyInfo",
		"LobbyPeer",
		"LobbyResponse",
		"LobbyResult",
		"ViewLobbyResponse",
		"ViewLobbyResult",
		"ScriptedLobbyClient",
		"ScriptedLobbyResponse",
		"ScriptedLobbyResult",
		"LoginClient",
		"LoginURLResponse",
		"LoginURLResult",
		"LoginConnectResponse",
		"LoginConnectResult",
		"LoginVerifyTokenResponse",
		"LoginVerifyTokenResult",
		"LoginIDResponse",
		"LoginIDResult",
		"LoginAuthResponse",
		"LoginAuthResult",
		"ThirdPartyClient",
		"DiscordEmbeddedAppClient",
		"DiscordEmbeddedAppResponse",
		"DiscordEmbeddedAppResult",
	]


def get_doc_path():
	return "doc_classes"
