#pragma once
#include "GCViewBase.h"
#include "IUnit3D.h"
#include "TrackAnimationCtrl.h"
#include "DlgViewerHttp.h"

class GCForumViewer: public GCViewBase
{
public:
	GCForumViewer(CPhantomGCDoc* docPtr);
	~GCForumViewer(void);
	virtual	VOID				OnActive();		//������
	virtual	VOID				OnDeActive();	//ʧȥ����
	virtual	BOOL				OpenFile(const wchar_t* szFile);	//���ļ�,���ʧ������Զ�ɾ��
	virtual	BOOL				SaveFile(BOOL bSaveAs);	//�����ļ�
	virtual void				OnFrameMove(const RenderParameter& r);	//ÿ�θ���
	virtual void				OnPushRenderObjects(const RenderParameter& r);	//��Ⱦ
	virtual	FileViewerType		GetViewerType(){return FileViewerType_HomeViewer;}
	virtual	HICON				GetViewerIcon();
	virtual	VOID		GetNewFileName(wchar_t* szFile);
	virtual void		OnRenderingEnd(const RenderParameter& r);	//��Ⱦ
	//
	VOID				RebuildTrees();
	enum{
		TEXTURE_NONE	=	0,
		TEXTURE_MAIN,
	};
	void				OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp);
	VOID				OnChangeTreeSelect(CMTreeCtrl* treePtr, HTREEITEM hAddItem);	//����ѡ�����οؼ�
	virtual	void		OnUpdateUI(INT nMenuID, CCmdUI* pCmdUI);
	virtual	void		OnCommandUI(INT nMenuID);
	//
	VOID				BuildAll();
	//
public:
	CDlgViewerHttp		m_viewerHttp;
};

