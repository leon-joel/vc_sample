#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MiscUnitTest
{
	template<typename T, typename P>
	tostream& operator<<(tostream& os, const boost::numeric::interval<T, P>& itv)
	{
		return os << _T("[from ") << itv.lower() <<
			_T(" to ") << itv.upper() << _T("]");
	}

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

	TEST_CLASS(BoostTest)
	{
	public:

		//UnitTest1()
		//{
		//	Logger::WriteMessage("In BoostTest");
		//}
		//~UnitTest1()
		//{
		//	Logger::WriteMessage("In ~BoostTest");
		//}

		//TEST_CLASS_INITIALIZE(ClassInitialize)
		//{
		//	Logger::WriteMessage("In Class Initialize");
		//}
		//TEST_CLASS_CLEANUP(ClassCleanup)
		//{
		//	Logger::WriteMessage("In Class Cleanup");
		//}


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

		TEST_METHOD(TestIota)
		{
			// iota�ŘA�Ԃ𐶐���array�ɑ��
			std::array<int, 3> arr;
			std::iota(arr.begin(), arr.end(), -1);

			Assert::AreEqual(-1, arr[0]);
			Assert::AreEqual(0, arr[1]);
			Assert::AreEqual(1, arr[2]);
		}

		TEST_METHOD(TestBoostIota)
		{
			// [boost��] iota�ŘA�Ԃ𐶐���array�ɑ��
			std::array<int, 3> arr;
			boost::iota(arr, 1);

			Assert::AreEqual((size_t)3, arr.size());

			Assert::AreEqual(1, arr[0]);
			Assert::AreEqual(2, arr[1]);
			Assert::AreEqual(3, arr[2]);
		}

		// boost/filesystem.hpp �̃e�X�g�� misc_test.cpp �̕��ɋL��

		TEST_METHOD(BoostVectorErase)
		{
			std::vector<int> vec(3);	// �T�C�Y��3
			boost::iota(vec, 1);		// 1����n�܂�A�Ԃ��i�[
			Assert::AreEqual((size_t)3, vec.size());

			auto it = boost::find(vec, 2);		// 2��T��
			vec.erase(vec.begin(), it);			// 2�̎�O�܂ŗv�f����菜��

			Assert::AreEqual((size_t)2, vec.size());
			Assert::AreEqual(2, vec[0]);
			Assert::AreEqual(3, vec[1]);
		}

		TEST_METHOD(BoostClampTest)
		{
			Assert::AreEqual(0, boost::algorithm::clamp(-1, 0, 10));
			Assert::AreEqual(0, boost::algorithm::clamp(0, 0, 10));
			Assert::AreEqual(5, boost::algorithm::clamp(5, 0, 10));
			Assert::AreEqual(10, boost::algorithm::clamp(10, 0, 10));
			Assert::AreEqual(10, boost::algorithm::clamp(11, 0, 10));

			Assert::AreEqual(0.0, boost::algorithm::clamp(-1.0, 0.0, 10.0));
			Assert::AreEqual(0.0, boost::algorithm::clamp(0.0, 0.0, 10.0));
			Assert::AreEqual(5.0, boost::algorithm::clamp(5.0, 0.0, 10.0));
			Assert::AreEqual(10.0, boost::algorithm::clamp(10.0, 0.0, 10.0));
			Assert::AreEqual(10.0, boost::algorithm::clamp(11.0, 0.0, 10.0));
		}

		TEST_METHOD(BoostRangeClampTest)
		{
			std::array<int, 4> arr;
			boost::iota(arr, -1);	// -1, 0, 1, 2

			boost::algorithm::clamp_range(arr, arr.begin(), 0, 1);
			Assert::AreEqual(0, arr[0]);
			Assert::AreEqual(0, arr[1]);
			Assert::AreEqual(1, arr[2]);
			Assert::AreEqual(1, arr[3]);
		}

		TEST_METHOD(BoostIntervalTest)
		{
			// Let's Boost��� http://www.kmonos.net/alang/boost/classes/interval.html

			boost::numeric::interval<int> x(0, 100);
			boost::numeric::interval<int> y(-20, 55);
			boost::numeric::interval<int> z = x*y;
			tostringstream ost;
			ost << x << " * " << y << " = " << z << std::endl;
			// ��interval�p�� <<���Z�q����̕��Œ�`�����̂ŁA����ȂɃX�b�L��������

			// �l����ԂɊ܂܂�Ă��邩�H
			ost << "is 20 in " << x << " ? " << std::boolalpha << in(20, x) << std::endl;

			// ��Ԃɓ���v�f����������ǂ����H
			ost << boost::numeric::singleton(boost::numeric::interval<int>(1, 1)) << std::endl;

			// ��ԂƋ�Ԃ̋��ʕ���
			// �� hull �� std::make_pair �I�ȕ֗��֐��ł�
			ost << boost::numeric::intersect(boost::numeric::hull(-2.0, 6.0), boost::numeric::hull(5.5, -4.0)) << std::endl;
			// -> [from -2 to 5.5]

			ost << boost::numeric::intersect(boost::numeric::hull(-2, 6), boost::numeric::hull(6, 7)) << std::endl;
			// -> [from 6 to 6]

			try {
				auto itv = boost::numeric::intersect(boost::numeric::hull(-2, 6), boost::numeric::hull(7, 8));
				// ������exception����яo���Ă���I�I�I -> boost::interval: empty interval created
				ost << itv << std::endl;
			} catch (std::exception ex) {
				ost << ex.what() << std::endl;
			}

			Logger::WriteMessage(ost.str().c_str());
		}

	};
}