#pragma once

#include "../Base/Base.h"
#include "../Base/TypeHelpers.h"
#include "SwizzleHelper.h"

namespace Pandora
{
	namespace Math {
		// Generic 2 component Vector class.
		template<typename t>
		struct Vector2;

		// Generic 3 component Vector class.
		template<typename T>
		struct Vector3;

		// Generic 4 component Vector class.
		template<typename T>
		struct Vector4;
		
		// Define some common Vector2 types.
		using Vec2d = Vector2<float64>;
		using Vec2f = Vector2<float32>;
		using Vec2h = Vector2<float16>;
		using Vec2i = Vector2<int32>;

		// Define some common Vector3 types.
		using Vec3d = Vector3<float64>;
		using Vec3f = Vector3<float32>;
		using Vec3h = Vector3<float16>;
		using Vec3i = Vector3<int32>;

		// Define some common Vector4 types.
		using Vec4d = Vector4<float64>;
		using Vec4f = Vector4<float32>;
		using Vec4h = Vector4<float16>;
		using Vec4i = Vector4<int32>;

		template<typename T, typename U, typename ... Args, template<typename, typename...> class VecT>
		auto vector_cast(const VecT<U, Args...> &other)
		{
			using VecType = VecT<U, Args...>;
			static_assert(!std::is_reference_v<T>, "Type T cannot be reference type for vector type");
			if constexpr (IsVec2V<VecType>)
			{
				return Make_Vector(
					static_cast<T>(other.x), 
					static_cast<T>(other.y));
			} 
			else if constexpr (IsVec3V<VecType>)
			{
				return Make_Vector(
					static_cast<T>(other.x),
					static_cast<T>(other.y),
					static_cast<T>(other.z));
			}
			else if constexpr (IsVec4V<VecType>)
			{
				return Make_Vector(
					static_cast<T>(other.x),
					static_cast<T>(other.y),
					static_cast<T>(other.z),
					static_cast<T>(other.w));
			}
			else
			{
				static_assert(false, "Cannot vector_cast from unknown vector type.");
			}
		}

		// Return the square length of any vector
		template<	typename T, typename ...Args, template<typename, typename...> class VecType,
					typename = std::enable_if_t<AllVector2<VecType<T, Args...>> ||
												AllVector3<VecType<T, Args...>> ||
												AllVector4<VecType<T, Args...>>>
		>
		T Length2(const VecType<T, Args...> &a)
		{
			return Dot(a, a);
		}


		// Return the length of any vector
		template<	typename T, typename ...Args, template<typename, typename...> class VecType,
					typename = std::enable_if_t<AllVector2<VecType<T, Args...>> ||
												AllVector3<VecType<T, Args...>> ||
												AllVector4<VecType<T, Args...>>>
		>
		auto Length(const VecType<T, Args...> &a)
			-> decltype(sqrt(std::declval<T>()))
		{
			return sqrt(Length2(a));
		}

		// Alias the length function to return magnitude
		template<	typename T, typename ...Args, template<typename, typename...> class VecType,
					typename = std::enable_if_t<AllVector2<VecType<T, Args...>> ||
												AllVector3<VecType<T, Args...>> ||
												AllVector4<VecType<T, Args...>>>
		>
		inline auto Magnitude(const VecType<T, Args...> &a)
		{
			return Length(a);
		}

		template<	typename T, template<typename, typename...> class VecType, typename ...Args,
					typename = std::enable_if_t<IsAnyVecTypeV<VecType<T, Args...>>>
		>
		inline auto Normalize(const VecType<T, Args...> &a)
			-> RemoveCVRefT< decltype(std::declval<VecType<T, Args...>>()()) >
		{
			return a / Length(a);
		}
	}
}

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"