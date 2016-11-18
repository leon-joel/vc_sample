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

		TEST_METHOD(TestPath)
		{
			tostringstream ost;
			tstring filename(_T("F:/SecondYear/VCproject/cloud/raw-format/data/cloud-velocity.exe"));
			std::tr2::sys::path path(filename);
			Assert::AreEqual(_T("F:\\"), path.root_path().c_str());
			Assert::AreEqual(LR"(F:\)", path.root_path().c_str());
			// �� \\ ���ς킵���̂�C+11�œ������ꂽ Raw String Literal �ŋL�q���Ă݂� ��https://msdn.microsoft.com/ja-jp/library/69ze775t.aspx
			//    �ȒP�ɋL�q�ł��邪�ATCHAR+RAW �̃}�N�����Ȃ������Ȃ̂ŁAUnicode/MBCS�͂ǂ��炩�����ߑł��ŏ������ƂɂȂ肻���c
			ost << _T("�h���C�u��(root_path): ") << path.root_path() << std::endl;	// F:\  ����؂蕶���� \ �ɕϊ�����Ă���_�ɒ���

			//ost << "�f�B���N�g��:" << path.directory_string() << std::endl;
			Assert::AreEqual(LR"(F:\SecondYear\VCproject\cloud\raw-format\data)", path.parent_path().c_str());	// Raw String Literal�ŋL�q���Ă݂� ��https://msdn.microsoft.com/ja-jp/library/69ze775t.aspx
			ost << _T("parent_path: ") << path.parent_path() << std::endl;			// F:\SecondYear\VCproject\cloud\raw-format\data


			//ost << "�t�@�C����:" << path.basename() << std::endl;
			Assert::AreEqual(LR"(cloud-velocity.exe)", path.filename().c_str());
			ost << _T("filename: ") << path.filename() << std::endl;				// cloud-velocity.exe
			//ost << "file_string:" << path.file_string() << std::endl;
			Assert::AreEqual(LR"(.exe)", path.extension().c_str());
			ost << _T("�g���q: ") << path.extension() << std::endl;					// .exe
			Assert::AreEqual(LR"(F:)", path.root_name().c_str());
			ost << _T("root_name: ") << path.root_name() << std::endl;				// F:
			Assert::AreEqual(LR"(\)", path.root_directory().c_str());
			ost << _T("root_directory: ") << path.root_directory() << std::endl;	// \
			//ost << "�t���p�X:" << path.string() << std::endl;
			Assert::AreEqual(LR"(F:\SecondYear\VCproject\cloud\raw-format\data\cloud-velocity.exe)", path.c_str());
			ost << _T("�t���p�X: ") << path.c_str() << std::endl;

			Assert::IsTrue(path.is_absolute());
			ost << _T("��΃p�X�H: ") << path.is_absolute() << std::endl;				// 1

			Logger::WriteMessage(ost.str().c_str());
		}

		TEST_METHOD(TestPath2)
		{
			tostringstream ost;
			tstring filename(LR"(..\test\fname)");
			std::tr2::sys::path path(filename);

			Assert::IsFalse(path.is_absolute());
			ost << _T("��΃p�X�H: ") << path.is_absolute() << std::endl;				// 0

			Assert::AreEqual(LR"(fname)", path.filename().c_str());
			ost << _T("filename: ") << path.filename() << std::endl;				// fname
			Assert::AreEqual(LR"()", path.extension().c_str());
			ost << _T("�g���q: ") << path.extension() << std::endl;					// 


			filename = LR"(test/body.ext1.ext2.ext3)";
			path = filename;
			ost << std::endl;

			path = path.stem();
			Assert::AreEqual(LR"(body.ext1.ext2)", path.filename().c_str());
			ost << _T("���[�g���q��Trim��: ") << path.filename().c_str() << std::endl;	// body.ext1.ext2
			path = path.stem();
			Assert::AreEqual(LR"(body.ext1)", path.filename().c_str());
			ost << _T("���[�g���q��Trim��: ") << path.filename().c_str() << std::endl;	// body.ext1
			path = path.stem();
			Assert::AreEqual(LR"(body)", path.filename().c_str());
			ost << _T("���[�g���q��Trim��: ") << path.filename().c_str() << std::endl;	// body
			path = path.stem();
			Assert::AreEqual(LR"(body)", path.filename().c_str());
			ost << _T("���[�g���q��Trim��: ") << path.filename().c_str() << std::endl;	// body  ������ȏ��Trim����Ȃ��悤��

			Logger::WriteMessage(ost.str().c_str());
		}

		TEST_METHOD(BoostPathTest)
		{
			tostringstream ost;
			tstring filename(_T("F:/SecondYear/VCproject/cloud/raw-format/data/cloud-velocity.exe"));
			boost::filesystem::path path(filename);

			Assert::AreEqual(_T("F:/"), path.root_path().c_str());
			Assert::AreEqual(LR"(F:/)", path.root_path().c_str());
			// �� \\ ���ς킵���̂�C+11�œ������ꂽ Raw String Literal �ŋL�q���Ă݂� ��https://msdn.microsoft.com/ja-jp/library/69ze775t.aspx
			//    �ȒP�ɋL�q�ł��邪�ATCHAR+RAW �̃}�N�����Ȃ������Ȃ̂ŁAUnicode/MBCS�͂ǂ��炩�����ߑł��ŏ������ƂɂȂ肻���c
			ost << _T("�h���C�u��(root_path): ") << path.root_path() << std::endl;	// F:/ ��Boost�ł͋�؂蕶����ϊ����Ȃ��_�ɒ��ӁI

			Assert::AreEqual(LR"(F:/SecondYear/VCproject/cloud/raw-format/data)", path.parent_path().c_str());	// Raw String Literal�ŋL�q���Ă݂� ��https://msdn.microsoft.com/ja-jp/library/69ze775t.aspx
			ost << _T("parent_path: ") << path.parent_path() << std::endl;			// F:/SecondYear/VCproject/cloud/raw-format/data

			Assert::AreEqual(LR"(cloud-velocity.exe)", path.filename().c_str());
			ost << _T("filename: ") << path.filename() << std::endl;				// cloud-velocity.exe

			Assert::AreEqual(LR"(.exe)", path.extension().c_str());
			ost << _T("�g���q: ") << path.extension() << std::endl;					// .exe
			Assert::AreEqual(LR"(F:)", path.root_name().c_str());
			ost << _T("root_name: ") << path.root_name() << std::endl;				// F:
			Assert::AreEqual(LR"(/)", path.root_directory().c_str());
			ost << _T("root_directory: ") << path.root_directory() << std::endl;	// /

			Assert::AreEqual(LR"(F:/SecondYear/VCproject/cloud/raw-format/data/cloud-velocity.exe)", path.c_str());
			ost << _T("�t���p�X: ") << path.c_str() << std::endl;

			Assert::IsTrue(path.is_absolute());
			ost << _T("��΃p�X�H: ") << path.is_absolute() << std::endl;				// 1

			Logger::WriteMessage(ost.str().c_str());
		}

		TEST_METHOD(BoostPathTest2)
		{
			tostringstream ost;
			tstring filename(LR"(..\test\fname)");
			boost::filesystem::path path(filename);

			Assert::IsFalse(path.is_absolute());
			ost << _T("��΃p�X�H: ") << path.is_absolute() << std::endl;				// 0

			Assert::AreEqual(LR"(..\test)", path.parent_path().c_str());			// ..\test  ��Boost�ł͋�؂蕶����ϊ����Ȃ��_�ɒ��ӁI
			ost << _T("parent_path: ") << path.parent_path() << std::endl;

			Assert::AreEqual(LR"(fname)", path.filename().c_str());
			ost << _T("filename: ") << path.filename() << std::endl;				// fname
			Assert::AreEqual(LR"()", path.extension().c_str());
			ost << _T("�g���q: ") << path.extension() << std::endl;					// 


			filename = LR"(test/body.ext1.ext2.ext3)";
			path = filename;
			ost << std::endl;

			path = path.stem();
			Assert::AreEqual(LR"(body.ext1.ext2)", path.filename().c_str());
			ost << _T("���[�g���q��Trim��: ") << path.filename().c_str() << std::endl;	// body.ext1.ext2
			path = path.stem();
			Assert::AreEqual(LR"(body.ext1)", path.filename().c_str());
			ost << _T("���[�g���q��Trim��: ") << path.filename().c_str() << std::endl;	// body.ext1
			path = path.stem();
			Assert::AreEqual(LR"(body)", path.filename().c_str());
			ost << _T("���[�g���q��Trim��: ") << path.filename().c_str() << std::endl;	// body
			path = path.stem();
			Assert::AreEqual(LR"(body)", path.filename().c_str());
			ost << _T("���[�g���q��Trim��: ") << path.filename().c_str() << std::endl;	// body  ������ȏ��Trim����Ȃ��悤��

			Logger::WriteMessage(ost.str().c_str());
		}

		const int VEC_SIZE = 100;
		std::vector<int> moveVector()
		{
			std::vector<int> vec(VEC_SIZE);
			boost::iota(vec, 0);

			return std::move(vec);
		}

		std::vector<int> copyVector()
		{
			std::vector<int> vec(VEC_SIZE);
			boost::iota(vec, 0);

			return vec;
		}

		void refVector(std::vector<int>& vec)
		{
			vec.resize(VEC_SIZE);
			boost::iota(vec, 0);
		}

		TEST_METHOD(StdChrono)
		{
			tostringstream ost;

			// 1. �֐��������� std::move ���Ăяo���Ă���
			auto start = std::chrono::system_clock::now();
			int sum = 0;
			for (long i = 0; i < 1000; ++i) {
				std::vector<int> vec = moveVector();
				//sum = boost::accumulate(vec, 0);
				sum = vec.size();
			}
			ost << sum << std::endl;
			auto end = std::chrono::system_clock::now();
			LONG64 elapsed1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

			// 2. �֐��������� std::move ���Ăяo�����A�R�s�[��Ԃ��Ă���i����j
			start = std::chrono::system_clock::now();
			for (long i = 0; i < 1000; ++i) {
				std::vector<int> vec = copyVector();
				//sum = boost::accumulate(vec, 0);
				sum = vec.size();
			}
			ost << sum << std::endl;
			end = std::chrono::system_clock::now();
			LONG64 elapsed2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

			// 3. �]���I�Ȃ����i���ꕨ���Q�ƂŎ󂯎��A�֐����ŋl�ߍ���ł�����j
			start = std::chrono::system_clock::now();
			for (long i = 0; i < 1000; ++i) {
				std::vector<int> vec;
				refVector(vec);
				//sum = boost::accumulate(vec, 0);
				sum = vec.size();
			}
			ost << sum << std::endl;
			end = std::chrono::system_clock::now();
			LONG64 elapsed3 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

			// 4. ������ɃR�s�[�R���X�g���N�g�𑖂点�Ă���
			start = std::chrono::system_clock::now();
			for (long i = 0; i < 1000; ++i) {
				std::vector<int> vec;
				refVector(vec);
				std::vector<int> vec2(vec);
				//sum = boost::accumulate(vec, 0);
				sum = vec.size();
			}
			ost << sum << std::endl;
			end = std::chrono::system_clock::now();
			LONG64 elapsed4 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();



			ost << _T("�o�ߎ���1 (move): ") << elapsed1 << _T("msec") << std::endl;
			ost << _T("�o�ߎ���2 (copy): ") << elapsed2 << _T("msec") << std::endl;
			ost << _T("�o�ߎ���3 (ref ): ") << elapsed3 << _T("msec") << std::endl;
			ost << _T("�o�ߎ���4 (cpy ): ") << elapsed4 << _T("msec") << std::endl;
			Logger::WriteMessage(ost.str().c_str());

			// x86/Debug��     5����
			//�o�ߎ���1(move) : 12980msec
			//�o�ߎ���2(copy) : 12430msec
			//�o�ߎ���3(ref ) : 12465msec
			//�o�ߎ���4(cpy ) : 12529msec

			// x86/Release��           20����
			//�o�ߎ���1(move) : 36msec  283msec
			//�o�ߎ���2(copy) : 37msec  281msec
			//�o�ߎ���3(ref ) : 36msec  316msec
			//�o�ߎ���4(cpy ) : 77msec  824msec

			// x64/Release��           20����
			//�o�ߎ���1(move) : 32msec  188msec
			//�o�ߎ���2(copy) : 32msec  186msec
			//�o�ߎ���3(ref ) : 46msec  221msec
			//�o�ߎ���4(cpy ) : 40msec  523msec

			// �l�@: 
			// x86/Release�ł̌��ʂɂ���: 
			//   VC14��std::vector�ɂ̓��[�u������Z�q�i�E�Ӓl�Q�Ƃ��󂯎�������Z�q CMyClass& operator=(CMyClass&& value) ��
			//   ��`����Ă���̂ŁA1, 2 �̂ǂ�����R�s�[�͔������Ă��Ȃ����̂Ǝv����B
			//   �i1.��std::move���Ăяo���Ă��镪������ƒx���̂��ȁH�j
			//   3. �͏]���ʂ�̂����Ȃ̂ŁAMove��Copy���������Ă��炸�����͓̂��R�Bresize���Ă��镪�����x���̂����B
			//   4.�͖�����R�s�[�����Ă���̂œ��R�x���B
			//   http://program.station.ez-net.jp/special/handbook/cpp/syntax/move.asp

			// x64/Release�ł̌��ʂɂ���: 
			//   �f�[�^�������Ȃ��ꍇ�ɂ͂��܂荷���o�Ȃ������B3���4�̕��������̂��ӊO�B�덷���ȁH
			//   �f�[�^����4�{�ɑ��₵���ꍇ�i20�����j�ɂ́Ax86�łƓ����X���ɂȂ����B
			//
			// Debug�ł̌��ʂɂ���: 
			//   �ǂ���قړ������v���ԂȂ̂��悭������Ȃ��B
			//   �������[�`�F�b�N���s�����߁ADebug�łł̓R�s�[�ɋ߂����Ƃ��s���Ă���̂�������Ȃ��B		

			// ���_: 
			// �Estd::vector�̂悤�ɁA���[�u����E���[�u�R�s�[���������Ă���N���X�̏ꍇ�́A
			//   return���鎞�� std::move ������K�v�͂Ȃ��A2.�̂������x�X�g�`���C�X�B
			// �E�Ή����Ă��Ȃ��ꍇ�́A�]���ʂ�̂����A�܂�3.�ł�邵���Ȃ��B
			// �E����N���X�ŃR�s�[�Ɏ��ԁi�ƃ��\�[�X�j�������肻���Ȃ��̂̏ꍇ�́A
			//   ���[�u����E���[�u�R�s�[���������Ă����B
		}

		TEST_METHOD(IntersectRect)
		{
			// r2��r1�̒��ɑS�������Ă���
			CRect r1(0, 0, 10, 20);
			CRect r2(3, 5, 8, 18);

			CRect ir;
			Assert::IsTrue(ir.IntersectRect(r1, r2) != 0);
			Assert::AreEqual(3l, ir.left);
			Assert::AreEqual(5l, ir.top);
			Assert::AreEqual(5, ir.Width());
			Assert::AreEqual(13, ir.Height());

			// �����͂ݏo���Ă��� ��&= ���Z�q�ł����������ł���B�A���A�߂�l�������Ȃ��B
			ir.SetRect(8, 13, 13, 26);
			ir &= r1;
			Assert::AreEqual(8l, ir.left);
			Assert::AreEqual(13l, ir.top);
			Assert::AreEqual(2, ir.Width());
			Assert::AreEqual(7, ir.Height());

			// ���E�����d�Ȃ��Ă��� �� False
			// ���摜�����ł͍��W���s�N�Z�������̂���_ �Ȃ̂ŁA���E�����d�Ȃ遁RECT���������� �ƈ���Ȃ��Ƃ����Ȃ��i���ȁH�j
			r2.SetRect(10, 13, 13, 26);
			Assert::IsTrue(ir.IntersectRect(r1, r2) == 0, L"test");	// RECT���������Ȃ��̂�False���Ԃ��Ă���

																	// ���S�ɔ�яo���Ă��� �� False
			r2.SetRect(11, 13, 13, 26);
			Assert::IsTrue(ir.IntersectRect(r1, r2) == 0);

			// �񐳋K��RECT��n���Ă݂� �� False
			r2.SetRect(13, 13, 8, 26);		// 2�Ԗڂ̃T���v�����㉺�t�]
			Assert::IsTrue(ir.IntersectRect(r1, r2) == 0, L"test2");	// False���Ԃ��Ă���
			tostringstream ost;
			ost << bformat(_T(" LT(%d, %d)")) % ir.left % ir.top
				<< bformat(_T(" RB(%d, %d)")) % ir.right % ir.bottom << std::endl;
			Logger::WriteMessage(ost.str().c_str());
		}
	};
}
