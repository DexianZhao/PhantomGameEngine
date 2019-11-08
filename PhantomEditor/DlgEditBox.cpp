/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
// DlgEditBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgEditBox.h"
#include "afxdialogex.h"


// CDlgEditBox �Ի���

IMPLEMENT_DYNAMIC(CDlgEditBox, CDialogEx)

CDlgEditBox::CDlgEditBox(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgEditBox::IDD, pParent)
{
	m_id	=	0;
	m_edit.m_dlgEdit = this;
}

CDlgEditBox::~CDlgEditBox()
{
}

void CDlgEditBox::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_EDITBOX, m_edit);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgEditBox, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgEditBox::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgEditBox::OnBnClickedCancel)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgEditBox ��Ϣ�������

extern "C"{
	void	closeEdit(int bIsClose);
};

void CDlgEditBox::OnBnClickedOk()
{
	closeEdit(false);
	CDialogEx::OnOK();
}


void CDlgEditBox::OnBnClickedCancel()
{
	closeEdit(true);
	CDialogEx::OnCancel();
}


void CDlgEditBox::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CWnd* wnd = GetDlgItem(IDC_EDITBOX);
	if(wnd&&wnd->m_hWnd){
		wnd->MoveWindow(0, 0, cx, cy);
	}
	// TODO: �ڴ˴������Ϣ����������
}
