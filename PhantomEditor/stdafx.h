
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
#include <afxdhtml.h>




#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#

struct Wutf8
{
	wchar_t* buf;
	Wutf8(const char* w)
	{
		int slen = (int)strlen(w);
		int len = (int)slen * 3 + 1;
		buf = new wchar_t[len];
		len = ::MultiByteToWideChar(CP_UTF8, 0, w, slen, buf, len);
		buf[len] = 0;
	}
	inline	operator const wchar_t*(){return buf;}
	~Wutf8(){if(buf)delete[] buf;}
};

struct Autf8
{
	char* buf;
	Autf8(const wchar_t* w)
	{
		int slen = (int)wcslen(w);
		int len = (int)slen * 3 + 1;
		buf = new char[len];
		len = ::WideCharToMultiByte(CP_UTF8, 0, w, slen, buf, len, 0, 0);
		buf[len] = 0;
	}
	inline	operator const char*(){return buf;}
	~Autf8(){if(buf)delete[] buf;}
};


struct W
{
	wchar_t* buf;
	W(const char* w)
	{
		int slen = (int)strlen(w);
		int len = (int)slen * 3 + 1;
		buf = new wchar_t[len];
		len = ::MultiByteToWideChar(CP_ACP, 0, w, slen, buf, len);
		buf[len] = 0;
	}
	inline	operator const wchar_t*(){return buf;}
	~W(){if(buf)delete[] buf;}
};

struct A
{
	char* buf;
	A(const wchar_t* w)
	{
		int slen = (int)wcslen(w);
		int len = (int)slen * 3 + 1;
		buf = new char[len];
		len = ::WideCharToMultiByte(CP_ACP, 0, w, slen, buf, len, 0, 0);
		buf[len] = 0;
	}
	inline	operator const char*(){return buf;}
	~A(){if(buf)delete[] buf;}
};

struct	format//��ʽ��ansi�ַ���
{
	char		szText[1024];
	inline	format(const char* szFmt,...){_vsnprintf(szText,1024,szFmt,(va_list)(&szFmt+1));}
	inline	operator	char*	(){return szText;}
};
struct	formatw//��ʽ���ַ���(���ֽ�)
{
	wchar_t		szText[1024];
	inline	formatw(const wchar_t* szFmt,...){_vsnwprintf(szText,1024,szFmt,(va_list)(&szFmt+1));}
	inline	operator	wchar_t*	(){return szText;}
};

class base_reg//ע��������
{
public:
	base_reg();
	~base_reg();
	bool	openKey(HKEY hKey, const char* szSubKey);//��һ��ע�����
	bool	createKey(HKEY hKey, const char* szSubKey);//����һ��ע�����
	void	close();//�رմ򿪵�ע���

	int		setBinaryValue(const char* szName, const char* binary, int length);//��ȡ����������
	int		getBinaryValue(const char* szName, char* binary, int length);//��ȡ����������
	bool	addTextValue(const char* szName, const char* szValue);//���ݵ�ǰ�򿪵�ע�����д��һ���ı�
	bool	addIntValue(const char* szName, int nValue);//���ݵ�ǰ�򿪵�ע�����д��һ������
	
	HKEY	m_hKey;
};

extern	VOID	WriteRegValue(const char* szKey, const char* szText);
extern	BOOL	ReadRegValue(const char* szKey, char* szText);
extern	BOOL	GetCopyKeyboard();
extern	BOOL	GetSelectKeyboard();
extern	BOOL	IsKeyDown(int key);
extern	void			SetProjectPath( const char* szBuf );
extern	void			SetProjectPath();
extern	const char*		GetProjectPath();
extern	HWND	GetDeviceWindow();

#include "PhantomManager.h"
using namespace Phantom;
