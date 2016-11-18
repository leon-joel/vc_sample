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

			// 1. 関数内末尾で std::move を呼び出している
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

			// 2. 関数内末尾で std::move を呼び出さず、コピーを返している（つもり）
			start = std::chrono::system_clock::now();
			for (long i = 0; i < 1000; ++i) {
				std::vector<int> vec = copyVector();
				//sum = boost::accumulate(vec, 0);
				sum = vec.size();
			}
			ost << sum << std::endl;
			end = std::chrono::system_clock::now();
			LONG64 elapsed2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

			// 3. 従来的なやり方（入れ物を参照で受け取り、関数内で詰め込んであげる）
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

			// 4. 無理矢理にコピーコンストラクトを走らせている
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



			ost << _T("経過時間1 (move): ") << elapsed1 << _T("msec") << std::endl;
			ost << _T("経過時間2 (copy): ") << elapsed2 << _T("msec") << std::endl;
			ost << _T("経過時間3 (ref ): ") << elapsed3 << _T("msec") << std::endl;
			ost << _T("経過時間4 (cpy ): ") << elapsed4 << _T("msec") << std::endl;
			Logger::WriteMessage(ost.str().c_str());

			// x86/Debug版     5万件
			//経過時間1(move) : 12980msec
			//経過時間2(copy) : 12430msec
			//経過時間3(ref ) : 12465msec
			//経過時間4(cpy ) : 12529msec

			// x86/Release版           20万件
			//経過時間1(move) : 36msec  283msec
			//経過時間2(copy) : 37msec  281msec
			//経過時間3(ref ) : 36msec  316msec
			//経過時間4(cpy ) : 77msec  824msec

			// x64/Release版           20万件
			//経過時間1(move) : 32msec  188msec
			//経過時間2(copy) : 32msec  186msec
			//経過時間3(ref ) : 46msec  221msec
			//経過時間4(cpy ) : 40msec  523msec

			// 考察: 
			// x86/Release版の結果について: 
			//   VC14のstd::vectorにはムーブ代入演算子（右辺値参照を受け取る代入演算子 CMyClass& operator=(CMyClass&& value) が
			//   定義されているので、1, 2 のどちらもコピーは発生していないものと思われる。
			//   （1.がstd::moveを呼び出している分ちょっと遅いのかな？）
			//   3. は従来通りのやり方なので、MoveもCopyも発生しておらず速いのは当然。resizeしている分少し遅いのかも。
			//   4.は無理矢理コピーさせているので当然遅い。
			//   http://program.station.ez-net.jp/special/handbook/cpp/syntax/move.asp

			// x64/Release版の結果について: 
			//   データ数が少ない場合にはあまり差が出なかった。3より4の方が速いのも意外。誤差かな？
			//   データ数を4倍に増やした場合（20万件）には、x86版と同じ傾向になった。
			//
			// Debug版の結果について: 
			//   どれもほぼ同じ所要時間なのがよく分からない。
			//   メモリーチェックを行うため、Debug版ではコピーに近いことが行われているのかもしれない。		

			// 結論: 
			// ・std::vectorのように、ムーブ代入・ムーブコピーを実装しているクラスの場合は、
			//   returnする時に std::move を入れる必要はなく、2.のやり方がベストチョイス。
			// ・対応していない場合は、従来通りのやり方、つまり3.でやるしかない。
			// ・自作クラスでコピーに時間（とリソース）がかかりそうなものの場合は、
			//   ムーブ代入・ムーブコピーを実装しておく。
		}

		TEST_METHOD(IntersectRect)
		{
			// r2がr1の中に全部入っている
			CRect r1(0, 0, 10, 20);
			CRect r2(3, 5, 8, 18);

			CRect ir;
			Assert::IsTrue(ir.IntersectRect(r1, r2) != 0);
			Assert::AreEqual(3l, ir.left);
			Assert::AreEqual(5l, ir.top);
			Assert::AreEqual(5, ir.Width());
			Assert::AreEqual(13, ir.Height());

			// 少しはみ出している ※&= 演算子でも同じ事ができる。但し、戻り値が得られない。
			ir.SetRect(8, 13, 13, 26);
			ir &= r1;
			Assert::AreEqual(8l, ir.left);
			Assert::AreEqual(13l, ir.top);
			Assert::AreEqual(2, ir.Width());
			Assert::AreEqual(7, ir.Height());

			// 境界線が重なっている ⇒ False
			// ※画像処理では座標＝ピクセル＝幅のある点 なので、境界線が重なる＝RECTが成立する と扱わないといけない（かな？）
			r2.SetRect(10, 13, 13, 26);
			Assert::IsTrue(ir.IntersectRect(r1, r2) == 0, L"test");	// RECTが成立しないのでFalseが返ってくる

																	// 完全に飛び出している ⇒ False
			r2.SetRect(11, 13, 13, 26);
			Assert::IsTrue(ir.IntersectRect(r1, r2) == 0);

			// 非正規化RECTを渡してみる ⇒ False
			r2.SetRect(13, 13, 8, 26);		// 2番目のサンプルを上下逆転
			Assert::IsTrue(ir.IntersectRect(r1, r2) == 0, L"test2");	// Falseが返ってくる
			tostringstream ost;
			ost << bformat(_T(" LT(%d, %d)")) % ir.left % ir.top
				<< bformat(_T(" RB(%d, %d)")) % ir.right % ir.bottom << std::endl;
			Logger::WriteMessage(ost.str().c_str());
		}
	};
}
