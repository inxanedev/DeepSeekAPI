#pragma once

#include <string>
#include <vector>
#include "DeepSeekMessage.h"
#include "DeepSeekModel.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Crypt32.lib")
#ifdef _MSC_VER
#pragma comment(lib, "Secur32.lib")
#endif

namespace inx::DeepSeek {
	/// <summary>
	/// The main class for interacting with the DeepSeek API.
	/// </summary>
	class API {
	public:
		/// <summary>
		/// Instantiates the DeepSeek API wrapper.
		/// </summary>
		/// <param name="api_key">Your API key from https://platform.deepseek.com/api_keys</param>
		/// <param name="model">The model to use for completions</param>
		/// <param name="system_prompt">The system prompt (it will be added as the first system message)</param>
		API(std::string_view api_key, Model model, std::string_view system_prompt);

		/// <summary>
		/// Adds your message to the history.
		/// <para>Usually, you'd call GetCompletion after this.</para>
		/// </summary>
		/// <param name="message">The message to add</param>
		void AddMessage(const std::string& message);

		/// <summary>
		/// Adds a custom message to the history. You can define the role (system, user, assistant) yourself.
		/// </summary>
		/// <param name="message">The message to add</param>
		void AddCustomMessage(const Message& message);

		/// <summary>
		/// Adds the message to the history and calls GetCompletion for you.
		/// <para>This is a convenience function combining AddMessage and GetCompletion.</para>
		/// </summary>
		/// <param name="message">The message</param>
		/// <returns></returns>
		std::string AddMessageAndGetCompletion(const std::string& message);

		/// <summary>
		/// Performs a blocking completion request to DeepSeek.
		/// <para>It will use the message history from previous AddMessage calls.</para>
		/// <para>After the request, the return message will be added to the history as well.</para>
		/// </summary>
		/// <returns>The AI's response</returns>
		std::string GetCompletion();

		/// <summary>
		/// Performs a blocking completion request to DeepSeek.
		/// <para>It will not read any message history, this function creates its own, containing only the system prompt and the provided message.</para>
		/// <para>This is intended for single-turn interactions without maintaining state.</para>
		/// </summary>
		/// <param name="system_prompt">The system prompt</param>
		/// <param name="user_message">The user message</param>
		/// <returns></returns>
		std::string GetSingleCompletion(const std::string& system_prompt, const std::string& user_message);

		/// <summary>
		/// Overwrites the message history with your own one.
		/// <para>This will remove all previous history!</para>
		/// <para>Make sure the first message is a system prompt message.</para>
		/// </summary>
		/// <param name="new_history">The history to overwrite the current one with.</param>
		void SetMessageHistory(const std::vector<Message>& new_history);

		/// <summary>
		/// Resets the message history to only contain the system prompt.
		/// </summary>
		/// <param name="new_system_prompt">If provided, replaces the current system prompt with this new one.</param>
		void ResetMessageHistory(std::optional<std::string> new_system_prompt = {});

		/// <summary>
		/// Returns a non-modifiable message history as an std::vector.
		/// </summary>
		/// <returns></returns>
		const std::vector<Message>& GetMessageHistory() const;

		/// <summary>
		/// Changes the model used for completions.
		/// </summary>
		/// <param name="model">The new model</param>
		void SetModel(Model model);
	private:
		std::string APIKey, SystemPrompt;
		std::vector<Message> History;
		Model SelectedModel;
	};
}