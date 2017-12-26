#pragma once

#include "SwizzleHelper.h"
#include "../Base/TypeHelpers.h"

namespace Pandora {
	namespace Math {



		template<typename T>
		struct Vector2 : public SwizzleHelper<T>
		{
			static_assert(!std::is_reference_v<T>, "Type T cannot be a reference for Vector2<T>");
			static_assert(!std::is_pointer_v<T>, "Type T cannot be pointer type for Vector2<T>");
			static_assert(std::is_arithmetic_v<T>, "Type T must be an arithmetic type for Vector2<T>");

			using ValueType = T;

		private:
#include "DefineSwizzleTypes.inl"
#include "DefineSwizzlesX.inl"
#include "DefineSwizzlesY.inl"

		public:
			union {
#include "DeclareSwizzlesX.inl"
#include "DeclareSwizzlesY.inl"

				struct
				{
					T x;
					T y;
				};

				T v[2];
			};



			Vector2(T ix, T iy)
				: x(ix), y(iy)
			{}

			Vector2(const Vector2& other)
				: Vector2(other.x, other.y)
			{}

//			template<	typename VecT,
//						typename = std::enable_if_t<IsVec2V<VecT>>
//			>
//			Vector2(const VecT& other)
//				: Vector2(other.x, other.y)
//			{}

			const Vector2& operator()() const
			{
				return (*this);
			}

			Vector2& operator=(const Vector2& other)
			{
				x = other.x;
				y = other.y;
				return (*this);
			}

//			template<typename U> 
//			operator Vector2<U>() const
//			{
//				return Make_Vector(static_cast<U>(x), static_cast<U>(y));
//			}

			template<	typename U, typename ... Args, template<typename, typename...> class Vec2T,
						typename = std::enable_if_t<AllVector2<Vec2T<U, Args...>>>
			>
			Vector2<T>& operator+=(const Vec2T<U, Args...> &o)
			{
				if constexpr ( IsSameAnyV< Vec2T<U, Args...>, Vector2<T>, XY, YY > )
				{
					x += o.x;
					y += o.y;
				}
				else if constexpr ( IsSameAnyV< Vec2T<U, Args...>, XX> )
				{
					y += o.y;
					x += o.x;
				}
				else if constexpr ( IsSameAnyV< Vec2T<U, Args...>, YX> )
				{
					auto oy = o.y;
					x += o.x;
					y += oy;
				}
				else
				{
					static_assert(false, "Non optimised path.");
					// fallback to explicit copy
					Vector2<T> other = o;
					x += other.x;
					y += other.y;
				}
				return (*this);
			}

			template<	typename U, typename ... Args, template<typename, typename...> class Vec2T,
						typename = std::enable_if_t<AllVector2<Vec2T<U, Args...>>>
			>
			Vector2<T>& operator-=(const Vec2T<U, Args...> &o)
			{
				Vector2<T> other = o;
				x -= other.x;
				y -= other.y;
				return (*this);
			}

			template<	typename S,
						typename= std::enable_if_t<std::is_arithmetic_v<S>>
			>
			Vector2<T>& operator*=(S s)
			{
				x *= s;
				y *= s;
				return (*this);
			}

			template<	typename U, typename ... Args, template<typename, typename...> class Vec2T,
						typename = std::enable_if_t<AllVector2<Vec2T<U, Args...>>>
			>
			Vector2<T>& operator*=(const Vec2T<U, Args...> &o)
			{
				Vector2<T> other = o;
				x *= other.x;
				y *= other.y;
				return (*this);
			}

			template<	typename S,
						typename = std::enable_if_t<std::is_arithmetic_v<S>>
			>
			Vector2<T>& operator /=(S s)
			{
				x /= s;
				y /= s;
				return (*this);
			}

			template<	typename U, typename ... Args, template<typename, typename...> class Vec2T,
						typename = std::enable_if_t<AllVector2<Vec2T<U, Args...>>>
			>
				Vector2<T>& operator/=(const Vec2T<U, Args...> &o)
			{
				Vector2<T> other = o;
				x /= other.x;
				y /= other.y;
				return (*this);
			}
		};

		template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
		Vector2<T> Make_Vector(T x, T y)
		{
			return Vector2<T>(x, y);
		}

//		template<typename T, typename U>
//		Vector2<T> vector_cast(Vector2<U> &other)
//		{
//			static_assert(!std::is_reference_v<T>, "Type T cannot be reference type for Vector2<T>.");
//			return Vector2<T>(static_cast<T>(other.x), static_cast<T>(other.y));
//		}

		// Stream operator Vector2
		template<typename VecT, typename StreamType>
		std::enable_if_t<IsVec2V<VecT>, StreamType&>
			operator<<(StreamType& stream, const VecT &obj)
		{
			stream << obj.x << obj.y;
			return stream;
		}
		
		template<typename VecT1, typename VecT2>
		std::enable_if_t<AllVector2<VecT1, VecT2>, bool>
			operator==(const VecT1& a, const VecT2& b)
		{
			return a.x == b.x && a.y == b.y;
		}

		template<typename VecT1, typename VecT2>
		std::enable_if_t<AllVector2<VecT1, VecT2>, bool>
			operator!=(const VecT1& a, const VecT2& b)
		{
			return !(a==b);
		}

		//	template<typename Vec3T1, typename Vec3T2,
//		typename = std::enable_if_t<AllVector2<Vec3T1, Vec3T2>>>
//		bool operator==(const Vec3T1& a, const Vec3T2& b)
//	{
//		return a.x == b.x && a.y == b.y;
//	}
//

		template<typename Vec2T1, typename Vec2T2,
				typename = std::enable_if_t<AllVector2<Vec2T1, Vec2T2>>
		>	
		auto operator+(const Vec2T1 &a, const Vec2T2 &b)
			->Vector2<decltype(a.x+b.x)>
		{
			return Make_Vector(a.x + b.x, a.y + b.y);
		}

		template<typename Vec2T1, typename Vec2T2,
			typename = std::enable_if_t<AllVector2<Vec2T1, Vec2T2>>
		>
		auto operator-(const Vec2T1 &a, const Vec2T2 &b)
			->Vector2<decltype(a.x - b.x)>
		{
			return Make_Vector(a.x - b.x, a.y - b.y);
		}

		template<	typename T, typename ... Args1, template<typename, typename...> class Vec2T1,
					typename S,
					typename = std::enable_if_t<IsVec2V<Vec2T1<T, Args1...>> &&
												std::is_arithmetic_v<S>>
		>
		auto operator*(const Vec2T1<T, Args1...> &a, const S &s)
			-> Vector2<decltype(a.x * s)>
		{
			return Make_Vector(a.x * s, a.y * s);
		}

		template<	typename T, typename ... Args1, template<typename, typename...> class Vec2T1, 
					typename U, typename ... Args2, template<typename, typename...> class Vec2T2,
					typename = std::enable_if_t<AllVector2<Vec2T1<T, Args1...>, Vec2T2<U, Args2...>>>
		>
		auto operator*(const Vec2T1<T, Args1...> &a, const Vec2T2<U, Args2...> &b)
			-> Vector2<decltype(a.x * b.x)>
		{
			return Make_Vector(a.x * b.x, a.y * b.y);
		}

//		template<	typename T,  template<typename, typename...> class Vec2T,
//					typename S,
//					typename ... Args1,
//					typename = std::enable_if_t<IsVec2V<Vec2T<T, Args1...>> && 
//												std::is_arithmetic_v<S>>
//		>
//		auto operator/(const Vec2T<T, Args1...> &a, S s)
//			-> Vector2<decltype(std::declval<T>() / std::declval<S>())>
//		{
//			return Make_Vector(a.x / s, a.y / s);
//		}

		template<	typename T, typename ... Args, template<typename, typename...> class Vec2T,
					typename S,
					typename = std::enable_if_t<IsVec2V<Vec2T<T, Args...>> && 
												std::is_arithmetic_v<S>>
		>
		auto operator/(const Vec2T<T, Args...> &a, S s)
			-> Vector2<decltype(std::declval<T>() / std::declval<S>())>
		{
			return Make_Vector(a.x / s, a.y / s);
		}

		template<	typename T, typename ... Args1, template<typename, typename...> class Vec2T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec2T2,
					typename = std::enable_if_t<AllVector2<Vec2T1<T, Args1...>, Vec2T2<U, Args2...>>>
		>
		auto operator/(const Vec2T1<T, Args1...> &a, const Vec2T2<U, Args2...> &b)
			-> Vector2<decltype(std::declval<T>() * std::declval<U>())>
		{
			return Make_Vector(a.x / b.x, a.y / b.y);
		}


		template<	typename T, typename ... Args1, template<typename, typename...> class Vec2T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec2T2,
					typename = std::enable_if_t<AllVector2<Vec2T1<T, Args1...>, Vec2T2<U, Args2...>>>
		>
		auto Dot(const Vec2T1<T, Args1...> &a, const Vec2T2<U, Args2...> &b)
			-> decltype(a.x * b.x)
		{
			return a.x*b.x + a.y*b.y;
		}


		template<	typename T, typename ... Args1, template<typename, typename...> class Vec2T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec2T2,
					typename = std::enable_if_t<AllVector2<Vec2T1<T, Args1...>, Vec2T2<U, Args2...>>>
		>
		auto Min(const Vec2T1<T, Args1...> &a, const Vec2T2<U, Args2...> &b)
			->Vector2<RemoveCVRefT<T>>
		{
			static_assert(std::is_same_v<T, U>, "Cannot find minimum between Vector2 with different value types. Return type is ambiguous.");
			return Make_Vector(	std::min(a.x, b.x), 
								std::min(a.y, b.y));
		}

		template<	typename T, typename ... Args1, template<typename, typename...> class Vec2T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec2T2,
					typename = std::enable_if_t<AllVector2<Vec2T1<T, Args1...>, Vec2T2<U, Args2...>>>
		>
		auto Max(const Vec2T1<T, Args1...> &a, const Vec2T2<U, Args2...> &b)
			->Vector2<RemoveCVRefT<T>>
		{
			static_assert(std::is_same_v<T, U>, "Cannot find maximum between Vector2 with different value types. Return type is ambiguous.");
			return Make_Vector( std::max(a.x, b.x),
								std::max(a.y, b.y));
		}

		template<	typename T, typename ... Args1, template<typename, typename...> class Vec2T1,
					typename U, typename ... Args2, template<typename, typename...> class Vec2T2,
					typename V, typename ... Args3, template<typename, typename...> class Vec2T3,
					typename = std::enable_if_t<AllVector2<Vec2T1<T, Args1...>, Vec2T2<U, Args2...>, Vec2T3<V, Args3...>>>
		>
		auto Clamp(const Vec2T1<T, Args1...> &val, const Vec2T2<U, Args2...> &min, const Vec2T3<V, Args3...> &max)
			->Vector2<RemoveCVRefT<T>>
		{
			static_assert(std::is_same_v<T, U> && std::is_same_v<T,V>, 
				"Cannot clamp between Vector2 with different value types. Return type is ambiguous.");

			return Min(max, Max(min, val));
		}

	};
};