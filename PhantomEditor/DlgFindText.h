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

// DlgFindText �Ի���

class DlgFindText : public CDialogEx
{
	DECLARE_DYNAMIC(DlgFindText)

public:
	DlgFindText(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgFindText();

// �Ի�������
	enum { IDD = IDD_FIND_TEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
