#pragma once
#include <string>

namespace inx::DeepSeek {
	/// <summary>
	/// Represents the available DeepSeek models.
	/// </summary>
	enum class Model {
		/// <summary>
		/// The cheap, faster, but less capable model.
		/// </summary>
		DeepSeekChat,
		/// <summary>
		/// The more expensive, slower, but significantly more capable model.
		/// </summary>
		DeepSeekReasoner
	};
	/// <summary>
	/// (internal) Converts a Model enum to its string representation for API calls.
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	std::string ModelToString(Model model);
}