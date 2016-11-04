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
			// 0詰めの桁数指定
			CString sFormat;
			sFormat.Format(_T("%%s%%s%%0%dd%%s"), 2);
			//Logger::WriteMessage(sFormat);	// -> %s%s%02d%s

			// フォーマット
			CString sReadPath;
			sReadPath.Format(sFormat,
							 _T("dir"),
							 _T("Title"),
							 9,
							 _T("ext"));
			//Logger::WriteMessage(sReadPath);	// -> dirTitle09ext
	

			// 0詰め桁数指定しつつ、フォーマットする
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
			// ↑ \\ が煩わしいのでC+11で導入された Raw String Literal で記述してみた ※https://msdn.microsoft.com/ja-jp/library/69ze775t.aspx
			//    簡単に記述できるが、TCHAR+RAW のマクロがなさそうなので、Unicode/MBCSはどちらかを決め打ちで書くことになりそう…
			ost << _T("ドライブ名(root_path): ") << path.root_path() << std::endl;	// F:\  ※区切り文字が \ に変換されている点に着目

			//ost << "ディレクトリ:" << path.directory_string() << std::endl;
			Assert::AreEqual(LR"(F:\SecondYear\VCproject\cloud\raw-format\data)", path.parent_path().c_str());	// Raw String Literalで記述してみた ※https://msdn.microsoft.com/ja-jp/library/69ze775t.aspx
			ost << _T("parent_path: ") << path.parent_path() << std::endl;			// F:\SecondYear\VCproject\cloud\raw-format\data


			//ost << "ファイル名:" << path.basename() << std::endl;
			Assert::AreEqual(LR"(cloud-velocity.exe)", path.filename().c_str());
			ost << _T("filename: ") << path.filename() << std::endl;				// cloud-velocity.exe
			//ost << "file_string:" << path.file_string() << std::endl;
			Assert::AreEqual(LR"(.exe)", path.extension().c_str());
			ost << _T("拡張子: ") << path.extension() << std::endl;					// .exe
			Assert::AreEqual(LR"(F:)", path.root_name().c_str());
			ost << _T("root_name: ") << path.root_name() << std::endl;				// F:
			Assert::AreEqual(LR"(\)", path.root_directory().c_str());
			ost << _T("root_directory: ") << path.root_directory() << std::endl;	// \
			//ost << "フルパス:" << path.string() << std::endl;
			Assert::AreEqual(LR"(F:\SecondYear\VCproject\cloud\raw-format\data\cloud-velocity.exe)", path.c_str());
			ost << _T("フルパス: ") << path.c_str() << std::endl;

			Assert::IsTrue(path.is_absolute());
			ost << _T("絶対パス？: ") << path.is_absolute() << std::endl;				// 1

			Logger::WriteMessage(ost.str().c_str());
		}

		TEST_METHOD(TestPath2)
		{
			tostringstream ost;
			tstring filename(LR"(..\test\fname)");
			std::tr2::sys::path path(filename);

			Assert::IsFalse(path.is_absolute());
			ost << _T("絶対パス？: ") << path.is_absolute() << std::endl;				// 0

			Assert::AreEqual(LR"(fname)", path.filename().c_str());
			ost << _T("filename: ") << path.filename() << std::endl;				// fname
			Assert::AreEqual(LR"()", path.extension().c_str());
			ost << _T("拡張子: ") << path.extension() << std::endl;					// 


			filename = LR"(test/body.ext1.ext2.ext3)";
			path = filename;
			ost << std::endl;

			path = path.stem();
			Assert::AreEqual(LR"(body.ext1.ext2)", path.filename().c_str());
			ost << _T("末端拡張子をTrim後: ") << path.filename().c_str() << std::endl;	// body.ext1.ext2
			path = path.stem();
			Assert::AreEqual(LR"(body.ext1)", path.filename().c_str());
			ost << _T("末端拡張子をTrim後: ") << path.filename().c_str() << std::endl;	// body.ext1
			path = path.stem();
			Assert::AreEqual(LR"(body)", path.filename().c_str());
			ost << _T("末端拡張子をTrim後: ") << path.filename().c_str() << std::endl;	// body
			path = path.stem();
			Assert::AreEqual(LR"(body)", path.filename().c_str());
			ost << _T("末端拡張子をTrim後: ") << path.filename().c_str() << std::endl;	// body  ※これ以上はTrimされないようだ

			Logger::WriteMessage(ost.str().c_str());
		}

		TEST_METHOD(BoostPathTest)
		{
			tostringstream ost;
			tstring filename(_T("F:/SecondYear/VCproject/cloud/raw-format/data/cloud-velocity.exe"));
			boost::filesystem::path path(filename);

			Assert::AreEqual(_T("F:/"), path.root_path().c_str());
			Assert::AreEqual(LR"(F:/)", path.root_path().c_str());
			// ↑ \\ が煩わしいのでC+11で導入された Raw String Literal で記述してみた ※https://msdn.microsoft.com/ja-jp/library/69ze775t.aspx
			//    簡単に記述できるが、TCHAR+RAW のマクロがなさそうなので、Unicode/MBCSはどちらかを決め打ちで書くことになりそう…
			ost << _T("ドライブ名(root_path): ") << path.root_path() << std::endl;	// F:/ ※Boost版は区切り文字を変換しない点に注意！

			Assert::AreEqual(LR"(F:/SecondYear/VCproject/cloud/raw-format/data)", path.parent_path().c_str());	// Raw String Literalで記述してみた ※https://msdn.microsoft.com/ja-jp/library/69ze775t.aspx
			ost << _T("parent_path: ") << path.parent_path() << std::endl;			// F:/SecondYear/VCproject/cloud/raw-format/data

			Assert::AreEqual(LR"(cloud-velocity.exe)", path.filename().c_str());
			ost << _T("filename: ") << path.filename() << std::endl;				// cloud-velocity.exe

			Assert::AreEqual(LR"(.exe)", path.extension().c_str());
			ost << _T("拡張子: ") << path.extension() << std::endl;					// .exe
			Assert::AreEqual(LR"(F:)", path.root_name().c_str());
			ost << _T("root_name: ") << path.root_name() << std::endl;				// F:
			Assert::AreEqual(LR"(/)", path.root_directory().c_str());
			ost << _T("root_directory: ") << path.root_directory() << std::endl;	// /

			Assert::AreEqual(LR"(F:/SecondYear/VCproject/cloud/raw-format/data/cloud-velocity.exe)", path.c_str());
			ost << _T("フルパス: ") << path.c_str() << std::endl;

			Assert::IsTrue(path.is_absolute());
			ost << _T("絶対パス？: ") << path.is_absolute() << std::endl;				// 1

			Logger::WriteMessage(ost.str().c_str());
		}

		TEST_METHOD(BoostPathTest2)
		{
			tostringstream ost;
			tstring filename(LR"(..\test\fname)");
			boost::filesystem::path path(filename);

			Assert::IsFalse(path.is_absolute());
			ost << _T("絶対パス？: ") << path.is_absolute() << std::endl;				// 0

			Assert::AreEqual(LR"(..\test)", path.parent_path().c_str());			// ..\test  ※Boost版は区切り文字を変換しない点に注意！
			ost << _T("parent_path: ") << path.parent_path() << std::endl;

			Assert::AreEqual(LR"(fname)", path.filename().c_str());
			ost << _T("filename: ") << path.filename() << std::endl;				// fname
			Assert::AreEqual(LR"()", path.extension().c_str());
			ost << _T("拡張子: ") << path.extension() << std::endl;					// 


			filename = LR"(test/body.ext1.ext2.ext3)";
			path = filename;
			ost << std::endl;

			path = path.stem();
			Assert::AreEqual(LR"(body.ext1.ext2)", path.filename().c_str());
			ost << _T("末端拡張子をTrim後: ") << path.filename().c_str() << std::endl;	// body.ext1.ext2
			path = path.stem();
			Assert::AreEqual(LR"(body.ext1)", path.filename().c_str());
			ost << _T("末端拡張子をTrim後: ") << path.filename().c_str() << std::endl;	// body.ext1
			path = path.stem();
			Assert::AreEqual(LR"(body)", path.filename().c_str());
			ost << _T("末端拡張子をTrim後: ") << path.filename().c_str() << std::endl;	// body
			path = path.stem();
			Assert::AreEqual(LR"(body)", path.filename().c_str());
			ost << _T("末端拡張子をTrim後: ") << path.filename().c_str() << std::endl;	// body  ※これ以上はTrimされないようだ

			Logger::WriteMessage(ost.str().c_str());
		}
	};
}
