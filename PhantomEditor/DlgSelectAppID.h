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

// CDlgSelectAppID �Ի���

class CDlgSelectAppID : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSelectAppID)

public:
	CDlgSelectAppID(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSelectAppID();

// �Ի�������
	enum { IDD = IDD_SELECT_APPID };
	CComboBox		m_cbAppIDs;
	CButton			m_btOK;
	CString			m_strAppID;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
