#pragma once

#include "resource.h"
#include "afxwin.h"

// COpenEdit �Ի���

class COpenEdit : public CDialogEx
{
	DECLARE_DYNAMIC(COpenEdit)

public:
	COpenEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COpenEdit();

// �Ի�������
	enum { IDD = IDD_OPEN_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_ed;
};
