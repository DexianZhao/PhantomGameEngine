/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once

#include "CodeEditor.h"
#include "CodeComboBox.h"
#include "afxcmn.h"

// CMyLuaEditor �Ի���

class CMyLuaEditor : public CDialogEx, public LuaEditorWindow
{
	DECLARE_DYNAMIC(CMyLuaEditor)

public:
	CMyLuaEditor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyLuaEditor();
	CodeEditor*						m_current;
	CodeEditor*						Open(const char* szFile);
	VOID							SetModifyed(CodeEditor* e, BOOL b);
	VOID							InvalidateDlg();
	VOID							UpdateTipText(const wchar_t* str, CWnd* wnd);
	VOID							OffsetToolRect(int x, int y);

	CWnd*			GetWindowPtr(){return this;}
	VOID			OnMouseWheel(int delta){}
	VOID			OnKeyDown(int key){}
	VOID			OnKeyUp(int key){}
	VOID			OnViewSize(CRect* rc);
	enum { IDD = IDD_MY_EDITOR };
	CImage							m_image;
	VOID							RedrawLines();
	CToolTipCtrl					m_tooltip;
	VOID							RecalcRects();
	BOOL			m_bIsFirst;
	//
	BOOL			InitEvent(char* retAIName, const char* tableName, FileName& f);//�Ƿ��������ű�
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};

