#pragma once

#include "Vector3.h"

namespace Pandora {
	namespace Math {

		// Generic 4 component Vector class.
		template<typename T>
		struct Vector4
		{
		public:
			Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

			template<typename S>
			Vector4<T>& operator*=(S s)
			{
				x *= s;
				y *= s;
				z *= s;
				w *= s;
				return (*this);
			}

			template<typename S>
			Vector4<T>& operator/=(S s)
			{
				x /= s;
				y /= s;
				z /= s;
				w /= s;
				return (*this);
			}

			Vector4<T>& operator+=(const Vector4<T> &o)
			{
				x += o.x;
				y += o.y;
				z += o.z;
				w += o.w;
				return (*this);
			}

			Vector4<T>& operator-=(const Vector4<T> &o)
			{
				x -= o.x;
				y -= o.y;
				z -= o.z;
				w -= o.w;
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

			Vector4<T>& operator/=(const Vector4<T> &o)
			{
				x /= o.x;
				y /= o.y;
				z /= o.z;
				w /= 0.w;
				return (*this);
			}

			T x;
			T y;
			T z;
			T w;
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

		// Equality operators
		template<typename T>
		bool operator==(const Vector4<T>& a, const Vector4<T>& b)
		{
			return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
		}

		// Multiply a vector by a scalar
		template<typename T, typename S>
		Vector4<T> operator*(const Vector4<T>& vec, S scale)
		{
			return Vector4<T>(vec.x * scale, vec.y * scale, vec.z * scale, vec.w * scale);
		}

		// Divide a vector by a scalar
		template<typename T, typename S>
		Vector4<T> operator/(const Vector4<T>& vec, S s)
		{
			return Vector4<T>(vec.x / s, vec.y / s, vec.z / s, vec.w / s);
		}

		// Multiply two vectors of the same type componentwise
		template<typename T>
		Vector4<T> operator*(const Vector4<T>& a, const Vector4<T> &b)
		{
			return Vector4<T>(a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w);
		}

		// Divide two vectors of the same type componentwise
		template<typename T>
		Vector4<T> operator/(const Vector4<T> &a, const Vector4<T> &b)
		{
			return Vector4<T>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
		}

		// Add two vectors of the same type componentwise
		template<typename T>
		Vector4<T> operator+(const Vector4<T> &a, const Vector4<T> &b)
		{
			return Vector4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
		}

		// Subtract two vectors of the same type componentwise
		template<typename T>
		Vector4<T> operator-(const Vector4<T> &a, const Vector4<T> &b)
		{
			return Vector4<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
		}
	}
}
