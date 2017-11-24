#pragma once

#include "../Base/Base.h"

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

		
		// Create a Vector of a particular type
		template<typename T>
		Vector3<T> Make_Vector(T x, T y, T z);

		template<typename T>
		Vector4<T> Make_Vector(T x, T y, T z, T w);

		template<typename T>
		Vector4<T> Make_Vector(const Vector3<T> &i, T w);

		
		// Stream Vector operator 
		template<typename T, typename StreamType>
		StreamType& operator<<(StreamType& stream, const Vector3<T> &obj);

		template<typename T, typename StreamType>
		StreamType& operator<<(StreamType& stream, const Vector4<T> &obj);

		
		// Equality operators
	//	template<typename T>
	//	bool operator==(const Vector3<T>& a, const Vector3<T>& b);

		template<typename T>
		bool operator==(const Vector4<T>& a, const Vector4<T>& b);

		
		// Mutlitply a Vector by a scalar
//		template<typename T, typename S>
//		Vector3<T> operator*(const Vector3<T>& vec, S s);

//		template<typename T, typename S>
//		Vector4<T> operator*(const Vector4<T>& vec, S s);

		// Divide a vector by a scalar
//		template<typename T, typename S>
//		Vector3<T> operator/(const Vector3<T> &a, S s);

		template<typename T, typename S>
		Vector4<T> operator/(const Vector4<T> &a, S s);
		

		// Multiply two vectors of the same type componentwise
		//template<typename T>
		//Vector3<T> operator*(const Vector3<T> &a, const Vector3<T> &b);

//		template<typename T>
//		Vector4<T> operator*(const Vector4<T> &a, const Vector4<T> &b);


		// Divide two vectors of the same type componentwise
		//template<typename T>
		//Vector3<T> operator/(const Vector3<T> &a, const Vector3<T> &b);

		template<typename T>
		Vector4<T> operator/(const Vector4<T> &a, const Vector4<T> &b);


		// Add two vectors using the + operator componentwise
//		template<typename T>
//		Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b);

		template<typename T>
		Vector4<T> operator+(const Vector4<T> &a, const Vector4<T> &b);

		// Add a swizzled vector by a Vector3 componentwise
//		template<typename T, typename A, typename B1, typename C>
//		Vector3<T> operator+(const Vector3<T>::template Swizzle<A, B1, C>& swizzled,
//			const Vector3<T>& other);

		// Subtract two vectors of the same type componentwise
//		template<typename T>
	//	Vector3<T> operator-(const Vector3<T> &a, const Vector3<T> &b);

		template<typename T>
		Vector4<T> operator-(const Vector4<T> &a, const Vector4<T> &b);


		// Return the dot product of two vector3
//		template<typename T> 
//		T Dot(const Vector3<T>& a, const Vector3<T>& b);
		

		// Return the cross product of two vector3
//		template<typename T>
//		Vector3<T> Cross(const Vector3<T> &a, const Vector3<T> &b);


		// Return the square length of a vector3
//		template<typename T>
	//	T Length2(const Vector3<T> &a);


		// Return the length of a vector3
//		template<typename T>
//		float Length(const Vector3<T> &a);


		// Alias the length function to return magnitude
//		template<typename T>
//		constexpr auto Magnitude(const Vector3<T>& a) ->decltype(Length(a));


		// Normaliza a vector3
//		template<typename T>
//		Vector3<T> Normalize(const Vector3<T>& a);


		// Compute the componentwise minimum of two vector3
//		template<typename T>
//		Vector3<T> Min(const Vector3<T> &a, const Vector3<T> &b);

		template<typename T>
		Vector4<T> Min(const Vector4<T> &a, const Vector4<T> &b);


		// Compute the componentwise maximum of two vector4
//		template<typename T>
//		Vector3<T> Max(const Vector3<T> &a, const Vector3<T> &b);

		template<typename T>
		Vector4<T> Max(const Vector4<T> &a, const Vector4<T> &b);


		// Returns the compoenent wise clamped values between min and max.
//		template<typename T>
//		Vector3<T> Clamp(const Vector3<T> &value, const Vector3<T> &min, const Vector3<T> &max);

		template<typename T>
		Vector4<T> Clamp(const Vector4<T> &value, const Vector4<T> &min, const Vector4<T> &max);

	}
}

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"