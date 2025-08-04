#ifndef LEADERBOARDS_CLIENT_H
#define LEADERBOARDS_CLIENT_H

#include "../discord/discord_embedded_app_client.h"
#include "../network_client.h"
#include <godot_cpp/classes/http_request.hpp>
#include <godot_cpp/classes/json.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

class LeaderboardData : public RefCounted {
  GDCLASS(LeaderboardData, RefCounted);
  String user_id;
  int score = 0;
  String timestamp;

protected:
  static void _bind_methods() {
    ClassDB::bind_method(D_METHOD("get_user_id"),
                         &LeaderboardData::get_user_id);
    ClassDB::bind_method(D_METHOD("set_user_id", "user_id"),
                         &LeaderboardData::set_user_id);
    ClassDB::bind_method(D_METHOD("get_score"), &LeaderboardData::get_score);
    ClassDB::bind_method(D_METHOD("set_score", "score"),
                         &LeaderboardData::set_score);
    ClassDB::bind_method(D_METHOD("get_timestamp"),
                         &LeaderboardData::get_timestamp);
    ClassDB::bind_method(D_METHOD("set_timestamp", "timestamp"),
                         &LeaderboardData::set_timestamp);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "user_id"), "set_user_id",
                 "get_user_id");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "score"), "set_score", "get_score");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "timestamp"), "set_timestamp",
                 "get_timestamp");
  }

public:
  void set_user_id(String p_id) { user_id = p_id; }
  String get_user_id() const { return user_id; }
  void set_score(int p_score) { score = p_score; }
  int get_score() const { return score; }
  void set_timestamp(String p_ts) { timestamp = p_ts; }
  String get_timestamp() const { return timestamp; }
};

class LeaderboardResult : public RefCounted {
  GDCLASS(LeaderboardResult, RefCounted);

  String error = "";
  Array leaderboard_data;

protected:
  static void _bind_methods() {
    ClassDB::bind_method(D_METHOD("get_leaderboard_data"),
                         &LeaderboardResult::get_leaderboard_data);
    ClassDB::bind_method(D_METHOD("has_error"), &LeaderboardResult::has_error);
    ClassDB::bind_method(D_METHOD("get_error"), &LeaderboardResult::get_error);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "error"), "", "get_error");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "leaderboard_data",
                              PROPERTY_HINT_ARRAY_TYPE, "LeaderboardData"),
                 "", "get_leaderboard_data");
  }

public:
  void set_leaderboard_data(Array p_data) { leaderboard_data = p_data; }
  void set_error(String p_error) { this->error = p_error; }

  bool has_error() const { return !error.is_empty(); }
  String get_error() const { return error; }
  Array get_leaderboard_data() const { return leaderboard_data; }
};

class LeaderboardResponse : public RefCounted {
  GDCLASS(LeaderboardResponse, RefCounted);

protected:
  static void _bind_methods() {
    ADD_SIGNAL(MethodInfo("finished", PropertyInfo(Variant::OBJECT, "result",
                                                   PROPERTY_HINT_RESOURCE_TYPE,
                                                   "LeaderboardResult")));
  }

public:
  void signal_finish(String p_error, Array p_data = Array()) {
    Ref<LeaderboardResult> result;
    result.instantiate();
    result->set_error(p_error);
    result->set_leaderboard_data(p_data);
    this->emit_signal("finished", result);
  }
};

class LeaderboardsClient : public NetworkClient {
  GDCLASS(LeaderboardsClient, NetworkClient);

protected:
  String override_discord_path = "appsinacup/lobby";
  String server_url = "lobby.appsinacup.com";
  String http_prefix = "https://";
  String game_id = "";
  Ref<LeaderboardResponse> leaderboard_response;
  HTTPRequest *request = nullptr;

protected:
  static void _bind_methods() {
    ClassDB::bind_method(D_METHOD("set_game_id", "game_id"),
                         &LeaderboardsClient::set_game_id);
    ClassDB::bind_method(D_METHOD("get_game_id"),
                         &LeaderboardsClient::get_game_id);
    ClassDB::bind_method(D_METHOD("set_server_url", "server_url"),
                         &LeaderboardsClient::set_server_url);
    ClassDB::bind_method(D_METHOD("get_server_url"),
                         &LeaderboardsClient::get_server_url);
    ClassDB::bind_method(D_METHOD("set_http_prefix", "http_prefix"),
                         &LeaderboardsClient::set_http_prefix);
    ClassDB::bind_method(D_METHOD("get_http_prefix"),
                         &LeaderboardsClient::get_http_prefix);
    ClassDB::bind_method(D_METHOD("request_leaderboard", "leaderboard_id"),
                         &LeaderboardsClient::request_leaderboard);
    ADD_SIGNAL(MethodInfo("log_updated", PropertyInfo(Variant::STRING, "type"),
                          PropertyInfo(Variant::STRING, "message")));
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "game_id"), "set_game_id",
                 "get_game_id");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "server_url"), "set_server_url",
                 "get_server_url");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "http_prefix"),
                 "set_http_prefix", "get_http_prefix");
  }

public:
  void set_game_id(String p_game_id) { this->game_id = p_game_id; }
  String get_game_id() const { return game_id; }

  void set_server_url(String p_server_url) { this->server_url = p_server_url; }
  String get_server_url() const { return server_url; }

  void set_http_prefix(String p_http_prefix) {
    this->http_prefix = p_http_prefix;
  }
  String get_http_prefix() const { return http_prefix; }

  void set_override_discord_path(String p_path) {
    override_discord_path = p_path;
    if (DiscordEmbeddedAppClient::static_is_discord_environment()) {
      server_url = DiscordEmbeddedAppClient::static_find_client_id() +
                   ".discordsays.com/.proxy/" + override_discord_path;
    }
  }
  String get_override_discord_path() const { return override_discord_path; }

  Ref<LeaderboardResponse> request_leaderboard(String leaderboard_id) {
    if (game_id.is_empty()) {
      Ref<LeaderboardResponse> response;
      response.instantiate();
      Callable callable =
          callable_mp(*response, &LeaderboardResponse::signal_finish);
      callable.call_deferred("Game ID not set.", Array());
      emit_signal("log_updated", "error", "Game ID not set.");
      return response;
    }
    if (request) {
      request->queue_free();
      request = nullptr;
    }
    String url = http_prefix + server_url + "/game/" + game_id +
                 "/leaderboard/" + leaderboard_id;
    emit_signal("log_updated", "request_leaderboard",
                "Requesting leaderboard: " + leaderboard_id);
    request = memnew(HTTPRequest);
    add_child(request);
    request->connect(
        "request_completed",
        callable_mp(this, &LeaderboardsClient::_on_request_completed));
    request->request(url, PackedStringArray(), HTTPClient::METHOD_GET);
    return leaderboard_response;
  }

  void _on_request_completed(int p_status, int p_code,
                             const PackedStringArray &p_headers,
                             const PackedByteArray &p_data) {
    Ref<LeaderboardResult> result;
    result.instantiate();
    Array leaderboard_array;
    String result_str = String::utf8((const char *)p_data.ptr(), p_data.size());
    if (p_code != 200 || result_str == "") {
      result->set_error("Request failed with code: " + String::num(p_code) +
                        " " + result_str);
      emit_signal("log_updated", "error",
                  "Request failed with code: " + String::num(p_code) + " " +
                      result_str);
    } else {
      Variant parse_result = JSON::parse_string(result_str);
      Array raw_array = parse_result;
      for (int i = 0; i < raw_array.size(); ++i) {
        Dictionary entry = raw_array[i];
        Ref<LeaderboardData> data;
        data.instantiate();
        data->set_user_id(entry.get("user_id", ""));
        data->set_score(entry.get("score", 0));
        data->set_timestamp(entry.get("timestamp", ""));
        leaderboard_array.append(data);
      }
      result->set_leaderboard_data(leaderboard_array);
      emit_signal("log_updated", "request_leaderboard", "Success");
    }
    leaderboard_response->emit_signal("finished", result);
    if (request) {
      request->queue_free();
      request = nullptr;
    }
  }

  LeaderboardsClient() {
    if (DiscordEmbeddedAppClient::static_is_discord_environment()) {
      server_url = DiscordEmbeddedAppClient::static_find_client_id() +
                   ".discordsays.com/.proxy/" + override_discord_path;
    } else {
      server_url = "leaderboards.appsinacup.com";
    }
    leaderboard_response.instantiate();
  }

  ~LeaderboardsClient() {}
};

#endif // LEADERBOARDS_CLIENT_H
