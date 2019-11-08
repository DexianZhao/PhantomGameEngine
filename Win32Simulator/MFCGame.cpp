
// BaiWanGame.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MFCGame.h"
#include "MFCGameDlg.h"
#include "MyInclude.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBaiWanGameApp

BEGIN_MESSAGE_MAP(CBaiWanGameApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBaiWanGameApp ����

CBaiWanGameApp::CBaiWanGameApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CBaiWanGameApp ����

CBaiWanGameApp theApp;


// CBaiWanGameApp ��ʼ��

BOOL CBaiWanGameApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);
	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	//SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CoInitialize(0);
	SetCharLocale("chs", 0);
	//
	LPSTR szCmd = ::GetCommandLineA();
	if(szCmd && szCmd[0])
	{
		char szExePath[1024];
		int len = ::WideCharToMultiByte(CP_ACP, 0, _wpgmptr, -1, szExePath, 1024, "", 0);
		szExePath[len] = 0;

		char dir[256], file[256];
		_splitpath(szExePath, dir, file, 0, 0);
		strcat(dir, file);
		char szIni[256];
		strcpy(szIni, dir);
		strcat(szIni, "Phantom.ini");
		SetCurrentDirectoryA(dir);
		char path[256];
		strcpy(path, szCmd);
		if(path[strlen(path)-1] =='\\')
			path[strlen(path)-1] = 0;
		_splitpath(path, 0, dir, file, 0);
		char temp[256];
		strcpy(temp, file);
		strcat(temp, "\\bin");
		if(::GetPrivateProfileStringA(file, "path", "", path, 256, szIni))
		{
			::WritePrivateProfileStringA("active", "name", file, szIni);
		}
		else
		{
			WIN32_FIND_DATAA w32;
			HANDLE h = ::FindFirstFileA(temp, &w32);
			if(h == INVALID_HANDLE_VALUE)
			{
			}
			else
			{
				::WritePrivateProfileStringA(file, "path", temp, szIni);
				::WritePrivateProfileStringA(file, "game_width", "960", szIni);
				::WritePrivateProfileStringA(file, "game_height", "640", szIni);
				::WritePrivateProfileStringA(file, "window_width", "960", szIni);
				::WritePrivateProfileStringA(file, "window_height", "640", szIni);
				::WritePrivateProfileStringA("active", "name", file, szIni);
				FindClose(h);
			}
		}
	}
	CBaiWanGameDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	OnAppDestroy();
	WSACleanup();
	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

