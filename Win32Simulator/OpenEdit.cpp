// OpenEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OpenEdit.h"
#include "afxdialogex.h"


// COpenEdit �Ի���

IMPLEMENT_DYNAMIC(COpenEdit, CDialogEx)

COpenEdit::COpenEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpenEdit::IDD, pParent)
{

}

COpenEdit::~COpenEdit()
{
}

void COpenEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ed);
}


BEGIN_MESSAGE_MAP(COpenEdit, CDialogEx)
	ON_BN_CLICKED(IDOK, &COpenEdit::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &COpenEdit::OnBnClickedCancel)
END_MESSAGE_MAP()


// COpenEdit ��Ϣ�������


void COpenEdit::OnBnClickedOk()
{
}


void COpenEdit::OnBnClickedCancel()
{
}
