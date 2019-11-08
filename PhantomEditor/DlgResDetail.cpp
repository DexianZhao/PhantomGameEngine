// DlgResDetail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgResDetail.h"
#include "afxdialogex.h"


// CDlgResDetail �Ի���

IMPLEMENT_DYNAMIC(CDlgResDetail, CDialogEx)

CDlgResDetail::CDlgResDetail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgResDetail::IDD, pParent)
{

}

CDlgResDetail::~CDlgResDetail()
{
}

void CDlgResDetail::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_DESC, m_edDetail);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgResDetail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgResDetail::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgResDetail ��Ϣ�������


BOOL CDlgResDetail::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_edDetail.SetWindowTextW(m_strDetail);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgResDetail::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
