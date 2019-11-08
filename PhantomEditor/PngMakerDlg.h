#pragma once

#include "resource.h"
#include <map>
// CFileFilterDlg �Ի���

class CFileFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileFilterDlg)

public:
	CFileFilterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFileFilterDlg();

// �Ի�������
	enum { IDD = IDD_FILE_SHAIXUAN };
	CButton		m_chkDir;
	CListBox	m_lbFilePath;
	CComboBox	m_edFilePath;
	std::map<std::string, std::string> m_extFiles;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeExportPaths();
	afx_msg void OnBnClickedCreateDir();
};
