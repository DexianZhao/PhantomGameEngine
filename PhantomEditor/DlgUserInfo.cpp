// DlgUserInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgUserInfo.h"
#include "afxdialogex.h"
#include "IDEHttp.h"
#include "DlgBuyVIP.h"

// CDlgUserInfo �Ի���

CDlgUserInfo*	g_userinfo = 0;

IMPLEMENT_DYNAMIC(CDlgUserInfo, CDialogBase)

CDlgUserInfo::CDlgUserInfo(CWnd* pParent /*=NULL*/)
	: CDialogBase(CDlgUserInfo::IDD, pParent)
{
	g_userinfo = this;
}

CDlgUserInfo::~CDlgUserInfo()
{
	g_userinfo = 0;
}

extern	BOOL	CheckLogin();
VOID	ShowUserInfo()
{
	if(!CheckLogin())
		return;
	CDlgUserInfo dlg;
	dlg.DoModal();
}


void CDlgUserInfo::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_HUANYING_POINT, m_edPPoint);
	DDX_Control(pDX, IDC_USER_LEVEL, m_edLevel);
	DDX_Control(pDX, IDC_USER_VIPEND, m_edVipEnd);
	CDialogBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgUserInfo, CDialogEx)
	ON_BN_CLICKED(IDC_CHANGEACCOUNT, &CDlgUserInfo::OnBnClickedChangeaccount)
	ON_BN_CLICKED(IDC_BUY_TO_URL, &CDlgUserInfo::OnBnClickedBuyToUrl)
	ON_BN_CLICKED(IDC_BUY_TO_URL2, &CDlgUserInfo::OnBnClickedBuyToUrl2)
	ON_BN_CLICKED(IDCANCEL, &CDlgUserInfo::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgUserInfo ��Ϣ�������

extern	VOID	Reinit();
void CDlgUserInfo::OnBnClickedChangeaccount()
{
	if(MessageBox(L"��Ҫ��������������֤��ȷ������������", 0, MB_YESNO)==IDNO)
		return;
	WriteRegValue("password", "");
	Reinit();
	OnCancel();//
}

void	SetUserInfoPPoint(int nvip, int p, const char* vipend){
	if(!g_userinfo)return;
	wchar_t buf[128];
	swprintf(buf, L"%d", p);
	g_userinfo->m_edPPoint.SetWindowTextW(buf);
	int level = nvip;
	if(level == 0)
		g_userinfo->m_edLevel.SetWindowTextW(Language(L"�ο�"));
	else
	{
		swprintf(buf, L"VIP%d", level);
		g_userinfo->m_edLevel.SetWindowTextW(buf);
	}
	g_userinfo->m_edVipEnd.SetWindowTextW(W(vipend).buf);
}
void WINAPI OnUserInfoCallback(Phantom::Name& file, IDCJsonObject& obj, const char* errorText, void* param)//���غ���
{
	if(!g_userinfo)
		return;
	if(errorText){
		g_userinfo->MessageBox(W(errorText), Language(L"��������"), MB_OK|MB_ICONERROR);
		g_userinfo->SetWindowTextW(Language(L"��ȡ������Ϣ���ִ���!"));
		return;
	}
	int result = obj["result"];
	if(result == 1){
		//д�����һ�ε�¼���˺�����
		int nVip = obj["vip"];
		SetIsVIP(nVip);
		if(nVip)
			SetVipCode(obj["code"]);
		//
		int point = obj["ppoint"];
		SetPPoint(point);
		MonthPoint mp;
		mp.month1 = obj["mpoint"];
		mp.month6 = obj["mpoint6"];
		mp.month12 = obj["mpoint12"];
		mp.month24= obj["mpoint24"];
		mp.vipurl = obj["vipurl"].operator LPCSTR();
		SetMonthPoint(mp);
		const char* vipend = obj["vipend"];
		SetUserInfoPPoint(nVip, point, vipend);
		g_userinfo->GetDlgItem(IDC_BUY_TO_URL)->EnableWindow(true);
		g_userinfo->GetDlgItem(IDC_BUY_TO_URL2)->EnableWindow(true);
		g_userinfo->SetWindowTextW(Language(L"�û���Ϣ"));
	}
	else
	{
		g_userinfo->SetWindowTextW(Language(L"�û���Ϣ���ش���!"));
		MessageResult(g_userinfo->m_hWnd, result);
	}
}

BOOL CDlgUserInfo::OnInitDialog()
{
	CDialogBase::OnInitDialog();
	IDCJsonObject obj;
	obj["key"] = GetHttpKey();
	Request("pvd_userinfo", obj, OnUserInfoCallback, true);
	this->SetWindowTextW(Language(L"�ȴ�������Ϣ..."));
	GetDlgItem(IDC_BUY_TO_URL)->EnableWindow(false);
	GetDlgItem(IDC_BUY_TO_URL2)->EnableWindow(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgUserInfo::OnBnClickedBuyToUrl()
{
	ShellExecuteA( NULL, "open", "http://www.aixspace.com/buy/", NULL, NULL, SW_SHOWNORMAL);
}


void CDlgUserInfo::OnBnClickedBuyToUrl2()
{
	CDlgBuyVIP dlg(this);
	dlg.DoModal();
}


void CDlgUserInfo::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
