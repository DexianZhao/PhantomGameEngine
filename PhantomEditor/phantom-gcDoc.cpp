
// phantom-gcDoc.cpp : CPhantomGCDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "phantom-gc.h"
#endif

#include "GCViewManager.h"

#include "phantom-gcDoc.h"

#include <propkey.h>
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPhantomGCDoc

IMPLEMENT_DYNCREATE(CPhantomGCDoc, CDocument)

BEGIN_MESSAGE_MAP(CPhantomGCDoc, CDocument)
END_MESSAGE_MAP()


// CPhantomGCDoc ����/����

CPhantomGCDoc::CPhantomGCDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CPhantomGCDoc::~CPhantomGCDoc()
{
}

int		g_createFileType	=	0;
VOID	CreateNewFile(int nType)
{
	g_createFileType	=	nType;
	AfxGetApp()->m_pDocManager->OnFileNew();
}

BOOL CPhantomGCDoc::OnNewDocument()
{
	if(g_createFileType == 0)
		return false;///
	int ct	=	g_createFileType;
	g_createFileType	=	0;
	if (!CDocument::OnNewDocument())
		return FALSE;
	if(!GetViewManager()->InsertDocument(this, (FileViewerType)ct, L""))
		return false;
	return TRUE;
}




// CPhantomGCDoc ���л�

void CPhantomGCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

// CPhantomGCDoc ���

#ifdef _DEBUG
void CPhantomGCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPhantomGCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPhantomGCDoc ����


void CPhantomGCDoc::OnChangedViewList()
{
	CDocument::OnChangedViewList();
}

BOOL CPhantomGCDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	if(!GetViewManager()->InsertDocument(this, lpszPathName))
		return false;
	return true;
}


BOOL CPhantomGCDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	GCViewBase* base	=	GetViewManager()->FindDocument(this);
	if(base)
		return base->SaveFile();
	return false;
}


void CPhantomGCDoc::OnCloseDocument()
{
	CDocument::OnCloseDocument();
	GetViewManager()->RemoveDocument(this);
	UpdateMainTitle();
}
