/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/

#pragma once

#include "ListBoxIcon.h"

/////////////////////////////////////////////////////////////////////////////
// COutputList ����

#define	OUTPUT_ERROR_ICON	33
class COutputWnd;
class COutputList : public CListBoxIcon
{
// ����
public:
	COutputList();

// ʵ��
public:
	virtual ~COutputList();

	COutputWnd*		m_wndOutput;
protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();
	//afx_msg void OnLbnSelchange();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchange();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

class COutputWnd : public CDockablePane
{
// ����
public:
	COutputWnd();
// ����
	VOID			AddMessage(INT nIcon, const wchar_t* szText, INT id = 0, COLORREF textColor = 0);
	VOID			ClearMessage();
	//
	CEdit			m_wndErrorText;
protected:
	//CMFCTabCtrl	m_wndTabs;

	//COutputList m_wndErrorOutput;
	COutputList m_wndOpOutput;

protected:

	void AdjustHorzScroll(CListBox& wndListBox);

// ʵ��
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

