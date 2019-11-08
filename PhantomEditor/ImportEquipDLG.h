/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include <vector>
#include "afxwin.h"

// CImportEquipDLG �Ի���

struct ImportPartEquipObject
{
	int									objectIndex;
	int									partIndex;
	std::string							name;
};

class CImportEquipDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CImportEquipDLG)

public:
	CImportEquipDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CImportEquipDLG();

	//VOID								SetInitialize(IGeometryGroupData* groupPtr, CDynamicArray<const char*>& objects);
	//
	std::vector<ImportPartEquipObject>	m_objects;
	//
	//CDynamicArray<ImportEquip>			m_returns;
	//
// �Ի�������
	enum { IDD = IDD_SELECT_EQUIPS };

	VOID								RebuildObjectList();
	VOID								RebuildPartObjects();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_lbObjects;
	CListBox m_lbParts;
	CListBox m_lbPartObjects;
	afx_msg void OnBnClickedAddImport();
	afx_msg void OnBnClickedRemoveImport();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangePartList();
};
