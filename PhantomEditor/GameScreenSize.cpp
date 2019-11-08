/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
// GameScreenSize.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameScreenSize.h"
#include "afxdialogex.h"
#include "GCMFCHelper.h"
#include "GCRenderSystem.h"

// CGameScreenSize �Ի���

IMPLEMENT_DYNAMIC(CGameScreenSize, CDialogEx)

CGameScreenSize::CGameScreenSize(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameScreenSize::IDD, pParent)
{

}

CGameScreenSize::~CGameScreenSize()
{
}

void CGameScreenSize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCREEN_X, m_edScreenX);
	DDX_Control(pDX, IDC_SCREEN_Y, m_edScreenY);
}


BEGIN_MESSAGE_MAP(CGameScreenSize, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGameScreenSize::OnBnClickedOk)
END_MESSAGE_MAP()


// CGameScreenSize ��Ϣ�������


void CGameScreenSize::OnBnClickedOk()
{
	wchar_t buf[128];
	m_edScreenX.GetWindowTextW(buf, 128);
	SetConfigInt("screenX", _wtoi(buf));
	m_edScreenY.GetWindowTextW(buf, 128);
	SetConfigInt("screenY", _wtoi(buf));
	SetRenderWindowSize(GetConfigInt("screenX", 800), GetConfigInt("screenY", 600));
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


BOOL CGameScreenSize::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_SHOW);
	//
	char buf[128];
	sprintf(buf, "%d", GetConfigInt("screenX", 800));
	this->m_edScreenX.SetWindowTextW(W(buf));
	sprintf(buf, "%d", GetConfigInt("screenY", 600));
	this->m_edScreenY.SetWindowTextW(W(buf));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
