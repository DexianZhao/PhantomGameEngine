/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once

#include "DialogBase.h"
#include "afxwin.h"

// CDlgMixFPS �Ի���

class CDlgMixFPS : public CDialogBase
{
	DECLARE_DYNAMIC(CDlgMixFPS)

public:
	CDlgMixFPS(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMixFPS();

// �Ի�������
	enum { IDD = IDD_MIX_FPS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edFPS;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
