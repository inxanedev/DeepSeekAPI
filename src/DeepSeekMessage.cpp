#include "DeepSeekMessage.h"

std::string RoleToString(inx::DeepSeek::Message::Role role)
{
	switch (role) {
	case inx::DeepSeek::Message::Role::System:
		return "system";
	case inx::DeepSeek::Message::Role::User:
		return "user";
	case inx::DeepSeek::Message::Role::Assistant:
		return "assistant";
	default: // only adding this to avoid compiler warnings
		return "user";
	}
}

nlohmann::json inx::DeepSeek::Message::ToJSON() const
{
	nlohmann::json object;
	object["role"] = RoleToString(role);
	object["content"] = content;
	return object;
}
