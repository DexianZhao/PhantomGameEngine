/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include "afxwin.h"
#include "ImageCheck.h"
#include "DialogBase.h"

// CCreateFileDlg �Ի���

class CCreateFileDlg : public CDialogBase
{
	DECLARE_DYNAMIC(CCreateFileDlg)

public:
	CCreateFileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreateFileDlg();

// �Ի�������
	enum { IDD = IDD_CREATE_FILES };

	CString		m_strGameProj;
	INT			m_createType;
	CString		m_strScene3D;

	VOID		SetCheck(CImageCheck* c);
	CImage		m_createImage;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CImageCheck m_chkUIFile;
	CImageCheck m_chkUnit2D;
	CImageCheck m_chkCursors;
	CImageCheck m_chkScene2D;
	CImageCheck m_chkGameProject;
	CImageCheck m_chkScene3D;
	CImageCheck m_chkUnit3D;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCreateUi();
	afx_msg void OnBnDoubleclickedCreateUi();
	afx_msg void OnBnClickedCreateUnit2d();
	afx_msg void OnBnClickedCreateCursors();
	afx_msg void OnBnClickedCreateScene2d();
	afx_msg void OnBnClickedCreateGameProject();
	afx_msg void OnBnClickedCreateScene3d();
	afx_msg void OnBnClickedCreateUnit3d();
	afx_msg void OnBnDoubleclickedCreateUnit3d();
	afx_msg void OnBnDoubleclickedCreateScene3d();
};
