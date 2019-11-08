/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
// DialogBase.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogBase.h"
#include "afxdialogex.h"
#include "GCViewManager.h"


// CDialogBase �Ի���

IMPLEMENT_DYNAMIC(CDialogBase, CDialogEx)

CDialogBase::CDialogBase(UINT nID, CWnd* pParent /*=NULL*/)
	: CDialogEx(nID, pParent)
{

}

CDialogBase::~CDialogBase()
{
}

void CDialogBase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogBase, CDialogEx)
END_MESSAGE_MAP()


// CDialogBase ��Ϣ�������

BOOL	CDialogBase::OnInitDialog()
{
	if(!__super::OnInitDialog())
		return false;
	if(GetLanguagesPtr())
		GetLanguagesPtr()->SetChildsText(m_hWnd);
	InitTool(m_toolTip, this);
	ShowWindow(SW_SHOW);
	return true;
}

VOID	CDialogBase::AddTool(CWnd& wnd, const wchar_t* szText)
{
	::AddTool(m_toolTip, wnd, szText);
}

BOOL	CDialogBase::PreTranslateMessage(MSG* pMsg)
{
	m_toolTip.RelayEvent( pMsg );
	return __super::PreTranslateMessage(pMsg);
}
