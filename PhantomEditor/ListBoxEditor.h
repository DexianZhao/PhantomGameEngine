/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include "afxvslistbox.h"
#include <vector>
#include <string>
#include <map>
// CListBoxEditor �Ի���

class CListBoxEditor : public CDialogEx
{
	DECLARE_DYNAMIC(CListBoxEditor)

public:
	CListBoxEditor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CListBoxEditor();

// �Ի�������
	enum { IDD = IDD_EDIT_LISTBOX };
	std::vector<std::wstring>	m_lists;
	std::map<int,std::wstring>	m_maps;
	std::vector<int>			m_mapsel;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox	m_mapBox;
	CVSListBox	m_listBox;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
