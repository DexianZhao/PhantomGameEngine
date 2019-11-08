// BigTextEditor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "BigTextEditor.h"
#include "afxdialogex.h"


// CBigTextEditor �Ի���

IMPLEMENT_DYNAMIC(CBigTextEditor, CDialogEx)

CBigTextEditor::CBigTextEditor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBigTextEditor::IDD, pParent)
{

}

CBigTextEditor::~CBigTextEditor()
{
}

void CBigTextEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBigTextEditor, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBigTextEditor::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBigTextEditor::OnBnClickedCancel)
END_MESSAGE_MAP()


// CBigTextEditor ��Ϣ�������


void CBigTextEditor::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_richEdit.GetWindowText(m_editText);
	CDialogEx::OnOK();
}


void CBigTextEditor::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


BOOL CBigTextEditor::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ShowWindow(SW_SHOW);
	CRect	rc;
	GetClientRect(&rc);
	rc.bottom	-=	30;
	m_richEdit.Create(ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_WANTRETURN | WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_HSCROLL, rc, this, 0);
	m_richEdit.SetFont(this->GetFont());
	m_richEdit.SetWindowText(m_editText);
	return TRUE;
}
