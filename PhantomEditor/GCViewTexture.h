#pragma once
#include "GCViewBase.h"
#include "TrackAnimationCtrl.h"

class GCViewTextureEditor: public GCViewBase
{
public:
	GCViewTextureEditor(CPhantomGCDoc* docPtr);
	~GCViewTextureEditor(void);
	virtual	VOID				OnActive();		//������
	virtual	VOID				OnDeActive();	//ʧȥ����
	virtual	VOID				CloseFile();
	virtual	BOOL				OpenFile(const wchar_t* szFile);	//���ļ�,���ʧ������Զ�ɾ��
	virtual	BOOL				SaveFile(BOOL bSaveAs);	//�����ļ�
	virtual void				OnFrameMove();	//ÿ�θ���
	virtual void				OnPushRenderObjects();	//��Ⱦ
	virtual	FileViewerType		GetViewerType(){return FileViewerType_Texture;}
	virtual	HICON				GetViewerIcon();
	virtual void				OnRenderingEnd();	//��Ⱦ
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
	//std::vector<IGeometryGroup*>	m_saveGeometrys;//����ģ�Ͷ���
	//IGeometryGroup*		m_geometryPtr;
	//IDialog2D*			m_dialogPtr;
	Phantom::Texture*		m_texturePtr;
};

