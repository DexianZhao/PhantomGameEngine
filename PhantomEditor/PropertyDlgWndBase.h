/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include "resource.h"

// CPropertyDlgWndBase �Ի���

class CPropertyDlgWndBase : public CDialogEx
{
	DECLARE_DYNAMIC(CPropertyDlgWndBase)

public:
	CPropertyDlgWndBase(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPropertyDlgWndBase();

// �Ի�������
	enum { IDD = IDD_PROPERTY_DLG_WND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};
