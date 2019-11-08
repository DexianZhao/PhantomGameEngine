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
#include "resource.h"

// CGameScreenSize �Ի���

class CGameScreenSize : public CDialogEx
{
	DECLARE_DYNAMIC(CGameScreenSize)

public:
	CGameScreenSize(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameScreenSize();

// �Ի�������
	enum { IDD = IDD_GAME_SCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edScreenX;
	CEdit m_edScreenY;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
