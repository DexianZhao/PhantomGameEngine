#pragma once
#include "resource.h"
#include "DialogBase.h"

// CDlgUserInfo �Ի���

class CDlgUserInfo : public CDialogBase
{
	DECLARE_DYNAMIC(CDlgUserInfo)

public:
	CDlgUserInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUserInfo();

// �Ի�������
	enum { IDD = IDC_USER_INFO };
	CEdit	m_edPPoint,m_edLevel,m_edVipEnd;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedChangeaccount();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBuyToUrl();
	afx_msg void OnBnClickedBuyToUrl2();
	afx_msg void OnBnClickedCancel();
};
