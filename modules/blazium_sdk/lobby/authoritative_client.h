/**************************************************************************/
/*  lobby_client.h                                                        */
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

#ifndef AUTHORITATIVE_CLIENT_H
#define AUTHORITATIVE_CLIENT_H

#include "lobby_client.h"

class AuthoritativeClient : public LobbyClient {
	GDCLASS(AuthoritativeClient, LobbyClient);

public:
	class LobbyCallResponse : public RefCounted {
		GDCLASS(LobbyCallResponse, RefCounted);

	protected:
		static void _bind_methods() {
			ADD_SIGNAL(MethodInfo("finished", PropertyInfo(Variant::OBJECT, "result", PROPERTY_HINT_RESOURCE_TYPE, "LobbyCallResult")));
		}

	public:
		class LobbyCallResult : public RefCounted {
			GDCLASS(LobbyCallResult, RefCounted);
			Variant result;
			String error;

		protected:
			static void _bind_methods() {
				ClassDB::bind_method(D_METHOD("has_error"), &LobbyCallResult::has_error);
				ClassDB::bind_method(D_METHOD("get_error"), &LobbyCallResult::get_error);
				ClassDB::bind_method(D_METHOD("get_result"), &LobbyCallResult::get_result);
				ADD_PROPERTY(PropertyInfo(Variant::STRING, "error"), "", "get_error");
			}

		public:
			void set_error(String p_error) { this->error = p_error; }
			void set_result(Variant p_result) { this->result = p_result; }

			bool has_error() const { return !error.is_empty(); }
			String get_error() const { return error; }
			Variant get_result() const { return result; }
		};
	};

protected:
	static void _bind_methods();

public:
	Ref<LobbyCallResponse> lobby_call(const String &p_method, const Array &p_args);

	AuthoritativeClient() {
		server_url = "wss://authlobby.blazium.app/connect";
	}
};

#endif // AUTHORITATIVE_CLIENT_H
