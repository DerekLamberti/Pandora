#pragma once


namespace Pandora
{
	namespace Math
	{
		// Generic 3 component Vector class.
		template<typename T>
		struct Vector3
		{
		public:
			Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

			template<typename S>
			Vector3<T>& operator*=(S s)
			{
				x *= s;
				y *= s;
				z *= s;
				return (*this);
			}

			template<typename S>
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

			Vector3<T>& operator-=(const Vector3<T> &o)
			{
				x -= o.x;
				y -= o.y;
				z -= 0.z;
				return (*this);
			}

			Vector3<T>& operator*=(const Vector3<T> &o)
			{
				x *= o.x;
				y *= o.y;
				z *= o.z;
				return (*this);
			}

			Vector3<T>& operator/=(const Vector3<T> &o)
			{
				x /= o.x;
				y /= o.y;
				z /= o.z;
				return (*this);
			}

			T x;
			T y;
			T z;
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

		// Equality operators
		template<typename T>
		bool operator==(const Vector3<T>& a, const Vector3<T>& b)
		{
			return a.x == b.x && a.y == b.y && a.z == b.z;
		}

		// Mutlitply a Vector by a scalar
		template<typename T, typename S>
		Vector3<T> operator*(const Vector3<T>& vec, S scale)
		{
			return Vector3<T>(vec.x * scale, vec.y * scale, vec.z * scale);
		}

		// Divide a Vector by a scalar
		template<typename T, typename S>
		Vector3<T> operator/(const Vector3<T>& vec, S scale)
		{
			return Vector3<T>(vec.x / scale, vec.y / scale, vec.z / scale);
		}

		// Multiply two vectors of the same type componentwise
		template<typename T>
		Vector3<T> operator*(const Vector3<T>& a, const Vector3<T>& b)
		{
			return Vector3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
		}

		// Divide two vectors of the same type componentwise
		template<typename T>
		Vector3<T> operator/(const Vector3<T>& a, const Vector3<T>& b)
		{
			return Vector3<T>(a.x / b.x, a.y / b.y, a.z / b.z);
		}

		// Add two vectors of the same type componentwise
		template<typename T>
		Vector3<T> operator+(const Vector3<T>& vecA, const Vector3<T>& vecB)
		{
			return Vector3<T>(vecA.x + vecB.x, vecA.y + vecB.y, vecA.z + vecB.z);
		}

		// Subtract two vectors of the same type componentwise
		template<typename T>
		Vector3<T> operator-(const Vector3<T>& vecA, const Vector3<T>& vecB)
		{
			return Vector3<T>(vecA.x - vecB.x, vecA.y - vecB.y, vecA.z - vecB.z);
		}

		// Return the dot product of two vector3
		template<typename T>
		T Dot(const Vector3<T>& a, const Vector3<T>& b)
		{
			return a.x*b.x + a.y*b.y + a.z*b.z;
		}

		// Return the cross product of two vectors
		template<typename T>
		Vector3<T> Cross(const Vector3<T> &a, const Vector3<T> &b)
		{
			return Vector3<T>(	a.y*b.z - a.z*b.y,
								a.z*b.x - a.x*b.z,
								a.x*b.y - a.y*b.x
				);
		}

		// Return the square length of a vector3
		template<typename T>
		T Length2(const Vector3<T> &a)
		{
			return Dot(a, a);
		}

		// Return the length of a vector3
		template<typename T>
		float Length(const Vector3<T> &a)
		{
			return sqrt(Length2(a));
		}

		// Alias the length function to return magnitude
		template<typename T>
		constexpr auto Magnitude(const Vector3<T>& a) ->decltype(Length(a))
		{
			return Length(a);
		}

		// Normaliza a vector3
		template<typename T>
		Vector3<T> Normalize(const Vector3<T>& a)
		{
			return a / Length(a);
		}

		// Compute the componentwise minimum of two vector3
		template<typename T>
		Vector3<T> Min(const Vector3<T> &a, const Vector3<T> &b)
		{
			return Vector3<T>(
				std::min(a.x, b.x),
				std::min(a.y, b.y),
				std::min(a.z, b.z));
		}

		// Compute the componentwise maximum of two vector4
		template<typename T>
		Vector3<T> Max(const Vector3<T> &a, const Vector3<T> &b)
		{
			return Vector3<T>(
				std::max(a.x, b.x),
				std::max(a.y, b.y),
				std::max(a.z, b.z));
		}

		// Returns the compoenent wise clamped values between min and max.
		template<typename T>
		Vector3<T> Clamp(const Vector3<T> &value, const Vector3<T> &min, const Vector3<T> &max)
		{
			return Min(max, Max(min, value));
		}

	}
}
