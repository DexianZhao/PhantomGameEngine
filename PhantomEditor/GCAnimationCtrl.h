/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include <vector>
#include "resource.h"
#include "afxwin.h"

#define	TRACK_BEGIN_X	5
#define	TRACK_BEGIN_Y	5

// GCAnimationCtrl �Ի���

struct	GCAnimationKey
{
	INT			beginFrame;
	INT			endFrame;
	INT			id;
	INT			index;
	COLORREF	c;
	Phantom::NameW		name;
	//
	CRect		beginRc, endRc, bodyRc;
};

__interface	GCAnimationCallback
{
	INT				GetKeyFrameCount();
	BOOL			OnTrackChange(INT id, INT nBeginFrame, INT nEndFrame);	//�������TRUE��ʾ���Ա��ı�
	VOID			EnumTracks(std::vector<GCAnimationKey>& rets);
};

class GCAnimationCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(GCAnimationCtrl)

public:
	GCAnimationCtrl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~GCAnimationCtrl();
	enum TrackPosition
	{
		TrackPosition_None	=	0,
		TrackPosition_Left,
		TrackPosition_Center,
		TrackPosition_Right,
	};

// �Ի�������
	enum { IDD = IDD_CONTROL_DLG };
	//
	VOID						SetCallback(GCAnimationCallback* cb);//
	GCAnimationKey*					GetTrackItem(INT id);
	INT							SetMoveCursor(TrackPosition* ret);
	INT							GetKeyFrameByPos(INT x);
	INT							GetPosByFrame(INT nFrame);
	//
	INT							GetTrackBeginX();
	INT							GetTrackBeginY();
	VOID						ResizeScroll();
	VOID						DrawTrack(CDC& dc, const CRect& drawRect, const CSize& keySize, GCAnimationKey& track);
	VOID						DrawKeyFrames(CDC& dc, const CRect& drawRect, const CSize& keySize, INT nFrameCount, INT nTrackCount);
	VOID						DrawTrackRect(CDC& dc, const CRect& rc, COLORREF c);
protected:
	CImage						m_bgImage;
	INT							m_keyCount;	//�ؼ�֡����
	std::vector<GCAnimationKey>		m_tracks;
	GCAnimationCallback*	m_callback;
	CSize						m_keySize;	//һ���ؼ�֡�Ĵ�С
	BOOL						m_bLButtonDown;
	//
	INT							m_nTrackSelectID;
	TrackPosition				m_trackPosition;
	INT							m_nTrackBeginPixel;
	CEdit						m_editName;
	BOOL						m_bEditNameMode;
	CPoint						m_saveFrame;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	CStatic m_stBegin;
	CEdit m_edBegin;
	CStatic m_stEnd;
	CEdit m_edEnd;
};

VOID		DrawLine2(HDC dc, const CPoint& from, const CPoint& to, const CPoint& offset);
VOID		DrawLine2(HDC dc, const CPoint& from, const CPoint& to, COLORREF c);
COLORREF	InvertColor2(COLORREF c);
HCURSOR		GetCursorHandle2(LPCTSTR str);

