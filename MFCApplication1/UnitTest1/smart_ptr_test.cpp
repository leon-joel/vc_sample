#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SmartPtrTest
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

	TEST_CLASS(SmartPtrTest)
	{
	public:

		// �����̃e�X�g�����s����ƃS�~�t�@�C�����c��̂ŁA���i�̓R�����g�����Ă���

		//TEST_METHOD(UniquePtrTest)
		//{
		//	//std::unique_ptr<int> p(new int(2));
		//	//Assert::AreEqual(2, *p);
		//	//Logger::WriteMessage((bformat(_T("int: %d")) % *p).str().c_str());	// -> 2

		//	//int* p2 = new int(3);		// Detected memory leaks! ���f�o�b�O���s�Ń��[�N���o�����
		//	//Assert::AreEqual(3, *p2);

		//	//FILE* pf(_tfopen(_T("f:/work/tmp/test.txt"), _T("ab")));
		//	//_fputts(_T("test\r\n"), pf);	// �t�@�C���J�����ςȂ��̓f�o�b�O���s�ł����o����Ȃ�

		//	using UPTR_FILE = std::unique_ptr<FILE, decltype(&fclose)>;
		//	UPTR_FILE pf(_tfopen(_T("t:/unknown_drive.txt"), _T("ab")), fclose);
		//	Assert::IsTrue(nullptr == pf.get());	// ���|�C���^�[
		//	Assert::IsTrue(nullptr == pf);			// operator== ���I�[�o�[���C�h����Ă���悤��
		//	Assert::IsFalse((bool)pf);				// nullptr�̏ꍇ�͏��L���Ȃ��ƂȂ�悤��

		//	UPTR_FILE pf2(_tfopen(_T("f:/work/tmp/test.txt"), _T("ab")), fclose);
		//	Assert::IsTrue(nullptr != pf2.get());
		//	Assert::IsTrue(nullptr != pf2);
		//	Assert::IsTrue((bool)pf2);
		//	_fputts(_T("test2\r\n"), pf2.get());

		//	
		//	//UPTR_FILE pf3 = pf2;			// unique_ptr�̃R�s�[�͕s�� ���r���h�G���[
		//	UPTR_FILE pf3 = std::move(pf2);	// ���[�u�͉\
		//	Assert::IsFalse((bool)pf2);		// pf2�͂��͂⏊�L���������Ă���
		//	Assert::IsTrue((bool)pf3);		// pf3�ɏ��L�����ڂ��Ă���

		//	{
		//		std::vector<UPTR_FILE> vec;
		//		vec.push_back(UPTR_FILE(_tfopen(_T("f:/work/tmp/test1.txt"), _T("ab")), fclose));
		//		vec.push_back(UPTR_FILE(_tfopen(_T("f:/work/tmp/test2.txt"), _T("ab")), fclose));
		//		vec.push_back(UPTR_FILE(_tfopen(_T("f:/work/tmp/test3.txt"), _T("ab")), fclose));
		//		vec.push_back(UPTR_FILE(_tfopen(_T("f:/work/tmp/test4.txt"), _T("ab")), fclose));

		//		_fputts(_T("test1\r\n"), vec[0].get());
		//		_fputts(_T("test2\r\n"), vec[1].get());
		//		_fputts(_T("test3\r\n"), vec[2].get());
		//		_fputts(_T("test4\r\n"), vec[3].get());

		//		// ������4�t�@�C��Close�����
		//	}

		//	std::unique_ptr<int> p(new int(2));
		//	Assert::AreEqual(2, *p);

		//	// ���|�C���^��fclose�����ɕ��u���Ă݂�
		//	FILE* f(_tfopen(_T("f:/work/tmp/test.txt"), _T("ab")));
		//	_fputts(_T("test\r\n"), f);
		//	// VS�f�o�b�O���s�ł̓��[�N���o����Ȃ����A
		//	// Process Explorer�Ō���΃v���Z�X�����ʂ܂�Open�����ςȂ��ł��邱�Ƃ�������B
		//	// https://technet.microsoft.com/en-us/sysinternals/bb896653.aspx?f=255&MSPPError=-2147217396
		//}



	};
}