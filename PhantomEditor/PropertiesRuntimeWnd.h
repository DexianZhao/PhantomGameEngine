
#pragma once
#include "PropertiesWnd.h"

class CPropertiesRuntimeWnd : public CDockablePane
{
// ����
public:
	CPropertiesRuntimeWnd();

	void AdjustLayout();

// ����
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

	VOID		SetCurrentProperties(GCPropertyBase* base, const wchar_t* szPropertyName = 0);
	GCPropertyBase*	GetCurrentProperties(){return m_wndCurrentProp;}
protected:
	CFont m_fntPropList;
	CPropertiesToolBar m_wndToolBar;
	GCPropertyBase*	m_wndCurrentProp;
	//
	GCPropertyBase m_wndPropList;

// ʵ��
public:
	virtual ~CPropertiesRuntimeWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();
};

CPropertiesRuntimeWnd*		GetPropertiesRuntimeWindow();
