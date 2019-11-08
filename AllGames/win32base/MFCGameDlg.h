
// BaiWanGameDlg.h : ͷ�ļ�
//

#pragma once

#include "OpenEdit.h"
#include "DlgLog.h"
#include "DlgBindBar.h"


// CBaiWanGameDlg �Ի���
class CBaiWanGameDlg : public CDialogEx
{
// ����
public:
	CBaiWanGameDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BAIWANGAME_DIALOG };

	COpenEdit	m_edit;
	CDlgBindBar	m_bind;
	CDlgLog		m_log;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��



// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnMove(int x, int y);
};
