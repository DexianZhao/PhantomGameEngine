/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/

#pragma once

#include "ViewTree.h"
#include "GCViewTreeBase.h"
#include <map>
//#include "PngMakerDlg.h"

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// ����
public:
	CFileView();

	void AdjustLayout();
// ����
protected:
// ʵ��
public:
	virtual ~CFileView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateMenuCommand(CCmdUI *pCmdUI);
	afx_msg void OnMenuCommand();
};

CFileView*		GetFileViewPtr();


class CFileBrowser : public CDockablePane, public IViewBaseCallback
{
// ����
public:
	CFileBrowser();

	void	OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp){}
	void	OnChangeTreeSelect(CMTreeCtrl* treePtr, HTREEITEM hAddItem);	//����ѡ�����οؼ�
	void	OnDoubleClick(CMTreeCtrl* treePtr, HTREEITEM hItem){}	//����ѡ�����οؼ�
	void	OnTreeViewKeyDown(INT nChar){}
	//
	CMFCPropertyGridFloatProperty*	FindFloatPtr(CMFCPropertyGridProperty* g){return 0;}
	CMFCPropertyGridIntProperty*	FindIntPtr(CMFCPropertyGridProperty* g){return 0;}

	void AdjustLayout();
// ����
protected:
// ʵ��
public:
	virtual ~CFileBrowser();
	HTREEITEM		m_hViewItem;
	//CFileFilterDlg	m_filter;
	wchar_t	m_szExt[128];
	VOID	Refresh(BOOL bRebuild);
	VOID	RebuildSubDir(HTREEITEM hItem, const wchar_t* szDir, const wchar_t* szPath);
	GCViewTreeBase		m_treeView;
	std::map<HTREEITEM, std::wstring>	m_files;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateMenuCommand(CCmdUI *pCmdUI);
	afx_msg void OnMenuCommand();
};

CFileBrowser*		GetFileBrowserPtr();
