#pragma once
#include "afxwin.h"
#include "GameDirectorRun.h"
#include "GCViewTreeBase.h"
#include "ListBoxIcon.h"
#include "ImageButton.h"
#include "DialogBase.h"

// CPlotCallViewer �Ի���

struct	PlotCallFrame
{
	enum FrameCall
	{
		FrameCall_None	=	0,		//���ٷ��ʿ���
		FrameCall_Script,			//Lua�ű�����
		FrameCall_VariantDefine,	//������ֵ
		FrameCall_VariantPropCall,	//��������
	};
};

class GCGameProject;

class CPlotCallViewer : public CDialogBase
{
	DECLARE_DYNAMIC(CPlotCallViewer)

public:
	CPlotCallViewer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPlotCallViewer();

	VOID				SetPlotCall(CPlotState* c);
public:
	GCGameProject*		m_gamePtr;
	CPlotState*			m_plotCall;
// �Ի�������
	enum { IDD = IDD_RENDER_PLOTCALL };
	//
	VOID				EnableToolBar();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnInserScript();
	afx_msg void OnInsertVariantSet();
	afx_msg void OnInsertPropCall();
	afx_msg void OnRemove();


	CListBoxIcon m_listCall;
	afx_msg void OnLbnSelchangeIconList();
	CImage			m_imageButton;
	CImageButton	m_btVariantSet;
	CImageButton	m_btPropertyCall;
	CImageButton	m_btLuaScript;
	CImageButton	m_btRemove;
};
