#pragma once

#include "half.h"

namespace Pandora
{
	using int8 = int8_t;
	using uint8 = uint8_t;

	using int16 = int16_t;
	using uint16 = uint16_t;

	using int32 = int32_t;
	using uint32 = uint32_t;

	using int64 = int64_t;
	using uint64 = uint64_t;

	using namespace half_float::literal;
	using half_float::half_cast;
	using float16 = half_float::half;

	using float32 = float;
	using float64 = double;
}
