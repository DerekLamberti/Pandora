#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
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