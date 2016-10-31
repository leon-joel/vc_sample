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

		// constexpr（コンパイル時定数・コンパイル時処理）の実験
		TEST_METHOD(TestConstexpr)
		{
			constexpr unsigned N = std::max(10, 8);			// コンパイル時定数は配列のサイズやテンプレート引数として使用可能
			//const static unsigned N = std::max(10, 8);	// const static は使用可能のようだ
			//const unsigned N = std::max(10, 8);			// これもOK
			//unsigned N = std::max(10, 8);					// これはビルドエラー

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
		//	T x = s / 2.0;	// VC14(VS2015)では constexpr関数内での変数宣言は不可 -> error C3250: 'x': 宣言は 'constexpr' 関数本体では許可されていません
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
			// コンパイル時処理（ここではsquare関数）によってコンパイル時定数を求めることができる
			constexpr int s = square(16);

			// static_assertを使い、意図通りに動作していないことをコンパイル時に検出することもできる
			static_assert(s == 256, "");
			//static_assert(s == 0, "");		// -> error C2338:静的なアサーションは "" で失敗しました

			// CppUnitTestも使える
			Assert::AreEqual(256, s);
			//Assert::AreEqual(0, s);			// -> Assert に失敗しました。必要 : <0> 実際 : <256>


			// 同じ square関数を（コンパイル時ではなく）普通に実行することも出来る
			int i = 15;
			int s2 = square(i);
			Assert::AreEqual(225, s2);
			//static_assert(s2 == 225, "");		// -> s2が定数じゃないので、static_assertは使えない
		}
	};
}