#include "DeepSeekAPI.h"
#include <curl/curl.h>

inx::DeepSeek::API::API(std::string_view api_key, Model model, std::string_view system_prompt)
{
	APIKey = api_key;
	SystemPrompt = system_prompt;
    SelectedModel = model;
	ResetMessageHistory();
}

void inx::DeepSeek::API::AddMessage(const std::string& message)
{
	History.emplace_back(Message::Role::User, message);
}

void inx::DeepSeek::API::AddCustomMessage(const Message& message)
{
	History.push_back(message);
}

std::string inx::DeepSeek::API::AddMessageAndGetCompletion(const std::string& message)
{
	AddMessage(message);
	return GetCompletion();
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::string* s = static_cast<std::string*>(userp);
    size_t totalSize = size * nmemb;
    s->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string inx::DeepSeek::API::GetCompletion() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize CURL");
    }

    std::string url = "https://api.deepseek.com/chat/completions";
    std::string response_string;
    std::string body_str;

    nlohmann::json body;
    body["model"] = ModelToString(SelectedModel);

	if (MaxTokens.has_value()) {
		body["max_tokens"] = MaxTokens.value();
	}
	if (Temperature.has_value()) {
		body["temperature"] = Temperature.value();
	}
	if (TopP.has_value()) {
		body["top_p"] = TopP.value();
	}

    nlohmann::json messages = nlohmann::json::array();
    for (const auto& message : History) {
        messages.push_back(message.ToJSON());
    }
    body["messages"] = messages;
    body_str = body.dump();

    struct curl_slist* headers = nullptr;
    std::string auth_header = "Authorization: Bearer " + APIKey;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, auth_header.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body_str.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body_str.size());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
    }

    nlohmann::json json_response = nlohmann::json::parse(response_string);
    std::string response_message = json_response["choices"][0]["message"]["content"].get<std::string>();
    
    History.emplace_back(Message::Role::Assistant, response_message);

    return response_message;
}

std::string inx::DeepSeek::API::GetSingleCompletion(const std::string& system_prompt, const std::string& user_message)
{
    std::vector<Message> previous_history = History;
	ResetMessageHistory(system_prompt);
	AddMessage(user_message);
	std::string response = GetCompletion();
	History = previous_history;
	return response;
}

void inx::DeepSeek::API::SetMessageHistory(const std::vector<Message>& new_history)
{
	History = new_history;
}

void inx::DeepSeek::API::ResetMessageHistory(std::optional<std::string> new_system_prompt)
{
	History.clear();
	if (new_system_prompt.has_value()) {
		SystemPrompt = new_system_prompt.value();
	}
	History.emplace_back(Message::Role::System, SystemPrompt);
}

const std::vector<inx::DeepSeek::Message>& inx::DeepSeek::API::GetMessageHistory() const
{
	return History;
}

void inx::DeepSeek::API::SetModel(Model model)
{
	SelectedModel = model;
}

inx::DeepSeek::Balance inx::DeepSeek::API::GetBalance()
{
	CURL* curl = curl_easy_init();
	if (!curl) {
		throw std::runtime_error("Failed to initialize CURL");
	}
	std::string url = "https://api.deepseek.com/user/balance";
	std::string response_string;
	struct curl_slist* headers = nullptr;
	std::string auth_header = "Authorization: Bearer " + APIKey;
	headers = curl_slist_append(headers, auth_header.c_str());
	headers = curl_slist_append(headers, "Accept: application/json");
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
	CURLcode res = curl_easy_perform(curl);
	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);
	if (res != CURLE_OK) {
		throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
	}
	nlohmann::json json_response = nlohmann::json::parse(response_string);
	Balance balance;
	balance.IsAvailable = json_response["is_available"].get<bool>();
	balance.Currency = json_response["balance_infos"][0]["currency"].get<std::string>();
	balance.TotalBalance = std::stod(json_response["balance_infos"][0]["total_balance"].get<std::string>());
	balance.GrantedBalance = std::stod(json_response["balance_infos"][0]["granted_balance"].get<std::string>());
	balance.ToppedUpBalance = std::stod(json_response["balance_infos"][0]["topped_up_balance"].get<std::string>());
	return balance;
}
