//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	�ļ�       :   RenderBufferSettings.cpp
	�������   :   ��Ӱ��Ϸ����

	��Ʊ�д�� :   �Ե���(Ӣ��:ZhaoDexian)
	Email: yuzhou_995@hotmail.com
	
	Copyright 2009-2016 Zhao Dexian
	
	-------------------------------------------------------------------------------------------------


	-------------------------------------------------------------------------------------------------
	*/
//////////////////////////////////////////////////////////////////////////////////////////////////////


// RenderBufferSettings.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include ".\RenderBufferSettings.h"

CRenderBufferSettings*	g_pRenderBufferSettings = 0;
CRenderBufferSettings*	GetRenderBufferSettings()
{
	return g_pRenderBufferSettings;
}

// CRenderBufferSettings �Ի���

IMPLEMENT_DYNAMIC(CRenderBufferSettings, CDialogBase)
CRenderBufferSettings::CRenderBufferSettings(CWnd* pParent /*=NULL*/)
	: CDialogBase(CRenderBufferSettings::IDD, pParent)
{
	g_pRenderBufferSettings	=	this;
	m_scene3D				=	0;
}

CRenderBufferSettings::~CRenderBufferSettings()
{
}

void CRenderBufferSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USE_TARGET_BUFFER, m_chkEnableMultiBuffer);
	DDX_Control(pDX, IDC_BUFFER_SIZE, m_cbBufferSize);
	DDX_Control(pDX, IDC_USE_BLUR, m_chkBlurMode);
	DDX_Control(pDX, IDC_BUFFER_BLUR_SIZE, m_edBlurSize);
}


BEGIN_MESSAGE_MAP(CRenderBufferSettings, CDialogBase)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_USE_TARGET_BUFFER, OnBnClickedUseTargetBuffer)
	ON_CBN_SELCHANGE(IDC_BUFFER_SIZE, OnCbnSelchangeBufferSize)
	ON_BN_CLICKED(IDC_USE_BLUR, OnBnClickedUseBlur)
	ON_BN_CLICKED(IDC_SET_BLUR, OnBnClickedSetBlur)
END_MESSAGE_MAP()


// CRenderBufferSettings ��Ϣ�������

void CRenderBufferSettings::OnBnClickedOk()
{
}

void CRenderBufferSettings::OnBnClickedCancel()
{
	OnCancel();
}

BOOL CRenderBufferSettings::OnInitDialog()
{
	CDialogBase::OnInitDialog();
	m_cbBufferSize.SetItemData(m_cbBufferSize.AddString(Language(L"һ����������С")), 1);
	m_cbBufferSize.SetItemData(m_cbBufferSize.AddString(Language(L"������������С")), 2);
	m_cbBufferSize.SetItemData(m_cbBufferSize.AddString(Language(L"������������С")), 3);
	m_cbBufferSize.SetItemData(m_cbBufferSize.AddString(Language(L"�ı���������С")), 4);
	return TRUE;
}

VOID CRenderBufferSettings::OnChangeScene()
{
	if(!m_scene3D)
		return;
	this->m_chkEnableMultiBuffer.SetCheck(m_scene3D->GetMultiBufferEnable());
	this->m_chkBlurMode.SetCheck(m_scene3D->GetMultiBufferBlurEnable());
	for(int i=0;i<this->m_cbBufferSize.GetCount();i++)
	{
		if(this->m_cbBufferSize.GetItemData(i) == m_scene3D->GetMultiBufferSize())
		{
			this->m_cbBufferSize.SetCurSel(i);
			break;
		}
	}
	wchar_t buf[128];
	swprintf(buf, L"%.03f", m_scene3D->GetMultiBufferBlurSize());
	this->m_edBlurSize.SetWindowText(buf);
}

void CRenderBufferSettings::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogBase::OnShowWindow(bShow, nStatus);
}

void CRenderBufferSettings::OnBnClickedUseTargetBuffer()
{
	if(!m_scene3D)return;
#ifdef Developer_Authorize
	::StudioMessageBox("�˹��ܽ�����ҵ�û�����");
#else
	m_scene3D->SetMultiBufferEnable(this->m_chkEnableMultiBuffer.GetCheck());
#endif
}

void CRenderBufferSettings::OnCbnSelchangeBufferSize()
{
	if(!m_scene3D || this->m_cbBufferSize.GetCurSel() < 0)return;
#ifdef Developer_Authorize
	::StudioMessageBox("�˹��ܽ�����ҵ�û�����");
#else
	m_scene3D->SetMultiBufferSize(this->m_cbBufferSize.GetItemData(this->m_cbBufferSize.GetCurSel()));
#endif
}

void CRenderBufferSettings::OnBnClickedUseBlur()
{
	if(!m_scene3D)return;
#ifdef Developer_Authorize
	::StudioMessageBox("�˹��ܽ�����ҵ�û�����");
#else
	m_scene3D->SetMultiBufferBlurEnable(this->m_chkBlurMode.GetCheck());
#endif
}

void CRenderBufferSettings::OnBnClickedSetBlur()
{
	if(!m_scene3D)return;
#ifdef Developer_Authorize
	::StudioMessageBox("�˹��ܽ�����ҵ�û�����");
#else
	CString str;
	this->m_edBlurSize.GetWindowText(str);
	m_scene3D->SetMultiBufferBlurSize(_wtof(str));
#endif
}
