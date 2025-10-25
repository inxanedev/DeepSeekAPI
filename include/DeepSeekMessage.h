#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace inx::DeepSeek {
	/// <summary>
	/// Represents a message in the DeepSeek conversation.
	/// <para>Used for a nice implementation of the message history.</para>
	/// </summary>
	class Message {
	public:
		/// <summary>
		/// Represents the author of the message.
		/// </summary>
		enum class Role {
			/// <summary>
			/// The system prompt message.
			/// </summary>
			System,
			/// <summary>
			/// The user's messages.
			/// </summary>
			User,
			/// <summary>
			/// The AI's responses.
			/// </summary>
			Assistant
		};
		Message(Role role, const std::string& content)
			: role(role), content(content) {}

		Role role;
		std::string content;

		/// <summary>
		/// (internal) Converts the message to a JSON object for API calls.
		/// </summary>
		/// <returns>Example: {"role": "assistant", "content": "Hello! How can I help you?"}</returns>
		nlohmann::json ToJSON() const;
	};
}