/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#include "StdAfx.h"
#include "GCCodeEditor.h"
#include "MainFrm.h"
#include "PropertiesDialogWnd.h"
#include "phantom-gcView.h"

GCCodeEditor::GCCodeEditor(CPhantomGCDoc* docPtr)
	:GCViewBase(docPtr, Language(L"�ű��༭"), IDB_UI_VIEW_BMP)
{
}

GCCodeEditor::~GCCodeEditor(void)
{
	CloseFile();
}

HICON		GCCodeEditor::GetViewerIcon()
{
	static HICON	hIcon	=	AfxGetApp()->LoadIcon(IDI_LUA_FILE_ICON);
	return hIcon;
}

void		GCCodeEditor::OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp)
{
	__super::OnPropertyChanged(wnd, pProp);
}

VOID		GCCodeEditor::OnChangeTreeSelect(CMTreeCtrl* treePtr, HTREEITEM hAddItem)	//����ѡ�����οؼ�
{
	if(treePtr == &m_treeView)
	{
		TreeItemType* type	=	this->GetSelectedItem();
		if(!type)
		{
			SetCurrentProperties(&m_viewerProps, L"�ļ�����", NULL);
			return;
		}
		switch(type->type)
		{
		case FUNCTION_MAIN:
			{
				SetCurrentProperties(NULL, NULL, NULL);
			}
			break;
		default:
			SetCurrentProperties(NULL, NULL, NULL);
			break;
		}
		return;
	}
	SetCurrentProperties(NULL, NULL, NULL);
}
VOID		GCCodeEditor::CloseFile(){
	if(m_luaEditor.m_current)
		delete m_luaEditor.m_current;
	m_luaEditor.m_current = 0;
}
BOOL		GCCodeEditor::OpenFile(const wchar_t* szFile)	//���ļ�,���ʧ������Զ�ɾ��
{
	this->m_strFile	=	szFile;
	if(!__super::OpenFile(szFile))
		return false;
	wchar_t dir[512];
	GetCurrentDirectory(512, dir);
	m_luaEditor.Create(m_luaEditor.IDD, GetMainFrame());
	m_luaEditor.ShowWindow(SW_SHOW);
	if(!m_luaEditor.Open(A(szFile)))
		return false;
	m_cb.m_t = this;
	m_luaEditor.m_current->m_callback = &m_cb;
	GetActiveView()->m_wndViewer	=	&m_luaEditor;
	GetActiveView()->m_bIsPopup		=	true;
	CRect rc;
	GetActiveView()->GetWindowRect(&rc);
	GetMainFrame()->ScreenToClient(&rc);
	m_luaEditor.MoveWindow(&rc);//0, 0, rc.Width(), rc.Height());
	ShowWindow(GetDeviceWindow(), SW_HIDE);
	//
	RebuildTrees();
	if(m_viewerProps.m_hWnd == 0)
		InitViewerProps();
	::SetWindowPos(m_luaEditor.m_hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
	return true;
}

VOID		GCCodeEditor::RebuildTrees()
{
	if(m_hViewItem)
		m_treeView.DeleteItem(m_hViewItem);
	wchar_t wFileName[256], wExt[256];
	_wsplitpath(m_strFile.c_str(), 0, 0, wFileName, wExt);
	wcscat(wFileName, wExt);
	m_hViewItem = m_treeView.InsertItem(wFileName, 33, 33);
	m_treeView.SetItemState(m_hViewItem, TVIS_BOLD, TVIS_BOLD);
	m_treeView.Expand(m_hViewItem, TVE_EXPAND);
	//
	this->ClearTreeItem();
	BuildAll();
	//
	m_treeView.m_callback	=	this;
}

VOID		GCCodeEditor::BuildAll()
{
	m_treeView.SelectItem(m_hViewItem);
	DeleteChildItems(m_hViewItem);
	//m_treeView.SetItemData(m_hViewItem, AddTreeItem(FUNCTION_MAIN));
}

VOID		GCCodeEditor::OnActive()		//������
{
	ShowWindow(GetDeviceWindow(), SW_HIDE);
	__super::OnActive();
	ShowWindow(GetDeviceWindow(), SW_HIDE);
	if(m_luaEditor.m_hWnd)
	{
		m_luaEditor.ShowWindow(SW_SHOW);
		m_luaEditor.RecalcRects();
		::SetWindowPos(m_luaEditor.m_hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
		if(m_luaEditor.m_current){
			m_luaEditor.m_current->SetFocus();
			GetMainFrame()->m_dlgFind.m_editor = m_luaEditor.m_current;
		}
	}
}

VOID		GCCodeEditor::OnDeActive()		//ʧȥ����
{
	if(m_luaEditor.m_hWnd)
		m_luaEditor.ShowWindow(SW_HIDE);
	ShowWindow(GetDeviceWindow(), SW_SHOW);
	__super::OnDeActive();
}
VOID		GCCodeEditor::OnSetFocus()
{
	if(m_luaEditor&&m_luaEditor.m_current)
		m_luaEditor.m_current->SetFocus();
}
void		GCCodeEditor::OnFrameMove()	//ÿ�θ���
{
}

void		GCCodeEditor::OnPushRenderObjects()	//��Ⱦ
{
}

BOOL		GCCodeEditor::SaveFile(BOOL bSaveAs)	//�����ļ�
{
	bool bNew	=	false;
	if(bSaveAs || m_strFile.size() == 0)
	{
		wchar_t wExt[125];
		_wsplitpath(m_strFile.c_str(), 0, 0, 0, wExt);
		bNew	=	true;
		CFileDialog dlg(FALSE, 0, 0, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, formatw(L"%s|*%s||", Language(L"LuaFileType", L"�ű��ļ�"), wExt ), GetMainFrame());
		wchar_t buffer[1024];
		dlg.m_pOFN->lpstrInitialDir	=	AToW(GetProjectPath(), buffer, 1024);
		if(dlg.DoModal() != IDOK)
			return false;
		SetProjectPath();
		wchar_t szPath[256], szFile[256], szDir[256];
		_wsplitpath(dlg.GetPathName(), szPath, szDir, szFile, 0);
		wcscat(szPath, szDir);
		wcscat(szPath, szFile);
		wcscat(szPath, wExt);
		m_strFile	=	szPath;
	}
	CString str;
	m_luaEditor.m_current->GetWindowTextW(str);
	Phantom::SaveUtf8(A(m_strFile.c_str()), Autf8(str));
	return __super::SaveFile(bSaveAs);
}

void		GCCodeEditor::OnRenderingEnd()
{
}
//��Ⱦ
void		GCCodeEditor::OnUpdateUI(INT nMenuID, CCmdUI* pCmdUI)
{
	switch(nMenuID)
	{
	default:
		pCmdUI->Enable(false);
		break;
	}
}


void		GCCodeEditor::OnCommandUI(INT nMenuID)
{
}
