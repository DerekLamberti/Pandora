#pragma once


namespace Pandora {

	// Removes Const Volatile Reference qualifiers if present. (Same as C++20 std::remove_cvref)
	template<typename T>
	struct RemoveCVRef
	{
		using Type = std::remove_cv_t<std::remove_reference_t<T>>;
	};

	// Short hand version
	template<typename T>
	using RemoveCVRefT = typename RemoveCVRef<T>::Type;


	// Returns true at compile time if Any of the list of subsequent types match the first type.
	template<typename TypeToMatch, typename T, typename ... Args>
	constexpr bool IsSameAny()
	{
		if constexpr (sizeof...(Args) > 0)
			return IsSameAny<TypeToMatch, Args...>() || std::is_same_v<TypeToMatch, T>;
		else
			return std::is_same_v<TypeToMatch, T>;
	};

	template<typename TypeToMatch, typename T, typename ... Args>
	constexpr bool IsSameAnyV = IsSameAny < TypeToMatch, T, Args... >();

} // Pandora