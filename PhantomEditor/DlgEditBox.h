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
#include "DlgGameEditBox.h"
// CDlgEditBox �Ի���

class CDlgEditBox : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgEditBox)

public:
	CDlgEditBox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgEditBox();

// �Ի�������
	enum { IDD = IDD_EDIT_TEXT };
	DlgGameEditBox		m_edit;
	int			m_id;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
