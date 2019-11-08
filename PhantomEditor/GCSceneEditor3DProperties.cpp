//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	�ļ�       :   GCSceneEditor3D.cpp
	�������   :   ��Ӱ��Ϸ����

	��Ʊ�д�� :   �Ե���(Ӣ��:ZhaoDexian)
	Email: yuzhou_995@hotmail.com
	
	Copyright 2009-2016 Zhao Dexian
	
	-------------------------------------------------------------------------------------------------


	-------------------------------------------------------------------------------------------------
	*/
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "StdAfx.h"
#include "GCSceneEditor3D.h"
#include "MainFrm.h"
#include "PropertiesDialogWnd.h"
//#include "GCGameProject.h"
int	GetSceneObjTypeCount(){return 5;}
const wchar_t*	GetSceneObjType(int type)
{
	switch(type)
	{
	case 1:
		return Language(L"�¼�����");
	case 2:
		return Language(L"�ɵ�ѡ:��̬����");
	case 3:
		return Language(L"�������");
	case 4:
		return Language(L"NPC����");
	default:
		return Language(L"��̬����");
	};
	return Language(L"��̬����");
}
VOID		GCSceneEditor3D::LoopAllSkys(ProSceneSky proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
{
	std::map<HTREEITEM,TreeItemType*> selectTypes;
	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
	{
		HTREEITEM hItem		=	m_treeView.GetSelect(i);
		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
		if(type)
		{
			selectTypes[hItem]	=	type;
		}
	}
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == this->SCENE3D_SKY)
		{
			Phantom::PtrID id;
			id.id	=	type->p1;
			Phantom::SceneSkyData* sky	=	m_scene3D->m_skyDataPtr.GetDataPtr(id);
			if(proc)
				(*proc)(m_scene3D, sky, nParameter, nParameter2);
			SetModifyed(true);
			if(bRename)
				m_treeView.SetItemText(it->first, Wutf8(sky->name.t));
		}
	}
}
//
//VOID		GCSceneEditor3D::LoopAllShadows(ProSceneShadow proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
//{
//	std::map<HTREEITEM,TreeItemType*> selectTypes;
//	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
//	{
//		HTREEITEM hItem		=	m_treeView.GetSelect(i);
//		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
//		if(type)
//		{
//			selectTypes[hItem]	=	type;
//		}
//	}
//	//for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
//	//{
//	//	TreeItemType* type	=	it->second;
//	//	if(!type)
//	//		continue;
//	//	if(type->type == this->SCENE3D_EFFECT_SHADOW)
//	//	{
//	//		Phantom::PtrID id;
//	//		id.id	=	type->p1;
//	//		SceneShadowData* sky	=	m_scene3D->GetShadowDataPtr()->GetDataPtr(id);
//	//		if(proc)
//	//			(*proc)(m_scene3D, sky, nParameter, nParameter2);
//	//		SetModifyed(true);
//	//		if(bRename)
//	//			m_treeView.SetItemText(it->first, W(sky->name.t));
//	//	}
//	//}
//}
//
//VOID		GCSceneEditor3D::LoopAllAdvanceds(ProSceneAdvanced proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
//{
//	std::map<HTREEITEM,TreeItemType*> selectTypes;
//	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
//	{
//		HTREEITEM hItem		=	m_treeView.GetSelect(i);
//		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
//		if(type)
//		{
//			selectTypes[hItem]	=	type;
//		}
//	}
//	//for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
//	//{
//	//	TreeItemType* type	=	it->second;
//	//	if(!type)
//	//		continue;
//	//	if(type->type == this->SCENE3D_EFFECT_ADVANCED)
//	//	{
//	//		Phantom::PtrID id;
//	//		id.id	=	type->p1;
//	//		IAdvancedEffect* sky	=	m_scene3D->GetAdvancedEffects().GetDataPtr(id);
//	//		if(proc)
//	//			(*proc)(m_scene3D, sky, nParameter, nParameter2);
//	//		SetModifyed(true);
//	//		if(bRename)
//	//			m_treeView.SetItemText(it->first, W(sky->GetName()));
//	//	}
//	//}
//}
//
//VOID		GCSceneEditor3D::LoopAllFlares(ProSceneFlare proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
//{
//	std::map<HTREEITEM,TreeItemType*> selectTypes;
//	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
//	{
//		HTREEITEM hItem		=	m_treeView.GetSelect(i);
//		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
//		if(type)
//		{
//			selectTypes[hItem]	=	type;
//		}
//	}
//	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
//	{
//		TreeItemType* type	=	it->second;
//		if(!type)
//			continue;
//		if(type->type == this->SCENE3D_FLARE)
//		{
//			Phantom::PtrID id;
//			id.id	=	type->p1;
//			Phantom::SceneSkyData* sky	=	m_scene3D->m_skyDataPtr.GetDataPtr(id);
//			if(proc)
//				(*proc)(m_scene3D, sky, type->p2, nParameter, nParameter2);
//			SetModifyed(true);
//			if(bRename)
//				m_treeView.SetItemText(it->first, Wutf8(sky->name.t));
//		}
//	}
//}

VOID		GCSceneEditor3D::LoopAllObjects(ProSceneObject proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
{
	std::map<HTREEITEM,TreeItemType*> selectTypes;
	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
	{
		HTREEITEM hItem		=	m_treeView.GetSelect(i);
		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
		if(type)
		{
			selectTypes[hItem]	=	type;
		}
	}
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == this->SCENE3D_OBJECT)
		{
			Phantom::PtrID id;
			id.id	=	type->p1;
			Phantom::SceneObjectFile* file	=	m_scene3D->m_objectFilePtr.GetDataPtr(id);
			if(proc)
				(*proc)(m_scene3D, file, nParameter, nParameter2);
			SetModifyed(true);
			if(bRename)
				m_treeView.SetItemText(it->first, Wutf8(file->name.t));
		}
	}
}
VOID		GCSceneEditor3D::LoopAllEnv(ProSceneEnv proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
{
	std::map<HTREEITEM,TreeItemType*> selectTypes;
	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
	{
		HTREEITEM hItem		=	m_treeView.GetSelect(i);
		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
		if(type)
		{
			selectTypes[hItem]	=	type;
		}
	}
	this->BeginUndo();
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == this->SCENE3D_ENV)
		{
			Phantom::SceneEnv* env = 0;
			if(type->p1==0)
				env = &m_scene3D->m_defaultEnv;
			else
				env = m_scene3D->GetEnvByID(type->p1);
			if(proc&&env)
			{
				UndoPtr uptr;
				uptr.buff = AddUndoRedo(GCSceneEditor3D::SCENE3D_ENV, (ProcUndoRedo)proc);
				uptr.urMode = UndoRedoBuffer::URMode_Add;
				uptr.buff->m_id		=	type->p1;
				(*proc)(m_scene3D, env, nParameter, nParameter2, &uptr);
			}
			SetModifyed(true);
			if(bRename&&type->p1>0)
				m_treeView.SetItemText(it->first, Wutf8(env->m_name.t));
		}
	}
}
VOID		GCSceneEditor3D::LoopAllLight(ProSceneLight proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
{
	this->BeginUndo();
	if(m_lightSelect==0){
		std::map<HTREEITEM,TreeItemType*> selectTypes;
		for(int i=0;i<this->m_treeView.GetSelectCount();i++)
		{
			HTREEITEM hItem		=	m_treeView.GetSelect(i);
			TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
			if(type)
			{
				selectTypes[hItem]	=	type;
			}
		}
		for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
		{
			TreeItemType* type	=	it->second;
			if(!type)
				continue;
			if(type->type == this->SCENE3D_LIGHT)
			{
				Phantom::SceneLight* light = 0;
				if(type->p1==0)
					light = &m_scene3D->GetActiveEnv()->m_defaultLight;
				else
				{
					Phantom::GameID id;
					id.id = type->p1;
					light = m_scene3D->GetActiveEnv()->GetLightPtr(id);
				}
				if(proc&&light)
				{
					UndoPtr uptr;
					uptr.buff = AddUndoRedo(GCSceneEditor3D::SCENE3D_LIGHT, (ProcUndoRedo)proc);
					uptr.urMode = UndoRedoBuffer::URMode_Add;
					uptr.buff->m_id		=	type->p1;

					(*proc)(m_scene3D, light, nParameter, nParameter2, &uptr);
				}
				SetModifyed(true);
				if(bRename&&type->p1>0)
					m_treeView.SetItemText(it->first, Wutf8(light->m_name.t));
			}
		}
	}
	else{
		for(int i=0;i<m_selects.size();i++){
			if(m_selects[i].m_lightPtr&&!m_selects[i].m_bLightTarget){
					UndoPtr uptr;
					uptr.buff = AddUndoRedo(GCSceneEditor3D::SCENE3D_LIGHT, (ProcUndoRedo)proc);
					uptr.urMode = UndoRedoBuffer::URMode_Add;
					uptr.buff->m_id		=	m_selects[i].m_lightPtr->GetID();
				(*proc)(m_scene3D, m_selects[i].m_lightPtr, nParameter, nParameter2, &uptr);
				SetModifyed(true);
			}
		}
	}
}
VOID		GCSceneEditor3D::LoopAllRegion(ProSceneRegion proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
{
	std::map<HTREEITEM,TreeItemType*> selectTypes;
	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
	{
		HTREEITEM hItem		=	m_treeView.GetSelect(i);
		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
		if(type)
		{
			selectTypes[hItem]	=	type;
		}
	}
	this->BeginUndo();
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == this->SCENE3D_REGION)
		{
			if(proc)
			{
				UndoPtr uptr;
				uptr.buff = AddUndoRedo(GCSceneEditor3D::SCENE3D_REGION, (ProcUndoRedo)proc);
				uptr.urMode = UndoRedoBuffer::URMode_Add;
				uptr.buff->m_id		=	type->p1;
				(*proc)(m_scene3D, m_scene3D->GetRegionPtr(type->p1), nParameter, nParameter2, &uptr);
			}
			SetModifyed(true);
			if(bRename&&type->p1>=0)
				m_treeView.SetItemText(it->first, Wutf8(m_scene3D->GetRegionName(type->p1)));
		}
	}
}
//
//VOID		GCSceneEditor3D::LoopAllGrass(ProSceneGrass proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
//{
//	std::map<HTREEITEM,TreeItemType*> selectTypes;
//	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
//	{
//		HTREEITEM hItem		=	m_treeView.GetSelect(i);
//		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
//		if(type)
//		{
//			selectTypes[hItem]	=	type;
//		}
//	}
//	//for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
//	//{
//	//	TreeItemType* type	=	it->second;
//	//	if(!type)
//	//		continue;
//	//	if(type->type == this->SCENE3D_GRASS)
//	//	{
//	//		Phantom::PtrID id;
//	//		id.id	=	type->p1;
//	//		ISceneGrassTexture* grass =	m_scene3D->GetGrassDataPtr()->GetDataPtr(id);
//	//		if(proc)
//	//			(*proc)(m_scene3D, grass, nParameter, nParameter2);
//	//		SetModifyed(true);
//	//		if(bRename)
//	//			m_treeView.SetItemText(it->first, W(grass->GetName()));
//	//	}
//	//}
//}
//
//VOID		GCSceneEditor3D::LoopAllAnimations(ProSceneAnimation proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
//{
//	std::map<HTREEITEM,TreeItemType*> selectTypes;
//	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
//	{
//		HTREEITEM hItem		=	m_treeView.GetSelect(i);
//		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
//		if(type)
//		{
//			selectTypes[hItem]	=	type;
//		}
//	}
//	//for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
//	//{
//	//	TreeItemType* type	=	it->second;
//	//	if(!type)
//	//		continue;
//	//	if(type->type == this->SCENE3D_ANIMATION)
//	//	{
//	//		ISCA_Animation* ani	=	m_scene3D->GetAnimationManager().SearchDataPtr(type->p1);
//	//		if(proc)
//	//			(*proc)(m_scene3D, ani, nParameter, nParameter2);
//	//		SetModifyed(true);
//	//		if(bRename)
//	//			m_treeView.SetItemText(it->first, W(ani->GetName()));
//	//	}
//	//}
//}
//VOID		GCSceneEditor3D::LoopAllSCAs(ProSceneSCAs proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
//{
//	std::map<HTREEITEM,TreeItemType*> selectTypes;
//	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
//	{
//		HTREEITEM hItem		=	m_treeView.GetSelect(i);
//		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
//		if(type)
//		{
//			selectTypes[hItem]	=	type;
//		}
//	}
//	//for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
//	//{
//	//	TreeItemType* type	=	it->second;
//	//	if(!type)
//	//		continue;
//	//	if(type->type == this->SCENE3D_SCA)
//	//	{
//	//		ISCA_Animation* ani	=	m_scene3D->GetAnimationManager().SearchDataPtr(type->p1);
//	//		if(!ani)
//	//			continue;
//	//		ISCA_Base* base	=	ani->GetScaManager().SearchDataPtr(type->p2);
//	//		if(proc)
//	//			(*proc)(m_scene3D, ani, base, nParameter, nParameter2);
//	//		SetModifyed(true);
//	//		if(bRename)
//	//			m_treeView.SetItemText(it->first, W(base->GetName()));
//	//	}
//	//}
//}
//VOID		GCSceneEditor3D::LoopAllSCATracks(ProSceneSCATracks proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
//{
//	std::map<HTREEITEM,TreeItemType*> selectTypes;
//	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
//	{
//		HTREEITEM hItem		=	m_treeView.GetSelect(i);
//		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
//		if(type)
//		{
//			selectTypes[hItem]	=	type;
//		}
//	}
//	//for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
//	//{
//	//	TreeItemType* type	=	it->second;
//	//	if(!type)
//	//		continue;
//	//	if(type->type == this->SCENE3D_SCA_TRACK)
//	//	{
//	//		ISCA_Animation* ani	=	m_scene3D->GetAnimationManager().SearchDataPtr(type->p1);
//	//		if(!ani)
//	//			continue;
//	//		ISCA_Base* base		=	ani->GetScaManager().SearchDataPtr(type->p2);
//	//		if(!base)
//	//			continue;
//	//		ISCA_Track* track	=	base->GetTrackManager().SearchDataPtr(type->p3);
//	//		if(proc)
//	//			(*proc)(m_scene3D, ani, base, track, nParameter, nParameter2);
//	//		SetModifyed(true);
//	//		if(bRename)
//	//			m_treeView.SetItemText(it->first, W(track->GetName()));
//	//	}
//	//}
//}


VOID		GCSceneEditor3D::LoopAllCameras(ProSceneCamera proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
{
	std::map<HTREEITEM,TreeItemType*> selectTypes;
	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
	{
		HTREEITEM hItem		=	m_treeView.GetSelect(i);
		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
		if(type)
		{
			selectTypes[hItem]	=	type;
		}
	}
	this->BeginUndo();
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == this->SCENE3D_CAMERA)
		{
			Phantom::PtrID id;
			id.id	=	type->p1;
			Phantom::SceneCameraData* camera	=	m_scene3D->GetCameraDataPtr()->GetDataPtr(id);
			if(proc)
			{
				Phantom::CameraDataLocal d;
				Phantom::GetCameraPtr()->GetCameraConfig(d);
				camera->vEye	=	d.vEye;
				camera->vTarget	=	d.vTarget;
				camera->vRotate	=	d.vRotate;
				camera->fZNear	=	d.fZNear;
				camera->fZFar	=	d.fZFar;

				UndoPtr uptr;
				uptr.buff = AddUndoRedo(GCSceneEditor3D::SCENE3D_CAMERA, (ProcUndoRedo)proc);
				uptr.urMode = UndoRedoBuffer::URMode_Add;
				uptr.buff->m_id		=	type->p1;

				(*proc)(m_scene3D, camera, nParameter, nParameter2, &uptr);
				Phantom::GetCameraPtr()->SetCameraConfig(*camera);
			}
			SetModifyed(true);
			if(bRename)
				m_treeView.SetItemText(it->first, Wutf8(camera->name.t));
		}
	}
}
//
//VOID		GCSceneEditor3D::LoopAllWaters(ProSceneWater proc, LPARAM nParameter, BOOL bRename, LPARAM nParameter2)
//{
//	std::map<HTREEITEM,TreeItemType*> selectTypes;
//	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
//	{
//		HTREEITEM hItem		=	m_treeView.GetSelect(i);
//		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
//		if(type)
//		{
//			selectTypes[hItem]	=	type;
//		}
//	}
//	//for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
//	//{
//	//	TreeItemType* type	=	it->second;
//	//	if(!type)
//	//		continue;
//	//	if(type->type == this->SCENE3D_WATER)
//	//	{
//	//		Phantom::PtrID id;
//	//		id.id	=	type->p1;
//	//		SceneWaterData* water	=	m_scene3D->GetWaterDataPtr()->GetDataPtr(id);
//	//		if(proc)
//	//			(*proc)(m_scene3D, water, nParameter, nParameter2);
//	//		SetModifyed(true);
//	//		if(bRename)
//	//			m_treeView.SetItemText(it->first, W(water->name.t));
//	//	}
//	//}
//}

VOID	Scene3DSky_Name(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->name	=	(const char*)nParameter;
}
VOID	Scene3DSky_Texture(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, LPARAM nParameter, LPARAM nParameter2)
{
	//data->file	=	(const char*)nParameter;
	//scene->GetAtmospherePtr()->SetActiveSky(-1);
	//scene->GetAtmospherePtr()->SetActiveSky(data->id);
}
VOID	Scene3DSky_Visible(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->bEnable	=	nParameter;
}
VOID	Scene3DSky_Flare(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->bFlareEnable	=	nParameter;
}
VOID	Scene3DSky_Color(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->skyColor	=	nParameter;
}
VOID	Scene3DSky_AmbientColor(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->ambientColor	=	nParameter;
}
VOID	Scene3DSky_FlareFile(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, LPARAM nParameter, LPARAM nParameter2)
{
	//data->flareFile	=	(const char*)nParameter;
	//SetProjectPath();
	//scene->GetAtmospherePtr()->LoadFlare(data->flareFile);
}
VOID	Scene3DSky_FlareXAngle(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->fAngleX	=	*(float*)nParameter;
}
VOID	Scene3DSky_FlareYAngle(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->fAngleZ	=	*(float*)nParameter;
}
VOID	Scene3DSky_WindDirection(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->fWindDirection	=	*(float*)nParameter;
}
VOID	Scene3DSky_WindStrength(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->fWindPower		=	*(float*)nParameter;
}
//
//VOID	Scene3DFog_Name(Phantom::Scene3D* scene, Phantom::SceneFogData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->name	=	(const char*)nParameter;
//}
//VOID	Scene3DFog_Enable(Phantom::Scene3D* scene, Phantom::SceneFogData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->fogType	=	nParameter;
//}
//VOID	Scene3DFog_Color(Phantom::Scene3D* scene, Phantom::SceneFogData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->fogColor	=	nParameter;
//}
//VOID	Scene3DFog_Near(Phantom::Scene3D* scene, Phantom::SceneFogData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->fNear	=	*(float*)nParameter;
//}
//VOID	Scene3DFog_Far(Phantom::Scene3D* scene, Phantom::SceneFogData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->fFar	=	*(float*)nParameter;
//}
//
//VOID	Scene3DGrass_TextureFile(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetTextureFile((const char*)nParameter);
//}
//VOID	Scene3DGrass_AlphaBlend(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetAlphaBlend(nParameter);
//}
//VOID	Scene3DGrass_AlphaMask(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetAlphaMask(*(float*)nParameter);
//}
//VOID	Scene3DGrass_SizeW(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->SetGrassSize(Phantom::float2(*(float*)nParameter, data->GetGrassSize().y));
//}
//VOID	Scene3DGrass_SizeH(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->SetGrassSize(Phantom::float2(data->GetGrassSize().x, *(float*)nParameter));
//}
//VOID	Scene3DGrass_Wind(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->SetGrassWind(*(float*)nParameter);
//}
//VOID	Scene3DGrass_MaxVisible(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->SetVisibleLength(*(float*)nParameter);
//}
//VOID	Scene3DGrass_Color(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->SetColor(nParameter);
//}
//VOID	Scene3DGrass_FromColor(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->SetColorFrom(nParameter);
//}
//VOID	Scene3DGrass_Density(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->SetDensity(*(float*)nParameter);
//}
//VOID	Scene3DGrass_TextureLeft(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//PRect rc	=	data->GetTextureRect();
//	//float w		=	rc.right - rc.left;
//	//rc.left		=	nParameter;
//	//rc.right	=	rc.left + w;
//	//data->SetTextureRect(rc);
//}
//VOID	Scene3DGrass_TextureTop(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//PRect rc	=	data->GetTextureRect();
//	//float h		=	rc.bottom - rc.top;
//	//rc.top		=	nParameter;
//	//rc.bottom	=	rc.top + h;
//	//data->SetTextureRect(rc);
//}
//VOID	Scene3DGrass_TextureWidth(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//PRect rc	=	data->GetTextureRect();
//	//rc.right	=	rc.left + nParameter;
//	//data->SetTextureRect(rc);
//}
//VOID	Scene3DGrass_TextureHeight(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//PRect rc	=	data->GetTextureRect();
//	//rc.bottom	=	rc.top + nParameter;
//	//data->SetTextureRect(rc);
//}
//VOID	Scene3DGrass_CenterY(Phantom::Scene3D* scene, ISceneGrassTexture* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetTextureCenterY(nParameter);
//}

VOID	Scene3DCamera_Name(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, data->name.t, (const char*)nParameter);
	data->name = temp.t;
	GCSceneEditor3D* edview = static_cast<GCSceneEditor3D*>(GCViewBase::s_currView);
	HTREEITEM hItem = edview->FindTreeItem(edview->m_hViewItem, GCSceneEditor3D::SCENE3D_CAMERA, ptr->buff->m_id);
	if(hItem)
		edview->GetTreeView()->SetItemText(hItem, Wutf8(temp.t));
}
VOID	Scene3DCamera_Ortho(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsEnable(Phantom::CameraEnable_OrthoMode), nParameter);
	data->SetEnable(Phantom::CameraEnable_OrthoMode, temp);
}
VOID	Scene3DCamera_FPS(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsEnable(Phantom::CameraEnable_FPSMode), nParameter);
	data->SetEnable(Phantom::CameraEnable_FPSMode, temp);
}
VOID	Scene3DCamera_YRotEnable(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsEnable(Phantom::CameraEnable_YRotation), nParameter);
	data->SetEnable(Phantom::CameraEnable_YRotation, temp);
}
VOID	Scene3DCamera_XRotEnable(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsEnable(Phantom::CameraEnable_XRotation), nParameter);
	data->SetEnable(Phantom::CameraEnable_XRotation, temp);
}
VOID	Scene3DCamera_RotateX(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->vRotate.x, *(float*)nParameter);
	data->vRotate.x	=	temp;
}
VOID	Scene3DCamera_RotateZ(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->vRotate.y, *(float*)nParameter);
	data->vRotate.y	=	temp;
}
VOID	Scene3DCamera_TargetX(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->vTarget.x, *(float*)nParameter);
	data->vTarget.x	=	temp;
}
VOID	Scene3DCamera_TargetY(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->vTarget.y, *(float*)nParameter);
	data->vTarget.y	=	temp;
}
VOID	Scene3DCamera_TargetZ(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->vTarget.z, *(float*)nParameter);
	data->vTarget.z	=	temp;
}
VOID	Scene3DCamera_EyeX(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->vEye.x, *(float*)nParameter);
	data->vEye.x	=	temp;
}
VOID	Scene3DCamera_EyeY(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->vEye.y, *(float*)nParameter);
	data->vEye.y	=	temp;
}
VOID	Scene3DCamera_EyeZ(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->vEye.z, *(float*)nParameter);
	data->vEye.z	=	temp;
}
VOID	Scene3DCamera_Fov(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->fFov, *(float*)nParameter);
	data->fFov	=	temp;
}
VOID	Scene3DCamera_EnableMove(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsEnable(Phantom::CameraEnable_EnableMove), nParameter);
	data->SetEnable(Phantom::CameraEnable_EnableMove, temp);
}
VOID	Scene3DCamera_EnableDistance(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsEnable(Phantom::CameraEnable_EnableDistance), nParameter);
	data->SetEnable(Phantom::CameraEnable_EnableDistance, temp);
}
VOID	Scene3DCamera_MinDistance(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->fMinDistance, *(float*)nParameter);
	data->fMinDistance	=	temp;
}
VOID	Scene3DCamera_Distance(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::float3 vDir = data->vEye - data->vTarget;
	Phantom::float3 vEye;
	vDir.normalize();
	IF_ADD(){
		vDir *= *(float*)nParameter;
		vEye = data->vTarget + vDir;
	}
	ADD_UR(Phantom::float3, data->vEye, vEye);
	data->vEye = temp;
	Phantom::GetCameraPtr()->SetTarget(data->vTarget);
	Phantom::GetCameraPtr()->SetEye(data->vEye);
}
VOID	Scene3DCamera_MaxDistance(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->fMaxDistance, *(float*)nParameter);
	data->fMaxDistance	=	temp;
}
VOID	Scene3DCamera_MoveSpeed(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->fMoveSpeed, *(float*)nParameter);
	data->fMoveSpeed	=	temp;
}
VOID	Scene3DCamera_RotationSpeed(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->fRotationSpeedMask, *(float*)nParameter);
	data->fRotationSpeedMask	=	temp;
}
VOID	Scene3DCamera_Copy(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::GetCameraPtr()->GetCameraConfig(*data);
}
VOID	Scene3DCamera_Set(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::GetCameraPtr()->SetCameraConfig(*data);
	//scene->SetFov(data->fFov);
}

VOID	Scene3DCamera_CursorClipInRotMove(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsEnable(Phantom::CameraEnable_CursorClipInRotMove), nParameter);
	data->SetEnable(Phantom::CameraEnable_CursorClipInRotMove, temp);
}
VOID	Scene3DCamera_CenterCross(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsEnable(Phantom::CameraEnable_CenterCross), nParameter);
	data->SetEnable(Phantom::CameraEnable_CenterCross, temp);
}
//VOID	Scene3DCamera_ShiftMoveMul(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetEnable(Phantom::CameraEnable_ShiftMoveMul, nParameter);
//}
//VOID	Scene3DCamera_ShiftMoveMulValue(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->fShiftMoveMul = *(float*)nParameter;
//}
VOID	Scene3DCamera_MoveHeightIsZ(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsEnable(Phantom::CameraEnable_MoveHeightIsZ), nParameter);
	data->SetEnable(Phantom::CameraEnable_MoveHeightIsZ, temp);
}
VOID	Scene3DCamera_FixedZAxis(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsEnable(Phantom::CameraEnable_FixedZAxis), nParameter);
	data->SetEnable(Phantom::CameraEnable_FixedZAxis, temp);
}
VOID	Scene3DCamera_RotationMouseButton(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->rotButton, nParameter);
	data->rotButton	=	(Phantom::MouseButton)temp;
}
VOID	Scene3DCamera_MoveMouseButton(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->moveButton, nParameter);
	data->moveButton	=	(Phantom::MouseButton)temp;
}
//
//VOID	Scene3DCamera_MoveLeft(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->moveLeft	=	(KeyEnum)nParameter;
//}
//VOID	Scene3DCamera_MoveRight(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->moveRight	=	(KeyEnum)nParameter;
//}
//VOID	Scene3DCamera_MoveForward(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->moveForward	=	(KeyEnum)nParameter;
//}
//VOID	Scene3DCamera_MoveBack(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->moveBack	=	(KeyEnum)nParameter;
//}
//VOID	Scene3DCamera_MoveUp(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->moveUp	=	(KeyEnum)nParameter;
//}
//VOID	Scene3DCamera_MoveDown(Phantom::Scene3D* scene, Phantom::SceneCameraData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->moveDown	=	(KeyEnum)nParameter;
//}
//
//VOID	Scene3DWater_Name(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->name	=	(const char*)nParameter;
//}
//
//VOID	Scene3DWater_Visible(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->m_bWaterVisible	=	nParameter;
//}
//VOID	Scene3DWater_Texture(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->m_nWaterTextureID	=	nParameter;
//}
//VOID	Scene3DWater_Color(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	Phantom::color4 old(data->GetWaterColor());
//	Phantom::color4 c(nParameter, old.a);
//	data->SetWaterColor(c);
//}
//VOID	Scene3DWater_Alpha(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	Phantom::color4 old(data->GetWaterColor());
//	old.a	=	*(float*)nParameter;
//	data->SetWaterColor(old);
//}
//VOID	Scene3DWater_Rotation_1(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterRotation_1(*(float*)nParameter);
//}
//VOID	Scene3DWater_Speed_1(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterSpeed_1(*(float*)nParameter);
//}
//VOID	Scene3DWater_Rotation_2(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterRotation_2(*(float*)nParameter);
//}
//VOID	Scene3DWater_Speed_2(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterSpeed_2(*(float*)nParameter);
//}
//VOID	Scene3DWater_WaveX_1(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterWaveX(*(float*)nParameter);
//}
//VOID	Scene3DWater_WaveY_1(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterWaveY(*(float*)nParameter);
//}
//VOID	Scene3DWater_WaveX_2(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterWaveX_1(*(float*)nParameter);
//}
//VOID	Scene3DWater_WaveY_2(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterWaveY_1(*(float*)nParameter);
//}
//VOID	Scene3DWater_ReflectBump(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterReflectBump(*(float*)nParameter);
//}
//VOID	Scene3DWater_RefractBump(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterRefractBump(*(float*)nParameter);
//}
//VOID	Scene3DWater_ReflectWeight(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterReflectWeight(*(float*)nParameter);
//}
//VOID	Scene3DWater_RefractWeight(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterRefractWeight(*(float*)nParameter);
//}
//VOID	Scene3DWater_FadeBias(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterFadeBias(*(float*)nParameter);
//}
//VOID	Scene3DWater_FadeExponent(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterFadeExponent(*(float*)nParameter);
//}
//VOID	Scene3DWater_Height(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->SetWaterHeight(*(float*)nParameter);
//}
//VOID	Scene3DWater_HeightAlpha(Phantom::Scene3D* scene, SceneWaterData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	data->fWaterBlendAlpha	=	*(float*)nParameter;
//	//BOOL bSet	=	false;
//	//for(int i=0;i<scene->GetRenderCount();i++)
//	//{
//	//	Phantom::SceneBox* r	=	scene->GetRenderPtr(i);
//	//	if(r && r->GetWaterData() == data)
//	//	{
//	//		bSet	=	true;
//	//		r->SetModifyed(true);
//	//		scene->RecalcWaterHeightAlpha(r->GetRegionIndexX(), r->GetRegionIndexY());
//	//	}
//	//}
//	//if(bSet)
//	//	scene->RefreshBlendDatas();
//}


//
//VOID	Scene3DAnim_Name(Phantom::Scene3D* scene, ISCA_Animation* ani, LPARAM nParameter, LPARAM nParameter2)
//{
//	ani->SetName((const char*)nParameter);
//}
//VOID	Scene3DAnim_TimeLength(Phantom::Scene3D* scene, ISCA_Animation* ani, LPARAM nParameter, LPARAM nParameter2)
//{
//	ani->SetTrackTimeLength(*(float*)nParameter);
//}
//VOID	Scene3DAnim_TimeBegin(Phantom::Scene3D* scene, ISCA_Animation* ani, LPARAM nParameter, LPARAM nParameter2)
//{
//	ani->SetBeginTime(*(float*)nParameter);
//}
//VOID	Scene3DAnim_Enable(Phantom::Scene3D* scene, ISCA_Animation* ani, LPARAM nParameter, LPARAM nParameter2)
//{
//	ani->SetEnabled(nParameter);
//}
//
//VOID	Scene3DSCAs_Name(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, LPARAM nParameter, LPARAM nParameter2)
//{
//	base->SetName((const char*)nParameter);
//}
//VOID	Scene3DSCATracks_UnitSelect(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, ISCA_Track* t, LPARAM nParameter, LPARAM nParameter2)
//{
//	//CDynamicArray<EnumRequestData> rets;
//	//base->EnumUnit(rets);
//	//Phantom::PtrID	id;
//	//for(int i=0;i<rets.size();i++)
//	//{
//	//	char buf[128];
//	//	sprintf(buf, "%s[%d]", rets[i].name, rets[i].id.id);
//	//	if(stricmp(buf, (const char*)nParameter) == 0)
//	//	{
//	//		id	=	rets[i].id;
//	//		break;
//	//	}
//	//}
//	//t->SetUnitID(id);
//}
//VOID	Scene3DSCAs_Enable(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, LPARAM nParameter, LPARAM nParameter2)
//{
//	base->SetEnabled(nParameter);
//}
//VOID	Scene3DSCATracks_Name(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, ISCA_Track* t, LPARAM nParameter, LPARAM nParameter2)
//{
//	t->SetName((const char*)nParameter);
//}
//VOID	Scene3DSCATracks_Enable(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, ISCA_Track* t, LPARAM nParameter, LPARAM nParameter2)
//{
//	t->SetEnabled(nParameter);
//}
//VOID	Scene3DSCATracks_FrameTimeLength(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, ISCA_Track* t, LPARAM nParameter, LPARAM nParameter2)
//{
//	t->SetFrameTimeLength(*(float*)nParameter);
//}
//VOID	Scene3DSCATracks_ScriptEnable(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, ISCA_Track* t, LPARAM nParameter, LPARAM nParameter2)
//{
//	t->SetScriptEnable(nParameter);
//}
//VOID	Scene3DSCATracks_BlendTime(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, ISCA_Track* t, LPARAM nParameter, LPARAM nParameter2)
//{
//	t->SetBlendTime(*(float*)nParameter);
//}
//VOID	Scene3DSCATracks_PosEnable(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, ISCA_Track* t, LPARAM nParameter, LPARAM nParameter2)
//{
//	if(t->GetSccPosition())
//		t->GetSccPosition()->SetEnabled(nParameter);
//}
//VOID	Scene3DSCATracks_PosLookatTarget(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, ISCA_Track* t, LPARAM nParameter, LPARAM nParameter2)
//{
//	if(t->GetSccPosition())
//		t->GetSccPosition()->SetLookatTarget(nParameter);
//}
//VOID	Scene3DSCATracks_PosMoveSpeed(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, ISCA_Track* t, LPARAM nParameter, LPARAM nParameter2)
//{
//	if(t->GetSccPosition())
//		t->GetSccPosition()->SetMoveSpeed(*(float*)nParameter);
//}
//VOID	Scene3DSCATracks_ActionID(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, ISCA_Track* t, LPARAM nParameter, LPARAM nParameter2)
//{
//	//CDynamicArray<EnumRequestData> rets;
//	//base->EnumActions(rets);
//	//Phantom::PtrID	id;
//	//for(int i=0;i<rets.size();i++)
//	//{
//	//	char buf[128];
//	//	sprintf(buf, "%s[%d]", rets[i].name, rets[i].id.id);
//	//	if(stricmp(buf, (const char*)nParameter) == 0)
//	//	{
//	//		id	=	rets[i].id;
//	//		break;
//	//	}
//	//}
//	//if(t->GetSccAction())
//	//	t->GetSccAction()->SetActionID(id);
//}
//VOID	Scene3DSCATracks_ActionEnable(Phantom::Scene3D* scene, ISCA_Animation* ani, ISCA_Base* base, ISCA_Track* t, LPARAM nParameter, LPARAM nParameter2)
//{
//	if(t->GetSccAction())
//		t->GetSccAction()->SetEnabled(nParameter);
//}

VOID	SceneObject_SelectTable(Phantom::Scene3D* scene, Phantom::SceneObjectFile* data, LPARAM nParameter, LPARAM nParameter2)
{
	//data->tableName	=	(const char*)nParameter;
}
VOID	SceneObject_SelectTableLine(Phantom::Scene3D* scene, Phantom::SceneObjectFile* data, LPARAM nParameter, LPARAM nParameter2)
{
	//data->lineID	=	nParameter;
}
VOID	SceneObject_FileOpen(Phantom::Scene3D* scene, Phantom::SceneObjectFile* data, LPARAM nParameter, LPARAM nParameter2)
{
	AfxGetApp()->OpenDocumentFile(W(data->name.t).buf);
}
//
//VOID	Scene3DFlare_Texture(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, INT nFlareIndex, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->flares[nFlareIndex].textureFile	=	(const char*)nParameter;
//	//scene->GetAtmospherePtr()->ReloadFlare();
//}
//VOID	Scene3DFlare_Position(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, INT nFlareIndex, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->flares[nFlareIndex].fPosition	=	*(float*)nParameter;
//	//scene->GetAtmospherePtr()->ReloadFlare();
//}
//VOID	Scene3DFlare_Radius(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, INT nFlareIndex, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->flares[nFlareIndex].fRadius	=	*(float*)nParameter;
//	//scene->GetAtmospherePtr()->ReloadFlare();
//}
//VOID	Scene3DFlare_Alpha(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, INT nFlareIndex, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->flares[nFlareIndex].color.a	=	*(float*)nParameter;
//	//scene->GetAtmospherePtr()->ReloadFlare();
//}
//VOID	Scene3DFlare_Color(Phantom::Scene3D* scene, Phantom::SceneSkyData* data, INT nFlareIndex, LPARAM nParameter, LPARAM nParameter2)
//{
//	//Phantom::color4 c(nParameter);
//	//c.a	=	data->flares[nFlareIndex].color.a;
//	//data->flares[nFlareIndex].color	=	c;
//	//scene->GetAtmospherePtr()->ReloadFlare();
//}
//
//VOID	Scene3DShadow_Name(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->name	=	(const char*)nParameter;
//}
//VOID	Scene3DShadow_Enable(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->bEnable	=	nParameter;
//	//if(scene->GetActiveShadow().id == data->id)
//	//	scene->SetActiveShadow(data->id);
//}
//VOID	Scene3DShadow_MinVisible(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->fMinVisible	=	*(float*)nParameter;
//}
//VOID	Scene3DShadow_TextureSize(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->textureSize	=	nParameter;
//	//if(scene->GetActiveShadow().id == data->id)
//	//	scene->SetActiveShadow(data->id);
//}
//VOID	Scene3DShadow_SingleMap(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->bSingleMap	=	nParameter;
//	//if(scene->GetActiveShadow().id == data->id)
//	//	scene->SetActiveShadow(data->id);
//}
//VOID	Scene3DShadow_Epsilon(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->fEpsilon	=	*(float*)nParameter;
//}
//VOID	Scene3DShadow_Density(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->fDensity	=	*(float*)nParameter;
//}
//VOID	Scene3DShadow_PCFLevel(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->pcfLevel	=	(SHADOW_PCF)nParameter;
//}
//VOID	Scene3DShadow_SoftLevel(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->blurLevel	=	(SHADOW_BLUR)nParameter;
//}
//VOID	Scene3DShadow_SoftLevel1(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->fProportion[0]	=	*(float*)nParameter;
//}
//VOID	Scene3DShadow_SoftLevel2(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->fProportion[1]	=	*(float*)nParameter;
//}
//VOID	Scene3DShadow_SoftLevel3(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->fProportion[2]	=	*(float*)nParameter;
//}
//VOID	Scene3DShadow_TerrainShadowE(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//if(nParameter)
//	//	data->flags	|=	SHADOW_RENDER_TERRAINS;
//	//else if(data->flags & SHADOW_RENDER_TERRAINS)
//	//	data->flags	^=	SHADOW_RENDER_TERRAINS;
//}
//VOID	Scene3DShadow_TerrainAffectBy(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//if(nParameter)
//	//	data->flags	|=	SHADOW_RENDER_TERRAIN_A_SHADOW;
//	//else if(data->flags & SHADOW_RENDER_TERRAIN_A_SHADOW)
//	//	data->flags	^=	SHADOW_RENDER_TERRAIN_A_SHADOW;
//}
//VOID	Scene3DShadow_WaterAffectBy(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//if(nParameter)
//	//	data->flags	|=	SHADOW_RENDER_WATER_A_SHADOW;
//	//else if(data->flags & SHADOW_RENDER_WATER_A_SHADOW)
//	//	data->flags	^=	SHADOW_RENDER_WATER_A_SHADOW;
//}
//VOID	Scene3DShadow_ObjectShadow(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//if(nParameter)
//	//	data->flags	|=	SHADOW_RENDER_OBJECTS;
//	//else if(data->flags & SHADOW_RENDER_OBJECTS)
//	//	data->flags	^=	SHADOW_RENDER_OBJECTS;
//}
//VOID	Scene3DShadow_ObjectAffectBy(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//if(nParameter)
//	//	data->flags	|=	SHADOW_RENDER_OBJECT_A_SHADOW;
//	//else if(data->flags & SHADOW_RENDER_OBJECT_A_SHADOW)
//	//	data->flags	^=	SHADOW_RENDER_OBJECT_A_SHADOW;
//}
//VOID	Scene3DShadow_GrassShadow(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//if(nParameter)
//	//	data->flags	|=	SHADOW_RENDER_GRASS;
//	//else if(data->flags & SHADOW_RENDER_GRASS)
//	//	data->flags	^=	SHADOW_RENDER_GRASS;
//}
//VOID	Scene3DShadow_GrassAffectBy(Phantom::Scene3D* scene, SceneShadowData* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//if(nParameter)
//	//	data->flags	|=	SHADOW_RENDER_GRASS_A_SHADOW;
//	//else if(data->flags & SHADOW_RENDER_GRASS_A_SHADOW)
//	//	data->flags	^=	SHADOW_RENDER_GRASS_A_SHADOW;
//}
//
//VOID	Scene3DAdvanced_Name(Phantom::Scene3D* scene, IAdvancedEffect* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->SetName((const char*)nParameter);
//}
//VOID	Scene3DAdvanced_Enable(Phantom::Scene3D* scene, IAdvancedEffect* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->SetActive(nParameter);
//}
//VOID	Scene3DAdvanced_Target(Phantom::Scene3D* scene, IAdvancedEffect* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//data->SetTargetMode(nParameter);
//}
//VOID	Scene3DAdvanced_Value(Phantom::Scene3D* scene, IAdvancedEffect* data, LPARAM nParameter, LPARAM nParameter2)
//{
//	//CFloatAnimation* ani	=	data->GetKeyPtr(nParameter);
//	//if(ani)
//	//	ani->SetNormalValue(*(float*)nParameter2);
//}
VOID	Scene3DEnv_Name(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, data->m_name.t, (const char*)nParameter);
	data->m_name = temp.t;
	GCSceneEditor3D* edview = static_cast<GCSceneEditor3D*>(GCViewBase::s_currView);
	HTREEITEM hItem = edview->FindTreeItem(edview->m_hViewItem, GCSceneEditor3D::SCENE3D_ENV, data->GetID());
	if(hItem)
		edview->GetTreeView()->SetItemText(hItem, Wutf8(temp.t));
}
VOID	Scene3DEnv_FogColor(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(unsigned int, data->m_fogColor, nParameter);
	data->m_fogColor = temp;
	if(data->IsActive())data->CommitFog();
}

VOID	Scene3DEnv_AmbientColor(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(unsigned int, data->m_ambientColor, nParameter);
	data->m_ambientColor = temp;
	if(data->IsActive())
	{
		Phantom::color4 c = data->m_ambientColor;
		Phantom::g_manager.m_ambientColor.setxyz(c.r,c.g,c.b);
	}
}
VOID	Scene3DEnv_FogMode(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_fogType, nParameter);
	data->m_fogType = temp;
	if(data->IsActive())data->CommitFog();
}
VOID	Scene3DEnv_FogEnable(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_fogEnable, nParameter);
	data->m_fogEnable = temp;
	if(data->IsActive())data->CommitFog();
}
VOID	Scene3DEnv_FogNear(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->m_fNear,*(float*)nParameter);
	data->m_fNear = temp;
	if(data->IsActive())data->CommitFog();
}
VOID	Scene3DEnv_FogFar(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->m_fFar,*(float*)nParameter);
	data->m_fFar = temp;
	if(data->IsActive())data->CommitFog();
}

VOID	Scene3DEnv_BrightnessEnable(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_bBrightness, nParameter);
	data->m_bBrightness = temp;
	if(data->IsActive())data->CommitBrightness();
}
VOID	Scene3DEnv_ContrastEnable(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_bContrast, nParameter);
	data->m_bContrast = temp;
	if(data->IsActive())data->CommitContrast();
}
VOID	Scene3DEnv_Brightness(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->m_fBrightness,*(float*)nParameter);
	data->m_fBrightness = temp;
	if(data->IsActive())data->CommitBrightness();
}
VOID	Scene3DEnv_Contrast(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->m_fContrast,*(float*)nParameter);
	data->m_fContrast = temp;
	if(data->IsActive())data->CommitContrast();
}
VOID	Scene3DEnv_ShadowEnable(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->IsShadowEnable(Phantom::ShadowEnable_UseShadowMap), nParameter);
	data->SetShadowEnable(Phantom::ShadowEnable_UseShadowMap, temp);
	if(data==scene->GetActiveEnv())data->CommitShadowMap();
}
VOID	Scene3DEnv_ShadowMapSize(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_shadowMapSize, nParameter);
	data->m_shadowMapSize = temp;
	if(data==scene->GetActiveEnv())data->CommitShadowMap();
}
VOID	Scene3DEnv_ShadowBias(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->m_shadowBias, *(float*)nParameter);
	data->m_shadowBias = temp;
	if(data==scene->GetActiveEnv())data->CommitShadowMap();
}
VOID	Scene3DEnv_ShadowViewLength(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->m_shadowViewSize, *(float*)nParameter);
	data->m_shadowViewSize = temp;
	if(data==scene->GetActiveEnv())data->CommitShadowMap();
}
VOID	Scene3DEnv_ShadowPCF(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_shadowPCF, nParameter);
	data->m_shadowPCF = temp;
	if(data==scene->GetActiveEnv())data->CommitShadowMap();
}
VOID	Scene3DEnv_ShadowDensity(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->m_shadowDensity, *(float*)nParameter);
	data->m_shadowDensity = temp;
	if(data==scene->GetActiveEnv())data->CommitShadowMap();
}
VOID	Scene3DEnv_ShadowTerrainToMap(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsShadowEnable(Phantom::ShadowEnable_TerrainToMap), nParameter);
	data->SetShadowEnable(Phantom::ShadowEnable_TerrainToMap, temp);
	if(data==scene->GetActiveEnv())data->CommitShadowMap();
}
VOID	Scene3DEnv_ShadowObjectToMap(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsShadowEnable(Phantom::ShadowEnable_MeshToMap), nParameter);
	data->SetShadowEnable(Phantom::ShadowEnable_MeshToMap, temp);
	if(data==scene->GetActiveEnv())data->CommitShadowMap();
}
VOID	Scene3DEnv_ShadowTerrainWithMap(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsShadowEnable(Phantom::ShadowEnable_TerrainWithMap), nParameter);
	data->SetShadowEnable(Phantom::ShadowEnable_TerrainWithMap, temp);
	if(data==scene->GetActiveEnv())data->CommitShadowMap();
}
VOID	Scene3DEnv_ShadowObjectWithMap(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsShadowEnable(Phantom::ShadowEnable_MeshWithMap), nParameter);
	data->SetShadowEnable(Phantom::ShadowEnable_MeshWithMap, temp);
	if(data==scene->GetActiveEnv())data->CommitShadowMap();
}
VOID	Scene3DEnv_ShadowObjectCenter(Phantom::Scene3D* scene, Phantom::SceneEnv* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_shadowCenterObj.id, nParameter);
	data->m_shadowCenterObj.id = temp;
	data->m_shadowMode = Phantom::SceneEnv::ShadowMode_Object;
}

VOID	Scene3DRegion_Name(Phantom::Scene3D* scene, Phantom::SceneRegionData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, data->name.t, (const char*)nParameter);
	data->name = temp;
	GCSceneEditor3D* edview = static_cast<GCSceneEditor3D*>(GCViewBase::s_currView);
	HTREEITEM hItem = edview->FindTreeItem(edview->m_hViewItem, GCSceneEditor3D::SCENE3D_REGION, ptr->buff->m_id);
	if(hItem)
		edview->GetTreeView()->SetItemText(hItem, Wutf8(temp.t));
}
VOID	Scene3DRegion_NameEnable(Phantom::Scene3D* scene, Phantom::SceneRegionData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->bCustomName, nParameter);
	data->bCustomName = temp;
}
VOID	Scene3DLight_Name(Phantom::Scene3D* scene, Phantom::SceneLight* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, data->m_name.t, (const char*)nParameter);
	data->m_name = temp;
	GCSceneEditor3D* edview = static_cast<GCSceneEditor3D*>(GCViewBase::s_currView);
	HTREEITEM hItem = edview->FindTreeItem(edview->m_hViewItem, GCSceneEditor3D::SCENE3D_LIGHT, ptr->buff->m_id);
	if(hItem)
		edview->GetTreeView()->SetItemText(hItem, Wutf8(temp.t));
}
VOID	Scene3DLight_Enable(Phantom::Scene3D* scene, Phantom::SceneLight* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_bEnabled, nParameter);
	data->m_bEnabled = temp;
	scene->m_lightChanged++;
}
VOID	Scene3DLight_Near(Phantom::Scene3D* scene, Phantom::SceneLight* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->GetNear(), *(float*)nParameter);
	data->SetNear(temp);
	scene->m_lightChanged++;
}
VOID	Scene3DLight_Far(Phantom::Scene3D* scene, Phantom::SceneLight* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->GetFar(), *(float*)nParameter);
	data->SetFar(temp);
	scene->m_lightChanged++;
}
VOID	Scene3DLight_AngleS(Phantom::Scene3D* scene, Phantom::SceneLight* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->GetAngleSmall(), *(float*)nParameter);
	data->SetAngleSmall(temp);
	scene->m_lightChanged++;
}
VOID	Scene3DLight_AngleB(Phantom::Scene3D* scene, Phantom::SceneLight* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->GetAngleBig(), *(float*)nParameter);
	data->SetAngleBig(temp);
	scene->m_lightChanged++;
}
VOID	Scene3DLight_RotZ(Phantom::Scene3D* scene, Phantom::SceneLight* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->m_angleZ, *(float*)nParameter);
	data->m_angleZ = Radians(temp);
	data->recalcAngle();
	scene->m_lightChanged++;
}
VOID	Scene3DLight_RotY(Phantom::Scene3D* scene, Phantom::SceneLight* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->m_angleY, *(float*)nParameter);
	data->m_angleY = Radians(temp);
	data->recalcAngle();
	scene->m_lightChanged++;
}
VOID	Scene3DLight_Color(Phantom::Scene3D* scene, Phantom::SceneLight* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::color4 c(nParameter);
	Phantom::float3 vnew(c.r,c.g,c.b);
	ADD_UR(Phantom::float3, data->m_lightColor, vnew);
	data->m_lightColor = temp;//.setxyz(c.r,c.g,c.b);
	scene->m_lightChanged++;
}
VOID	Scene3DLight_Type(Phantom::Scene3D* scene, Phantom::SceneLight* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_lightType, nParameter);
	data->m_lightType = temp;
	scene->m_lightChanged++;
}
VOID	Scene3DRegion_RegionID(Phantom::Scene3D* scene, Phantom::SceneRegionData* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->regionid, nParameter);
	data->regionid = temp;
	if(Phantom::GetGameMgr()->m_tblCity){
		Phantom::ConfigLine* line = Phantom::GetGameMgr()->m_tblCity->GetLineFromID(data->regionid);
		if(line){
			data->name = line->GetLineName();
		}
	}
}

VOID	Proc_m_unitPositionX(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::float3 pos	=	se.GetPosition();
	IF_ADD(){
		pos.x		=	*(float*)nParameter;
	}
	ADD_UR(Phantom::float3, se.GetPosition(), pos);
	se.SetPosition(temp);
}
VOID	Proc_m_unitPositionY(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::float3 pos	=	se.GetPosition();
	IF_ADD(){
		pos.y		=	*(float*)nParameter;
	}
	ADD_UR(Phantom::float3, se.GetPosition(), pos);
	se.SetPosition(temp);
}
VOID	Proc_m_unitEnable(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, se.IsEnabled(), nParameter);
	se.SetEnabled(temp);
}
VOID	Proc_m_unitVisible(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, se.IsVisible(), nParameter);
	se.SetVisible(temp);
}
VOID	Proc_m_unitRange(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	if(!se.GetObjectPtr())
		return;
	ADD_UR(float, se.GetObjectPtr()->m_fRange, *(float*)nParameter);
	se.GetObjectPtr()->m_fRange = temp;
}
VOID	Proc_m_unitAtkRange(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	if(!se.GetObjectPtr())
		return;
	ADD_UR(float, se.GetObjectPtr()->m_fAtkRange, *(float*)nParameter);
	se.GetObjectPtr()->m_fAtkRange = temp;
}
VOID	Proc_m_unitName(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, se.GetName(), Autf8((const wchar_t*)nParameter).buf);
	se.SetName(temp, se.IsCustomName());
}
VOID	Proc_m_unitNameEnable(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, se.IsVisible(), nParameter);
	se.SetName(se.GetName(), temp);
}
VOID	Proc_m_unitID(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	if(!se.GetObjectPtr())return;
	ADD_UR(int, se.GetObjectPtr()->m_nContentID, nParameter);
	se.GetObjectPtr()->m_nContentID = nParameter;
}
VOID	Proc_m_unitEvents(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	if(!se.GetEventPtr())
		return;
	ADD_UR(int, se.GetEventPtr()->m_eventid, nParameter);
	se.GetEventPtr()->m_eventid = temp;
}
VOID	Proc_m_unitPositionZ(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::float3 pos	=	se.GetPosition();
	IF_ADD(){
		pos.z		=	*(float*)nParameter;
	}
	ADD_UR(Phantom::float3, se.GetPosition(), pos);
	se.SetPosition(temp);
}
VOID	Proc_m_unitScaleFull(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, se.GetSize(), *(float*)nParameter);
	se.SetSize(temp);
}
VOID	Proc_m_unitDiffuseIndex(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	if(!se.GetObjectPtr())return;
	ADD_UR(int, se.GetObjectPtr()->GetDiffuseIndex(), nParameter);
	se.GetObjectPtr()->ChangeDiffuse(temp);
}
VOID	Proc_m_unitAutoHeight(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	if(!se.GetObjectPtr())return;
	ADD_UR(int, se.GetObjectPtr()->m_bAutoHeight, nParameter);
	se.GetObjectPtr()->m_bAutoHeight = temp;
}
VOID	Proc_m_unitResetMatrix(Phantom::Scene3D* scene, SelectEditor& se, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//if(!se.GetObjectPtr())return;
	//Phantom::SavePosRot vold,vnew;
	//IF_ADD(){
	//	vold.rot = se.GetObjectPtr()->m_fRotationZ;
	//	vold.mat = *se.GetObjectPtr()->GetWorldPtr();
	//	vold.visible = se.GetObjectPtr()->GetVisible();
	//	vold.id = 0;
	//	se.GetObjectPtr()->ResetEnv(0);
	//	vnew.rot = se.GetObjectPtr()->m_fRotationZ;
	//	vnew.mat = *se.GetObjectPtr()->GetWorldPtr();
	//	vnew.visible = se.GetObjectPtr()->GetVisible();
	//	vnew.id = 0;
	//	if(scene->GetActiveEnv())
	//	{
	//		if(scene->GetActiveEnv()->RemoveObject(m_selects[i].GetObjectPtr()->GetID()))
	//			vold.id = 1;
	//		ptr->buff->m_id4 = scene->GetActiveEnv()->GetID();
	//	}
	//	ADD_UR(Phantom::SavePosRot, vold, vnew);
	//}
	//else{
	//	ptr->buff >> vold >> vnew;
	//	if(ptr->urMode==UndoRedoBuffer::URMode_Undo){
	//		Phantom::SceneEnv* env = scene->GetEnvByID(ptr->buff->m_id4);
	//		if(env){
	//			if(vold.id)
	//		}
	//		if(scene->GetActiveEnv())
	//	{
	//		if(scene->GetActiveEnv()->RemoveObject(m_selects[i].GetObjectPtr()->GetID()))
	//			vold.id = 1;
	//		ptr->buff->m_id4 = scene->GetActiveEnv()->GetID();
	//	}
	//	ADD_UR(Phantom::SavePosRot, vold, vnew);
	//	}
	//	else if(ptr->urMode==UndoRedoBuffer::URMode_Redo){
	//	}
	//}
}

void		GCSceneEditor3D::RefreshShadowEnable(BOOL b)
{
	m_envShadowMapSize->Enable(b);
	m_envShadowBias->Enable(b);
	m_envShadowViewLength->Enable(b);
	m_envShadowPCF->Enable(b);
	m_envShadowDensity->Enable(b);
	m_envTerrainToMap->Enable(b);
	m_envObjectToMap->Enable(b);
	m_envTerrainWithMap->Enable(b);
	m_envObjectWithMap->Enable(b);
	m_envCenterObj->Enable(b);
}
void		GCSceneEditor3D::OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp)
{
	__super::OnPropertyChanged(wnd, pProp);
	if(wnd == &m_sceneProperties)
	{
		/*if(pProp == m_sceneAmbientColor)
		{
			Phantom::color4 c(GetPropColor(m_sceneAmbientColor), 1.0f);
			m_scene3D->SetAmbientColor(c);
		}
		else if(pProp == m_sceneBrightness)
		{
			m_scene3D->SetSceneHighlight(GetPropFloat(m_sceneBrightness));
		}
		else */if(pProp == m_sceneSpecularExponent)
		{
			m_scene3D->m_specularExponent = GetPropFloat(m_sceneSpecularExponent);
		}
		else if(pProp == m_sceneSpecularPower)
		{
			m_scene3D->m_specularPower = GetPropFloat(m_sceneSpecularPower);
		}
		else if(pProp == m_sceneColor)
		{
			Phantom::color4 c	=	m_scene3D->m_sceneDiffuse;
			c.from(GetPropColor(m_sceneColor), c.a);
			m_scene3D->m_sceneDiffuse = c;
		}
		else if(pProp == m_sceneMaxVisible)
		{
			m_scene3D->m_fMaxViewDistance = GetPropFloat(m_sceneMaxVisible);
		}
		else if(pProp == m_sceneClipEnable)
		{
			m_scene3D->m_bClipCamera = GetPropBool(m_sceneClipEnable);
			m_scene3D->SetActiveCamera(this->m_currentCamera.name.t);
		}
		else if(pProp == m_sceneClipSize)
		{
			m_scene3D->m_fClipCameraSize = GetPropFloat(m_sceneClipSize);
			m_scene3D->SetActiveCamera(this->m_currentCamera.name.t);
		}
		//else if(pProp == m_sceneHeightAlign)
		//{
		//	//m_scene3D->SetHeightAlignValue(GetPropFloat(m_sceneHeightAlign));
		//	//for(int x=0;x<m_scene3D->GetSceneRegionCount();x++)
		//	//{
		//	//	Phantom::SceneBox* pRegion = m_scene3D->GetSceneRegionPtr(x);
		//	//	pRegion->SetModifyed(true);
		//	//	SetModifyed();
		//	//	m_scene3D->RebuildRegionFaces(pRegion->GetRegionIndexX(), pRegion->GetRegionIndexY());
		//	//}
		//}
		//else if(pProp == m_sceneLODDetailMax)
		//{
		//	//m_scene3D->SetTerrainLODDetail(GetPropFloat(m_sceneLODDetailMax));
		//}
		//else if(pProp == m_sceneLODDetailMin)
		//{
		//	//m_scene3D->SetLODMinLevelDetail(GetPropFloat(m_sceneLODDetailMin));
		//}
		//else if(pProp == m_sceneLODBuildGrids)
		//{
		//	//m_scene3D->SetLODBuildWidth(GetPropInt(m_sceneLODBuildGrids));
		//}
		//else if(pProp == m_sceneLODEnable)
		//{
		//	//m_scene3D->SetLODEnable(GetPropBool(m_sceneLODEnable));
		//}
		//else if(pProp == m_sceneUnitNameVisible)
		//{
		//	//m_scene3D->SetUnitNameVisible(GetPropBool(m_sceneUnitNameVisible));
		//}
		//else if(pProp == m_sceneUnitBloodVisible)
		//{
		//	//m_scene3D->SetUnitBloodVisible(GetPropBool(m_sceneUnitBloodVisible));
		//}
		//else if(pProp == m_sceneUnitNameSize)
		//{
		//	//m_scene3D->SetUnitNameSize(GetPropFloat(m_sceneUnitNameSize));
		//}
		//else if(pProp == m_sceneUnitBloodSize)
		//{
		//	//m_scene3D->SetUnitBloodSize(GetPropFloat(m_sceneUnitBloodSize));
		//}
		//else if(pProp == m_sceneUnitNameVisibleLength)
		//{
		//	//m_scene3D->SetUnitTopVisibleLength(GetPropFloat(m_sceneUnitNameVisibleLength));
		//}
		//else if(pProp == m_sceneUnitBloodTexture)
		//{
		//	//std::wstring str;
		//	//GetPropFile(m_sceneUnitBloodTexture, str);
		//	//m_scene3D->SetBloodTextureFile( BloodTextureInfo_Blood, A(str.c_str()) );
		//}
		//else if(pProp == m_sceneTextureMapBlur)
		//{
		//	this->SetModifyed();
		//	//m_scene3D->SetColorBlur(GetPropInt(m_sceneTextureMapBlur));
		//}
		//else if(pProp == m_sceneHeightMapBlur)
		//{
		//	this->SetModifyed();
		//	//m_scene3D->SetHeightBlur(GetPropInt(m_sceneHeightMapBlur));
		//}
		//else if(pProp == m_sceneHeightMapHeight)
		//{
		//	this->SetModifyed();
		//	//m_scene3D->SetHeightMapHeight(GetPropFloat(m_sceneHeightMapHeight));
		//}
		//else if(pProp == m_sceneTHBuildVisibleAll)
		//{
		//	DefineAuth_3();
		//	if(!CheckAuth_3(0))
		//		return;
		//	this->SetModifyed();
		//	//m_scene3D->RebuildOnlyNoInitRegion(false);
		//}
		//else if(pProp == m_sceneTHBuildAllScene)
		//{
		//	DefineAuth_3();
		//	if(!CheckAuth_3(0))
		//		return;
		//	this->SetModifyed();
		//	//m_scene3D->RebuildOnlyNoInitRegion(true);
		//}
		//else if(pProp == m_sceneLogicSystem)
		//{
		//	//std::wstring str;
		//	//GetPropFile(m_sceneLogicSystem, str);
		//	//m_scene3D->SetLogicSystemFile( A(str.c_str()) );
		//}
		//else if(pProp == m_sceneShadowAlpha)
		//{
		//	//m_scene3D->SetMeshShadowAlpha(GetPropFloat(m_sceneShadowAlpha));
		//}
		//else if(pProp == m_geometryLODDetail)
		//{
		//	//m_scene3D->SetObjectLODDetail(GetPropFloat(m_geometryLODDetail));
		//}
		//else if(pProp == m_geometryLODMaxVisible)
		//{
		//	//m_scene3D->SetObjectLODMinVisible(GetPropFloat(m_geometryLODMaxVisible));
		//}
		//else if(pProp == m_textureMinFilter)
		//	m_scene3D->SetMinFilter((Enum::TextureFilter)GetPropOption(m_textureMinFilter, g_typeFilter));
		//else if(pProp == m_textureMagFilter)
		//	m_scene3D->SetMagFilter((Enum::TextureFilter)GetPropOption(m_textureMagFilter, g_typeFilter));
		//else if(pProp == m_textureMipFilter)
		//	m_scene3D->SetMipFilter((Enum::TextureFilter)GetPropOption(m_textureMipFilter, g_typeFilter));
		else
			return;
		SetModifyed();
	}
	else if(wnd == &m_envProperties){
		if(pProp == m_envName){
			std::wstring str;
			GetPropText(m_envName, str);
			this->LoopAllEnv(Scene3DEnv_Name, (LPARAM)Autf8(str.c_str()).buf, true);
		}
		else if(pProp == m_envAmbientColor)
		{
			LoopAllEnv(Scene3DEnv_AmbientColor, Phantom::color4(GetPropColor(m_envAmbientColor), 1.0f));
		}
		else if(pProp == m_envFogEnable)
		{
			LoopAllEnv(Scene3DEnv_FogEnable, GetPropBool(m_envFogEnable));
			m_envFogMode->Enable(GetPropBool(m_envFogEnable));
			m_envFogColor->Enable(GetPropBool(m_envFogEnable));
			m_envFogNear->Enable(GetPropBool(m_envFogEnable));
			m_envFogFar->Enable(GetPropBool(m_envFogEnable));
		}
		else if(pProp == m_envFogMode)
		{
			LoopAllEnv(Scene3DEnv_FogMode, GetPropOption(m_envFogMode, g_typeFogMode));
		}
		else if(pProp == m_envFogColor)
		{
			LoopAllEnv(Scene3DEnv_FogColor, Phantom::color4(GetPropColor(m_envFogColor), 1.0f));
		}
		else if(pProp == m_envFogNear)
		{
			LoopAllEnv(Scene3DEnv_FogNear, (LPARAM)GetPropFloatPtr(m_envFogNear));
		}
		else if(pProp == m_envFogFar)
		{
			LoopAllEnv(Scene3DEnv_FogFar, (LPARAM)GetPropFloatPtr(m_envFogFar));
		}
		else if(pProp == m_envBrightnessEnable)
		{
			LoopAllEnv(Scene3DEnv_BrightnessEnable, GetPropBool(m_envBrightnessEnable));
			m_envBrightness->Enable(GetPropBool(m_envBrightnessEnable));
		}
		else if(pProp == m_envContrastEnable)
		{
			LoopAllEnv(Scene3DEnv_ContrastEnable, GetPropBool(m_envContrastEnable));
			m_envContrast->Enable(GetPropBool(m_envContrastEnable));
		}
		else if(pProp == m_envBrightness)
		{
			LoopAllEnv(Scene3DEnv_Brightness, (LPARAM)GetPropFloatPtr(m_envBrightness));
		}
		else if(pProp == m_envContrast)
		{
			LoopAllEnv(Scene3DEnv_Contrast, (LPARAM)GetPropFloatPtr(m_envContrast));
		}
		else if(pProp == m_envShadowEnable){
			LoopAllEnv(Scene3DEnv_ShadowEnable, (LPARAM)GetPropBool(m_envShadowEnable));
			this->RefreshShadowEnable(GetPropBool(m_envShadowEnable));
		}
		else if(pProp == m_envShadowMapSize){
			LoopAllEnv(Scene3DEnv_ShadowMapSize, (LPARAM)GetPropOption(m_envShadowMapSize, g_typeShadowMap));
		}
		else if(pProp == m_envShadowBias){
			LoopAllEnv(Scene3DEnv_ShadowBias, (LPARAM)GetPropFloatPtr(m_envShadowBias));
		}
		else if(pProp == m_envShadowViewLength){
			LoopAllEnv(Scene3DEnv_ShadowViewLength, (LPARAM)GetPropFloatPtr(m_envShadowViewLength));
		}
		else if(pProp == m_envShadowPCF){
			LoopAllEnv(Scene3DEnv_ShadowPCF, (LPARAM)GetPropOption(m_envShadowPCF, g_typeSoftPCF));
		}
		else if(pProp == m_envShadowDensity){
			LoopAllEnv(Scene3DEnv_ShadowDensity, (LPARAM)GetPropFloatPtr(m_envShadowDensity));
		}
		else if(pProp == m_envTerrainToMap){
			LoopAllEnv(Scene3DEnv_ShadowTerrainToMap, (LPARAM)GetPropBool(m_envTerrainToMap));
		}
		else if(pProp == m_envObjectToMap){
			LoopAllEnv(Scene3DEnv_ShadowObjectToMap, (LPARAM)GetPropBool(m_envObjectToMap));
		}
		else if(pProp == m_envTerrainWithMap){
			LoopAllEnv(Scene3DEnv_ShadowTerrainWithMap, (LPARAM)GetPropBool(m_envTerrainWithMap));
		}
		else if(pProp == m_envObjectWithMap){
			LoopAllEnv(Scene3DEnv_ShadowObjectWithMap, (LPARAM)GetPropBool(m_envObjectWithMap));
		}
		else if(pProp == m_envCenterObj){
			std::wstring str;
			GetPropText(m_envCenterObj, str);
			Autf8 name(str.c_str());
			int nID = 0;
			for(int i=0;i<this->m_scene3D->GetObjectCount();i++){
				SceneObject* obj = m_scene3D->GetObjectPtr(i);
				if(obj->GetType() == Phantom::MeshData::MeshType_Role || obj->GetType() == Phantom::MeshData::MeshType_SceneUnit)
				{
					char buf[256];
					sprintf(buf, "%s[%d]", obj->GetName(), obj->GetID());
					if(stricmp(name.buf, buf)==0)
					{
						nID = obj->GetID();
						break;
					}
				}
			}
			LoopAllEnv(Scene3DEnv_ShadowObjectCenter, (LPARAM)nID);
		}
	}
	else if(wnd == &m_lightProperties){
		if(pProp == m_lightName){
			std::wstring str;
			GetPropText(m_lightName, str);
			this->LoopAllLight(Scene3DLight_Name, (LPARAM)Autf8(str.c_str()).buf, true);
		}
		else if(pProp == m_lightDiffuse)
		{
			LoopAllLight(Scene3DLight_Color, Phantom::color4(GetPropColor(m_lightDiffuse), 1.0f));
		}
		else if(pProp == m_lightEnable)
		{
			LoopAllLight(Scene3DLight_Enable, GetPropBool(m_lightEnable));
		}
		else if(pProp == m_lightType)
		{
			LoopAllLight(Scene3DLight_Type, GetPropOption(m_lightType, g_typeLightType));
		}
		else if(pProp == m_lightNear)
		{
			LoopAllLight(Scene3DLight_Near, (LPARAM)GetPropFloatPtr(m_lightNear));
		}
		else if(pProp == m_lightFar)
		{
			LoopAllLight(Scene3DLight_Far, (LPARAM)GetPropFloatPtr(m_lightFar));
		}
		else if(pProp == m_lightAngleSmall)
		{
			LoopAllLight(Scene3DLight_AngleS, (LPARAM)GetPropFloatPtr(m_lightAngleSmall));
		}
		else if(pProp == m_lightAngleBig)
		{
			LoopAllLight(Scene3DLight_AngleB, (LPARAM)GetPropFloatPtr(m_lightAngleBig));
		}
		else if(pProp == m_lightRotX)
		{
			LoopAllLight(Scene3DLight_RotZ, (LPARAM)GetPropFloatPtr(m_lightRotX));
		}
		else if(pProp == m_lightRotY)
		{
			LoopAllLight(Scene3DLight_RotY, (LPARAM)GetPropFloatPtr(m_lightRotY));
		}

	}
	else if(wnd == &m_regionProperties){
		if(pProp == m_regionName){
			std::wstring str;
			GetPropText(m_regionName, str);
			this->LoopAllRegion(Scene3DRegion_Name, (LPARAM)Autf8(str.c_str()).buf, true);
		}
		else if(pProp == m_regionNameEnable){
			BOOL bEnable = GetPropBool(m_regionNameEnable);
			m_regionName->Enable(bEnable);
			this->LoopAllRegion(Scene3DRegion_NameEnable, bEnable, false);
		}
		else if(pProp == m_regionList){
			int lineid = GetPropOption(m_regionList, this->m_typeSceneID);
			this->LoopAllRegion(Scene3DRegion_RegionID, lineid, true);
		}
	}
	//else if(wnd == &m_grassProperties)
	//{
	//	if(pProp == m_grassTextureFile)
	//	{
	//		std::wstring file;
	//		GetPropFile(m_grassTextureFile, file);
	//		this->LoopAllGrass(Scene3DGrass_TextureFile, (LPARAM)A(file.c_str()).buf, true);
	//	}
	//	else if(pProp == m_grassAlphaBlend)
	//		LoopAllGrass(Scene3DGrass_AlphaBlend, GetPropBool(m_grassAlphaBlend));
	//	else if(pProp == m_grassAlphaMask)
	//		LoopAllGrass(Scene3DGrass_AlphaMask, (LPARAM)GetPropFloatPtr(m_grassAlphaMask));
	//	else if(pProp == m_grassAlphaSizeW)
	//		LoopAllGrass(Scene3DGrass_SizeW, (LPARAM)GetPropFloatPtr(m_grassAlphaSizeW));
	//	else if(pProp == m_grassAlphaSizeH)
	//		LoopAllGrass(Scene3DGrass_SizeH, (LPARAM)GetPropFloatPtr(m_grassAlphaSizeH));
	//	else if(pProp == m_grassWind)
	//		LoopAllGrass(Scene3DGrass_Wind, (LPARAM)GetPropFloatPtr(m_grassWind));
	//	else if(pProp == m_grassMaxVisible)
	//		LoopAllGrass(Scene3DGrass_MaxVisible, (LPARAM)GetPropFloatPtr(m_grassMaxVisible));
	//	else if(pProp == m_grassColor)
	//		LoopAllGrass(Scene3DGrass_Color, Phantom::color4(GetPropColor(m_grassColor), 1.0f));
	//	else if(pProp == m_grassFromColor)
	//		LoopAllGrass(Scene3DGrass_FromColor, Phantom::color4(GetPropColor(m_grassFromColor), 1.0f));
	//	else if(pProp == m_grassDensity)
	//		LoopAllGrass(Scene3DGrass_Density, (LPARAM)GetPropFloatPtr(m_grassDensity));
	//	else if(pProp == m_grassTextureLeft)
	//		LoopAllGrass(Scene3DGrass_TextureLeft, (LPARAM)GetPropInt(m_grassTextureLeft));
	//	else if(pProp == m_grassTextureTop)
	//		LoopAllGrass(Scene3DGrass_TextureTop, (LPARAM)GetPropInt(m_grassTextureTop));
	//	else if(pProp == m_grassTextureWidth)
	//		LoopAllGrass(Scene3DGrass_TextureWidth, (LPARAM)GetPropInt(m_grassTextureWidth));
	//	else if(pProp == m_grassTextureHeight)
	//		LoopAllGrass(Scene3DGrass_TextureHeight, (LPARAM)GetPropInt(m_grassTextureHeight));
	//	else if(pProp == m_grassTextureCenterY)
	//		LoopAllGrass(Scene3DGrass_CenterY, (LPARAM)GetPropInt(m_grassTextureCenterY));
	//}
	//else if(wnd == &m_skyProperties)
	//{
	//	if(pProp == m_skyName)
	//	{
	//		std::string str;
	//		GetPropText(m_skyName, str);
	//		this->LoopAllSkys(Scene3DSky_Name, (LPARAM)str.c_str(), true);
	//	}
	//	else if(pProp == m_skyFlareEnable)
	//	{
	//		LoopAllSkys(Scene3DSky_Flare, GetPropBool(m_skyFlareEnable));
	//	}
	//	else if(pProp == m_skyTextureFile)
	//	{
	//		std::wstring file;
	//		GetPropFile(m_skyTextureFile, file);
	//		this->LoopAllSkys(Scene3DSky_Texture, (LPARAM)A(file.c_str()).buf, false);
	//	}
	//	else if(pProp == m_skyVisible)
	//	{
	//		LoopAllSkys(Scene3DSky_Visible, GetPropBool(m_skyVisible));
	//	}
	//	else if(pProp == m_skyColor)
	//	{
	//		LoopAllSkys(Scene3DSky_Color, Phantom::color4(GetPropColor(m_skyColor), 1.0f));
	//	}
	//	else if(pProp == m_skyAmbientColor)
	//	{
	//		LoopAllSkys(Scene3DSky_AmbientColor, Phantom::color4(GetPropColor(m_skyAmbientColor), 1.0f));
	//	}
	//	else if(pProp == m_skyWindDirection)
	//	{
	//		LoopAllSkys(Scene3DSky_WindDirection, (LPARAM)GetPropFloatPtr(m_skyWindDirection));
	//	}
	//	else if(pProp == m_skyWindStrength)
	//	{
	//		LoopAllSkys(Scene3DSky_WindStrength, (LPARAM)GetPropFloatPtr(m_skyWindStrength));
	//	}
	//	else if(pProp == m_skyFlareFile)
	//	{
	//		std::wstring file;
	//		GetPropFile(m_skyFlareFile, file);
	//		DefineAuth_2();
	//		if(CheckAuth_2(0))
	//			this->LoopAllSkys(Scene3DSky_FlareFile, (LPARAM)A(file.c_str()).buf, false);
	//		else
	//			GetMainFrame()->m_bShowMessage	=	true;
	//	}
	//	else if(pProp == m_skyFlareXAngle)
	//	{
	//		LoopAllSkys(Scene3DSky_FlareXAngle, (LPARAM)GetPropFloatPtr(m_skyFlareXAngle));
	//	}
	//	else if(pProp == m_skyFlareYAngle)
	//	{
	//		LoopAllSkys(Scene3DSky_FlareYAngle, (LPARAM)GetPropFloatPtr(m_skyFlareYAngle));
	//	}
	//}
	//else if(wnd == &m_flareProperties)
	//{
	//	if(pProp == m_flareTexture)
	//	{
	//		std::wstring file;
	//		GetPropFile(m_flareTexture, file);
	//		this->LoopAllFlares(Scene3DFlare_Texture, (LPARAM)A(file.c_str()).buf, false);
	//	}
	//	else if(pProp == m_flarePosition)
	//	{
	//		LoopAllFlares(Scene3DFlare_Position, (LPARAM)GetPropFloatPtr(m_flarePosition));
	//	}
	//	else if(pProp == m_flareSize)
	//	{
	//		LoopAllFlares(Scene3DFlare_Radius, (LPARAM)GetPropFloatPtr(m_flareSize));
	//	}
	//	else if(pProp == m_flareAlpha)
	//	{
	//		LoopAllFlares(Scene3DFlare_Alpha, (LPARAM)GetPropFloatPtr(m_flareAlpha));
	//	}
	//	else if(pProp == m_flareColor)
	//	{
	//		LoopAllFlares(Scene3DFlare_Color, Phantom::color4(GetPropColor(m_flareColor), 1.0f));
	//	}
	//}
	//else if(wnd == &m_fogProperties)
	//{
	//	//if(pProp == m_fogName)
	//	//{
	//	//	std::string str;
	//	//	GetPropText(m_fogName, str);
	//	//	this->LoopAllFogs(Scene3DFog_Name, (LPARAM)str.c_str(), true);
	//	//}
	//	//else if(pProp == m_fogMode)
	//	//{
	//	//	LoopAllFogs(Scene3DFog_Enable, GetPropOption(m_fogMode, g_typeFogMode));
	//	//	Phantom::SceneFogData* fog = m_scene3D->GetFogDataPtr()->GetDataPtr(m_scene3D->m_activeFog);
	//	//	if(fog)
	//	//		Phantom::g_manager.UpdateFog(fog);
	//	//}
	//	//else if(pProp == m_fogColor)
	//	//{
	//	//	LoopAllFogs(Scene3DFog_Color, Phantom::color4(GetPropColor(m_fogColor), 1.0f));
	//	//	Phantom::SceneFogData* fog = m_scene3D->GetFogDataPtr()->GetDataPtr(m_scene3D->m_activeFog);
	//	//	if(fog)
	//	//		Phantom::g_manager.UpdateFog(fog);
	//	//}
	//	//else if(pProp == m_fogNear)
	//	//{
	//	//	LoopAllFogs(Scene3DFog_Near, (LPARAM)GetPropFloatPtr(m_fogNear));
	//	//	Phantom::SceneFogData* fog = m_scene3D->GetFogDataPtr()->GetDataPtr(m_scene3D->m_activeFog);
	//	//	if(fog)
	//	//		Phantom::g_manager.UpdateFog(fog);
	//	//}
	//	//else if(pProp == m_fogFar)
	//	//{
	//	//	LoopAllFogs(Scene3DFog_Far, (LPARAM)GetPropFloatPtr(m_fogFar));
	//	//	Phantom::SceneFogData* fog = m_scene3D->GetFogDataPtr()->GetDataPtr(m_scene3D->m_activeFog);
	//	//	if(fog)
	//	//		Phantom::g_manager.UpdateFog(fog);
	//	//}
	//}
	//else if(wnd == &m_advancedProperties)
	//{
	//	DefineAuth_3();
	//	if(!CheckAuth_3(0))
	//		return;
	//	if(pProp == m_advancedName)
	//	{
	//		std::string str;
	//		GetPropText(m_advancedName, str);
	//		this->LoopAllAdvanceds(Scene3DAdvanced_Name, (LPARAM)str.c_str(), true);
	//	}
	//	else if(pProp == m_advancedEnabled)
	//		LoopAllAdvanceds(Scene3DAdvanced_Enable, GetPropBool(m_advancedEnabled));
	//	else if(pProp == m_advancedTarget)
	//	{
	//		std::string buf;
	//		GetPropText(m_advancedTarget, buf);
	//		LoopAllAdvanceds(Scene3DAdvanced_Target, atoi(buf.c_str()));
	//	}
	//	else
	//	{
	//		for(int i=0;i<MAX_KEY_PARAMETER;i++)
	//		{
	//			if(m_advancedKeys[i] == pProp)
	//			{
	//				LoopAllAdvanceds(Scene3DAdvanced_Value, i, false, (LPARAM)GetPropFloatPtr(m_advancedKeys[i]));
	//				break;
	//			}
	//		}
	//	}
	//}
	else if(wnd == &m_cameraProperties)
	{
		if(pProp == m_cameraName)
		{
			std::string str;
			GetPropText(m_cameraName, str);
			this->LoopAllCameras(Scene3DCamera_Name, (LPARAM)str.c_str(), true);
		}
		else if(pProp == m_cameraOrtho)
		{
			LoopAllCameras(Scene3DCamera_Ortho, GetPropBool(m_cameraOrtho));
		}
		else if(pProp == m_cameraFPS)
		{
			LoopAllCameras(Scene3DCamera_FPS, GetPropBool(m_cameraFPS));
		}
		else if(pProp == m_cameraYRotEnable)
		{
			LoopAllCameras(Scene3DCamera_YRotEnable, GetPropBool(m_cameraYRotEnable));
		}
		else if(pProp == m_cameraXRotEnable)
		{
			LoopAllCameras(Scene3DCamera_XRotEnable, GetPropBool(m_cameraXRotEnable));
		}
		else if(pProp == m_cameraRotateX)
		{
			LoopAllCameras(Scene3DCamera_RotateX, (LPARAM)GetPropFloatPtr(m_cameraRotateX));
		}
		else if(pProp == m_cameraRotateZ)
		{
			LoopAllCameras(Scene3DCamera_RotateZ, (LPARAM)GetPropFloatPtr(m_cameraRotateZ));
		}
		else if(pProp == m_cameraTargetX)
		{
			LoopAllCameras(Scene3DCamera_TargetX, (LPARAM)GetPropFloatPtr(m_cameraTargetX));
		}
		else if(pProp == m_cameraTargetY)
		{
			LoopAllCameras(Scene3DCamera_TargetY, (LPARAM)GetPropFloatPtr(m_cameraTargetY));
		}
		else if(pProp == m_cameraTargetZ)
		{
			LoopAllCameras(Scene3DCamera_TargetZ, (LPARAM)GetPropFloatPtr(m_cameraTargetZ));
		}
		else if(pProp == m_cameraEyeX)
		{
			LoopAllCameras(Scene3DCamera_EyeX, (LPARAM)GetPropFloatPtr(m_cameraEyeX));
		}
		else if(pProp == m_cameraEyeY)
		{
			LoopAllCameras(Scene3DCamera_EyeY, (LPARAM)GetPropFloatPtr(m_cameraEyeY));
		}
		else if(pProp == m_cameraEyeZ)
		{
			LoopAllCameras(Scene3DCamera_EyeZ, (LPARAM)GetPropFloatPtr(m_cameraEyeZ));
		}
		else if(pProp == m_cameraFov)
		{
			LoopAllCameras(Scene3DCamera_Fov, (LPARAM)GetPropFloatPtr(m_cameraFov));
		}
		else if(pProp == m_cameraEnableMove)
		{
			LoopAllCameras(Scene3DCamera_EnableMove, (LPARAM)GetPropBool(m_cameraEnableMove));
		}
		else if(pProp == m_cameraEnableDistance)
		{
			LoopAllCameras(Scene3DCamera_EnableDistance, (LPARAM)GetPropBool(m_cameraEnableDistance));
		}
		else if(pProp == m_cameraMinDistance)
		{
			LoopAllCameras(Scene3DCamera_MinDistance, (LPARAM)GetPropFloatPtr(m_cameraMinDistance));
		}
		else if(pProp == m_cameraDistance)
		{
			LoopAllCameras(Scene3DCamera_Distance, (LPARAM)GetPropFloatPtr(m_cameraDistance));
		}
		else if(pProp == m_cameraMaxDistance)
		{
			LoopAllCameras(Scene3DCamera_MaxDistance, (LPARAM)GetPropFloatPtr(m_cameraMaxDistance));
		}
		else if(pProp == m_cameraMoveSpeed)
		{
			LoopAllCameras(Scene3DCamera_MoveSpeed, (LPARAM)GetPropFloatPtr(m_cameraMoveSpeed));
		}
		else if(pProp == m_cameraRotationSpeed)
			LoopAllCameras(Scene3DCamera_RotationSpeed, (LPARAM)GetPropFloatPtr(m_cameraRotationSpeed));
		//
		//else if(pProp == m_cameraShiftMoveMulValue)
		//	LoopAllCameras(Scene3DCamera_ShiftMoveMulValue, (LPARAM)GetPropFloatPtr(m_cameraShiftMoveMulValue));
		else if(pProp == m_cameraCursorClipInRotMove)
			LoopAllCameras(Scene3DCamera_CursorClipInRotMove, (LPARAM)GetPropBool(m_cameraCursorClipInRotMove));
		else if(pProp == m_cameraCenterCross)
			LoopAllCameras(Scene3DCamera_CenterCross, (LPARAM)GetPropBool(m_cameraCenterCross));
		//else if(pProp == m_cameraShiftMoveMul)
		//	LoopAllCameras(Scene3DCamera_ShiftMoveMul, (LPARAM)GetPropBool(m_cameraShiftMoveMul));
		else if(pProp == m_cameraMoveHeightIsZ)
			LoopAllCameras(Scene3DCamera_MoveHeightIsZ, (LPARAM)GetPropBool(m_cameraMoveHeightIsZ));
		else if(pProp == m_cameraFixedZAxis)
			LoopAllCameras(Scene3DCamera_FixedZAxis, (LPARAM)GetPropBool(m_cameraFixedZAxis));
		//
		else if(pProp == m_cameraRotationMouseButton)
			LoopAllCameras(Scene3DCamera_RotationMouseButton, (LPARAM)GetPropOption(m_cameraRotationMouseButton, g_typeMouseButton));
		else if(pProp == m_cameraMoveMouseButton)
			LoopAllCameras(Scene3DCamera_MoveMouseButton, (LPARAM)GetPropOption(m_cameraMoveMouseButton, g_typeMouseButton));
	}
	//else if(wnd == &m_waterProperties)
	//{
	//	if(pProp == m_waterName)
	//	{
	//		std::string str;
	//		GetPropText(m_waterName, str);
	//		this->LoopAllWaters(Scene3DWater_Name, (LPARAM)str.c_str(), true);
	//	}
	//	else if(pProp == m_waterVisible)
	//		LoopAllWaters(Scene3DWater_Visible, GetPropBool(m_waterVisible));
	//	//else if(pProp == m_waterTexture)
	//	//{
	//	//	std::wstring str;
	//	//	GetPropFile(m_waterTexture, str);
	//	//	int nTexture	=	m_scene3D->AddTexture(A(str.c_str()));
	//	//	LoopAllWaters(Scene3DWater_Texture, nTexture);
	//	//}
	//	else if(pProp == m_waterColor)
	//		LoopAllWaters(Scene3DWater_Color, GetPropColor(m_waterColor));
	//	else if(pProp == m_waterAlpha)
	//		LoopAllWaters(Scene3DWater_Alpha, (LPARAM)GetPropFloatPtr(m_waterAlpha));
	//	//
	//	else if(pProp == m_waterRotation_1)
	//		LoopAllWaters(Scene3DWater_Rotation_1, (LPARAM)GetPropFloatPtr(m_waterRotation_1));
	//	else if(pProp == m_waterSpeed_1)
	//		LoopAllWaters(Scene3DWater_Speed_1, (LPARAM)GetPropFloatPtr(m_waterSpeed_1));
	//	else if(pProp == m_waterRotation_2)
	//		LoopAllWaters(Scene3DWater_Rotation_2, (LPARAM)GetPropFloatPtr(m_waterRotation_2));
	//	else if(pProp == m_waterSpeed_2)
	//		LoopAllWaters(Scene3DWater_Speed_2, (LPARAM)GetPropFloatPtr(m_waterSpeed_2));
	//	else if(pProp == m_waterWaveX_1)
	//		LoopAllWaters(Scene3DWater_WaveX_1, (LPARAM)GetPropFloatPtr(m_waterWaveX_1));
	//	else if(pProp == m_waterWaveY_1)
	//		LoopAllWaters(Scene3DWater_WaveY_1, (LPARAM)GetPropFloatPtr(m_waterWaveY_1));
	//	else if(pProp == m_waterWaveX_2)
	//		LoopAllWaters(Scene3DWater_WaveX_2, (LPARAM)GetPropFloatPtr(m_waterWaveX_2));
	//	else if(pProp == m_waterWaveY_2)
	//		LoopAllWaters(Scene3DWater_WaveY_2, (LPARAM)GetPropFloatPtr(m_waterWaveY_2));
	//	//
	//	else if(pProp == m_waterReflectBump)
	//		LoopAllWaters(Scene3DWater_ReflectBump, (LPARAM)GetPropFloatPtr(m_waterReflectBump));
	//	else if(pProp == m_waterRefractBump)
	//		LoopAllWaters(Scene3DWater_RefractBump, (LPARAM)GetPropFloatPtr(m_waterRefractBump));
	//	else if(pProp == m_waterReflectWeight)
	//		LoopAllWaters(Scene3DWater_ReflectWeight, (LPARAM)GetPropFloatPtr(m_waterReflectWeight));
	//	//else if(pProp == m_waterRefractWeight)
	//		//LoopAllWaters(Scene3DWater_RefractWeight, (LPARAM)GetPropFloatPtr(m_waterRefractWeight));
	//	else if(pProp == m_waterFadeBias)
	//		LoopAllWaters(Scene3DWater_FadeBias, (LPARAM)GetPropFloatPtr(m_waterFadeBias));
	//	else if(pProp == m_waterFadeExponent)
	//		LoopAllWaters(Scene3DWater_FadeExponent, (LPARAM)GetPropFloatPtr(m_waterFadeExponent));
	//	else if(pProp == m_waterHeight)
	//		LoopAllWaters(Scene3DWater_Height, (LPARAM)GetPropFloatPtr(m_waterHeight));
	//	else if(pProp == m_waterEdgeAlpha)
	//		LoopAllWaters(Scene3DWater_HeightAlpha, (LPARAM)GetPropFloatPtr(m_waterEdgeAlpha));
	//}
	else if(wnd == &m_editorProperties && this->m_editorMode > EditorMode_None)
	{
		if(pProp == m_editorRadius)
		{
			this->m_fHeightRadius	=	this->GetPropFloat(m_editorRadius);
		}
		else if(pProp == m_editorVar)
		{
			this->m_editorInfo[m_editorMode].fVar	=	GetPropFloat(m_editorVar);
		}
		else if(pProp == m_editorNormalVar)
		{
			this->m_editorInfo[m_editorMode].fNormalVar	=	GetPropFloat(m_editorNormalVar);
		}
		else if(pProp == m_editorPower)
		{
			this->m_editorInfo[m_editorMode].fPower	=	GetPropFloat(m_editorPower);
		}
		else if(pProp == m_editorEnable)
		{
			this->m_editorInfo[m_editorMode].bEnable	=	GetPropBool(m_editorEnable);
		}
		else if(pProp == m_editorColor)
		{
			this->m_editorInfo[m_editorMode].color.from(GetPropColor(m_editorColor), 1);
		}
		else if(pProp == m_editorGrassSelect)
		{
			//std::string str;
			//GetPropText(m_editorGrassSelect, str);
			//ISceneGrassTexture* tex	=	m_scene3D->GetGrassDataPtr()->GetDataByName(str.c_str());
			//if(tex)
			//{
			//	m_selectGrassPtrID.id	=	tex->GetID();
			//	m_scene3D->GetGrassDataPtr()->GetDataPtr(m_selectGrassPtrID);
			//}
			//else
			//	m_selectGrassPtrID.id	=	0;
		}
		else if(pProp == m_editorMinValue)
		{
			this->m_editorInfo[m_editorMode].fMinValue	=	GetPropFloat(m_editorMinValue);
		}
		else if(pProp == m_editorMaxValue)
		{
			this->m_editorInfo[m_editorMode].fMaxValue	=	GetPropFloat(m_editorMaxValue);
		}
	}
	//else if(wnd == &m_animationProperties)
	//{
	//	if(pProp == m_animationName)
	//	{
	//		std::string str;
	//		GetPropText(m_animationName, str);
	//		LoopAllAnimations(Scene3DAnim_Name, (LPARAM)str.c_str(), true);
	//	}
	//	else if(pProp == m_animationTimeLength)
	//	{
	//		LoopAllAnimations(Scene3DAnim_TimeLength, (LPARAM)GetPropFloatPtr(m_animationTimeLength));
	//	}
	//	else if(pProp == m_animationTimeBegin)
	//	{
	//		LoopAllAnimations(Scene3DAnim_TimeBegin, (LPARAM)GetPropFloatPtr(m_animationTimeBegin));
	//	}
	//	else if(pProp == m_animationEnable)
	//	{
	//		LoopAllAnimations(Scene3DAnim_Enable, (LPARAM)GetPropBool(m_animationEnable));
	//	}
	//}
	//else if(wnd == &m_scaProperties)
	//{
	//	if(pProp == m_scaName)
	//	{
	//		std::string str;
	//		GetPropText(m_scaName, str);
	//		LoopAllSCAs(Scene3DSCAs_Name, (LPARAM)str.c_str(), true);
	//	}
	//	else if(pProp == m_scaEnable)
	//	{
	//		LoopAllSCAs(Scene3DSCAs_Enable, (LPARAM)GetPropBool(m_scaEnable));
	//	}
	//}
	//else if(wnd == &m_scaTrackProperties)
	//{
	//	if(pProp == m_trackName)
	//	{
	//		std::string str;
	//		GetPropText(m_trackName, str);
	//		LoopAllSCATracks(Scene3DSCATracks_Name, (LPARAM)str.c_str(), true);
	//	}
	//	else if(pProp == m_trackUnitSelect)
	//	{
	//		std::string str;
	//		GetPropText(m_trackUnitSelect, str);
	//		LoopAllSCATracks(Scene3DSCATracks_UnitSelect, (LPARAM)str.c_str());
	//	}
	//	else if(pProp == m_trackEnable)
	//	{
	//		LoopAllSCATracks(Scene3DSCATracks_Enable, (LPARAM)GetPropBool(m_trackEnable));
	//	}
	//	else if(pProp == m_trackFrameTimeLength)
	//	{
	//		LoopAllSCATracks(Scene3DSCATracks_FrameTimeLength, (LPARAM)GetPropFloatPtr(m_trackFrameTimeLength));
	//	}
	//	else if(pProp == m_trackScriptEnable)
	//	{
	//		LoopAllSCATracks(Scene3DSCATracks_ScriptEnable, (LPARAM)GetPropBool(m_trackScriptEnable));
	//	}
	//	else if(pProp == m_trackBlendTime)
	//	{
	//		LoopAllSCATracks(Scene3DSCATracks_BlendTime, (LPARAM)GetPropFloatPtr(m_trackBlendTime));
	//	}
	//	else if(pProp == m_sccPosEnable)
	//	{
	//		LoopAllSCATracks(Scene3DSCATracks_PosEnable, (LPARAM)GetPropBool(m_sccPosEnable));
	//	}
	//	else if(pProp == m_sccPosLookatTarget)
	//	{
	//		LoopAllSCATracks(Scene3DSCATracks_PosLookatTarget, (LPARAM)GetPropBool(m_sccPosLookatTarget));
	//	}
	//	else if(pProp == m_sccPosMoveSpeed)
	//	{
	//		LoopAllSCATracks(Scene3DSCATracks_PosMoveSpeed, (LPARAM)GetPropFloatPtr(m_sccPosMoveSpeed));
	//	}
	//	else if(pProp == m_sccPosResetFrames)
	//	{
	//	}
	//	else if(pProp == m_sccActionID)
	//	{
	//		std::string str;
	//		GetPropText(m_sccActionID, str);
	//		LoopAllSCATracks(Scene3DSCATracks_ActionID, (LPARAM)str.c_str());
	//	}
	//	else if(pProp == m_sccActionEnable)
	//	{
	//		LoopAllSCATracks(Scene3DSCATracks_ActionEnable, (LPARAM)GetPropBool(m_sccActionEnable));
	//	}
	//	else if(pProp == m_sccParentEnable)
	//	{
	//	}
	//	else if(pProp == m_sccParentID)
	//	{
	//	}
	//}
	else if(&m_unitProperties == wnd)
	{
		if(pProp == this->m_unitPositionX)
		{
			LoopAllUnits(Proc_m_unitPositionX, (LPARAM)GetPropFloatPtr(m_unitPositionX));
			//float fX	=	GetPropFloat(m_unitPositionX);
			//for(int i=0;i<this->m_selects.size();i++)
			//{
			//	Phantom::float3 pos	=	m_selects[i].GetPosition();
			//	pos.x		=	fX;
			//	m_selects[i].SetPosition(pos);
			//}
		}
		else if(pProp == this->m_unitPositionY)
		{
			LoopAllUnits(Proc_m_unitPositionY, (LPARAM)GetPropFloatPtr(m_unitPositionY));
			//float fY	=	GetPropFloat(m_unitPositionY);
			//for(int i=0;i<this->m_selects.size();i++)
			//{
			//	Phantom::float3 pos	=	m_selects[i].GetPosition();
			//	pos.y		=	fY;
			//	m_selects[i].SetPosition(pos);
			//	SetModifyed(true);
			//}
		}
		else if(pProp == this->m_unitEnable)
		{
			LoopAllUnits(Proc_m_unitEnable, (LPARAM)GetPropBool(m_unitEnable));
			//BOOL b	=	GetPropBool(m_unitEnable);
			//for(int i=0;i<this->m_selects.size();i++)
			//{
			//	m_selects[i].SetEnabled(b);
			//	SetModifyed(true);
			//}
		}
		else if(pProp == this->m_unitVisible)
		{
			LoopAllUnits(Proc_m_unitVisible, (LPARAM)GetPropBool(m_unitVisible));
			//BOOL b	=	GetPropBool(m_unitVisible);
			//for(int i=0;i<this->m_selects.size();i++)
			//{
			//	m_selects[i].SetVisible(b);
			//	SetModifyed(true);
			//}
		}
		else if(pProp == this->m_unitRange)
		{
			LoopAllUnits(Proc_m_unitRange, (LPARAM)GetPropFloatPtr(m_unitRange));
			//float b	=	To3DValue(GetPropFloat(m_unitRange));
			//for(int i=0;i<this->m_selects.size();i++)
			//{
			//	if(!m_selects[i].GetObjectPtr())
			//		continue;
			//	m_selects[i].GetObjectPtr()->m_fRange = b;
			//	SetModifyed(true);
			//}
		}
		else if(pProp == this->m_unitAtkRange)
		{
			LoopAllUnits(Proc_m_unitAtkRange, (LPARAM)GetPropFloatPtr(m_unitAtkRange));
			//float b	=	To3DValue(GetPropFloat(m_unitAtkRange));
			//for(int i=0;i<this->m_selects.size();i++)
			//{
			//	if(!m_selects[i].GetObjectPtr())
			//		continue;
			//	m_selects[i].GetObjectPtr()->m_fAtkRange = b;
			//	SetModifyed(true);
			//}
		}
		else if(pProp == this->m_unitName)//||pProp==m_unitNameEnable)
		{
			std::wstring name;
			GetPropText(m_unitName, name);
			LoopAllUnits(Proc_m_unitName, (LPARAM)name.c_str());
			//
			//for(int i=0;i<this->m_selects.size();i++)
			//{
			//	m_selects[i].SetName(Autf8(name.c_str()), GetPropBool(m_unitNameEnable));
			//	SetModifyed(true);
			//}
		}
		else if(pProp == this->m_unitNameEnable)//||pProp==m_unitNameEnable)
		{
			m_unitName->Enable(GetPropBool(m_unitNameEnable));
			LoopAllUnits(Proc_m_unitNameEnable, (LPARAM)GetPropBool(m_unitNameEnable));
		}
		else if(pProp == this->m_unitID)//||pProp==m_unitNameEnable)
		{
			int nContent = GetPropInt(m_unitID);
			if(this->m_scene3D->GetObjectByContentID(nContent)){
				GetMainFrame()->MessageBox(Language(L"�Ѿ��������ID��"));
				return;
			}
			LoopAllUnits(Proc_m_unitID, (LPARAM)nContent);
		}
		else if(pProp == this->m_unitEvents)
		{
			int eid = GetPropOption(m_unitEvents, g_typeTableEvents);
			std::wstring name;
			GetPropText(m_unitEvents, name);
			LoopAllUnits(Proc_m_unitEvents, (LPARAM)eid);
			for(int i=0;i<this->m_selects.size();i++)
			{
				if(m_selects[i].GetEventPtr())
				{
					if(stricmp(m_selects[i].GetEventPtr()->m_name.t, "event")==0){
						m_selects[i].GetEventPtr()->m_name = Autf8(name.c_str()).buf;
						SetPropText(m_unitName, Wutf8(m_selects[i].GetEventPtr()->m_name.t));
					}
				}
			}
		}
		else if(pProp == this->m_unitPositionZ)
		{
			LoopAllUnits(Proc_m_unitPositionZ, (LPARAM)GetPropFloatPtr(m_unitPositionZ));
			//float fZ	=	GetPropFloat(m_unitPositionZ);
			//for(int i=0;i<this->m_selects.size();i++)
			//{
			//	Phantom::float3 pos	=	m_selects[i].GetPosition();
			//	pos.z		=	fZ;
			//	m_selects[i].SetPosition(pos);
			//	SetModifyed(true);
			//}
		}
		else if(pProp == this->m_unitScaleFull)
		{
			LoopAllUnits(Proc_m_unitScaleFull, (LPARAM)GetPropFloatPtr(m_unitScaleFull));
			//float fScale	=	GetPropFloat(m_unitScaleFull);
			//for(int i=0;i<this->m_selects.size();i++)
			//{
			//	m_selects[i].SetSize(fScale);
			//	SetModifyed(true);
			//}
		}
		else if(pProp == this->m_unitDiffuseIndex)
		{
			int nDiffuse	=	GetPropOption(m_unitDiffuseIndex, g_typeGroupDiffuse);
			LoopAllUnits(Proc_m_unitDiffuseIndex, (LPARAM)nDiffuse);
			//for(int i=0;i<this->m_selects.size();i++)
			//{
			//	if(!m_selects[i].GetObjectPtr())
			//		continue;
			//	m_selects[i].GetObjectPtr()->ChangeDiffuse(nDiffuse);
			//	SetModifyed(true);
			//}
		}
		else if(pProp == this->m_unitFileOpen)
		{
			for(int i=0;i<this->m_selects.size();i++)
			{
				if(!m_selects[i].GetObjectPtr())
					continue;
				Phantom::SceneObjectFile* file = this->m_scene3D->GetObjectFile(m_selects[i].GetObjectPtr()->m_fileNameID);
				if(file)
					AfxGetApp()->OpenDocumentFile(W(file->name.t));
			}
		}
		else if(pProp == this->m_unitResetMatrix)
		{
			if(GetMainFrame()->MessageBox(Language(L"�Ƿ�Ҫ����ѡ�ж������Ϸ���黷���仯?��������޷�����"), 0, MB_YESNO)==IDYES){
				for(int i=0;i<this->m_selects.size();i++)
				{
					if(!m_selects[i].GetObjectPtr())
						continue;
					m_selects[i].GetObjectPtr()->ResetEnv(0);
					if(m_scene3D->GetActiveEnv())
						m_scene3D->GetActiveEnv()->RemoveObject(m_selects[i].GetObjectPtr()->GetID());
					this->SetModifyed();
				}
			}
		}
		else if(pProp == this->m_unitAutoHeight)
		{
			LoopAllUnits(Proc_m_unitAutoHeight, (LPARAM)GetPropBool(m_unitAutoHeight));
		}
		else if(pProp == this->m_unitResetToGame)
		{
			if(m_selects.size()>0&&GetMainFrame()->MessageBox(Language(L"�Ƿ�Ҫ����ѡ�ж������Ϸ���黷���仯?��������޷����� "), 0, MB_YESNO)==IDYES){
				for(int i=0;i<this->m_selects.size();i++)
				{
					if(!m_selects[i].GetObjectPtr())
						continue;
					if(m_scene3D->GetActiveEnv())
						m_selects[i].GetObjectPtr()->ResetSaveEnv();
				}
				for(int i=0;i<this->m_selects.size();i++)
				{
					if(!m_selects[i].GetObjectPtr())
						continue;
					m_scene3D->GetActiveEnv()->RemoveObject(m_selects[i].GetObjectPtr()->GetID());
				}
				this->SetModifyed();
			}
		}
	}
	else if(&m_objectProperties == wnd)
	{
		if(pProp == m_objectFileOpen)
		{
			LoopAllObjects(SceneObject_FileOpen);
		}
		else if(pProp == m_objectTable)
		{
			std::string str;
			GetPropText(m_objectTable, str);
			LoopAllObjects(SceneObject_SelectTable, (LPARAM)str.c_str());
			this->OnChangeTreeSelect(&m_treeView, 0);
		}
		else if(pProp == m_objectTableLine)
		{
			std::string str;
			GetPropText(m_objectTableLine, str);
			int len = str.size();
			int lineID	=	-1;
			for(int i=len-1;i>=0;i--)
			{
				if(str[i] == '[')
				{
					lineID	=	atoi(str.c_str() + i + 1);
					break;
				}
			}
			LoopAllObjects(SceneObject_SelectTableLine, (LPARAM)lineID);
			this->OnChangeTreeSelect(&m_treeView, 0);
		}
	}
}
VOID		GCSceneEditor3D::LoopAllUnits(ProSceneUnit proc, LPARAM nParameter, LPARAM nParameter2)
{
	this->BeginUndo();
	for(int i=0;i<this->m_selects.size();i++)
	{
		UndoPtr uptr;
		uptr.buff = AddUndoRedo(GCSceneEditor3D::SCENE3D_UNIT, (ProcUndoRedo)proc);
		uptr.urMode = UndoRedoBuffer::URMode_Add;
		uptr.buff->m_id		=	0;
		uptr.buff->m_id3 = this->m_scene3D->GetActiveEnv()->GetID();
		if(m_selects[i].m_objectPtr)
		{
			uptr.buff->m_id		=	1;
			uptr.buff->m_id2	=	m_selects[i].m_objectPtr->GetID();
		}
		else if(m_selects[i].m_eventPtr){
			uptr.buff->m_id		=	2;
			uptr.buff->m_id2	=	m_selects[i].m_eventPtr->GetID();
		}
		else if(m_selects[i].m_lightPtr){
			uptr.buff->m_id		=	3;
			uptr.buff->m_id2	=	m_selects[i].m_lightPtr->GetID();
			uptr.buff->m_id4	=	m_selects[i].m_bLightTarget;
		}
		else
			continue;
		(*proc)(this->m_scene3D, m_selects[i], nParameter, nParameter2, &uptr);
	}
	SetModifyed(true);
}
VOID		GCSceneEditor3D::SetLightEnable( int type )
{
	m_lightRotX->Enable(true);
	m_lightRotY->Enable(true);
	switch(type){
	case Phantom::SceneLight::LightType_Omni:
		{
			m_lightNear->Enable(true);
			m_lightFar->Enable(true);
			m_lightAngleSmall->Enable(false);
			m_lightAngleBig->Enable(false);
			m_lightRotX->Enable(false);
			m_lightRotY->Enable(false);
		}
		break;
	case Phantom::SceneLight::LightType_Spot:
		{
			m_lightNear->Enable(true);
			m_lightFar->Enable(true);
			m_lightAngleSmall->Enable(true);
			m_lightAngleBig->Enable(true);
		}
		break;
	case Phantom::SceneLight::LightType_Direction:
		{
			m_lightNear->Enable(false);
			m_lightFar->Enable(false);
			m_lightAngleSmall->Enable(false);
			m_lightAngleBig->Enable(false);
		}
		break;
	}
}
VOID		GCSceneEditor3D::RefreshLightProp(int lid)
{
	SetCurrentProperties(&m_lightProperties, L"�ƹ�����", NULL);
	//
	Phantom::GameID id;
	id.id	=	lid;
	Phantom::SceneLight* light	=	&m_scene3D->GetActiveEnv()->m_defaultLight;
	if(lid>0)
		light = m_scene3D->GetActiveEnv()->GetLightPtr(id);
	m_lightProperties.EnableRender(false);
	if(!light)
	{
		m_lightProperties.EnableWindow(false);
		m_lightProperties.EnableRender(true);
		return;
	}
	if(lid==0)
		SetPropText(m_lightName, Language(L"ȫ�ֹ�"));
	else
		SetPropText(m_lightName, light->m_name.t);
	SetPropOption(m_lightType, g_typeLightType, light->m_lightType);
	SetPropColor(m_lightDiffuse, Phantom::color4(light->m_lightColor.x, light->m_lightColor.y, light->m_lightColor.z, 0).getRGB());
	SetPropBool(m_lightEnable, light->m_bEnabled);
	SetPropFloat(m_lightNear, light->GetNear());
	SetPropFloat(m_lightFar, light->GetFar());
	SetPropFloat(m_lightAngleSmall, light->GetAngleSmall());
	SetPropFloat(m_lightRotX, Degress(light->m_angleZ));
	SetPropFloat(m_lightRotY, Degress(light->m_angleY));
	SetPropFloat(m_lightAngleBig, light->GetAngleBig());
	if(lid==0)
		light->m_lightType = Phantom::SceneLight::LightType_Direction;
	SetLightEnable(light->m_lightType);
	m_lightType->Enable(lid>0);
	m_lightProperties.EnableRender(true);
}
struct	FloatAni3
{
	Phantom::FloatAnimation* ani1[3];
	int	index;
	FloatAni3(){memset(ani1, 0, sizeof(ani1)); index = 0;}
};
VOID		GCSceneEditor3D::OnChangeTreeSelect()	//����ѡ�����οؼ�
{
	TreeItemType* type	=	this->GetSelectedItem();
	if(!type)
	{
		SetCurrentProperties(&m_viewerProps, L"�ļ�����", NULL);
		return;
	}
	switch(type->type)
	{
	case SCENE3D_MAIN:
		{
			SetCurrentProperties(&m_sceneProperties, L"������������", NULL);
			m_sceneProperties.EnableRender(false);
			//SetPropColor(m_sceneAmbientColor, m_scene3D->GetAmbientColor().getRGB());
			//SetPropFloat(m_sceneBrightness, m_scene3D->GetSceneHighlight());
			SetPropFloat(m_sceneSpecularExponent, m_scene3D->m_specularExponent);
			SetPropFloat(m_sceneSpecularPower, m_scene3D->m_specularPower);
			SetPropColor(m_sceneColor, m_scene3D->m_sceneDiffuse.getRGB());
			SetPropFloat(m_sceneMaxVisible, m_scene3D->m_fMaxViewDistance);
			SetPropBool(m_sceneClipEnable, m_scene3D->m_bClipCamera);
			SetPropFloat(m_sceneClipSize, m_scene3D->m_fClipCameraSize);
			//SetPropFloat(m_sceneHeightAlign, m_scene3D->GetHeightAlignValue());
			//
			//SetPropFloat(m_sceneLODDetailMax, m_scene3D->GetTerrainLODDetail());
			//SetPropFloat(m_sceneLODDetailMin, m_scene3D->GetLODMinLevelDetail());
			//SetPropInt(m_sceneLODBuildGrids, m_scene3D->GetLODBuildWidth());	//LOD���´�����������
			//SetPropBool(m_sceneLODEnable, m_scene3D->IsLODEnable());
			//
			//SetPropBool(m_sceneUnitNameVisible, m_scene3D->IsUnitNameVisible());
			//SetPropBool(m_sceneUnitBloodVisible, m_scene3D->IsUnitBloodVisible());
			//SetPropFloat(m_sceneUnitNameSize, m_scene3D->GetUnitNameSize());
			//SetPropFloat(m_sceneUnitBloodSize, m_scene3D->GetUnitBloodSize());
			//SetPropFloat(m_sceneUnitNameVisibleLength, m_scene3D->GetUnitTopVisibleLength());
			//SetPropFile(m_sceneUnitBloodTexture, m_scene3D->GetBloodTextureInfo(BloodTextureInfo_Blood)->textureFile.t);
			//SetPropFile(m_sceneLogicSystem, m_scene3D->GetLogicSystemFile());
			//SetPropFloat(m_sceneShadowAlpha, m_scene3D->GetMeshShadowAlpha());
			//
			//SetPropFloat(m_geometryLODDetail, m_scene3D->GetObjectLODDetail());
			//SetPropFloat(m_geometryLODMaxVisible, m_scene3D->GetObjectLODMinVisible());
			//SetPropOption(m_textureMinFilter, g_typeFilter, m_scene3D->GetMinFilter());
			//SetPropOption(m_textureMagFilter, g_typeFilter, m_scene3D->GetMagFilter());
			//SetPropOption(m_textureMipFilter, g_typeFilter, m_scene3D->GetMipFilter());
			m_sceneProperties.EnableRender(true);
		}
		break;
	case SCENE3D_FOG_LIST:
		{
			SetCurrentProperties(NULL, NULL, NULL);
		}
		break;
	case SCENE3D_LIGHT:
		{
			RefreshLightProp(type->p1);
			m_lightSelect = 0;
		}
		break;
	//case SCENE3D_GRASS:
	//	{
	//		SetCurrentProperties(&m_grassProperties, L"������", NULL);
	//		//
	//		Phantom::PtrID id;
	//		id.id	=	type->p1;
	//		ISceneGrassTexture* grass	=	m_scene3D->GetGrassDataPtr()->GetDataPtr(id);
	//		m_grassProperties.EnableRender(false);
	//		if(!grass)
	//		{
	//			m_grassProperties.EnableWindow(FALSE);
	//			m_grassProperties.EnableRender(true);
	//			break;
	//		}
	//		SetPropFile(m_grassTextureFile, grass->GetTextureFile());
	//		SetPropBool(m_grassAlphaBlend, grass->IsAlphaBlend());
	//		SetPropFloat(m_grassAlphaMask, grass->GetAlphaMask());
	//		SetPropFloat(m_grassAlphaSizeW, grass->GetGrassSize().x);
	//		SetPropFloat(m_grassAlphaSizeH, grass->GetGrassSize().y);
	//		SetPropFloat(m_grassWind, grass->GetGrassWind());
	//		SetPropFloat(m_grassMaxVisible, grass->GetVisibleLength());
	//		SetPropColor(m_grassColor, Phantom::color4(grass->GetColor()).getRGB());
	//		SetPropColor(m_grassFromColor, Phantom::color4(grass->GetColorFrom()).getRGB());
	//		SetPropFloat(m_grassDensity, grass->GetDensity());
	//		//
	//		PRect rc	=	grass->GetTextureRect();
	//		SetPropInt(m_grassTextureLeft, rc.left);
	//		SetPropInt(m_grassTextureTop, rc.top);
	//		SetPropInt(m_grassTextureWidth, rc.right - rc.left);
	//		SetPropInt(m_grassTextureHeight, rc.bottom - rc.top);
	//		SetPropInt(m_grassTextureCenterY, grass->GetTextureCenterY());
	//		m_selectGrassPtrID	=	id;
	//		//
	//		m_grassProperties.EnableRender(true);
	//	}
	//	break;
	case SCENE3D_CAMERA:
		{
			SetCurrentProperties(&m_cameraProperties, L"��ͷ����", NULL);
			//
			//Phantom::GetCameraPtr()->GetCameraConfig(m_currentCamera);
			//
			Phantom::PtrID id;
			id.id	=	type->p1;
			Phantom::SceneCameraData* camera	=	m_scene3D->GetCameraDataPtr()->GetDataPtr(id);
			m_cameraProperties.EnableRender(false);
			if(!camera)
			{
				m_cameraProperties.EnableWindow(FALSE);
				m_cameraProperties.EnableRender(true);
				break;
			}
			m_currentCamera = *camera;
			Phantom::GetCameraPtr()->SetCameraConfig(m_currentCamera);
			wchar_t wbuf[128];
			swprintf(wbuf, L"%s[%s]", Language(L"������б�"), Wutf8(m_currentCamera.name.t).buf);
			m_treeView.SetItemText(m_hCameraList, wbuf);
			SetPropText(m_cameraName, camera->name.t);
			Phantom::GetCameraPtr()->m_bOffsetEnable = true;
			if(strstr(camera->name.t, "game")){
				m_scene3D->SetActiveCamera(camera->name.t);
			}
			else{
				Phantom::GetCameraPtr()->m_bOffsetEnable = false;
				Phantom::GetCameraPtr()->m_bArea = false;
			}
			//m_cameraName->Enable(camera != m_currentCamera);
			SetPropBool(m_cameraOrtho, camera->IsEnable(Phantom::CameraEnable_OrthoMode));
			SetPropBool(m_cameraFPS, camera->IsEnable(Phantom::CameraEnable_FPSMode));
			SetPropBool(m_cameraYRotEnable, camera->IsEnable(Phantom::CameraEnable_YRotation));
			SetPropBool(m_cameraXRotEnable, camera->IsEnable(Phantom::CameraEnable_XRotation));
			SetPropFloat(m_cameraRotateX, camera->vRotate.x);
			SetPropFloat(m_cameraRotateZ, camera->vRotate.z);
			SetPropFloat(m_cameraTargetX, camera->vTarget.x);
			SetPropFloat(m_cameraTargetY, camera->vTarget.y);
			SetPropFloat(m_cameraTargetZ, camera->vTarget.z);
			//
			SetPropFloat(m_cameraEyeX, camera->vEye.x);
			SetPropFloat(m_cameraEyeY, camera->vEye.y);
			SetPropFloat(m_cameraEyeZ, camera->vEye.z);
			//
			SetPropFloat(m_cameraFov, camera->fFov);
			SetPropBool(m_cameraEnableMove, camera->IsEnable(Phantom::CameraEnable_EnableMove));
			SetPropBool(m_cameraEnableDistance, camera->IsEnable(Phantom::CameraEnable_EnableDistance));
			SetPropFloat(m_cameraDistance, GetCameraPtr()->GetDistance());
			SetPropFloat(m_cameraMinDistance, camera->fMinDistance);
			SetPropFloat(m_cameraMaxDistance, camera->fMaxDistance);
			SetPropFloat(m_cameraMoveSpeed, camera->fMoveSpeed);
			SetPropFloat(m_cameraRotationSpeed, camera->fRotationSpeedMask);
			//
			SetPropBool(m_cameraCursorClipInRotMove, camera->IsEnable(Phantom::CameraEnable_CursorClipInRotMove));
			SetPropBool(m_cameraCenterCross, camera->IsEnable(Phantom::CameraEnable_CenterCross));
			//SetPropBool(m_cameraShiftMoveMul, camera->IsEnable(Phantom::CameraEnable_ShiftMoveMul));
			SetPropBool(m_cameraMoveHeightIsZ, camera->IsEnable(Phantom::CameraEnable_MoveHeightIsZ));
			SetPropBool(m_cameraFixedZAxis, camera->IsEnable(Phantom::CameraEnable_FixedZAxis));
			//
			//SetPropFloat(m_cameraShiftMoveMulValue, camera->fShiftMoveMul);
			SetPropOption(m_cameraRotationMouseButton, g_typeMouseButton, camera->rotButton);	//ת����ť
			SetPropOption(m_cameraMoveMouseButton, g_typeMouseButton, camera->moveButton);	//ת����ť
			//
			//SetPropOption(m_cameraMoveLeft, g_typeInputKey,		camera->moveLeft);	//ת����ť
			//SetPropOption(m_cameraMoveRight, g_typeInputKey,	camera->moveRight);	//ת����ť
			//SetPropOption(m_cameraMoveForward, g_typeInputKey,	camera->moveForward);	//ת����ť
			//SetPropOption(m_cameraMoveBack, g_typeInputKey,		camera->moveBack);	//ת����ť
			//SetPropOption(m_cameraMoveUp, g_typeInputKey,		camera->moveUp);	//ת����ť
			//SetPropOption(m_cameraMoveDown, g_typeInputKey,		camera->moveDown);	//ת����ť
			//
			//m_scene3D->GetAtmospherePtr()->SetActiveCamera(camera->id);
			//Phantom::GetCameraPtr()->SetCameraConfig(*camera);
			//
			m_cameraProperties.EnableRender(true);
		}
		break;
	//case SCENE3D_FLARE:
	//	{
	//		SetCurrentProperties(&m_flareProperties, L"��������", NULL);
	//		//
	//		Phantom::PtrID id;
	//		id.id	=	type->p1;
	//		Phantom::SceneSkyData* sky	=	m_scene3D->m_skyDataPtr.GetDataPtr(id);
	//		m_flareProperties.EnableRender(false);
	//		if(!sky)
	//		{
	//			m_flareProperties.EnableWindow(FALSE);
	//			m_flareProperties.EnableRender(true);
	//			break;
	//		}
	//		SkyFlareInfo& info	=	sky->flares[type->p2];
	//		SetPropFile(m_flareTexture, info.textureFile.t);
	//		SetPropFloat(m_flarePosition, info.fPosition);
	//		SetPropFloat(m_flareSize, info.fRadius);
	//		SetPropColor(m_flareColor, info.color);
	//		SetPropFloat(m_flareAlpha, info.color.a);
	//		m_flareProperties.EnableWindow(true);
	//		m_flareProperties.EnableRender(true);
	//	}
	//	break;
	//case SCENE3D_EFFECT_ADVANCED:
	//	{
	//		SetCurrentProperties(&m_advancedProperties, L"ȫ��ĻЧ������", NULL);
	//		//
	//		Phantom::PtrID id;
	//		id.id	=	type->p1;
	//		IAdvancedEffect* adv	=	m_scene3D->GetAdvancedEffects().GetDataPtr(id);
	//		m_advancedProperties.EnableRender(false);
	//		if(!adv)
	//		{
	//			m_advancedProperties.EnableWindow(FALSE);
	//			m_advancedProperties.EnableRender(true);
	//			break;
	//		}
	//		m_advancedProperties.EnableWindow(true);
	//		//
	//		SetPropText(m_advancedName, adv->GetName());
	//		SetPropBool(m_advancedEnabled, adv->IsActive());
	//		switch(adv->GetType())
	//		{
	//		case AdvancedEffect_HDR:
	//			SetPropText(m_advancedType, "hdr");
	//			break;
	//		}
	//		m_advancedTarget->RemoveAllOptions();
	//		m_advancedTarget->AddOption(L"default");
	//		for(int i=0;i<MAX_KEY_PARAMETER;i++)
	//		{
	//			if(i >= adv->GetKeyCount())
	//				m_advancedKeys[i]->Show(false);
	//			else
	//			{
	//				m_advancedKeys[i]->Show(true);
	//				m_advancedKeys[i]->SetName(W(adv->GetKeyPtr(i)->GetFloatName()));
	//				SetPropFloat(m_advancedKeys[i], adv->GetKeyPtr(i)->GetNormalValue());
	//				m_advancedKeys[i]->SetMinMax(adv->GetKeyPtr(i)->GetMinValue(), adv->GetKeyPtr(i)->GetMaxValue());
	//			}
	//			//Scene3DAdvanced_Value
	//		}
	//		NameW select = L"default";
	//		for(int i=1;i<adv->GetTargetCount();i++)
	//		{
	//			wchar_t buf[128];
	//			swprintf(buf, L"%d", i);
	//			m_advancedTarget->AddOption(buf);
	//			if(i == adv->GetTargetMode())
	//				select	=	buf;
	//		}
	//		SetPropText(m_advancedTarget, select);
	//		//
	//		m_advancedProperties.EnableRender(true);
	//	}
	//	break;
	//case SCENE3D_SKY:
	//	{
	//		SetCurrentProperties(&m_skyProperties, L"�������", NULL);
	//		//
	//		Phantom::PtrID id;
	//		id.id	=	type->p1;
	//		Phantom::SceneSkyData* sky	=	m_scene3D->m_skyDataPtr.GetDataPtr(id);
	//		m_skyProperties.EnableRender(false);
	//		if(!sky)
	//		{
	//			m_skyProperties.EnableWindow(FALSE);
	//			m_skyProperties.EnableRender(true);
	//			break;
	//		}
	//		SetPropText(m_skyName, sky->name.t);
	//		SetPropBool(m_skyVisible, sky->bEnable);
	//		SetPropColor(m_skyColor, Phantom::color4(sky->skyColor).getRGB());
	//		SetPropColor(m_skyAmbientColor, Phantom::color4(sky->ambientColor).getRGB());
	//		SetPropFile(m_skyTextureFile, sky->file.t);
	//		SetPropBool(m_skyFlareEnable, sky->bFlareEnable);
	//		//SetPropFloat(m_skyHeightVar, sky->fHeight);
	//		SetPropFile(m_skyFlareFile, sky->flareFile.t);
	//		SetPropFloat(m_skyFlareXAngle, sky->fAngleX);
	//		SetPropFloat(m_skyFlareYAngle, sky->fAngleZ);
	//		SetPropFloat(m_skyWindDirection, sky->fWindDirection);
	//		SetPropFloat(m_skyWindStrength, sky->fWindPower);
	//		m_scene3D->GetAtmospherePtr()->SetActiveSky(sky->id);
	//		//
	//		m_skyProperties.EnableRender(true);
	//	}
	//	break;
	case SCENE3D_UNIT:
		{
			//
			Phantom::PtrID id;
			id.id	=	type->p1;
			Phantom::SceneObject* obj	=	m_scene3D->GetObjectByID(type->p1);
			if(!obj)
			{
				SetCurrentProperties(NULL, NULL, NULL);
				break;
			}
			//
			std::vector<SelectEditor> objects;
			std::map<HTREEITEM,TreeItemType*> selectTypes;
			for(int i=0;i<this->m_treeView.GetSelectCount();i++)
			{
				HTREEITEM hItem		=	m_treeView.GetSelect(i);
				TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
				if(type && type->type == SCENE3D_UNIT)
				{
					Phantom::PtrID id;
					id.id	=	type->p1;
					Phantom::SceneObject* obj	=	m_scene3D->GetObjectByID(type->p1);
					if(obj)
					{
						SelectEditor s;
						s.Init(obj);
						objects.push_back(s);
					}
				}
			}
			AddSelectObject(objects, false);
			SelectEditor sel;
			sel.Init(obj);
			OnSelectObject(sel);
		}
		break;
	case SCENE3D_POINT:
		{
			//
			Phantom::PtrID id;
			id.id	=	type->p1;
			Phantom::ScenePoint* obj	=	m_scene3D->GetActiveEnv()->GetPointByID(type->p1);
			if(!obj)
			{
				SetCurrentProperties(NULL, NULL, NULL);
				break;
			}
			//
			std::vector<SelectEditor> objects;
			std::map<HTREEITEM,TreeItemType*> selectTypes;
			for(int i=0;i<this->m_treeView.GetSelectCount();i++)
			{
				HTREEITEM hItem		=	m_treeView.GetSelect(i);
				TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
				if(type && type->type == SCENE3D_POINT)
				{
					Phantom::PtrID id;
					id.id	=	type->p1;
					Phantom::ScenePoint* obj	=	m_scene3D->GetActiveEnv()->GetPointByID(type->p1);
					if(obj)
					{
						SelectEditor s;
						s.Init(obj);
						objects.push_back(s);
					}
				}
			}
			AddSelectObject(objects, false);
			SelectEditor sel;
			sel.Init(obj);
			OnSelectObject(sel);
		}
		break;
	//case SCENE3D_WATER:
	//	{
	//		SetCurrentProperties(&m_waterProperties, L"ˮ������", NULL);
	//		//
	//		Phantom::PtrID id;
	//		id.id	=	type->p1;
	//		const SceneWaterData* water	=	m_scene3D->GetWaterDataPtr()->GetDataPtr(id);
	//		m_waterProperties.EnableRender(false);
	//		if(!water)
	//		{
	//			m_waterProperties.EnableWindow(FALSE);
	//			m_waterProperties.EnableRender(true);
	//			break;
	//		}
	//		SetPropText(m_waterName, water->name.t);
	//		SetPropBool(m_waterVisible, water->m_bWaterVisible);
	//		SetPropColor(m_waterColor, Phantom::color4(water->GetWaterColor()).getRGB());
	//		SceneTextureRuntime* tex	=	m_scene3D->GetTextureRuntime(water->m_nWaterTextureID);
	//		if(tex)
	//			SetPropFile(m_waterTexture, tex->fileName.t);
	//		else
	//			SetPropFile(m_waterTexture, L"");
	//		//
	//		SetPropFloat(m_waterEdgeAlpha, water->fWaterBlendAlpha);
	//		SetPropFloat(m_waterRotation_1, water->GetWaterRotation_1());
	//		SetPropFloat(m_waterSpeed_1, water->m_waterSpeed_1);
	//		SetPropFloat(m_waterRotation_2, water->m_waterRotation_2);
	//		SetPropFloat(m_waterSpeed_2, water->m_waterSpeed_2);
	//		SetPropFloat(m_waterWaveX_1, water->m_waterWaveX);
	//		SetPropFloat(m_waterWaveY_1, water->m_waterWaveY);
	//		SetPropFloat(m_waterWaveX_2, water->m_waterWaveX_1);
	//		SetPropFloat(m_waterWaveY_2, water->m_waterWaveY_1);
	//		SetPropFloat(m_waterReflectBump, water->m_waterReflectBump);
	//		SetPropFloat(m_waterRefractBump, water->m_waterRefractBump);
	//		SetPropFloat(m_waterReflectWeight, water->m_waterReflectWeight);
	//		//SetPropFloat(m_waterRefractWeight, water->m_waterRefractWeight);
	//		SetPropFloat(m_waterFadeBias, water->m_waterFadeBias);
	//		SetPropFloat(m_waterFadeExponent, water->m_waterFadeExponent);
	//		SetPropFloat(m_waterAlpha, Phantom::color4(water->GetWaterColor()).a);
	//		SetPropFloat(m_waterHeight, water->GetWaterHeight());
	//		//
	//		m_waterProperties.EnableRender(true);
	//	}
	//	break;
	case SCENE3D_ENV:
		{
			SetCurrentProperties(&m_envProperties, Language(L"��������"), NULL);
			m_envProperties.EnableRender(false);
			Phantom::SceneEnv* env		=	0;
			if(type->p1==0)
				env = &m_scene3D->m_defaultEnv;
			else
				env = m_scene3D->GetEnvByID(type->p1);
			if(!env)
			{
				m_treeView.SetItemText(this->m_hEnv, Language(L"�����б�"));
				m_scene3D->ActiveEnv(0);
				m_envProperties.EnableWindow(FALSE);
				m_envProperties.EnableRender(true);
				SetCurrentProperties(NULL, NULL, NULL);
				break;
			}
			m_scene3D->ActiveEnv(env);
			wchar_t name[256];
			swprintf(name, L"%s[%s]", Language(L"�����б�"), Wutf8(env->m_name.t).buf);
			m_treeView.SetItemText(this->m_hEnv, name);
			SetPropInt(m_envID, env->GetID());
			SetPropText(m_envName, Wutf8(env->GetName()));
			SetPropInt(m_envObjects, env->GetNumObject());
			//
			SetPropOption(m_envFogMode, g_typeFogMode, env->m_fogType);
			SetPropColor(m_envFogColor, Phantom::color4(env->m_fogColor).getRGB());
			SetPropColor(m_envAmbientColor, Phantom::color4(env->m_ambientColor).getRGB());
			SetPropFloat(m_envFogNear, env->m_fNear);
			SetPropFloat(m_envFogFar, env->m_fFar);
			SetPropBool(m_envBrightnessEnable, env->m_bBrightness);
			SetPropBool(m_envFogEnable, env->m_fogEnable);
			SetPropBool(m_envContrastEnable, env->m_bContrast);
			SetPropFloat(m_envBrightness, env->m_fBrightness);
			SetPropFloat(m_envContrast, env->m_fContrast);
			//
			SetPropBool(m_envShadowEnable, env->IsShadowEnable());
			SetPropOption(m_envShadowMapSize, g_typeShadowMap, env->m_shadowMapSize);
			SetPropFloat(m_envShadowBias, env->m_shadowBias);
			SetPropOption(m_envShadowPCF, g_typeSoftPCF, env->m_shadowPCF);
			SetPropFloat(m_envShadowViewLength, env->m_shadowViewSize);
			SetPropFloat(m_envShadowDensity, env->m_shadowDensity);
			SetPropBool(m_envTerrainToMap, env->IsShadowEnable(Phantom::ShadowEnable_TerrainToMap));
			SetPropBool(m_envObjectToMap, env->IsShadowEnable(Phantom::ShadowEnable_MeshToMap));
			SetPropBool(m_envTerrainWithMap, env->IsShadowEnable(Phantom::ShadowEnable_TerrainWithMap));
			SetPropBool(m_envObjectWithMap, env->IsShadowEnable(Phantom::ShadowEnable_MeshWithMap));
			RefreshShadowEnable(env->IsShadowEnable());
			//
			m_envCenterObj->RemoveAllOptions();
			m_envCenterObj->AddOption(L" ");
			NameW select;
			for(int i=0;i<this->m_scene3D->GetObjectCount();i++){
				SceneObject* obj = m_scene3D->GetObjectPtr(i);
				if(obj->GetType() == Phantom::MeshData::MeshType_Role || obj->GetType() == Phantom::MeshData::MeshType_SceneUnit)
				{
					wchar_t buf[256];
					swprintf(buf, L"%s[%d]", Wutf8(obj->GetName()).buf, obj->GetID());
					m_envCenterObj->AddOption(buf);
					if(obj->GetID() == env->m_shadowCenterObj.id)
						select = buf;
				}
			}
			SetPropText(m_envCenterObj, select);//m_dialogPtr->GetGroupPtr(control->GetGroupID())->GetName());//g_typeControlGroup, control->GetGroupID());
			//
			m_envFogMode->Enable(env->m_fogEnable);
			m_envFogColor->Enable(env->m_fogEnable);
			m_envFogNear->Enable(env->m_fogEnable);
			m_envFogFar->Enable(env->m_fogEnable);
			m_envBrightness->Enable(env->m_bBrightness);
			m_envContrast->Enable(env->m_bContrast);
			//
			m_envProperties.EnableRender(true);
			this->RebuildPoints();
			RefreshLights();
		}
		break;
	case SCENE3D_REGION:
		{
			SetCurrentProperties(&m_regionProperties, Language(L"��������"), NULL);
			m_regionProperties.EnableRender(false);
			Phantom::SceneRegionData* data = m_scene3D->GetRegionPtr(type->p1);
			if(!data)
			{
				m_regionProperties.EnableWindow(FALSE);
				m_regionProperties.EnableRender(true);
				SetCurrentProperties(NULL, NULL, NULL);
				break;
			}
			m_regionIndex = type->p1;
			SetPropText(m_regionName, Wutf8(m_scene3D->GetRegionName(type->p1)));
			SetPropBool(m_regionNameEnable, data->bCustomName);
			SetPropOption(m_regionList, this->m_typeSceneID, data->regionid);
			m_regionProperties.EnableRender(true);
			m_scene3D->RebuildRegionSets(m_regionIndex);
		}
		break;
	case SCENE3D_OBJECT:
		{
			SetCurrentProperties(&m_objectProperties, L"�����ļ�����", 0);
			//
			m_objectProperties.EnableRender(false);
			Phantom::SceneObjectFile* file	=	this->m_scene3D->m_objectFilePtr.GetDataPtr(Phantom::PtrID(0, type->p1));
			if(!file)
			{
				m_objectProperties.EnableWindow(FALSE);
				m_objectProperties.EnableRender(true);
				break;
			}
			m_objectProperties.EnableRender(true);
		}
		break;
	default:
		SetCurrentProperties(NULL, NULL, NULL);
		break;
	}
}
const wchar_t*	GetMeshTypeName(int type){
	switch(type){
	case Phantom::MeshData::MeshType_Role:
		return Language(L"��ɫ");
	case Phantom::MeshData::MeshType_SceneUnit:
		return Language(L"��������");
	case Phantom::MeshData::MeshType_StaticMesh:
		return Language(L"װ����");
	}
	return L"";
}
VOID		GCSceneEditor3D::OnSelectObject(SelectEditor& obj)
{
	if(obj.m_lightPtr){
		RefreshLightProp(obj.m_lightPtr->GetID());
		m_lightSelect = 1;
		return;
	}
	SetCurrentProperties(&m_unitProperties, L"��λ����", 0);
	m_unitProperties.EnableRender(false);
	//
	SetPropInt(m_unitID, obj.GetID());
	m_unitID->AllowEdit(obj.GetObjectPtr()!=0);
	SetPropFloat(m_unitPositionX, (obj.GetPosition().x));
	SetPropFloat(m_unitPositionY, (obj.GetPosition().y));
	SetPropFloat(m_unitPositionZ, (obj.GetPosition().z));
	SetPropBool(m_unitEnable, obj.IsEnabled());
	SetPropBool(m_unitVisible, obj.IsVisible());
	SetPropText(m_unitName, Wutf8(obj.GetName()));
	SetPropBool(m_unitNameEnable, obj.IsCustomName());
	m_unitName->Enable(obj.IsCustomName());
	m_unitRange->Show(obj.GetObjectPtr()!=0);
	m_unitAtkRange->Show(obj.GetObjectPtr()!=0);
	if(obj.GetObjectPtr()){
		m_unitRange->Enable(obj.GetObjectPtr()->GetMeshPtr()->GetDataPtr()->m_meshType==Phantom::MeshData::MeshType_Role);
		m_unitAtkRange->Enable(obj.GetObjectPtr()->GetMeshPtr()->GetDataPtr()->m_meshType==Phantom::MeshData::MeshType_Role);
		SetPropFloat(m_unitRange, ToMeter(obj.GetObjectPtr()->m_fRange));
		SetPropFloat(m_unitAtkRange, ToMeter(obj.GetObjectPtr()->m_fAtkRange));
	}
	//SetPropText(m_unitType, GetSceneObjType(obj->m_type));
	////
	//Phantom::matrix4x4 xmat	=	*obj->GetWorldPtr();
	//Phantom::float3 scale;
	//getMatrixScale(scale, xmat);
	SetPropFloat(this->m_unitScaleFull, obj.GetSize());//ToMeter(scale.z * fZ));
	m_unitDiffuseIndex->Show(obj.GetObjectPtr()!=0);
	this->m_unitFileOpen->Show(obj.GetObjectPtr()!=0);
	this->m_unitEvents->Show(obj.GetEventPtr()!=0);
	if(obj.GetEventPtr()){
		SetPropOption(this->m_unitEvents, g_typeTableEvents, obj.GetEventPtr()->m_eventid);
	}
	if(obj.GetObjectPtr())
		SetPropOption(m_unitDiffuseIndex, g_typeGroupDiffuse, obj.GetObjectPtr()->GetDiffuseIndex());
	this->m_unitType->Show(obj.GetObjectPtr()!=0);
	this->m_unitResetMatrix->Show(obj.GetObjectPtr()!=0);
	this->m_unitResetToGame->Show(obj.GetObjectPtr()!=0);
	if(obj.GetObjectPtr())
		SetPropBool(m_unitAutoHeight, obj.GetObjectPtr()->m_bAutoHeight);
	if(obj.GetObjectPtr()){
		SetPropText(m_unitType, GetMeshTypeName(obj.GetObjectPtr()->GetType()));
	}
	m_unitProperties.EnableRender(true);
}
//VOID		GCSceneEditor3D::PlayActive(ISCA_Animation* ani, ISCA_Base* b, ISCA_Track* t)
//{
//	//for(int i=0;i<this->m_scene3D->GetAnimationManager().GetDataCount();i++)
//	//{
//	//	if(ani != m_scene3D->GetAnimationManager().GetDataPtr(i))// || !m_bIsPlaying)
//	//		m_scene3D->GetAnimationManager().GetDataPtr(i)->Stop();
//	//	else// if(m_bIsPlaying)
//	//	{
//	//		m_scene3D->GetAnimationManager().GetDataPtr(i)->SetPlayTrackOnly(b, t);
//	//		if(m_bIsPlaying)
//	//			m_scene3D->GetAnimationManager().GetDataPtr(i)->Play();
//	//		else
//	//			m_scene3D->GetAnimationManager().GetDataPtr(i)->Stop();
//	//		m_scene3D->GetAnimationManager().GetDataPtr(i)->Pause(m_bIsPause);
//	//		m_scene3D->GetAnimationManager().GetDataPtr(i)->SetLoopMode(m_bLoopMode);
//	//	}
//	//}
//}

VOID		GCSceneEditor3D::SetPause(BOOL b)
{
	m_bIsPause	=	b;
	//for(int i=0;i<this->m_scene3D->GetAnimationManager().GetDataCount();i++)
	//	m_scene3D->GetAnimationManager().GetDataPtr(i)->Pause(b);
}
VOID		GCSceneEditor3D::SetPlay()
{
	//m_bIsPlaying	=	true;
	//for(int i=0;i<this->m_scene3D->GetAnimationManager().GetDataCount();i++)
	//{
	//	m_scene3D->GetAnimationManager().GetDataPtr(i)->Play();
	//	m_scene3D->GetAnimationManager().GetDataPtr(i)->SetPlayTime(0);
	//}
}
VOID		GCSceneEditor3D::SetStop()
{
	//m_bIsPlaying	=	false;
	//for(int i=0;i<this->m_scene3D->GetAnimationManager().GetDataCount();i++)
	//	m_scene3D->GetAnimationManager().GetDataPtr(i)->Stop();
}
VOID		GCSceneEditor3D::SetLoopMode(BOOL b)
{
	//m_bLoopMode	=	b;
	//for(int i=0;i<this->m_scene3D->GetAnimationManager().GetDataCount();i++)
	//	m_scene3D->GetAnimationManager().GetDataPtr(i)->SetLoopMode(b);
}

VOID		GCSceneEditor3D::InitSceneProperties()	//��ʼ����������
{
	CMFCPropertyGridProperty* group1			= new CMFCPropertyGridProperty(Language(L"���λ�������"));
	//group1->AddSubItem(m_sceneAmbientColor	=	AddPropColor(Language(L"��ɫ"), Language(L"m_sceneAmbientColor", L"���ó�����ɫ")));
	//group1->AddSubItem(m_sceneBrightness		=	AddPropFloat(Language(L"����"), Language(L"m_sceneBrightness", L"���ó�������"), false, -1.0f, 10.0f ));
	group1->AddSubItem(m_sceneColor				=	AddPropColor(Language(L"������ɫ"), Language(L"m_sceneColor", L"���ó�����ɫ")));
	group1->AddSubItem(m_sceneSpecularExponent	=	AddPropFloat(Language(L"����ָ��"), Language(L"m_sceneSpecularExponent", L"���ó�������ָ��"), false, 0.0f, 100.0f ));
	group1->AddSubItem(m_sceneSpecularPower		=	AddPropFloat(Language(L"����Ȩ��"), Language(L"m_sceneSpecularPower", L"���ó�������Ȩ��"), false, 0.0f, 100.0f ));
	group1->AddSubItem(m_sceneMaxVisible		=	AddPropFloat(Language(L"���ɼ�����(��)"), Language(L"m_sceneMaxVisible", L"���ó������ɼ����룬��λ����"), true, 10.0f, 100000.0f ));
	group1->AddSubItem(m_sceneClipEnable	=	AddPropBool(Language(L"��ͷ��������"), Language(L"m_sceneClipEnable", L"������������")));
	group1->AddSubItem(m_sceneClipSize	=	AddPropFloat(Language(L"��ͷ�����������"), Language(L"m_sceneClipSize", L"��������������ճ�����С�����Զ�����"), false, 0.001f, 10.0f, .1f));

	//group1->AddSubItem(m_sceneHeightAlign		=	AddPropFloat(Language(L"�߶ȶ��뵥λ(��)"), Language(L"m_sceneHeightAlign", L"���ó����߶ȶ��뵥λ����λ����"), true, 0.0f, 10000.0f ));
	//CMFCPropertyGridProperty* groupLod			=	new CMFCPropertyGridProperty(Language(L"����LOD����"));
	//groupLod->AddSubItem(m_sceneLODEnable		=	AddPropBool(Language(L"LOD�Ƿ���Ч"), Language(L"m_sceneLODEnable", L"LOD���أ��Ƿ�������LOD���㣬������Ҫ�رգ���Ҫ��������Ը߶˻���ʱʹ�ã����߱༭����ʹ�á�")));
	//groupLod->AddSubItem(m_sceneLODDetailMax	=	AddPropFloat(Language(L"���LODϸ�ڶ�"), Language(L"m_sceneLODDetailMax", L"����LODϸ�ڶȣ��������õ��μ���LOD��ϸ�ڶȣ�0.1ʱϸ�ڶȵͣ�1.0ʱϸ�ڶȸߣ����ߵ�ϸ�ڶ�Ҳ���и��ߵ���Ⱦ�档"), false, 0.01f, 1.0f));
	//groupLod->AddSubItem(m_sceneLODDetailMin	=	AddPropFloat(Language(L"�����Ԫ��.LODϸ�ڶ�"), Language(L"m_sceneLODDetailMin", L"����LODϸ�ڶȣ���������������μ���LOD��ϸ�ڶȣ�0.1ʱϸ�ڶȵͣ�1.0ʱϸ�ڶȸߣ����ߵ�ϸ�ڶ�Ҳ���и��ߵ���Ⱦ�档"), false, 0.01f, 1.0f));
	//groupLod->AddSubItem(m_sceneLODBuildGrids	=	AddPropInt(Language(L"LOD�ع�������"), Language(L"m_sceneLODBuildGrids", L"�������¹���ĸ���������ÿ�����������������ϵͳ���Զ�����һ��LOD�Խ�ʡ��������"), 1, 128));
	//toolbar�� m_sceneTerrainVisible, , ���ߵ���,���������,����Ҫʹ�öԻ���
	//CMFCPropertyGridProperty* groupGeomLod			= new CMFCPropertyGridProperty(Language(L"ģ��LOD����"));
	//groupGeomLod->AddSubItem(m_geometryLODDetail		=	AddPropFloat(Language(L"ģ��LODϸ�ڶ�"), Language(L"m_geometryLODDetail", L"����ϵͳ�е�ģ��LODϸ�ڶȣ���С0.1~10.0��"), false, 0.01f, 10.0f));
	//groupGeomLod->AddSubItem(m_geometryLODMaxVisible	=	AddPropFloat(Language(L"ģ��LOD���ɼ�����(��)"), Language(L"m_geometryLODMaxVisible", L"����ϵͳ�е�ģ��LOD��С�ɼ����룬������뷶Χ�ڶ���ɼ�����λ���ס�"), true, 10.0f, 10000.0f));
	//
	//CMFCPropertyGridProperty* groupFilter			= new CMFCPropertyGridProperty(Language(L"���ʹ��˷�ʽ"));
	//groupFilter->AddSubItem(m_textureMinFilter	=	AddPropOption(Language(L"��С���˷�ʽ"),	Language(L"m_textureMinFilter", L"��С���˲���"), g_typeFilter));
	//groupFilter->AddSubItem(m_textureMagFilter	=	AddPropOption(Language(L"�����˷�ʽ"),	Language(L"m_textureMagFilter", L"�����˷�ʽ"), g_typeFilter));
	//groupFilter->AddSubItem(m_textureMipFilter	=	AddPropOption(Language(L"MipMap���˷�ʽ"),	Language(L"m_textureMipFilter", L"MipMap���˷�ʽ"), g_typeFilter));
	//
	//CMFCPropertyGridProperty* groupUnit			= new CMFCPropertyGridProperty(Language(L"��λ���"));
	//groupUnit->AddSubItem(m_sceneLogicSystem	=	AddPropFile(Language(L"�߼�����(logic_system.txt)"), Language(L"m_sceneLogicSystem", L"�����߼�����(logic_system.txt)��"), L"logic_system.txt|logic_system.txt|*.*|*.*||"));
	//groupUnit->AddSubItem(m_sceneShadowAlpha	=	AddPropFloat(Language(L"����Ӱǿ��"), Language(L"m_sceneShadowAlpha", L"���ü���Ӱǿ�ȡ�"), false, 0.0f, 1.0f));
	//groupUnit->AddSubItem(m_sceneUnitNameVisible	=	AddPropBool(Language(L"��λ�����Ƿ���ʾ"), Language(L"m_sceneUnitNameVisible", L"���õ�λ�����Ƿ���ʾ��")));
	//groupUnit->AddSubItem(m_sceneUnitBloodVisible	=	AddPropBool(Language(L"��λѪ���Ƿ���ʾ"), Language(L"m_sceneUnitBloodVisible", L"���õ�λѪ���Ƿ���ʾ��")));
	////
	//groupUnit->AddSubItem(m_sceneUnitNameSize	=	AddPropFloat(Language(L"��λ���ִ�С"), Language(L"m_sceneUnitNameSize", L"���õ�λ���ִ�С��"), false, 0.1f, 1000.0f));
	//groupUnit->AddSubItem(m_sceneUnitBloodSize	=	AddPropFloat(Language(L"��λѪ����С"), Language(L"m_sceneUnitBloodSize", L"���õ�λѪ����С��"), false, 0.1f, 1000.0f));
	//groupUnit->AddSubItem(m_sceneUnitNameVisibleLength	=	AddPropFloat(Language(L"��λ[����/Ѫ��]���ɼ�����(��λ����)"), Language(L"m_sceneUnitNameVisibleLength", L"���õ�λ[����/Ѫ��]���ɼ����롣"), FloatType_Meter, 0.1f, 10000.0f));
	//groupUnit->AddSubItem(m_sceneUnitBloodTexture	=	AddPropFile(Language(L"��λѪ��ͼƬ"), Language(L"m_sceneUnitBloodTexture", L"���õ�λѪ��ͼƬ���ϰ벿�ֱ������°벿��Ѫ��ֵ��"), GetImageFilter()));
	//
	//CMFCPropertyGridProperty* groupHeightMap	= new CMFCPropertyGridProperty(Language(L"�߶�ͼ����"));
	//groupHeightMap->AddSubItem(m_sceneTextureMapBlur	=	AddPropInt(Language(L"��ͼģ������"), Language(L"m_sceneTextureMapBlur", L"���õ�ͼͼƬģ�����ء�"), 0, 128));
	//groupHeightMap->AddSubItem(m_sceneHeightMapBlur		=	AddPropInt(Language(L"�߶�ͼģ������"), Language(L"m_sceneHeightMapHeight", L"���ø߶�ͼģ�����ء�"), 0, 128));
	//groupHeightMap->AddSubItem(m_sceneHeightMapHeight	=	AddPropFloat(Language(L"�߶�ͼ��ߵ�"), Language(L"m_sceneHeightMapBlur", L"���ø߶�ͼ��ߵ㡣"), true, 1.0f, 1000.0f));
	//groupHeightMap->AddSubItem(m_sceneTHBuildVisibleAll	=	AddPropButton(Language(L"���¹���ɼ�����"), Language(L"m_sceneTHBuildVisibleAll", L"���¹���ɼ����֡�")));
	//
	//PropertyPtr			m_sceneLevelTex0;
	//PropertyPtr			m_sceneLevelTex1;
	//PropertyPtr			m_sceneLevelTex2;
	//PropertyPtr			m_sceneLevelTex3;
	//PropertyPtr			m_sceneLevelTex4;
	//PropertyPtr			m_sceneLevelTex5;
	//PropertyPtr			m_sceneLevelTexHeight0;
	//PropertyPtr			m_sceneLevelTexHeight1;
	//PropertyPtr			m_sceneLevelTexHeight2;
	//PropertyPtr			m_sceneLevelTexHeight3;
	//PropertyPtr			m_sceneLevelTexHeight4;
	//PropertyPtr			m_sceneLevelTexHeight5;
	//groupHeightMap->AddSubItem(m_sceneTHBuildAllScene	=	AddPropButton(Language(L"���¹������в���(�ļ���ܴ�)"), Language(L"m_sceneTHBuildAllScene", L"���¹������в���(�ļ���ܴ�)��")));
	//
	this->m_sceneProperties.AddProperty(group1);
	//this->m_sceneProperties.AddProperty(groupLod);
	//this->m_sceneProperties.AddProperty(groupGeomLod);
	//this->m_sceneProperties.AddProperty(groupFilter);
	//this->m_sceneProperties.AddProperty(groupUnit);
	//this->m_sceneProperties.AddProperty(groupHeightMap);
}
VOID		GCSceneEditor3D::InitSkyProperties()
{
	//CMFCPropertyGridProperty* group1			= new CMFCPropertyGridProperty(Language(L"��ջ�������"));
	//group1->AddSubItem(m_skyName		=	AddPropText(Language(L"����"), Language(L"m_skyName", L"�������ͼƬ"), false, Name::Length));
	//group1->AddSubItem(m_skyTextureFile	=	AddPropFile(Language(L"���ͼƬ"), Language(L"m_skyTextureFile", L"�������ͼƬ"), GetImageFilter()));
	//group1->AddSubItem(m_skyVisible		=	AddPropBool(Language(L"��տɼ�"), Language(L"m_skyVisible", L"��������Ƿ�ɼ�")));
	//group1->AddSubItem(m_skyColor		=	AddPropColor(Language(L"�����ɫ"), Language(L"m_skyColor", L"���������ɫ")));
	//group1->AddSubItem(m_skyAmbientColor=	AddPropColor(Language(L"��������ɫ"), Language(L"m_skyAmbientColor", L"���û�������ɫ")));
	////
	////group1->AddSubItem(m_skyHeightVar	=	AddPropFloat(Language(L"��ո߶�"), Language(L"m_skyHeightVar", L"��������������ƶ���Χ(��λ����)"), true, -1000.0f, 1000.0f));
	//group1->AddSubItem(m_skyFlareFile	=	AddPropFile(Language(L"�����ι��ļ�"), Language(L"m_skyFlareFile", L"���ó�������Ȩ��"), L"*.t|*.t||"));
	//group1->AddSubItem(m_skyFlareEnable	=	AddPropBool(Language(L"�ι���Ч"), Language(L"m_skyFlareEnable", L"���ó����ι���Ч")));
	//group1->AddSubItem(m_skyFlareXAngle	=	AddPropFloat(Language(L"���ⷽ������"), Language(L"m_skyFlareXAngle", L"���ù��ߵ�������ת(��λ���Ƕ�)"), FloatType_Angle, -360.0f, 360.0f));
	//group1->AddSubItem(m_skyFlareYAngle	=	AddPropFloat(Language(L"���ⷽ������"), Language(L"m_skyFlareYAngle", L"���ù��ߵ�������ת(��λ���Ƕ�)"), FloatType_Angle, -360.0f, 360.0f ));
	//CMFCPropertyGridProperty* groupWind			= new CMFCPropertyGridProperty(Language(L"��������"));
	//groupWind->AddSubItem(m_skyWindDirection	=	AddPropFloat(Language(L"��.����"), Language(L"m_skyWindDirection", L"���÷�ķ���"), FloatType_Angle, 0.0f, 360.0f));
	//groupWind->AddSubItem(m_skyWindStrength		=	AddPropFloat(Language(L"��.ǿ��(��/��)"), Language(L"m_skyWindStrength", L"���÷��ǿ��(��λ����/��)"), true, 0.0f, 15.0f));
	////
	//CMFCPropertyGridProperty* flarePtr			= new CMFCPropertyGridProperty(Language(L"��ջ�������"));
	//flarePtr->AddSubItem(m_flareTexture		=	AddPropFile(Language(L"ͼƬ"), Language(L"m_flareTexture", L"���ù���ͼƬ"), GetImageFilter()));
	//flarePtr->AddSubItem(m_flarePosition	=	AddPropFloat(Language(L"λ��"), Language(L"m_flarePosition", L"���ù���λ��"), false, 0.0f, 1.0f));
	//flarePtr->AddSubItem(m_flareSize		=	AddPropFloat(Language(L"��С"), Language(L"m_flareSize", L"���ù��δ�С"), false, 0.0f, 10.0f));
	//flarePtr->AddSubItem(m_flareColor		=	AddPropColor(Language(L"��ɫ"), Language(L"m_flareColor", L"���ù�����ɫ")));
	//flarePtr->AddSubItem(m_flareAlpha		=	AddPropFloat(Language(L"͸��"), Language(L"m_flareAlpha", L"���ù���͸��"), false, 0.0f, 1.0f));

	//this->m_skyProperties.AddProperty(group1);
	//this->m_skyProperties.AddProperty(groupWind);
	//this->m_flareProperties.AddProperty(flarePtr);
}

VOID		GCSceneEditor3D::InitFogProperties()
{
	CMFCPropertyGridProperty* group1			= new CMFCPropertyGridProperty(Language(L"���������"));
	//group1->AddSubItem(m_fogName		=	AddPropText(Language(L"����"), Language(L"m_fogName", L"������������"), false, Name::Length));
	//group1->AddSubItem(m_fogMode		=	AddPropOption(Language(L"����"), Language(L"m_fogMode", L"��������"), g_typeFogMode));
	//group1->AddSubItem(m_fogColor		=	AddPropColor(Language(L"����ɫ"), Language(L"m_fogColor", L"��������ɫ")));
	//group1->AddSubItem(m_fogNear		=	AddPropFloat(Language(L"������ɼ�"), Language(L"m_fogNear", L"����������ɼ�"), true, -1000.0f, 1000.0f, 10.0f));
	//group1->AddSubItem(m_fogFar			=	AddPropFloat(Language(L"����Զ�ɼ�"), Language(L"m_fogFar", L"��������Զ�ɼ�"), true, -10000.0f, 100000.0f, 10.0f));
	//
	this->m_fogProperties.AddProperty(group1);
}

VOID		GCSceneEditor3D::InitCameraProperties()
{
	CMFCPropertyGridProperty* group1	= new CMFCPropertyGridProperty(Language(L"��������"));
	group1->AddSubItem(m_cameraName		=	AddPropText(Language(L"����"), Language(L"m_cameraName", L"���þ�ͷ��������"), false, Name::Length));
	group1->AddSubItem(m_cameraFov		=	AddPropFloat(Language(L"���"), Language(L"m_cameraFov", L"���þ�ͷ��ǣ�1~180֮��"), FloatType_Angle, 1.0f, 180.0f, 1.0f));
	group1->AddSubItem(m_cameraOrtho	=	AddPropBool(Language(L"ƽ�澵ͷ"), Language(L"m_cameraOrtho", L"�����Ƿ�ƽ�澵ͷ")));
	group1->AddSubItem(m_cameraFPS		=	AddPropBool(Language(L"FPS��Ϸ�ӽ�"), Language(L"m_cameraFPS", L"�����Ƿ�FPS��Ϸ�ӽ�")));
	group1->AddSubItem(m_cameraCenterCross	=	AddPropBool(Language(L"��ʾFPS׼��"), Language(L"m_cameraCenterCross", L"�����Ƿ���ʾFPS׼��")));
	//
	CMFCPropertyGridProperty* groupRot	= new CMFCPropertyGridProperty(Language(L"��ͷת��"));
	groupRot->AddSubItem(m_cameraRotationMouseButton	=	AddPropOption(Language(L"��갴��[ת��]"), Language(L"m_cameraRotationMouseButton", L"���´���겢�ƶ�ʱ��ͷ����ת��"), g_typeMouseButton));
	groupRot->AddSubItem(m_cameraXRotEnable	=	AddPropBool(Language(L"����ת��"), Language(L"m_cameraXRotEnable", L"���þ�ͷ��������ת��")));
	groupRot->AddSubItem(m_cameraYRotEnable	=	AddPropBool(Language(L"����ת��"), Language(L"m_cameraYRotEnable", L"���þ�ͷ��������ת��")));
	groupRot->AddSubItem(m_cameraRotateX	=	AddPropFloat(Language(L"���½Ƕ�"), Language(L"m_cameraRotateX", L"���þ�ͷ���½Ƕ�"), FloatType_Angle, -360.0f, 360.0f, 1.0f));
	groupRot->AddSubItem(m_cameraRotateZ	=	AddPropFloat(Language(L"���ҽǶ�"), Language(L"m_cameraRotateZ", L"���þ�ͷ���ҽǶ�"), FloatType_Angle, -360.0f, 360.0f, 1.0f));
	groupRot->AddSubItem(m_cameraRotationSpeed	=	AddPropFloat(Language(L"ת���ٶ�"), Language(L"m_cameraRotationSpeed", L"���þ�ͷת���ٶ�"), false, 0.0f, 100.0f, .1f));
	//
	CMFCPropertyGridProperty* groupMove	= new CMFCPropertyGridProperty(Language(L"��ͷ�ƶ�"));
	groupMove->AddSubItem(m_cameraMoveMouseButton	=	AddPropOption(Language(L"��갴��[�ƶ�]"), Language(L"m_cameraMoveMouseButton", L"���´���겢�ƶ�ʱ��ͷ�����ƶ�"), g_typeMouseButton));
	groupMove->AddSubItem(m_cameraEnableMove		=	AddPropBool(Language(L"�����ƶ�"), Language(L"m_cameraEnableMove", L"���þ�ͷ�����ƶ�")));
	groupMove->AddSubItem(m_cameraCursorClipInRotMove	=	AddPropBool(Language(L"�������λ��"), Language(L"m_cameraCursorClipInRotMove", L"���þ�ͷ�ƶ�ʱ�������λ��")));
	groupMove->AddSubItem(m_cameraMoveSpeed			=	AddPropFloat(Language(L"�ƶ��ٶ�"), Language(L"m_cameraMoveSpeed", L"���þ�ͷ�ƶ��ٶ�(��λ����)"), true, 0.0f, 10000.0f, 1.0f));
	//groupMove->AddSubItem(m_cameraShiftMoveMul		=	AddPropBool(Language(L"��סShift�����ƶ�"), Language(L"m_cameraShiftMoveMul", L"���ð�סShift�����ƶ�")));
	//groupMove->AddSubItem(m_cameraShiftMoveMulValue	=	AddPropFloat(Language(L"��סShift�����ƶ�����"), Language(L"m_cameraShiftMoveMul", L"���þ�ͷ��סShift�����ƶ�����"), false, -100.0f, 100.0f, 1.0f));
	groupMove->AddSubItem(m_cameraMoveHeightIsZ		=	AddPropBool(Language(L"Y����ǰ�ƶ�"), Language(L"m_cameraMoveHeightIsZ", L"����Y����ǰ�ƶ�,���������3D������ǰ")));
	groupMove->AddSubItem(m_cameraFixedZAxis		=	AddPropBool(Language(L"Z��̶�����"), Language(L"m_cameraFixedZAxis", L"����Z��̶�����,RTS��Ϸ��ʹ��")));
	////
	//groupMove->AddSubItem(m_cameraMoveLeft		=	AddPropOption(Language(L"�����ƶ�[����]"), Language(L"m_cameraMoveLeft",	L"���ü����ƶ�ʱ���[����]"), g_typeInputKey));
	//groupMove->AddSubItem(m_cameraMoveRight		=	AddPropOption(Language(L"�����ƶ�[����]"), Language(L"m_cameraMoveRight",	L"���ü����ƶ�ʱ���[����]"), g_typeInputKey));
	//groupMove->AddSubItem(m_cameraMoveForward	=	AddPropOption(Language(L"�����ƶ�[��ǰ]"), Language(L"m_cameraMoveForward", L"���ü����ƶ�ʱ���[��ǰ]"), g_typeInputKey));
	//groupMove->AddSubItem(m_cameraMoveBack		=	AddPropOption(Language(L"�����ƶ�[���]"), Language(L"m_cameraMoveBack",	L"���ü����ƶ�ʱ���[���]"), g_typeInputKey));
	//groupMove->AddSubItem(m_cameraMoveUp		=	AddPropOption(Language(L"�����ƶ�[����]"), Language(L"m_cameraMoveUp",		L"���ü����ƶ�ʱ���[����]"), g_typeInputKey));
	//groupMove->AddSubItem(m_cameraMoveDown		=	AddPropOption(Language(L"�����ƶ�[����]"), Language(L"m_cameraMoveDown",	L"���ü����ƶ�ʱ���[����]"), g_typeInputKey));
	//
	CMFCPropertyGridProperty* groupDistance	= new CMFCPropertyGridProperty(Language(L"��ͷԶ���ƶ�"));
	groupDistance->AddSubItem(m_cameraEnableDistance	=	AddPropBool(Language(L"����Զ��"), Language(L"m_cameraEnableDistance", L"���þ�ͷ����Զ��")));
	groupDistance->AddSubItem(m_cameraMinDistance		=	AddPropFloat(Language(L"Զ���������(��)"), Language(L"m_cameraMinDistance", L"���þ�ͷԶ���������(��λ����)"), true, 1.0f, 1000.0f, 1.0f));
	groupDistance->AddSubItem(m_cameraDistance		=	AddPropFloat(Language(L"����(��)"), Language(L"m_cameraDistance", L"���þ�ͷ����(��λ����)"), true, 1.0f, 1000.0f, 1.0f));
	groupDistance->AddSubItem(m_cameraMaxDistance		=	AddPropFloat(Language(L"Զ����Զ����(��)"), Language(L"m_cameraMaxDistance", L"���þ�ͷԶ����Զ����(��λ����)"), true, 1.0f, 10000.0f, 1.0f));
	//
	CMFCPropertyGridProperty* groupPos	= new CMFCPropertyGridProperty(Language(L"��ͷλ��"));
	groupPos->AddSubItem(m_cameraTargetX			=	AddPropFloat(Language(L"Ŀ���X"), Language(L"m_cameraTargetX", L"���þ�ͷĿ���X(��λ����)"), true, -1000000.0f, 1000000.0f, 1.0f));
	groupPos->AddSubItem(m_cameraTargetY			=	AddPropFloat(Language(L"Ŀ���Y"), Language(L"m_cameraTargetY", L"���þ�ͷĿ���Y(��λ����)"), true, -1000000.0f, 1000000.0f, 1.0f));
	groupPos->AddSubItem(m_cameraTargetZ			=	AddPropFloat(Language(L"Ŀ���Z"), Language(L"m_cameraTargetZ", L"���þ�ͷĿ���Z(��λ����)"), true, -1000000.0f, 1000000.0f, 1.0f));
	groupPos->AddSubItem(m_cameraEyeX				=	AddPropFloat(Language(L"�ӵ�X"), Language(L"m_cameraEyeX", L"���þ�ͷ�ӵ�X(��λ����)"), true, -1000000.0f, 1000000.0f, 1.0f));
	groupPos->AddSubItem(m_cameraEyeY				=	AddPropFloat(Language(L"�ӵ�Y"), Language(L"m_cameraEyeY", L"���þ�ͷ�ӵ�Y(��λ����)"), true, -1000000.0f, 1000000.0f, 1.0f));
	groupPos->AddSubItem(m_cameraEyeZ				=	AddPropFloat(Language(L"�ӵ�Z"), Language(L"m_cameraEyeZ", L"���þ�ͷ�ӵ�Z(��λ����)"), true, -1000000.0f, 1000000.0f, 1.0f));
	//
	m_cameraProperties.AddProperty(group1);
	m_cameraProperties.AddProperty(groupRot);
	m_cameraProperties.AddProperty(groupMove);
	m_cameraProperties.AddProperty(groupDistance);
	m_cameraProperties.AddProperty(groupPos);
}

VOID		GCSceneEditor3D::InitWaterProperties()
{
	//CMFCPropertyGridProperty* group1		=	new CMFCPropertyGridProperty(Language(L"��������"));
	//group1->AddSubItem(m_waterName			=	AddPropText(Language(L"����"), Language(L"m_waterName", L"���þ�ͷ��������"), false, Name::Length));
	//group1->AddSubItem(m_waterVisible		=	AddPropBool(Language(L"�Ƿ���Ч"), Language(L"m_waterVisible", L"����ѡ��ˮ�����Ч���")));
	//group1->AddSubItem(m_waterColor			=	AddPropColor(Language(L"ˮ����ɫ"), Language(L"m_waterColor", L"����ˮ����ɫ")));
	//group1->AddSubItem(m_waterTexture		=	AddPropFile(Language(L"ˮ���ļ�"), Language(L"m_waterTexture", L"����ˮ���ļ�"), L"*.dds|*.dds||"));
	//group1->AddSubItem(m_waterEdgeAlpha		=	AddPropFloat(Language(L"��Ե�ɼ�����(��λ����)"), Language(L"m_regionWaterEdgeAlpha", L"���ñ�Ե�ɼ�����(��λ����)��"), true, 0.1f, 100.0f));
	////group1->AddSubItem(m_waterEdgeAlpha		=	AddPropButton(Language(L"���¼����Ե͸��"), Language(L"m_waterEdgeAlpha", L"���¼���ѡ������ĸ߶�͸��ֵ")));
	//group1->AddSubItem(m_waterAlpha			=	AddPropFloat(Language(L"͸��ֵ"), Language(L"m_waterAlpha", L"����ˮ��͸��ֵ0��ȫ͸��,1�ǲ�͸��"), 0, 0.0f, 1.0f));
	//group1->AddSubItem(m_waterHeight		=	AddPropFloat(Language(L"ˮ��߶�"), Language(L"m_waterHeight", L"����ˮ��߶�(��λ:��"), true, -1000.0f, 1000.0f, 1.0f));
	////
	//CMFCPropertyGridProperty* groupWave		=	new CMFCPropertyGridProperty(Language(L"��������"));
	//groupWave->AddSubItem(m_waterRotation_1		=	AddPropFloat(Language(L"ˮ����������"), Language(L"m_waterRotation_1", L"ˮ����������[һ��]"), FloatType_Angle, -360.0f, 360.0f, 1.0f));
	//groupWave->AddSubItem(m_waterSpeed_1		=	AddPropFloat(Language(L"ˮ�������ٶ�"), Language(L"m_waterSpeed_1",	 L"ˮ�������ٶ�[һ��]"), false, -100.0f, 100.0f, 1.0f));
	//groupWave->AddSubItem(m_waterRotation_2		=	AddPropFloat(Language(L"ˮ����������[����]"), Language(L"m_waterRotation_2", L"ˮ����������[����]"), FloatType_Angle, -360.0f, 360.0f, 1.0f));
	//groupWave->AddSubItem(m_waterSpeed_2		=	AddPropFloat(Language(L"ˮ�������ٶ�[����]"), Language(L"m_waterSpeed_2",	 L"ˮ�������ٶ�[����]"), false, -100.0f, 100.0f, 1.0f));
	//m_waterRotation_2->Show(false);
	//m_waterSpeed_2->Show(false);
	////
	//groupWave->AddSubItem(m_waterWaveX_1		=	AddPropFloat(Language(L"����X"), Language(L"m_waterWaveX_1", L"����ˮ�涫��������ܶ�"), 0, -100.0f, 100.0f, .1f));
	//groupWave->AddSubItem(m_waterWaveY_1		=	AddPropFloat(Language(L"����Y"), Language(L"m_waterWaveY_1", L"����ˮ���ϱ�������ܶ�"), 0, -100.0f, 100.0f, .1f));
	//groupWave->AddSubItem(m_waterWaveX_2		=	AddPropFloat(Language(L"����X"), Language(L"m_waterWaveX_2", L"����ˮ�涫��������ܶ�"), 0, -100.0f, 100.0f, .1f));
	//groupWave->AddSubItem(m_waterWaveY_2		=	AddPropFloat(Language(L"����Y"), Language(L"m_waterWaveY_2", L"����ˮ���ϱ�������ܶ�"), 0, -100.0f, 100.0f, .1f));
	//m_waterWaveX_2->Show(false);
	//m_waterWaveY_2->Show(false);
	////
	//CMFCPropertyGridProperty* groupR		=	new CMFCPropertyGridProperty(Language(L"��͹����"));
	//groupR->AddSubItem(m_waterReflectBump	=	AddPropFloat(Language(L"���䲨��ǿ��"), Language(L"m_waterReflectBump",		L"����ˮ�潥�����䲨��"), 0,-20.0f, 20.0f, .1f));
	//groupR->AddSubItem(m_waterRefractBump	=	AddPropFloat(Language(L"���䲨��ǿ��"), Language(L"m_waterRefractBump",		L"����ˮ�潥�����䲨��"), 0,-20.0f, 20.0f, .1f));
	//groupR->AddSubItem(m_waterReflectWeight	=	AddPropFloat(Language(L"���䲨��Ȩ��"), Language(L"m_waterReflectWeight",	L"����ˮ�潥������Ȩ��"), 0,-20.0f, 20.0f, .1f));
	////groupR->AddSubItem(m_waterRefractWeight	=	AddPropFloat(Language(L"����Ȩ��"), Language(L"m_waterRefractWeight",	L"����ˮ�潥������Ȩ��"), 0,-20.0f, 20.0f, .1f));
	//groupR->AddSubItem(m_waterFadeBias		=	AddPropFloat(Language(L"�߹�Ȩ��"), Language(L"m_waterFadeBias",		L"����ˮ�潥���߹�Ȩ��"), 0, 0.0f, 100.0f, 0.1f));
	//groupR->AddSubItem(m_waterFadeExponent	=	AddPropFloat(Language(L"ָ��"), Language(L"m_waterFadeExponent",		L"����ˮ�潥��ָ��"), 0, 0.01f, 1000.0f, 0.1f));
	////
	//m_waterProperties.AddProperty(group1);
	//m_waterProperties.AddProperty(groupWave);
	//m_waterProperties.AddProperty(groupR);
	////
}


VOID		GCSceneEditor3D::InitEditorProperties()
{
	CMFCPropertyGridProperty* group1		=	new CMFCPropertyGridProperty(Language(L"��������"));
	group1->AddSubItem(m_editorRadius		=	AddPropFloat(Language(L"�뾶(��)"), Language(L"m_editorRadius", L"�༭�뾶����λ���ף�"), true, 0.1f, 100.0f, 1.0f));
	group1->AddSubItem(m_editorVar			=	AddPropFloat(Language(L"�߶�ֵ"), Language(L"m_editorVar", L"��������λ���ף�"), true, -100.0f, 100.0f, 1.0f));
	group1->AddSubItem(m_editorEnable		=	AddPropBool(Language(L"����"), Language(L"m_editorEnable", L"�Ƿ���Ч������Ч")));
	group1->AddSubItem(m_editorNormalVar	=	AddPropFloat(Language(L"���߱���"), Language(L"m_editorNormalVar", L"���߱�����ֵԽ����Ч��Խ��."), 0, -100.0f, 100.0f, 1.0f));
	group1->AddSubItem(m_editorPower		=	AddPropFloat(Language(L"Ȩ��"), Language(L"m_editorPower", L"��ɢֵ(Ĭ����0.01)"), 0, 0.000001f, 100.0f));
	group1->AddSubItem(m_editorMinValue		=	AddPropFloat(Language(L"͸����Сֵ"), Language(L"m_editorMinValue", L"͸����Сֵ(Ĭ����0)"), 0, 0.000001f, 1.0f));
	group1->AddSubItem(m_editorMaxValue		=	AddPropFloat(Language(L"͸�����ֵ"), Language(L"m_editorMaxValue", L"͸�����ֵ(Ĭ����1)"), 0, 0.000001f, 1.0f));
	group1->AddSubItem(m_editorGrassSelect	=	AddPropOption(Language(L"���б�"), Language(L"m_editorGrassSelect", L"ѡ��һ��������ˢ��������Ҳ����ͨ���ұߵ����б���ѡ��"), g_typeDefault));
	group1->AddSubItem(m_editorColor		=	AddPropColor(Language(L"ˢ��ɫ"), Language(L"m_editorColor", L"����ˢ��ɫ")));
	//
	//m_regionGroup		=	new CMFCPropertyGridProperty(Language(L"��������"));
	//m_regionGroup->AddSubItem(m_regionName			=	AddPropText(Language(L"��������"), Language(L"m_regionName", L"��������"), false, Name::Length));
	//m_regionGroup->AddSubItem(m_regionVisible		=	AddPropBool(Language(L"��ʾ"), Language(L"m_regionVisible", L"��ʾ")));
	//m_regionGroup->AddSubItem(m_regionWater			=	AddPropOption(Language(L"����ˮ��ѡ��"), Language(L"m_regionWater", L"����ˮ��ѡ��"), g_typeDefault));
	//m_regionGroup->AddSubItem(m_regionRebuildHT		=	AddPropButton(Language(L"���¹���߶�ͼ����ɫͼ"), Language(L"m_regionRebuildHT", L"���¹���߶�ͼ����ɫͼ")));
	//
	//m_textureGroup		=	new CMFCPropertyGridProperty(Language(L"��������"));
	//m_textureGroup->AddSubItem(m_textureHighlight	=	AddPropFloat(Language(L"���ȵ���"),		Language(L"m_textureHighlight", L"���ȵ���"), 0, -10.0f, 10.0f));
	//m_textureGroup->AddSubItem(m_textureMipmapBias	=	AddPropFloat(Language(L"Mipmap����"),	Language(L"m_textureMipmapBias", L"Mipmap����"), 0, -10.0f, 10.0f));
	//m_textureGroup->AddSubItem(m_texturePositionX	=	AddPropFloat(Language(L"UVλ��X"),		Language(L"m_texturePositionX", L"UVλ��X"), 0, -100.0f, 100.0f));
	//m_textureGroup->AddSubItem(m_texturePositionY	=	AddPropFloat(Language(L"UVλ��Y"),		Language(L"m_texturePositionY", L"UVλ��Y"), 0, -100.0f, 100.0f));
	//m_textureGroup->AddSubItem(m_textureScalingX	=	AddPropFloat(Language(L"UV����"),		Language(L"m_textureScalingX", L"UV����X"), 0, 0.00001f, 100.0f));
	//m_textureGroup->AddSubItem(m_textureToAll	=	AddPropButton(Language(L"ճ��ͼƬ���������пɼ�����"),	Language(L"m_textureToAll", L"ճ��ͼƬ���������пɼ�����")));
	//m_textureGroup->AddSubItem(m_textureScalingY	=	AddPropFloat(Language(L"UV����Y"),		Language(L"m_textureScalingY", L"UV����Y"), 0, 0.00001f, 100.0f));
	//m_textureGroup->AddSubItem(m_textureRotationZ	=	AddPropFloat(Language(L"UVת��"),		Language(L"m_textureRotationZ", L"UVת��"), FloatType_Angle, -3600.0f, 3600.0f));
	//
	m_editorProperties.AddProperty(group1);
	//m_editorProperties.AddProperty(m_regionGroup);
	//m_editorProperties.AddProperty(m_textureGroup);
}

VOID		GCSceneEditor3D::InitObjectProperties()
{
}

VOID		GCSceneEditor3D::InitTextureProperties()
{
}
VOID		GCSceneEditor3D::InitEnvProperties()
{
	{
		CMFCPropertyGridProperty* group1	= new CMFCPropertyGridProperty(Language(L"��������"));
		group1->AddSubItem(m_envID			=	AddPropInt(Language(L"ID"), Language(L"m_envID", L"����ID,Ψһ")));
		m_envID->AllowEdit(false);
		group1->AddSubItem(m_envName		=	AddPropText(Language(L"��������"), Language(L"m_envName", L"��������"), Name::Length));
		group1->AddSubItem(m_envObjects		=	AddPropInt(Language(L"��Ӱ���������"), Language(L"m_envObjects", L"��������"), 0, 10000000, 1));
		group1->AddSubItem(m_envAmbientColor	=	AddPropColor(Language(L"������ɫ"), Language(L"m_envAmbientColor", L"���û�����ɫ")));
		CMFCPropertyGridProperty* groupFog	= new CMFCPropertyGridProperty(Language(L"������"));
		groupFog->AddSubItem(m_envFogEnable		=	AddPropBool(Language(L"������Ч"), Language(L"m_envFogEnable", L"������Ч")));
		groupFog->AddSubItem(m_envFogMode		=	AddPropOption(Language(L"����"), Language(L"m_envFogMode", L"��������"), g_typeFogMode));
		groupFog->AddSubItem(m_envFogColor	=	AddPropColor(Language(L"����ɫ"), Language(L"m_envFogColor", L"��������ɫ")));
		groupFog->AddSubItem(m_envFogNear	=	AddPropFloat(Language(L"������ɼ�(��)"), Language(L"m_envFogNear", L"����������ɼ�"), true, -1000.0f, 1000.0f, 10.0f));
		groupFog->AddSubItem(m_envFogFar	=	AddPropFloat(Language(L"����Զ�ɼ�(��)"), Language(L"m_envFogFar", L"��������Զ�ɼ�"), true, -10000.0f, 100000.0f, 10.0f));
		CMFCPropertyGridProperty* groupBC	= new CMFCPropertyGridProperty(Language(L"���ȶԱȶ�"));
		groupBC->AddSubItem(m_envBrightnessEnable	=	AddPropBool(Language(L"������Ч"), Language(L"m_envBrightnessEnable", L"������Ч")));
		groupBC->AddSubItem(m_envBrightness	=	AddPropFloat(Language(L"����"), Language(L"m_envBrightness", L"Brightness"), false, -10.0f, 10.0f));
		groupBC->AddSubItem(m_envContrastEnable		=	AddPropBool(Language(L"�Աȶ���Ч"), Language(L"m_envContrast", L"�Աȶ���Ч")));
		groupBC->AddSubItem(m_envContrast	=	AddPropFloat(Language(L"�Աȶ�"), Language(L"m_envContrast", L"Contrast"), false, -10.0f, 10.0f));
		CMFCPropertyGridProperty* groupShadow	= new CMFCPropertyGridProperty(Language(L"��Ӱ����"));
		groupShadow->AddSubItem(m_envShadowEnable	=	AddPropBool(Language(L"��Ӱ����"), Language(L"m_envShadowEnable", L"��Ӱ����")));
		groupShadow->AddSubItem(m_envShadowMapSize	=	AddPropOption(Language(L"��ͼ��С"), Language(L"m_envShadowMapSize", L"��ͼ��С��ͼƬԽ�󾫶�Խ�߿���Խ��"), g_typeShadowMap));
		groupShadow->AddSubItem(m_envShadowBias	=	AddPropFloat(Language(L"��Ӱϵ��"), Language(L"m_envShadowBias", L"��Ӱ����"), false, 0.0f, 100.0f));
		groupShadow->AddSubItem(m_envShadowViewLength	=	AddPropFloat(Language(L"��Ӱ��Χ(��)"), Language(L"m_envShadowViewLength", L"��Ӱ��Χ��������ΧԽ��ɼ���ӰԽ����Ҫ��������Ӱ��Ե���ò��ɼ����⴩��"), true, 1.0f, 100000.0f));
		groupShadow->AddSubItem(m_envShadowDensity	=	AddPropFloat(Language(L"��ӰŨ��"), Language(L"m_envShadowDensity", L"��ӰŨ��"), false, 0.01, 0.99));
		groupShadow->AddSubItem(m_envShadowPCF	=	AddPropOption(Language(L"��Ӱ���˷���"), Language(L"m_envShadowPCF", L"��Ӱ���˷�����ֵԽ������Խ��"), g_typeSoftPCF));
		groupShadow->AddSubItem(m_envTerrainToMap	=	AddPropBool(Language(L"������Ӱ��Ⱦ"), Language(L"m_envTerrainToMap", L"������Ӱ��Ⱦ")));
		groupShadow->AddSubItem(m_envObjectToMap	=	AddPropBool(Language(L"������Ӱ��Ⱦ"), Language(L"m_envObjectToMap", L"������Ӱ��Ⱦ")));
		groupShadow->AddSubItem(m_envTerrainWithMap	=	AddPropBool(Language(L"���ν�����Ӱ"), Language(L"m_envTerrainWithMap", L"���ν�����Ӱ")));
		groupShadow->AddSubItem(m_envObjectWithMap	=	AddPropBool(Language(L"���������Ӱ"), Language(L"m_envObjectWithMap", L"���������Ӱ")));
		groupShadow->AddSubItem(m_envCenterObj		=	AddPropOption(Language(L"��Ӱ���ĵ����"), Language(L"m_envCenterObj", L"��Ӱ���ĵ������Ӱ�����￪ʼ����"), g_typeCenterObj));

		m_envObjects->AllowEdit(false);
		this->m_envProperties.AddProperty(group1);
		this->m_envProperties.AddProperty(groupFog);
		this->m_envProperties.AddProperty(groupBC);
		this->m_envProperties.AddProperty(groupShadow);
	}
	{
		CMFCPropertyGridProperty* group1	= new CMFCPropertyGridProperty(Language(L"��������"));
		group1->AddSubItem(m_regionName			=	AddPropText(Language(L"��������"), Language(L"m_regionName", L"��������"), Name::Length));
		group1->AddSubItem(m_regionNameEnable	=	AddPropBool(Language(L"���������Զ���"), Language(L"m_regionNameEnable", L"���������Զ���")));
		m_regionName->Enable(false);
		m_typeSceneID.AddOption(L"", 0, true);
		if(Phantom::GetGameMgr()->m_tblScene&&Phantom::GetGameMgr()->m_tblCity){
			int scenename = Phantom::GetGameMgr()->m_tblScene->SearchCol("file");
			if(scenename>0){
				int sceneid = 0;
				for(int i=0;i<Phantom::GetGameMgr()->m_tblScene->GetLineCount();i++){
					Phantom::ConfigLine* line = Phantom::GetGameMgr()->m_tblScene->GetLine(i);
					if(stricmp(line->GetTextVal(scenename), m_scene3D->GetFileName().t) == 0)
					{
						sceneid = line->GetLineID();
						break;
					}
				}
				int citysceneid = Phantom::GetGameMgr()->m_tblCity->SearchCol("sceneid");
				if(sceneid>0&&citysceneid>0){
					for(int i=0;i<Phantom::GetGameMgr()->m_tblCity->GetLineCount();i++){
						Phantom::ConfigLine* line = Phantom::GetGameMgr()->m_tblCity->GetLine(i);
						if(line->GetIntVal(citysceneid)==sceneid){
							this->m_typeSceneID.AddOption(Wutf8(line->GetLineName()).buf, line->GetLineID(), 0);
						}
					}
				}
			}
		}
		group1->AddSubItem(m_regionList			=	AddPropOption(Language(L"����ѡ��"), Language(L"m_regionList", L"��region_table.txt�����ѡ������"), m_typeSceneID));
		this->m_regionProperties.AddProperty(group1);
	}
}
VOID		GCSceneEditor3D::InitGrassProperties()
{
	//CMFCPropertyGridProperty* group1	= new CMFCPropertyGridProperty(Language(L"��������"));
	//group1->AddSubItem(m_grassTextureFile	=	AddPropFile(Language(L"�ݵ���ͼ"), Language(L"m_grassTextureFile", L"���òݵ���ͼ"), GetImageFilter()));
	//group1->AddSubItem(m_grassWind			=	AddPropFloat(Language(L"Ʈ������"), Language(L"m_grassWind", L"����Ʈ��Ȧ��"), false, -10, 10));
	//group1->AddSubItem(m_grassMaxVisible	=	AddPropFloat(Language(L"���ɼ�����(��)"), Language(L"m_grassMaxVisible", L"�ݵ����ɼ�����(��)"), true, 1.0f, 1000.0f));
	//group1->AddSubItem(m_grassFromColor		=	AddPropColor(Language(L"�����ʼ��ɫ"), Language(L"m_grassFromColor", L"���������ʼ��ɫ")));
	//group1->AddSubItem(m_grassColor			=	AddPropColor(Language(L"���������ɫ"), Language(L"m_grassColor", L"�������������ɫ")));
	//group1->AddSubItem(m_grassDensity		=	AddPropFloat(Language(L"�ܶ�"), Language(L"m_grassDensity", L"���ò��ܶ�")));
	////
	//group1->AddSubItem(m_grassAlphaBlend	=	AddPropBool(Language(L"��͸����Ⱦ"), Language(L"m_grassAlphaBlend", L"�����Ƿ�͸�������Ⱦ")));
	//group1->AddSubItem(m_grassAlphaMask		=	AddPropFloat(Language(L"���Ȩ��"), Language(L"m_grassAlphaMask", L"�����Ƿ�͸�����Ȩ��"), false, 0, 1));
	////
	//CMFCPropertyGridProperty* grassSize	= new CMFCPropertyGridProperty(Language(L"�ݴ�С"));
	//grassSize->AddSubItem(m_grassAlphaSizeW		=	AddPropFloat(Language(L"���(��)"), Language(L"m_grassAlphaSizeW", L"���òݵĿ�ȣ���λ����"), true, -100.0f, 100.0f));
	//grassSize->AddSubItem(m_grassAlphaSizeH		=	AddPropFloat(Language(L"�߶�(��)"), Language(L"m_grassAlphaSizeH", L"���òݵĸ߶ȣ���λ����"), true, -100.0f, 100.0f));
	////
	//CMFCPropertyGridProperty* groupRect			= new CMFCPropertyGridProperty(Language(L"ͼƬ����"));
	//groupRect->AddSubItem(m_grassTextureLeft	= AddPropInt(Language(L"��"), Language(L"m_grassTextureLeft", L"����ͼƬ��Ч������ߡ�")));
	//groupRect->AddSubItem(m_grassTextureTop		= AddPropInt(Language(L"��"), Language(L"m_grassTextureTop", L"����ͼƬ��Ч�����ϱߡ�")));
	//groupRect->AddSubItem(m_grassTextureWidth	= AddPropInt(Language(L"���"), Language(L"m_grassTextureRight", L"����ͼƬ��Ч�����ȡ�")));
	//groupRect->AddSubItem(m_grassTextureHeight	= AddPropInt(Language(L"�߶�"), Language(L"m_grassTextureHeight", L"����ͼƬ��Ч����߶ȡ�")));
	//groupRect->AddSubItem(m_grassTextureCenterY	= AddPropInt(Language(L"���ĵ�Y"), Language(L"m_grassTextureCenterY", L"�������ĵ�Y��")));
	////
	//this->m_grassProperties.AddProperty(group1);
	//this->m_grassProperties.AddProperty(grassSize);
	//this->m_grassProperties.AddProperty(groupRect);
}

VOID		GCSceneEditor3D::InitUnitProperties()
{
	{
		CMFCPropertyGridProperty* group1	= new CMFCPropertyGridProperty(Language(L"��������"));
		group1->AddSubItem(m_objectFileOpen	=	AddPropButton(Language(L"���ļ�"), Language(L"m_objectFileOpen", L"���ļ�")));
		group1->AddSubItem(m_objectTable	=	AddPropOption(Language(L"��ѡ��"), Language(L"m_objectTable", L"��ѡ�񣬽��˶���ͱ������ݹҹ�"), g_typeDefault));
		group1->AddSubItem(m_objectTableLine	=	AddPropOption(Language(L"��ѡ��"), Language(L"m_objectTableLine", L"��ѡ�񣬽��˶���ͱ��������йҹ�"), g_typeDefault));
		//
		m_objectProperties.AddProperty(group1);
	}
	{
		CMFCPropertyGridProperty* group1	= new CMFCPropertyGridProperty(Language(L"��������"));
		group1->AddSubItem(m_unitID			=	AddPropInt(Language(L"ID"), Language(L"m_unitID", L"����ID,Ψһ")));
		group1->AddSubItem(m_unitNameEnable	=	AddPropBool(Language(L"�Զ�������"), Language(L"m_unitNameEnable", L"�Զ�������")));
		group1->AddSubItem(m_unitName		=	AddPropText(Language(L"����"), Language(L"m_unitName", L"��������"), Name::Length));
		group1->AddSubItem(m_unitPositionX	=	AddPropFloat(Language(L"λ��X(��)"), Language(L"m_unitPositionX", L"λ��X"), true, -1000000.0f, 1000000.0f));
		group1->AddSubItem(m_unitPositionY	=	AddPropFloat(Language(L"λ��Y(��)"), Language(L"m_unitPositionY", L"λ��Y"), true, -1000000.0f, 1000000.0f));
		group1->AddSubItem(m_unitPositionZ	=	AddPropFloat(Language(L"λ��Z(��)"), Language(L"m_unitPositionZ", L"λ��Z"), true, -1000000.0f, 1000000.0f));
		group1->AddSubItem(m_unitScaleFull	=	AddPropFloat(Language(L"��С"), Language(L"m_unitScaleFull", L"���õ�λ��С"), false, 0.001f, 20.0f));
		group1->AddSubItem(m_unitDiffuseIndex	=	AddPropOption(Language(L"���ʷ���"), Language(L"m_unitDiffuseIndex", L"���ʷ���"), g_typeGroupDiffuse));
		group1->AddSubItem(m_unitFileOpen	=	AddPropButton(Language(L"���ļ�"), Language(L"m_unitFileOpen", L"���ļ�")));
		group1->AddSubItem(m_unitEnable		=	AddPropBool(Language(L"�Ƿ���Ч"), Language(L"m_unitEnable", L"���õ�λ��Ч���")));
		group1->AddSubItem(m_unitVisible	=	AddPropBool(Language(L"�Ƿ���ʾ"), Language(L"m_unitVisible", L"���õ�λ��ʾ���")));
		group1->AddSubItem(m_unitAutoHeight	=	AddPropBool(Language(L"�Ƿ��Զ�ȡ�߶�"), Language(L"m_unitAutoHeight", L"�Ƿ��Զ�ȡ�߶�")));
		group1->AddSubItem(m_unitEvents		=	AddPropOption(Language(L"�¼��б�"), Language(L"m_unitEvents", L"�����¼�����"), g_typeTableEvents));
		group1->AddSubItem(m_unitType		=	AddPropText(Language(L"����"), Language(L"m_unitType", L"����")));
		m_unitType->AllowEdit(false);
		group1->AddSubItem(m_unitResetMatrix	=	AddPropButton(Language(L"���û���"), Language(L"m_unitResetMatrix", L"���û�������Ϸ����ģʽ")));
		group1->AddSubItem(m_unitResetToGame	=	AddPropButton(Language(L"���ó���Ϸ����"), Language(L"m_unitResetToGame", L"���ó���Ϸ����,��������������ҽ��仯��Ϊ��Ϸ����ʹ��")));
		//group1->AddSubItem(m_unitRoles		=	AddPropOption(Language(L"��ɫ�б�"), Language(L"m_unitRoles", L"���ý�ɫ�б�"), g_typeTableRoles));
		
		group1->AddSubItem(m_unitRange	=	AddPropFloat(Language(L"Ӱ�췶Χ(��)"), Language(L"m_unitRange", L"Ӱ�췶Χ(��),�ű��ں���affrange"), 0, 0, 20000));
		group1->AddSubItem(m_unitAtkRange	=	AddPropFloat(Language(L"������Χ(��)"), Language(L"m_unitAtkRange", L"������Χ(��),�ű��ں���atkrange"), 0, 0, 20000));
		//group1->AddSubItem(m_unitType	=	AddPropText(Language(L"����"), Language(L"m_unitType", L"��������")));
		//m_unitType->AllowEdit(false);
		//for(int i=0;i<GetSceneObjTypeCount();i++)
			//m_unitType->AddOption(GetSceneObjType(i));
		//
		//group1->AddSubItem(m_unitTableLine	=	AddPropOption(Language(L"��λ��(unit.txt)"), Language(L"m_unitTableLine", L"���õ�λ��"), g_typeDefault));
		//
		//m_unitID->AllowEdit(false);
		m_unitProperties.AddProperty(group1);
	}
}

VOID		GCSceneEditor3D::InitLightProperties()
{
	CMFCPropertyGridProperty* group1	= new CMFCPropertyGridProperty(Language(L"��������"));
	group1->AddSubItem(m_lightName		=	AddPropText(Language(L"����"), Language(L"m_lightName", L"���õƹⷽ������"), false, Name::Length));
	group1->AddSubItem(m_lightType		=	AddPropOption(Language(L"����"), Language(L"m_lightType", L"���õƹ�����"), g_typeLightType));
	group1->AddSubItem(m_lightEnable	=	AddPropBool(Language(L"����"), Language(L"m_lightEnable", L"���õƹ��Ƿ���Ч")));
	group1->AddSubItem(m_lightDiffuse	=	AddPropColor(Language(L"��ɫ"), Language(L"m_lightDiffuse", L"���õƹ���ɫ")));
	group1->AddSubItem(m_lightNear		=	AddPropFloat(Language(L"Ӱ�췶Χ:���(��)"), Language(L"m_lightNear", L"���õƹ�Ӱ�췶Χ���(��λ����)"), true, .1f, 1000000.0f, 1.0f));
	group1->AddSubItem(m_lightFar		=	AddPropFloat(Language(L"Ӱ�췶Χ:��Զ(��)"), Language(L"m_lightFar", L"���õƹ�Ӱ�췶Χ��Զ(��λ����)"), true, .1f, 1000000.0f, 1.0f));
	//
	group1->AddSubItem(m_lightRotX	=	AddPropFloat(Language(L"������ת"), Language(L"m_lightRotX", L"����������ת"), false, 0, 360.0f, 1.0f));
	group1->AddSubItem(m_lightRotY		=	AddPropFloat(Language(L"������ת"), Language(L"m_lightRotY", L"����������ת"), false, 0, 360.0f, 1.0f));
	group1->AddSubItem(m_lightAngleSmall	=	AddPropFloat(Language(L"�۹�Ʒ�Χ:��С�Ƕ�"), Language(L"m_lightAngleSmall", L"���õƹ�۹�Ʒ�Χ:��С�Ƕ�"), false, 0.1f, 359.0f, 1.0f));
	group1->AddSubItem(m_lightAngleBig		=	AddPropFloat(Language(L"�۹�Ʒ�Χ:���Ƕ�"), Language(L"m_lightAngleBig", L"���õƹ�۹�Ʒ�Χ:���Ƕ�"), false, .1f, 359.0f, 1.0f));
	m_lightProperties.AddProperty(group1);
}

VOID		GCSceneEditor3D::InitAnimationProperties()
{
	//CMFCPropertyGridProperty* ani			=	new CMFCPropertyGridProperty(Language(L"��������"));
	//ani->AddSubItem(m_animationName			=	AddPropText(Language(L"����"), Language(L"m_animationName", L"���ö�����������"), false, Name::Length));
	//ani->AddSubItem(m_animationEnable		=	AddPropBool(Language(L"�Ƿ���Ч"), Language(L"m_animationEnable", L"���ö��������Ƿ���Ч")));
	//ani->AddSubItem(m_animationTimeLength	=	AddPropFloat(Language(L"ʱ�䳤��"), Language(L"m_animationTimeLength", L"���ö�������ʱ���ܳ���"), false, 0.1f, 500.0f));
	//ani->AddSubItem(m_animationTimeBegin	=	AddPropFloat(Language(L"��ʼʱ��"), Language(L"m_animationTimeBegin", L"���ö�������ʱ�俪ʼ��"), false, 0.1f, 500.0f));
	////
	//m_animationProperties.AddProperty(ani);
}

VOID		GCSceneEditor3D::InitScaProperties()
{
	//CMFCPropertyGridProperty* ani		=	new CMFCPropertyGridProperty(Language(L"��������"));
	//ani->AddSubItem(m_scaName			=	AddPropText(Language(L"����"), Language(L"m_scaName", L"���õ�λ���Ʒ�������"), false, Name::Length));
	//ani->AddSubItem(m_scaEnable			=	AddPropBool(Language(L"�Ƿ���Ч"), Language(L"m_scaEnable", L"���ÿ����Ƿ���Ч")));
	////
	//m_scaProperties.AddProperty(ani);
}

VOID		GCSceneEditor3D::InitScaTrackProperties()
{
	//CMFCPropertyGridProperty* ani		=	new CMFCPropertyGridProperty(Language(L"��������"));
	//ani->AddSubItem(m_trackName			=	AddPropText(Language(L"����"), Language(L"m_trackName", L"���ÿ���������"), false, Name::Length));
	//ani->AddSubItem(m_trackEnable		=	AddPropBool(Language(L"�Ƿ���Ч"), Language(L"m_trackEnable", L"���ÿ������Ƿ���Ч")));
	//ani->AddSubItem(m_trackUnitSelect		=	AddPropOption(Language(L"���ƶ���ѡ��"), Language(L"m_trackUnitSelect", L"ѡ�������Ƶĵ�λ"), g_typeDefault));
	//ani->AddSubItem(m_trackFrameTimeLength		=	AddPropFloat(Language(L"ʱ�䳤��"), Language(L"m_trackFrameTimeLength", L"ѡ����������ʱ�䳤��"), false, 0.1f, 500.0f));
	//ani->AddSubItem(m_trackBlendTime		=	AddPropFloat(Language(L"���ʱ�䳤��"), Language(L"m_trackBlendTime", L"������������������ʱ��Ļ��ʱ�䳤��"), false, 0.0f, 500.0f));
	////
	//ani->AddSubItem(m_trackScriptEnable	=	AddPropBool(Language(L"�ű���Ч"), Language(L"m_trackScriptEnable", L"���ÿ������ű��Ƿ���Ч�������ڽű��༭����д��ű�")));
	////
	//m_sccPosGroup						=	new CMFCPropertyGridProperty(Language(L"λ������"));
	//m_sccPosGroup->AddSubItem(m_sccPosEnable		=	AddPropBool(Language(L"�Ƿ���Ч"), Language(L"m_sccPosEnable", L"���ÿ�����λ�ñ仯�Ƿ���Ч")));
	//m_sccPosGroup->AddSubItem(m_sccPosLookatTarget=	AddPropBool(Language(L"ʼ�ն�Ŀ���"), Language(L"m_sccPosLookatTarget", L"���ÿ�����ʼ�ն�Ŀ���")));
	//m_sccPosGroup->AddSubItem(m_sccPosMoveSpeed		=	AddPropFloat(Language(L"�ƶ��ٶ�"), Language(L"m_sccPosMoveSpeed", L"���ÿ������ƶ��ٶ�,������ƶ��ٶ��Զ���������ʱ��")));
	////
	//m_sccActionGroup						=	new CMFCPropertyGridProperty(Language(L"��������"));
	//m_sccActionGroup->AddSubItem(m_sccActionEnable			=	AddPropBool(Language(L"�Ƿ���Ч"), Language(L"m_sccActionEnable", L"���ÿ��ƶ����仯�Ƿ���Ч")));
	//m_sccActionGroup->AddSubItem(m_sccActionID		=	AddPropOption(Language(L"����ѡ��"), Language(L"m_sccActionID", L"ѡ�������Ƶĵ�λ����ѡ��"), g_typeDefault));

	//m_sccParentGroup						=	new CMFCPropertyGridProperty(Language(L"���游����"));
	//m_sccParentGroup->AddSubItem(m_sccParentEnable			=	AddPropBool(Language(L"�Ƿ���Ч"), Language(L"m_sccParentEnable", L"���ÿ��Ƹ��������仯�Ƿ���Ч")));
	//m_sccParentGroup->AddSubItem(m_sccParentID		=	AddPropOption(Language(L"�������б�"), Language(L"m_sccParentID", L"ѡ�������Ƶĵ�λ������ѡ��"), g_typeDefault));
	////
	//m_scaTrackProperties.AddProperty(ani);
	//m_scaTrackProperties.AddProperty(m_sccPosGroup);
	//m_scaTrackProperties.AddProperty(m_sccActionGroup);
	//m_scaTrackProperties.AddProperty(m_sccParentGroup);
}

VOID		GCSceneEditor3D::InitSmallMapProperties()
{
}

VOID		GCSceneEditor3D::InitShadowProperties()
{
	//CMFCPropertyGridProperty* adv			=	new CMFCPropertyGridProperty(Language(L"��������"));
	//adv->AddSubItem(m_advancedName			=	AddPropText(Language(L"����"), Language(L"m_advancedName", L"����Ч������"), 0, Name::Length));
	//adv->AddSubItem(m_advancedType			=	AddPropText(Language(L"����"), Language(L"m_advancedType", L"Ч������"), 0, Name::Length));
	//m_advancedType->AllowEdit(false);
	//adv->AddSubItem(m_advancedEnabled		=	AddPropBool(Language(L"�Ƿ���Ч"), Language(L"m_advancedEnabled", L"������Ч��Ч")));
	//adv->AddSubItem(m_advancedTarget		=	AddPropOption(Language(L"������ȾĿ��"), Language(L"m_advancedTarget", L"������ȾĿ��"), g_typeDefault));
	////
	//CMFCPropertyGridProperty* advKey		=	new CMFCPropertyGridProperty(Language(L"�����б�"));
	//for(int i=0;i<MAX_KEY_PARAMETER;i++)
	//{
	//	wchar_t buf[128];
	//	swprintf(buf, L"%d", i + 1);
	//	advKey->AddSubItem(m_advancedKeys[i]	=	AddPropFloat(buf, Language(L"m_advancedKeys", L"���ò���")));
	//	m_advancedKeys[i]->Show(false);
	//}
	//m_advancedProperties.AddProperty(adv);
	//m_advancedProperties.AddProperty(advKey);
}
