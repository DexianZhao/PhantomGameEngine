/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include "GCViewBase.h"
#include "MyLuaEditor.h"

class GCCodeEditor: public GCViewBase
{
public:
	GCCodeEditor(CPhantomGCDoc* docPtr);
	~GCCodeEditor(void);
	virtual	VOID				OnActive();		//������
	virtual	VOID				OnDeActive();	//ʧȥ����
	virtual	VOID				CloseFile();
	virtual	BOOL				OpenFile(const wchar_t* szFile);	//���ļ�,���ʧ������Զ�ɾ��
	virtual	BOOL				SaveFile(BOOL bSaveAs=false);	//�����ļ�
	virtual void				OnFrameMove();	//ÿ�θ���
	virtual void				OnPushRenderObjects();	//��Ⱦ
	virtual	FileViewerType		GetViewerType(){return FileViewerType_Lua;}
	virtual	HICON				GetViewerIcon();
	virtual	VOID		OnSetFocus();
	virtual void		OnRenderingEnd();	//��Ⱦ
	//
	EditorCallbackT<GCCodeEditor>	m_cb;
	VOID				RebuildTrees();
	enum{
		FUNCTION_NONE	=	0,
		FUNCTION_MAIN,
	};
	void				OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp);
	VOID				OnChangeTreeSelect(CMTreeCtrl* treePtr, HTREEITEM hAddItem);	//����ѡ�����οؼ�
	virtual	void		OnUpdateUI(INT nMenuID, CCmdUI* pCmdUI);
	virtual	void		OnCommandUI(INT nMenuID);
	//
	VOID				BuildAll();
	//
public:
	CMyLuaEditor		m_luaEditor;
};

