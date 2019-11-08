#pragma once
#include "DialogBase.h"
#include "afxwin.h"

// CSceneCreateDlg �Ի���

class CSceneCreateDlg : public CDialogBase
{
	DECLARE_DYNAMIC(CSceneCreateDlg)

public:
	CSceneCreateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSceneCreateDlg();
	float			m_fGridSize;
	INT				m_nMapSizeLevel;
	VOID			RebuildInfoView();
// �Ի�������
	enum { IDD = IDD_SCENE_CreateScene };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CEdit m_edGridSize;
	CComboBox m_cbMapSizeLevel;
	afx_msg void OnCbnSelchangeMapSizeLevel();
	afx_msg void OnEnChangeGridSize();
};
