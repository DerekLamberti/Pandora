#pragma once
#include <type_traits>

#include "SwizzleHelper.h"

namespace Pandora
{
	namespace Math
	{
#define IsVector3Like(TypeName) std::is_convertible_v<TypeName, Vector3<decltype(std::declval<TypeName>().x)>>

		// Generic 3 component Vector class.
		template<typename T>
		struct Vector3 : public SwizzleHelper<T>
		{
		public:
			using ValueType = T;

			using typename SwizzleHelper<T>::UXY;
			using typename SwizzleHelper<T>::UXZ;
			using typename SwizzleHelper<T>::UYZ;
			using typename SwizzleHelper<T>::UXYZ;
			using typename SwizzleHelper<T>::SX;
			using typename SwizzleHelper<T>::SY;
			using typename SwizzleHelper<T>::SZ;

			template<int N>
			using Offset = typename SwizzleHelper<T>:: template Offset<N>;

			Vector3(T ix, T iy, T iz) 
				: x(ix), y(iy), z(iz) 
			{}

			Vector3(const Vector3& other)
				: Vector3(other.x, other.y, other.z)
			{}

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
				typename = std::enable_if_t<IsVector3Like(Vec3Type) &&
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
				typename = std::enable_if_t<IsVector3Like(Vec3T) && 
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
				typename = std::enable_if_t<IsVector3Like(Vec3T) &&
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

			template<typename Vec3T,
				typename = std::enable_if_t<IsVector3Like(Vec3T) &&
				!std::is_same<Vec3T, Vector3<T>>::value>>
			Vector3<T>& operator/=(const Vec3T &o)
			{
				Vector3<T> other = o;
				(*this) /= other;
				return (*this);
			}

		private:
#include "DefineSwizzle2.inl"
#include "DefineSwizzle2withZ.inl"
#include "DefineSwizzle3.inl"
			
		public:

			union {
#include "DeclareSwizzle2.inl"
#include "DeclareSwizzle2WithZ.inl"
#include "DeclareSwizzle3.inl"

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


		template<typename T>
		struct IsVector3Type
		{
			constexpr static const bool Value = std::is_convertible_v < T, Vector3<decltype(std::declval<T>().x)>>;
		};

		template<typename T>
		constexpr bool IsVector3 = IsVector3Type<T>::Value;

		template<typename T1, typename ... TypesList>
		struct AllVector3Types	{
			constexpr static const bool Value = IsVector3<T1> &&
				AllVector3Types<TypesList...>::Value;
		};

		template<typename T1>
		struct AllVector3Types<T1>
		{
			constexpr static const bool Value = IsVector3<T1>;
		};

		template<typename ... TypesList>
		constexpr bool AllVector3 = AllVector3Types<TypesList...>::Value;




		// Equality operators
		template<typename Vec3T1, typename Vec3T2,
			typename = std::enable_if_t<AllVector3<Vec3T1, Vec3T2>>>
		bool operator==(const Vec3T1& a, const Vec3T2& b)
		{
			return a.x == b.x && a.y == b.y && a.z == b.z;
		}

		// Mutlitply a Vector by a scalar
		template<typename Vec3T1, typename S,
			typename = std::enable_if_t<IsVector3<Vec3T1> && std::is_arithmetic<S>::value>>
		auto operator * (const Vec3T1& vec, S scale)
		{
			return Make_Vector(vec.x * scale, vec.y * scale, vec.z * scale);
		}

		// Multiply two vectors of the same type componentwise
		template<typename Vec3T1, typename Vec3T2,
			typename = std::enable_if_t<IsVector3Like(Vec3T1) && IsVector3Like(Vec3T2)> >
		auto operator * (const Vec3T1& a, const Vec3T2& b)
		{
			return Make_Vector(a.x * b.x, a.y * b.y, a.z * b.z);
		}

		// Divide a 3 component Vector by a scalar
		template<typename Vec3T, typename S,
			typename = std::enable_if_t<IsVector3<Vec3T> && std::is_arithmetic<S>::value>>
		auto operator / (const Vec3T& vec, S scale)
		{
			return Make_Vector(vec.x / scale, vec.y / scale, vec.z / scale);
		}

		// Divide two 3 component vectors componentwise
		template<typename Vec3T1, typename Vec3T2,
			typename = std::enable_if_t<IsVector3Like(Vec3T1) && IsVector3Like(Vec3T2)> >
		auto operator / (const Vec3T1& a, const Vec3T2& b)
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
		template<typename Vec3T1, typename Vec3T2,
			typename = std::enable_if_t<AllVector3<Vec3T1, Vec3T1>>>
		auto Dot(const Vec3T1& a, const Vec3T2& b)
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

		// Return the square length of a vector3
		template<typename Vec3T,
			typename = std::enable_if_t<AllVector3<Vec3T>>>
		auto Length2(const Vec3T &a)
		{
			return Dot(a, a);
		}

		// Return the length of a vector3
		template<typename Vec3T,
			typename = std::enable_if_t<AllVector3<Vec3T>>>
		auto Length(const Vec3T &a)
		{
			return sqrt(Length2(a));
		}

		// Alias the length function to return magnitude
		template<typename Vec3T, 
			typename = std::enable_if_t<AllVector3<Vec3T>>>
		inline auto Magnitude(const Vec3T& a)
		{
			return Length(a);
		}

		// Normaliza a vector3
		template<typename Vec3T,
			typename = std::enable_if_t<AllVector3<Vec3T>>>
		auto Normalize(const Vec3T& a)
		{
			return a / Length(a);
		}

		// Compute the componentwise minimum of two vector3
		template<typename Vec3T1, typename Vec3T2,
			typename = std::enable_if_t<AllVector3<Vec3T1, Vec3T2>>>
		auto Min(const Vec3T1 &a, const Vec3T2 &b)
		{
			return Make_Vector(
				std::min(a.x, b.x),
				std::min(a.y, b.y),
				std::min(a.z, b.z));
		}

		// Compute the componentwise maximum of two vector4
		template<typename Vec3T1, typename Vec3T2,
			typename = std::enable_if_t<AllVector3<Vec3T1, Vec3T2>>>
		auto Max(const Vec3T1 &a, const Vec3T2 &b)
		{
			return Make_Vector(
				std::max(a.x, b.x),
				std::max(a.y, b.y),
				std::max(a.z, b.z));
		}

		// Returns the compoenent wise clamped values between min and max.
		template<typename Vec3T1, typename Vec3T2, typename Vec3T3,
			typename = std::enable_if_t<AllVector3<Vec3T1, Vec3T2, Vec3T3>>>
		auto Clamp(const Vec3T1 &value, const Vec3T2 &min, const Vec3T3 &max)
		{
			return Min(max, Max(min, value));
		}

	}
}
