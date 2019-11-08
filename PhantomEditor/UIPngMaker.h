/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include "DialogBase.h"
#include <vector>
#include <string>
#include <atlimage.h>
#include "afxwin.h"
#include "resource.h"

// CUIPngMaker �Ի���

class CUIPngMaker : public CDialogBase
{
	DECLARE_DYNAMIC(CUIPngMaker)

public:
	CUIPngMaker(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUIPngMaker();

// �Ի�������
	enum { IDD = IDD_UIPNGMAKE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	//
	afx_msg void OnBnClickedBrowser();
	std::vector<std::wstring> m_files;
	CListBox m_lbAddFile;
	afx_msg void OnBnClickedRemove();
	afx_msg void OnBnClickedClear2();
	afx_msg void OnBnClickedButton1();
	CEdit m_edOutputName;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedBuildAll();
	afx_msg void OnBnClickedOk();
	CComboBox m_cbSize;
	CEdit		m_edScale;
	CEdit		m_edReserved;
	CComboBox	m_cbDirectory;
	CComboBox	m_cbAlign;
	CButton		m_chkAlpha;
	CString		m_loadFile;
public:
	afx_msg void OnBnClicked1005();
	afx_msg void OnBnClicked1004();
	afx_msg void OnBnClicked1008();
	afx_msg void OnBnClickedBuildAll2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedBrowser2();
	afx_msg void OnBnClickedButton100();
};
