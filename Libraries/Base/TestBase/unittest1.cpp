#include "stdafx.h"
#include "CppUnitTest.h"
#include "../BaseTypes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			using namespace Pandora;

			template<> static std::wstring ToString<Pandora::float16>(const float16& t) { RETURN_WIDE_STRING(t); }
			template<> inline std::wstring ToString<Pandora::float16>(const float16* t) { RETURN_WIDE_STRING(t); }
			template<> inline std::wstring ToString<Pandora::float16>(float16* t) { RETURN_WIDE_STRING(t); }
		}
	}
}
namespace UnitTests
{		
	using namespace Pandora;
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestBasicTypeSizes)
		{
			Assert::AreEqual(size_t{1}, sizeof(int8), L"Test int8 is 1 byte.");
			Assert::AreEqual(size_t{1}, sizeof(uint8), L"Test uint8 is 1 byte.");

			Assert::AreEqual(size_t{2}, sizeof(int16), L"Test int16 is 2 bytes.");
			Assert::AreEqual(size_t{2}, sizeof(uint16), L"Test uint16 is 2 bytes.");

			Assert::AreEqual(size_t{4}, sizeof(int32), L"Test int32 is 4 bytes.");
			Assert::AreEqual(size_t{4}, sizeof(uint32), L"Test uint32 is 4 bytes.");

			Assert::AreEqual(size_t{8}, sizeof(int64), L"Test int64 is 8 bytes.");
			Assert::AreEqual(size_t{8}, sizeof(uint64), L"Test uint64 is 8 bytes.");

			Assert::AreEqual(size_t{2}, sizeof(float16), L"Test float16 is 2 bytes.");
			Assert::AreEqual(size_t{4}, sizeof(float32), L"Test float32 is 4 bytes.");
			Assert::AreEqual(size_t{8}, sizeof(float64), L"Test float64 is 8 bytes.");

			// TODO: Your test code here
		}

		bool ConvertDownAndBack(float x)
		{
			float16 h = half_cast<float16>(x);
			float f = half_cast<float>(h);
			return f == h;
		}

		TEST_METHOD(TestHalfPrecisionFloat)
		{
			float32 zerof = 0.0f;
			float16 zeroh = half_cast<float16>(zerof);

			Assert::AreEqual(0.0_h, zeroh, L"Test float16 -> float16 comparison.");
			Assert::AreEqual(1.0_h, half_cast<float16>(1.0f), L"Test float16 value 1.0f conversion.");
			Assert::AreEqual(2.0_h, half_cast<float16>(2.0f), L"Test float16 value 2.0f conversion.");
			Assert::AreEqual(4.0_h, half_cast<float16>(4.0f), L"Test float16 value 4.0f conversion.");
			Assert::AreEqual(8.0_h, half_cast<float16>(8.0f), L"Test float16 value 8.0f conversion.");
			Assert::AreEqual(16.0_h, half_cast<float16>(16.0f), L"Test float16 value 16.0f conversion.");

			Assert::IsTrue(ConvertDownAndBack(1.0f), L"Test converting 1.0f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(2.0f), L"Test converting 2.0f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(4.0f), L"Test converting 4.0f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(8.0f), L"Test converting 8.0f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(16.0f), L"Test converting 16.0f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(32.0f), L"Test converting 32.0f to half and back to float32.");

			Assert::IsTrue(ConvertDownAndBack(-1.0f), L"Test converting -1.0f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(-2.0f), L"Test converting -2.0f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(-4.0f), L"Test converting -4.0f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(-8.0f), L"Test converting -8.0f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(-16.0f), L"Test converting -16.0f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(-32.0f), L"Test converting -32.0f to half and back to float32.");

			Assert::IsTrue(ConvertDownAndBack(0.1f), L"Test converting 0.1f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(0.2f), L"Test converting 0.2f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(0.4f), L"Test converting 0.4f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(0.8f), L"Test converting 0.8f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(0.16f), L"Test converting 0.16f to half and back to float32.");
			Assert::IsTrue(ConvertDownAndBack(0.32f), L"Test converting 0.32f to half and back to float32.");

			Assert::AreEqual(0.5_h, half_cast<float16>(0.25_h * 2), L"Test float16 multiplication");
			Assert::AreEqual(0.75_h, half_cast<float16>(0.5_h + 0.25_h), L"Test float16 addition.");
		}

	};
}