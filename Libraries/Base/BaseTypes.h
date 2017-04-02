#pragma once

#include "half.h"

namespace Pandora
{

	typedef char int8;
	typedef unsigned char uint8;

	typedef short int16;
	typedef unsigned short uint16;

	typedef int int32;
	typedef unsigned int uint32;

	typedef long long int64;
	typedef unsigned long long uint64;

	using namespace half_float::literal;
	using half_float::half_cast;
	typedef half_float::half float16;

	typedef float float32;
	typedef double float64;
}
