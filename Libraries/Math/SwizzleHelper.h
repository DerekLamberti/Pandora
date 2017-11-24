#pragma once
namespace Pandora {
	namespace Math {

		struct NULL0 {};
		struct NULL1 {};
		struct NULL2 {};

		template<typename T>
		struct SwizzleHelper
		{

			template<int Size>
			struct Offset
			{
				T _padding[Size];
			};

			struct UXY
			{
				union {
					T x;
					T y;
				};
			};
			struct UXZ {
				union {
					T x;
					T z;
				};
			};

			struct UYZ {
				union {
					T y;
					T z;
				};
			};

			struct UYZW
			{
				union {
					T y;
					T z;
					T w;
				};
			};
			struct UXZW {
				union {
					T x;
					T z;
					T w;
				};
			};
			struct UXYW
			{
				union {
					T x;
					T y;
					T w;
				};
			};

			struct UXYZ
			{
				union {
					T x;
					T y;
					T z;
				};
			};

			struct UXYZW
			{
				union {
					T x;
					T y;
					T z;
					T w;
				};
			};

			struct SX
			{
				T x;
			};
			struct SY
			{
				T y;
			};
			struct SZ
			{
				T z;
			};
			struct SXY {
				T x;
				T y;
			};
			struct SYZ {
				T y;
				T z;
			};
			struct SXZ {
				T x;
				T z;
			};
			struct SXYZ {
				T x;
				T y;
				T z;
			};
			struct SXYZW
			{
				T x;
				T y;
				T z;
				T w;
			};
		};

		template<typename T>
		struct Vector2;

		template<typename T>
		struct Vector3;

		template<typename T>
		struct Vector4;

		template<typename T, typename A, typename B = NULL0, typename C = NULL1>
		struct Swizzle2T : public A, public B, public C
		{
			using ValueType = T;

			Swizzle2T() = delete;
			Swizzle2T(const Swizzle2T& other) = delete;
			Swizzle2T(Swizzle2T&& other) = delete;
			Swizzle2T& operator=(const Swizzle2T& other) = delete;
			Swizzle2T& operator=(const Vector2<T>& other) = delete;

			T GetX() { this->x; };
			operator Vector2<T>() const { return Vector2<T>(
				Swizzle2T::x, 
				Swizzle2T::y); }
		};

		template<typename T, typename A, typename B = NULL0, typename C = NULL1>
		struct Swizzle3T : public A, public B, public C
		{
			using ValueType = T;

			Swizzle3T() = delete;
			Swizzle3T(const Swizzle3T& other) = delete;
			Swizzle3T(Swizzle3T&& other) = delete;
			Swizzle3T& operator=(const Swizzle3T& other) = delete;
			Swizzle3T& operator=(const Vector3<T>& other) = delete;

			operator Vector3<T>() const { return Vector3<T>(
				Swizzle3T::x, 
				Swizzle3T::y, 
				Swizzle3T::z); }
		};

		template<typename T, typename A, typename B = NULL0, typename C = NULL1, typename D = NULL2>
		struct Swizzle4T : public A, public B, public C, public D
		{
			using ValueType = T;

			Swizzle4T() = delete;
			Swizzle4T(const Swizzle4T& other) = delete;
			Swizzle4T(Swizzle4T&& other) = delete;
			Swizzle4T& operator=(const Swizzle4T& other) = delete;
			Swizzle4T& operator=(const Vector4<T>& other) = delete;

			operator Vector4<T>() const { return Vector4<T>(
				Swizzle4T::x, 
				Swizzle4T::y, 
				Swizzle4T::z, 
				Swizzle4T::w); }
		};

	}
}