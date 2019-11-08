//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	�ļ�       :   GCCursorEditor.h
	�������   :   ��Ӱ��Ϸ����

	��Ʊ�д�� :   �Ե���(Ӣ��:ZhaoDexian)
	Email: yuzhou_995@hotmail.com
	
	Copyright 2009-2016 Zhao Dexian
	
	-------------------------------------------------------------------------------------------------


	-------------------------------------------------------------------------------------------------
	*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GCCURSOREDITOR__H___
#define ___GCCURSOREDITOR__H___


#pragma once
#include "GCViewBase.h"
#include "IUnit3D.h"
#include "TrackAnimationCtrl.h"

typedef	VOID	(*ProCursors)(ICursorRender* data, LPARAM nParameter, LPARAM nParameter2);

class GCViewCursorEditor: public GCViewBase
{
public:
	GCViewCursorEditor(CPhantomGCDoc* docPtr);
	~GCViewCursorEditor(void);
	virtual	VOID				OnActive();		//������
	virtual	VOID				OnDeActive();	//ʧȥ����
	virtual	VOID				CloseFile();
	virtual	BOOL				OpenFile(const wchar_t* szFile);	//���ļ�,���ʧ������Զ�ɾ��
	virtual	BOOL				SaveFile(BOOL bSaveAs);	//�����ļ�
	virtual void				OnFrameMove(const RenderParameter& r);	//ÿ�θ���
	virtual void				OnPushRenderObjects(const RenderParameter& r);	//��Ⱦ
	virtual	FileViewerType		GetViewerType(){return FileViewerType_CursorEditor;}
	virtual	HICON				GetViewerIcon();
	virtual	INT					GetPopupMenuID(){return 4;}
	virtual void				OnRenderingEnd(const RenderParameter& r);	//��Ⱦ
	//
	VOID						LoopAllCursors(ProCursors proc, LPARAM nParameter = 0, LPARAM nParameter2 = 0, BOOL bRename = FALSE, BOOL bDefault = false);
	//
	VOID						GetNewFileName(wchar_t* szFile);
	VOID						RebuildTrees();
	void						OnTreeViewKeyDown(INT nChar);
	//
	virtual	VOID				OnCopyTree();
	virtual	VOID				OnPasteTree();

	enum{
		CURSOR_NONE	=	0,
		CURSOR_MAIN,
		CURSOR_CURSOR,
	};
	void						OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp);
	VOID						OnChangeTreeSelect(CMTreeCtrl* treePtr, HTREEITEM hAddItem);	//����ѡ�����οؼ�
	virtual	void				OnUpdateUI(INT nMenuID, CCmdUI* pCmdUI);
	virtual	void				OnCommandUI(INT nMenuID);
	virtual	BOOL				IsCopyTree();
	virtual	BOOL				IsPasteTree();
	virtual	VOID				OnDeleteTree();
	virtual	BOOL				IsDeleteTree();
	//
	VOID						BuildAll();
	VOID						RefreshAllCursors();
	//
	VOID						InitCursorProp();
	//
	GCPropertyBase				m_managerProp;
	PropertyPtr					m_managerHardware;
	//
	GCPropertyBase				m_cursorProp;
	//
	PropertyPtr					m_cursorPlaySpeed;
	PropertyFilePtr				m_cursorFileSet;
	PropertyPtr					m_cursorFileClear;
	PropertyPtr					m_cursorName;
	PropertyPtr					m_cursorIsDefault;
	//
	PropertyPtr					m_cursorCenterX;
	PropertyPtr					m_cursorCenterY;
	//
	PropertyPtr					m_cursorUVMapW;
	PropertyPtr					m_cursorUVMapH;
	PropertyPtr					m_cursorUVMapBegin;
	PropertyPtr					m_cursorUVMapCount;
public:
	ICursorManager*				m_cursorPtr;
};



#endif
