// DlgViewerHttp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgViewerHttp.h"


// CDlgViewerHttp �Ի���

IMPLEMENT_DYNCREATE(CDlgViewerHttp, CDHtmlDialog)

CDlgViewerHttp::CDlgViewerHttp(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CDlgViewerHttp::IDD, CDlgViewerHttp::IDH, pParent)
{

}

CDlgViewerHttp::~CDlgViewerHttp()
{
}

void CDlgViewerHttp::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CDlgViewerHttp::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	SetHostFlags(DOCHOSTUIFLAG_FLAT_SCROLLBAR);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CDlgViewerHttp, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CDlgViewerHttp)
END_DHTML_EVENT_MAP()



// CDlgViewerHttp ��Ϣ�������

HRESULT CDlgViewerHttp::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CDlgViewerHttp::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}


BOOL CDlgViewerHttp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch(pMsg->message)
	{
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
		return true;
	case WM_KEYDOWN:
	case WM_KEYUP:
		{
			char buf[512];
			::GetClassNameA(pMsg->hwnd, buf, 512);
			if(GetSelectKeyboard() && (pMsg->wParam == 'C' || pMsg->wParam == 'A'))
				return true;
		}
		break;
	}
	return __super::PreTranslateMessage(pMsg);
}
