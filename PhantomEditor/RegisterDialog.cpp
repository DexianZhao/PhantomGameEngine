// RegisterDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RegisterDialog.h"
#include "afxdialogex.h"
#include "GCMFCHelper.h"
#include "IDEHttp.h"
#include "GCLanguage.h"

using namespace PhantomV1;

// CRegisterDialog �Ի���

CRegisterDialog*	g_registerDlg = 0;

IMPLEMENT_DYNAMIC(CRegisterDialog, CDialogBase)

CRegisterDialog::CRegisterDialog(CWnd* pParent /*=NULL*/)
	: CDialogBase(CRegisterDialog::IDD, pParent)
{
	g_registerDlg	=	this;
}

CRegisterDialog::~CRegisterDialog()
{
}

void CRegisterDialog::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_EDIT1, m_edEmail);
	DDX_Control(pDX, IDC_EDIT3, m_edPassword);
	DDX_Control(pDX, IDC_EDIT4, m_edRepassword);
	//m_edEmail,m_edPassword,m_edRepassword,m_edNickname
	CDialogBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRegisterDialog, CDialogBase)
	ON_BN_CLICKED(IDOK, &CRegisterDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRegisterDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CRegisterDialog ��Ϣ�������
extern VOID		ReloadLogin();
void WINAPI OnRegisterCallback(Phantom::Name& file, IDCJsonObject& obj, const char* errorText, void* param)//���غ���
{
	if(errorText){
		g_registerDlg->MessageBox(W(errorText), Language(L"��������"), MB_OK|MB_ICONERROR);
		return;
	}
	int result = obj["result"];
	if(result == 1){
		g_registerDlg->MessageBox(Language(L"���������Ѿ����͵��������\n�ɹ������ʼ�֮�����Ϳ�����ʽ��Ϊ\"��Ӱ������\"�û�\n�����Ϊ\"��Ӱ������\"֮��������ʹ�û�Ӱ������Ϸ�ˣ�"), Language(L"��ϲ��ɹ�ע��"), MB_OK);
		CString strEmail;
		g_registerDlg->m_edEmail.GetWindowText(strEmail);
		WriteRegValue("email", A(g_registerDlg->m_strEmail).buf);
		WriteRegValue("password", A(g_registerDlg->m_strPassword).buf);
		g_registerDlg->OK();
		ReloadLogin();
	}
	else
	{
		MessageResult(g_registerDlg->m_hWnd, result);
	}
}

void CRegisterDialog::OnBnClickedOk()
{
	CString strEmail,strPassword,strRepassword;
	m_edEmail.GetWindowText(strEmail);
	m_edPassword.GetWindowText(strPassword);
	m_edRepassword.GetWindowText(strRepassword);
	BOOL bAscii = 1;
	for(int i=0;i<strEmail.GetLength();i++)
	{
		wchar_t t = strEmail[i];
		if(!((t>='0'&&t<='9')||(t>='a'&&t<='z')||(t>='A'&&t<='Z')||t=='@'||t=='.'))
		{
			MessageBox(Language(L"�����ַ����ֻ��ʹ��Ӣ�ĺ�����"));
			return;
		}
	}
	if(strEmail.GetLength()<5 || wcsstr(strEmail, L"@") == 0 || wcsstr(strEmail, L".") == 0){
		MessageBox(Language(L"�����ַ����"));
		return;
	}
	if(wcsicmp(strPassword,strRepassword) != 0)
	{
		MessageBox(Language(L"���벻һ��"));
		return;
	}
	if(strPassword.GetLength()<6)
	{
		MessageBox(Language(L"��������6����"));
		return;
	}
	IDCJsonObject obj;
	obj["email"] = A(strEmail).buf;
	std::string m5;
	md5(A(strPassword).buf, m5);
	obj["password"] = m5.c_str();
	m_strEmail = strEmail;
	m_strPassword = m5.c_str();
	Request("pvd_register", obj, OnRegisterCallback, false);
	//CDialogBase::OnOK();
}


void CRegisterDialog::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogBase::OnCancel();
}
