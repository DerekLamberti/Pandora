#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Pandora;
using namespace Pandora::Math;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template <> static std::wstring ToString(const Vec3f& t) { RETURN_WIDE_STRING(t); }
		}
	}
}

namespace TestMath
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(VectorConstruction)
		{
			Vector3<float32> vector = Make_Vector(1.0f, 2.0f, 3.0f);
			Assert::AreEqual(1.0f, vector.X, L"Test vector constructs X correctly.");
			Assert::AreEqual(2.0f, vector.Y, L"Test vector constructs Y correctly.");
			Assert::AreEqual(3.0f, vector.Z, L"Test vector constructs Z correctly.");

			Vec3f vec3f = Make_Vector(4.4f, 5.5f, 6.6f);
			Assert::AreEqual(4.4f, vec3f.X, L"Test vector constructs X correctly.");
			Assert::AreEqual(5.5f, vec3f.Y, L"Test vector constructs Y correctly.");
			Assert::AreEqual(6.6f, vec3f.Z, L"Test vector constructs Z correctly.");

		}

		TEST_METHOD(VectorScaling)
		{
			Vec3f a = Make_Vector(1.0f, 2.0f, 3.0f);			
			Vec3f b = Mul(a, 3.0f);

			Assert::AreEqual(3.0f, b.X, L"Test vector scales X.");
			Assert::AreEqual(6.0f, b.Y, L"Test vector scales Y.");
			Assert::AreEqual(9.0f, b.Z, L"Test vector scales Z.");
		}

		TEST_METHOD(VectorAddition)
		{
			Vec3f a = Make_Vector(1.0f, 2.0f, 3.0f);
			Vec3f b = Make_Vector(10.5f, 11.5f, 12.5f);
			Vec3f c = Add(a, b);

			Assert::AreEqual(11.5f, c.X, L"Test vector adds X components.");
			Assert::AreEqual(13.5f, c.Y, L"Test vector adds Y components.");
			Assert::AreEqual(15.5f, c.Z, L"Test vector adds Z components.");
		}

		TEST_METHOD(VectorMultiplication)
		{
			Vec3f a = Make_Vector(1.0f, 2.0f, 3.0f);
			Vec3f b = Make_Vector(8.0f, 9.0f, 10.0f);
			Vec3f c = Mul(a,b);
			Vec3f d = Mul(b,a);

			Assert::AreEqual(8.0f, c.X, L"Test 2 vectors multiply X component wize.");
			Assert::AreEqual(18.0f, c.Y, L"Test 2 vectors multiply Y component wize.");
			Assert::AreEqual(30.0f, c.Z, L"Test 2 vectors multiply Z component wize.");

			Assert::AreEqual(c, d, L"Test commutivity of Vector multiplication");
		}
	};
}