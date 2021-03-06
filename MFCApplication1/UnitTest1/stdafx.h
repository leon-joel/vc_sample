// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define NO_WARN_MBCS_MFC_DEPRECATION	// 警告抑止 warning C4996: 'MBCS_Support_Deprecated_In_MFC': MBCS support in MFC is deprecated and may be removed in a future version of MFC.

#define NOMINMAX		// minwindef.hに記述されているmin/maxマクロを使わない。※std::max/min を邪魔しないように

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Windows ヘッダーから使用されていない部分を除外します。
#endif

#include "targetver.h"


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 一部の CString コンストラクターは明示的です。


#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分

//#ifndef _AFX_NO_OLE_SUPPORT
//#include <afxole.h>         // MFC OLE クラス
//#include <afxodlgs.h>       // MFC OLE ダイアログ クラス
//#include <afxdisp.h>        // MFC オートメーション クラス
//#endif // _AFX_NO_OLE_SUPPORT
//
//#ifndef _AFX_NO_DB_SUPPORT
//#include <afxdb.h>                      // MFC ODBC データベース クラス
//#endif // _AFX_NO_DB_SUPPORT
//
//#ifndef _AFX_NO_DAO_SUPPORT
//#include <afxdao.h>                     // MFC DAO データベース クラス
//#endif // _AFX_NO_DAO_SUPPORT
//
//#ifndef _AFX_NO_OLE_SUPPORT
//#include <afxdtctl.h>           // MFC の Internet Explorer 4 コモン コントロール サポート
//#endif
//#ifndef _AFX_NO_AFXCMN_SUPPORT
//#include <afxcmn.h>                     // MFC の Windows コモン コントロール サポート
//#endif // _AFX_NO_AFXCMN_SUPPORT




// CppUnitTest のヘッダー
#include "CppUnitTest.h"



// TODO: プログラムに必要な追加ヘッダーをここで参照してください

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <numeric>
#include <algorithm>
#include <filesystem>
#include <cmath>
#include <chrono>
#include <ctime>

#pragma warning( push )
#pragma warning(disable : 4819)		// interval.hpp あたりの作者名がドイツ語(?)かなにかで、この警告が大量に表示されてしまう ⇒ 現在のコード ページ (数) で表示できない文字を含んでいます。
#include <boost/numeric/interval.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/clamp.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm_ext/iota.hpp>
#include <boost/filesystem.hpp>
#include <boost/chrono/chrono.hpp>
//#include <boost/timer/timer.hpp>	// 使えなかった ※WEBから落としてきたバイナリーだったからかも
#pragma warning( pop )

#if defined(UNICODE) || defined(_UNICODE)
# define tout std::wcout
# define tin std::wcin
# define terr std::wcerr
# define tlog std::wclog
#else
# define tout std::cout
# define tin std::cin
# define terr std::cerr
# define tlog std::clog
#endif

//typedef std::basic_string<_TCHAR> tstring
//typedef std::basic_stringstream<_TCHAR> tstringstream;
//typedef std::basic_ostringstream<_TCHAR> tostringstream;
//typedef std::basic_istringstream<_TCHAR> tistringstream;

using tstring = std::basic_string<_TCHAR>;
using tostream = std::basic_ostream<_TCHAR, std::char_traits<_TCHAR>>;
using tstringstream = std::basic_stringstream<_TCHAR>;
using tostringstream = std::basic_ostringstream<_TCHAR>;
using tistringstream = std::basic_istringstream<_TCHAR>;

// boost用
#if defined(UNICODE) || defined(_UNICODE)
using bformat = boost::basic_format<wchar_t >;
#else
using bformat = boost::basic_format<char >;
#endif
