#pragma once
#include "afxcmn.h"
#include "resource.h"
#include "FloatAnimationCtrl.h"
#include "afxwin.h"
#include "ImageButton.h"
#include "ImageCheck.h"
#include "TrackAnimationCtrl.h"

// CTrackEditorDlg �Ի���

struct	TrackEditor
{
	enum EditorType{
		Editor_None	=	0,
		Editor_Float,
		Editor_Color,
		Editor_Float3,
	};
	wchar_t					szName[128];
	EditorType				type;
	int						id;
	CFloatAnimationCtrl		ctrl;
	int						nTabItem;
};

class GCViewBase;

class CTrackEditorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTrackEditorDlg)

public:
	CTrackEditorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTrackEditorDlg();
	VOID				BeginSet();
	VOID				SetAnimationPtr(int id, CFloatAnimation* ani1, CFloatAnimation* ani2 = 0, CFloatAnimation* ani3 = 0, const char* szName = 0);
	VOID				EndSet();
	//
	VOID				AddEditor(const wchar_t* name, int _id, float fMin, float fMax, bool bIsColor);
	VOID				ClearAnimationPtr();
	VOID				OnFrameMove(float fElapsedTime);
	float				GetValueByPos(INT nPosX);
	INT					GetPosByValue(float f);
	VOID				SetNull();
// �Ի�������
	enum { IDD = IDD_TRACK_EDITORS };
	//
	VOID				SetStatus(TrackStatus s);
	BOOL				SetPlayValue(float f);
	float				GetPlayValue();
	VOID				SetModifyed();
	GCViewBase*			m_baseView;
	VOID				SetPlaySpeed(float f);
	float				GetPlaySpeed(){return m_fPlaySpeed;}
	VOID				SetTrackKeyCount(int nF);
	VOID				OnSelectTab();
	VOID				Refresh();
	//
	BOOL				IsCanEditor(CFloatAnimation* f);
protected:
	VOID				OnResize();
	//
	CRect				m_rectEditor;
	CRect				m_rectTrack;
	CRect				m_rectTab;
	CSize				m_keySize;
	TrackStatus			m_trackStatus;
	int					m_nFrameCount;
	float				m_fPlaySpeed;
	//
	BOOL				m_bDownTrack;
	//
	float				m_fPlayIndex;
	//
	VOID				SetCheck(CImageCheck* current);
	VOID				DrawKeyFrames(CDC& dc, const CRect& drawRect, const CSize& keySize, INT nFrameCount, INT nTrackCount);
protected:
	std::vector<TrackEditor*>	m_editors;
	std::vector<TrackEditor*>	m_saveEditors;
	//
	int				GetTrackBeginX();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabEditor;
	afx_msg void OnTRBNThumbPosChangingPlaySlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabEditor(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	//
	CImage			m_imagePlayTrack;
	//
	int				m_lastTabSelect;
	CButton			m_chkEnable;
	//
	CButton			m_chkX;
	CButton			m_chkY;
	CButton			m_chkZ;
	//
	CImageCheck		m_btPlay;
	CImageCheck		m_btPlayBack;
	CImageCheck		m_btQuickPlay;
	CImageCheck		m_btQPlayBack;
	CImageCheck		m_btStop;
	CImageCheck		m_btPause;
	CImage			m_trackImage;
	afx_msg void OnBnClickedMinMax();
	afx_msg void OnBnClickedNull(){}
	afx_msg void OnBnClickedPlayTrack();
	afx_msg void OnBnClickedPlaybackTrack();
	afx_msg void OnBnClickedQplayTrack();
	afx_msg void OnBnClickedQplaybackTrack();
	afx_msg void OnBnClickedStopTrack();
	afx_msg void OnBnClickedPauseTrack();
	afx_msg void OnBnClickedEnable();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CEdit m_edValue;
	CButton m_btSetValue;
	CEdit m_edMinValue;
	CEdit m_edMaxValue;
	CButton m_btSetMinMaxValue;
	afx_msg void OnBnClickedSetValue();
	afx_msg void OnBnClickedSel();
};
