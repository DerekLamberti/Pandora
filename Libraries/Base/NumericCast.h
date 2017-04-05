#pragma once

#include <type_traits>
#include <cassert>

// Enable numeric cast test ALWAYS when asserts are enabled (ie Debug).
#ifndef NDEBUG
#define VALIDATE_NUMERIC_CAST
#endif


// If numeric cast tests are enabled, select test method. (assert or exception)
#if defined(VALIDATE_NUMERIC_CAST)
#	if defined(VALIDATE_NUMERIC_CAST_WITH_EXCEPTIONS) // defined before header is included. Used to turn on exceptions for unit tests.
#		define THROW_ASSERT(x,e) if (!(x)) throw e;
#	else
#		define THROW_ASSERT(x,e) assert(x)
#	endif
#else 
#	define THROW_ASSERT(x,e)
#endif

// Inlude exceptions and define a general exception for numeric_cast failures.
#if defined(VALIDATE_NUMERIC_CAST_WITH_EXCEPTIONS)
#include <exception>

// Define a general exception for numeric cast errors.
struct BadNumericCast : public std::exception
{
	const char* What() const throw()
	{
		return "Numeric cast exception. Bad cast.";
	}
};
#endif

namespace Pandora
{
	template<typename D, typename S>
	typename std::enable_if< std::is_unsigned<S>::value && std::is_unsigned<D>::value, D>::type
		numeric_cast(S source)
	{
		THROW_ASSERT(source <= std::numeric_limits<D>::max(), BadNumericCast());
		return static_cast<D>(source);
	};

	template<typename D, typename S>
	typename std::enable_if< std::is_signed<S>::value && std::is_signed<D>::value, D>::type
		numeric_cast(S source)
	{
		THROW_ASSERT(std::abs(source) <= std::numeric_limits<D>::max(), BadNumericCast());
		return static_cast<D>(source);
	};

	// numeric cast from unsigned to signed checked for narrowing overflows
	template<typename S, typename U>
	typename std::enable_if< std::is_signed<S>::value && std::is_unsigned<U>::value, S>::type
		numeric_cast(U uValue)
	{
		THROW_ASSERT(uValue <= static_cast< typename std::make_unsigned<S>::type >(std::numeric_limits<S>::max()), BadNumericCast());
		return static_cast<S>(uValue);
	};

	// numeric cast from signed to unsigned checked for narrowing overflows
	template<typename U, typename S>
	typename std::enable_if< std::is_unsigned<U>::value && std::is_signed<S>::value, U>::type
		numeric_cast(S sValue)
	{
		THROW_ASSERT(sValue >= 0 && static_cast< typename std::make_unsigned<S>::type >(sValue) <= std::numeric_limits<U>::max(), BadNumericCast());
		return static_cast<U>(sValue);
	};
}

#undef VALIDATE_NUMERIC_CAST