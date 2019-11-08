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

// CMultiExportDlg �Ի���

class CMultiExportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMultiExportDlg)

public:
	CMultiExportDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMultiExportDlg();

// �Ի�������
	enum { IDD = IDD_MULTIEXPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_edSrcPath;
	CEdit m_edExportPath;
	CButton m_chkTextureRename;
	CButton m_chkMeshRename;
};
