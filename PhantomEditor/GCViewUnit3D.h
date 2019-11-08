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
#include "PhantomUnit3D.h"
#include "TrackAnimationCtrl.h"
#include "GCTrackEditor.h"
#include "PhantomUnit3D.h"

typedef	VOID	(*ProActionProject)(Phantom::Unit3DActionData* data, LPARAM nParameter, LPARAM nParameter2);
typedef	VOID	(*ProEffectElement)(Phantom::CActionElement* data, LPARAM nParameter, LPARAM nParameter2);
typedef	VOID	(*ProUnitMesh)(Phantom::Unit3DMesh* render, Phantom::Unit3DMeshData* data, LPARAM nParameter, LPARAM nParameter2);

class GCViewUnit3D: public GCViewBase, public ITrackAnimationCallback
{
public:
	GCViewUnit3D(CPhantomGCDoc* docPtr);
	~GCViewUnit3D(void);
	virtual	VOID				OnActive();		//������
	virtual	VOID				OnDeActive();	//ʧȥ����
	virtual	VOID				CloseFile();
	virtual	BOOL				OpenFile(const wchar_t* szFile);	//���ļ�,���ʧ������Զ�ɾ��
	virtual	BOOL				SaveFile(BOOL bSaveAs);	//�����ļ�
	virtual void				OnFrameMove();	//ÿ�θ���
	virtual void				OnPushRenderObjects();	//��Ⱦ
	virtual	FileViewerType		GetViewerType(){return FileViewerType_Unit3D;}
	void						OnRendering();	//��Ⱦ
	virtual	INT					GetPopupMenuID(){return 15;}
	virtual	HICON				GetViewerIcon();
	//
	VOID						LoopAllMeshs(ProUnitMesh proc, LPARAM nParameter = 0, LPARAM nParameter2 = 0, BOOL bRename = FALSE);
	VOID						LoopAllActions(ProActionProject proc, LPARAM nParameter = 0, LPARAM nParameter2 = 0, BOOL bRename = FALSE);
	VOID						LoopAllElements(ProEffectElement proc, LPARAM nParameter = 0, LPARAM nParameter2 = 0, BOOL bRename = FALSE);
public:
	INT							GetKeyFrameCount();
	BOOL						OnTrackChange(INT id, INT nBeginFrame, INT nEndFrame);	//�������TRUE��ʾ���Ա��ı�
	VOID						EnumTracks(std::vector<TrackItem>& rets);
	//
	VOID						AddAllActions();
	VOID						GetNewFileName(wchar_t* szFile);
	VOID						RebuildTrees();
	enum{
		UNIT3D_NONE	=	0,
		UNIT3D_MAIN,
		UNIT3D_MESH_LIST,
		UNIT3D_CHILD_MESH,
		UNIT3D_ACTION_PROJECT,
		UNIT3D_GEOMETRY,
		UNIT3D_PARTICLE,
		UNIT3D_SOUND,
		UNIT3D_UNITCONTROL,
		UNIT3D_MESHCONTROL,
		UNIT3D_PARTICLE_ONE,
		//
		UNIT3D_VALUE_ALPHA,
		UNIT3D_VALUE_COLOR,
		UNIT3D_VALUE_SCALE,
		UNIT3D_VALUE_SCALEFull,
		UNIT3D_VALUE_POSITION,
		UNIT3D_VALUE_OFFSET_POSITION,
		UNIT3D_VALUE_ROTATION,
		UNIT3D_VALUE_PARAM1,
		UNIT3D_VALUE_PARAM2,
		UNIT3D_VALUE_PARAM3,
		UNIT3D_MAX_TRACK,
	};
	VOID								SetAnimationPtr(Phantom::CActionElement* ele);
	VOID								SetEmissionAni(Phantom::CActionElement* ele);
	//
	virtual	VOID						OnCopyTree();
	virtual	VOID						OnPasteTree();
	virtual	BOOL						IsCopyTree();
	virtual	BOOL						IsPasteTree();
	virtual	VOID						OnDeleteTree();
	virtual	BOOL						IsDeleteTree();
	//
	void								OnTreeViewKeyDown(INT nChar);
	void								OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp);
	VOID								OnChangeTreeSelect(CMTreeCtrl* treePtr, HTREEITEM hAddItem);	//����ѡ�����οؼ�
	virtual	void						OnUpdateUI(INT nMenuID, CCmdUI* pCmdUI);
	virtual	void						OnCommandUI(INT nMenuID);
	//
	VOID								RefreshMeshs(HTREEITEM hMesh);
	VOID								RefreshAction(Phantom::Unit3DActionData* proj, HTREEITEM hItem);
	VOID								BuildAll();
	//
	VOID								InitEffectProp();
	VOID								InitActionProp();
	VOID								InitElementProp();
	VOID								InitParticleProp();
	//
	VOID								SetElementProp(Phantom::Unit3DActionData* proj, Phantom::CActionElement* ele);
public:
	GCPropertyBase						m_unitProperties;
	GCPropertyBase						m_actionProperties;
	GCPropertyBase						m_elementProperties;
	GCPropertyBase						m_particleProperties;
	FileName							m_lastGeometryFile;
	//
	VOID								InitMeshProp();
	GCPropertyBase						m_meshProperties;
	PropertyFilePtr						m_meshGeometryFile;	//��ģ���ļ�
	PropertyPtr							m_meshGeometryScale;	//
	PropertyPtr							m_meshGeometryFileClear;	//�����б�
	PropertyPtr							m_meshName;	//�����б�
	std::vector<PropertyPtr>			m_childMeshs;//[MAX_ELEMENT_MESH];	//װ���б��Զ������ʹ�С,��󶼻���һ��
public:
	PropertyFilePtr						m_unitGeometryFile;	//��ģ���ļ�
	PropertyPtr							m_unitGeometryFileOpen;	//��ģ���ļ�
	PropertyPtr							m_unitGeometryScale;
	PropertyPtr							m_unitIsStatic;
	PropertyPtr							m_unitIsPick;
	//
	PropertyPtr							m_actionID;
	PropertyPtr							m_actionName;
	PropertyPtr							m_actionKeyCount;
	PropertyPtr							m_actionNextId;
	PropertyPtr							m_actionSpeed;
	PropertyPtr							m_actionActionType;
	PropertyPtr							m_actionIsTemplate;
	PropertyPtr							m_actionParameter[MAX_FLOAT_PARAMETER];

//	PropertyPtr							m_actionID;	//�����б�
	//
	PropertyPtr							m_elementName;	//�����б�
	PropertyPtr							m_elementFrameCount;	//���б�
	PropertyFilePtr						m_elementGeometryFile;	//�����б�
	PropertyFilePtr						m_elementSoundFile;		//�����б�
	PropertyFilePtr						m_elementTextureFile;	//�����б�
	PropertyPtr							m_elementFileOpen;	//��ģ���ļ�
	PropertyPtr							m_elementVisible;	//�����б�
	PropertyPtr							m_elementBindPoint;	//���б�
	PropertyPtr							m_elementVisibleTempalate;
	//PropertyPtr							m_elementParts[MAX_ELEMENT_MESH];	//װ���б�
	//
	PropertyPtr							m_elementActionGroup;
	PropertyPtr							m_elementMusicGroup;
	PropertyPtr							m_elementMeshGroup;
	PropertyPtr							m_elementChildMeshGroup;
	PropertyPtr							m_emissionGroup;
	//
	PropertyPtr							m_elementChildMeshs;
	//
	PropertyPtr							m_elementActionID;
	PropertySelListPtr					m_elementSubMeshs;
	PropertyPtr							m_elementKeyBegin;
	PropertyPtr							m_elementKeyEnd;
	PropertyPtr							m_elementLoopCount;
	PropertyPtr							m_elementPlayLoop;
	PropertyPtr							m_elementIncidence;
	PropertyPtr							m_elementWeight;
	PropertyPtr							m_elementPlaySpeed;
	VOID								InitActions(Phantom::Mesh* g, int nActionID, int nBegin, int nEnd);
	//
	PropertyPtr							m_emissionRenderType;//ParticleRenderType					GetRenderType();
	//PropertyPtr							m_emissionCreationTime;//λ�ƿ�ʼ��
	//PropertyPtr							m_emissionMaxParticle;
	PropertyPtr							m_emissionTextureOP;
	PropertyPtr							m_emissionSrcBlend;
	PropertyPtr							m_emissionDestBlend;
	//PropertyPtr							m_emissionZEnable;
	PropertyPtr							m_emissionType;
	PropertyPtr							m_emissionUseSystemWind;
	PropertyPtr							m_emissionFaceIndex;
	PropertyPtr							m_emissionBindPoint;
	//
	//�������,m_emissionProperties
	//PropertyPtr							m_emitTexFrameCount;	//>0������Ч
	//PropertyPtr							m_emitTexAniSpeed;
	//PropertyPtr							m_emitTexLoopCount;
	//PropertyPtr							m_emitTexRandom;
	//PropertyPtr							m_emitTexWidthCount;
	//PropertyPtr							m_emitTexHeightCount;
	////
	//PropertyPtr							m_emitTrackEnable;
	//PropertyPtr							m_emitTrackMaxCount;
	//PropertyPtr							m_emitTrackDelayTime;
	//PropertyPtr							m_emitTrackU;
	//PropertyPtr							m_emitTrackV;
	////
	//PropertyPtr							m_particleFrame;	//���ӹؼ�֡����
	////
	//PropertyPtr							m_emitRangeMinX;
	//PropertyPtr							m_emitRangeMaxX;
	//PropertyPtr							m_emitRangeMinY;
	//PropertyPtr							m_emitRangeMaxY;
	//PropertyPtr							m_emitRangeMinZ;
	//PropertyPtr							m_emitRangeMaxZ;
	//PropertyPtr							m_emitLifeMin;
	//PropertyPtr							m_emitLifeMax;
	//PropertyColorPtr					m_emitColorMin;
	//PropertyColorPtr					m_emitColorMax;
	//PropertyPtr							m_emitAlphaMin;
	//PropertyPtr							m_emitAlphaMax;
	//PropertyPtr							m_emitOffsetMinX;//λ�ƿ�ʼ��
	//PropertyPtr							m_emitOffsetMaxX;
	//PropertyPtr							m_emitOffsetMinY;//λ�ƿ�ʼ��
	//PropertyPtr							m_emitOffsetMaxY;
	//PropertyPtr							m_emitOffsetMinZ;//λ�ƿ�ʼ��
	//PropertyPtr							m_emitOffsetMaxZ;
	//PropertyPtr							m_emitScaleFullMin;//λ�ƿ�ʼ��
	//PropertyPtr							m_emitScaleFullMax;
	////
	//PropertyPtr							m_emitScaleMinX;//λ�ƿ�ʼ��
	//PropertyPtr							m_emitScaleMaxX;
	//PropertyPtr							m_emitScaleMinY;//λ�ƿ�ʼ��
	//PropertyPtr							m_emitScaleMaxY;
	//PropertyPtr							m_emitScaleMinZ;//λ�ƿ�ʼ��
	//PropertyPtr							m_emitScaleMaxZ;
	//PropertyPtr							m_emitRotationMinX;//λ�ƿ�ʼ��
	//PropertyPtr							m_emitRotationMaxX;
	//PropertyPtr							m_emitRotationMinY;//λ�ƿ�ʼ��
	//PropertyPtr							m_emitRotationMaxY;
	//PropertyPtr							m_emitOffsetSelfMin;//λ�ƿ�ʼ��
	//PropertyPtr							m_emitOffsetSelfMax;
	//PropertyPtr							m_emitSelfRotationMin;//λ�ƿ�ʼ��
	//PropertyPtr							m_emitSelfRotationMax;
	//
	virtual	VOID		PlayAnimation();
	virtual	VOID		StopAnimation();
	virtual	VOID		PauseAnimation(BOOL bPause);
	virtual	VOID		SetAnimationLoop(BOOL bLoop);
	virtual	BOOL		IsAnimationCanPlayStop();
	virtual	BOOL		IsAnimationCanPause();
	virtual	BOOL		IsAnimationCanLoop();
	virtual	BOOL		IsAnimationPlaying();
	virtual	BOOL		IsAnimationPause();
	virtual	BOOL		IsAnimationLoop();
	//���ӵ����ӿ��ƶ���
public:
	//
	CTrackAnimationCtrl	m_trackCtrl;
	//CFloatAnimationCtrl	m_floatAni;
	GCTrackEditor		m_trackDlg;
	//EffectProp
public:
	Phantom::AutoPtr<Phantom::Unit3DData>	m_unitPtr;
	Phantom::AutoPtr<Phantom::Unit3D>		m_unitRender;
};

