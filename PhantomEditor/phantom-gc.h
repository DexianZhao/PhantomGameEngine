
// phantom-gc.h : phantom-gc Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


#define	AUTH_MODE	1	//���������û�֧��

// CPhantomGCApp:
// �йش����ʵ�֣������ phantom-gc.cpp
//

class CPhantomGCApp : public CWinAppEx
{
public:
	CPhantomGCApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual CDataRecoveryHandler *GetDataRecoveryHandler(){return NULL;}
// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual BOOL OnIdle(LONG lCount); // return TRUE if more idle processing

	BOOL			IsUpdateCmdUI();
	unsigned int	m_nLastTickTime;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void OnGotoForum();
	afx_msg void OnBuyProfessional();
	afx_msg void OnShowHelp();
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
};

extern CPhantomGCApp theApp;

extern	VOID		UpdateMainTitle();
