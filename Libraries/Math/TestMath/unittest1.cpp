#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Math.h"
#include "../SwizzleHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			// Enable any vector type to work with the unit test framework
			template <typename Q, typename ... Args, template<typename, typename...> class Vec> 
			static std::wstring
				ToString(const Vec<Q, Args...> &t) { RETURN_WIDE_STRING(t);  }
		}
	}
}

namespace TestMath
{		
	using namespace Pandora;
	using namespace Pandora::Math;

#define TEST_V2(vec, ex, ey) \
	Assert::AreEqual(ex, vec.x, L"Failed when comparing " #vec " X component."); \
	Assert::AreEqual(ey, vec.y, L"Failed when comparing " #vec " Y component.");

#define TEST_V3(vec, ex, ey, ez) \
	Assert::AreEqual(ex, vec.x, L"Failed when comparing " #vec " X component."); \
	Assert::AreEqual(ey, vec.y, L"Failed when comparing " #vec " Y component."); \
	Assert::AreEqual(ez, vec.z, L"Failed when comparing " #vec " Z component.");

#define TEST_V4(vec, ex, ey, ez, ew) \
	Assert::AreEqual(ex, vec.x, L"Failed when comparing " #vec " X component."); \
	Assert::AreEqual(ey, vec.y, L"Failed when comparing " #vec " Y component."); \
	Assert::AreEqual(ez, vec.z, L"Failed when comparing " #vec " Z component."); \
	Assert::AreEqual(ew, vec.w, L"Failed when comparing " #vec " W component.");


#define TEST_SELF_OP_2(init, op, ex, ey) \
	{\
		auto var = init; \
		var op var; \
		Assert::AreEqual(ex, var.x, L"Operator " #op " failed on X."); \
		Assert::AreEqual(ey, var.y, L"Operator " #op " failed on Y."); \
	}

#define TEST_SELF_OP_3(init, op, ex, ey, ez) \
	{\
		auto var = init; \
		var op var; \
		Assert::AreEqual(ex, var.x, L"Operator " #op " failed on X."); \
		Assert::AreEqual(ey, var.y, L"Operator " #op " failed on Y."); \
		Assert::AreEqual(ez, var.z, L"Operator " #op " failed on Z."); \
	}

#define TEST_SELF_OP_4(init, op, ex, ey, ez, ew) \
	{\
		auto var = init; \
		var op var; \
		Assert::AreEqual(ex, var.x, L"Operator " #op " failed on X."); \
		Assert::AreEqual(ey, var.y, L"Operator " #op " failed on Y."); \
		Assert::AreEqual(ez, var.z, L"Operator " #op " failed on Z."); \
		Assert::AreEqual(ew, var.w, L"Operator " #op " failed on W."); \
	}


#define TEST_SELF_OP_SWIZZLE_2(init, op, swizzle, ex, ey) \
	{\
		auto var = init; \
		var op var.swizzle; \
		Assert::AreEqual(ex, var.x, L"Operator " #op " " #swizzle " failed on X."); \
		Assert::AreEqual(ey, var.y, L"Operator " #op " " #swizzle " failed on Y."); \
	}

#define TEST_SELF_OP_SWIZZLE_3(init, op, swizzle, ex, ey, ez) \
	{\
		auto var = init; \
		var op var.swizzle; \
		Assert::AreEqual(ex, var.x, L"Operator " #op " " #swizzle " failed on X."); \
		Assert::AreEqual(ey, var.y, L"Operator " #op " " #swizzle " failed on Y."); \
		Assert::AreEqual(ez, var.z, L"Operator " #op " " #swizzle " failed on Z."); \
	}


#define TEST_SELF_OP_SWIZZLE_4(init, op, swizzle, ex, ey, ez, ew) \
	{ \
		auto varA = init; \
		varA op varA.swizzle; \
		Assert::AreEqual(ex, varA.x, L"Operator " #op " " #swizzle " failed on X."); \
		Assert::AreEqual(ey, varA.y, L"Operator " #op " " #swizzle " failed on Y."); \
		Assert::AreEqual(ez, varA.z, L"Operator " #op " " #swizzle " failed on Z."); \
		Assert::AreEqual(ew, varA.w, L"Operator " #op " " #swizzle " failed on W."); \
	}

#define TEST_SWIZZLE_OP_SWIZZLE_2(init1, swizzle1, op, init2, swizzle2, ex, ey) \
	{ \
		auto var = init1.swizzle1 op init2.swizzle2; \
		Assert::AreEqual(ex, var.x, L"" #init1#swizzle1 " " #op " " #init2#swizzle2 " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1#swizzle1 " " #op " " #init2#swizzle2 " failed on Y."); \
	}

#define TEST_SWIZZLE_OP_SWIZZLE_3(init1, swizzle1, op, init2, swizzle2, ex, ey, ez) \
	{ \
		auto var = init1.swizzle1 op init2.swizzle2; \
		Assert::AreEqual(ex, var.x, L"" #init1#swizzle1 " " #op " " #init2#swizzle2 " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1#swizzle1 " " #op " " #init2#swizzle2 " failed on Y."); \
		Assert::AreEqual(ez, var.z, L"" #init1#swizzle1 " " #op " " #init2#swizzle2 " failed on Z."); \
	}

#define TEST_SWIZZLE_OP_SWIZZLE_4(init1, swizzle1, op, init2, swizzle2, ex, ey, ez, ew) \
	{ \
		auto var = init1.swizzle1 op init2.swizzle2; \
		Assert::AreEqual(ex, var.x, L"" #init1#swizzle1 " " #op " " #init2#swizzle2 " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1#swizzle1 " " #op " " #init2#swizzle2 " failed on Y."); \
		Assert::AreEqual(ez, var.z, L"" #init1#swizzle1 " " #op " " #init2#swizzle2 " failed on Z."); \
		Assert::AreEqual(ew, var.w, L"" #init1#swizzle1 " " #op " " #init2#swizzle2 " failed on W."); \
	}

#define TEST_A_OP_SWIZZLE_2(init1, op, init2, swizzle, ex, ey) \
	{ \
		auto var = init1 op init2.swizzle; \
		Assert::AreEqual(ex, var.x, L"" #init1 " " #op " " #init2#swizzle " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1 " " #op " " #init2#swizzle " failed on Y."); \
	}

#define TEST_A_OP_SWIZZLE_3(init1, op, init2, swizzle, ex, ey, ez) \
	{ \
		auto var = init1 op init2.swizzle; \
		Assert::AreEqual(ex, var.x, L"" #init1 " " #op " " #init2#swizzle " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1 " " #op " " #init2#swizzle " failed on Y."); \
		Assert::AreEqual(ez, var.z, L"" #init1 " " #op " " #init2#swizzle " failed on Z."); \
	}

#define TEST_A_OP_SWIZZLE_4(init1, op, init2, swizzle, ex, ey, ez, ew) \
	{ \
		auto var = init1 op init2.swizzle; \
		Assert::AreEqual(ex, var.x, L"" #init1 " " #op " " #init2#swizzle " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1 " " #op " " #init2#swizzle " failed on Y."); \
		Assert::AreEqual(ez, var.z, L"" #init1 " " #op " " #init2#swizzle " failed on Z."); \
		Assert::AreEqual(ew, var.w, L"" #init1 " " #op " " #init2#swizzle " failed on W."); \
	}


#define TEST_SWIZZLE_OP_B_2(init1, swizzle, op, init2, ex, ey) \
	{ \
		auto var = init1.swizzle op init2; \
		Assert::AreEqual(ex, var.x, L"" #init1#swizzle " " #op " " #init2 " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1#swizzle " " #op " " #init2 " failed on Y."); \
	}

#define TEST_SWIZZLE_OP_B_3(init1, swizzle, op, init2, ex, ey, ez) \
	{ \
		auto var = init1.swizzle op init2; \
		Assert::AreEqual(ex, var.x, L"" #init1#swizzle " " #op " " #init2 " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1#swizzle " " #op " " #init2 " failed on Y."); \
		Assert::AreEqual(ez, var.z, L"" #init1#swizzle " " #op " " #init2 " failed on Z."); \
	}

#define TEST_SWIZZLE_OP_B_4(init1, swizzle, op, init2, ex, ey, ez, ew) \
	{ \
		auto var = init1.swizzle op init2; \
		Assert::AreEqual(ex, var.x, L"" #init1#swizzle " " #op " " #init2 " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1#swizzle " " #op " " #init2 " failed on Y."); \
		Assert::AreEqual(ez, var.z, L"" #init1#swizzle " " #op " " #init2 " failed on Z."); \
		Assert::AreEqual(ew, var.w, L"" #init1#swizzle " " #op " " #init2 " failed on W."); \
	}


#define TEST_A_OP_B_2(init1, op, init2, ex, ey) \
	{ \
		auto var = init1 op init2; \
		Assert::AreEqual(ex, var.x, L"" #init1 " " #op " " #init2 " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1 " " #op " " #init2 " failed on Y."); \
	}

#define TEST_A_OP_B_3(init1, op, init2, ex, ey, ez) \
	{ \
		auto var = init1 op init2; \
		Assert::AreEqual(ex, var.x, L"" #init1 " " #op " " #init2 " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1 " " #op " " #init2 " failed on Y."); \
		Assert::AreEqual(ez, var.z, L"" #init1 " " #op " " #init2 " failed on Z."); \
	}

#define TEST_A_OP_B_4(init1, op, init2, ex, ey, ez, ew) \
	{ \
		auto var = init1 op init2; \
		Assert::AreEqual(ex, var.x, L"" #init1 " " #op " " #init2 " failed on X."); \
		Assert::AreEqual(ey, var.y, L"" #init1 " " #op " " #init2 " failed on Y."); \
		Assert::AreEqual(ez, var.z, L"" #init1 " " #op " " #init2 " failed on Z."); \
		Assert::AreEqual(ew, var.w, L"" #init1 " " #op " " #init2 " failed on W."); \
	}


#define TEST_SWIZZLE_2(in, ex, ey, swizzle) \
			auto swizzle = in.swizzle(); \
			Assert::AreEqual(ex, swizzle.x, L"Failed to compare X for " #swizzle); \
			Assert::AreEqual(ey, swizzle.y, L"Failed to compare Y for " #swizzle); \

#define TEST_SWIZZLE_3(in, ex, ey, ez, swizzle) \
			auto swizzle = in.swizzle(); \
			Assert::AreEqual(ex, swizzle.x, L"Failed to compare X for " #swizzle); \
			Assert::AreEqual(ey, swizzle.y, L"Failed to compare Y for " #swizzle); \
			Assert::AreEqual(ez, swizzle.z, L"Failed to compare Z for " #swizzle); \

#define TEST_SWIZZLE_4(in, ex, ey,ez,ew, swizzle) \
			auto swizzle = in.swizzle(); \
			Assert::AreEqual(ex, swizzle.x, L"Failed to compare X for " #swizzle); \
			Assert::AreEqual(ey, swizzle.y, L"Failed to compare Y for " #swizzle); \
			Assert::AreEqual(ez, swizzle.z, L"Failed to compare Z for " #swizzle); \
			Assert::AreEqual(ew, swizzle.w, L"Failed to compare W for " #swizzle);

	TEST_CLASS(Vector2Type)
	{
		TEST_METHOD(Vector2Construction)
		{
			auto a = Make_Vector(2, 3);
			TEST_V2(a, 2, 3);

			auto b = std::make_unique<Vector2<int>>(2, 3);
			Assert::AreEqual(a, *b, L"a is expected to match  b.");

			Vector2<int32> c = Vector2<int>(a);
			Assert::AreEqual(a, c, L"Copy construction didn't match.");
		}

		TEST_METHOD(Vector2SizeOf)
		{
			Assert::AreEqual((size_t)2, sizeof(Vector2<int8>));
			Assert::AreEqual((size_t)4, sizeof(Vector2<int16>));
			Assert::AreEqual((size_t)8, sizeof(Vector2<int32>));

			Vector2<int8> a(1, 2);
			Assert::AreEqual((size_t)2, sizeof(a.xy));
		}

		TEST_METHOD(Vector2Equality)
		{
			auto a = Make_Vector(2, 3);

			Assert::IsTrue(a == a, L"Vector2 != Vector2");
			Assert::IsTrue(a.xy == a, L"Swizzle2 != Vector2");
			Assert::IsTrue(a == a.xy, L"Vector2 != Swizzle2");
			Assert::IsTrue(a.xy == a.xy, L"Swizzle2 != Swizzle2");

			auto b = Make_Vector(2, 3, 7);
			Assert::IsTrue(a != b.xx, L"Vector2 != Swizzle2");
			Assert::IsTrue(a.xxx != b, L"Swizzle2 != Vector3");
			Assert::IsTrue(a.xx != b.yy, L"Swizzle2 == Swizzle2");

			Assert::AreEqual(a.xy, a.xy, L"Stream operator");
		}

		TEST_METHOD(Vector2AddVector)
		{
			auto a = Make_Vector(2, 4);
			auto b = Make_Vector(6, 5);
			auto c = Make_Vector(7, 8);
			auto d = Make_Vector(3, 9);

			TEST_SELF_OP_2(a, +=, 4, 8);
			TEST_SELF_OP_SWIZZLE_2(a, +=, xx, 4, 6);
			TEST_SELF_OP_SWIZZLE_2(b, +=, xy, 12, 10);
			TEST_SELF_OP_SWIZZLE_2(c, +=, yx, 15, 15);
			TEST_SELF_OP_SWIZZLE_2(d, +=, yy, 12, 18);

			TEST_A_OP_B_2(a, +, b, 8, 9);
			TEST_A_OP_SWIZZLE_2(a, +, b, yx, 7, 10);
			TEST_SWIZZLE_OP_B_2(b, yx, +, a, 7, 10);
			TEST_SWIZZLE_OP_SWIZZLE_2(a, xy, +, b, yx, 7, 10);

			// test mixing types
			auto e = Make_Vector(2.f, 3.f);
			auto f = a + e;
			Assert::AreEqual(4.f, f.x, L"float x not matching.");
			Assert::AreEqual(7.f, f.y, L"float y not matching.");

			// test return type deduction
			auto g = e + a;
			Assert::IsTrue(std::is_same_v<float, decltype(g.x)>, L"Deduced type expected float.");

			//test commutativity
			Assert::AreEqual(f, g, L"f should match g.");
		}

		TEST_METHOD(Vector2SubVector)
		{
			auto a = Make_Vector(2, 4);
			auto b = Make_Vector(6, 5);

			TEST_SELF_OP_2(a, -=, 0, 0);
			TEST_SELF_OP_SWIZZLE_2(a, -=, xx, 0, 2);
			TEST_SELF_OP_SWIZZLE_2(a, -=, xy, 0, 0);
			TEST_SELF_OP_SWIZZLE_2(a, -=, yx, -2, 2);
			TEST_SELF_OP_SWIZZLE_2(a, -=, yy, -2, 0);

			TEST_A_OP_B_2(a, -, b, -4, -1);
			TEST_A_OP_SWIZZLE_2(a, -, b, xy, -4, -1);
			TEST_SWIZZLE_OP_B_2(a, xy, -, b, -4, -1);
			TEST_SWIZZLE_OP_SWIZZLE_2(a, xy, -, b, xy, -4, -1);
		}

		TEST_METHOD(Vector2MulVector)
		{
			auto a = Make_Vector(2, 4);
			auto b = Make_Vector(6, 5);

			TEST_SELF_OP_2(a, *=, 4, 16);
			TEST_SELF_OP_SWIZZLE_2(a, *=, xx, 4, 8);
			TEST_SELF_OP_SWIZZLE_2(a, *=, xy, 4, 16);
			TEST_SELF_OP_SWIZZLE_2(a, *=, yx, 8, 8);
			TEST_SELF_OP_SWIZZLE_2(a, *=, yy, 8, 16);

			TEST_A_OP_B_2(a, *, b, 12, 20);
			TEST_A_OP_SWIZZLE_2(a, *, b, xy, 12, 20);
			TEST_SWIZZLE_OP_B_2(a, xy, *, b, 12, 20);
			TEST_SWIZZLE_OP_SWIZZLE_2(a, xy, *, b, xy, 12, 20);

			//test commutativity
			auto c = a * b;
			auto d = b * a;
			Assert::AreEqual(c, d, L"c is expected to match d.");
		}

		TEST_METHOD(Vector2MulScalar)
		{
			auto a = Make_Vector(2, 3);
			auto b = a * 5;
			TEST_V2(b, 10, 15);

			auto c = a;
			c *= 5;
			TEST_V2(c, 10, 15);
		}

		TEST_METHOD(Vector2DivVector)
		{
			auto a = Make_Vector(12, 15);
			auto b = Make_Vector(4, 3);

			TEST_SELF_OP_2(a, /=, 1, 1);
			TEST_SELF_OP_SWIZZLE_2(a, /=, xx, 1, 1);
			TEST_SELF_OP_SWIZZLE_2(a, /=, xy, 1, 1);
			TEST_SELF_OP_SWIZZLE_2(a, /=, yx, 0, 1);
			TEST_SELF_OP_SWIZZLE_2(a, /=, yy, 0, 1);

			TEST_A_OP_B_2(a, /, b, 3, 5);
			TEST_A_OP_SWIZZLE_2(a, /, b, xy, 3, 5);
			TEST_SWIZZLE_OP_B_2(a, xy, /, b, 3, 5);
			TEST_SWIZZLE_OP_SWIZZLE_2(a, xy, /, b, xy, 3, 5);
		}

		TEST_METHOD(Vector2DivScalar)
		{
			auto a = Make_Vector(12, 15);
			auto b = a / 3;
			TEST_V2(b, 4, 5);

			auto c = a;
			c /= 3;
			TEST_V2(c, 4, 5);

			auto d = a;
			d = d.xy / 3;
			TEST_V2(d, 4, 5);
		}

		TEST_METHOD(Vector2Dot)
		{
			auto a = Make_Vector(0, 1);
			auto b = Make_Vector(1, 0);
			auto c = Make_Vector(1, 1);
			auto d = Make_Vector(-1, 1);
			auto e = Make_Vector(-1, -1);

			Assert::AreEqual(0, Dot(a, b), L"Perpendicular (a,b) should be zero");
			Assert::AreEqual(0, Dot(d, e), L"Perpendicular (d,e) should be zero");
			Assert::AreEqual(1, Dot(a, a), L"Same direction should be > 0 (or 1 in this case)");
			Assert::AreEqual(-2, Dot(c, e), L"Opposite direction should be < 0 (or -2 this case");

			Assert::AreEqual(0, Dot(a.xy, b), L"Perpendicular (a.xy,b) should be zero");
			Assert::AreEqual(0, Dot(d, e.xy), L"Perpendicular (d,e.xy) should be zero");
			Assert::AreEqual(1, Dot(a.xy, a.xy), L"Same direction swizzled should be > 0 (or 1 in this case)");
			Assert::AreEqual(-2, Dot(c.xy, e.xy), L"Opposite direction swizzled should be < 0 (or -2 this case");
		}

		TEST_METHOD(Vector2Length)
		{
			auto x = Make_Vector(2, 0);
			auto y = Make_Vector(0, 2);

			auto lx = Length(x);
			auto ly = Length(y.xy);

			Assert::IsTrue(lx == ly, L"Lengths not equal");
			Assert::AreEqual(2.0, lx, L"lx.xy expected to be 2");
		}

		TEST_METHOD(Vector2Normalize)
		{
			Vec2f vec = Make_Vector(23.0f, 43.0f);

			auto normal = Normalize(vec);
			float nLen = Length(normal);

			Assert::AreEqual(1.0f, nLen, 0.0001f, L"Test vector normalization.");

			auto normXY = Normalize(vec.xy);

			Assert::AreEqual(normal, normXY, L"Normalized vectors don't match");
		}

		TEST_METHOD(Vector2Min)
		{
			auto a = Make_Vector(4, 6);
			auto b = Make_Vector(7, 5);

			auto c = Min(a, b);
			TEST_V2(c, 4, 5);

			auto d = Min(a, a.yx);
			TEST_V2(d, 4, 4);

			auto e = Min(a.yx, a);
			TEST_V2(e, 4, 4);
		}

		TEST_METHOD(Vector2Max)
		{
			auto a = Make_Vector(4, 6);
			auto b = Make_Vector(7, 5);

			auto c = Max(a, b);
			TEST_V2(c, 7, 6);

			auto d = Max(a, a.yx);
			TEST_V2(d, 6, 6);

			auto e = Max(a.yx, a);
			TEST_V2(e, 6, 6);
		}
		
		TEST_METHOD(Vector2Clamp)
		{
			auto min = Make_Vector(2, 4);
			auto max = Make_Vector(8, 9);

			auto a = Make_Vector(20, 20);
			auto b = Make_Vector(2,1);

			auto c = Make_Vector(5, 6);

			{
				auto maxClamp = Clamp(a, min, max);
				auto minClamp = Clamp(b, min, max);
				auto mixClamp = Clamp(c, min, max);

				TEST_V2(maxClamp, 8, 9);
				TEST_V2(minClamp, 2, 4);
				TEST_V2(mixClamp, 5, 6);
			}

			// test calling with various swizzles
			{
				auto maxClamp = Clamp(a.xy, min, max);
				TEST_V2(maxClamp, 8, 9);

				auto minClamp = Clamp(b, min.xy, max);
				TEST_V2(minClamp, 2, 4);

				auto mixClamp = Clamp(c, min, max.xy);
				TEST_V2(mixClamp, 5, 6);
			}

		}

		TEST_METHOD(Vector2Assignment)
		{
			Vector2<int32> a = Make_Vector(2, 3);

			auto b = a.xy();
			Vector2<int32> c = a.xy;
			Assert::AreEqual(true, std::is_same<decltype(b), decltype(c)>::value);

			Assert::AreEqual(b, c);
		}

		TEST_METHOD(Vector2Cast)
		{
			Vector2<int32> a = Make_Vector(2, 3);
			Vector2<float> b = vector_cast<float>(a);
			TEST_V2(b, 2.0f, 3.0f);

			auto c = vector_cast<float>(a.xy);
			Assert::IsTrue( std::is_same_v<decltype(c), decltype(b)>, L"Cast_Vector<float>() produced an unexpected type.");
		}
	};

	TEST_CLASS(VectorTypeHelpers)
	{
		TEST_METHOD(AllVectorX)
		{
			auto a = Make_Vector(5, 6);
			auto b = Make_Vector(4.f, 3.f);

			static_assert(AllVector2<decltype(a), decltype(b)>, "Could not verify Vector2 with differnet value types.");

			static_assert(AllVector2<decltype(a)>, "Cannot convert Vector2 type to Vector2.");
			static_assert(AllVector2<decltype(a.xy)>, "Cannot convert swizzle type to Vector2.");
			static_assert(!AllVector3<decltype(a)>, "Thinks vec2 is vec3");
			static_assert(!AllVector4<decltype(a)>, "Thinks vec2 is vec4");
		}

		TEST_METHOD(HasMember$)
		{
			static_assert(HasX<Vector2<int>>::value, "Could not deduce member x");
			static_assert(HasX<Vector3<int>>::value, "Could not deduce member x");
			static_assert(HasX<Vector4<int>>::value, "Could not deduce member x");

			static_assert(HasY<Vector2<int>>::value, "Could not deduce member y");
			static_assert(HasY<Vector3<int>>::value, "Could not deduce member y");
			static_assert(HasY<Vector4<int>>::value, "Could not deduce member y");

			static_assert(!HasZ<Vector2<int>>::value, "Could deduce member z");
			static_assert(HasZ<Vector3<int>>::value, "Could not deduce member z");
			static_assert(HasZ<Vector4<int>>::value, "Could not deduce member z");

			static_assert(!HasW<Vector2<int>>::value, "Could deduce member w");
			static_assert(!HasW<Vector3<int>>::value, "Could deduce member w");
			static_assert(HasW<Vector4<int>>::value, "Could not deduce member w");
		}

		TEST_METHOD(IsVec$)
		{
			static_assert(IsVec2<Vector2<int>>::value);
			static_assert(IsVec3<Vector3<int>>::value);
			static_assert(IsVec4<Vector4<int>>::value);

			Vector4<int> v4 = Make_Vector(2, 3, 4, 5);
			static_assert(IsVec2<decltype(v4.xx)>::value);
			static_assert(IsVec3<decltype(v4.xxx)>::value);
			static_assert(IsVec4<decltype(v4.xxxx)>::value);

			static_assert(!IsVec2<Vector3<int>>::value);
			static_assert(!IsVec2<Vector4<int>>::value);

			static_assert(!IsVec3<Vector2<int>>::value);
			static_assert(!IsVec3<Vector4<int>>::value);

			static_assert(!IsVec4<Vector2<int>>::value);
			static_assert(!IsVec4<Vector3<int>>::value);
		}
	};

	TEST_CLASS(Vector2Swizzle)
	{
		TEST_METHOD(Vector2Swizzle$$)
		{
			Vector2<int32> a = Make_Vector(2, 3);

			TEST_SWIZZLE_2(a, 2, 2, xx);
			TEST_SWIZZLE_2(a, 2, 3, xy);
			TEST_SWIZZLE_2(a, 3, 2, yx);
			TEST_SWIZZLE_2(a, 3, 3, yy);
		}

		TEST_METHOD(Vector2Swizzle$$$)
		{
			auto a = Make_Vector(2, 3);
			TEST_SWIZZLE_3(a, 2, 2, 2, xxx);
			TEST_SWIZZLE_3(a, 2, 2, 3, xxy);
			TEST_SWIZZLE_3(a, 2, 3, 2, xyx);
			TEST_SWIZZLE_3(a, 2, 3, 3, xyy);

			TEST_SWIZZLE_3(a, 3, 2, 2, yxx);
			TEST_SWIZZLE_3(a, 3, 2, 3, yxy);
			TEST_SWIZZLE_3(a, 3, 3, 2, yyx);
			TEST_SWIZZLE_3(a, 3, 3, 3, yyy);
		}


		TEST_METHOD(Vector2Swizzle$$$$)
		{
			auto a = Make_Vector(2, 3);
			TEST_SWIZZLE_4(a, 2, 2, 2, 2, xxxx);
			TEST_SWIZZLE_4(a, 2, 2, 2, 3, xxxy);
			TEST_SWIZZLE_4(a, 2, 2, 3, 2, xxyx);
			TEST_SWIZZLE_4(a, 2, 2, 3, 3, xxyy);
			TEST_SWIZZLE_4(a, 2, 3, 2, 2, xyxx);
			TEST_SWIZZLE_4(a, 2, 3, 2, 3, xyxy);
			TEST_SWIZZLE_4(a, 2, 3, 3, 2, xyyx);
			TEST_SWIZZLE_4(a, 2, 3, 3, 3, xyyy);

			TEST_SWIZZLE_4(a, 3, 2, 2, 2, yxxx);
			TEST_SWIZZLE_4(a, 3, 2, 2, 3, yxxy);
			TEST_SWIZZLE_4(a, 3, 2, 3, 2, yxyx);
			TEST_SWIZZLE_4(a, 3, 2, 3, 3, yxyy);
			TEST_SWIZZLE_4(a, 3, 3, 2, 2, yyxx);
			TEST_SWIZZLE_4(a, 3, 3, 2, 3, yyxy);
			TEST_SWIZZLE_4(a, 3, 3, 3, 2, yyyx);
			TEST_SWIZZLE_4(a, 3, 3, 3, 3, yyyy);
		}
	};

	TEST_CLASS(Vector3Type)
	{
	public:
		
		TEST_METHOD(Vector3Construction)
		{
			Vector3<float32> vector = Make_Vector(1.0f, 2.0f, 3.0f);
			TEST_V3(vector, 1.0f, 2.0f, 3.0f);

			Vec3f vec3f = Make_Vector(4.4f, 5.5f, 6.6f);
			TEST_V3(vec3f, 4.4f, 5.5f, 6.6f);

			auto ptr = std::make_unique<Vector3<int32>>(3, 4, 5);
			TEST_V3((*ptr), 3, 4, 5);

			Vec3f copy(vec3f);
			Assert::AreEqual(vec3f, copy, L"Test vector copy construction.");
		}

		TEST_METHOD(Vector3SizeOf)
		{
			Assert::AreEqual((size_t)3, sizeof(Vector3<uint8>));
			Assert::AreEqual((size_t)6, sizeof(Vector3<float16>));
			Assert::AreEqual((size_t)12, sizeof(Vector3<float32>));
		}

		TEST_METHOD(Vector3Equality)
		{
			auto a = Make_Vector(2, 3, 4);

			Assert::IsTrue(a == a, L"Vector3 != Vector3");
			Assert::IsTrue(a.xyz == a, L"Swizzle3 != Vector3");
			Assert::IsTrue(a == a.xyz, L"Vector3 != Swizzle3");
			Assert::IsTrue(a.xyz == a.xyz, L"Swizzle3 != Swizzle3");

			auto b = Make_Vector(2, 3, 7, 8);
			Assert::IsTrue(a != b.xxx, L"Vector3 == Vector4");

		}

		TEST_METHOD(Vector3MulScalar)
		{
			Vec3f a = Make_Vector(1.0f, 2.0f, 3.0f);
			Vec3f b = a * 3.0f;
			TEST_V3(b, 3.0f, 6.0f, 9.0f);

			auto c = a.xyz * 3.0f;
			TEST_V3(c, 3.0f, 6.0f, 9.0f);
		}

		TEST_METHOD(Vector3AddVector)
		{
			Vec3f a = Make_Vector(2.0f, 3.0f, 4.0f);
			TEST_SELF_OP_3(a, +=, 4.f, 6.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, xxx, 4.f, 5.f, 6.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, xxy, 4.f, 5.f, 7.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, xxz, 4.f, 5.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, xyx, 4.f, 6.f, 6.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, xyy, 4.f, 6.f, 7.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, xyz, 4.f, 6.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, xzx, 4.f, 7.f, 6.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, xzy, 4.f, 7.f, 7.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, xzz, 4.f, 7.f, 8.f);

			TEST_SELF_OP_SWIZZLE_3(a, +=, yxx, 5.f, 5.f, 6.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, yxy, 5.f, 5.f, 7.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, yxz, 5.f, 5.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, yyx, 5.f, 6.f, 6.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, yyy, 5.f, 6.f, 7.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, yyz, 5.f, 6.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, yzx, 5.f, 7.f, 6.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, yzy, 5.f, 7.f, 7.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, yzz, 5.f, 7.f, 8.f);

			TEST_SELF_OP_SWIZZLE_3(a, +=, zxx, 6.f, 5.f, 6.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, zxy, 6.f, 5.f, 7.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, zxz, 6.f, 5.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, zyx, 6.f, 6.f, 6.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, zyy, 6.f, 6.f, 7.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, zyz, 6.f, 6.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, zzx, 6.f, 7.f, 6.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, zzy, 6.f, 7.f, 7.f);
			TEST_SELF_OP_SWIZZLE_3(a, +=, zzz, 6.f, 7.f, 8.f);

			auto b = Make_Vector(6, 7, 9);
			TEST_A_OP_B_3(a, +, b, 8.f, 10.f, 13.f);
			TEST_A_OP_SWIZZLE_3(a, +, b, xyz, 8.f, 10.f, 13.f);
			TEST_SWIZZLE_OP_B_3(a, xyz, +, b, 8.f, 10.f, 13.f);
			TEST_SWIZZLE_OP_SWIZZLE_3(a, xyz, +, b, xyz, 8.f, 10.f, 13.f);

			auto c = a + b;
			auto d = b + a;
			Assert::AreEqual(c, d, L"c expected to match d");
		}

		TEST_METHOD(Vector3SubVector)
		{
			auto a = Make_Vector(2, 4, 7);
			TEST_SELF_OP_3(a, -=, 0, 0, 0);
			TEST_SELF_OP_SWIZZLE_3(a, -=, xxx, 0, 2, 5);
			TEST_SELF_OP_SWIZZLE_3(a, -=, xxy, 0, 2, 3);
			TEST_SELF_OP_SWIZZLE_3(a, -=, xxz, 0, 2, 0);
			TEST_SELF_OP_SWIZZLE_3(a, -=, xyx, 0, 0, 5);
			TEST_SELF_OP_SWIZZLE_3(a, -=, xyy, 0, 0, 3);
			TEST_SELF_OP_SWIZZLE_3(a, -=, xyz, 0, 0, 0);
			TEST_SELF_OP_SWIZZLE_3(a, -=, xzx, 0, -3, 5);
			TEST_SELF_OP_SWIZZLE_3(a, -=, xzy, 0, -3, 3);
			TEST_SELF_OP_SWIZZLE_3(a, -=, xzz, 0, -3, 0);

			TEST_SELF_OP_SWIZZLE_3(a, -=, yxx, -2, 2, 5);
			TEST_SELF_OP_SWIZZLE_3(a, -=, yxy, -2, 2, 3);
			TEST_SELF_OP_SWIZZLE_3(a, -=, yxz, -2, 2, 0);
			TEST_SELF_OP_SWIZZLE_3(a, -=, yyx, -2, 0, 5);
			TEST_SELF_OP_SWIZZLE_3(a, -=, yyy, -2, 0, 3);
			TEST_SELF_OP_SWIZZLE_3(a, -=, yyz, -2, 0, 0);
			TEST_SELF_OP_SWIZZLE_3(a, -=, yzx, -2, -3, 5);
			TEST_SELF_OP_SWIZZLE_3(a, -=, yzy, -2, -3, 3);
			TEST_SELF_OP_SWIZZLE_3(a, -=, yzz, -2, -3, 0);

			TEST_SELF_OP_SWIZZLE_3(a, -=, zxx, -5, 2, 5);
			TEST_SELF_OP_SWIZZLE_3(a, -=, zxy, -5, 2, 3);
			TEST_SELF_OP_SWIZZLE_3(a, -=, zxz, -5, 2, 0);
			TEST_SELF_OP_SWIZZLE_3(a, -=, zyx, -5, 0, 5);
			TEST_SELF_OP_SWIZZLE_3(a, -=, zyy, -5, 0, 3);
			TEST_SELF_OP_SWIZZLE_3(a, -=, zyz, -5, 0, 0);
			TEST_SELF_OP_SWIZZLE_3(a, -=, zzx, -5, -3, 5);
			TEST_SELF_OP_SWIZZLE_3(a, -=, zzy, -5, -3, 3);
			TEST_SELF_OP_SWIZZLE_3(a, -=, zzz, -5, -3, 0);

			auto b = Make_Vector(6, 5, 9);
			TEST_A_OP_B_3(a, -, b, -4, -1, -2);
			TEST_A_OP_SWIZZLE_3(a, -, b, xyz, -4, -1, -2);
			TEST_SWIZZLE_OP_B_3(a, xyz, -, b, -4, -1, -2);
			TEST_SWIZZLE_OP_SWIZZLE_3(a, xyz, -, b, xyz, -4, -1, -2);
		}

		TEST_METHOD(Vector3MulVector)
		{
			Vec3f a = Make_Vector(2.0f, 3.0f, 4.0f);
			TEST_SELF_OP_3(a, *=, 4.f, 9.f, 16.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, xxx, 4.f, 6.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, xxy, 4.f, 6.f, 12.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, xxz, 4.f, 6.f, 16.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, xyx, 4.f, 9.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, xyy, 4.f, 9.f, 12.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, xyz, 4.f, 9.f, 16.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, xzx, 4.f, 12.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, xzy, 4.f, 12.f, 12.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, xzz, 4.f, 12.f, 16.f);

			TEST_SELF_OP_SWIZZLE_3(a, *=, yxx, 6.f, 6.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, yxy, 6.f, 6.f, 12.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, yxz, 6.f, 6.f, 16.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, yyx, 6.f, 9.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, yyy, 6.f, 9.f, 12.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, yyz, 6.f, 9.f, 16.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, yzx, 6.f, 12.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, yzy, 6.f, 12.f, 12.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, yzz, 6.f, 12.f, 16.f);

			TEST_SELF_OP_SWIZZLE_3(a, *=, zxx, 8.f, 6.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, zxy, 8.f, 6.f, 12.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, zxz, 8.f, 6.f, 16.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, zyx, 8.f, 9.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, zyy, 8.f, 9.f, 12.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, zyz, 8.f, 9.f, 16.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, zzx, 8.f, 12.f, 8.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, zzy, 8.f, 12.f, 12.f);
			TEST_SELF_OP_SWIZZLE_3(a, *=, zzz, 8.f, 12.f, 16.f);

			Vec3f b = Make_Vector(8.0f, 9.0f, 10.0f);
			TEST_A_OP_B_3(a, *, b, 16.f, 27.f, 40.f);
			TEST_A_OP_B_3(b, *, a, 16.f, 27.f, 40.f);
			TEST_A_OP_SWIZZLE_3(a, *, b, xyz, 16.f, 27.f, 40.f);
			TEST_SWIZZLE_OP_B_3(a, xyz, *, b, 16.f, 27.f, 40.f);
			TEST_SWIZZLE_OP_SWIZZLE_3(a, xyz, *, b, xyz, 16.f, 27.f, 40.f);
		}

		TEST_METHOD(Vector3DivScalar)
		{
			auto a = Make_Vector(12, 15, 18);
			auto b = a / 3;
			auto c = a;

			TEST_V3(b, 4, 5, 6);

			a /= 3;
			TEST_V3(a, 4, 5, 6);

			c = c.xyz / 3;
			TEST_V3(c, 4, 5, 6);
		}

		TEST_METHOD(Vector3DivVector)
		{
			auto a = Make_Vector(1.f, 2.f, 4.f);

			TEST_SELF_OP_3(a, /=, 1.f, 1.f, 1.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, xxx, 1.f, 2.f, 4.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, xxy, 1.f, 2.f, 2.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, xxz, 1.f, 2.f, 1.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, xyx, 1.f, 1.f, 4.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, xyy, 1.f, 1.f, 2.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, xyz, 1.f, 1.f, 1.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, xzx, 1.f, .5f, 4.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, xzy, 1.f, .5f, 2.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, xzz, 1.f, .5f, 1.f);

			TEST_SELF_OP_SWIZZLE_3(a, /=, yxx, .5f, 2.f, 4.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, yxy, .5f, 2.f, 2.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, yxz, .5f, 2.f, 1.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, yyx, .5f, 1.f, 4.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, yyy, .5f, 1.f, 2.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, yyz, .5f, 1.f, 1.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, yzx, .5f, .5f, 4.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, yzy, .5f, .5f, 2.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, yzz, .5f, .5f, 1.f);

			TEST_SELF_OP_SWIZZLE_3(a, /=, zxx, .25f, 2.f, 4.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, zxy, .25f, 2.f, 2.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, zxz, .25f, 2.f, 1.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, zyx, .25f, 1.f, 4.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, zyy, .25f, 1.f, 2.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, zyz, .25f, 1.f, 1.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, zzx, .25f, .5f, 4.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, zzy, .25f, .5f, 2.f);
			TEST_SELF_OP_SWIZZLE_3(a, /=, zzz, .25f, .5f, 1.f);

			auto b = Make_Vector(2.f, 1.f, 0.5f);
			TEST_A_OP_B_3(a, /, b, .5f, 2.f, 8.f);
			TEST_A_OP_B_3(b, /, a, 2.f, .5f, .125f);
			TEST_A_OP_SWIZZLE_3(a, /, b, xyz, .5f, 2.f, 8.f);
			TEST_SWIZZLE_OP_B_3(a, xyz, /, b, .5f, 2.f, 8.f);
			TEST_SWIZZLE_OP_SWIZZLE_3(a, xyz, /, b, xyz, .5f, 2.f, 8.f);
		}

		TEST_METHOD(Vector3Dot)
		{
			Vec3f a = Make_Vector(1.0f, 2.0f, 3.0f);
			Vec3f b = Make_Vector(4.0f, 6.0f, 8.0f);
			float dpAB = Dot(a, b);
			Assert::AreEqual(40.0f, dpAB, L"Test dot product between two vectors.");

			float dpBA = Dot(b, a);
			Assert::AreEqual(dpBA, dpAB, L"Test vector dot product commutative.");

			float af = Dot(a.xyz, b);
			float bf = Dot(a, b.xyz);
			float cf = Dot(a.xyz, b.xyz);
			Assert::AreEqual(dpAB, af, L"af is expected to match dpAB");
			Assert::AreEqual(dpAB, bf, L"bf is expected to match dpAB");
			Assert::AreEqual(dpAB, cf, L"cf is expected to match dpAB");
		}

		TEST_METHOD(Vector3Cross)
		{
			Vec3f a = Make_Vector(1.0f, 2.0f, 3.0f);
			Vec3f b = Make_Vector(4.0f, 6.0f, 8.0f);

			Vec3f cpAB = Cross(a, b);
			TEST_V3(cpAB, 16.0f - 18.0f, 12.0f - 8.0f, 6.0f - 8.0f);

			Vec3f cpBA = Cross(b, a);
			TEST_V3(cpBA, 18.0f - 16.0f, 8.0f - 12.0f, 8.0f - 6.0f);

			auto sAB = Cross(a.xyz, b);
			Assert::AreEqual(cpAB, sAB, L"sAB expected to match cpAB");
			auto AsB = Cross(a, b.xyz);
			Assert::AreEqual(cpAB, AsB, L"AsB expected to match cpAB");
			auto sAsB = Cross(a.xyz, b.xyz);
			Assert::AreEqual(cpAB, sAsB, L"sAsB expected to match cpAB");
		}

		TEST_METHOD(Vector3Length)
		{
			Vec3f a = Make_Vector(3.0f, 0.0f, 0.0f);

			float length2A = Length2(a);
			Assert::AreEqual(9.0f, length2A, L"Test the vector length squared function.");

			float length = Length(a);
			Assert::AreEqual(3.0f, length, L"Test the vector length.");

			float mag = Magnitude(a);
			Assert::AreEqual(length, mag, L"Test the magnitude of a vector.");

			float l2a = Length2(a.xyz);
			Assert::AreEqual(length2A, l2a, L"l2A is expected to match length2A");
		}

		TEST_METHOD(Vector3Normalize)
		{
			Vec3f vec = Make_Vector(23.0f, 43.0f, 14.0f);

			auto normal = Normalize(vec);
			float nLen = Length(normal);

			Assert::AreEqual(1.0f, nLen, 0.0001f, L"Test vector normalization.");

			auto n2 = Normalize(vec.xyz);
			Assert::AreEqual(normal, n2, L"n2 is expected to match normal.");
		}

		TEST_METHOD(Vector3Min)
		{
			auto a = Make_Vector(4, 5, 6);
			auto b = Make_Vector(6, 5, 4);
			auto c = Min(a, b);
			TEST_V3(c, 4, 5, 4);

			auto d = Min(a.xyz, b);
			TEST_V3(d, 4, 5, 4);

			auto e = Min(a, b.xyz);
			TEST_V3(e, 4, 5, 4);

			auto f = Min(a.xyz, b.xyz);
			TEST_V3(f, 4, 5, 4);
		}

		TEST_METHOD(Vector3Max)
		{
			auto a = Make_Vector(4, 5, 6);
			auto b = Make_Vector(6, 5, 4);
			auto c = Max(a, b);
			TEST_V3(c, 6, 5, 6);

			auto d = Max(a.xyz, b);
			TEST_V3(d, 6, 5, 6);

			auto e = Max(a, b.xyz);
			TEST_V3(e, 6, 5, 6);

			auto f = Max(a.xyz, b.xyz);
			TEST_V3(f, 6, 5, 6);
		}

		TEST_METHOD(Vector3Clamp)
		{
			auto a = Make_Vector(3, 5, 7);
			auto b = Make_Vector(4, 4, 4);
			auto c = Make_Vector(6, 6, 6);

			auto d = Clamp(a, b, c);
			TEST_V3(d, 4, 5, 6);

			auto e = Clamp(a.xyz, b, c);
			TEST_V3(e, 4, 5, 6);

			auto f = Clamp(a, b.xyz, c);
			TEST_V3(f, 4, 5, 6);

			auto g = Clamp(a, b, c.xyz);
			TEST_V3(g, 4, 5, 6);
		}

		TEST_METHOD(Vector3Assignment)
		{
			Vector3<int32> a = Make_Vector(2, 3, 4);

			auto b = a.xyz();
			Vector3<int32> c = a.xyz;
			Assert::AreEqual(true, std::is_same<decltype(b), decltype(c)>::value);

			Assert::AreEqual(b, c);
		}

		TEST_METHOD(Vector3Cast)
		{
			Vector3<int32> a = Make_Vector(2, 3, 4);
			Vector3<float> b = vector_cast<float>(a);
			TEST_V3(b, 2.0f, 3.0f, 4.0f);

			auto c = vector_cast<float>(a);
			Assert::IsTrue(std::is_same_v<decltype(c), decltype(b)>, L"vector_cast<float>() produced an unexpected type.");
		}
	};

	TEST_CLASS(Vector3Swizzle)
	{
		TEST_METHOD(Vector3Swizzle$$)
		{
			Vector3<int32> a = Make_Vector(2, 3, 4);

			TEST_SWIZZLE_2(a, 2, 2, xx);
			TEST_SWIZZLE_2(a, 2, 3, xy);
			TEST_SWIZZLE_2(a, 2, 4, xz);

			TEST_SWIZZLE_2(a, 3, 2, yx);
			TEST_SWIZZLE_2(a, 3, 3, yy);
			TEST_SWIZZLE_2(a, 3, 4, yz);

			TEST_SWIZZLE_2(a, 4, 2, zx);
			TEST_SWIZZLE_2(a, 4, 3, zy);
			TEST_SWIZZLE_2(a, 4, 4, zz);
		}

		TEST_METHOD(Vector3Swizzle$$$)
		{
			auto a = Make_Vector(2, 3, 4);
			TEST_SWIZZLE_3(a, 2, 2, 2, xxx);
			TEST_SWIZZLE_3(a, 2, 2, 3, xxy);
			TEST_SWIZZLE_3(a, 2, 2, 4, xxz);
			TEST_SWIZZLE_3(a, 2, 3, 2, xyx);
			TEST_SWIZZLE_3(a, 2, 3, 3, xyy);
			TEST_SWIZZLE_3(a, 2, 3, 4, xyz);
			TEST_SWIZZLE_3(a, 2, 4, 2, xzx);
			TEST_SWIZZLE_3(a, 2, 4, 3, xzy);
			TEST_SWIZZLE_3(a, 2, 4, 4, xzz);

			TEST_SWIZZLE_3(a, 3, 2, 2, yxx);
			TEST_SWIZZLE_3(a, 3, 2, 3, yxy);
			TEST_SWIZZLE_3(a, 3, 2, 4, yxz);
			TEST_SWIZZLE_3(a, 3, 3, 2, yyx);
			TEST_SWIZZLE_3(a, 3, 3, 3, yyy);
			TEST_SWIZZLE_3(a, 3, 3, 4, yyz);
			TEST_SWIZZLE_3(a, 3, 4, 2, yzx);
			TEST_SWIZZLE_3(a, 3, 4, 3, yzy);
			TEST_SWIZZLE_3(a, 3, 4, 4, yzz);

			TEST_SWIZZLE_3(a, 4, 2, 2, zxx);
			TEST_SWIZZLE_3(a, 4, 2, 3, zxy);
			TEST_SWIZZLE_3(a, 4, 2, 4, zxz);
			TEST_SWIZZLE_3(a, 4, 3, 2, zyx);
			TEST_SWIZZLE_3(a, 4, 3, 3, zyy);
			TEST_SWIZZLE_3(a, 4, 3, 4, zyz);
			TEST_SWIZZLE_3(a, 4, 4, 2, zzx);
			TEST_SWIZZLE_3(a, 4, 4, 3, zzy);
			TEST_SWIZZLE_3(a, 4, 4, 4, zzz);
		}


		TEST_METHOD(Vector3Swizzle$$$$)
		{
			auto a = Make_Vector(2, 3, 4);

			TEST_SWIZZLE_4(a, 2, 2, 2, 2, xxxx);
			TEST_SWIZZLE_4(a, 2, 2, 2, 3, xxxy);
			TEST_SWIZZLE_4(a, 2, 2, 2, 4, xxxz);
			TEST_SWIZZLE_4(a, 2, 2, 3, 2, xxyx);
			TEST_SWIZZLE_4(a, 2, 2, 3, 3, xxyy);
			TEST_SWIZZLE_4(a, 2, 2, 3, 4, xxyz);
			TEST_SWIZZLE_4(a, 2, 2, 4, 2, xxzx);
			TEST_SWIZZLE_4(a, 2, 2, 4, 3, xxzy);
			TEST_SWIZZLE_4(a, 2, 2, 4, 4, xxzz);
			TEST_SWIZZLE_4(a, 2, 3, 2, 2, xyxx);
			TEST_SWIZZLE_4(a, 2, 3, 2, 3, xyxy);
			TEST_SWIZZLE_4(a, 2, 3, 2, 4, xyxz);
			TEST_SWIZZLE_4(a, 2, 3, 3, 2, xyyx);
			TEST_SWIZZLE_4(a, 2, 3, 3, 3, xyyy);
			TEST_SWIZZLE_4(a, 2, 3, 3, 4, xyyz);
			TEST_SWIZZLE_4(a, 2, 3, 4, 2, xyzx);
			TEST_SWIZZLE_4(a, 2, 3, 4, 3, xyzy);
			TEST_SWIZZLE_4(a, 2, 3, 4, 4, xyzz);
			TEST_SWIZZLE_4(a, 2, 4, 2, 2, xzxx);
			TEST_SWIZZLE_4(a, 2, 4, 2, 3, xzxy);
			TEST_SWIZZLE_4(a, 2, 4, 2, 4, xzxz);
			TEST_SWIZZLE_4(a, 2, 4, 3, 2, xzyx);
			TEST_SWIZZLE_4(a, 2, 4, 3, 3, xzyy);
			TEST_SWIZZLE_4(a, 2, 4, 3, 4, xzyz);
			TEST_SWIZZLE_4(a, 2, 4, 4, 2, xzzx);
			TEST_SWIZZLE_4(a, 2, 4, 4, 3, xzzy);
			TEST_SWIZZLE_4(a, 2, 4, 4, 4, xzzz);

			TEST_SWIZZLE_4(a, 3, 2, 2, 2, yxxx);
			TEST_SWIZZLE_4(a, 3, 2, 2, 3, yxxy);
			TEST_SWIZZLE_4(a, 3, 2, 2, 4, yxxz);
			TEST_SWIZZLE_4(a, 3, 2, 3, 2, yxyx);
			TEST_SWIZZLE_4(a, 3, 2, 3, 3, yxyy);
			TEST_SWIZZLE_4(a, 3, 2, 3, 4, yxyz);
			TEST_SWIZZLE_4(a, 3, 2, 4, 2, yxzx);
			TEST_SWIZZLE_4(a, 3, 2, 4, 3, yxzy);
			TEST_SWIZZLE_4(a, 3, 2, 4, 4, yxzz);
			TEST_SWIZZLE_4(a, 3, 3, 2, 2, yyxx);
			TEST_SWIZZLE_4(a, 3, 3, 2, 3, yyxy);
			TEST_SWIZZLE_4(a, 3, 3, 2, 4, yyxz);
			TEST_SWIZZLE_4(a, 3, 3, 3, 2, yyyx);
			TEST_SWIZZLE_4(a, 3, 3, 3, 3, yyyy);
			TEST_SWIZZLE_4(a, 3, 3, 3, 4, yyyz);
			TEST_SWIZZLE_4(a, 3, 3, 4, 2, yyzx);
			TEST_SWIZZLE_4(a, 3, 3, 4, 3, yyzy);
			TEST_SWIZZLE_4(a, 3, 3, 4, 4, yyzz);
			TEST_SWIZZLE_4(a, 3, 4, 2, 2, yzxx);
			TEST_SWIZZLE_4(a, 3, 4, 2, 3, yzxy);
			TEST_SWIZZLE_4(a, 3, 4, 2, 4, yzxz);
			TEST_SWIZZLE_4(a, 3, 4, 3, 2, yzyx);
			TEST_SWIZZLE_4(a, 3, 4, 3, 3, yzyy);
			TEST_SWIZZLE_4(a, 3, 4, 3, 4, yzyz);
			TEST_SWIZZLE_4(a, 3, 4, 4, 2, yzzx);
			TEST_SWIZZLE_4(a, 3, 4, 4, 3, yzzy);
			TEST_SWIZZLE_4(a, 3, 4, 4, 4, yzzz);

			TEST_SWIZZLE_4(a, 4, 2, 2, 2, zxxx);
			TEST_SWIZZLE_4(a, 4, 2, 2, 3, zxxy);
			TEST_SWIZZLE_4(a, 4, 2, 2, 4, zxxz);
			TEST_SWIZZLE_4(a, 4, 2, 3, 2, zxyx);
			TEST_SWIZZLE_4(a, 4, 2, 3, 3, zxyy);
			TEST_SWIZZLE_4(a, 4, 2, 3, 4, zxyz);
			TEST_SWIZZLE_4(a, 4, 2, 4, 2, zxzx);
			TEST_SWIZZLE_4(a, 4, 2, 4, 3, zxzy);
			TEST_SWIZZLE_4(a, 4, 2, 4, 4, zxzz);
			TEST_SWIZZLE_4(a, 4, 3, 2, 2, zyxx);
			TEST_SWIZZLE_4(a, 4, 3, 2, 3, zyxy);
			TEST_SWIZZLE_4(a, 4, 3, 2, 4, zyxz);
			TEST_SWIZZLE_4(a, 4, 3, 3, 2, zyyx);
			TEST_SWIZZLE_4(a, 4, 3, 3, 3, zyyy);
			TEST_SWIZZLE_4(a, 4, 3, 3, 4, zyyz);
			TEST_SWIZZLE_4(a, 4, 3, 4, 2, zyzx);
			TEST_SWIZZLE_4(a, 4, 3, 4, 3, zyzy);
			TEST_SWIZZLE_4(a, 4, 3, 4, 4, zyzz);
			TEST_SWIZZLE_4(a, 4, 4, 2, 2, zzxx);
			TEST_SWIZZLE_4(a, 4, 4, 2, 3, zzxy);
			TEST_SWIZZLE_4(a, 4, 4, 2, 4, zzxz);
			TEST_SWIZZLE_4(a, 4, 4, 3, 2, zzyx);
			TEST_SWIZZLE_4(a, 4, 4, 3, 3, zzyy);
			TEST_SWIZZLE_4(a, 4, 4, 3, 4, zzyz);
			TEST_SWIZZLE_4(a, 4, 4, 4, 2, zzzx);
			TEST_SWIZZLE_4(a, 4, 4, 4, 3, zzzy);
			TEST_SWIZZLE_4(a, 4, 4, 4, 4, zzzz);
		}
	};

	TEST_CLASS(Vector4Type)
	{
		TEST_METHOD(Vector4SizeOf)
		{
			Assert::AreEqual((size_t)4, sizeof(Vector4<uint8>));
			Assert::AreEqual((size_t)8, sizeof(Vector4<float16>));
			Assert::AreEqual((size_t)16, sizeof(Vector4<float32>));
		}

		TEST_METHOD(Vector4Construction)
		{
			Vector4<float32> vector = Make_Vector(1.0f, 2.0f, 3.0f, 4.0f);
			TEST_V4(vector, 1.0f, 2.0f, 3.0f, 4.0f);

			Vec4f vec4f = Make_Vector(4.4f, 5.5f, 6.6f, 7.7f);
			TEST_V4(vec4f, 4.4f, 5.5f, 6.6f, 7.7f);

			auto ptr = std::make_unique<Vector4<int32>>(3, 4, 5, 6);
			TEST_V4((*ptr), 3, 4, 5, 6);

			Vec4f copy(vec4f);
			Assert::AreEqual(vec4f, copy, L"Test vector4 copy construction.");
		}

		TEST_METHOD(Vector4Equality)
		{
			auto a = Make_Vector(2, 3, 4, 5);

			Assert::IsTrue(a == a, L"Vector4 != Vector4");
			Assert::IsTrue(a.xyzw == a, L"Swizzle4 != Vector4");
			Assert::IsTrue(a == a.xyzw, L"Vector4 != Swizzle4");
			Assert::IsTrue(a.xyzw == a.xyzw, L"Swizzle4 != Swizzle4");

			auto b = Make_Vector(2, 3);
			Assert::IsTrue(a != b.xxxx, L"Vector4 == Vector4");
		}

		TEST_METHOD(Vector4MulScalar)
		{
			Vec4f a = Make_Vector(1.0f, 2.0f, 3.0f, 4.0f);
			Vec4f b = a * 3.0f;
			TEST_V4(b, 3.0f, 6.0f, 9.0f, 12.0f);

			Vec4f c = a.xyzw * 3.0f;
			TEST_V4(c, 3.0f, 6.0f, 9.0f, 12.0f);
		}

		TEST_METHOD(Vector4AddVector)
		{
			Vec4f a = Make_Vector(1.0f, 2.0f, 3.0f, 4.0f);

			{
				auto b = a;
				b += b.xxxx;
			}
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxxx, 2.0f, 3.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxxy, 2.0f, 3.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxxz, 2.0f, 3.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxxw, 2.0f, 3.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxyx, 2.0f, 3.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxyy, 2.0f, 3.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxyz, 2.0f, 3.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxyw, 2.0f, 3.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxzx, 2.0f, 3.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxzy, 2.0f, 3.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxzz, 2.0f, 3.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxzw, 2.0f, 3.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxwx, 2.0f, 3.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxwy, 2.0f, 3.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxwz, 2.0f, 3.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xxww, 2.0f, 3.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyxx, 2.0f, 4.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyxy, 2.0f, 4.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyxz, 2.0f, 4.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyxw, 2.0f, 4.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyyx, 2.0f, 4.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyyy, 2.0f, 4.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyyz, 2.0f, 4.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyyw, 2.0f, 4.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyzx, 2.0f, 4.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyzy, 2.0f, 4.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyzz, 2.0f, 4.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyzw, 2.0f, 4.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xywx, 2.0f, 4.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xywy, 2.0f, 4.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xywz, 2.0f, 4.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xyww, 2.0f, 4.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzxx, 2.0f, 5.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzxy, 2.0f, 5.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzxz, 2.0f, 5.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzxw, 2.0f, 5.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzyx, 2.0f, 5.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzyy, 2.0f, 5.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzyz, 2.0f, 5.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzyw, 2.0f, 5.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzzx, 2.0f, 5.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzzy, 2.0f, 5.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzzz, 2.0f, 5.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzzw, 2.0f, 5.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzwx, 2.0f, 5.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzwy, 2.0f, 5.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzwz, 2.0f, 5.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xzww, 2.0f, 5.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwxx, 2.0f, 6.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwxy, 2.0f, 6.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwxz, 2.0f, 6.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwxw, 2.0f, 6.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwyx, 2.0f, 6.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwyy, 2.0f, 6.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwyz, 2.0f, 6.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwyw, 2.0f, 6.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwzx, 2.0f, 6.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwzy, 2.0f, 6.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwzz, 2.0f, 6.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwzw, 2.0f, 6.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwwx, 2.0f, 6.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwwy, 2.0f, 6.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwwz, 2.0f, 6.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, xwww, 2.0f, 6.0f, 7.0f, 8.0f);

			TEST_SELF_OP_SWIZZLE_4(a, +=, yxxx, 3.0f, 3.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxxy, 3.0f, 3.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxxz, 3.0f, 3.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxxw, 3.0f, 3.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxyx, 3.0f, 3.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxyy, 3.0f, 3.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxyz, 3.0f, 3.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxyw, 3.0f, 3.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxzx, 3.0f, 3.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxzy, 3.0f, 3.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxzz, 3.0f, 3.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxzw, 3.0f, 3.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxwx, 3.0f, 3.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxwy, 3.0f, 3.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxwz, 3.0f, 3.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yxww, 3.0f, 3.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyxx, 3.0f, 4.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyxy, 3.0f, 4.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyxz, 3.0f, 4.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyxw, 3.0f, 4.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyyx, 3.0f, 4.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyyy, 3.0f, 4.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyyz, 3.0f, 4.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyyw, 3.0f, 4.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyzx, 3.0f, 4.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyzy, 3.0f, 4.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyzz, 3.0f, 4.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyzw, 3.0f, 4.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yywx, 3.0f, 4.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yywy, 3.0f, 4.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yywz, 3.0f, 4.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yyww, 3.0f, 4.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzxx, 3.0f, 5.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzxy, 3.0f, 5.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzxz, 3.0f, 5.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzxw, 3.0f, 5.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzyx, 3.0f, 5.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzyy, 3.0f, 5.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzyz, 3.0f, 5.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzyw, 3.0f, 5.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzzx, 3.0f, 5.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzzy, 3.0f, 5.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzzz, 3.0f, 5.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzzw, 3.0f, 5.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzwx, 3.0f, 5.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzwy, 3.0f, 5.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzwz, 3.0f, 5.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, yzww, 3.0f, 5.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywxx, 3.0f, 6.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywxy, 3.0f, 6.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywxz, 3.0f, 6.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywxw, 3.0f, 6.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywyx, 3.0f, 6.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywyy, 3.0f, 6.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywyz, 3.0f, 6.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywyw, 3.0f, 6.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywzx, 3.0f, 6.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywzy, 3.0f, 6.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywzz, 3.0f, 6.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywzw, 3.0f, 6.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywwx, 3.0f, 6.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywwy, 3.0f, 6.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywwz, 3.0f, 6.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, ywww, 3.0f, 6.0f, 7.0f, 8.0f);

			TEST_SELF_OP_SWIZZLE_4(a, +=, zxxx, 4.0f, 3.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxxy, 4.0f, 3.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxxz, 4.0f, 3.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxxw, 4.0f, 3.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxyx, 4.0f, 3.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxyy, 4.0f, 3.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxyz, 4.0f, 3.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxyw, 4.0f, 3.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxzx, 4.0f, 3.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxzy, 4.0f, 3.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxzz, 4.0f, 3.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxzw, 4.0f, 3.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxwx, 4.0f, 3.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxwy, 4.0f, 3.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxwz, 4.0f, 3.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zxww, 4.0f, 3.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyxx, 4.0f, 4.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyxy, 4.0f, 4.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyxz, 4.0f, 4.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyxw, 4.0f, 4.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyyx, 4.0f, 4.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyyy, 4.0f, 4.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyyz, 4.0f, 4.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyyw, 4.0f, 4.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyzx, 4.0f, 4.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyzy, 4.0f, 4.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyzz, 4.0f, 4.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyzw, 4.0f, 4.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zywx, 4.0f, 4.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zywy, 4.0f, 4.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zywz, 4.0f, 4.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zyww, 4.0f, 4.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzxx, 4.0f, 5.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzxy, 4.0f, 5.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzxz, 4.0f, 5.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzxw, 4.0f, 5.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzyx, 4.0f, 5.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzyy, 4.0f, 5.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzyz, 4.0f, 5.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzyw, 4.0f, 5.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzzx, 4.0f, 5.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzzy, 4.0f, 5.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzzz, 4.0f, 5.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzzw, 4.0f, 5.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzwx, 4.0f, 5.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzwy, 4.0f, 5.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzwz, 4.0f, 5.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zzww, 4.0f, 5.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwxx, 4.0f, 6.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwxy, 4.0f, 6.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwxz, 4.0f, 6.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwxw, 4.0f, 6.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwyx, 4.0f, 6.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwyy, 4.0f, 6.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwyz, 4.0f, 6.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwyw, 4.0f, 6.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwzx, 4.0f, 6.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwzy, 4.0f, 6.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwzz, 4.0f, 6.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwzw, 4.0f, 6.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwwx, 4.0f, 6.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwwy, 4.0f, 6.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwwz, 4.0f, 6.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, zwww, 4.0f, 6.0f, 7.0f, 8.0f);

			TEST_SELF_OP_SWIZZLE_4(a, +=, wxxx, 5.0f, 3.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxxy, 5.0f, 3.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxxz, 5.0f, 3.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxxw, 5.0f, 3.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxyx, 5.0f, 3.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxyy, 5.0f, 3.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxyz, 5.0f, 3.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxyw, 5.0f, 3.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxzx, 5.0f, 3.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxzy, 5.0f, 3.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxzz, 5.0f, 3.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxzw, 5.0f, 3.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxwx, 5.0f, 3.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxwy, 5.0f, 3.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxwz, 5.0f, 3.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wxww, 5.0f, 3.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyxx, 5.0f, 4.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyxy, 5.0f, 4.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyxz, 5.0f, 4.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyxw, 5.0f, 4.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyyx, 5.0f, 4.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyyy, 5.0f, 4.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyyz, 5.0f, 4.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyyw, 5.0f, 4.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyzx, 5.0f, 4.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyzy, 5.0f, 4.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyzz, 5.0f, 4.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyzw, 5.0f, 4.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wywx, 5.0f, 4.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wywy, 5.0f, 4.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wywz, 5.0f, 4.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wyww, 5.0f, 4.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzxx, 5.0f, 5.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzxy, 5.0f, 5.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzxz, 5.0f, 5.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzxw, 5.0f, 5.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzyx, 5.0f, 5.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzyy, 5.0f, 5.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzyz, 5.0f, 5.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzyw, 5.0f, 5.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzzx, 5.0f, 5.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzzy, 5.0f, 5.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzzz, 5.0f, 5.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzzw, 5.0f, 5.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzwx, 5.0f, 5.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzwy, 5.0f, 5.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzwz, 5.0f, 5.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wzww, 5.0f, 5.0f, 7.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwxx, 5.0f, 6.0f, 4.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwxy, 5.0f, 6.0f, 4.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwxz, 5.0f, 6.0f, 4.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwxw, 5.0f, 6.0f, 4.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwyx, 5.0f, 6.0f, 5.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwyy, 5.0f, 6.0f, 5.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwyz, 5.0f, 6.0f, 5.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwyw, 5.0f, 6.0f, 5.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwzx, 5.0f, 6.0f, 6.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwzy, 5.0f, 6.0f, 6.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwzz, 5.0f, 6.0f, 6.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwzw, 5.0f, 6.0f, 6.0f, 8.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwwx, 5.0f, 6.0f, 7.0f, 5.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwwy, 5.0f, 6.0f, 7.0f, 6.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwwz, 5.0f, 6.0f, 7.0f, 7.0f);
			TEST_SELF_OP_SWIZZLE_4(a, +=, wwww, 5.0f, 6.0f, 7.0f, 8.0f);

			Vec4f b = Make_Vector(8.0f, 9.0f, 10.0f, 12.0f);
			TEST_A_OP_B_4(a, +, b, 9.f, 11.f, 13.f, 16.0f);
			TEST_A_OP_B_4(b, +, a, 9.f, 11.f, 13.f, 16.0f);
			TEST_A_OP_SWIZZLE_4(a, +, b, xyzw, 9.f, 11.f, 13.f, 16.f);
			TEST_SWIZZLE_OP_B_4(a, xyzw, +, b, 9.f, 11.f, 13.f, 16.f);
			TEST_SWIZZLE_OP_SWIZZLE_4(a, xyzw, +, b, xyzw, 9.f, 11.f, 13.f, 16.f);
		}

		TEST_METHOD(Vector4MulVector)
		{
			Vec4f a = Make_Vector(2.0f, 3.0f, 4.0f, 5.0f);

			TEST_SELF_OP_4(a, *=, 4.f, 9.f, 16.f, 25.0f);

			TEST_SELF_OP_SWIZZLE_4(a, *=, xxxx, 4.0f, 6.0f, 8.0f, 10.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxxy, 4.f, 6.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxxz, 4.f, 6.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxxw, 4.f, 6.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxyx, 4.f, 6.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxyy, 4.f, 6.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxyz, 4.f, 6.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxyw, 4.f, 6.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxzx, 4.f, 6.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxzy, 4.f, 6.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxzz, 4.f, 6.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxzw, 4.f, 6.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxwx, 4.f, 6.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxwy, 4.f, 6.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxwz, 4.f, 6.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xxww, 4.f, 6.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyxx, 4.f, 9.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyxy, 4.f, 9.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyxz, 4.f, 9.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyxw, 4.f, 9.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyyx, 4.f, 9.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyyy, 4.f, 9.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyyz, 4.f, 9.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyyw, 4.f, 9.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyzx, 4.f, 9.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyzy, 4.f, 9.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyzz, 4.f, 9.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyzw, 4.f, 9.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xywx, 4.f, 9.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xywy, 4.f, 9.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xywz, 4.f, 9.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xyww, 4.f, 9.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzxx, 4.f, 12.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzxy, 4.f, 12.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzxz, 4.f, 12.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzxw, 4.f, 12.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzyx, 4.f, 12.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzyy, 4.f, 12.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzyz, 4.f, 12.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzyw, 4.f, 12.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzzx, 4.f, 12.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzzy, 4.f, 12.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzzz, 4.f, 12.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzzw, 4.f, 12.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzwx, 4.f, 12.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzwy, 4.f, 12.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzwz, 4.f, 12.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xzww, 4.f, 12.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwxx, 4.f, 15.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwxy, 4.f, 15.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwxz, 4.f, 15.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwxw, 4.f, 15.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwyx, 4.f, 15.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwyy, 4.f, 15.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwyz, 4.f, 15.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwyw, 4.f, 15.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwzx, 4.f, 15.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwzy, 4.f, 15.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwzz, 4.f, 15.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwzw, 4.f, 15.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwwx, 4.f, 15.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwwy, 4.f, 15.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwwz, 4.f, 15.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, xwww, 4.f, 15.f, 20.f, 25.0f);

			TEST_SELF_OP_SWIZZLE_4(a, *=, yxxx, 6.f, 6.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxxy, 6.f, 6.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxxz, 6.f, 6.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxxw, 6.f, 6.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxyx, 6.f, 6.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxyy, 6.f, 6.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxyz, 6.f, 6.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxyw, 6.f, 6.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxzx, 6.f, 6.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxzy, 6.f, 6.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxzz, 6.f, 6.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxzw, 6.f, 6.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxwx, 6.f, 6.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxwy, 6.f, 6.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxwz, 6.f, 6.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yxww, 6.f, 6.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyxx, 6.f, 9.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyxy, 6.f, 9.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyxz, 6.f, 9.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyxw, 6.f, 9.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyyx, 6.f, 9.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyyy, 6.f, 9.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyyz, 6.f, 9.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyyw, 6.f, 9.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyzx, 6.f, 9.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyzy, 6.f, 9.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyzz, 6.f, 9.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyzw, 6.f, 9.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yywx, 6.f, 9.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yywy, 6.f, 9.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yywz, 6.f, 9.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yyww, 6.f, 9.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzxx, 6.f, 12.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzxy, 6.f, 12.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzxz, 6.f, 12.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzxw, 6.f, 12.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzyx, 6.f, 12.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzyy, 6.f, 12.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzyz, 6.f, 12.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzyw, 6.f, 12.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzzx, 6.f, 12.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzzy, 6.f, 12.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzzz, 6.f, 12.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzzw, 6.f, 12.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzwx, 6.f, 12.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzwy, 6.f, 12.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzwz, 6.f, 12.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, yzww, 6.f, 12.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywxx, 6.f, 15.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywxy, 6.f, 15.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywxz, 6.f, 15.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywxw, 6.f, 15.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywyx, 6.f, 15.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywyy, 6.f, 15.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywyz, 6.f, 15.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywyw, 6.f, 15.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywzx, 6.f, 15.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywzy, 6.f, 15.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywzz, 6.f, 15.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywzw, 6.f, 15.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywwx, 6.f, 15.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywwy, 6.f, 15.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywwz, 6.f, 15.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, ywww, 6.f, 15.f, 20.f, 25.0f);

			TEST_SELF_OP_SWIZZLE_4(a, *=, zxxx, 8.f, 6.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxxy, 8.f, 6.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxxz, 8.f, 6.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxxw, 8.f, 6.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxyx, 8.f, 6.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxyy, 8.f, 6.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxyz, 8.f, 6.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxyw, 8.f, 6.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxzx, 8.f, 6.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxzy, 8.f, 6.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxzz, 8.f, 6.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxzw, 8.f, 6.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxwx, 8.f, 6.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxwy, 8.f, 6.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxwz, 8.f, 6.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zxww, 8.f, 6.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyxx, 8.f, 9.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyxy, 8.f, 9.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyxz, 8.f, 9.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyxw, 8.f, 9.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyyx, 8.f, 9.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyyy, 8.f, 9.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyyz, 8.f, 9.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyyw, 8.f, 9.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyzx, 8.f, 9.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyzy, 8.f, 9.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyzz, 8.f, 9.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyzw, 8.f, 9.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zywx, 8.f, 9.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zywy, 8.f, 9.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zywz, 8.f, 9.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zyww, 8.f, 9.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzxx, 8.f, 12.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzxy, 8.f, 12.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzxz, 8.f, 12.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzxw, 8.f, 12.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzyx, 8.f, 12.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzyy, 8.f, 12.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzyz, 8.f, 12.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzyw, 8.f, 12.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzzx, 8.f, 12.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzzy, 8.f, 12.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzzz, 8.f, 12.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzzw, 8.f, 12.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzwx, 8.f, 12.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzwy, 8.f, 12.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzwz, 8.f, 12.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zzww, 8.f, 12.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwxx, 8.f, 15.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwxy, 8.f, 15.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwxz, 8.f, 15.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwxw, 8.f, 15.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwyx, 8.f, 15.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwyy, 8.f, 15.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwyz, 8.f, 15.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwyw, 8.f, 15.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwzx, 8.f, 15.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwzy, 8.f, 15.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwzz, 8.f, 15.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwzw, 8.f, 15.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwwx, 8.f, 15.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwwy, 8.f, 15.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwwz, 8.f, 15.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, zwww, 8.f, 15.f, 20.f, 25.0f);

			TEST_SELF_OP_SWIZZLE_4(a, *=, wxxx, 10.f, 6.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxxy, 10.f, 6.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxxz, 10.f, 6.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxxw, 10.f, 6.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxyx, 10.f, 6.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxyy, 10.f, 6.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxyz, 10.f, 6.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxyw, 10.f, 6.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxzx, 10.f, 6.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxzy, 10.f, 6.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxzz, 10.f, 6.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxzw, 10.f, 6.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxwx, 10.f, 6.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxwy, 10.f, 6.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxwz, 10.f, 6.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wxww, 10.f, 6.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyxx, 10.f, 9.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyxy, 10.f, 9.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyxz, 10.f, 9.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyxw, 10.f, 9.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyyx, 10.f, 9.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyyy, 10.f, 9.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyyz, 10.f, 9.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyyw, 10.f, 9.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyzx, 10.f, 9.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyzy, 10.f, 9.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyzz, 10.f, 9.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyzw, 10.f, 9.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wywx, 10.f, 9.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wywy, 10.f, 9.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wywz, 10.f, 9.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wyww, 10.f, 9.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzxx, 10.f, 12.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzxy, 10.f, 12.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzxz, 10.f, 12.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzxw, 10.f, 12.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzyx, 10.f, 12.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzyy, 10.f, 12.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzyz, 10.f, 12.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzyw, 10.f, 12.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzzx, 10.f, 12.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzzy, 10.f, 12.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzzz, 10.f, 12.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzzw, 10.f, 12.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzwx, 10.f, 12.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzwy, 10.f, 12.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzwz, 10.f, 12.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wzww, 10.f, 12.f, 20.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwxx, 10.f, 15.f, 8.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwxy, 10.f, 15.f, 8.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwxz, 10.f, 15.f, 8.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwxw, 10.f, 15.f, 8.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwyx, 10.f, 15.f, 12.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwyy, 10.f, 15.f, 12.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwyz, 10.f, 15.f, 12.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwyw, 10.f, 15.f, 12.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwzx, 10.f, 15.f, 16.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwzy, 10.f, 15.f, 16.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwzz, 10.f, 15.f, 16.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwzw, 10.f, 15.f, 16.f, 25.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwwx, 10.f, 15.f, 20.f, 10.f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwwy, 10.f, 15.f, 20.f, 15.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwwz, 10.f, 15.f, 20.f, 20.0f);
			TEST_SELF_OP_SWIZZLE_4(a, *=, wwww, 10.f, 15.f, 20.f, 25.0f);

			Vec4f b = Make_Vector(8.0f, 9.0f, 10.0f, 12.0f);
			TEST_A_OP_B_4(a, *, b, 16.f, 27.f, 40.f, 60.0f);
			TEST_A_OP_B_4(b, *, a, 16.f, 27.f, 40.f, 60.0f);
			TEST_A_OP_SWIZZLE_4(a, *, b, xyzw, 16.f, 27.f, 40.f, 60.f);
			TEST_SWIZZLE_OP_B_4(a, xyzw, *, b, 16.f, 27.f, 40.f, 60.f);
			TEST_SWIZZLE_OP_SWIZZLE_4(a, xyzw, *, b, xyzw, 16.f, 27.f, 40.f, 60.f);
		}

		TEST_METHOD(Vector4DivScalar)
		{
			Vec4f a = Make_Vector(9.0f, 12.0f, 15.0f, 21.0f);
			Vec4f b = a / 3.0f;
			TEST_V4(b, 3.0f, 4.0f, 5.0f, 7.0f);

			Vec4f c = a.xyzw / 3.0f;
			TEST_V4(c, 3.0f, 4.0f, 5.0f, 7.0f);
		}

		TEST_METHOD(Vector4DivVector)
		{
			Vec4f a = Make_Vector(8.0f, 4.0f, 2.0f, 1.0f);
			TEST_SELF_OP_4(a, /=, 1.f, 1.f, 1.f, 1.f);

			TEST_SELF_OP_SWIZZLE_4(a, /=, xxxx, 1.0f, 0.5f, 0.25f, 0.125f); 
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxxy, 1.0f, 0.5f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxxz, 1.0f, 0.5f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxxw, 1.0f, 0.5f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxyx, 1.0f, 0.5f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxyy, 1.0f, 0.5f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxyz, 1.0f, 0.5f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxyw, 1.0f, 0.5f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxzx, 1.0f, 0.5f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxzy, 1.0f, 0.5f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxzz, 1.0f, 0.5f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxzw, 1.0f, 0.5f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxwx, 1.0f, 0.5f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxwy, 1.0f, 0.5f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxwz, 1.0f, 0.5f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xxww, 1.0f, 0.5f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyxx, 1.0f, 1.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyxy, 1.0f, 1.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyxz, 1.0f, 1.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyxw, 1.0f, 1.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyyx, 1.0f, 1.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyyy, 1.0f, 1.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyyz, 1.0f, 1.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyyw, 1.0f, 1.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyzx, 1.0f, 1.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyzy, 1.0f, 1.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyzz, 1.0f, 1.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyzw, 1.0f, 1.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xywx, 1.0f, 1.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xywy, 1.0f, 1.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xywz, 1.0f, 1.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xyww, 1.0f, 1.0f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzxx, 1.0f, 2.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzxy, 1.0f, 2.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzxz, 1.0f, 2.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzxw, 1.0f, 2.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzyx, 1.0f, 2.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzyy, 1.0f, 2.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzyz, 1.0f, 2.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzyw, 1.0f, 2.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzzx, 1.0f, 2.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzzy, 1.0f, 2.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzzz, 1.0f, 2.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzzw, 1.0f, 2.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzwx, 1.0f, 2.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzwy, 1.0f, 2.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzwz, 1.0f, 2.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xzww, 1.0f, 2.0f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwxx, 1.0f, 4.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwxy, 1.0f, 4.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwxz, 1.0f, 4.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwxw, 1.0f, 4.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwyx, 1.0f, 4.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwyy, 1.0f, 4.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwyz, 1.0f, 4.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwyw, 1.0f, 4.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwzx, 1.0f, 4.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwzy, 1.0f, 4.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwzz, 1.0f, 4.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwzw, 1.0f, 4.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwwx, 1.0f, 4.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwwy, 1.0f, 4.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwwz, 1.0f, 4.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, xwww, 1.0f, 4.0f, 2.0f, 1.0f);

			TEST_SELF_OP_SWIZZLE_4(a, /=, yxxx, 2.0f, 0.5f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxxy, 2.0f, 0.5f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxxz, 2.0f, 0.5f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxxw, 2.0f, 0.5f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxyx, 2.0f, 0.5f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxyy, 2.0f, 0.5f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxyz, 2.0f, 0.5f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxyw, 2.0f, 0.5f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxzx, 2.0f, 0.5f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxzy, 2.0f, 0.5f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxzz, 2.0f, 0.5f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxzw, 2.0f, 0.5f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxwx, 2.0f, 0.5f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxwy, 2.0f, 0.5f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxwz, 2.0f, 0.5f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yxww, 2.0f, 0.5f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyxx, 2.0f, 1.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyxy, 2.0f, 1.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyxz, 2.0f, 1.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyxw, 2.0f, 1.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyyx, 2.0f, 1.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyyy, 2.0f, 1.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyyz, 2.0f, 1.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyyw, 2.0f, 1.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyzx, 2.0f, 1.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyzy, 2.0f, 1.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyzz, 2.0f, 1.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyzw, 2.0f, 1.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yywx, 2.0f, 1.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yywy, 2.0f, 1.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yywz, 2.0f, 1.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yyww, 2.0f, 1.0f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzxx, 2.0f, 2.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzxy, 2.0f, 2.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzxz, 2.0f, 2.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzxw, 2.0f, 2.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzyx, 2.0f, 2.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzyy, 2.0f, 2.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzyz, 2.0f, 2.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzyw, 2.0f, 2.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzzx, 2.0f, 2.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzzy, 2.0f, 2.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzzz, 2.0f, 2.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzzw, 2.0f, 2.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzwx, 2.0f, 2.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzwy, 2.0f, 2.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzwz, 2.0f, 2.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, yzww, 2.0f, 2.0f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywxx, 2.0f, 4.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywxy, 2.0f, 4.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywxz, 2.0f, 4.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywxw, 2.0f, 4.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywyx, 2.0f, 4.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywyy, 2.0f, 4.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywyz, 2.0f, 4.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywyw, 2.0f, 4.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywzx, 2.0f, 4.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywzy, 2.0f, 4.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywzz, 2.0f, 4.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywzw, 2.0f, 4.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywwx, 2.0f, 4.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywwy, 2.0f, 4.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywwz, 2.0f, 4.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, ywww, 2.0f, 4.0f, 2.0f, 1.0f);

			TEST_SELF_OP_SWIZZLE_4(a, /=, zxxx, 4.0f, 0.5f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxxy, 4.0f, 0.5f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxxz, 4.0f, 0.5f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxxw, 4.0f, 0.5f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxyx, 4.0f, 0.5f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxyy, 4.0f, 0.5f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxyz, 4.0f, 0.5f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxyw, 4.0f, 0.5f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxzx, 4.0f, 0.5f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxzy, 4.0f, 0.5f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxzz, 4.0f, 0.5f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxzw, 4.0f, 0.5f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxwx, 4.0f, 0.5f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxwy, 4.0f, 0.5f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxwz, 4.0f, 0.5f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zxww, 4.0f, 0.5f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyxx, 4.0f, 1.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyxy, 4.0f, 1.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyxz, 4.0f, 1.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyxw, 4.0f, 1.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyyx, 4.0f, 1.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyyy, 4.0f, 1.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyyz, 4.0f, 1.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyyw, 4.0f, 1.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyzx, 4.0f, 1.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyzy, 4.0f, 1.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyzz, 4.0f, 1.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyzw, 4.0f, 1.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zywx, 4.0f, 1.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zywy, 4.0f, 1.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zywz, 4.0f, 1.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zyww, 4.0f, 1.0f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzxx, 4.0f, 2.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzxy, 4.0f, 2.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzxz, 4.0f, 2.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzxw, 4.0f, 2.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzyx, 4.0f, 2.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzyy, 4.0f, 2.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzyz, 4.0f, 2.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzyw, 4.0f, 2.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzzx, 4.0f, 2.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzzy, 4.0f, 2.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzzz, 4.0f, 2.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzzw, 4.0f, 2.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzwx, 4.0f, 2.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzwy, 4.0f, 2.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzwz, 4.0f, 2.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zzww, 4.0f, 2.0f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwxx, 4.0f, 4.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwxy, 4.0f, 4.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwxz, 4.0f, 4.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwxw, 4.0f, 4.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwyx, 4.0f, 4.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwyy, 4.0f, 4.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwyz, 4.0f, 4.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwyw, 4.0f, 4.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwzx, 4.0f, 4.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwzy, 4.0f, 4.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwzz, 4.0f, 4.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwzw, 4.0f, 4.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwwx, 4.0f, 4.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwwy, 4.0f, 4.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwwz, 4.0f, 4.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, zwww, 4.0f, 4.0f, 2.0f, 1.0f);

			TEST_SELF_OP_SWIZZLE_4(a, /=, wxxx, 8.0f, 0.5f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxxy, 8.0f, 0.5f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxxz, 8.0f, 0.5f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxxw, 8.0f, 0.5f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxyx, 8.0f, 0.5f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxyy, 8.0f, 0.5f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxyz, 8.0f, 0.5f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxyw, 8.0f, 0.5f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxzx, 8.0f, 0.5f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxzy, 8.0f, 0.5f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxzz, 8.0f, 0.5f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxzw, 8.0f, 0.5f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxwx, 8.0f, 0.5f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxwy, 8.0f, 0.5f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxwz, 8.0f, 0.5f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wxww, 8.0f, 0.5f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyxx, 8.0f, 1.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyxy, 8.0f, 1.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyxz, 8.0f, 1.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyxw, 8.0f, 1.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyyx, 8.0f, 1.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyyy, 8.0f, 1.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyyz, 8.0f, 1.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyyw, 8.0f, 1.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyzx, 8.0f, 1.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyzy, 8.0f, 1.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyzz, 8.0f, 1.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyzw, 8.0f, 1.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wywx, 8.0f, 1.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wywy, 8.0f, 1.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wywz, 8.0f, 1.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wyww, 8.0f, 1.0f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzxx, 8.0f, 2.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzxy, 8.0f, 2.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzxz, 8.0f, 2.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzxw, 8.0f, 2.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzyx, 8.0f, 2.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzyy, 8.0f, 2.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzyz, 8.0f, 2.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzyw, 8.0f, 2.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzzx, 8.0f, 2.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzzy, 8.0f, 2.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzzz, 8.0f, 2.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzzw, 8.0f, 2.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzwx, 8.0f, 2.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzwy, 8.0f, 2.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzwz, 8.0f, 2.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wzww, 8.0f, 2.0f, 2.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwxx, 8.0f, 4.0f, 0.25f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwxy, 8.0f, 4.0f, 0.25f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwxz, 8.0f, 4.0f, 0.25f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwxw, 8.0f, 4.0f, 0.25f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwyx, 8.0f, 4.0f, 0.5f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwyy, 8.0f, 4.0f, 0.5f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwyz, 8.0f, 4.0f, 0.5f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwyw, 8.0f, 4.0f, 0.5f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwzx, 8.0f, 4.0f, 1.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwzy, 8.0f, 4.0f, 1.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwzz, 8.0f, 4.0f, 1.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwzw, 8.0f, 4.0f, 1.0f, 1.0f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwwx, 8.0f, 4.0f, 2.0f, 0.125f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwwy, 8.0f, 4.0f, 2.0f, 0.25f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwwz, 8.0f, 4.0f, 2.0f, 0.5f);
			TEST_SELF_OP_SWIZZLE_4(a, /=, wwww, 8.0f, 4.0f, 2.0f, 1.0f);

			Vec4f b = Make_Vector(1.f, 2.0f, 4.0f, 8.0f);
			TEST_A_OP_B_4(a, /, b, 8.f, 2.f, 0.5f, 0.125f);
			TEST_A_OP_B_4(b, /, a, 0.125f, 0.5f, 2.f, 8.0f);
			TEST_A_OP_SWIZZLE_4(a, /, b, xyzw, 8.f, 2.f, 0.5f, 0.125f);
			TEST_SWIZZLE_OP_B_4(a, xyzw, /, b, 8.f, 2.f, 0.5f, 0.125f);
			TEST_SWIZZLE_OP_SWIZZLE_4(a, xyzw, /, b, xyzw, 8.f, 2.f, 0.5f, 0.125f);
		}

		TEST_METHOD(Vector4SubVector)
		{
			auto a = Make_Vector(2, 4, 7, 9);
			TEST_SELF_OP_4(a, -=, 0, 0, 0, 0);

			TEST_SELF_OP_SWIZZLE_4(a, -=, xxxx, 0, 2, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxxy, 0, 2, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxxz, 0, 2, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxxw, 0, 2, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxyx, 0, 2, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxyy, 0, 2, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxyz, 0, 2, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxyw, 0, 2, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxzx, 0, 2, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxzy, 0, 2, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxzz, 0, 2, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxzw, 0, 2, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxwx, 0, 2, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxwy, 0, 2, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxwz, 0, 2, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xxww, 0, 2, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyxx, 0, 0, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyxy, 0, 0, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyxz, 0, 0, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyxw, 0, 0, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyyx, 0, 0, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyyy, 0, 0, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyyz, 0, 0, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyyw, 0, 0, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyzx, 0, 0, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyzy, 0, 0, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyzz, 0, 0, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyzw, 0, 0, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xywx, 0, 0, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xywy, 0, 0, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xywz, 0, 0, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xyww, 0, 0, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzxx, 0, -3, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzxy, 0, -3, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzxz, 0, -3, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzxw, 0, -3, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzyx, 0, -3, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzyy, 0, -3, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzyz, 0, -3, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzyw, 0, -3, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzzx, 0, -3, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzzy, 0, -3, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzzz, 0, -3, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzzw, 0, -3, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzwx, 0, -3, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzwy, 0, -3, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzwz, 0, -3, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xzww, 0, -3, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwxx, 0, -5, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwxy, 0, -5, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwxz, 0, -5, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwxw, 0, -5, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwyx, 0, -5, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwyy, 0, -5, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwyz, 0, -5, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwyw, 0, -5, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwzx, 0, -5, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwzy, 0, -5, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwzz, 0, -5, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwzw, 0, -5, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwwx, 0, -5, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwwy, 0, -5, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwwz, 0, -5, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, xwww, 0, -5, -2, 0);

			TEST_SELF_OP_SWIZZLE_4(a, -=, yxxx, -2, 2, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxxy, -2, 2, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxxz, -2, 2, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxxw, -2, 2, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxyx, -2, 2, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxyy, -2, 2, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxyz, -2, 2, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxyw, -2, 2, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxzx, -2, 2, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxzy, -2, 2, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxzz, -2, 2, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxzw, -2, 2, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxwx, -2, 2, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxwy, -2, 2, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxwz, -2, 2, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yxww, -2, 2, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyxx, -2, 0, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyxy, -2, 0, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyxz, -2, 0, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyxw, -2, 0, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyyx, -2, 0, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyyy, -2, 0, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyyz, -2, 0, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyyw, -2, 0, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyzx, -2, 0, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyzy, -2, 0, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyzz, -2, 0, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyzw, -2, 0, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yywx, -2, 0, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yywy, -2, 0, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yywz, -2, 0, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yyww, -2, 0, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzxx, -2, -3, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzxy, -2, -3, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzxz, -2, -3, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzxw, -2, -3, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzyx, -2, -3, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzyy, -2, -3, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzyz, -2, -3, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzyw, -2, -3, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzzx, -2, -3, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzzy, -2, -3, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzzz, -2, -3, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzzw, -2, -3, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzwx, -2, -3, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzwy, -2, -3, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzwz, -2, -3, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, yzww, -2, -3, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywxx, -2, -5, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywxy, -2, -5, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywxz, -2, -5, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywxw, -2, -5, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywyx, -2, -5, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywyy, -2, -5, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywyz, -2, -5, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywyw, -2, -5, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywzx, -2, -5, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywzy, -2, -5, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywzz, -2, -5, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywzw, -2, -5, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywwx, -2, -5, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywwy, -2, -5, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywwz, -2, -5, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, ywww, -2, -5, -2, 0);

			TEST_SELF_OP_SWIZZLE_4(a, -=, zxxx, -5, 2, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxxy, -5, 2, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxxz, -5, 2, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxxw, -5, 2, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxyx, -5, 2, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxyy, -5, 2, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxyz, -5, 2, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxyw, -5, 2, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxzx, -5, 2, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxzy, -5, 2, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxzz, -5, 2, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxzw, -5, 2, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxwx, -5, 2, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxwy, -5, 2, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxwz, -5, 2, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zxww, -5, 2, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyxx, -5, 0, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyxy, -5, 0, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyxz, -5, 0, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyxw, -5, 0, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyyx, -5, 0, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyyy, -5, 0, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyyz, -5, 0, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyyw, -5, 0, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyzx, -5, 0, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyzy, -5, 0, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyzz, -5, 0, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyzw, -5, 0, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zywx, -5, 0, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zywy, -5, 0, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zywz, -5, 0, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zyww, -5, 0, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzxx, -5, -3, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzxy, -5, -3, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzxz, -5, -3, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzxw, -5, -3, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzyx, -5, -3, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzyy, -5, -3, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzyz, -5, -3, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzyw, -5, -3, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzzx, -5, -3, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzzy, -5, -3, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzzz, -5, -3, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzzw, -5, -3, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzwx, -5, -3, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzwy, -5, -3, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzwz, -5, -3, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zzww, -5, -3, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwxx, -5, -5, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwxy, -5, -5, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwxz, -5, -5, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwxw, -5, -5, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwyx, -5, -5, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwyy, -5, -5, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwyz, -5, -5, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwyw, -5, -5, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwzx, -5, -5, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwzy, -5, -5, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwzz, -5, -5, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwzw, -5, -5, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwwx, -5, -5, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwwy, -5, -5, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwwz, -5, -5, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, zwww, -5, -5, -2, 0);

			TEST_SELF_OP_SWIZZLE_4(a, -=, wxxx, -7, 2, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxxy, -7, 2, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxxz, -7, 2, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxxw, -7, 2, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxyx, -7, 2, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxyy, -7, 2, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxyz, -7, 2, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxyw, -7, 2, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxzx, -7, 2, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxzy, -7, 2, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxzz, -7, 2, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxzw, -7, 2, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxwx, -7, 2, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxwy, -7, 2, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxwz, -7, 2, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wxww, -7, 2, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyxx, -7, 0, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyxy, -7, 0, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyxz, -7, 0, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyxw, -7, 0, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyyx, -7, 0, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyyy, -7, 0, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyyz, -7, 0, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyyw, -7, 0, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyzx, -7, 0, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyzy, -7, 0, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyzz, -7, 0, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyzw, -7, 0, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wywx, -7, 0, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wywy, -7, 0, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wywz, -7, 0, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wyww, -7, 0, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzxx, -7, -3, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzxy, -7, -3, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzxz, -7, -3, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzxw, -7, -3, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzyx, -7, -3, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzyy, -7, -3, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzyz, -7, -3, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzyw, -7, -3, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzzx, -7, -3, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzzy, -7, -3, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzzz, -7, -3, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzzw, -7, -3, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzwx, -7, -3, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzwy, -7, -3, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzwz, -7, -3, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wzww, -7, -3, -2, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwxx, -7, -5, 5, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwxy, -7, -5, 5, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwxz, -7, -5, 5, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwxw, -7, -5, 5, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwyx, -7, -5, 3, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwyy, -7, -5, 3, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwyz, -7, -5, 3, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwyw, -7, -5, 3, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwzx, -7, -5, 0, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwzy, -7, -5, 0, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwzz, -7, -5, 0, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwzw, -7, -5, 0, 0);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwwx, -7, -5, -2, 7);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwwy, -7, -5, -2, 5);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwwz, -7, -5, -2, 2);
			TEST_SELF_OP_SWIZZLE_4(a, -=, wwww, -7, -5, -2, 0);
		}

		TEST_METHOD(Vector4Min)
		{
			auto a = Make_Vector(4, 5, 6, 7);
			auto b = Make_Vector(7, 6, 5, 4);

			auto c = Min(a, b);
			TEST_V4(c, 4, 5, 5, 4);

			auto d = Min(a.xyzw, b);
			TEST_V4(d, 4, 5, 5, 4);

			auto e = Min(a, b.xyzw);
			TEST_V4(e, 4, 5, 5, 4);

			auto f = Min(a.xyzw, b.xyzw);
			TEST_V4(f, 4, 5, 5, 4);
		}

		TEST_METHOD(Vector4Max)
		{
			auto a = Make_Vector(4, 5, 6, 7);
			auto b = Make_Vector(7, 6, 5, 4);
			static_assert(AllVector4<decltype(a), decltype(b)>, "Whoa!");

			auto c = Max(a, b);
			TEST_V4(c, 7, 6, 6, 7);

			auto d = Max(a.xyzw, b);
			TEST_V4(c, 7, 6, 6, 7);

			auto e = Max(a, b.xyzw);
			TEST_V4(e, 7, 6, 6, 7);

			auto f = Max(a.xyzw, b.xyzw);
			TEST_V4(f, 7, 6, 6, 7);
		}

		TEST_METHOD(Vector4Clamp)
		{
			auto a = Make_Vector(3, 5, 7, 9);
			auto b = Make_Vector(4, 4, 4, 4);
			auto c = Make_Vector(6, 6, 6, 6);

			auto d = Clamp(a, b, c);
			TEST_V4(d, 4, 5, 6, 6);

			auto e = Clamp(a.xyzw, b.xyzw, c.xyzw);
			TEST_V4(e, 4, 5, 6, 6);

			auto f = Clamp(a.xyzw, b, c);
			TEST_V4(f, 4, 5, 6, 6);

			auto g = Clamp(a, b.xyzw, c);
			TEST_V4(g, 4, 5, 6, 6);

			auto h = Clamp(a, b, c.xyzw);
			TEST_V4(h, 4, 5, 6, 6);
		}

		TEST_METHOD(Vector4Assignment)
		{
			Vector4<int32> a = Make_Vector(2, 3, 4, 5);

			auto b = a.xyzw();
			Vector4<int32> c = a.xyzw;
			Assert::AreEqual(true, std::is_same<decltype(b), decltype(c)>::value);

			Assert::AreEqual(b, c);
		}

		TEST_METHOD(Vector4Cast)
		{
			Vector4<int32> a = Make_Vector(2, 3, 4, 5);
			Vector4<float> b = vector_cast<float>(a);
			TEST_V4(b, 2.0f, 3.0f, 4.0f, 5.0f);

			auto c = vector_cast<float>(a.xyzw);
			Assert::IsTrue(std::is_same_v<decltype(c), decltype(b)>, L"vector_cast<float>() produced an unexpected type.");
		}

		TEST_METHOD(Vector4Dot)
		{
			Vec4f a = Make_Vector(1.0f, 2.0f, 3.0f, 4.0f);
			Vec4f b = Make_Vector(5.0f, 6.0f, 7.0f, 8.0f);
			float dpAB = Dot(a, b); // 5 + 12 + 21 + 32
			Assert::AreEqual(70.0f, dpAB, L"Test dot product between two vectors.");

			float dpBA = Dot(b, a);
			Assert::AreEqual(dpBA, dpAB, L"Test vector dot product commutative.");

			float af = Dot(a.xyzw, b);
			float bf = Dot(a, b.xyzw);
			float cf = Dot(a.xyzw, b.xyzw);
			Assert::AreEqual(dpAB, af, L"af is expected to match dpAB");
			Assert::AreEqual(dpAB, bf, L"bf is expected to match dpAB");
			Assert::AreEqual(dpAB, cf, L"cf is expected to match dpAB");
		}

		TEST_METHOD(Vector4Cross)
		{
			auto a = Make_Vector(1.0f, 2.0f, 3.0f, 1.f);
			auto b = Make_Vector(4.0f, 6.0f, 8.0f, 1.f);

			auto cpAB = Cross(a.xyz, b.xyz);
			TEST_V3(cpAB, 16.0f - 18.0f, 12.0f - 8.0f, 6.0f - 8.0f);
		}

		TEST_METHOD(Vector4Length)
		{
			auto a = Make_Vector(0.0f, 3.0f, 0.0f, 0.0f);

			float length2A = Length2(a);
			Assert::AreEqual(9.0f, length2A, L"Test the vector length squared function.");

			float length = Length(a);
			Assert::AreEqual(3.0f, length, L"Test the vector length.");

			float mag = Magnitude(a);
			Assert::AreEqual(length, mag, L"Test the magnitude of a vector.");

			float l2a = Length2(a.xyz);
			Assert::AreEqual(length2A, l2a, L"l2A is expected to match length2A");
		}
	};

	TEST_CLASS(Vector4Swizzle)
	{
		TEST_METHOD(Vector4Swizzle$$)
		{
			auto a = Make_Vector(2, 3, 4, 5);
			TEST_SWIZZLE_2(a, 2, 2, xx);
			TEST_SWIZZLE_2(a, 2, 3, xy);
			TEST_SWIZZLE_2(a, 2, 4, xz);
			TEST_SWIZZLE_2(a, 2, 5, xw);

			TEST_SWIZZLE_2(a, 3, 2, yx);
			TEST_SWIZZLE_2(a, 3, 3, yy);
			TEST_SWIZZLE_2(a, 3, 4, yz);
			TEST_SWIZZLE_2(a, 3, 5, yw);

			TEST_SWIZZLE_2(a, 4, 2, zx);
			TEST_SWIZZLE_2(a, 4, 3, zy);
			TEST_SWIZZLE_2(a, 4, 4, zz);
			TEST_SWIZZLE_2(a, 4, 5, zw);

			TEST_SWIZZLE_2(a, 5, 2, wx);
			TEST_SWIZZLE_2(a, 5, 3, wy);
			TEST_SWIZZLE_2(a, 5, 4, wz);
			TEST_SWIZZLE_2(a, 5, 5, ww);
		}

		TEST_METHOD(Vector4Swizzle$$$)
		{
			auto a = Make_Vector(2, 3, 4, 5);
			TEST_SWIZZLE_3(a, 2, 2, 2, xxx);
			TEST_SWIZZLE_3(a, 2, 2, 3, xxy);
			TEST_SWIZZLE_3(a, 2, 2, 4, xxz);
			TEST_SWIZZLE_3(a, 2, 2, 5, xxw);
			TEST_SWIZZLE_3(a, 2, 3, 2, xyx);
			TEST_SWIZZLE_3(a, 2, 3, 3, xyy);
			TEST_SWIZZLE_3(a, 2, 3, 4, xyz);
			TEST_SWIZZLE_3(a, 2, 3, 5, xyw);
			TEST_SWIZZLE_3(a, 2, 4, 2, xzx);
			TEST_SWIZZLE_3(a, 2, 4, 3, xzy);
			TEST_SWIZZLE_3(a, 2, 4, 4, xzz);
			TEST_SWIZZLE_3(a, 2, 4, 5, xzw);

			TEST_SWIZZLE_3(a, 2, 5, 2, xwx);
			TEST_SWIZZLE_3(a, 2, 5, 3, xwy);
			TEST_SWIZZLE_3(a, 2, 5, 4, xwz);
			TEST_SWIZZLE_3(a, 2, 5, 5, xww);

			TEST_SWIZZLE_3(a, 3, 2, 2, yxx);
			TEST_SWIZZLE_3(a, 3, 2, 3, yxy);
			TEST_SWIZZLE_3(a, 3, 2, 4, yxz);
			TEST_SWIZZLE_3(a, 3, 2, 5, yxw);
			TEST_SWIZZLE_3(a, 3, 3, 2, yyx);
			TEST_SWIZZLE_3(a, 3, 3, 3, yyy);
			TEST_SWIZZLE_3(a, 3, 3, 4, yyz);
			TEST_SWIZZLE_3(a, 3, 3, 5, yyw);
			TEST_SWIZZLE_3(a, 3, 4, 2, yzx);
			TEST_SWIZZLE_3(a, 3, 4, 3, yzy);
			TEST_SWIZZLE_3(a, 3, 4, 4, yzz);
			TEST_SWIZZLE_3(a, 3, 4, 5, yzw);
			TEST_SWIZZLE_3(a, 3, 5, 2, ywx);
			TEST_SWIZZLE_3(a, 3, 5, 3, ywy);
			TEST_SWIZZLE_3(a, 3, 5, 4, ywz);
			TEST_SWIZZLE_3(a, 3, 5, 5, yww);

			TEST_SWIZZLE_3(a, 4, 2, 2, zxx);
			TEST_SWIZZLE_3(a, 4, 2, 3, zxy);
			TEST_SWIZZLE_3(a, 4, 2, 4, zxz);
			TEST_SWIZZLE_3(a, 4, 2, 5, zxw);
			TEST_SWIZZLE_3(a, 4, 3, 2, zyx);
			TEST_SWIZZLE_3(a, 4, 3, 3, zyy);
			TEST_SWIZZLE_3(a, 4, 3, 4, zyz);
			TEST_SWIZZLE_3(a, 4, 3, 5, zyw);
			TEST_SWIZZLE_3(a, 4, 4, 2, zzx);
			TEST_SWIZZLE_3(a, 4, 4, 3, zzy);
			TEST_SWIZZLE_3(a, 4, 4, 4, zzz);
			TEST_SWIZZLE_3(a, 4, 4, 5, zzw);
			TEST_SWIZZLE_3(a, 4, 5, 2, zwx);
			TEST_SWIZZLE_3(a, 4, 5, 3, zwy);
			TEST_SWIZZLE_3(a, 4, 5, 4, zwz);
			TEST_SWIZZLE_3(a, 4, 5, 5, zww);

			TEST_SWIZZLE_3(a, 5, 2, 2, wxx);
			TEST_SWIZZLE_3(a, 5, 2, 3, wxy);
			TEST_SWIZZLE_3(a, 5, 2, 4, wxz);
			TEST_SWIZZLE_3(a, 5, 2, 5, wxw);
			TEST_SWIZZLE_3(a, 5, 3, 2, wyx);
			TEST_SWIZZLE_3(a, 5, 3, 3, wyy);
			TEST_SWIZZLE_3(a, 5, 3, 4, wyz);
			TEST_SWIZZLE_3(a, 5, 3, 5, wyw);
			TEST_SWIZZLE_3(a, 5, 4, 2, wzx);
			TEST_SWIZZLE_3(a, 5, 4, 3, wzy);
			TEST_SWIZZLE_3(a, 5, 4, 4, wzz);
			TEST_SWIZZLE_3(a, 5, 4, 5, wzw);
			TEST_SWIZZLE_3(a, 5, 5, 2, wwx);
			TEST_SWIZZLE_3(a, 5, 5, 3, wwy);
			TEST_SWIZZLE_3(a, 5, 5, 4, wwz);
			TEST_SWIZZLE_3(a, 5, 5, 5, www);
		}

		TEST_METHOD(Vector4Swizzle$$$$)
		{
			auto a = Make_Vector(2, 3, 4, 5);
			TEST_SWIZZLE_4(a, 2, 2, 2, 2, xxxx);
			TEST_SWIZZLE_4(a, 2, 2, 2, 3, xxxy);
			TEST_SWIZZLE_4(a, 2, 2, 2, 4, xxxz);
			TEST_SWIZZLE_4(a, 2, 2, 2, 5, xxxw);

			TEST_SWIZZLE_4(a, 2, 2, 3, 2, xxyx);
			TEST_SWIZZLE_4(a, 2, 2, 3, 3, xxyy);
			TEST_SWIZZLE_4(a, 2, 2, 3, 4, xxyz);
			TEST_SWIZZLE_4(a, 2, 2, 3, 5, xxyw);

			TEST_SWIZZLE_4(a, 2, 2, 4, 2, xxzx);
			TEST_SWIZZLE_4(a, 2, 2, 4, 3, xxzy);
			TEST_SWIZZLE_4(a, 2, 2, 4, 4, xxzz);
			TEST_SWIZZLE_4(a, 2, 2, 4, 5, xxzw);
			
			TEST_SWIZZLE_4(a, 2, 2, 5, 2, xxwx);
			TEST_SWIZZLE_4(a, 2, 2, 5, 3, xxwy);
			TEST_SWIZZLE_4(a, 2, 2, 5, 4, xxwz);
			TEST_SWIZZLE_4(a, 2, 2, 5, 5, xxww);
			
			TEST_SWIZZLE_4(a, 2, 3, 2, 2, xyxx);
			TEST_SWIZZLE_4(a, 2, 3, 2, 3, xyxy);
			TEST_SWIZZLE_4(a, 2, 3, 2, 4, xyxz);
			TEST_SWIZZLE_4(a, 2, 3, 2, 5, xyxw);

			TEST_SWIZZLE_4(a, 2, 3, 3, 2, xyyx);
			TEST_SWIZZLE_4(a, 2, 3, 3, 3, xyyy);
			TEST_SWIZZLE_4(a, 2, 3, 3, 4, xyyz);
			TEST_SWIZZLE_4(a, 2, 3, 3, 5, xyyw);

			TEST_SWIZZLE_4(a, 2, 3, 4, 2, xyzx);
			TEST_SWIZZLE_4(a, 2, 3, 4, 3, xyzy);
			TEST_SWIZZLE_4(a, 2, 3, 4, 4, xyzz);
			TEST_SWIZZLE_4(a, 2, 3, 4, 5, xyzw);

			TEST_SWIZZLE_4(a, 2, 3, 5, 2, xywx);
			TEST_SWIZZLE_4(a, 2, 3, 5, 3, xywy);
			TEST_SWIZZLE_4(a, 2, 3, 5, 4, xywz);
			TEST_SWIZZLE_4(a, 2, 3, 5, 5, xyww);

			TEST_SWIZZLE_4(a, 2, 4, 2, 2, xzxx);
			TEST_SWIZZLE_4(a, 2, 4, 2, 3, xzxy);
			TEST_SWIZZLE_4(a, 2, 4, 2, 4, xzxz);
			TEST_SWIZZLE_4(a, 2, 4, 2, 5, xzxw);

			TEST_SWIZZLE_4(a, 2, 4, 3, 2, xzyx);
			TEST_SWIZZLE_4(a, 2, 4, 3, 3, xzyy);
			TEST_SWIZZLE_4(a, 2, 4, 3, 4, xzyz);
			TEST_SWIZZLE_4(a, 2, 4, 3, 5, xzyw);

			TEST_SWIZZLE_4(a, 2, 4, 4, 2, xzzx);
			TEST_SWIZZLE_4(a, 2, 4, 4, 3, xzzy);
			TEST_SWIZZLE_4(a, 2, 4, 4, 4, xzzz);
			TEST_SWIZZLE_4(a, 2, 4, 4, 5, xzzw);

			TEST_SWIZZLE_4(a, 2, 4, 5, 2, xzwx);
			TEST_SWIZZLE_4(a, 2, 4, 5, 3, xzwy);
			TEST_SWIZZLE_4(a, 2, 4, 5, 4, xzwz);
			TEST_SWIZZLE_4(a, 2, 4, 5, 5, xzww);

			TEST_SWIZZLE_4(a, 2, 5, 2, 2, xwxx);
			TEST_SWIZZLE_4(a, 2, 5, 2, 3, xwxy);
			TEST_SWIZZLE_4(a, 2, 5, 2, 4, xwxz);
			TEST_SWIZZLE_4(a, 2, 5, 2, 5, xwxw);

			TEST_SWIZZLE_4(a, 2, 5, 3, 2, xwyx);
			TEST_SWIZZLE_4(a, 2, 5, 3, 3, xwyy);
			TEST_SWIZZLE_4(a, 2, 5, 3, 4, xwyz);
			TEST_SWIZZLE_4(a, 2, 5, 3, 5, xwyw);

			TEST_SWIZZLE_4(a, 2, 5, 4, 2, xwzx);
			TEST_SWIZZLE_4(a, 2, 5, 4, 3, xwzy);
			TEST_SWIZZLE_4(a, 2, 5, 4, 4, xwzz);
			TEST_SWIZZLE_4(a, 2, 5, 4, 5, xwzw);

			TEST_SWIZZLE_4(a, 2, 5, 5, 2, xwwx);
			TEST_SWIZZLE_4(a, 2, 5, 5, 3, xwwy);
			TEST_SWIZZLE_4(a, 2, 5, 5, 4, xwwz);
			TEST_SWIZZLE_4(a, 2, 5, 5, 5, xwww);



			TEST_SWIZZLE_4(a, 3, 2, 2, 2, yxxx);
			TEST_SWIZZLE_4(a, 3, 2, 2, 3, yxxy);
			TEST_SWIZZLE_4(a, 3, 2, 2, 4, yxxz);
			TEST_SWIZZLE_4(a, 3, 2, 2, 5, yxxw);

			TEST_SWIZZLE_4(a, 3, 2, 3, 2, yxyx);
			TEST_SWIZZLE_4(a, 3, 2, 3, 3, yxyy);
			TEST_SWIZZLE_4(a, 3, 2, 3, 4, yxyz);
			TEST_SWIZZLE_4(a, 3, 2, 3, 5, yxyw);

			TEST_SWIZZLE_4(a, 3, 2, 4, 2, yxzx);
			TEST_SWIZZLE_4(a, 3, 2, 4, 3, yxzy);
			TEST_SWIZZLE_4(a, 3, 2, 4, 4, yxzz);
			TEST_SWIZZLE_4(a, 3, 2, 4, 5, yxzw);

			TEST_SWIZZLE_4(a, 3, 2, 5, 2, yxwx);
			TEST_SWIZZLE_4(a, 3, 2, 5, 3, yxwy);
			TEST_SWIZZLE_4(a, 3, 2, 5, 4, yxwz);
			TEST_SWIZZLE_4(a, 3, 2, 5, 5, yxww);

			TEST_SWIZZLE_4(a, 3, 3, 2, 2, yyxx);
			TEST_SWIZZLE_4(a, 3, 3, 2, 3, yyxy);
			TEST_SWIZZLE_4(a, 3, 3, 2, 4, yyxz);
			TEST_SWIZZLE_4(a, 3, 3, 2, 5, yyxw);

			TEST_SWIZZLE_4(a, 3, 3, 3, 2, yyyx);
			TEST_SWIZZLE_4(a, 3, 3, 3, 3, yyyy);
			TEST_SWIZZLE_4(a, 3, 3, 3, 4, yyyz);
			TEST_SWIZZLE_4(a, 3, 3, 3, 5, yyyw);

			TEST_SWIZZLE_4(a, 3, 3, 4, 2, yyzx);
			TEST_SWIZZLE_4(a, 3, 3, 4, 3, yyzy);
			TEST_SWIZZLE_4(a, 3, 3, 4, 4, yyzz);
			TEST_SWIZZLE_4(a, 3, 3, 4, 5, yyzw);

			TEST_SWIZZLE_4(a, 3, 3, 5, 2, yywx);
			TEST_SWIZZLE_4(a, 3, 3, 5, 3, yywy);
			TEST_SWIZZLE_4(a, 3, 3, 5, 4, yywz);
			TEST_SWIZZLE_4(a, 3, 3, 5, 5, yyww);

			TEST_SWIZZLE_4(a, 3, 4, 2, 2, yzxx);
			TEST_SWIZZLE_4(a, 3, 4, 2, 3, yzxy);
			TEST_SWIZZLE_4(a, 3, 4, 2, 4, yzxz);
			TEST_SWIZZLE_4(a, 3, 4, 2, 5, yzxw);

			TEST_SWIZZLE_4(a, 3, 4, 3, 2, yzyx);
			TEST_SWIZZLE_4(a, 3, 4, 3, 3, yzyy);
			TEST_SWIZZLE_4(a, 3, 4, 3, 4, yzyz);
			TEST_SWIZZLE_4(a, 3, 4, 3, 5, yzyw);

			TEST_SWIZZLE_4(a, 3, 4, 4, 2, yzzx);
			TEST_SWIZZLE_4(a, 3, 4, 4, 3, yzzy);
			TEST_SWIZZLE_4(a, 3, 4, 4, 4, yzzz);
			TEST_SWIZZLE_4(a, 3, 4, 4, 5, yzzw);

			TEST_SWIZZLE_4(a, 3, 4, 5, 2, yzwx);
			TEST_SWIZZLE_4(a, 3, 4, 5, 3, yzwy);
			TEST_SWIZZLE_4(a, 3, 4, 5, 4, yzwz);
			TEST_SWIZZLE_4(a, 3, 4, 5, 5, yzww);

			TEST_SWIZZLE_4(a, 3, 5, 2, 2, ywxx);
			TEST_SWIZZLE_4(a, 3, 5, 2, 3, ywxy);
			TEST_SWIZZLE_4(a, 3, 5, 2, 4, ywxz);
			TEST_SWIZZLE_4(a, 3, 5, 2, 5, ywxw);

			TEST_SWIZZLE_4(a, 3, 5, 3, 2, ywyx);
			TEST_SWIZZLE_4(a, 3, 5, 3, 3, ywyy);
			TEST_SWIZZLE_4(a, 3, 5, 3, 4, ywyz);
			TEST_SWIZZLE_4(a, 3, 5, 3, 5, ywyw);

			TEST_SWIZZLE_4(a, 3, 5, 4, 2, ywzx);
			TEST_SWIZZLE_4(a, 3, 5, 4, 3, ywzy);
			TEST_SWIZZLE_4(a, 3, 5, 4, 4, ywzz);
			TEST_SWIZZLE_4(a, 3, 5, 4, 5, ywzw);

			TEST_SWIZZLE_4(a, 3, 5, 5, 2, ywwx);
			TEST_SWIZZLE_4(a, 3, 5, 5, 3, ywwy);
			TEST_SWIZZLE_4(a, 3, 5, 5, 4, ywwz);
			TEST_SWIZZLE_4(a, 3, 5, 5, 5, ywww);



			TEST_SWIZZLE_4(a, 4, 2, 2, 2, zxxx);
			TEST_SWIZZLE_4(a, 4, 2, 2, 3, zxxy);
			TEST_SWIZZLE_4(a, 4, 2, 2, 4, zxxz);
			TEST_SWIZZLE_4(a, 4, 2, 2, 5, zxxw);

			TEST_SWIZZLE_4(a, 4, 2, 3, 2, zxyx);
			TEST_SWIZZLE_4(a, 4, 2, 3, 3, zxyy);
			TEST_SWIZZLE_4(a, 4, 2, 3, 4, zxyz);
			TEST_SWIZZLE_4(a, 4, 2, 3, 5, zxyw);

			TEST_SWIZZLE_4(a, 4, 2, 4, 2, zxzx);
			TEST_SWIZZLE_4(a, 4, 2, 4, 3, zxzy);
			TEST_SWIZZLE_4(a, 4, 2, 4, 4, zxzz);
			TEST_SWIZZLE_4(a, 4, 2, 4, 5, zxzw);

			TEST_SWIZZLE_4(a, 4, 2, 5, 2, zxwx);
			TEST_SWIZZLE_4(a, 4, 2, 5, 3, zxwy);
			TEST_SWIZZLE_4(a, 4, 2, 5, 4, zxwz);
			TEST_SWIZZLE_4(a, 4, 2, 5, 5, zxww);

			TEST_SWIZZLE_4(a, 4, 3, 2, 2, zyxx);
			TEST_SWIZZLE_4(a, 4, 3, 2, 3, zyxy);
			TEST_SWIZZLE_4(a, 4, 3, 2, 4, zyxz);
			TEST_SWIZZLE_4(a, 4, 3, 2, 5, zyxw);

			TEST_SWIZZLE_4(a, 4, 3, 3, 2, zyyx);
			TEST_SWIZZLE_4(a, 4, 3, 3, 3, zyyy);
			TEST_SWIZZLE_4(a, 4, 3, 3, 4, zyyz);
			TEST_SWIZZLE_4(a, 4, 3, 3, 5, zyyw);

			TEST_SWIZZLE_4(a, 4, 3, 4, 2, zyzx);
			TEST_SWIZZLE_4(a, 4, 3, 4, 3, zyzy);
			TEST_SWIZZLE_4(a, 4, 3, 4, 4, zyzz);
			TEST_SWIZZLE_4(a, 4, 3, 4, 5, zyzw);

			TEST_SWIZZLE_4(a, 4, 3, 5, 2, zywx);
			TEST_SWIZZLE_4(a, 4, 3, 5, 3, zywy);
			TEST_SWIZZLE_4(a, 4, 3, 5, 4, zywz);
			TEST_SWIZZLE_4(a, 4, 3, 5, 5, zyww);

			TEST_SWIZZLE_4(a, 4, 4, 2, 2, zzxx);
			TEST_SWIZZLE_4(a, 4, 4, 2, 3, zzxy);
			TEST_SWIZZLE_4(a, 4, 4, 2, 4, zzxz);
			TEST_SWIZZLE_4(a, 4, 4, 2, 5, zzxw);

			TEST_SWIZZLE_4(a, 4, 4, 3, 2, zzyx);
			TEST_SWIZZLE_4(a, 4, 4, 3, 3, zzyy);
			TEST_SWIZZLE_4(a, 4, 4, 3, 4, zzyz);
			TEST_SWIZZLE_4(a, 4, 4, 3, 5, zzyw);

			TEST_SWIZZLE_4(a, 4, 4, 4, 2, zzzx);
			TEST_SWIZZLE_4(a, 4, 4, 4, 3, zzzy);
			TEST_SWIZZLE_4(a, 4, 4, 4, 4, zzzz);
			TEST_SWIZZLE_4(a, 4, 4, 4, 5, zzzw);

			TEST_SWIZZLE_4(a, 4, 4, 5, 2, zzwx);
			TEST_SWIZZLE_4(a, 4, 4, 5, 3, zzwy);
			TEST_SWIZZLE_4(a, 4, 4, 5, 4, zzwz);
			TEST_SWIZZLE_4(a, 4, 4, 5, 5, zzww);

			TEST_SWIZZLE_4(a, 4, 5, 2, 2, zwxx);
			TEST_SWIZZLE_4(a, 4, 5, 2, 3, zwxy);
			TEST_SWIZZLE_4(a, 4, 5, 2, 4, zwxz);
			TEST_SWIZZLE_4(a, 4, 5, 2, 5, zwxw);

			TEST_SWIZZLE_4(a, 4, 5, 3, 2, zwyx);
			TEST_SWIZZLE_4(a, 4, 5, 3, 3, zwyy);
			TEST_SWIZZLE_4(a, 4, 5, 3, 4, zwyz);
			TEST_SWIZZLE_4(a, 4, 5, 3, 5, zwyw);

			TEST_SWIZZLE_4(a, 4, 5, 4, 2, zwzx);
			TEST_SWIZZLE_4(a, 4, 5, 4, 3, zwzy);
			TEST_SWIZZLE_4(a, 4, 5, 4, 4, zwzz);
			TEST_SWIZZLE_4(a, 4, 5, 4, 5, zwzw);

			TEST_SWIZZLE_4(a, 4, 5, 5, 2, zwwx);
			TEST_SWIZZLE_4(a, 4, 5, 5, 3, zwwy);
			TEST_SWIZZLE_4(a, 4, 5, 5, 4, zwwz);
			TEST_SWIZZLE_4(a, 4, 5, 5, 5, zwww);



			TEST_SWIZZLE_4(a, 5, 2, 2, 2, wxxx);
			TEST_SWIZZLE_4(a, 5, 2, 2, 3, wxxy);
			TEST_SWIZZLE_4(a, 5, 2, 2, 4, wxxz);
			TEST_SWIZZLE_4(a, 5, 2, 2, 5, wxxw);

			TEST_SWIZZLE_4(a, 5, 2, 3, 2, wxyx);
			TEST_SWIZZLE_4(a, 5, 2, 3, 3, wxyy);
			TEST_SWIZZLE_4(a, 5, 2, 3, 4, wxyz);
			TEST_SWIZZLE_4(a, 5, 2, 3, 5, wxyw);

			TEST_SWIZZLE_4(a, 5, 2, 4, 2, wxzx);
			TEST_SWIZZLE_4(a, 5, 2, 4, 3, wxzy);
			TEST_SWIZZLE_4(a, 5, 2, 4, 4, wxzz);
			TEST_SWIZZLE_4(a, 5, 2, 4, 5, wxzw);

			TEST_SWIZZLE_4(a, 5, 2, 5, 2, wxwx);
			TEST_SWIZZLE_4(a, 5, 2, 5, 3, wxwy);
			TEST_SWIZZLE_4(a, 5, 2, 5, 4, wxwz);
			TEST_SWIZZLE_4(a, 5, 2, 5, 5, wxww);

			TEST_SWIZZLE_4(a, 5, 3, 2, 2, wyxx);
			TEST_SWIZZLE_4(a, 5, 3, 2, 3, wyxy);
			TEST_SWIZZLE_4(a, 5, 3, 2, 4, wyxz);
			TEST_SWIZZLE_4(a, 5, 3, 2, 5, wyxw);

			TEST_SWIZZLE_4(a, 5, 3, 3, 2, wyyx);
			TEST_SWIZZLE_4(a, 5, 3, 3, 3, wyyy);
			TEST_SWIZZLE_4(a, 5, 3, 3, 4, wyyz);
			TEST_SWIZZLE_4(a, 5, 3, 3, 5, wyyw);

			TEST_SWIZZLE_4(a, 5, 3, 4, 2, wyzx);
			TEST_SWIZZLE_4(a, 5, 3, 4, 3, wyzy);
			TEST_SWIZZLE_4(a, 5, 3, 4, 4, wyzz);
			TEST_SWIZZLE_4(a, 5, 3, 4, 5, wyzw);

			TEST_SWIZZLE_4(a, 5, 3, 5, 2, wywx);
			TEST_SWIZZLE_4(a, 5, 3, 5, 3, wywy);
			TEST_SWIZZLE_4(a, 5, 3, 5, 4, wywz);
			TEST_SWIZZLE_4(a, 5, 3, 5, 5, wyww);

			TEST_SWIZZLE_4(a, 5, 4, 2, 2, wzxx);
			TEST_SWIZZLE_4(a, 5, 4, 2, 3, wzxy);
			TEST_SWIZZLE_4(a, 5, 4, 2, 4, wzxz);
			TEST_SWIZZLE_4(a, 5, 4, 2, 5, wzxw);

			TEST_SWIZZLE_4(a, 5, 4, 3, 2, wzyx);
			TEST_SWIZZLE_4(a, 5, 4, 3, 3, wzyy);
			TEST_SWIZZLE_4(a, 5, 4, 3, 4, wzyz);
			TEST_SWIZZLE_4(a, 5, 4, 3, 5, wzyw);

			TEST_SWIZZLE_4(a, 5, 4, 4, 2, wzzx);
			TEST_SWIZZLE_4(a, 5, 4, 4, 3, wzzy);
			TEST_SWIZZLE_4(a, 5, 4, 4, 4, wzzz);
			TEST_SWIZZLE_4(a, 5, 4, 4, 5, wzzw);

			TEST_SWIZZLE_4(a, 5, 4, 5, 2, wzwx);
			TEST_SWIZZLE_4(a, 5, 4, 5, 3, wzwy);
			TEST_SWIZZLE_4(a, 5, 4, 5, 4, wzwz);
			TEST_SWIZZLE_4(a, 5, 4, 5, 5, wzww);

			TEST_SWIZZLE_4(a, 5, 5, 2, 2, wwxx);
			TEST_SWIZZLE_4(a, 5, 5, 2, 3, wwxy);
			TEST_SWIZZLE_4(a, 5, 5, 2, 4, wwxz);
			TEST_SWIZZLE_4(a, 5, 5, 2, 5, wwxw);

			TEST_SWIZZLE_4(a, 5, 5, 3, 2, wwyx);
			TEST_SWIZZLE_4(a, 5, 5, 3, 3, wwyy);
			TEST_SWIZZLE_4(a, 5, 5, 3, 4, wwyz);
			TEST_SWIZZLE_4(a, 5, 5, 3, 5, wwyw);

			TEST_SWIZZLE_4(a, 5, 5, 4, 2, wwzx);
			TEST_SWIZZLE_4(a, 5, 5, 4, 3, wwzy);
			TEST_SWIZZLE_4(a, 5, 5, 4, 4, wwzz);
			TEST_SWIZZLE_4(a, 5, 5, 4, 5, wwzw);

			TEST_SWIZZLE_4(a, 5, 5, 5, 2, wwwx);
			TEST_SWIZZLE_4(a, 5, 5, 5, 3, wwwy);
			TEST_SWIZZLE_4(a, 5, 5, 5, 4, wwwz);
			TEST_SWIZZLE_4(a, 5, 5, 5, 5, wwww);
		}
	};
}