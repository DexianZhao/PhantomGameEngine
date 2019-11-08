#pragma once
#include "resource.h"

// CDlgBindBar �Ի���

class CDlgBindBar : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBindBar)

public:
	CDlgBindBar(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBindBar();

// �Ի�������
	enum { IDD = IDD_BIND_BAR };
	HWND		m_hWndBind;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
