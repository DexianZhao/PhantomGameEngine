/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/

// phantom-gc.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "afxdatarecovery.h"
#include "phantom-gc.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "phantom-gcDoc.h"
#include "phantom-gcView.h"
#include "GCDefine.h"
#include "GCLanguage.h"
#include "IDEHttp.h"
#include "LoginDialog.h"
#include "../PhantomEngine/encrypt.h"
#include "PhantomDB.h"
#include "MyLuaEditor.h"
#include "io.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern BOOL	LoadResData(CDynamicArray<char>& rets, const wchar_t* szResID, const wchar_t* szResType, HMODULE hModule);
class CLogoDialog : public CDialogEx
{
public:
	CLogoDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogoDialog();

// �Ի�������
	enum { IDD = IDD_LOGO };

	CImage	m_imgLogo;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

CLogoDialog::CLogoDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogoDialog::IDD, pParent)
{
}

CLogoDialog::~CLogoDialog()
{
}

void CLogoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogoDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CLogoDialog ��Ϣ�������

BOOL	LoadResImage(CImage& img, const wchar_t* szName)
{
	HRSRC hRsrc	=	::FindResourceW(NULL, szName, L"MAIN");//
	//��ȡ��Դ�Ĵ�С
	DWORD dwSize = SizeofResource(NULL, hRsrc);
	if(0 == dwSize)
		return FALSE;
	//������Դ
	HGLOBAL hResHandle = LoadResource(NULL, hRsrc);
	if(NULL == hResHandle)
		return FALSE;
	IStream* pStream = 0;
	bool bRet	=	false;
	LPVOID pBuffer = LockResource(hResHandle);
	if(NULL == pBuffer)
		return FALSE;
	//
	HGLOBAL hGlobal = GlobalAlloc(GMEM_FIXED, dwSize);
	void* pVoid = GlobalLock(hGlobal);
	memcpy(pVoid, pBuffer, dwSize);
	GlobalUnlock(hGlobal);
	UnlockResource(hResHandle);
	FreeResource(hResHandle);
	//
	if(SUCCEEDED(::CreateStreamOnHGlobal(hGlobal, false, &pStream)))
	{
		if(!img.IsNull())
			img.Destroy();
		if(SUCCEEDED(img.Load(pStream)))
			bRet = true;
	}
	GlobalFree(hGlobal);
	return bRet;
}

void CLogoDialog::OnBnClickedOk(){}
void CLogoDialog::OnBnClickedCancel(){}
BOOL CLogoDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_SHOW);
	if(!LoadResImage(m_imgLogo, MAKEINTRESOURCE(IDR_MAIN2)))
		return FALSE;
	INT cx	=	::GetSystemMetrics(SM_CXSCREEN);
	INT cy	=	::GetSystemMetrics(SM_CYSCREEN);
	int w	=	m_imgLogo.GetWidth();
	int h	=	m_imgLogo.GetHeight();
	CRect rcWindow((cx - w)/2, (cy - h)/2, 0, 0);
	rcWindow.right	=	rcWindow.left + w;
	rcWindow.bottom	=	rcWindow.top + h;
	MoveWindow(&rcWindow);
	return TRUE;
}

void CLogoDialog::OnTimer(UINT_PTR nIDEvent)
{
	OnOK();
	CDialogEx::OnTimer(nIDEvent);
}

void CLogoDialog::OnPaint()
{
	CPaintDC dc(this);
	HDC hdc	=	this->m_imgLogo.GetDC();
	BitBlt(dc.m_hDC, 0, 0, m_imgLogo.GetWidth(), m_imgLogo.GetHeight(), hdc, 0, 0, SRCCOPY);
	m_imgLogo.ReleaseDC();
}

BOOL CLogoDialog::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

COLORREF	MaskText::Read(int mask, COLORREF c)
{
	char buf[128];
	sprintf(buf, "mask%d", mask);
	return GetConfigInt(buf, c);
}
VOID		MaskText::Write(int mask, COLORREF c)
{
	char buf[128];
	sprintf(buf, "mask%d", mask);
	SetConfigInt(buf, c);
}

// CPhantomGCApp

BEGIN_MESSAGE_MAP(CPhantomGCApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CPhantomGCApp::OnAppAbout)
	ON_COMMAND(ID_BUY_PROFESSIONAL, &CPhantomGCApp::OnBuyProfessional)
	ON_COMMAND(ID_OPEN_HELP, &CPhantomGCApp::OnShowHelp)
	ON_COMMAND(ID_GOTO_FORUM, &CPhantomGCApp::OnGotoForum)

	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CPhantomGCApp ����
CPhantomGCApp*	g_myapp = 0;
CPhantomGCApp::CPhantomGCApp()
{
	g_myapp	=	this;
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("PhantomVD.AppID.1.8"));

	m_nLastTickTime		=	0;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}
std::string		g_authCode;

DWORD	WINAPI	ShowLogoDialog(LPVOID lpParameter)
{
	CLogoDialog logo;
	logo.DoModal();
	return 0;
}

// Ψһ��һ�� CPhantomGCApp ����

CPhantomGCApp theApp;

VOID	RegisterFileType(const char* szFileExt, const char* szFileType, const char* szViewName, int nIconID, BOOL bIsPlatform = false)
{
	char szFilePath[512];
	int len = ::WideCharToMultiByte(CP_ACP, 0, _wpgmptr, -1, szFilePath, 512, 0, 0);
	szFilePath[len] = 0;
	if(bIsPlatform)
	{
		char szDrive[255], szDir[256];
		_splitpath(szFilePath, szDrive, szDir, 0, 0);
		strcat(szDrive, szDir);
		strcat(szDrive, "PhantomPlatform.exe");
		strcpy(szFilePath, szDrive);
	}
	base_reg reg;
	reg.createKey(HKEY_CLASSES_ROOT, szFileExt);
	reg.addTextValue(0, format("PhantomGC_%s.Document", szFileType));
	//
	reg.createKey(HKEY_CLASSES_ROOT, format("PhantomGC_%s.Document", szFileType));
	reg.addTextValue(0, szViewName);
	reg.addTextValue("AppUserModelID", "PhantomGC.AppID.1.8");
	//
	reg.createKey(HKEY_CLASSES_ROOT, format("PhantomGC_%s.Document\\DefaultIcon", szFileType));
	reg.addTextValue(0, format("%s,%d", szFilePath, nIconID));
	//
	reg.createKey(HKEY_CLASSES_ROOT, format("PhantomGC_%s.Document\\shell", szFileType));
	reg.createKey(HKEY_CLASSES_ROOT, format("PhantomGC_%s.Document\\shell\\open", szFileType));
	reg.createKey(HKEY_CLASSES_ROOT, format("PhantomGC_%s.Document\\shell\\open\\command", szFileType));
	//char szDrive[256], szDir[256];
	//_splitpath(szFilePath, szDrive, szDir, 0, 0);
	//strcat(szDrive, szDir);
	//strcat(szDrive, "PhantomVDOpen.exe");
	reg.addTextValue(0, format("\"%s\" \"%%1\"", szFilePath));
}

// CPhantomGCApp ��ʼ��

#pragma data_seg("PhantomShare") // ���干���
HWND	g_hWndPhantomFrame	=	0;	//ֻ������һ��ʵ��������������ֵ�������Ϣ����
BOOL	g_bInitialized		=	false;
#pragma data_seg()
#pragma comment(linker, "/Section:PhantomShare,RWS") // ���߱������ö�Ϊ�����

extern	VOID			InitTypeOptions();

VOID	Reinit()
{
	g_hWndPhantomFrame	=	0;	//ֻ������һ��ʵ��������������ֵ�������Ϣ����
	g_bInitialized		=	false;
	ShellExecuteA( NULL, "open", A(_wpgmptr).buf, NULL, NULL, SW_SHOWNORMAL);
}

const char*	GetDocumentPath()
{
	static std::string strDocument;
	if(!strDocument.empty())
		return strDocument.c_str();
	LPITEMIDLIST pidl=NULL;
 	char szDocument[512];
	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &pidl);
    if(pidl && SHGetPathFromIDListA(pidl, szDocument))
    {
		strcat(szDocument, "\\Phantom Games");
		CreateDirectoryA(szDocument, NULL);
		strcat(szDocument, "\\IDE");
		CreateDirectoryA(szDocument, NULL);
		strcat(szDocument, "\\");
		strDocument	=	szDocument;
	}
	return strDocument.c_str();
}

VOID	SetExecutePath()
{
	wchar_t szDrive[256], szDir[256];
	_wsplitpath(_wpgmptr, szDrive, szDir, 0, 0);
	wcscat(szDrive, szDir);
	SetProjectPath(A(szDrive));
}
//extern	VOID	SetOpenHttpFile(const wchar_t* szUrl);
//extern	std::vector<unsigned char> g_authCodeVec;
extern	VOID	CreateNewFile(int nType);
wchar_t g_szProjectName[128] = {0};
wchar_t *	GetProjectName()
{
	return g_szProjectName;
}

VOID	WriteRegValue(const char* szKey, const char* szText){
	g_myapp->WriteString(W(szKey), W(szText));
}
BOOL	ReadRegValue(const char* szKey, char* szText){
	strcpy(szText, A(g_myapp->GetString(W(szKey), L"")));
	return (szText[0]!=0);
}

//VOID	OpenMyUrl()
//{
//	//SetOpenHttpFile(L"http://www.aixspace.com");
//}

VOID	OnDownloadVersion(const char* requestText, const char* indocFile, std::vector<char>& buffers, BOOL bError)
{
	//int newV = atoi(&buffers.at(0));
	//int oldV = PHANTOM_ENGINE_VERSION;//::GetProfileIntA("PhantomV1", "version", 1900);//���°汾1900
	//::WriteProfileStringA("Phantom", "newversion", &buffers.at(0));
	//if(newV>oldV)
	//{
	//	if(GetMainFrame()->MessageBox(L"���°汾�������Ƿ�Ҫ���µ����°汾��", L"���°汾", MB_YESNO) == IDNO)
	//		return;
	//	WinExec("update.exe", SW_SHOW);
	//	::PostQuitMessage(0);
	//}
}
//extern	void	SetServerIP(const char* ip);
//void WINAPI OnRequestIP(Name& file, IDCJsonObject& obj, const char* errorText, void* param)
//{
//	if(errorText){
//		GetMainFrame()->MessageBox(W(errorText));
//		return;
//	}
//	const char* pvdapp = obj["pvdapp"];
//	int newV = obj["version"];
//	const char* szfile = obj["downloadurl"];
//	SetServerIP(pvdapp);
//	//AfxGetApp()->WriteProfileStringW(L"system", L"pvdapp", W(pvdapp).buf);
//	int oldV = GetProfileIntA("Phantom", "version", PHANTOM_ENGINE_VERSION);//���°汾2000
//	char szNewV[128];
//	sprintf(szNewV, "%d", newV);
//	::WriteProfileStringA("Phantom", "newversion", szNewV);
//	::WriteProfileStringA("Phantom", "params", szfile);
//	const char* desc = obj["desc"];
//	if(newV>oldV)
//	{
//		if(GetMainFrame()->MessageBox(W(desc).buf, L"���°汾���Ը��£��Ƿ���£�", MB_YESNO) == IDNO)
//			return;
//		WinExec("upd.exe", SW_SHOW);
//		::PostQuitMessage(0);
//	}
//}
//VOID	CheckRequestIP(){
//	static BOOL bRequest = false;
//	if(!bRequest){
//		RequestIP(OnRequestIP, GetHomeUrl());
//		bRequest = true;
//	}
//}
int g_nGameWidth = 960;
int g_nGameHeight = 640;
int	GetGameWidth(){return g_nGameWidth;}
int	GetGameHeight(){return g_nGameHeight;}
extern void SetPngCompress(int n);
extern BOOL	LoadResData(CDynamicArray<char>& rets, const wchar_t* szResID, const wchar_t* szResType, HMODULE hModule);
BOOL CPhantomGCApp::InitInstance()
{
	if(g_hWndPhantomFrame || g_bInitialized)
	{
		if(!g_hWndPhantomFrame)
			return false;
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);
		wchar_t szExt[128];
		_wsplitpath(cmdInfo.m_strFileName, 0, 0, 0, szExt);
		if(wcsicmp(szExt, L".rpgproj") != 0)
		{
			char buf[512];
			int len = ::WideCharToMultiByte(CP_ACP, 0, cmdInfo.m_strFileName, -1, buf, 512, 0, 0);
			if(len > 0)
			{
				buf[len] = 0;
				FILE* f = fopen(buf, "rb");
				if(f)
				{
					fclose(f);
					//
					COPYDATASTRUCT cd;
					memset(&cd, 0, sizeof(cd));
					cd.dwData	=	WM_DDE_FILEOPEN;
					cd.lpData	=	buf;
					cd.cbData	=	len + 1;
					SendMessage(g_hWndPhantomFrame, WM_COPYDATA, 0, (LPARAM)&cd);
					return false;
				}
			}
		}
	}
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);
	SetExecutePath();
	char szConfig[512];
	strcpy(szConfig, GetDocumentPath());
	strcat(szConfig, "config.ini");
	LoadConfigs(szConfig);
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	const wchar_t* szCmd = cmdInfo.m_strFileName;
	if(szCmd && szCmd[0])
	{
		char dir[256], file[256], ext[128];
		_splitpath(A(_wpgmptr).buf, dir, file, 0, 0);
		char szMydir[256];
		strcat(dir, file);
		strcpy(szMydir, dir);
		char szIni[256];
		strcpy(szIni, dir);
		strcat(szIni, "Phantom.ini");
		{
			WIN32_FIND_DATAA w32;
			HANDLE h = ::FindFirstFileA(szIni, &w32);
			if(h == INVALID_HANDLE_VALUE)
			{
				FILE* f = fopen(szIni, "wb");
				const char* szInit = "[active]\r\n";
				fwrite(szInit,strlen(szInit), 1, f);
				fclose(f);
			}
			else
				FindClose(h);
		}
		SetCurrentDirectoryA(dir);
		char path[256];
		strcpy(path, A(szCmd).buf);
		if(path[strlen(path)-1] =='\\')
			path[strlen(path)-1] = 0;
		_splitpath(path, 0, dir, file, 0);
		if(::GetPrivateProfileStringA(file, "path", "", path, 256, szIni))
		{
			::WritePrivateProfileStringA("active", "name", file, szIni);
		}
		else
		{
			char temp[256];
			strcpy(temp, A(szCmd).buf);
			strcat(temp, "\\bin");
			WIN32_FIND_DATAA w32;
			HANDLE h = ::FindFirstFileA(temp, &w32);
			if(h == INVALID_HANDLE_VALUE)
			{
				return false;
			}
			else
			{
				const char* mineDir = temp + strlen(szMydir);
				::WritePrivateProfileStringA(file, "path", mineDir, szIni);
				::WritePrivateProfileStringA(file, "game_width", "960", szIni);
				::WritePrivateProfileStringA(file, "game_height", "640", szIni);
				::WritePrivateProfileStringA(file, "window_width", "960", szIni);
				::WritePrivateProfileStringA(file, "window_height", "640", szIni);
				::WritePrivateProfileStringA("active", "name", file, szIni);
				FindClose(h);
			}
		}
	}
	int nScreenW = 0;
	int nScreenH = 0;
	if(fexist("Phantom.ini"))
	{
		wchar_t wdrive[256], wdir[256];
		_wsplitpath(_wpgmptr, wdrive, wdir, 0, 0);
		wcscat(wdrive, wdir);
		wchar_t szIni[256];// = 
		wcscpy(szIni, wdrive);
		wcscat(szIni, L"Phantom.ini");
		wchar_t active[128];
		wchar_t pngcompress[125];
		::GetPrivateProfileStringW(L"active", L"name", L"", active, 128, szIni);
		wchar_t screenW[128],screenH[128], current[128];
		::GetPrivateProfileStringW(active, L"window_width", L"", screenW, 128, szIni);
		::GetPrivateProfileStringW(active, L"window_height", L"", screenH, 128, szIni);
		::GetPrivateProfileStringW(active, L"path", L"", current, 128, szIni);
		::GetPrivateProfileStringW(active, L"pngcompress", L"", pngcompress, 128, szIni);
		SetPngCompress(_wtoi(pngcompress));
		wchar_t screenW2[128],screenH2[128];
		::GetPrivateProfileStringW(active, L"game_width", L"", screenW2, 128, szIni);
		::GetPrivateProfileStringW(active, L"game_height",L"", screenH2, 128, szIni);
		g_nGameWidth = _wtoi(screenW2);
		g_nGameHeight = _wtoi(screenH2);
		nScreenW = _wtoi(screenW);
		nScreenH = _wtoi(screenH);
		wcscpy(g_szProjectName, active);
		wcscat(wdrive, current);
		wcscat(wdrive, L"\\");
		SetProjectPath(A(wdrive));
		//
	}
	//
	SetProjectPath();
	DWORD threadID	=	0;
	HANDLE hThread = ::CreateThread(NULL, NULL, ShowLogoDialog, 0, 0, &threadID);

	g_bInitialized	=	true;
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();
	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	//

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(16);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
	InitContextMenuManager();
	InitKeyboardManager();
	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = true;
	ttParams.m_bBoldLabel	=	true;
	ttParams.m_bDrawDescription	=	true;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MyTYPE,
		RUNTIME_CLASS(CPhantomGCDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CPhantomGCView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	GetLanguagesPtr()->LoadFromFile();
#ifdef _DEBUG
	GetLanguagesDebug()->LoadDebug();
#endif
	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		//delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	UpdateMainText(L"");
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������
	// ������/��
	m_pMainWnd->DragAcceptFiles();

	// ������׼ shell ���DDE�����ļ�������������

	// ���á�DDE ִ�С�
	EnableShellOpen();
	//RegisterShellFileTypes(TRUE);
	RegisterFileType(".rpgmesh", "PhantomGeometry", A(Language(L"��Ӱ��Ϸ����-ģ���ļ�")), 10);
	//RegisterFileType(".rpgEmt", "PhantomEmitter", A(Language(L"��Ӱ��Ϸ����-�����ļ�")), 18);
	RegisterFileType(".pakmesh", "PhantomGeometry2", A(Language(L"��Ӱ��Ϸ����-������ģ���ļ�")), 10);
	RegisterFileType(".pakui", "PhantomUI2", A(Language(L"��Ӱ��Ϸ����-�����Ľ����ļ�")), 14);
	//RegisterFileType(".rpgunit", "PhantomUnit3D", A(Language(L"��Ӱ��Ϸ����-3D�����ļ�")), 13);
	RegisterFileType(".rpgui", "PhantomUI", A(Language(L"��Ӱ��Ϸ����-�����ļ�")), 14);
	//RegisterFileType(".rpg2D", "PhantomUnit2D", A(Language(L"��Ӱ��Ϸ����-2D�����ļ�")), 17);
	//RegisterFileType(".rpgCur", "PhantomCursor", A(Language(L"��Ӱ��Ϸ����-����ļ�")), 19);
	//RegisterFileType(".rpgProj", "PhantomGameProject", A(Language(L"��Ӱ��Ϸ����-��Ŀ�����ļ�")), 21);
	RegisterFileType(".rpgscene", "PhantomScene3D", A(Language(L"��Ӱ��Ϸ����-����3D�����ļ�")), 22);
	//RegisterFileType(".rpg2ds", "PhantomScene2D", A(Language(L"��Ӱ��Ϸ����-����2.5D�����ļ�")), 22);
	//
	RegisterFileType(".lua", "Lua Script File", A(Language(L"Lua �ű��ļ�")), 33);
	//
	g_hWndPhantomFrame	=	m_pMainWnd->m_hWnd;
	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	ProcessShellCommand(cmdInfo);
	::TerminateThread(hThread, 0);
	CloseHandle(hThread);
	//
	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	pMainFrame->SetForegroundWindow();
	UpdateMainTitle();
	CDynamicArray<char> codeXml;
	if(!LoadResData(codeXml, MAKEINTRESOURCE(IDR_CODE_LUA1), L"CODE_LUA", AfxGetResourceHandle()))
		return false;
	FILE* f = fopen("E:/PhantomGameEngine/lua_code.xml", "rb");
	if(f){
		int len = filelength(_fileno(f));
		codeXml.SetArrayCount(len, false);
		fread(codeXml.GetPtr(), len, 1, f);
		fclose(f);
	}
	GetCodeXmlManager()->LoadContent(codeXml);
	//
	if(nScreenW > 0 && nScreenH > 0)
		SetRenderWindowSize(nScreenW, nScreenH);
	InitTypeOptions();
	::ShowWindow(GetDeviceWindow(), SW_HIDE);
	return true;
}

extern	VOID	DeleteLanguages();
extern	VOID	DeleteCodeManager();
int CPhantomGCApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);
	char szConfig[512];
	strcpy(szConfig, GetDocumentPath());
	strcat(szConfig, "config.ini");
	SaveConfigs(szConfig);
	//
	DestroyConfigs();
	//LuaCleanup();
#ifdef _DEBUG
	GetLanguagesDebug()->SaveToFile();
#endif
	DeleteLanguages();
	DeleteCodeManager();
	return CWinAppEx::ExitInstance();
}

int	Get_MAX_FREE_CHAPTER_COUNT()
{
	return 9999992;
}
int	Get_MAX_FREE_DRAMA_COUNT()
{
	return 99999;
}
int	Get_MAX_FREE_PLOT_OBJECT()
{
	return 97923;
}
int	Get_MAX_FREE_PLOT_ACTION()
{
	return 97832;
}
int	Get_MAX_FREE_PLOT_CALL()
{
	return 98232;
}

int	Get_MAX_ADD_UNITACTION()
{
	return 98232;
}
int	Get_MAX_ADD_ELEMENT()
{
	return 98232;
}

int	Get_MAX_MESH_ACTION_COUNT()
{
	return 98232;
}

extern int Get_MAX_SCENE_OBJECT()
{
	return 98232;
}
extern int Get_MAX_SCENE_SKY()
{
	return 98232;
}
extern int Get_MAX_SCENE_FOG()
{
	return 98232;
}
extern int Get_MAX_SCENE_CAMERA()
{
	return 98232;
}
extern int Get_MAX_SCENE_GRASS()
{
	return 98232;
}
extern int Get_MAX_SCENE_WATER()
{
	return 98232;
}
extern int Get_MAX_SCENE_SIZE()
{
	return 538;
}

extern	int	Get_MAX_CONTROL_COUNT()
{
	return 104020;
}

// CPhantomGCApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	CImage m_imgLogo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CPhantomGCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
unsigned char g_buy_text[] = {0x9e,0xa5,0xc8,0xc4,0x34,0xc2,0x57,0xf8,0xe3,0x23,0xbb,0xb7,0x73,0x8c,0xd5,0xd0,0x81,0x60,0x1f,0x58,0xa3,0xd4};
unsigned char g_buy_password[] = {0xee,0xc9,0xa4,0xac,0x16,0xf5,0x60,0x97,0x8c,0x4c,0x8d,0x9c,0x0f,0xf3,0xac,0xa5,0xfc,0x40,0x29,0x23,0xd4,0xa1,0x1b,0x3e,0x30,0x8d,0xfc,0x79,0x02,0x0a,0xab,0x7a};

extern	int	g_nAuthModeTemp;//	=	AuthGUID::AuthFlags_Error;
void CPhantomGCApp::OnBuyProfessional()
{
}

void CPhantomGCApp::OnGotoForum()
{
	//unsigned char g_text[] = {0xf6,0xf2,0x86,0x84,0x30,0x8b,0x99,0xfa,0xa7,0xa9,0xb0,0x2c,0x31,0x73,0x74,0x17,0x57,0xb8,0x38,0x48,0xe8,0x98,0x2e,0xd5,0x2c,0xd2,0x7a,0x43,0x82,0x52,0x22,0x9e,0xb0,0xf6,0x9a,0x84};
	//unsigned char g_password[] = {0x86,0x9e,0xea,0xec,0x12,0xbc,0xae,0x95,0xc8,0xc6,0x86,0x57,0x46,0x18,0x01,0x66,0x2c,0x8d,0x4c,0x39,0x96,0xe5,0x18,0xae,0x5b,0xa7,0x4d,0x3d,0xf5,0x38,0x4f,0xeb};
	//OpenMyUrl();//SetOpenHttpFile(L"http://www.aixspace.com/");
	CreateNewFile(FileViewerType_HomeViewer);
	//ShellExecuteA( NULL, "open", CTextCrypts(g_password, sizeof(g_password), g_text, sizeof(g_text)), NULL, NULL, SW_SHOWNORMAL);
}
void CPhantomGCApp::OnShowHelp()
{
	wchar_t exeDir[256], exeTemp[256];
	_wsplitpath(_wpgmptr, exeDir, exeTemp, 0, 0);
	wcscat(exeDir, exeTemp);
	wcscat(exeDir, L"PhantomHelpLua.chm");
	ShellExecuteA( NULL, "open", A(exeDir).buf, NULL, NULL, SW_SHOWNORMAL);
}
// CPhantomGCApp �Զ������/���淽��

void CPhantomGCApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CPhantomGCApp::LoadCustomState()
{
}

void CPhantomGCApp::SaveCustomState()
{
}

// CPhantomGCApp ��Ϣ�������

BOOL		g_bUpdateRobbinNow	=	false;
VOID		UpdateRobbinNow()
{
	g_bUpdateRobbinNow	=	true;
}

BOOL		CPhantomGCApp::IsUpdateCmdUI()
{
	UINT uNow	=	::GetTickCount();
	if((uNow - m_nLastTickTime) > 200 || g_bUpdateRobbinNow)
	{
		m_nLastTickTime		=	uNow;
		g_bUpdateRobbinNow	=	false;
		return true;
	}
	//Sleep(200);
	return false;
}

BOOL		CPhantomGCApp::OnIdle(LONG lCount) // return TRUE if more idle processing
{
	//if(GetMainFrame())
	//{
		//if(GetMainFrame()->m_wndRibbonBar.GetHideFlags() == AFX_RIBBONBAR_HIDE_ELEMENTS)
			//return false;
	//}
	//if(!IsUpdateCmdUI())
		//return false;
	return __super::OnIdle(lCount);
}

BOOL CPhantomGCApp::PreTranslateMessage(MSG* pMsg)
{
	return CWinAppEx::PreTranslateMessage(pMsg);
}


CDocument* CPhantomGCApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	if(wcsnicmp(lpszFileName, L"http://", 7) != 0)
	{
		FILE* f = fopen(A(lpszFileName), "rb");
		if(!f)
			return 0;
		fclose(f);
	}
	CDocument* doc	=	CWinAppEx::OpenDocumentFile(lpszFileName);
	UpdateMainTitle();
	return doc;
}


void CAboutDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


void CAboutDlg::OnPaint()
{
	CPaintDC dc(this);
	HDC hdc	=	this->m_imgLogo.GetDC();
	BitBlt(dc.m_hDC, 0, 0, m_imgLogo.GetWidth(), m_imgLogo.GetHeight(), hdc, 0, 0, SRCCOPY);
	m_imgLogo.ReleaseDC();
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_SHOW);
	//
	wchar_t szTitle[512];
	wcscpy(szTitle, L"��Ӱ��Ϸ����");
	SetWindowText(szTitle);
	//
	LoadResImage(m_imgLogo, MAKEINTRESOURCE(IDR_MAIN2));
	return TRUE;
}
