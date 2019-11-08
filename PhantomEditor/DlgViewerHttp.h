#pragma once
#include "resource.h"
#include "GCMFCHelper.h"

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CDHtmlDialog��"
#endif 

// CDlgViewerHttp �Ի���

class CDlgViewerHttp : public CDHtmlDialog, public ViewerWindow
{
	DECLARE_DYNCREATE(CDlgViewerHttp)

public:
	CDlgViewerHttp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgViewerHttp();
// ��д
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	CWnd*			GetWindowPtr(){return this;}
	VOID			OnMouseWheel(int delta){}
	VOID			OnKeyDown(int key){}
	VOID			OnKeyUp(int key){}
	VOID			OnViewSize(CRect* rc){}

// �Ի�������
	enum { IDD = IDD_VIEWER_HTTP, IDH = IDR_HTML_DLGVIEWERHTTP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
