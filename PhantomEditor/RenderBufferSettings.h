//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	�ļ�       :   RenderBufferSettings.h
	�������   :   ��Ӱ��Ϸ����

	��Ʊ�д�� :   �Ե���(Ӣ��:ZhaoDexian)
	Email: yuzhou_995@hotmail.com
	
	Copyright 2009-2016 Zhao Dexian
	
	-------------------------------------------------------------------------------------------------


	-------------------------------------------------------------------------------------------------
	*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___RENDERBUFFERSETTINGS__H___
#define ___RENDERBUFFERSETTINGS__H___


#pragma once
#include "afxwin.h"
#include "DialogBase.h"
#include "PhantomProject.h"

// CRenderBufferSettings �Ի���

class CRenderBufferSettings : public CDialogBase
{
	DECLARE_DYNAMIC(CRenderBufferSettings)

public:
	CRenderBufferSettings(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRenderBufferSettings();

// �Ի�������
	enum { IDD = IDD_RENDER_SETTINGS };

	VOID		OnChangeScene();
	Phantom::Scene3D		*	m_scene3D;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_chkEnableMultiBuffer;
	CComboBox m_cbBufferSize;
	CButton m_chkBlurMode;
	CEdit m_edBlurSize;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedUseTargetBuffer();
	afx_msg void OnCbnSelchangeBufferSize();
	afx_msg void OnBnClickedUseBlur();
	afx_msg void OnBnClickedSetBlur();
};

CRenderBufferSettings*	GetRenderBufferSettings();


#endif
