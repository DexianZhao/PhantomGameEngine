#pragma once
#include "resource.h"
#include "DialogBase.h"
// CRegisterDialog �Ի���

class CRegisterDialog : public CDialogBase
{
	DECLARE_DYNAMIC(CRegisterDialog)

public:
	CRegisterDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegisterDialog();

	VOID	OK(){CDialogEx::OnOK();}
// �Ի�������
	enum { IDD = IDD_REGISTER_USER };

	CEdit	m_edEmail,m_edPassword,m_edRepassword;
	CString	m_strEmail,m_strPassword;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
