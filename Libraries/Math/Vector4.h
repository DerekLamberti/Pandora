#pragma once

#include "Vector3.h"
#include "../Base/TypeHelpers.h"
#include <type_traits>

namespace Pandora {
	namespace Math {

#define IsVector4Like(TypeName) std::is_convertible_v<TypeName, Vector4<decltype(std::declval<TypeName>().x)>>

		// Generic 4 component Vector class.
		template<typename T>
		struct Vector4 : public SwizzleHelper<T>
		{
		public:
			using ValueType = T;

			Vector4(T x, T y, T z, T w) 
				: x(x), y(y), z(z), w(w) 
			{}

			Vector4(const Vector4& other) 
				: Vector4(other.x, other.y, other.z, other.w)
			{}

			const Vector4& operator()() const
			{
				return (*this);
			}

			Vector4& operator=(const Vector4& other)
			{
				x = other.x;
				y = other.y;
				z = other.z;
				w = other.w;
				return (*this);
			}

//			Vector4<T>& operator+=(const Vector4<T> &o)
//			{
//				static_assert(false, "Ho humm");
//				x += o.x;
//				y += o.y;
//				z += o.z;
//				w += o.w;
//				return (*this);
//			}
//
//			template<typename T, typename ...Args>
//			Vector4<T>& operator+=(const Swizzle4T<T, Args...> &o)
//			{
//				static_assert(false, "Goody");
//				(*this) += o();
//				return (*this);
//			}
			template<	typename U, typename ... Args, template<typename, typename...> class VecT,
						typename = std::enable_if_t<AllVector4<VecT<U, Args...>>>
			>
				Vector4<T>& operator+=(const VecT<U, Args...> &o)
			{
				if constexpr (IsSameAnyV<VecT<U, Args...>,
					Vector4<T>, XYZW, 
					XYWW, XZZW, XZWW, XWWW,
					YYZW, YYWW, YZWW, YWWW,
					ZZZW, ZWWW, WWWW>)
				{
					x += o.x;
					y += o.y;
					z += o.z;
					w += o.w;
					return (*this);
				}
				else
				{
					// Cast to Vector4 then recursively call += operator.
					(*this) += o(); 
					return (*this);
				}
			}

			Vector4<T>& operator-=(const Vector4<T> &o)
			{
				x -= o.x;
				y -= o.y;
				z -= o.z;
				w -= o.w;
				return (*this);
			}


			template<	typename S, 
						typename = std::enable_if_t<std::is_arithmetic_v<S> &&
													!IsAnyVecTypeV<S>>
			>
			Vector4<T>& operator*=(S s)
			{
				x *= s;
				y *= s;
				z *= s;
				w *= s;
				return (*this);
			}

			Vector4<T>& operator*=(const Vector4<T> &o)
			{
				x *= o.x;
				y *= o.y;
				z *= o.z;
				w *= o.w;
				return (*this);
			}

			template<	typename VecT,
						typename = std::enable_if_t<IsVec4<VecT>>
			>
				Vector4<T>& operator*=(const VecT &o)
			{
				(*this) += o();
				return (*this);
			}

			template<	typename S,
						typename = std::enable_if_t<std::is_arithmetic_v<S>>
			>
			Vector4<T>& operator/=(S s)
			{
				x /= s;
				y /= s;
				z /= s;
				w /= s;
				return (*this);
			}

			Vector4<T>& operator/=(const Vector4<T> &o)
			{
				x /= o.x;
				y /= o.y;
				z /= o.z;
				w /= o.w;
				return (*this);
			}

			template<	typename VecT,
						typename = std::enable_if_t<IsVec4<VecT> &&
										!std::is_same<VecT, Vector4<T>>::value>
			>
				Vector4<T>& operator/=(const VecT& o)
			{
				(*this) /= o();
				return (*this);
			}



		private:
#include "DefineSwizzleTypes.inl"
#include "DefineSwizzlesX.inl"
#include "DefineSwizzlesY.inl"
#include "DefineSwizzlesZ.inl"
#include "DefineSwizzlesW.inl"

		public:
			union {
#include "DeclareSwizzlesX.inl"
#include "DeclareSwizzlesY.inl"
#include "DeclareSwizzlesZ.inl"
#include "DeclareSwizzlesW.inl"

				struct {
					T x;
					T y;
					T z;
					T w;
				};

				T v[4];
			};
		};

		// Create a Vector4 of a particular type
		template<typename T>
		Vector4<T> Make_Vector(T x, T y, T z, T w)
		{
			return Vector4<T>(x, y, z, w);
		}

		// Create a vector4 from a vector3 and a w
		template<typename T>
		Vector4<T> Make_Vector(const Vector3<T>& i, T w)
		{
			return Vector4<T>(i.x, i.y, i.z, w);
		}

		// Stream operator Vector4
		template<typename T, typename StreamType>
		StreamType& operator<<(StreamType& stream, const Vector4<T> &obj)
		{
			stream << obj.x << obj.y << obj.z << obj.w;
			return stream;
		}

		template<typename VecT1, typename VecT2>
		std::enable_if_t<AllVector4<VecT1, VecT2>, bool>
			operator==(const VecT1& a, const VecT2& b)
		{
			return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
		}

		template<typename VecT1, typename VecT2>
		std::enable_if_t<AllVector4<VecT1, VecT2>, bool>
			operator!=(const VecT1& a, const VecT2& b)
		{
			return !(a == b);
		}

		// Divide a vector by a scalar
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec4T1,
					typename S,
					typename = std::enable_if_t<IsVec4V<Vec4T1<T, Args1...>> &&
												std::is_arithmetic_v<S>>
		>
		auto operator/(const Vec4T1<T, Args1...> &vec, const S &s)
			-> Vector4<decltype(std::declval<T>() / std::declval<S>())>
		{
			return Make_Vector(vec.x / s, vec.y / s, vec.z / s, vec.w / s);
		}

		// Divide two vectors of the same type componentwise
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec4T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec4T2,
					typename = std::enable_if_t<AllVector4<Vec4T1<T, Args1...>, Vec4T2<U, Args2...>>>
		>
		auto operator/(const Vec4T1<T, Args1...> &a, const Vec4T2<U, Args2...> &b)
			-> Vector4<decltype(a.x/b.x)>
		{
			return Make_Vector(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
		}

		// Multiply a vector by a scalar
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec4T1,
					typename S,
					typename = std::enable_if_t<AllVector4<Vec4T1<T, Args1...>> &&
					std::is_arithmetic_v<S>>
		>
		auto operator*(const Vec4T1<T, Args1...> &a, const S &s)
			-> Vector4<decltype(a.x*s)>
		{
			return Make_Vector(a.x * s, a.y * s, a.z* s, a.w * s);
		}

		// Multiply two vectors of the same type componentwise
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec4T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec4T2,
					typename = std::enable_if_t<AllVector4<Vec4T1<T, Args1...>, Vec4T2<U, Args2...>>>
		>
		auto operator*(const Vec4T1<T, Args1...> &a, const Vec4T2<U, Args2...> &b)
			-> Vector4<decltype(a.x*b.x)>
		{
			return Make_Vector(a.x * b.x, a.y * b.y, a.z*b.z, a.w*b.w);
		}

		// Add two vectors of the same type componentwise
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec4T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec4T2,
					typename = std::enable_if_t<AllVector4<Vec4T1<T, Args1...>, Vec4T2<U, Args2...>>>
		>
		auto operator+(const Vec4T1<T, Args1...> &a, const Vec4T2<U, Args2...> &b)
			-> Vector4<decltype(a.x+b.x)>
		{
			return Make_Vector(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
		}

		// Subtract two vectors of the same type componentwise
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec4T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec4T2,
					typename = std::enable_if_t<AllVector4<Vec4T1<T, Args1...>, Vec4T2<U, Args2...>>>
		>
		auto operator-(const Vec4T1<T, Args1...> &a, const Vec4T2<U, Args2...> &b)
			-> Vector4<decltype(a.x - b.x)>
		{
			return Make_Vector(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
		}


		// Compute the componentwise minimum of two Vector4
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec4T1,
					typename Y, typename ... Args2, template<typename, typename...> class Vec4T2,
					typename = std::enable_if_t<std::is_arithmetic<T>::value && 
												std::is_arithmetic<Y>::value &&
												AllVector4<Vec4T1<T, Args1...>, Vec4T2<Y, Args2...>>>
			>
		auto Min(const Vec4T1<T, Args1...> &a, const Vec4T2<Y, Args2...> &b)
			->Vector4<RemoveCVRefT<decltype(std::min(std::declval<T>(), std::declval<Y>()))>>
		{
			return Make_Vector(
				std::min(a.x, b.x),
				std::min(a.y, b.y),
				std::min(a.z, b.z),
				std::min(a.w, b.w));
		}

		// Compute the componentwise maximum of two vector4
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec4T1,
					typename Y, typename ... Args2, template<typename, typename...> class Vec4T2,
					typename = std::enable_if_t<std::is_arithmetic<T>::value && 
												std::is_arithmetic<Y>::value &&
												AllVector4<Vec4T1<T, Args1...>, Vec4T2<Y, Args2...>>>
		>
		auto Max(const Vec4T1<T, Args1...> &a, const Vec4T2<Y, Args2...> &b)
			->Vector4<RemoveCVRefT<decltype(std::max(std::declval<T>(), std::declval<Y>()))>>
		{
			return Make_Vector(
				std::max(a.x, b.x),
				std::max(a.y, b.y),
				std::max(a.z, b.z),
				std::max(a.w, b.w));
		}

		// Returns the compoenent wise clamped values between min and max.
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec4T1,
					typename Y, typename ... Args2, template<typename, typename...> class Vec4T2,
					typename U, typename ... Args3, template<typename, typename...> class Vec4T3,
					typename = std::enable_if_t<std::is_arithmetic<T>::value &&
												std::is_arithmetic<Y>::value &&
												std::is_arithmetic<U>::value &&
												AllVector4<Vec4T1<T, Args1...>, Vec4T2<Y, Args2...>, Vec4T3<U, Args3...>>
												>
		>
		auto Clamp(const Vec4T1<T, Args1...> &value, const Vec4T2<Y, Args2...> &min, const Vec4T3<U, Args3...> &max)
			->Vector4<RemoveCVRefT<T>>
		{
			static_assert(std::is_same_v<T, U> && std::is_same_v<T, Y>,
				"Cannot clamp between Vector4 with different value types. Return type is ambiguous.");

			return Min(max, Max(min, value));
		}

		// Return the dot product of two 3 component vectors
		template<	typename Vec4T1,
					typename Vec4T2,
					typename = std::enable_if_t<AllVector4<Vec4T1, Vec4T2>>
		>
		auto Dot(const Vec4T1 &a, const Vec4T2 &b)
			-> decltype(a.x*b.x)
		{
			return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
		}

	}
}
