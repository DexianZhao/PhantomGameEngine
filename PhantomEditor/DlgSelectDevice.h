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

// DlgSelectDevice �Ի���

class DlgSelectDevice : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSelectDevice)

public:
	DlgSelectDevice(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgSelectDevice();

// �Ի�������
	enum { IDD = IDD_SELECT_DEVICE };
	CListBox	m_lbDevices;
	int			m_nLastCount;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRun();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLbnDblclkDeviceList();
};
