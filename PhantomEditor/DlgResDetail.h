#pragma once
#include "resource.h"

// CDlgResDetail �Ի���

class CDlgResDetail : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgResDetail)

public:
	CDlgResDetail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgResDetail();
	CString	m_strDetail;
	CEdit	m_edDetail;
// �Ի�������
	enum { IDD = IDD_RESOURCE_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
