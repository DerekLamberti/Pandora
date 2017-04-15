#pragma once

#include "../Base/Base.h"

namespace Pandora
{
	namespace Math {

		// Generic 3 component Vector class.
		template<typename T>
		struct Vector3
		{
		public:
			Vector3(T x, T y, T z) : X(x), Y(y), Z(z) {}

			T X;
			T Y;
			T Z;
		};

		// Define some common Vector3 types.
		typedef Vector3<float64>	Vec3d;
		typedef Vector3<float32>	Vec3f;
		typedef Vector3<float16>	Vec3h;
		typedef Vector3<int32>		Vec3i;

		// Create a Vector3 of a particular type.
		template<typename T>
		Vector3<T> Make_Vector(T x, T y, T z)
		{
			return Vector3<T>{ x,y,z };
		}

		// Stream operator
		template<typename T, typename StreamType>
		StreamType& operator<<(StreamType& stream, const Vector3<T> &obj)
		{
			stream << obj.X << obj.Y << obj.Z;
			return stream;
		}

		// Equality operator
		template<typename T>
		bool operator==(const Vector3<T>& a, const Vector3<T>& b)
		{
			return a.X == b.X && a.Y == b.Y && a.Z == b.Z;
		}

		// Inequality operator
		template<typename T>
		bool operator!=(const Vector3<T>& a, const Vector3<T>& b)
		{
			return !operator==(a, b);
		}

		// Mutlitply a Vector by a scalar
		template<typename T, typename S>
		Vector3<T> Mul(const Vector3<T>& vec, S scale)
		{
			return Vector3<T>{ vec.X * scale, vec.Y * scale, vec.Z * scale };
		}

		// Multiply two vectors of the same type componentwise
		template<typename T>
		Vector3<T> Mul(const Vector3<T>& a, const Vector3<T>& b)
		{
			return Vector3<T>{a.X * b.X, a.Y * b.Y, a.Z * b.Z};
		}

		// Multiple two vectors componentwise using operator *
		template<typename T>
		Vector3<T> operator*(const Vector3<T> &a, const Vector3<T> &b)
		{
			return Mul(a, b);
		}

		// Scale a vector using operator *
		template<typename T, typename S>
		Vector3<T> operator*(const Vector3<T> &a, S scale)
		{
			return Mul(a, scale);
		}

		// Add two vectors of the same type component wise
		template<typename T>
		Vector3<T> Add(const Vector3<T>& vecA, const Vector3<T>& vecB)
		{
			return Vector3<T>{vecA.X + vecB.X, vecA.Y + vecB.Y, vecA.Z + vecB.Z};
		}

		// Add two vectors using the + operator
		template<typename T>
		Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b)
		{
			return Add(a, b);
		}

		// Return the dot product of two vector3
		template<typename T>
		T Dot(const Vector3<T>& a, const Vector3<T>& b)
		{
			return a.X*b.X + a.Y*b.Y + a.Z*b.Z;
		}

		// Return the cross product of two vectors
		template<typename T>
		Vector3<T> Cross(const Vector3<T> &a, const Vector3<T> &b)
		{
			return Vector3<T>{	a.Y*b.Z - a.Z*b.Y,
								a.Z*b.X - a.X*b.Z,
								a.X*b.Y - a.Y*b.X
			};
		}

		// Return the square length of a vectore
		template<typename T>
		T Length2(const Vector3<T> &a)
		{
			return Dot(a, a);
		}

		// Return the length of a vector
		template<typename T>
		float Length(const Vector3<T> &a)
		{
			return sqrt(Length2(a));
		}

		// Alias the length function to return magnitude
		template<typename T> 
		constexpr auto Magnitude(const T& a) ->decltype(Length(a))
		{
			return Length(a);
		}
	}
}
