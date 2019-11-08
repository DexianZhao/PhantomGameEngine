
// BaiWanGameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCGame.h"
#include "MFCGameDlg.h"
#include "afxdialogex.h"
#include "MyInclude.h"
#include "GameManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBaiWanGameDlg �Ի���




CBaiWanGameDlg::CBaiWanGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBaiWanGameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBaiWanGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBaiWanGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOVING()
	ON_BN_CLICKED(IDOK, &CBaiWanGameDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBaiWanGameDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CBaiWanGameDlg ��Ϣ�������
extern	VOID	InitDevice(const RECT& rc);
extern	VOID	SetParentHWND(HWND hWndParent);
extern	VOID	InitWindow();

CBaiWanGameDlg*	g_dlg = 0;

VOID ThisLogPrint(const char* szText)//�����Ϣ
{
#ifdef USE_DLG
	if(g_dlg)
		g_dlg->m_log.AddLog(szText);
#endif
}
extern	const char*	GetProjectName();
extern "C"{
	extern void MyCreatePhantom(int nDiv, int nOS);
};
extern	HWND	GetDeviceWindow();

BOOL		LoadResData(CDynamicArray<char>& rets, const char* szResID, const char* szResType, HMODULE hModule)
{
	HRSRC hRsrc	=	::FindResourceA(hModule, szResID, szResType);
	//��ȡ��Դ�Ĵ�С
	DWORD dwSize = SizeofResource(hModule, hRsrc);
	if(0 == dwSize)
		return FALSE;
	//������Դ
	HGLOBAL hResHandle = LoadResource(hModule, hRsrc);
	if(NULL == hResHandle)
		return FALSE;
	LPVOID pBuffer = LockResource(hResHandle);
	if(NULL == pBuffer)
		return FALSE;
	rets.SetArrayCount(dwSize, false);
	memcpy(rets.GetPtr(), pBuffer, dwSize);
	UnlockResource(hResHandle);
	FreeResource(hResHandle);
	return TRUE;
}

BOOL CBaiWanGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//::SetCurrentDirectoryA("../bin");
	g_dlg = this;
	SetLogPrint(ThisLogPrint);
#ifdef USE_DLG
	m_log.Create(m_log.IDD, 0);
	m_log.ShowWindow(SW_SHOW);
#endif
	m_bind.Create(m_bind.IDD, 0);
	m_bind.ShowWindow(SW_SHOW);
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	assert((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	assert(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		assert(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CRect client, window;
	GetClientRect(&client);
	GetWindowRect(&window);
	int w	=	GetSystemMetrics(SM_CXSCREEN);
	int h	=	GetSystemMetrics(SM_CYSCREEN);
	int windowWidth	=	960;
	int windowHeight	=	640;
	char wdrive[256], wdir[256];
	char szIni[256];// = 
	char screenW[128],screenH[128], current[128];
	_splitpath(_pgmptr, wdrive, wdir, 0, 0);
	strcat(wdrive, wdir);
	strcpy(szIni, wdrive);
	strcat(szIni, "Phantom.ini");
	char szWidth[128], szHeight[128];
	char file[128];
	GetPrivateProfileStringA("active", "name", "", file, 128, szIni);
	::GetPrivateProfileStringA(file, "window_width", "960", szWidth, 128, szIni);
	::GetPrivateProfileStringA(file, "window_height", "640", szHeight, 128, szIni);
	windowWidth = atoi(szWidth);
	windowHeight = atoi(szHeight);
	int left = ::GetProfileIntA("DWZB", "left", (w - windowWidth) / 2);
	int top = ::GetProfileIntA("DWZB", "top", (h - windowHeight) / 2);
	MoveWindow(left, top, windowWidth + (window.Width() - client.Width()), windowHeight + (window.Height() - client.Height()));
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetWindowRect(&window);
	int logHeight = ::GetProfileIntA("DWZB", "logHeight", 200);
#ifdef USE_DLG
	m_log.MoveWindow(window.left, window.bottom, window.Width(), logHeight);
#endif
	int bindHeight = ::GetProfileIntA("DWZB", "bindHeight", 200);
	m_bind.MoveWindow(window.right, window.top, w - window.right, bindHeight);
	m_bind.ShowWindow(SW_HIDE);

	ShowWindow(SW_SHOW);
	SetTimer(0, 40, 0);
	//
	SetParentHWND(m_hWnd);
	InitWindow();
	//AddZipFile("..\\android\\PhantomApp\\data.zip", "assets");
		CDynamicArray<char> defaultZip;
		if(!LoadResData(defaultZip, MAKEINTRESOURCE(IDR_INIT_DATA), "INIT_DATA", AfxGetResourceHandle()))
			return false;
		//
		Phantom::open_zip_mem(defaultZip.GetPtr(), defaultZip.size());

	MyCreatePhantom(1,0);
	RECT rc;
	GetClientRect(&rc);
	InitDevice(rc);
	m_edit.Create(m_edit.IDD, this);
	m_edit.ShowWindow(SW_HIDE);
	//
	g_manager.SetActiveSDK(GetGameManager());
	char buf[512];
	sprintf(buf, "��Ӱ��ƽ̨ģ����[%s]", GetGameManager()->GetGameName());
	SetWindowText(buf);
	//
	//m_webview.Create(m_webview.IDD, this);
	//m_webview.ShowWindow(SW_SHOW);
	//::ShowWindow(GetDeviceWindow(), SW_HIDE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
//BOOL g_bActive = false;
//VOID	ActiveGameMode(BOOL b){
//	return;
//	g_bActive = b;
//	g_dlg->m_webview.ShowWindow(b?SW_HIDE:SW_SHOW);
//	::ShowWindow(GetDeviceWindow(), b?SW_SHOW:SW_HIDE);
//	if(!b)
//	{
//		FreeAllMemoryFiles();
//		g_manager.StopAllMusic();
//		g_luamanager.Destroy();
//	}
//}
extern "C"
{
	BOOL CreatePhantom(int nDiv, int nOS, int* authcode)
	{
		return OnAppCreate(0, nDiv, OSType_Windows, authcode);
	}
	extern	const char*		call_lua(const char* type, const char* params);//����lua�ڲ��ĺ���oncall
    extern	void    showAd(int x, int y, int type, int bShow){
		call_lua("jifen_score", "100");
		bool b = false;
	}
    extern	void    shopBuy(const char* buyName){}
	extern	void    shopRestore(const char* buyName){}
	extern void SetBuyADOK(BOOL bFail);
	void	gotoBuyRemoveAD(int){SetBuyADOK(false);}
	void	gotoComment(){}
	void	openRank(const char* rank){}
	void	setRankScore(const char* rank, int value){}
	void	setAchievement(const char* achievement, int persent){}
	void	openUrl(const char* url){
		::ShellExecuteA(g_dlg->m_hWnd, "open", url, 0, 0, SW_SHOW);
	}
	void	openEdit(const char* szDefault, int x, int y, int w, int h)
	{
		CRect rc(x, y, x + w, y + h);
		g_dlg->ClientToScreen(&rc);
		rc.OffsetRect(-::GetSystemMetrics(SM_CXBORDER), -::GetSystemMetrics(SM_CYCAPTION) - GetSystemMetrics(SM_CYBORDER));
		g_dlg->m_edit.MoveWindow(&rc);
		g_dlg->m_edit.m_ed.MoveWindow(0, 0, w, h);
		g_dlg->m_edit.ShowWindow(SW_SHOW);
	}
	void	closeEdit(char* ret)
	{
		g_dlg->m_edit.m_ed.GetWindowTextA(ret, 256);
		g_dlg->m_edit.ShowWindow(SW_HIDE);
	}
	const char*	onAlert(const char* message, const char* title, const char* type)
	{
		int nType = MB_OK;
		if(stricmp(type, "yesno") == 0)
			nType = MB_YESNO;
		else if(stricmp(type, "okcancel") == 0)
			nType = MB_OKCANCEL;
		else if(stricmp(type, "yesnocancel") == 0)
			nType = MB_YESNOCANCEL;
		int nRet = g_dlg->MessageBox(message, title, nType);
		if(nRet == IDCANCEL)return "cancel";
		if(nRet == IDYES)return "yes";
		if(nRet == IDNO)return "no";
		return "ok";
	}

    int            DrawTextIOS(const unsigned short* text, int textLength, int fontHeight, int fontStyle, const char* fontName, int*inoutW, int*inoutH, int*outImageW, int*outImageH, unsigned char** ret)
	{
		return 0;
	}
    int            DrawTextIOSA(const char* text, int textLength, int fontHeight, int fontStyle, const char* fontName, int*inoutW, int*inoutH, int*outImageW, int*outImageH, unsigned char** ret)
	{
		return 0;
	}
    void    saveConfig(const char* key, const char* value)
	{
		AfxGetApp()->WriteProfileStringA("config", key, value);
	}
    int     loadConfig(const char* key,char* retvalue)
	{
		CString str = AfxGetApp()->GetProfileStringA("config", key, "");
		strcpy(retvalue, str);
		return 1;
	}
	const char* GetDeviceName(char*ch)
	{
		strcpy(ch, "Windows");
		return ch;
	}
	void    SetViewOrientation(int ori)
	{
	}
	void	onVibrator(float f){}
};

int __cdecl OnWin32Proc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

void CBaiWanGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBaiWanGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBaiWanGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



extern	VOID	OnIdleRender();
void CBaiWanGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	static BOOL b = false;
	if(!b)
	{
		b	=	true;
		if(::IsWindowVisible(GetDeviceWindow()))
			OnIdleRender();
		b	=	false;
	}
	CDialogEx::OnTimer(nIDEvent);
}

extern	HWND	GetDeviceWindow();
void CBaiWanGameDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(cx > 0 && cy > 0 && GetDeviceWindow())
		::MoveWindow(GetDeviceWindow(), 0, 0, cx, cy, true);
	//if(this->m_webview.m_hWnd)
	//{
	//	::MoveWindow(m_webview.m_hWnd, 0, 0, cx, cy, true);
	//	ActiveGameMode(g_bActive);
	//}
	//OnAppResize(cx, cy);
}


void CBaiWanGameDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
#ifdef USE_DLG
	if(m_log.m_hWnd){
		int w	=	GetSystemMetrics(SM_CXSCREEN);
		int h	=	GetSystemMetrics(SM_CYSCREEN);
		CRect window;
		CRect rcB, rcL;
		GetWindowRect(&window);
		m_log.GetWindowRect(&rcL);
		m_log.MoveWindow(window.left, window.bottom, window.Width(), rcL.Height());
		//m_bind.GetWindowRect(&rcB);
		if(m_bind.m_hWndBind)
		{
			//::GetWindowRect(m_bind.m_hWndBind, &rcB);
			//::MoveWindow(m_bind.m_hWndBind, window.right, window.top, w - window.right, rcB.Height(), true);
		}
		char buf[128];
		sprintf(buf, "%d", window.left);
		::WriteProfileStringA("DWZB", "left", buf);
		sprintf(buf, "%d", window.top);
		::WriteProfileStringA("DWZB", "top", buf);
		sprintf(buf, "%d", rcL.Height());
		::WriteProfileStringA("DWZB", "logHeight", buf);
		sprintf(buf, "%d", rcB.Height());
		::WriteProfileStringA("DWZB", "bindHeight", buf);
	}
#endif
	CDialogEx::OnMoving(fwSide, pRect);

	// TODO: �ڴ˴������Ϣ����������
}


void CBaiWanGameDlg::OnBnClickedOk()
{
}


void CBaiWanGameDlg::OnBnClickedCancel()
{
	if(MessageBox("�Ƿ����Ҫ�˳���", 0, MB_YESNO) == IDYES)
		CDialogEx::OnCancel();
}
