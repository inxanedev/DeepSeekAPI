#pragma once

#include <string>

namespace inx::DeepSeek {
	/// <summary>
	/// Represents the balance available for the provided API key.
	/// </summary>
	class Balance {
	public:
		/// <summary>
		/// Whether the user's balance is sufficient for API calls.
		/// </summary>
		bool IsAvailable;
		/// <summary>
		/// Possible values: "CNY", "USD"
		/// <para>The currency of the balance.</para>
		/// </summary>
		std::string Currency;
		/// <summary>
		/// The total available balance, including the granted balance and the topped-up balance.
		/// </summary>
		double TotalBalance;
		/// <summary>
		/// The total not expired granted balance.
		/// </summary>
		double GrantedBalance;
		/// <summary>
		/// The total topped-up balance.
		/// </summary>
		double ToppedUpBalance;
	};
}