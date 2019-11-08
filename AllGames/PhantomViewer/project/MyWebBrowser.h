#pragma once
#include "resource.h"
#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CDHtmlDialog��"
#endif 

// CMyWebBrowser �Ի���

class CMyWebBrowser : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CMyWebBrowser)

public:
	CMyWebBrowser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyWebBrowser();
// ��д
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	virtual void OnNavigateComplete(LPDISPATCH pDisp, LPCTSTR szUrl);
	virtual void OnBeforeNavigate(LPDISPATCH pDisp, LPCTSTR szUrl);
// �Ի�������
	enum { IDD = IDD_MYWEBBROWSER, IDH = IDR_HTML_MYWEBBROWSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
