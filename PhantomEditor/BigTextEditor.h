#pragma once


// CBigTextEditor �Ի���

class CBigTextEditor : public CDialogEx
{
	DECLARE_DYNAMIC(CBigTextEditor)

public:
	CBigTextEditor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBigTextEditor();

// �Ի�������
	enum { IDD = IDD_EDIT_BIG_TEXT };

	CString					m_editText;
	CEdit					m_richEdit;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
