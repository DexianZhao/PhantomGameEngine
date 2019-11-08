//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	�ļ�       :   GCUnit2DEditor.h
	�������   :   ��Ӱ��Ϸ����

	��Ʊ�д�� :   �Ե���(Ӣ��:ZhaoDexian)
	Email: yuzhou_995@hotmail.com
	
	Copyright 2009-2016 Zhao Dexian
	
	-------------------------------------------------------------------------------------------------


	-------------------------------------------------------------------------------------------------
	*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GCGAMEMAKER__H___
#define ___GCGAMEMAKER__H___
#pragma once
#pragma once
#include "GCViewBase.h"
#include "TrackAnimationCtrl.h"

typedef	VOID	(*ProcUnit2DEquip)(IUnit2DEquip* data, LPARAM nParameter, LPARAM nParameter2);
typedef	VOID	(*ProcUnit2DAnimation)(IUnit2DAnimationData* data, LPARAM nParameter, LPARAM nParameter2);
typedef	VOID	(*ProcUnit2DTexture)(IUnit2DTexture* data, LPARAM nParameter, LPARAM nParameter2);

class GCViewUnit2DEditor: public GCViewBase
{
public:
	GCViewUnit2DEditor(CPhantomGCDoc* docPtr);
	~GCViewUnit2DEditor(void);
	virtual	VOID				OnActive();		//������
	virtual	VOID				OnDeActive();	//ʧȥ����
	virtual	VOID				CloseFile();
	virtual	BOOL				OpenFile(const wchar_t* szFile);	//���ļ�,���ʧ������Զ�ɾ��
	virtual	BOOL				SaveFile(BOOL bSaveAs);	//�����ļ�
	virtual void				OnFrameMove();	//ÿ�θ���
	virtual void				OnPushRenderObjects();	//��Ⱦ
	virtual	FileViewerType		GetViewerType(){return FileViewerType_Unit2D;}
	virtual	HICON				GetViewerIcon();
	virtual	INT					GetPopupMenuID(){return 3;}
	virtual void				OnRenderingEnd();	//��Ⱦ
	virtual	bool				OnWindowProc(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam);
	//
	VOID						RebuildTrees();
	enum{
		UNIT2D_NONE	=	0,
		UNIT2D_MAIN,
		UNIT2D_EQUIP_LIST,			//װ���б�
		UNIT2D_EQUIP,
		UNIT2D_ANIMATION,
		UNIT2D_TEXTURE,
		UNIT2D_ANIMATION_LIST,		//��������
		UNIT2D_ANIMATION_ID,		//����
	};
	VOID						GetNewFileName(wchar_t* szFile);
	void						OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp);
	VOID						OnChangeTreeSelect(CMTreeCtrl* treePtr, HTREEITEM hAddItem);	//����ѡ�����οؼ�
	virtual	void				OnUpdateUI(INT nMenuID, CCmdUI* pCmdUI);
	virtual	void				OnCommandUI(INT nMenuID);
	void						OnTreeViewKeyDown(INT nChar);
	//
	VOID						OnRenameAnimations(IUnit2DAnimationData* ani);
	//
	VOID						LoopAllUnit2DEquips(ProcUnit2DEquip proc, LPARAM nParameter = 0, LPARAM nParameter2 = 0, BOOL bRename = FALSE);
	VOID						LoopAllUnit2DAnimations(ProcUnit2DAnimation proc, LPARAM nParameter = 0, LPARAM nParameter2 = 0, BOOL bRename = FALSE);
	VOID						LoopAllUnit2DTexture(ProcUnit2DTexture proc, LPARAM nParameter = 0, LPARAM nParameter2 = 0, BOOL bRect = false);
	//
	VOID						BuildAll();
	//
	GCPropertyBase				m_unitProp;
	GCPropertyBase				m_equipProp;
	GCPropertyBase				m_textureProp;
	GCPropertyBase				m_animationIDProp;
	//
	VOID						InitUnitProp();
	VOID						InitEquipProp();
	VOID						InitTextureProp();
	VOID						InitAnimaionProp();
	//
	PropertyPtr					m_equipName;
	PropertyPtr					m_equipID;
	PropertyPtr					m_equipLayer;
	//
	PropertyPtr					m_textureUVCountW;
	PropertyPtr					m_textureUVCountH;
	PropertyPtr					m_textureUVBeginIndex;
	PropertyPtr					m_textureUVPlayCount;
	PropertyPtr					m_textureTileCountW;
	PropertyPtr					m_textureTileCountH;
	PropertyPtr					m_textureScale;
	PropertyFilePtr				m_textureFile;
	PropertyPtr					m_textureFileClear;//���ÿ�ͼƬ
	PropertyPtr					m_textureRectL;
	PropertyPtr					m_textureRectT;
	PropertyPtr					m_textureRectW;
	PropertyPtr					m_textureRectH;
	PropertyPtr					m_textureRenderSide;
	PropertyPtr					m_texturePick;
	PropertyPtr					m_textureRegetRect;
	//
	PropertyPtr					m_animationName;
	PropertyPtr					m_animationID;
	//
	PropertyPtr					m_unitSizeW;
	PropertyPtr					m_unitSizeH;
	PropertyPtr					m_unitCenterX;
	PropertyPtr					m_unitCenterY;
	//
	VOID						RefreshEquips();
	VOID						RefreshAnimations();
	//
	virtual	VOID				OnCopyTree();
	virtual	VOID				OnPasteTree();
	virtual	BOOL				IsCopyTree();
	virtual	BOOL				IsPasteTree();
	virtual	VOID				OnDeleteTree();
	virtual	BOOL				IsDeleteTree();
	//
	VOID						RefreshEquip(IUnit2DEquip* ele, HTREEITEM hEquip);
	//
	HTREEITEM					m_hEquipList;
	HTREEITEM					m_hAnimationList;
public:
	IUnit2DData*				m_dataPtr;
	IUnit2DRender*				m_renderPtr;
	BOOL						m_bLButtonDown;
	CPoint						m_downPoint;
	CPoint						m_downOffset;
	enum EditorMode{
		EditorMode_None	=	0,
		EditorMode_CenterPos,
	};
	EditorMode					m_editMode;
};



#endif
