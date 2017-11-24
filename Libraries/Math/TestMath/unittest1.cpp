#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template <> static std::wstring ToString(const Pandora::Math::Vec3i& t) { RETURN_WIDE_STRING(t); }
			template <> static std::wstring ToString(const Pandora::Math::Vec3f& t) { RETURN_WIDE_STRING(t); }
			template <> static std::wstring ToString(const Pandora::Math::Vec4f& t) { RETURN_WIDE_STRING(t); }
		}
	}
}

namespace TestMath
{		
	using namespace Pandora;
	using namespace Pandora::Math;

	TEST_CLASS(Vector3Type)
	{
	public:
		
		TEST_METHOD(Vector3Construction)
		{
			Vector3<float32> vector = Make_Vector(1.0f, 2.0f, 3.0f);
			Assert::AreEqual(1.0f, vector.x, L"Test vector constructs X correctly.");
			Assert::AreEqual(2.0f, vector.y, L"Test vector constructs Y correctly.");
			Assert::AreEqual(3.0f, vector.z, L"Test vector constructs Z correctly.");

			Vec3f vec3f = Make_Vector(4.4f, 5.5f, 6.6f);
			Assert::AreEqual(4.4f, vec3f.x, L"Test vector constructs X correctly.");
			Assert::AreEqual(5.5f, vec3f.y, L"Test vector constructs Y correctly.");
			Assert::AreEqual(6.6f, vec3f.z, L"Test vector constructs Z correctly.");

			Vec3f copy(vec3f);
			Assert::AreEqual(vec3f, copy, L"Test vector copy construction.");
		}

		TEST_METHOD(Vector3Scaling)
		{
			Vec3f a = Make_Vector(1.0f, 2.0f, 3.0f);
			Vec3f b = a * 3.0f;

			Assert::AreEqual(3.0f, b.x, L"Test vector scales X.");
			Assert::AreEqual(6.0f, b.y, L"Test vector scales Y.");
			Assert::AreEqual(9.0f, b.z, L"Test vector scales Z.");
		}

		TEST_METHOD(Vector3Addition)
		{
			Vec3f a = Make_Vector(1.0f, 2.0f, 3.0f);
			Vec3f b = Make_Vector(10.5f, 11.5f, 12.5f);
			Vec3f c = a + b;

			Assert::AreEqual(11.5f, c.x, L"Test vector adds X components.");
			Assert::AreEqual(13.5f, c.y, L"Test vector adds Y components.");
			Assert::AreEqual(15.5f, c.z, L"Test vector adds Z components.");
		}

		TEST_METHOD(Vector3Multiplication)
		{
			Vec3f a = Make_Vector(1.0f, 2.0f, 3.0f);
			Vec3f b = Make_Vector(8.0f, 9.0f, 10.0f);
			Vec3f c = a * b;
			Vec3f d = b * a;
			
			Assert::AreEqual(8.0f, c.x, L"Test 2 vectors multiply X component wize.");
			Assert::AreEqual(18.0f, c.y, L"Test 2 vectors multiply Y component wize.");
			Assert::AreEqual(30.0f, c.z, L"Test 2 vectors multiply Z component wize.");
			
			Assert::AreEqual(c, d, L"Test commutivity of Vector multiplication");
		}

		TEST_METHOD(Vector3DotProduct)
		{
			Vec3f a = Make_Vector(1.0f, 2.0f, 3.0f);
			Vec3f b = Make_Vector(4.0f, 6.0f, 8.0f);
			float dpAB = Dot(a, b);

			Assert::AreEqual(40.0f, dpAB, L"Test dot product between two vectors.");


			float dpBA = Dot(b, a);
			Assert::AreEqual(dpBA, dpAB, L"Test vector dot product commutative.");
		}

		TEST_METHOD(Vector3CrossProduct)
		{
			Vec3f a = Make_Vector(1.0f, 2.0f, 3.0f);
			Vec3f b = Make_Vector(4.0f, 6.0f, 8.0f);

			Vec3f cpAB = Cross(a, b);
			Vec3f expectedAB = Make_Vector(16.0f - 18.0f, 12.0f - 8.0f, 6.0f - 8.0f);
			Assert::AreEqual(expectedAB, cpAB, L"Test cross product between two vector3.");

			Vec3f cpBA = Cross(b, a);
			Vec3f expectedBA = Make_Vector(18.0f - 16.0f, 8.0f - 12.0f, 8.0f - 6.0f);
			Assert::AreEqual(expectedBA, cpBA, L"Test vector cross product commutative.");
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
		}

		TEST_METHOD(Vector3Normalize)
		{
			Vec3f vec = Make_Vector(23.0f, 43.0f, 14.0f);

			auto normal = Normalize(vec);
			float nLen = Length(normal);

			Assert::AreEqual(1.0f, nLen, 0.0001f, L"Test vector normalization.");

		}

		TEST_METHOD(Vector3Min)
		{
			auto a = Make_Vector(4, 5, 6);
			auto b = Make_Vector(6, 5, 4);
			auto c = Min(a, b);

			Assert::AreEqual(4, c.x, L"Test min component x.");
			Assert::AreEqual(5, c.y, L"Test min component y.");
			Assert::AreEqual(4, c.z, L"Test min component z.");
		}

		TEST_METHOD(Vector3Max)
		{
			auto a = Make_Vector(4, 5, 6);
			auto b = Make_Vector(6, 5, 4);
			auto c = Max(a, b);

			Assert::AreEqual(6, c.x, L"Test max component x.");
			Assert::AreEqual(5, c.y, L"Test max component y.");
			Assert::AreEqual(6, c.z, L"Test max component z.");
		}

		TEST_METHOD(Vector3Clamp)
		{
			auto a = Make_Vector(3, 5, 7);
			auto b = Make_Vector(4, 4, 4);
			auto c = Make_Vector(6, 6, 6);

			auto d = Clamp(a, b, c);

			Assert::AreEqual(4, d.x, L"Test clamped value x.");
			Assert::AreEqual(5, d.y, L"Test clamped value y.");
			Assert::AreEqual(6, d.z, L"Test clamped value z.");
		}
	};

	TEST_CLASS(Vector3Swizzle)
	{
		TEST_METHOD(Vector3SwizzleXX)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(3, a.xx.x);
			Assert::AreEqual(3, a.xx.y);
		}

		TEST_METHOD(Vector3SwizzleXY)
		{
			auto a = Make_Vector(3, 4, 5);
			Assert::AreEqual(3, a.xy.x);
			Assert::AreEqual(4, a.xy.y);
		}

		TEST_METHOD(Vector3SwizzleXZ)
		{
			auto a = Make_Vector(3, 4, 5);
			Assert::AreEqual(3, a.xz.x);
			Assert::AreEqual(5, a.xz.y);
		}

		TEST_METHOD(Vector3SwizzleYX)
		{
			auto a = Make_Vector(3, 4, 5);
			Assert::AreEqual(4, a.yx.x);
			Assert::AreEqual(3, a.yx.y);
		}

		TEST_METHOD(Vector3SwizzleYY)
		{
			auto a = Make_Vector(3, 4, 5);
			Assert::AreEqual(4, a.yy.x);
			Assert::AreEqual(4, a.yy.y);
		}

		TEST_METHOD(Vector3SwizzleYZ)
		{
			auto a = Make_Vector(3, 4, 5);
			Assert::AreEqual(4, a.yz.x);
			Assert::AreEqual(5, a.yz.y);
		}

		TEST_METHOD(Vector3SwizzleZX)
		{
			auto a = Make_Vector(3, 4, 5);
			Assert::AreEqual(5, a.zx.x);
			Assert::AreEqual(3, a.zx.y);
		}
		TEST_METHOD(Vector3SwizzleZY)
		{
			auto a = Make_Vector(3, 4, 5);
			Assert::AreEqual(5, a.zy.x);
			Assert::AreEqual(4, a.zy.y);
		}

		TEST_METHOD(Vector3SwizzleZZ)
		{
			auto a = Make_Vector(3, 4, 5);
			Assert::AreEqual(5, a.zz.x);
			Assert::AreEqual(5, a.zz.y);
		}

		TEST_METHOD(Vector3SwizzleXXX)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(3, a.xxx.x);
			Assert::AreEqual(3, a.xxx.y);
			Assert::AreEqual(3, a.xxx.z);
		}

		TEST_METHOD(Vector3SwizzleXXY)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(3, a.xxy.x);
			Assert::AreEqual(3, a.xxy.y);
			Assert::AreEqual(4, a.xxy.z);
		}

		TEST_METHOD(Vector3SwizzleXXZ)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(3, a.xxz.x);
			Assert::AreEqual(3, a.xxz.y);
			Assert::AreEqual(5, a.xxz.z);
		}

		TEST_METHOD(Vector3SwizzleXYX)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(3, a.xyx.x);
			Assert::AreEqual(4, a.xyx.y);
			Assert::AreEqual(3, a.xyx.z);
		}

		TEST_METHOD(Vector3SwizzleXYY)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(3, a.xyy.x);
			Assert::AreEqual(4, a.xyy.y);
			Assert::AreEqual(4, a.xyy.z);
		}

		TEST_METHOD(Vector3SwizzleXYZ)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(3, a.xyz.x);
			Assert::AreEqual(4, a.xyz.y);
			Assert::AreEqual(5, a.xyz.z);
		}

		TEST_METHOD(Vector3SwizzleXZX)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(3, a.xzx.x);
			Assert::AreEqual(5, a.xzx.y);
			Assert::AreEqual(3, a.xzx.z);
		}

		TEST_METHOD(Vector3SwizzleXZY)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(3, a.xzy.x);
			Assert::AreEqual(5, a.xzy.y);
			Assert::AreEqual(4, a.xzy.z);
		}

		TEST_METHOD(Vector3SwizzleXZZ)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(3, a.xzz.x);
			Assert::AreEqual(5, a.xzz.y);
			Assert::AreEqual(5, a.xzz.z);
		}

		TEST_METHOD(Vector3SwizzleYXX)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(4, a.yxx.x);
			Assert::AreEqual(3, a.yxx.y);
			Assert::AreEqual(3, a.yxx.z);
		}

		TEST_METHOD(Vector3SwizzleYXY)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(4, a.yxy.x);
			Assert::AreEqual(3, a.yxy.y);
			Assert::AreEqual(4, a.yxy.z);
		}

		TEST_METHOD(Vector3SwizzleYXZ)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(4, a.yxz.x);
			Assert::AreEqual(3, a.yxz.y);
			Assert::AreEqual(5, a.yxz.z);
		}

		TEST_METHOD(Vector3SwizzleYYX)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(4, a.yyx.x);
			Assert::AreEqual(4, a.yyx.y);
			Assert::AreEqual(3, a.yyx.z);
		}

		TEST_METHOD(Vector3SwizzleYYY)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(4, a.yyy.x);
			Assert::AreEqual(4, a.yyy.y);
			Assert::AreEqual(4, a.yyy.z);
		}

		TEST_METHOD(Vector3SwizzleYYZ)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(4, a.yyz.x);
			Assert::AreEqual(4, a.yyz.y);
			Assert::AreEqual(5, a.yyz.z);
		}

		TEST_METHOD(Vector3SwizzleYZX)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(4, a.yzx.x);
			Assert::AreEqual(5, a.yzx.y);
			Assert::AreEqual(3, a.yzx.z);
		}

		TEST_METHOD(Vector3SwizzleYZY)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(4, a.yzy.x);
			Assert::AreEqual(5, a.yzy.y);
			Assert::AreEqual(4, a.yzy.z);
		}

		TEST_METHOD(Vector3SwizzleYZZ)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(4, a.yzz.x);
			Assert::AreEqual(5, a.yzz.y);
			Assert::AreEqual(5, a.yzz.z);
		}

		TEST_METHOD(Vector3SwizzleZXX)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(5, a.zxx.x);
			Assert::AreEqual(3, a.zxx.y);
			Assert::AreEqual(3, a.zxx.z);
		}

		TEST_METHOD(Vector3SwizzleZXY)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(5, a.zxy.x);
			Assert::AreEqual(3, a.zxy.y);
			Assert::AreEqual(4, a.zxy.z);
		}

		TEST_METHOD(Vector3SwizzleZXZ)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(5, a.zxz.x);
			Assert::AreEqual(3, a.zxz.y);
			Assert::AreEqual(5, a.zxz.z);
		}

		TEST_METHOD(Vector3SwizzleZYX)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(5, a.zyx.x);
			Assert::AreEqual(4, a.zyx.y);
			Assert::AreEqual(3, a.zyx.z);
		}

		TEST_METHOD(Vector3SwizzleZYY)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(5, a.zyy.x);
			Assert::AreEqual(4, a.zyy.y);
			Assert::AreEqual(4, a.zyy.z);
		}

		TEST_METHOD(Vector3SwizzleZYZ)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(5, a.zyz.x);
			Assert::AreEqual(4, a.zyz.y);
			Assert::AreEqual(5, a.zyz.z);
		}

		TEST_METHOD(Vector3SwizzleZZX)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(5, a.zzx.x);
			Assert::AreEqual(5, a.zzx.y);
			Assert::AreEqual(3, a.zzx.z);
		}
		TEST_METHOD(Vector3SwizzleZZY)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(5, a.zzy.x);
			Assert::AreEqual(5, a.zzy.y);
			Assert::AreEqual(4, a.zzy.z);
		}
		TEST_METHOD(Vector3SwizzleZZZ)
		{
			auto a = Make_Vector(3, 4, 5);

			Assert::AreEqual(5, a.zzz.x);
			Assert::AreEqual(5, a.zzz.y);
			Assert::AreEqual(5, a.zzz.z);
		}
		TEST_METHOD(Vector3SwizzleAdd)
		{
			auto a = Make_Vector(3, 4, 5);
			auto b = Make_Vector(7, 8, 9);

   			auto c = a.xxx + b;
			auto d = b + a.xxx;

			Assert::AreEqual(10, c.x);
			Assert::AreEqual(11, c.y);
			Assert::AreEqual(12, c.z);
			Assert::AreEqual(c.x, d.x);
			Assert::AreEqual(c.y, d.y);
			Assert::AreEqual(c.z, d.z);
		}
		TEST_METHOD(Vector3SwizzleSub)
		{
			auto a = Make_Vector(3, 4, 5);
			auto b = Make_Vector(9, 8, 7);

			auto c = a.xyz - b;
			auto d = b - a.xyz;

			Assert::AreEqual(-6, c.x);
			Assert::AreEqual(-4, c.y);
			Assert::AreEqual(-2, c.z);
			Assert::AreEqual(6, d.x);
			Assert::AreEqual(4, d.y);
			Assert::AreEqual(2, d.z);
		}

		TEST_METHOD(Vector3SwizzleMullVector)
		{
			auto a = Make_Vector(3, 4, 5);
			auto b = Make_Vector(7, 8, 9);

			auto c = a.xyz * b.xyz;
			Assert::AreEqual(21, c.x);
			Assert::AreEqual(32, c.y);
			Assert::AreEqual(45, c.z);
		}

		TEST_METHOD(Vector3SwizzleMulScalar)
		{
			auto a = Make_Vector(3, 4, 5);

			auto b = a.xyz * 3;

			Assert::AreEqual(9, b.x);
			Assert::AreEqual(12, b.y);
			Assert::AreEqual(15, b.z);
		}

		TEST_METHOD(Vector3SwizzleDivVector)
		{
			auto a = Make_Vector(21, 32, 45);
			auto b = Make_Vector(3, 4, 5);
			auto c = a / b;

			Assert::AreEqual(7, c.x);
			Assert::AreEqual(8, c.y);
			Assert::AreEqual(9, c.z);
		}

		TEST_METHOD(Vector3SwizzleDivScalar)
		{
			auto a = Make_Vector(9, 12, 15);

			auto b = a.xyz / 3;

			Assert::AreEqual(3, b.x);
			Assert::AreEqual(4, b.y);
			Assert::AreEqual(5, b.z);
		}

		TEST_METHOD(Vector3SwizzleDot)
		{
			auto a = Make_Vector(3, 4, 5);
			auto b = Make_Vector(7, 8, 9);

			auto c = Dot(a.xyz, b);
			auto d = Dot(a, b.xyz);
			auto e = Dot(a.xyz, b.xyz);

			Assert::AreEqual(98, c);
			Assert::AreEqual(98, d);
			Assert::AreEqual(98, e);
		}

		TEST_METHOD(Vector3SwizzleCross)
		{
			auto a = Make_Vector(3, 4, 5);
			auto b = Make_Vector(7, 8, 9);

			auto c = Cross(a, b);
			auto d = Cross(a.xyz, b.xyz);
			auto e = Cross(a.xyz, b);
			auto f = Cross(a, b.xyz);

			Assert::AreEqual(c, d);
			Assert::AreEqual(c, e);
			Assert::AreEqual(c, f);
		}

		TEST_METHOD(VectorSwizzleLength2)
		{
			auto a = Make_Vector(3.0f, 4.0f, 5.0f);

			auto c = Length2(a);
			auto d = Length2(a.xyz);
			auto e = Length2(a.yxz);
			auto f = Length2(a.zxy);

			Assert::AreEqual(c, d);
			Assert::AreEqual(c, e);
			Assert::AreEqual(c, f);
		}
	};

	TEST_CLASS(Vector4Type)
	{
		TEST_METHOD(Vector4Construction)
		{
			auto vec = Make_Vector(1.0f, 2.0f, 3.0f, 4.0f);
			Assert::AreEqual(1.0f, vec.x, L"Test Vector4 x construction");
			Assert::AreEqual(2.0f, vec.y, L"Test Vector4 y construction");
			Assert::AreEqual(3.0f, vec.z, L"Test Vector4 z construction");
			Assert::AreEqual(4.0f, vec.w, L"Test Vector4 w construction");

			auto copy = Vec4f(vec);
			Assert::AreEqual(vec, copy, L"Test vector4 copy construtor.");
		}

		TEST_METHOD(Vector4Scaling)
		{
			Vec4f a = Make_Vector(1.0f, 2.0f, 3.0f, 4.0f);
			Vec4f b = a * 3.0f;

			Assert::AreEqual(3.0f, b.x, L"Test vector scales X.");
			Assert::AreEqual(6.0f, b.y, L"Test vector scales Y.");
			Assert::AreEqual(9.0f, b.z, L"Test vector scales Z.");
			Assert::AreEqual(12.0f, b.w, L"Test vector scales W.");
		}

		TEST_METHOD(Vector4Addition)
		{
			Vec4f a = Make_Vector(1.0f, 2.0f, 3.0f, 4.0f);
			Vec4f b = Make_Vector(10.5f, 11.5f, 12.5f, 13.5f);
			Vec4f c = a + b;

			Assert::AreEqual(11.5f, c.x, L"Test vector adds X components.");
			Assert::AreEqual(13.5f, c.y, L"Test vector adds Y components.");
			Assert::AreEqual(15.5f, c.z, L"Test vector adds Z components.");
			Assert::AreEqual(17.5f, c.w, L"Test vector adds W components.");
		}

		TEST_METHOD(Vector4Multiplication)
		{
			Vec4f a = Make_Vector(1.0f, 2.0f, 3.0f, 4.0f);
			Vec4f b = Make_Vector(8.0f, 9.0f, 10.0f, 11.0f);
			Vec4f c = a * b;
			Vec4f d = b * a;

			Assert::AreEqual(8.0f, c.x, L"Test 2 vectors multiply X componentwise.");
			Assert::AreEqual(18.0f, c.y, L"Test 2 vectors multiply Y componentwise.");
			Assert::AreEqual(30.0f, c.z, L"Test 2 vectors multiply Z componentwise.");
			Assert::AreEqual(44.0f, c.w, L"Test 2 vectors multiply W componentwise.");

			Assert::AreEqual(c, d, L"Test commutivity of Vector multiplication");
		}

		TEST_METHOD(Vector4Min)
		{
			auto a = Make_Vector(4, 5, 6, 7);
			auto b = Make_Vector(7, 6, 5, 4);
			auto c = Min(a, b);

			Assert::AreEqual(4, c.x, L"Test min component x.");
			Assert::AreEqual(5, c.y, L"Test min component y.");
			Assert::AreEqual(5, c.z, L"Test min component z.");
			Assert::AreEqual(4, c.w, L"Test min component w.");
		}

		TEST_METHOD(Vector4Max)
		{
			auto a = Make_Vector(4, 5, 6, 7);
			auto b = Make_Vector(7, 6, 5, 4);
			auto c = Max(a, b);

			Assert::AreEqual(7, c.x, L"Test max component x.");
			Assert::AreEqual(6, c.y, L"Test max component y.");
			Assert::AreEqual(6, c.z, L"Test max component z.");
			Assert::AreEqual(7, c.w, L"Test max component w.");
		}

		TEST_METHOD(Vector4Clamp)
		{
			auto a = Make_Vector(3, 5, 7, 9);
			auto b = Make_Vector(4, 4, 4, 4);
			auto c = Make_Vector(6, 6, 6, 6);

			auto d = Clamp(a, b, c);

			Assert::AreEqual(4, d.x, L"Test clamped value x.");
			Assert::AreEqual(5, d.y, L"Test clamped value y.");
			Assert::AreEqual(6, d.z, L"Test clamped value z.");
			Assert::AreEqual(6, d.z, L"Test clamped value w.");
		}

	};
}