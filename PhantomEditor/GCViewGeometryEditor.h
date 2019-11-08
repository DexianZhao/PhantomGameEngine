/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#ifndef __GC_VIEW_GEOMETRY_EDITOR_H__
#define	__GC_VIEW_GEOMETRY_EDITOR_H__

#pragma once
#include "GCViewBase.h"
#include "SubGeometryEditorDlg.h"
#include "PhantomManager.h"

typedef	VOID	(*ProcPartType)(Phantom::MeshData* data, INT nPartIndex, LPARAM nParameter, LPARAM nParameter2);
typedef	VOID	(*ProcSubGeometryData)(Phantom::MeshData* data, Phantom::SubMeshData* geoms, Phantom::SubMesh* render, LPARAM nParameter, LPARAM nParameter2);
typedef	VOID	(*ProcGeometryMaterial)(Phantom::MeshData* data, Phantom::SubMeshData* geoms, Phantom::SubMesh* render, INT nMaterialIndex, LPARAM nParameter, LPARAM nParameter2);
typedef	VOID	(*ProcGeometryAction)(Phantom::MeshData* data, INT nActionID, LPARAM nParameter, LPARAM nParameter2);
typedef	VOID	(*ProcGeometryShader)(Phantom::MeshData* data, Phantom::SubMeshData* geoms, Phantom::SubMesh* render, Phantom::MeshShaderProject* shader, LPARAM nParameter, LPARAM nParameter2);
typedef	VOID	(*ProcGeometryRibbon)(Phantom::MeshData* data, int index, LPARAM nParameter, LPARAM nParameter2);
typedef	VOID	(*ProcGeometryParticle)(Phantom::MeshData* data, Phantom::ParticleEmitterData2* d, LPARAM nParameter, LPARAM nParameter2);

class GCViewGeometryEditor: public GCViewBase
{
public:
	GCViewGeometryEditor(CPhantomGCDoc* docPtr);
	~GCViewGeometryEditor(void);
	//
	virtual	bool				OnWindowProc(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam);
	virtual	VOID				OnActive();		//������
	virtual	VOID				OnDeActive();	//ʧȥ����
	virtual	VOID				CloseFile();
	virtual	BOOL				OpenFile(const wchar_t* szFile);	//���ļ�,���ʧ������Զ�ɾ��
	virtual	BOOL				SaveFile(BOOL bSaveAs);	//�����ļ�
	virtual void				OnFrameMove();	//ÿ�θ���
	virtual void				OnPushRenderObjects();	//��Ⱦ
	virtual void				OnRendering();	//��Ⱦ
	virtual	FileViewerType		GetViewerType(){return FileViewerType_GeometryEditor;}
	virtual	INT					GetPopupMenuID(){return 1;}
	virtual	HICON				GetViewerIcon();
	//
	virtual	VOID		OnCopyTree();
	virtual	VOID		OnPasteTree();
	virtual	BOOL		IsCopyTree();
	virtual	BOOL		IsPasteTree();
	//
	virtual	BOOL		OnDragDropFile(const wchar_t* szFile);	//���ⲿ�ļ����϶����������ڲ���ʱ������
	void				OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp);
	VOID				OnChangeTreeSelect(CMTreeCtrl* treePtr, HTREEITEM hAddItem);	//����ѡ�����οؼ�
	//
	VOID				LoopAllParts(ProcPartType proc, LPARAM nParameter, LPARAM nParameter2 = 0, BOOL bRefreshTree = false);
	//
	VOID				LoopAllGeometrys(ProcSubGeometryData proc, LPARAM nParameter, LPARAM nParameter2 = 0, BOOL bRefreshTree = false);
	VOID				LoopAllActions(ProcGeometryAction proc, LPARAM nParameter, LPARAM nParameter2 = 0, BOOL bRefreshTree = false);
	VOID				LoopAllGeometryMaterials(ProcGeometryMaterial proc, LPARAM nParameter, BOOL bReloadTexture, LPARAM nParameter2 = 0);
	VOID				LoopAllGeometryShaders(ProcGeometryShader proc, LPARAM nParameter, BOOL bRename = false, LPARAM nParameter2 = 0);
	VOID				LoopAllRibbon(ProcGeometryRibbon proc, LPARAM nParameter, BOOL bRename = false, LPARAM nParameter2 = 0);
	VOID				LoopAllParticle(ProcGeometryParticle proc, LPARAM nParameter, BOOL bRename = false, LPARAM nParameter2 = 0);
	//
	void				ExportFbx();
	virtual	VOID				OnDeleteTree();
	virtual	BOOL				IsDeleteTree();
	void				OnTreeViewKeyDown(INT nChar);
	VOID				EnableDisableAll();
	//
	virtual	void		OnUpdateUI(INT nMenuID, CCmdUI* pCmdUI);
	virtual	void		OnCommandUI(INT nMenuID);
	//
	enum{
		GEMOETRY_PART_TYPE		=	1,
		GEOMETRY_MODEL_LIST,
		GEOMETRY_ACTION_LIST,
		GEOMETRY_BIND_LIST,
		GEOMETRY_MODELS,
		GEOMETRY_SHADER_LIST,
		GEOMETRY_SHADER,
		GEOMETRY_MATERIAL,
		GEOMETRY_ACTION,
		GEOMETRY_BIND,
		GEOMETRY_RIBBON_LIST,
		GEOMETRY_RIBBON_BIND,
		GEOMETRY_PARTICLE_LIST,
		GEOMETRY_PARTICLE_BIND,
	};
	VOID						InitGroupProp();
	VOID						InitModelProp();
	VOID						InitShaderProp();
	VOID						InitPartProp();
	VOID						InitMaterialProp();
	VOID						InitActionProp();	//��������
	//
	VOID						RebuildVSPS();
	VOID						RebuildLODs();
	VOID						RebuildShaderVars();
	//
	VOID						ReinitGeometry();
	//
	virtual	BOOL				IsExportPak(){return true;}
	virtual	VOID				ExportPak();
	//
	const wchar_t*				GetShaderMode(int type);
	void						GetShaderMode(std::vector<std::wstring>& values);
	int							GetShaderMode(const wchar_t* szText);
	//
	const wchar_t*				GetShaderTechnique(const char* type);
	void						GetShaderTechnique(std::vector<std::wstring>& values);
	const char*					GetShaderTechnique(const wchar_t* szText);
	//
	virtual	VOID				RebuildTrees();	//���¹��������б�
	VOID						RefreshShaders(Phantom::SubMeshData* s, INT iGeom, HTREEITEM hItem);
	//
	VOID						ResetPartNames();
	VOID						ResetModelNames();
	VOID						ResetActionNames();
	VOID						ResetMaterialProps(int submeshIndex, int mtrlIndex);
	VOID						OnMaterialChange(const CMFCPropertyGridProperty* pProp);
	virtual	VOID				SetModifyed(BOOL bModifyed = TRUE);	//�����޸�״̬
	//
	GCPropertyBase				m_groupProps;
	GCPropertyBase				m_modelProps;
	GCPropertyBase				m_shaderProps;
	GCPropertyBase				m_partListProp;
	GCPropertyBase				m_materialProps;
	GCPropertyBase				m_actionProps;
	GCPropertyBase				m_ribbonEffect;//������Ч
	GCPropertyBase				m_particleProps;//������Ч
	std::map<std::string, std::wstring>		m_vspsTechniques;
	std::map<std::wstring, int>				m_vspsModes;
	//
	VOID						AddActionFile(const char* szFile);
	int							m_nLodViewIndex;
	CSubGeometryEditorDlg		m_subGeometryEditor;
	//
	PropertyPtr					m_propPartName//װ����
								;
	PropertyPtr					m_propModelName,//��ģ��
								m_propModelID,//��ģ��ID
								m_propModelVisible,
								m_propModelZWrite,
								m_propModelUseColor,
								m_propModelSelfAni,
								m_propModelGenTangent,
								m_propModelMinFilter,
								m_propModelMagFilter,
								m_propModelSetCollision,
								m_propModelMaxAnisotropy,
								m_propModelMipmapBias,
								m_propModelVertexCount,
								m_propModelGenLOD,
								m_propModelFaceCount,
								m_propModel32BitMesh,
								m_propModelIsBlend,
								m_propModelHighlight,
								m_propModelLodVisible,
								m_propModelInvertFace,
								m_propModelWithShadow,
								m_propModelToShadow,
								m_propModelInvertTurn,
								m_propModelIsCollision
								;
	//
	PropertyPtr					m_propModelOnAction[MAX_SHOW_ON_ACTION];
	PropertyPtr					m_propModelLODLevel[MAX_LOD_LEVEL_COUNT];
	PropertyPtr					m_shaderTechnique;
	PropertyPtr					m_shaderForceAlpha;
	PropertyPtr					m_shaderSrcBlend;
	PropertyPtr					m_shaderDestBlend;
	PropertyPtr					m_shaderZWriteEnable;
	PropertyPtr					m_shaderCullMode;
	//
	PropertyPtr					m_propGroupRenderToShadow,//ģ����
								m_propGroupByShadowMap,
								m_propGroupShadowEpsilon,
								m_propGroupShaderMode,
								m_propGroupLodRangeLength,
								m_propGroupLodMaxEnable,
								m_propGroupLodMaxVisible,
								m_propGroupClipVisible,
								m_propGroupScale,
								m_propGroupSetCollision,
								m_propGroupHeight,
								m_propGroupHeightBase,
								m_propGroupType,//����
								m_propGroupTableLine,//�����
								m_propGroupDiffuse,//���ʷ���
								//
								m_propGroupShadowVisible,
								m_propGroupShadowUVOffsetX,
								m_propGroupShadowUVOffsetY,
								m_propGroupShadowSize,
								m_propGroupShadowTextureClear
								;
	//
	PropertyPtr					m_groupActiveShader;
	PropertyPtr					m_groupPartsMode;
	PropertyPtr					m_groupShaderCount;
	PropertyPtr					m_groupShowSelect;
	BOOL						m_bPartMode;
	//
	PropertyPtr					m_ribbonBindBone;
	PropertyPtr					m_ribbonBindBone2;
	PropertyFilePtr				m_ribbonTexture;
	PropertyPtr					m_ribbonLiveSecond;
	PropertyPtr					m_ribbonSrcBlend;
	PropertyPtr					m_ribbonDestBlend;
	PropertyPtr					m_ribbonAlpha;
	//
	PropertyPtr					m_particleBindBone;
	PropertyFilePtr				m_particleTexture;
	PropertyPtr					m_particleSpeed;
	PropertyPtr					m_particleVariation;
	PropertyPtr					m_particleConeAngle;
	//
	PropertyPtr					m_particleLifeSpan;
	PropertyPtr					m_particleEmissionRate;
	PropertyPtr					m_particleWidth;
	PropertyPtr					m_particleHeight;
	//��ͼUV����
	PropertyPtr					m_particleRow;
	PropertyPtr					m_particleCol;
	PropertyPtr					m_particleTailLength;
	PropertyPtr					m_particleMiddleTime;
	PropertyPtr					m_particleSrcBlend;
	PropertyPtr					m_particleEnable;
	PropertyPtr					m_particleDestBlend;
	PropertyColorPtr			m_particleColor[3];
	PropertyPtr					m_particleAlpha[3];
	PropertyPtr					m_particleScaling[3];
	PropertyPtr					m_particleUVAnimFps;
	PropertyPtr					m_particleLifeSpanUVAnim[3];
	PropertyPtr					m_particleDecayUVAnim[3];
	PropertyPtr					m_particlePivot[3];
	PropertyPtr					m_particlePlaneNormal[3];
	//
	PropertyFilePtr				m_propGroupShadowTexture;
	//
	PropertyPtr					m_propMtrlCullMode,//����
								m_propMtrlAlphaMode,
								m_propMtrlLodEnable,
								m_propMtrlVisible,
								m_propMtrlVisibleInShadowMap,
								m_propMtrlSrcBlend,
								m_propMtrlDestBlend,
								m_propMtrlFaceCount,
								m_propMtrlAnimationSpeed,
								m_propMtrlTextureChange,
								m_propMtrlColorChange,
								m_propMtrlTransparent
								;
	PropertyFilePtr				m_propMtrlTextureFile[Phantom::TEXTURE_MAX_COUNT];
	PropertyFilePtr				m_propMtrlDiffuseFile[DIFFUSE_TEXTURE_COUNT];
	PropertyColorPtr			m_propMtrlDiffuseColors[DIFFUSE_TEXTURE_COUNT];
	PropertyPtr					m_propMtrlTextureClear;//[TEXTURE_MAX_COUNT];
	PropertyColorPtr			m_propMtrlDiffuseColor,
								m_propMtrlEmissiveColor,
								m_propMtrlSpecularColor;

	PropertyPtr					m_propActionName,
								m_propActionSetDefault,
								m_propActionKeyCount,
								m_propActionID,
								m_propActionBeginKey,//����
								m_propActionEndKey,
								m_propActionSpeed,
								m_propActionRotation,
								m_propActionHit1,
								m_propActionHit2,
								m_propActionType,
								m_propActionSndPlayKey,
								m_propActionSndPlayKey2,
								m_propActionMoveOffset,
								m_propActionRibbon,//�Ƿ�������Ч��
								m_propActionLoopMode//�Ƿ�ѭ������
								;
	PropertyFilePtr				m_propActionSndFile;
	PropertyPtr					m_propActionSndClear;

	HTREEITEM					m_hActionList,
								m_hGeometryList,
								m_hRibbonList,
								m_hParticleList;
	//
	VOID						BuildRibbonList();
	VOID						BuildParticleList();
	VOID						BuildActionList();
	VOID						BuildGeometrys();
	VOID						BuildTableLine();
	BOOL						m_bAutoMoveMode;
	BOOL						m_bShowBox;
	Phantom::float3				m_moveDir;
	Phantom::float3				m_moveOrig;
	BOOL				m_bMoveDir;
	float				m_fMoveLength;
	float				m_fMoveTime;
	Phantom::CameraDataLocal	m_cameraSave;
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

	Phantom::AutoPtr<Phantom::Mesh>	m_pGeometryPtr;

};

#endif
