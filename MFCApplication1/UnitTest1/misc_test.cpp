#include "stdafx.h"

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

	TEST_CLASS(MiscTest)
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

		TEST_METHOD(TestCString)
		{
			// 0�l�߂̌����w��
			CString sFormat;
			sFormat.Format(_T("%%s%%s%%0%dd%%s"), 2);
			//Logger::WriteMessage(sFormat);	// -> %s%s%02d%s

			// �t�H�[�}�b�g
			CString sReadPath;
			sReadPath.Format(sFormat,
							 _T("dir"),
							 _T("Title"),
							 9,
							 _T("ext"));
			//Logger::WriteMessage(sReadPath);	// -> dirTitle09ext
	

			// 0�l�ߌ����w�肵�A�t�H�[�}�b�g����
			CString sReadPath2;
			sReadPath2.Format(_T("%s%s%0*d%s"),
							  _T("dir"),
							  _T("Title"),
							  3,
							  9,
							  _T("ext"));
			//Logger::WriteMessage(sReadPath2);	// -> dirTitle009ext



		}

	};
}
