/**************************************************************************/
/*  youtube_playables_response.h                                          */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             BLAZIUM ENGINE                             */
/*                          https://blazium.app                           */
/**************************************************************************/
/* Copyright (c) 2024-present Blazium Engine contributors.                */
/* Copyright (c) 2025 Nicholas Santos Shiden.                             */
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

#ifndef YOUTUBE_PLAYABLES_RESPONSE_H
#define YOUTUBE_PLAYABLES_RESPONSE_H

#include "core/object/ref_counted.h"
#include "core/io/json.h"
#include "platform/web/api/javascript_bridge_singleton.h"

class YoutubePlayablesResponse : public RefCounted {
	GDCLASS(YoutubePlayablesResponse, RefCounted);

	String error;
	String data;
	Ref<JavaScriptObject> signal_response_callback;
protected:
	static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("_signal_response"), &YoutubePlayablesResponse::_signal_response);

		ClassDB::bind_method(D_METHOD("get_data"), &YoutubePlayablesResponse::get_data);
		ClassDB::bind_method(D_METHOD("has_error"), &YoutubePlayablesResponse::has_error);
		ClassDB::bind_method(D_METHOD("get_error"), &YoutubePlayablesResponse::get_error);

		ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "data"), "", "get_data");
		ADD_PROPERTY(PropertyInfo(Variant::STRING, "error"), "", "get_error");

		ADD_SIGNAL(MethodInfo("response", PropertyInfo(Variant::OBJECT, "response", PROPERTY_HINT_RESOURCE_TYPE, "YoutubePlayablesResponse")));
	}
public:
	void set_error(String p_error) { this->error = p_error; }
	bool has_error() const { return !error.is_empty(); }
	String get_error() const { return error; }

	void set_data(String p_data) { this->data = p_data; }
	String get_data() const { return data; }

	void _signal_response(Array p_input) {
		Dictionary dict = JSON::parse_string(p_input[0]);
		set_error(dict.get("error", ""));
		set_data(dict.get("data", ""));
		emit_signal("response", this);
	}

	void _signal_response_error(String p_input) {
		set_error(p_input);
		emit_signal("response", this);
	}

	void create_signal_reponse_callback() {
		JavaScriptBridge *singleton = JavaScriptBridge::get_singleton();
		if (!singleton) {
			ERR_PRINT("JavaScriptBridge singleton is invalid");
			return;
		}
		signal_response_callback = singleton->create_callback(Callable(this, "_signal_response"));
	}

	Ref<JavaScriptObject> get_signal_reponse_callback() {
		return signal_response_callback;
	}
};

#endif // YOUTUBE_PLAYABLES_RESPONSE_H
