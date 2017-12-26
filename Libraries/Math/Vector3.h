#pragma once
#include <type_traits>

#include "SwizzleHelper.h"
#include "../Base/TypeHelpers.h"

namespace Pandora
{
	namespace Math
	{

		// Generic 3 component Vector class.
		template<typename T>
		struct Vector3 : public SwizzleHelper<T>
		{
		public:
			using ValueType = T;

			Vector3(T ix, T iy, T iz) 
				: x(ix), y(iy), z(iz) 
			{}

			Vector3(const Vector3& other)
				: Vector3(other.x, other.y, other.z)
			{}

			Vector3& operator()()
			{
				return (*this);
			}

			Vector3& operator=(const Vector3& other)
			{
				x = other.x;
				y = other.y;
				z = other.z;
				return (*this);
			}

			template<typename S,
				typename = std::enable_if_t<std::is_arithmetic<S>::value>>
			Vector3<T>& operator*=(S s)
			{
				x *= s;
				y *= s;
				z *= s;
				return (*this);
			}

			template<typename S,
				typename = std::enable_if_t<std::is_arithmetic<S>::value>>
			Vector3<T>& operator/=(S s)
			{
				x /= s;
				y /= s;
				z /= s;
				return (*this);
			}

			Vector3<T>& operator+=(const Vector3<T> &o)
			{
				x += o.x;
				y += o.y;
				z += o.z;
				return (*this);
			}

			template<typename Vec3Type,
				typename = std::enable_if_t<IsVec3<Vec3Type> &&
				!std::is_same<Vec3Type, Vector3<T>>::value>>
				Vector3<T>& operator+=(const Vec3Type &o)
			{
				Vector3<T> other = static_cast<Vector3<T>>(o);
				(*this) += other;
				return (*this);
			}


			Vector3<T>& operator-=(const Vector3<T> &o)
			{
				x -= o.x;
				y -= o.y;
				z -= o.z;
				return (*this);
			}

			
			template<typename Vec3T,
				typename = std::enable_if_t<IsVec3<Vec3T> && 
				!std::is_same<Vec3T, Vector3<T>>::value>>
			Vector3<T>& operator-=(const Vec3T &o)
			{
				Vector3<T> other = static_cast<Vector3<T>>(o);
				(*this) -= other;
				return (*this);
			}
			

			Vector3<T>& operator*=(const Vector3<T> &o)
			{
				x *= o.x;
				y *= o.y;
				z *= o.z;
				return (*this);
			}

			template<typename Vec3T,
				typename = std::enable_if_t<IsVec3<Vec3T> &&
				!std::is_same<Vec3T, Vector3<T>>::value>>
			Vector3<T>& operator*=(const Vec3T &o)
			{
				Vector3<T> other = static_cast<Vector3<T>>(o);
				(*this) *= other;
				return (*this);
			}


			Vector3<T>& operator/=(const Vector3<T> &o)
			{
				x /= o.x;
				y /= o.y;
				z /= o.z;
				return (*this);
			}

			template<	typename Vec3T,
						typename = std::enable_if_t<IsVec3<Vec3T> &&
									!std::is_same<Vec3T, Vector3<T>>::value>>
			Vector3<T>& operator/=(const Vec3T &o)
			{
				Vector3<T> other = o;
				(*this) /= other;
				return (*this);
			}

		private:
#include "DefineSwizzleTypes.inl"
#include "DefineSwizzlesX.inl"
#include "DefineSwizzlesY.inl"
#include "DefineSwizzlesZ.inl"
			
		public:
			union {
#include "DeclareSwizzlesX.inl"
#include "DeclareSwizzlesY.inl"
#include "DeclareSwizzlesZ.inl"

				struct
				{
					T x;
					T y;
					T z;
				};

				T v[3];

			};
		};

		// Create a Vector3 of a particular type
		template<typename T>
		Vector3<T> Make_Vector(T x, T y, T z)
		{
			return Vector3<T>(x, y, z);
		}

		// Stream operator Vector3
		template<typename T, typename StreamType>
		StreamType& operator<<(StreamType& stream, const Vector3<T> &obj)
		{
			stream << obj.x << obj.y << obj.z;
			return stream;
		}

		template<typename VecT1, typename VecT2>
		std::enable_if_t<AllVector3<VecT1, VecT2>, bool>
			operator==(const VecT1& a, const VecT2& b)
		{
			return a.x == b.x && a.y == b.y && a.z == b.z;
		}

		template<typename VecT1, typename VecT2>
		std::enable_if_t<AllVector3<VecT1, VecT2>, bool>
			operator!=(const VecT1& a, const VecT2& b)
		{
			return !(a == b);
		}

		// Equality operators
//		bool operator==(const Vec3T1& a, const Vec3T2& b)
//		{
//			return a.x == b.x && a.y == b.y && a.z == b.z;
//		}

		// Mutlitply a Vector by a scalar
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec3T1,
					typename S,
					typename = std::enable_if_t<AllVector3<Vec3T1<T, Args1...>> &&
												std::is_arithmetic_v<S>>
			>
		auto operator*(const Vec3T1<T, Args1...> &a, const S &s)
			-> Vector3<decltype(a.x * s)>
		{
			return Make_Vector(a.x * s, a.y * s, a.z* s);
		}

		// Multiply two vectors of the same type componentwise
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec3T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec3T2,
					typename = std::enable_if_t<AllVector3<Vec3T1<T, Args1...>, Vec3T2<U, Args2...>>>
		>
		auto operator*(const Vec3T1<T, Args1...> &a, const Vec3T2<U, Args2...> &b)
			-> Vector3<decltype(a.x*b.x)>
		{
			return Make_Vector(a.x * b.x, a.y * b.y, a.z*b.z);
		}

//		// Divide a 3 component Vector by a scalar
//		template<	typename T, typename ... Args1, template<typename, typename...> class Vec3T1,
//					typename S,
//					typename = std::enable_if_t<IsVec3V<Vec3T1<T, Args1...>> &&
//												std::is_arithmetic_v<S>>
//			>
//		auto operator/(const Vec3T1<T, Args1...> &a, const S &s)
//			-> Vector3<decltype(std::declval<T>() / std::declval<S>(s))>
//		{
//			return Make_Vector(a.x / s, a.y / s, a.z / s);
//		}
//
		template<	typename Vec2T,
					typename S,
					typename = std::enable_if_t<IsVec3V<Vec2T> &&
												std::is_arithmetic_v<S>>
			>
			auto operator/(const Vec2T &a, S s)
			-> Vector3<decltype(std::declval<typename Vec2T::ValueType>() / std::declval<S>())>
		{
//|#pragma message("got here v3")
			return Make_Vector(a.x / s, a.y / s, a.z / s);
		}


		// Divide two 3 component vectors componentwise
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec3T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec3T2,
					typename = std::enable_if_t<AllVector3<Vec3T1<T, Args1...>, Vec3T2<U, Args2...>>>
		>
		auto operator/(const Vec3T1<T, Args1...> &a, const Vec3T2<U, Args2...> &b)
			-> Vector3<decltype(a.x / b.x)>
		{
			return Make_Vector(a.x / b.x, a.y / b.y, a.z / b.z);
		}

		// Add two 3 component vectors componentwise
		template<typename Vec3T1, typename Vec3T2,
			typename = std::enable_if_t< AllVector3<Vec3T1, Vec3T2>>>
		auto operator + (const Vec3T1& vecA, const Vec3T2& vecB)
		{
			return Make_Vector(vecA.x + vecB.x, vecA.y + vecB.y, vecA.z + vecB.z);
		}

		// Subtract two 3 componet vectors componentwise
		template<typename Vec3T1, typename Vec3T2, 
			typename = std::enable_if_t<AllVector3<Vec3T1, Vec3T1>>> 
		auto operator - (const Vec3T1& vecA, const Vec3T2& vecB)
		{
			return Make_Vector(vecA.x - vecB.x, vecA.y - vecB.y, vecA.z - vecB.z);
		}

		// Return the dot product of two 3 component vectors
		template<	typename Vec3T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec3T2,
					typename = std::enable_if_t<AllVector3<Vec3T1, Vec3T2<U, Args2...>>>
		>
		auto Dot(const Vec3T1 &a, const Vec3T2<U, Args2...> &b)
			-> decltype(a.x*b.x)
		{
			return a.x*b.x + a.y*b.y + a.z*b.z;
		}

		// Return the cross product of two vectors
		template<typename Vec3T1, typename Vec3T2,
			typename = std::enable_if_t<AllVector3<Vec3T1, Vec3T2>>>
		auto Cross(const Vec3T1 &a, const Vec3T2 &b)
		{
			return Make_Vector(	a.y*b.z - a.z*b.y,
								a.z*b.x - a.x*b.z,
								a.x*b.y - a.y*b.x
				);
		}

		template<	typename T, typename ... Args1, template<typename, typename...> class Vec3T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec3T2,
					typename = std::enable_if_t<AllVector3<Vec3T1<T, Args1...>, Vec3T2<U, Args2...>>>
		>
		auto Min(const Vec3T1<T, Args1...> &a, const Vec3T2<U, Args2...> &b)
			->Vector3<RemoveCVRefT<T>>
		{
			static_assert(std::is_same_v<T, U>, "Cannot find minimum between Vector3 with different value types. Return type is ambiguous.");
			return Make_Vector(
				std::min(a.x, b.x),
				std::min(a.y, b.y),
				std::min(a.z, b.z));
		}

		// Compute the componentwise maximum of two vector3
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec3T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec3T2,
					typename = std::enable_if_t<AllVector3<Vec3T1<T, Args1...>, Vec3T2<U, Args2...>>>
		>
		auto Max(const Vec3T1<T, Args1...> &a, const Vec3T2<U, Args2...> &b)
			->Vector3<RemoveCVRefT<T>>
		{
			static_assert(std::is_same_v<T, U>, "Cannot find maximum between Vector3 with different value types. Return type is ambiguous.");

			return Make_Vector(
				std::max(a.x, b.x),
				std::max(a.y, b.y),
				std::max(a.z, b.z));
		}

		// Returns the compoenent wise clamped values between min and max.
		template<	typename T, typename ... Args1, template<typename, typename...> class Vec3T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec3T2,
					typename V, typename ... Args3, template<typename, typename...> class Vec3T3,
					typename = std::enable_if_t<AllVector3<Vec3T1<T, Args1...>, Vec3T2<U, Args2...>, Vec3T3<V, Args3...>>>
		>
		auto Clamp(const Vec3T1<T, Args1...> &val, const Vec3T2<U, Args2...> &min, const Vec3T3<V, Args3...> &max)
			->Vector3<RemoveCVRefT<T>>
		{

			static_assert(std::is_same_v<T, U> && std::is_same_v<T, V>,
				"Cannot clamp between Vector3 with different value types. Return type is ambiguous.");

			return Min(max, Max(min, val));
		}
	}
}
