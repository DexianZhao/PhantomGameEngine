/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/

// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "phantom-gc.h"
#include "GCViewManager.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_MDIACTIVATE()
	ON_WM_DROPFILES()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CChildFrame ����/����

std::vector<CChildFrame*>	g_childFrames;
CChildFrame*		GetChildFrame(HWND hWnd)
{
	for(int i=0;i<g_childFrames.size();i++)
	{
		if(g_childFrames[i]->m_hWnd == hWnd)
			return g_childFrames[i];
		if(g_childFrames[i]->GetActiveFrame())
			if(g_childFrames[i]->GetActiveFrame()->m_hWnd == hWnd)
				return g_childFrames[i];
	}
	return 0;
}

CChildFrame::CChildFrame()
{
	m_hIcon	=	0;
	g_childFrames.push_back(this);
}

CChildFrame::~CChildFrame()
{
	for(int i=0;i<g_childFrames.size();i++)
	{
		if(g_childFrames[i] == this)
		{
			g_childFrames.erase(g_childFrames.begin() + i);
			break;
		}
	}
}

HICON CChildFrame::GetFrameIcon() const
{
	if(m_hIcon)
		return m_hIcon;
	return __super::GetFrameIcon();
}

HBITMAP CChildFrame::OnGetIconicThumbnail(int nWidth, int nHeight)
{
	if(m_pViewActive)
	{
		//GCViewBase* view	=	GetViewManager()->FindDocument(m_pViewActive->m_hWnd);
		//view->m_iconImage.
	}
	return NULL;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������


void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(GetActiveView())
	{
		GCViewBase* pView	=	GetViewManager()->FindDocument(GetActiveView()->m_hWnd);
		if(pView)
			pView->SetActiveFrame(this);
	}

	CMDIChildWndEx::ActivateFrame(nCmdShow);
}


void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CMDIChildWndEx::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	if(bActivate && pActivateWnd == this)
	{
		GetViewManager()->OnActiveDocument(this->m_pViewActive->m_hWnd);//pActivateWnd->m_hWnd);
	}

	// TODO: �ڴ˴������Ϣ����������
}


void CChildFrame::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CMDIChildWndEx::OnDropFiles(hDropInfo);
}


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	this->DragAcceptFiles(TRUE);
	return 0;
}

VOID CChildFrame::SetToolTip(const wchar_t* szText)
{
	if(!this->m_pRelatedTabGroup)
		return;
	m_pRelatedTabGroup->EnableCustomToolTips(FALSE);
}

void CChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CMDIChildWndEx::OnUpdateFrameTitle(bAddToTitle);
}

extern	void AFXAPI AfxCancelModes(HWND hWndRcvr);
BOOL CChildFrame::PreTranslateMessage(MSG* pMsg)
{
	return CMDIChildWndEx::PreTranslateMessage(pMsg);
}
