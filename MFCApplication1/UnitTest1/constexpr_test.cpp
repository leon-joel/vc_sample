#include "stdafx.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	//BEGIN_TEST_MODULE_ATTRIBUTE()
	//	TEST_MODULE_ATTRIBUTE(L"Date", L"2010/6/12")
	//	END_TEST_MODULE_ATTRIBUTE()


	//	TEST_MODULE_INITIALIZE(ModuleInitialize)
	//{
	//	Logger::WriteMessage("In Module Initialize");
	//}

	//TEST_MODULE_CLEANUP(ModuleCleanup)
	//{
	//	Logger::WriteMessage("In Module Cleanup");
	//}

	TEST_CLASS(UnitTest1)
	{
	public:
		
		//UnitTest1()
		//{
		//	Logger::WriteMessage("In UnitTest1");
		//}
		//~UnitTest1()
		//{
		//	Logger::WriteMessage("In ~UnitTest1");
		//}

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize");
		}
		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In Class Cleanup");
		}


		//BEGIN_TEST_METHOD_ATTRIBUTE(TestMethod1)
		//	TEST_OWNER(L"OwnerName")
		//	TEST_PRIORITY(1)
		//END_TEST_METHOD_ATTRIBUTE()
		//TEST_METHOD(TestMethod1)
		//{
		//	Logger::WriteMessage("In TestMethod1");
		//	Assert::AreEqual(0, 0);
		//}

		//TEST_METHOD(TestMethod2)
		//{
		//	Assert::Fail(L"Fail");
		//}

		// constexpr�i�R���p�C�����萔�E�R���p�C���������j�̎���
		TEST_METHOD(TestConstexpr)
		{
			constexpr unsigned N = std::max(10, 8);			// �R���p�C�����萔�͔z��̃T�C�Y��e���v���[�g�����Ƃ��Ďg�p�\
			//const static unsigned N = std::max(10, 8);	// const static �͎g�p�\�̂悤��
			//const unsigned N = std::max(10, 8);			// �����OK
			//unsigned N = std::max(10, 8);					// ����̓r���h�G���[

			constexpr std::array<int, N> arr = { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } };
			static_assert(10 == arr[9], "");

			int sum = 0;
			for (const auto& i : arr) {
				sum += i;
			}

			//constexpr int sum = sum_array(arr);
			Assert::AreEqual(55, sum);

			//double result = sqrt(10.0);
			//static_assert(1.4 == result, "");
			//Assert::AreEqual(5.0, result);
		}

		//template<class T>
		//constexpr static T sum_array(const std::array<T, 10U> const& arr) {
		//	T s = 0;
		//	for (constexpr auto& i : arr) {
		//		s += i;
		//	}
		//	return s;
		//}


		//template < typename T >
		//constexpr T sqrt(T s) const
		//{
		//	T x = s / 2.0;	// VC14(VS2015)�ł� constexpr�֐����ł̕ϐ��錾�͕s�� -> error C3250: 'x': �錾�� 'constexpr' �֐��{�̂ł͋�����Ă��܂���
		//	T prev = 0.0;

		//	while (x != prev)
		//	{
		//		prev = x;
		//		x = (x + s / x) / 2.0;
		//	}
		//	return x;
		//}


		template<typename T>
		constexpr static T square(T const& t) { return t * t; }

		TEST_METHOD(TestConstexprMethod) {
			// �R���p�C���������i�����ł�square�֐��j�ɂ���ăR���p�C�����萔�����߂邱�Ƃ��ł���
			constexpr int s = square(16);

			// static_assert���g���A�Ӑ}�ʂ�ɓ��삵�Ă��Ȃ����Ƃ��R���p�C�����Ɍ��o���邱�Ƃ��ł���
			static_assert(s == 256, "");
			//static_assert(s == 0, "");		// -> error C2338:�ÓI�ȃA�T�[�V������ "" �Ŏ��s���܂���

			// CppUnitTest���g����
			Assert::AreEqual(256, s);
			//Assert::AreEqual(0, s);			// -> Assert �Ɏ��s���܂����B�K�v : <0> ���� : <256>


			// ���� square�֐����i�R���p�C�����ł͂Ȃ��j���ʂɎ��s���邱�Ƃ��o����
			int i = 15;
			int s2 = square(i);
			Assert::AreEqual(225, s2);
			//static_assert(s2 == 225, "");		// -> s2���萔����Ȃ��̂ŁAstatic_assert�͎g���Ȃ�
		}
	};
}