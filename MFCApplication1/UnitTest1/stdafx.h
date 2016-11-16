// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once


#define NOMINMAX		// minwindef.h�ɋL�q����Ă���min/max�}�N�����g��Ȃ��B��std::max/min ���ז����Ȃ��悤��

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
#endif

#include "targetver.h"


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �ꕔ�� CString �R���X�g���N�^�[�͖����I�ł��B


#include <afxwin.h>         // MFC �̃R�A����ѕW���R���|�[�l���g
#include <afxext.h>         // MFC �̊g������

//#ifndef _AFX_NO_OLE_SUPPORT
//#include <afxole.h>         // MFC OLE �N���X
//#include <afxodlgs.h>       // MFC OLE �_�C�A���O �N���X
//#include <afxdisp.h>        // MFC �I�[�g���[�V���� �N���X
//#endif // _AFX_NO_OLE_SUPPORT
//
//#ifndef _AFX_NO_DB_SUPPORT
//#include <afxdb.h>                      // MFC ODBC �f�[�^�x�[�X �N���X
//#endif // _AFX_NO_DB_SUPPORT
//
//#ifndef _AFX_NO_DAO_SUPPORT
//#include <afxdao.h>                     // MFC DAO �f�[�^�x�[�X �N���X
//#endif // _AFX_NO_DAO_SUPPORT
//
//#ifndef _AFX_NO_OLE_SUPPORT
//#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �R���� �R���g���[�� �T�|�[�g
//#endif
//#ifndef _AFX_NO_AFXCMN_SUPPORT
//#include <afxcmn.h>                     // MFC �� Windows �R���� �R���g���[�� �T�|�[�g
//#endif // _AFX_NO_AFXCMN_SUPPORT




// CppUnitTest �̃w�b�_�[
#include "CppUnitTest.h"



// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă�������

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

#include <boost/algorithm/clamp.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm_ext/iota.hpp>
#include <boost/filesystem.hpp>
//#include <boost/timer/timer.hpp>	// �g���Ȃ����� ��WEB���痎�Ƃ��Ă����o�C�i���[���������炩��

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
using tstringstream = std::basic_stringstream<_TCHAR>;
using tostringstream = std::basic_ostringstream<_TCHAR>;
using tistringstream = std::basic_istringstream<_TCHAR>;
