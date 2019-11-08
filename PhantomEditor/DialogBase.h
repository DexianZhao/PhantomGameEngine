/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include "afxwin.h"
#include "GCLanguage.h"

// CDialogBase �Ի���

class CDialogBase : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogBase)

public:
	CDialogBase(UINT nID, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogBase();

	CToolTipCtrl	m_toolTip;
	virtual BOOL OnInitDialog();
	VOID			AddTool(CWnd& wnd, const wchar_t* szText);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
};
