/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
// DlgSelectAppID.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgSelectAppID.h"
#include "afxdialogex.h"
#include "IDEHttp.h"
#include "resource.h"
#include "GCLanguage.h"

// CDlgSelectAppID �Ի���

CDlgSelectAppID*	g_selectApps = 0;
IMPLEMENT_DYNAMIC(CDlgSelectAppID, CDialogEx)

CDlgSelectAppID::CDlgSelectAppID(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSelectAppID::IDD, pParent)
{
	g_selectApps = this;
}

CDlgSelectAppID::~CDlgSelectAppID()
{
}

void CDlgSelectAppID::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDC_APPID_LIST, m_cbAppIDs);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSelectAppID, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSelectAppID::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSelectAppID ��Ϣ�������

extern wchar_t *	GetProjectName();
void WINAPI OnUserAppList(Phantom::Name& file, IDCJsonObject& obj, const char* errorText, void* param)//���غ���
{
	if(!g_selectApps)
		return;
	if(errorText){
		g_selectApps->MessageBox(W(errorText), Language(L"��������"), MB_OK|MB_ICONERROR);
		g_selectApps->SetWindowTextW(Language(L"��ȡ��Ȩ���б����!"));
		return;
	}
	int result = obj["result"];
	if(result == 1){
		int count = obj["count"];
		if(count>0){
			CString appkey = AfxGetApp()->GetProfileStringW(L"AppID", GetProjectName(), L"");
			for(int i=0;i<count;i++){
				char buf[128];
				sprintf(buf, "appid%d", i);
				const char* szid = obj[buf];
				Wutf8 w(szid);
				int index = g_selectApps->m_cbAppIDs.AddString(w.buf);
				if(wcsicmp(appkey, w.buf)==0){
					g_selectApps->m_cbAppIDs.SetCurSel(index);
				}
			}
			g_selectApps->m_btOK.EnableWindow(true);
			
		}
	}
	else
	{
		g_selectApps->SetWindowTextW(Language(L"�û���Ϣ���ش���!"));
		MessageResult(g_selectApps->m_hWnd, result);
	}
}

BOOL CDlgSelectAppID::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	IDCJsonObject obj;
	obj["key"] = GetHttpKey();
	Request("pvd_applist", obj, OnUserAppList, true);
	this->m_btOK.EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgSelectAppID::OnBnClickedOk()
{
	if(m_cbAppIDs.GetCurSel()<0){
		MessageBox(Language(L"����Ҫѡ��һ��"));
		return;
	}
	m_cbAppIDs.GetLBText(m_cbAppIDs.GetCurSel(), m_strAppID);
	AfxGetApp()->WriteProfileStringW(L"AppID", GetProjectName(), m_strAppID);
	CDialogEx::OnOK();
}
