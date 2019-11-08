#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DialogBase.h"

// CDlgInsertEvent �Ի���

class CDlgInsertEvent : public CDialogBase
{
	DECLARE_DYNAMIC(CDlgInsertEvent)

public:
	CDlgInsertEvent(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInsertEvent();

	VOID		Init(INT nEventID, INT nParam1 = 0, INT nParam2 = 0, INT nParam3 = 0, INT nParam4 = 0, INT nParam5 = 0);
// �Ի�������
	enum { IDD = IDD_INSERT_EVENT };
	INT			m_nEventID;
	INT			m_nParameter[MAX_EVENT_PARAM_COUNT];
	wchar_t		m_name[128];
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CTreeCtrl m_treeCtrl;
	afx_msg void OnTvnSelchangedGameProj(NMHDR *pNMHDR, LRESULT *pResult);
};
