#pragma once
#include <type_traits>

namespace Pandora {
	namespace Math {

		// Forward declare vector types.
		template<typename T>
		struct Vector2;

		template<typename T>
		struct Vector3;

		template<typename T>
		struct Vector4;

		template<typename T, typename = bool>
		struct HasX
			: public std::false_type {};

		template<typename T>
		struct HasX<T, decltype(std::declval<T>().x, bool())>
			: std::true_type {};


		template<typename T, typename = bool>
		struct HasY 
			: public std::false_type {};

		template<typename T>
		struct HasY<T, decltype(std::declval<T>().y, bool())> 
			: std::true_type {};


		template<typename T, typename = bool>
		struct HasZ
			: public std::false_type {};

		template<typename T>
		struct HasZ<T, decltype(std::declval<T>().z, bool())>
			: std::true_type {};


		template<typename T, typename = bool>
		struct HasW
			: public std::false_type {};

		template<typename T>
		struct HasW<T, decltype(std::declval<T>().w, bool())>
			: std::true_type {};


		template<typename T, typename = bool>
		struct IsVec2
			: public std::false_type {};

		template<typename T>
		struct IsVec2<T, std::enable_if_t <
			HasX<T>::value &&
			HasY<T>::value &&
			!HasZ<T>::value &&
			!HasW<T>::value &&
			std::is_convertible_v<T, Vector2<typename T::ValueType>>
			, bool>>
			: public std::true_type {};

		template<typename T>
		static constexpr bool IsVec2V = IsVec2<T>::value;


		template<typename T, typename = bool>
		struct IsVec3 : public std::false_type {};

		template<typename T>
		struct IsVec3<T, std::enable_if_t<	
			HasX<T>::value &&
			HasY<T>::value &&
			HasZ<T>::value &&
			!HasW<T>::value &&
			std::is_convertible_v<T, Vector3<typename T::ValueType>>
			, bool>>
			: public std::true_type {};

		template<typename T>
		static constexpr bool IsVec3V = IsVec3<T>::value;


		template<typename T, typename = bool>
		struct IsVec4 : public std::false_type {};

		template<typename T>
		struct IsVec4<T, std::enable_if_t<
			HasX<T>::value &&
			HasY<T>::value &&
			HasZ<T>::value &&
			HasW<T>::value &&
			std::is_convertible_v<T, Vector4<typename T::ValueType>>
			, bool>>
			: public std::true_type {};

		template<typename T>
		static constexpr bool IsVec4V = IsVec4<T>::value;


		template<typename T, typename = bool>
		struct IsAnyVecType : public std::false_type {};

		template<typename T>
		struct IsAnyVecType<T, std::enable_if_t<IsVec2V<T> || 
												IsVec3V<T> || 
												IsVec4V<T>, 
			bool>>	: public std::true_type {};

		template<typename T>
		static constexpr bool IsAnyVecTypeV = IsAnyVecType<T>::value;

		template<typename T, typename...Ts>
		constexpr bool AllVector2Func()
		{
			if constexpr (sizeof...(Ts) > 0)
			{
				return AllVector2Func<Ts...>() && IsVec2V<T>;
			}
			else
			{
				return IsVec2V<T>;
			}
		}

		template<typename ... Ts>
		constexpr bool AllVector2 = AllVector2Func<Ts...>();

		template<typename T, typename...Ts>
		constexpr bool AllVector3Func()
		{
			if constexpr (sizeof...(Ts) > 0)
			{
				return AllVector3Func<Ts...>() && IsVec3V<T>;
			}
			else
			{
				return IsVec3V<T>;
			}
		}

		template<typename ...Ts>
		constexpr bool AllVector3 = AllVector3Func<Ts...>();


		template<typename T, typename...Ts>
		constexpr bool AllVector4Func()
		{
			if constexpr (sizeof...(Ts) > 0)
			{
				return AllVector4Func<Ts...>() && IsVec4V<T>;
			}
			else
			{
				return IsVec4V<T>;
			}
		}

		template<typename ...Ts>
		constexpr bool AllVector4 = AllVector4Func<Ts...>();

		struct SwizzleCommon {
			template<typename S>
			SwizzleCommon& operator/=(const S &s) const
			{
				static_assert(false, "Cannot call operator /= on swizzle. All swizzles are constant and not modifiable.");
			}
		};

		// SwizzleBase struct. Allows for specifying up to 4 base classes but overloaded to
		// ensure that when fewer are provided, the size in bytes is kept to minimum.
		template<typename T, typename A, typename B, typename C, typename D>
		struct SwizzleBase : public A, public B, public C, public D, public SwizzleCommon
		{};

		template<typename T, typename A, typename B, typename C>
		struct SwizzleBase<T, A, B, C, void> : public A, public B, public C, public SwizzleCommon
		{};

		template<typename T, typename A, typename B>
		struct SwizzleBase<T, A, B, void, void> : public A, public B, public SwizzleCommon
		{};

		template<typename T, typename A>
		struct SwizzleBase<T, A, void, void, void> : public A, public SwizzleCommon
		{};

		// Main helper class
		template<typename T>
		struct SwizzleHelper
		{
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

			struct UXW {
				union {
					T x;
					T w;
				};
			};

			struct UYW {
				union {
					T y;
					T w;
				};
			};

			struct UYZ {
				union {
					T y;
					T z;
				};
			};

			struct UZW {
				union {
					T z;
					T w;
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
			struct SW
			{
				T w;
			};
			struct P1 
			{
				T _Padding1;
			};
			struct P2
			{
				T _Padding2;
			};
			struct P3
			{
				T _Padding3;
			};
		}; //Struct SwizzleHelper


		template<typename T, typename A, typename B, typename C, typename D>
		struct Swizzle2T : public SwizzleBase<T, A, B, C, D>
		{

			using ValueType = T;


			Swizzle2T(const Swizzle2T& other)
			{
				static_assert(false,
					"Cannot copy construct swizzled type. Use operator() to explicitly convert swizzled type to Vector2 type.");
			}

			Swizzle2T() = delete;
			Swizzle2T(Swizzle2T&& other) = delete;
			Swizzle2T& operator=(const Swizzle2T& other) = delete;
			const Swizzle2T& operator=(const Vector2<T>& other) = delete;

			operator Vector2<T>() const {
				return Vector2<T>(
					SwizzleBase::x,
					SwizzleBase::y);
			}

			Vector2<T> operator()() const {
				return static_cast<Vector2<T>>(*this);
			}
		};


		template<typename T, typename A, typename B, typename C, typename D>
		struct Swizzle3T : SwizzleBase<T, A, B, C, D>
		{
			using ValueType = T;

			Swizzle3T(const Swizzle3T& other)
			{
				static_assert(false,
					"Cannot copy construct swizzled type. Use operator() to explicitly convert swizzled type to Vector3 type.");
			}


			Swizzle3T() = delete;
			Swizzle3T(Swizzle3T&& other) = delete;
			Swizzle3T& operator=(const Swizzle3T& other) = delete;
			Swizzle3T& operator=(const Vector3<T>& other) = delete;

			operator Vector3<T>() const { return Vector3<T>(
				Swizzle3T::x, 
				Swizzle3T::y, 
				Swizzle3T::z); }

			Vector3<T> operator()() const {
				return static_cast<Vector3<T>>(*this);
			}
		};

		template<typename T, typename A, typename B, typename C, typename D>
		struct Swizzle4T : public SwizzleBase<T, A, B, C, D>
		{
			using ValueType = T;

			Swizzle4T(const Swizzle4T& other)
			{
				static_assert(false,
					"Cannot copy construct swizzled type. Use operator() to explcitly convert swizzled type to Vector4 type.");
			}

			Swizzle4T() = delete;
			Swizzle4T(Swizzle4T&& other) = delete;
			Swizzle4T& operator=(const Swizzle4T& other) = delete;
			Swizzle4T& operator=(const Vector4<T>& other) = delete;

			operator Vector4<T>() const { return Vector4<T>(
				Swizzle4T::x, 
				Swizzle4T::y, 
				Swizzle4T::z, 
				Swizzle4T::w); }

			Vector4<T> operator()() const
			{
				return static_cast<Vector4<T>>(*this);
			}
		};
	}
}