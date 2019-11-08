// DlgWebView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgWebView.h"
#include "afxdialogex.h"
extern "C"
{
	void SetBuyADOK(BOOL bFail)
	{
	}
};

// CDlgWebView �Ի���

IMPLEMENT_DYNAMIC(CDlgWebView, CDialogEx)

CDlgWebView::CDlgWebView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWebView::IDD, pParent)
{

}

CDlgWebView::~CDlgWebView()
{
}

void CDlgWebView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_URL, m_cbUrl);
	DDX_Control(pDX, IDC_OPEN, m_btOpen);
	DDX_Control(pDX, IDC_BACK_FORWARD, m_spBackForward);
}


BEGIN_MESSAGE_MAP(CDlgWebView, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgWebView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgWebView::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_OPEN, &CDlgWebView::OnBnClickedOpen)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgWebView ��Ϣ�������


void CDlgWebView::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CDlgWebView::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

extern	INT			GetBrowserUrlCount();
extern	const char* GetBrowserUrl(int index);
extern	BOOL		AddBrowserUrl(const char* url);
BOOL CDlgWebView::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_web.Create(m_web.IDD, this);
	m_web.ShowWindow(SW_SHOW);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	int num = GetBrowserUrlCount();
	for(int i=0;i<num;i++)
	{
		m_cbUrl.AddString(GetBrowserUrl(i));
	}
	CRect rc;
	GetClientRect(&rc);
	m_web.MoveWindow(0, 20, rc.Width(), rc.Height()-20);
	m_web.ShowWindow(SW_HIDE);
	m_web.Navigate("http://www.51duli.com");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgWebView::OnBnClickedOpen()
{
	char buf[1024];
	CString url;
	this->m_cbUrl.GetWindowTextA(buf, 1024);
	if(strnicmp(buf, "http://", 7)!=0)
	{
		url = "http://";
		url += buf;
	}
	else
		url = buf;
	if(AddBrowserUrl(url))
		m_cbUrl.AddString(url);
	m_web.Navigate(url);
}


void CDlgWebView::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(m_web.m_hWnd)
	{
		m_web.MoveWindow(0, 20, cx, cy-20);
	}
}
