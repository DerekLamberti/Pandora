#pragma once

#include "SwizzleHelper.h"

namespace Pandora {
	namespace Math {

		template<typename T>
		struct Vector2 : public SwizzleHelper<T>
		{
			using typename SwizzleHelper<T>::UXY;
			using typename SwizzleHelper<T>::SX;
			using typename SwizzleHelper<T>::SY;

			template<int N>
			using Offset = typename SwizzleHelper<T>:: template Offset<N>;

			Vector2(T ix, T iy)
				: x(ix), y(iy)
			{}

			Vector2(const Vector2& other)
				: Vector2(other.x, other.y)
			{}

		private:
#include "DefineSwizzle2.inl"

		public:
			union {
#include "DeclareSwizzle2.inl"
				struct
				{
					T x;
					T y;
				};

				T v[2];
			};
		};

		template<typename T>
		Vector2<T> Make_Vector(T x, T y)
		{
			return Vector2<T>(x, y);
		}
	};
};