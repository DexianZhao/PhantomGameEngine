/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
// PropertyDlgWndBase.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "phantom-gc.h"
#include "PropertyDlgWndBase.h"
#include "afxdialogex.h"


// CPropertyDlgWndBase �Ի���

IMPLEMENT_DYNAMIC(CPropertyDlgWndBase, CDialogEx)

CPropertyDlgWndBase::CPropertyDlgWndBase(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPropertyDlgWndBase::IDD, pParent)
{

}

CPropertyDlgWndBase::~CPropertyDlgWndBase()
{
}

void CPropertyDlgWndBase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPropertyDlgWndBase, CDialogEx)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CPropertyDlgWndBase ��Ϣ�������


void CPropertyDlgWndBase::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CPropertyDlgWndBase::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnRButtonUp(nFlags, point);
}
