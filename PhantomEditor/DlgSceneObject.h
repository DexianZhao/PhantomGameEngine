/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include "resource.h"

// DlgSceneObject �Ի���
class GCSceneEditor3D;
class DlgSceneObject : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSceneObject)

public:
	DlgSceneObject(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgSceneObject();

// �Ի�������
	enum { IDD = IDD_SCENE_OBJECTS };
	//
	GCSceneEditor3D*	m_editors;
	VOID		RefreshSceneUnits();
	VOID		RefershRoles();
	VOID		RefreshEvents();
	//
	VOID		Active(CButton* b);
	//
	CListBox	m_lbSceneUnits;
	CListBox	m_lbRoles;
	CListBox	m_lbEvents;
	CButton		m_chkSceneUnits,m_chkRoles,m_chkEvents;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkSceneunits();
	afx_msg void OnBnClickedChkRoles();
	afx_msg void OnBnClickedChkEvents();
	afx_msg void OnLbnSelchangeSceneUnits();
	afx_msg void OnLbnSelchangeRoles();
	afx_msg void OnLbnSelchangeEvents();
};
