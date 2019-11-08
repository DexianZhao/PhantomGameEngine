/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#include "StdAfx.h"
#include "GCViewUIEditor.h"
#include "MainFrm.h"
#include "PropertiesDialogWnd.h"
#include "phantom-gcDoc.h"
#include "phantom-gcView.h"
#include "SetElementTextureDlg.h"
#include "PhantomUIProgress.h"
extern	const wchar_t*	GetElementName(int type, int index);
extern	Phantom::UVAnimation*	GetUVAniByID(Phantom::UIElement* ele, INT nID);


VOID	GCViewUIEditor::LoopAllGroup(ProcGroup3D proc, LPARAM nParameter, LPARAM nParameter2, BOOL bRename, BOOL bGroup)
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
		if(type->type == UI_PROP_GROUP)
		{
			Phantom::UIGroup* g	=	m_dialogPtr->FindGroupPtr(Phantom::PtrID(0, type->p1));
			//
			UndoPtr uptr;
			uptr.buff = AddUndoRedo(GCViewUIEditor::UI_PROP_GROUP, (ProcUndoRedo)proc);
			uptr.urMode = UndoRedoBuffer::URMode_Add;
			uptr.buff->m_id	=	g->GetID();
			//
			(*proc)(g, nParameter, nParameter2, &uptr);
			SetModifyed();
			if(bRename)
				m_treeView.SetItemText(it->first, Wutf8(g->GetName()));
		}
	}
}
#ifdef USE_BOX
VOID	GCViewUIEditor::LoopAllBodys(ProcBox2DBody proc, LPARAM nParameter, LPARAM nParameter2, BOOL bRename)
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
	std::map<int,bool> groups;
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == UI_PROP_B2_BODY)
		{
			Phantom::B2Body* body	=	m_dialogPtr->m_box2World.GetBodyPtr(Phantom::PtrID(0, type->p1));
			if(body)
				(*proc)(body, nParameter, nParameter2);
			SetModifyed();
			if(bRename)
				m_treeView.SetItemText(it->first, W(body->m_bodyData.name.t));
				//m_treeView.SetItemText(it->first, control->GetName());
		}
	}
}

VOID	GCViewUIEditor::LoopAllJoints(ProcBox2DJoint proc, LPARAM nParameter, LPARAM nParameter2, BOOL bRename)
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
	std::map<int,bool> groups;
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == UI_PROP_B2_JOINT)
		{
			Phantom::B2Joint* joint	=	m_dialogPtr->m_box2World.GetJointPtr(Phantom::PtrID(0, type->p1));
			if(joint)
			{
				(*proc)(joint, nParameter, nParameter2);
				if(bRename)
				{
					m_treeView.SetItemText(it->first, W(joint->m_data.name.t));
					this->OnJointMode(joint);
				}
			}
			SetModifyed();
		}
	}
}

VOID	GCViewUIEditor::LoopAllShapes(ProcBox2DShape proc, LPARAM nParameter, LPARAM nParameter2, BOOL bRename)
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
	std::map<int,bool> groups;
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == UI_PROP_B2_SHAPE)
		{
			Phantom::B2Body* body	=	m_dialogPtr->m_box2World.GetBodyPtr(Phantom::PtrID(0, type->p1));
			if(body)
			{
				Phantom::B2Shape* shape	=	body->GetShapePtr(Phantom::PtrID(0, type->p2));
				if(shape)
				{
					(*proc)(body, shape, nParameter, nParameter2);
					if(bRename)
						this->OnShapeMode(shape);
				}
			}
			SetModifyed();
				//m_treeView.SetItemText(it->first, control->GetName());
		}
	}
}
#endif
//typedef	VOID	(*ProcControl3D)(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2);
Phantom::UIControl*	GCViewUIEditor::LoopAllControls(ProcControl3D proc, LPARAM nParameter, LPARAM nParameter2, BOOL bRename, BOOL bGroup, BOOL bControl)
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
	std::map<int,bool> groups;
	Phantom::UIControl* ret = 0;
	this->BeginUndo();
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == UI_PROP_CONTROL)
		{
			Phantom::UIControl* control	=	this->m_dialogPtr->GetControlPtrFromID(type->p1);
			if(bGroup)
				groups[control->GetGroupID()] = true;
			//
			UndoPtr uptr;
			uptr.buff = AddUndoRedo(GCViewUIEditor::UI_PROP_CONTROL, (ProcUndoRedo)proc);
			uptr.urMode = UndoRedoBuffer::URMode_Add;
			uptr.buff->m_id	=	control->GetID();
			//
			(*proc)(control, nParameter, nParameter2, &uptr);
			SetModifyed();
			if(bRename)
				m_treeView.SetItemText(it->first, Wutf8(control->GetName()));
			if(bGroup)
				groups[control->GetGroupID()] = true;
			if(bControl)
				this->RefreshControl(control, it->first);
			ret  = control;
		}
	}
	for(std::map<int,bool>::iterator it = groups.begin(); it != groups.end(); it++)
	{
		RefreshGroup(it->first);
	}
	return ret;
}

Phantom::UIElement*	GCViewUIEditor::LoopAllElements(ProcControlElement3D proc, LPARAM nParameter, LPARAM nParameter2, BOOL bRename)
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
	Phantom::UIElement* ret = 0;
	this->BeginUndo();
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == UI_PROP_ELEMENTS)
		{
			Phantom::UIControl* control	=	this->m_dialogPtr->GetControlPtrFromID(type->p1);
			if(!control)
				continue;
			Phantom::UIElement* e		=	control->GetElementPtr(type->p2);
			if(e)
			{
				//
				UndoPtr uptr;
				uptr.buff = AddUndoRedo(GCViewUIEditor::UI_PROP_ELEMENTS, (ProcUndoRedo)proc);
				uptr.urMode = UndoRedoBuffer::URMode_Add;
				uptr.buff->m_id		=	control->GetID();
				uptr.buff->m_id2	=	type->p2;
				//
				(*proc)(control, e, nParameter, nParameter2, &uptr);
				SetModifyed();
			}
			if(bRename)
				m_treeView.SetItemText(it->first, GetElementName(control->GetType(), type->p2));
			ret = e;
		}
	}
	return ret;
}

VOID	GCViewUIEditor::LoopAllUVAnimations(ProcControlUVAnimation proc, LPARAM nParameter, LPARAM nParameter2, BOOL bRename, BOOL bRebuildUVRects, BOOL bRefreshControl)
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
	std::map<Phantom::UIControl*,HTREEITEM> controls;
	this->BeginUndo();
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == UI_PROP_UV_ANIMATION)
		{
			Phantom::UIControl* control	=	this->m_dialogPtr->GetControlPtrFromID(type->p1);
			if(!control)
				continue;
			Phantom::UIElement* e		=	control->GetElementPtr(type->p2);
			if(e)
			{
				Phantom::UVAnimation* eUV	=	GetUVAniByID(e, type->p3);
				if(eUV)
				{
					//
					UndoPtr uptr;
					uptr.buff = AddUndoRedo(GCViewUIEditor::UI_PROP_UV_ANIMATION, (ProcUndoRedo)proc);
					uptr.urMode = UndoRedoBuffer::URMode_Add;
					uptr.buff->m_id		=	control->GetID();
					uptr.buff->m_id2	=	type->p2;
					uptr.buff->m_id3	=	type->p3;
					//
					(*proc)(control, e, eUV, nParameter, nParameter2, &uptr);
					SetModifyed();
				}
				if(bRename)
				{
					wchar_t buf[256];
					if(control->GetEnableUnitAngle())
						swprintf(buf, L"%s[%s:%s]", Wutf8(eUV->GetName()).buf, g_typeUnitActionType[eUV->GetActionType()], g_type2DUnitAngle[eUV->GetAngle()]);
					else
						wcscpy(buf, Wutf8(eUV->GetName()).buf);
					m_treeView.SetItemText(it->first, buf);
				}
				if(bRefreshControl)
				{
					HTREEITEM hParent	=	m_treeView.GetParentItem(it->first);
					while(hParent)
					{
						TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hParent));
						if(type && type->type == UI_PROP_CONTROL)
						{
							controls[control] = hParent;
							break;
						}
						hParent	=	m_treeView.GetParentItem(hParent);
					}
				}					
				else if(bRebuildUVRects)
					this->RefreshUVRects(control, e, type->p2, eUV, type->p3, it->first);
			}
		}
	}
	if(bRefreshControl)
	{
		for(std::map<Phantom::UIControl*,HTREEITEM>::iterator it = controls.begin(); it != controls.end();it++)
		{
			this->RefreshControl(it->first, it->second);
		}
	}
}

VOID	GCViewUIEditor::LoopAllUVAnimationsR(ProcControlUVAnimationR proc, LPARAM nParameter, LPARAM nParameter2, BOOL bRename)
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
		if(type->type == UI_PROP_UV_ANIMATION_RECT)
		{
			Phantom::UIControl* control	=	this->m_dialogPtr->GetControlPtrFromID(type->p1);
			if(!control)
				continue;
			Phantom::UIElement* e		=	control->GetElementPtr(type->p2);
			if(e)
			{
				Phantom::UVAnimation* eUV	=	GetUVAniByID(e, type->p3);
				if(eUV)
				{
					//
					UndoPtr uptr;
					uptr.buff = AddUndoRedo(GCViewUIEditor::UI_PROP_UV_ANIMATION_RECT, (ProcUndoRedo)proc);
					uptr.urMode = UndoRedoBuffer::URMode_Add;
					uptr.buff->m_id		=	control->GetID();
					uptr.buff->m_id2	=	type->p2;
					uptr.buff->m_id3	=	type->p3;
					uptr.buff->m_id4	=	type->p4;
					//
					(*proc)(control, e, eUV, type->p4, nParameter, nParameter2, &uptr);
					SetModifyed();
				}
				const Phantom::TextureRect* rect	=	eUV->GetTextureRect(type->p4);
				if(bRename && rect)
				{
					char buf[128];
					if(rect->name.t[0])
						strcpy(buf, rect->name.t);
					else
						sprintf(buf, "%d", type->p4);
					m_treeView.SetItemText(it->first, Wutf8(buf));
				}
			}
		}
	}
}

VOID	GCViewUIEditor::LoopAllAnimations(ProcControlAnimation3D proc, LPARAM nParameter, LPARAM nParameter2, BOOL bRename)
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
		if(type->type == UI_PROP_ANIMATION)
		{
			Phantom::UIControl* control	=	this->m_dialogPtr->GetControlPtrFromID(type->p1);
			if(!control)
				continue;
			Phantom::UIAnimationTrack* e		=	control->GetTrackPtr(type->p2);
			if(e)
			{
				//
				UndoPtr uptr;
				uptr.buff = AddUndoRedo(GCViewUIEditor::UI_PROP_ANIMATION, (ProcUndoRedo)proc);
				uptr.urMode = UndoRedoBuffer::URMode_Add;
				uptr.buff->m_id		=	control->GetID();
				uptr.buff->m_id2	=	type->p2;
				uptr.buff->m_id3	=	type->p3;
				uptr.buff->m_id4	=	type->p4;
				//
				(*proc)(control, e, nParameter, nParameter2, &uptr);
				SetModifyed();
			}
			if(bRename)
				m_treeView.SetItemText(it->first, Wutf8(e->GetName()));
		}
	}
}
#ifdef USE_BOX
VOID	Prop_m_body_name(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.name	=	(const char*)nParameter;
}

VOID	Box2DBody_BodyType(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.bodyType	=	nParameter;
}
VOID	Box2DBody_m_body_position_x(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.position.x	=	data->GetWorldPtr()->GetScreenPosSize(Phantom::Pixel(*(float*)nParameter, 0)).x;
}
VOID	Box2DBody_m_body_position_y(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.position.y	=	data->GetWorldPtr()->GetScreenPosSize(Phantom::Pixel(0, *(float*)nParameter)).y;
}
VOID	Box2DBody_m_body_angle(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.angle	=	*(float*)nParameter;
}
VOID	Box2DBody_m_body_linearVelocity_x(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.linearVelocity.x	=	data->GetWorldPtr()->GetScreenPosSize(Phantom::Pixel(*(float*)nParameter, 0)).x;
}
VOID	Box2DBody_m_body_linearVelocity_y(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.linearVelocity.y	=	data->GetWorldPtr()->GetScreenPosSize(Phantom::Pixel(0, *(float*)nParameter)).y;
}
VOID	Box2DBody_m_body_angularVelocity(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.angularVelocity	=	*(float*)nParameter;
}
VOID	Box2DBody_m_body_linearDamping(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.linearDamping	=	*(float*)nParameter;
}
VOID	Box2DBody_m_body_angularDamping(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.angularDamping	=	*(float*)nParameter;
}
VOID	Box2DBody_m_body_gravityScale(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.gravityScale	=	*(float*)nParameter;
}
VOID	Box2DBody_m_body_allowSleep(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.allowSleep	=	nParameter;
}
VOID	Box2DBody_m_body_awake(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.awake	=	nParameter;
}
VOID	Box2DBody_m_body_fixedRotation(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.fixedRotation	=	nParameter;
}
VOID	Box2DBody_m_body_bullet(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.bullet	=	nParameter;
}
VOID	Box2DBody_m_body_active(Phantom::B2Body* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_bodyData.active	=	nParameter;
}

VOID	Box2DShape_m_shape_type(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.type	=	nParameter;
}
VOID	Prop_m_shape_control(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.m_bindControl.id	=	nParameter;
}
VOID	Box2DShape_m_shape_m_density(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.m_density	=	*(float*)nParameter;
}
VOID	Box2DShape_m_shape_m_radius(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.m_radius	=	data->GetWorldPtr()->GetScreenPosSize(Phantom::Pixel(*(float*)nParameter, 0)).x;
}
VOID	Box2DShape_m_shape_m_p_x(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.m_p.x	=	data->GetWorldPtr()->GetScreenPosSize(Phantom::Pixel(*(float*)nParameter, 0)).x;
}
VOID	Box2DShape_m_shape_m_p_y(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.m_p.y	=	data->GetWorldPtr()->GetScreenPosSize(Phantom::Pixel(0, *(float*)nParameter)).y;
}
VOID	Box2DShape_m_shape_m_fAngle(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.m_fAngle	=	*(float*)nParameter;
}
VOID	Box2DShape_m_shape_m_boxWidth(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.m_boxWidth	=	data->GetWorldPtr()->GetScreenPosSize(Phantom::Pixel(*(float*)nParameter, 0)).x;
}
VOID	Box2DShape_m_shape_m_boxHeight(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.m_boxHeight	=	data->GetWorldPtr()->GetScreenPosSize(Phantom::Pixel(0, *(float*)nParameter)).y;
}
VOID	Box2DBody_m_shape_m_bChainLoop(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.m_bChainLoop	=	nParameter;
}
VOID	Box2DBody_m_shape_m_hasVertex0(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.m_hasVertex0	=	nParameter;
}
VOID	Box2DBody_m_shape_m_hasVertex3(Phantom::B2Body* data, Phantom::B2Shape* shape, LPARAM nParameter, LPARAM nParameter2)
{
	shape->m_data.m_hasVertex3	=	nParameter;
}

VOID	Box2DShape_m_joint_jointType(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.jointType	=	nParameter;
}
VOID	Prop_m_joint_name(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.name	=	(const char*)nParameter;
}
VOID	Prop_m_joint_bodyA(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.bodyA	=	nParameter;
}
VOID	Prop_m_joint_bodyB(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.bodyB	=	nParameter;
}
VOID	Prop_m_joint_collideConnected(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.collideConnected	=	nParameter;
}
VOID	Prop_m_joint_localAnchorA_x(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.localAnchorA.x	=	data->GetWorldPtr()->GetScreenPosX((*(float*)nParameter));
}
VOID	Prop_m_joint_localAnchorA_y(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.localAnchorA.y	=	data->GetWorldPtr()->GetScreenPosY((*(float*)nParameter));
}
VOID	Prop_m_joint_localAnchorB_x(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.localAnchorB.x	=	data->GetWorldPtr()->GetScreenPosX((*(float*)nParameter));
}
VOID	Prop_m_joint_localAnchorB_y(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.localAnchorB.y	=	data->GetWorldPtr()->GetScreenPosY((*(float*)nParameter));
}
VOID	Prop_m_joint_maxForce(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.maxForce	=	*(float*)nParameter;
}
VOID	Prop_m_joint_maxTorque(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.maxTorque	=	*(float*)nParameter;
}
VOID	Prop_m_joint_joint1(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.joint1	=	nParameter;
}
VOID	Prop_m_joint_joint2(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.joint2	=	nParameter;
}
VOID	Prop_m_joint_ratio(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.ratio	=	*(float*)nParameter;
}
VOID	Prop_m_joint_target_x(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.target.x	=	*(float*)nParameter;
}
VOID	Prop_m_joint_target_y(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.target.y	=	*(float*)nParameter;
}
VOID	Prop_m_joint_frequencyHz(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.frequencyHz	=	*(float*)nParameter;
}
VOID	Prop_m_joint_localAxisA_x(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.localAxisA.x	=	*(float*)nParameter;
}
VOID	Prop_m_joint_localAxisA_y(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.localAxisA.y	=	*(float*)nParameter;
}
VOID	Prop_m_joint_referenceAngle(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.referenceAngle	=	*(float*)nParameter;
}
VOID	Prop_m_joint_enableLimit(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.enableLimit	=	nParameter;
}
VOID	Prop_m_joint_lowerTranslation(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.lowerTranslation	=	*(float*)nParameter;
}
VOID	Prop_m_joint_upperTranslation(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.upperTranslation	=	*(float*)nParameter;
}
VOID	Prop_m_joint_enableMotor(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.enableMotor	=	nParameter;
}
VOID	Prop_m_joint_maxMotorForce(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.maxMotorForce	=	*(float*)nParameter;
}
VOID	Prop_m_joint_motorSpeed(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.motorSpeed	=	*(float*)nParameter;
}
VOID	Prop_m_joint_groundAnchorA_x(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.groundAnchorA.x	=	*(float*)nParameter;
}
VOID	Prop_m_joint_groundAnchorA_y(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.groundAnchorA.y	=	*(float*)nParameter;
}
VOID	Prop_m_joint_groundAnchorB_x(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.groundAnchorB.x	=	*(float*)nParameter;
}
VOID	Prop_m_joint_groundAnchorB_y(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.groundAnchorB.y	=	*(float*)nParameter;
}
VOID	Prop_m_joint_lengthA(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.lengthA	=	*(float*)nParameter;
}
VOID	Prop_m_joint_lengthB(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.lengthB	=	*(float*)nParameter;
}
VOID	Prop_m_joint_lowerAngle(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.lowerAngle	=	*(float*)nParameter;
}
VOID	Prop_m_joint_upperAngle(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.upperAngle	=	*(float*)nParameter;
}
VOID	Prop_m_joint_maxMotorTorque(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.maxMotorTorque	=	*(float*)nParameter;
}
VOID	Prop_m_joint_maxLength(Phantom::B2Joint* data, LPARAM nParameter, LPARAM nParameter2)
{
	data->m_data.maxLength	=	*(float*)nParameter;
}
#endif
VOID	ProcControl3D_ToolTip(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2)
{
	//data->SetToolTipText((const wchar_t*)nParameter);
}

VOID	ProcControl3D_ToolTipPopup(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2)
{
	//data->SetToolTipPopupType(nParameter);
}


VOID	ProcControl3D_ControlName(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, data->GetName(), Autf8((const wchar_t*)nParameter).buf);
	GCViewUIEditor* edview = static_cast<GCViewUIEditor*>(GCViewBase::s_currView);
	HTREEITEM hItem = edview->FindTreeItem(edview->m_hViewItem, GCViewUIEditor::UI_PROP_CONTROL, data->GetID());
	if(hItem)
		edview->GetTreeView()->SetItemText(hItem, Wutf8(temp.t));
	//
	data->SetName(temp);
}
VOID ProcControl3D_ControlRectLeft(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	data->GetRenderRect();
	int width	=	rc.GetWidth();
	IF_ADD(){
		rc.left		=	nParameter;
		rc.right	=	rc.left + width;
	}
	ADD_UR(Phantom::Rect, data->GetRenderRect(), rc);
	data->SetRenderRect(temp);
}
VOID ProcControl3D_ControlRectTop(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	data->GetRenderRect();
	int height	=	rc.GetHeight();
	IF_ADD(){
		rc.top		=	nParameter;
		rc.bottom	=	rc.top + height;
	}
	ADD_UR(Phantom::Rect, data->GetRenderRect(), rc);
	data->SetRenderRect(temp);
}
VOID ProcControl3D_ControlRectWidth(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	data->GetRenderRect();
	int oldW	=	rc.GetWidth();
	if(oldW<1)oldW=1;
	IF_ADD(){
		rc.right	=	rc.left + nParameter;
	}
	ADD_UR(Phantom::Rect, data->GetRenderRect(), rc);
	data->SetRotCenter(Phantom::Pixel(data->GetRotCenter().x*temp.GetWidth()/oldW, data->GetRotCenter().y));
	data->SetRenderRect(temp);
}
VOID ProcControl3D_ControlRectHeight(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	data->GetRenderRect();
	int oldH	=	rc.GetHeight();
	if(oldH<1)oldH=1;
	IF_ADD(){
		rc.bottom	=	rc.top + nParameter;
	}
	ADD_UR(Phantom::Rect, data->GetRenderRect(), rc);
	data->SetRotCenter(Phantom::Pixel(data->GetRotCenter().x, data->GetRotCenter().y*temp.GetHeight()/oldH));
	data->SetRenderRect(temp);
}
VOID ProcControl3D_ControlScale(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	data->GetRenderRect();
	int oldW	=	rc.GetWidth();
	int oldH	=	rc.GetHeight();
	IF_ADD(){
		float fWidth	=	(float)data->GetElementPtr(0)->GetSourceRect().GetWidth();
		float fHeight	=	(float)data->GetElementPtr(0)->GetSourceRect().GetHeight();
		rc.right	=	rc.left + (int)(fWidth * *(float*)nParameter);
		rc.bottom	=	rc.top + (int)(fHeight * *(float*)nParameter);
	}
	ADD_UR(Phantom::Rect, data->GetRenderRect(), rc);
	int newW	=	temp.GetWidth();
	int newH	=	temp.GetHeight();
	data->SetRotCenter(Phantom::Pixel(data->GetRotCenter().x*newW/oldW, data->GetRotCenter().y*newH/oldH));
	data->SetRenderRect(temp);
}

VOID ProcControl3D_ControlAlignMode(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	int align = 0;
	IF_ADD(){
		if(nParameter == 1)
			align |= 0x01;
		else if(nParameter == 2)
			align |= 0x02;
		else if(nParameter == 3)
			align |= 0x04;
		else if(nParameter == 4)
			align |= 0x08;
		if(nParameter2 == 1)
			align |= 0x10;
		else if(nParameter2 == 2)
			align |= 0x20;
		else if(nParameter2 == 3)
			align |= 0x40;
		else if(nParameter2 == 4)
			align |= 0x80;
	}
	ADD_UR(int, data->m_nAlignMode, align);
	data->m_nAlignMode = temp;
}

VOID ProcControl3D_ControlOnLua(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetVisibleOnScript(), nParameter);
	data->SetVisibleOnScript(temp);
}

VOID ProcControl3D_GroupID(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetGroupID(), nParameter);
	data->SetGroupID(temp);
}

VOID ProcControl3D_MoveDialog(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetParentMove(), nParameter);
	data->SetParentMove(temp != 0);
}

VOID ProcControl3D_Background(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_bIsBackground, nParameter);
	data->SetBackground(temp != 0);
}
VOID ProcControl3D_Layer(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetLayer(), nParameter);
	data->SetLayer(temp);
}
VOID ProcControl3D_IsGrid(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_bIsGridObject, nParameter);
	data->m_bIsGridObject = temp;
}
VOID ProcControl3D_GridOffset(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_sGridOffsetY, nParameter);
	data->m_sGridOffsetY = temp;
}
VOID ProcControl3D_Context(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//data->SetContext(nParameter);
}
VOID ProcControl3D_TextAlignLR(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	unsigned int n	=	data->GetTextFormat();
	IF_ADD(){
		n	^=	(n & (DT_LEFT | DT_CENTER | DT_RIGHT));
		n	|=	nParameter;
	}
	ADD_UR(unsigned int, data->GetTextFormat(), n);
	data->SetTextFormat(temp);
}

VOID ProcControl3D_TextAlignTB(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	unsigned int n	=	data->GetTextFormat();
	IF_ADD(){
	n	^=	(n & (DT_TOP | DT_VCENTER | DT_BOTTOM));
	n	|=	nParameter;
	if(n & DT_VCENTER)
		n	|=	DT_SINGLELINE;
	else if(n & DT_SINGLELINE)
		n ^= DT_SINGLELINE;
	}
	ADD_UR(unsigned int, data->GetTextFormat(), n);
	//n	|=	DT_EXPANDTABS;
	data->SetTextFormat(temp);
}

VOID ProcControl3D_Visible(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetVisible(), nParameter);
	data->SetVisible(temp != 0);
}

VOID ProcControl3D_CanActive(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetCanFocus(), nParameter);
	data->SetCanFocus(temp != 0);
}

VOID ProcControl3D_Enable(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetEnabled(), nParameter);
	data->SetEnabled(temp != 0);
}

VOID ProcControl3D_Select(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_bSelect, nParameter);
	data->m_bSelect = (temp != 0);
}

VOID ProcControl3D_AniCenter(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_bAniCenter, nParameter);
	data->m_bAniCenter = temp != 0;
}

VOID ProcControl3D_EnableImgText(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsEnableUseImageText(), nParameter);
	data->EnableUseImageText(temp != 0);
}

VOID ProcControl3D_ImgTextBegin(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, data->m_szNumberBegin, (const char*)nParameter);
	strcpy(data->m_szNumberBegin, temp);
}
VOID ProcControl3D_ImgSizeAdd(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_numberSizeAdd, nParameter);
	data->m_numberSizeAdd = clamp(temp, -100, 100);
}
VOID ProcControl3D_ShadowWidth(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//data->ShowTextShadow(nParameter);
}

VOID ProcControl3D_ShadowColor(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
//	Phantom::color4 c(data->GetShadowColor());
//	data->SetShadowColor(Phantom::color4(nParameter, c.a));
}

VOID ProcControl3D_ShadowColorA(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//Phantom::color4 c(data->GetShadowColor());
	//c.a	=	*(float*)nParameter;
	//data->SetShadowColor(c);
}

VOID ProcControl3D_ControlText(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(NameT<1024>, data->GetText(), Autf8((const wchar_t*)nParameter).buf);
	data->SetText(temp);
}

VOID ProcControl3D_TextColor(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(Phantom::color4, data->GetTextColor(), Phantom::color4(nParameter, data->GetTextColor().a));
	data->SetTextColor(temp);
	data->SetText(data->GetText());
}
VOID ProcControl3D_SingleLine(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	unsigned int n	=	data->GetTextFormat();
	IF_ADD(){
	n	^=	(n & DT_SINGLELINE);
	n	|=	nParameter;
	}
	ADD_UR(int, data->GetTextFormat(), n);
	data->SetTextFormat(temp);
}
VOID ProcControl3D_ImageFont(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_bUseImageFont, nParameter);
	data->m_bUseImageFont = temp;
	data->OnChangeText();
}

VOID ProcControl3D_TextureColor(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(Phantom::color4, data->GetTextureColor(), Phantom::color4(nParameter, data->GetTextureColor().a));
	data->SetTextureColor(temp);
}

VOID ProcControl3D_DisableColor(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
}
VOID ProcControl3D_TextAlpha(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::color4 c	=	data->GetTextColor();
	IF_ADD(){
	c.a	=	*(float*)nParameter;
	}
	ADD_UR(Phantom::color4, data->GetTextColor(), c);
	data->SetTextColor(temp);
}

VOID ProcControl3D_TextureAlpha(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::color4 c	=	data->GetTextureColor();
	IF_ADD(){
	c.a	=	*(float*)nParameter;
	}
	ADD_UR(Phantom::color4, data->GetTextureColor(), c);
	data->SetTextureColor(temp);
}

VOID ProcControl3D_TabIndex(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetTabIndex(), nParameter);
	data->SetTabIndex(temp);
}

VOID ProcControl3D_CursorName(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//data->SetCursorName(A((const wchar_t*)nParameter));
}
VOID ProcControl3D_GroupCenter(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::UIGroup* g = data->GetGroupPtr();
	for(int i=0;i<g->GetControlCount();i++){
		if(g->GetControlPtr(i))
			g->GetControlPtr(i)->m_bIsGroupCenter = 0;
	}
	ADD_UR(int, data->m_bIsGroupCenter, nParameter);
	data->m_bIsGroupCenter = temp;
}
VOID ProcControl3D_Rotation(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsRotation(), nParameter);
	data->SetRotation(temp != 0, data->GetRotationAngle());
}
VOID ProcControl3D_Pixel(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsPickPixel(), nParameter);
	data->SetPickPixel(temp);
}

VOID ProcControl3D_Parent(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetParentControlID(), ((Phantom::UIControl*)nParameter)->GetID());
	data->SetParentControlID(temp);
}

VOID ProcControl3D_RotationAngle(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->GetRotationAngle(), *(float*)nParameter);
	data->SetRotation(data->IsRotation(), temp);
}

VOID ProcControl3D_CenterX(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Pixel pt	=	data->GetRotCenter();
	IF_ADD(){
		pt.x	=	nParameter;
	}
	ADD_UR(Phantom::Pixel, data->GetRotCenter(), pt);
	data->SetRotCenter(temp);
}

VOID ProcControl3D_CenterY(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Pixel pt	=	data->GetRotCenter();
	IF_ADD(){
		pt.y	=	nParameter;
	}
	ADD_UR(Phantom::Pixel, data->GetRotCenter(), pt);
	data->SetRotCenter(temp);
}
VOID ProcEdit3D_Password(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UITextBox*>(data)->m_bPassword, nParameter);
	static_cast<Phantom::UITextBox*>(data)->m_bPassword = (temp != 0);
}

VOID ProcEdit3D_EnableIME(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//static_cast<Phantom::UITextBox*>(data)->EnableIME(nParameter != 0);
}

VOID ProcEdit3D_ReadOnly(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetReadOnly(), nParameter);
	data->SetReadOnly(temp != 0);
}

VOID ProcEdit3D_Indicator(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//static_cast<Phantom::UITextBox*>(data)->SetRenderIndicator(nParameter != 0);
}

VOID ProcEdit3D_SBWidth(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetScrollBarWidth(), nParameter);
	data->SetScrollBarWidth(temp);
}

VOID ProcEdit3D_CandList(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//static_cast<Phantom::UITextBox*>(data)->SetRenderCandList(nParameter != 0);
}

VOID ProcEdit3D_BorderWidth(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//static_cast<Phantom::UITextBox*>(data)->SetRenderBorder(nParameter > 0);
	//static_cast<Phantom::UITextBox*>(data)->SetBorderWidth(nParameter);
}

VOID ProcEdit3D_CaretColor(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//static_cast<Phantom::UITextBox*>(data)->SetCaretColor(Phantom::color4(nParameter, 1.0f));
}

VOID ProcEdit3D_SelectTextColor(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//static_cast<Phantom::UITextBox*>(data)->SetSelectedTextColor(Phantom::color4(nParameter, 1.0f));
}

VOID ProcEdit3D_SelectBackColor(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//static_cast<Phantom::UITextBox*>(data)->SetSelectedBackColor(Phantom::color4(nParameter, 1.0f));
}

VOID ProcProgress3D_Mode(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetProgressType(), nParameter);
	data->SetProgressType(temp);
}

VOID ProcProgress3D_Value(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->GetProgressValue(), *(float*)nParameter);
	data->SetProgressValue(temp);
}

VOID ProcProgress3D_Size(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UIProgress*>(data)->m_chInnerSize, nParameter);
	static_cast<Phantom::UIProgress*>(data)->m_chInnerSize = temp;
}
VOID ProcCombo3D_DropHeight(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UIComboBox*>(data)->GetDropHeight(), nParameter);
	static_cast<Phantom::UIComboBox*>(data)->SetDropHeight(temp);
}

VOID ProcCombo3D_SBWidth(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
}

VOID ProcCombo3D_Values(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	std::vector<std::wstring>* list = (std::vector<std::wstring>*)nParameter;
	static_cast<Phantom::UIComboBox*>(data)->RemoveAllItems();
	for(int i=0;i<list->size();i++)
	{
		static_cast<Phantom::UIComboBox*>(data)->AddItem(Autf8(list->at(i).c_str()), 0);
	}
}

VOID ProcFormat_EventColor(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
//	data->GetFormatEditBox()->SetEventColor(Phantom::color4(nParameter, 1.0f));
}

VOID ProcFormat_SelectColor(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
//	data->GetFormatEditBox()->SetSelectColor(Phantom::color4(nParameter, 1.0f));
}

VOID ProcFormat_LineHeight(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
//	data->GetFormatEditBox()->SetLineSpacingHeight(nParameter);
}

VOID ProcListBox_LineHeight(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UIListBox*>(data)->GetLineHeight(), nParameter);
	static_cast<Phantom::UIListBox*>(data)->SetLineHeight(temp);
}

VOID ProcListBox_SBWidth(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
}

VOID ProcListBox_TextLeft(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UIListBox*>(data)->GetLineTextFirst(), nParameter);
	static_cast<Phantom::UIListBox*>(data)->SetLineTextFirst(temp);
}

VOID ProcListBox_Values(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	std::vector<std::wstring>* list = (std::vector<std::wstring>*)nParameter;
	static_cast<Phantom::UIListBox*>(data)->RemoveAllItems();
	for(int i=0;i<list->size();i++)
	{
		static_cast<Phantom::UIListBox*>(data)->AddItem(Autf8(list->at(i).c_str()), 0);
	}
}

VOID ProcListCtrl_LineHeight(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UIListCtrl*>(data)->GetLineHeight(), nParameter);
	static_cast<Phantom::UIListCtrl*>(data)->SetLineHeight(temp);
}

VOID ProcListCtrl_ColumnHeight(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UIListCtrl*>(data)->GetColumnHeight(), nParameter);
	static_cast<Phantom::UIListCtrl*>(data)->SetColumnHeight(temp);
}

VOID ProcListCtrl_SBWidth(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
}

VOID ProcListCtrl_TextLeft(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UIListCtrl*>(data)->GetLineTextFirst(), nParameter);
	static_cast<Phantom::UIListCtrl*>(data)->SetLineTextFirst(temp);
}

VOID ProcListCtrl_SortEnable(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UIListCtrl*>(data)->IsSortEnable(), nParameter);
	static_cast<Phantom::UIListCtrl*>(data)->SetSortEnable(temp);
}

VOID ProcListCtrl_ColumnValues(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	std::vector<std::wstring>* list = (std::vector<std::wstring>*)nParameter;
	static_cast<Phantom::UIListCtrl*>(data)->RemoveAllColumn();
	for(int i=0;i<list->size();i++)
	{
		wchar_t* str	=	(wchar_t*)list->at(i).c_str();
		int width	=	50;
		while(*str != 0)
		{
			if(*str == '|')
			{
				*str	=	0;
				width	=	_wtoi(str + 1);
				break;
			}
			str++;
		}
		static_cast<Phantom::UIListCtrl*>(data)->InsertColumn(Autf8(list->at(i).c_str()).buf, width);
	}
}

VOID ProcListCtrl_Values(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	std::vector<std::wstring>* list = (std::vector<std::wstring>*)nParameter;
	static_cast<Phantom::UIListCtrl*>(data)->RemoveAllItems();
	for(int i=0;i<list->size();i++)
	{
		int index	=	static_cast<Phantom::UIListCtrl*>(data)->InsertItem(i, "", 0);
		wchar_t* str	=	(wchar_t*)list->at(i).c_str();
		wchar_t* lastStr	=	str;
		int width	=	50;
		int column	=	0;
		while(*str != 0)
		{
			if(*str == '|')
			{
				*str	=	0;
				static_cast<Phantom::UIListCtrl*>(data)->SetItemText(index, column, Autf8(lastStr).buf);
				lastStr	=	str + 1;
				column++;
			}
			str++;
		}
	}
}

VOID ProcCheckBox_Checked(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetChecked(), nParameter);
	data->SetChecked(temp != 0);
}

VOID ProcEffect_FrameCount(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UIEffect*>(data)->GetFrameCount(), nParameter);
	static_cast<Phantom::UIEffect*>(data)->SetFrameCount(temp);
}

VOID ProcEffect_LoopCount(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UIEffect*>(data)->GetLoopCount(), nParameter);
	static_cast<Phantom::UIEffect*>(data)->SetLoopCount(temp);
}

VOID ProcEffect_PlaySpeed(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->GetPlaySpeed(), *(float*)nParameter);
	data->SetPlaySpeed(temp);
}

VOID PropStatic_BorderWidth(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, static_cast<Phantom::UIStatic*>(data)->GetBorderWidth(), nParameter);
	static_cast<Phantom::UIStatic*>(data)->SetBorderWidth(temp);
}

VOID ProcButton_ClickSound(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, data->GetSoundPlayID(Phantom::UISoundPlay_buttonDown), (nParameter ? Autf8((const wchar_t*)nParameter) : ""));
	data->SetSoundPlayID(Phantom::UISoundPlay_buttonDown, temp);
}
VOID PropStatic_MouseSrcBlend(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//data->SetMouseEnterSrc((Phantom::BlendMode)nParameter);
}
VOID PropStatic_MouseEnable(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//data->SetMouseEnterEffect(nParameter);
}
VOID PropStatic_MouseDestBlend(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//data->SetMouseEnterDest((Phantom::BlendMode)nParameter);
}
VOID PropStatic_TextureColor(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::color4 c	=	data->m_textureColor;//GetMouseEnterColor();
	IF_ADD(){
		c.from(nParameter, c.a);
	}
	ADD_UR(Phantom::color4, data->m_textureColor, c);
	data->m_textureColor = temp;
}
VOID PropStatic_TextureAlpha(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::color4 c	=	data->m_textureColor;
	IF_ADD(){
		c.a	=	*(float*)nParameter;
	}
	ADD_UR(Phantom::color4, data->m_textureColor, c);
	data->m_textureColor = temp;
}

VOID ProcButton_MouseMoveSound(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, data->GetSoundPlayID(Phantom::UISoundPlay_mouseIn), (nParameter ? Autf8((const wchar_t*)nParameter) : ""));
	data->SetSoundPlayID(Phantom::UISoundPlay_mouseIn, temp);
}

VOID ProcButton_ButtonType(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetButtonType(), nParameter);
	data->SetButtonType((Phantom::UIButtonType)temp);
}

VOID ProcControl_DrawFocusFrame(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsDrawFocusFrame(), nParameter);
	data->DrawFocusFrame(temp);
}

VOID ProcControl_SleepTime(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, data->GetSleepTime(), *(float*)nParameter);
	data->SetSleepTime(temp);
}

VOID ProcControl_Angle8(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetEnableUnitAngle(), nParameter);
	data->SetEnableUnitAngle(temp);
}

VOID ProcControl_Font(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	INT nFont = 0;
	IF_ADD(){
		FontNode2D* node	=	(FontNode2D*)nParameter;
		nFont	=	Phantom::GetDlgManager()->AddFont(node->fontName.t, node->nFontHeight, node->nWeight, node->bItalic, node->bUnderline);
	}
	ADD_UR(int, data->GetElementPtr(0)->GetFontID(), nFont);
	for(int i=0;i<data->GetElementCount();i++)
		data->GetElementPtr(i)->SetFontID(temp);
	data->SetText(data->GetText());
}

VOID ProcControl_AutoSort(Phantom::UIControl* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetAutoSort(), nParameter);
	data->SetAutoSort(temp);
}

VOID ProcElement_ImageSet(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	const char* szMode = element->m_textureMode.t;
	char buf[128];
	if(szMode)
		strcpy(buf, szMode);
	ADD_UR(FileName, element->GetTexture(), Autf8((const wchar_t*)nParameter).buf);
	element->SetTexture(temp);
	if(szMode)
		element->SetTextureMode(buf);
	//element->SetSourceRect(Phantom::Rect(0,0,-1,-1));
}

VOID ProcElement_ImageName(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	//element->SetElementName((const wchar_t*)nParameter);
}

VOID ProcElement_ImageUnitSide(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	data->GetWindowRect();
	rc.right	=	rc.left + element->GetSourceRect().GetWidth();
	rc.bottom	=	rc.top + element->GetSourceRect().GetHeight();
	const Phantom::TextureRect* prc	=	Phantom::GetDlgManager()->GetTextureRect(element->GetTextureID(), element->m_textureMode.t);
	if(prc)
	{
		rc.right	=	prc->orig.cx + rc.left;
		rc.bottom	=	prc->orig.cy + rc.top;
	}
	ADD_UR(Phantom::Rect, data->GetWindowRect(), rc);
	data->SetWindowRect(temp);
	//element->SetUnitRenderSide((UnitRenderSide)nParameter);
}

VOID ProcElement_ImageClear(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetTextureID(), -1);
	element->SetTextureID(temp);
}

VOID ProcElement_ImageOpen(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::TextureNode2D* node	=	Phantom::GetDlgManager()->GetTextureNode(element->GetTextureID());
	if(node)
	{
		char drive[256], dir[256];
		_splitpath(data->GetDialogPtr()->m_strFile.t, drive, dir, 0, 0);
		strcat(drive, dir);
		SetCurrentDirectory(W(drive));
		AfxGetApp()->OpenDocumentFile(Wutf8(node->fileName.t).buf);
	}
}

VOID ProcElement_ImageDefault(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->m_bNoTexture, nParameter);
	element->m_bNoTexture = temp;
}

VOID ProcElement_ImageScale(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetRenderScale(), nParameter != 0);
	element->SetRenderScale(temp, element->GetRenderScaleAsWrap(), element->GetWrapWidth());
}

VOID ProcElement_ImageContScale(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetRenderScaleAsWrap(), nParameter != 0);
	element->SetRenderScale(element->GetRenderScale(), temp, element->GetWrapWidth());
}

VOID ProcElement_ImageContW(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Pixel p	=	element->GetWrapWidth();
	p.x	=	nParameter;
	ADD_UR(Phantom::Pixel, element->GetWrapWidth(), p);
	element->SetRenderScale(element->GetRenderScale(), element->GetRenderScaleAsWrap(), temp);
}

VOID ProcElement_ImageContH(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Pixel p	=	element->GetWrapWidth();
	p.y	=	nParameter;
	ADD_UR(Phantom::Pixel, element->GetWrapWidth(), p);
	element->SetRenderScale(element->GetRenderScale(), element->GetRenderScaleAsWrap(), temp);
}

VOID ProcElement_ImageTileW(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetTileWidth(), nParameter);
	element->SetTileWidth(temp);
}

VOID ProcElement_ImageTileH(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetTileHeight(), nParameter);
	element->SetTileHeight(temp);
}

VOID ProcElement_ImageTileOffX(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->m_nTileOffX, nParameter);
	element->m_nTileOffX = (temp);
}

VOID ProcElement_ImageTileOffY(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->m_nTileOffY, nParameter);
	element->m_nTileOffY = (temp);
}
VOID ProcElement_ImageTileScaleX(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, element->m_nTileScaleX, *(float*)nParameter);
	element->m_nTileScaleX = (temp);
}

VOID ProcElement_ImageTileScaleY(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, element->m_nTileScaleY, *(float*)nParameter);
	element->m_nTileScaleY = (temp);
}


VOID ProcElement_ImageTileLX(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->m_tileXieJiao, nParameter);
	element->m_tileXieJiao = temp;
}
VOID ProcElement_ImageRectLeft(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	element->GetSourceRect();
	int width	=	rc.GetWidth();
	rc.left		=	nParameter;
	rc.right	=	rc.left + width;
	ADD_UR(Phantom::Rect, element->GetSourceRect(), rc);
	element->SetSourceRect(temp);
}
VOID ProcElement_ImageRectTop(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	element->GetSourceRect();
	int height	=	rc.GetHeight();
	rc.top		=	nParameter;
	rc.bottom	=	rc.top + height;
	ADD_UR(Phantom::Rect, element->GetSourceRect(), rc);
	element->SetSourceRect(temp);
}
VOID ProcElement_ImageRectWidth(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	element->GetSourceRect();
	rc.right	=	rc.left + nParameter;
	ADD_UR(Phantom::Rect, element->GetSourceRect(), rc);
	element->SetSourceRect(temp);
}
VOID ProcElement_ImageRectHeight(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	element->GetSourceRect();
	rc.bottom	=	rc.top + nParameter;
	ADD_UR(Phantom::Rect, element->GetSourceRect(), rc);
	element->SetSourceRect(temp);
}

VOID ProcElement_ImageRectOffsetLeft(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	element->GetRectOffset();
	int width	=	rc.GetWidth();
	rc.left		=	nParameter;
	rc.right	=	rc.left + width;
	ADD_UR(Phantom::Rect, element->GetRectOffset(), rc);
	element->SetRectOffset(temp);
}
VOID ProcElement_ImageRectOffsetTop(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	element->GetRectOffset();
	int height	=	rc.GetHeight();
	rc.top		=	nParameter;
	rc.bottom	=	rc.top + height;
	ADD_UR(Phantom::Rect, element->GetRectOffset(), rc);
	element->SetRectOffset(temp);
}
VOID ProcElement_ImageRectOffsetWidth(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	element->GetRectOffset();
	rc.right	=	rc.left + nParameter;
	ADD_UR(Phantom::Rect, element->GetRectOffset(), rc);
	element->SetRectOffset(temp);
}
VOID ProcElement_ImageRectOffsetHeight(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc	=	element->GetRectOffset();
	rc.bottom	=	rc.top + nParameter;
	ADD_UR(Phantom::Rect, element->GetRectOffset(), rc);
	element->SetRectOffset(temp);
}
VOID ProcElement_ImageMode(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, element->GetTextureMode(), (const char*)nParameter);
	element->SetTextureMode(temp);
	if(!GetCopyKeyboard() && data->GetElementPtr(0) == element)
	{
		Phantom::Rect rc	=	data->GetWindowRect();
		rc.right	=	rc.left + element->GetSourceRect().GetWidth();
		rc.bottom	=	rc.top + element->GetSourceRect().GetHeight();
		const Phantom::TextureRect* prc	=	Phantom::GetDlgManager()->GetTextureRect(element->GetTextureID(), element->m_textureMode.t);
		if(prc)
		{
			rc.right	=	prc->orig.cx + rc.left;
			rc.bottom	=	prc->orig.cy + rc.top;
		}
		data->SetWindowRect(rc);
	}
}
VOID ProcElement_RandomImage(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	FileName vold,vnew;
	IF_ADD(){
		vold = element->GetTextureMode();
		element->RandomSetMode();
		vnew = element->GetTextureMode();
	}
	ADD_UR(FileName, vold, vnew);
	IF_ADD(){
	}
	else{
		element->SetTextureMode(temp);
	}
	if(!GetCopyKeyboard() && data->GetElementPtr(0) == element)
	{
		Phantom::Rect rc	=	data->GetWindowRect();
		rc.right	=	rc.left + element->GetSourceRect().GetWidth();
		rc.bottom	=	rc.top + element->GetSourceRect().GetHeight();
		const Phantom::TextureRect* prc	=	Phantom::GetDlgManager()->GetTextureRect(element->GetTextureID(), element->m_textureMode.t);
		if(prc)
		{
			rc.right	=	prc->orig.cx + rc.left;
			rc.bottom	=	prc->orig.cy + rc.top;
		}
		data->SetWindowRect(rc);
	}
}
VOID ProcElement_ImageRectReget(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Rect rc(-1, -1, -1, -1);
	ADD_UR(Phantom::Rect, element->GetSourceRect(), rc);
	element->SetSourceRect(temp);
}

VOID ProcElement_TextColor(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::color4 c;
	IF_ADD(){
	c.from(nParameter, element->GetTextColor().a);
	}
	ADD_UR(Phantom::color4, element->GetTextColor(), c);
	element->SetTextColor(temp);
}

VOID ProcElement_TextColorA(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::color4 c = element->GetTextColor();
	IF_ADD(){
	c.a		=	*(float*)nParameter;
	}
	ADD_UR(Phantom::color4, element->GetTextColor(), c);
	element->SetTextColor(temp);
}
//
//VOID ProcElement_ShadowColor(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2)
//{
//	Phantom::color4 c(nParameter, element->GetShadowColor().a);
//	element->SetShadowColor(c);
//}
//
//VOID ProcElement_ShadowColorA(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2)
//{
//	Phantom::color4 c = element->GetShadowColor();
//	c.a		=	*(float*)nParameter;
//	element->SetShadowColor(c);
//}

VOID ProcElement_TextureColor(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::color4 c;
	IF_ADD(){
	c.from(nParameter, element->GetTextureColor().a);
	}
	ADD_UR(Phantom::color4, element->GetTextureColor(), c);
	element->SetTextureColor(temp);
}

VOID ProcElement_TextureColorA(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::color4 c = element->GetTextureColor();
	IF_ADD(){
	c.a		=	*(float*)nParameter;
	}
	ADD_UR(Phantom::color4, element->GetTextureColor(), c);
	element->SetTextureColor(temp);
}

VOID ProcElement_ColorOP(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetColorOP(), nParameter);
	element->SetColorOP(temp);
}

VOID ProcElement_SrcBlend(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetSrcBlend(), nParameter);
	element->SetSrcBlend(temp);
}

VOID ProcElement_DestBlend(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetDestBlend(), nParameter);
	element->SetDestBlend(temp);
}
VOID ProcElement_Filter(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->m_imageFilter, nParameter);
	element->m_imageFilter = temp;
}

VOID ProcElement_UCount(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	int w = 0, h = 0;
	element->GetUVAnimation(w, h);
	ADD_UR(int, w, nParameter);
	element->SetUVAnimation(temp, h);
}

VOID ProcElement_VCount(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	int w = 0, h = 0;
	element->GetUVAnimation(w, h);
	ADD_UR(int, h, nParameter);
	element->SetUVAnimation(w, temp);
}

VOID ProcElement_InvW(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->IsInvW(), nParameter);
	element->SetInvW(temp);
}

VOID ProcElement_InvH(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->IsInvH(), nParameter);
	element->SetInvH(temp);
}
VOID ProcElement_UVSpeed(Phantom::UIControl* data, Phantom::UIElement* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, element->GetUVPlaySpeed(), *(float*)nParameter);
	element->SetUVPlaySpeed(temp);
}

VOID ProcAnimation3D_Name(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, element->GetName(), Autf8((wchar_t*)nParameter).buf);
	element->SetName(temp);
	GCViewUIEditor* edview = static_cast<GCViewUIEditor*>(GCViewBase::s_currView);
	HTREEITEM hItem = edview->FindTreeItem(edview->m_hViewItem, GCViewUIEditor::UI_PROP_ANIMATION, ptr->buff->m_id, ptr->buff->m_id2, ptr->buff->m_id3, ptr->buff->m_id4);
	if(hItem)
		edview->GetTreeView()->SetItemText(hItem, Wutf8(temp.t));
}
VOID ProcAnimation3D_FrameCount(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetFrameCount(), (int)(*(float*)nParameter * TRACK_SECOND_LENGTH));
	element->SetTrackKeyCount(temp);
}
VOID ProcAnimation3D_Default(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetTrackDefaultID(), (nParameter ? element->m_nID : -1));
	data->SetTrackDefaultID(temp);
}
VOID ProcAnimation3D_SleepTime(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, element->GetSleepTime(), *(float*)nParameter);
	element->SetSleepTime(temp);
}
VOID ProcAnimation3D_WaveSleepTime(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, element->GetWaveSleepTime(), *(float*)nParameter);
	element->SetWaveSleepTime(temp);
}
VOID ProcAnimation3D_HideAtSleep(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetSleepAtHide(), nParameter);
	element->SetSleepAtHide(temp);
}
VOID ProcAnimation3D_HideOnOver(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->m_bHideOnOver, nParameter);
	element->m_bHideOnOver = temp;
}

VOID ProcAnimation3D_Speed(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, element->GetPlaySpeed(), *(float*)nParameter);
	element->SetPlaySpeed(temp);
}
VOID ProcAnimation3D_Element(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	int vold = element->GetElementIndex();
	int vnew = 0;
	const char* szName	=	(const char*)nParameter;
	for(int i=0;i<data->GetElementCount();i++)
	{
		if(stricmp(szName, Autf8(GetElementName(data->GetType(), i)).buf) == 0)
		{
			vnew = i;
			break;
		}
	}
	ADD_UR(int, vold, vnew);
	element->SetElementIndex(temp);
}
VOID ProcAnimation3D_ElementAni(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	if(element->GetElementIndex() < 0 || element->GetElementIndex() >= data->GetElementCount())
		return;
	Phantom::UIElement* ele	=	data->GetElementPtr(element->GetElementIndex());
	int vold = element->GetUVAnimation();
	int vnew = 0;
	IF_ADD(){
		const char* szName	=	(const char*)nParameter;
		for(int i=0;i<ele->GetUVAnimationCount();i++)
		{
			if(stricmp(szName, ele->GetUVAnimationPtr(i)->GetName()) == 0)
			{
				vnew = ele->GetUVAnimationPtr(i)->GetActionType();
				break;
			}
		}
	}
	ADD_UR(int, vold, vnew);
	element->SetUVAnimation((Phantom::ActionType)temp);
}
VOID ProcAnimation3D_LoopCount(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetLoopCount(), nParameter);
	element->SetLoopCount(temp);
}
VOID ProcAnimation3D_WaitEnable(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->IsWaitTimeEnable(), nParameter);
	element->SetWaitTimeEnable(temp);
}
VOID ProcAnimation3D_NextID(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetNextActionType(), nParameter);
	element->SetNextActionType((Phantom::ActionType)temp);
}
VOID ProcAnimation3D_UnitType(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, element->GetActionType(), nParameter);
	element->SetActionType((Phantom::ActionType)temp);
}
VOID ProcAnimation3D_WaveFile(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, element->GetWaveFile(), (const char*)nParameter);
	element->SetWaveFile(temp);
}

VOID ProcAnimation3D_WaveSpeed(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, element->GetWaveSpeed(), *(float*)nParameter);
	element->SetWaveSpeed(temp);
}

VOID ProcAnimation3D_WaveVolume(Phantom::UIControl* data, Phantom::UIAnimationTrack* element, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, element->GetWaveVolume(), *(float*)nParameter);
	element->SetWaveVolume(temp);
}

VOID ProcUVAnimation_PlaySpeed(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, eUV->GetPlaySpeed(), *(float*)nParameter);
	eUV->SetPlaySpeed(temp);
}
VOID ProcUVAnimation_Name(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, eUV->m_name, Autf8((wchar_t*)nParameter).buf);
	eUV->m_name = temp;
}
VOID ProcUVAnimation_LoopCount(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, eUV->GetLoopCount(), nParameter);
	eUV->SetLoopCount(temp);
}
VOID ProcUVAnimation_Angle(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, eUV->m_angle2D, nParameter);
	eUV->m_angle2D = ((Phantom::Unit2DAngle)temp);
}
VOID ProcUVAnimation_InvW(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, eUV->IsInvW(), nParameter);
	eUV->SetInvW(temp);
}
VOID ProcUVAnimation_InvH(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, eUV->IsInvH(), nParameter);
	eUV->SetInvH(temp);
}
VOID ProcUVAnimation_ImageList(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, INT nIndex, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	const Phantom::TextureRect* rect	=	eUV->GetTextureRect(nIndex);
	if(!rect)return;
	Phantom::TextureRect rc	=	*rect;
	IF_ADD(){
		rc.name			=	(const char*)nParameter;
	}
	ADD_UR(Phantom::TextureRect, *rect, rc);
	eUV->SetTextureRect(nIndex, temp);
}

VOID ProcUVAnimation_Fills(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	IF_ADD(){
		int nB, nCount;
		eUV->GetUVMapIndex(nB, nCount);
		int len = strlen((const char*)nParameter);
		char fmt[256];
		strcpy(fmt, (const char*)nParameter);
		char szDrive[256], szDir[266], szFile[128], szExt[128];
		_splitpath(fmt, szDrive, szDir, szFile, szExt);
		strcat(szDrive, szDir);
		int nLen = strlen(szFile);
		int nNum = 0;
		for(int i=nLen-1;i>=0;i--)
		{
			if(szFile[i] >= '0' && szFile[i] <= '9')
				nNum++;
			else
				break;
		}
		char szLeft[128];
		memset(szLeft, 0, sizeof(szLeft));
		strncpy(szLeft, szFile, nLen-nNum);
		szLeft[nLen-nNum] = 0;
		strcat(szDrive, szLeft);
		//
		char szRight[128];
		memset(szRight, 0, sizeof(szRight));
		if(nNum > 0)
			strcpy(szRight, szFile + (nLen-nNum));

		int nBegin = atoi(szRight);
		(*ptr->buff) << nCount;
		for(int i=0;i<nCount;i++)
		{
			if(nNum > 1)
				sprintf(fmt, "%%0%dd", nNum);
			else
				sprintf(fmt, "%%d");
			char buf[256];
			strcpy(szDir, szDrive);
			sprintf(buf, fmt, i + nBegin);
			strcat(szDir, buf);
			strcat(szDir, szExt);
			const Phantom::TextureRect* rc = eUV->GetTextureRect(i);
			BOOL bExist = (rc!=0);
			(*ptr->buff) << bExist;
			if(rc)
			{
				Phantom::TextureRect r = *rc;
				r.name	=	szDir;
				(*ptr->buff) << i << *rc << r;
				eUV->SetTextureRect(i, r);
			}
		}
	}
	else if(ptr->urMode==UndoRedoBuffer::URMode_Undo){
		int nCount=0;
		(*ptr->buff) >> nCount;
		for(int i=0;i<nCount;i++){
			BOOL bExist = 0;
			(*ptr->buff) >> bExist;
			if(bExist){
				Phantom::TextureRect nold,nnew;
				int index;
				(*ptr->buff) >> index >> nold >> nnew;
				eUV->SetTextureRect(index, nold);
			}
		}
	}
	else if(ptr->urMode==UndoRedoBuffer::URMode_Undo){
		int nCount=0;
		(*ptr->buff) >> nCount;
		for(int i=0;i<nCount;i++){
			BOOL bExist = 0;
			(*ptr->buff) >> bExist;
			if(bExist){
				Phantom::TextureRect nold,nnew;
				int index;
				(*ptr->buff) >> index >> nold >> nnew;
				eUV->SetTextureRect(index, nnew);
			}
		}
	}
}
VOID ProcUVAnimation_CustomEnable(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, eUV->IsCustomEnable(), nParameter);
	eUV->SetCustomEnable(nParameter);
}
VOID ProcUVAnimation_SetTextureID(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, eUV->GetTexture(), (nParameter?Autf8((const wchar_t*)nParameter).buf:""));
	eUV->SetTexture(temp);
}
VOID ProcUVAnimation_RegetRects(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	eUV->RegetRects();
}
VOID ProcUVAnimation_SetLeft(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, INT nIndex, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	const Phantom::TextureRect* rect	=	eUV->GetTextureRect(nIndex);
	if(!rect)return;
	Phantom::TextureRect rc	=	*rect;
	IF_ADD(){
	int width	=	rc.rc.GetWidth();
	rc.rc.left	=	nParameter;
	rc.rc.right	=	rc.rc.left + width;
	}
	ADD_UR(Phantom::TextureRect, *rect, rc);
	eUV->SetTextureRect(nIndex, temp);
}
VOID ProcUVAnimation_SetTop(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, INT nIndex, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	const Phantom::TextureRect* rect	=	eUV->GetTextureRect(nIndex);
	if(!rect)return;
	Phantom::TextureRect rc	=	*rect;
	IF_ADD(){
	int height		=	rc.rc.GetHeight();
	rc.rc.top		=	nParameter;
	rc.rc.bottom	=	rc.rc.top + height;
	}
	ADD_UR(Phantom::TextureRect, *rect, rc);
	eUV->SetTextureRect(nIndex, temp);
}
VOID ProcUVAnimation_SetWidth(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, INT nIndex, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	const Phantom::TextureRect* rect	=	eUV->GetTextureRect(nIndex);
	if(!rect)return;
	Phantom::TextureRect rc	=	*rect;
	IF_ADD(){
	rc.rc.right		=	rc.rc.left + nParameter;
	}
	ADD_UR(Phantom::TextureRect, *rect, rc);
	eUV->SetTextureRect(nIndex, temp);
}
VOID ProcUVAnimation_SetHeight(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, INT nIndex, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	const Phantom::TextureRect* rect	=	eUV->GetTextureRect(nIndex);
	if(!rect)return;
	Phantom::TextureRect rc	=	*rect;
	IF_ADD(){
	rc.rc.bottom	=	rc.rc.top + nParameter;
	}
	ADD_UR(Phantom::TextureRect, *rect, rc);
	eUV->SetTextureRect(nIndex, temp);
}
VOID ProcUVAnimation_OffsetX(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, INT nIndex, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	const Phantom::Pixel* pos	=	eUV->GetTextureOffset(nIndex);
	if(!pos)return;
	Phantom::Pixel p		=	*pos;
	p.x				=	nParameter;
	ADD_UR(Phantom::Pixel, *pos, p);
	eUV->SetTextureOffset(nIndex, temp);
}
VOID ProcUVAnimation_OffsetY(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, INT nIndex, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	const Phantom::Pixel* pos	=	eUV->GetTextureOffset(nIndex);
	if(!pos)return;
	Phantom::Pixel p		=	*pos;
	p.y				=	nParameter;
	ADD_UR(Phantom::Pixel, *pos, p);
	eUV->SetTextureOffset(nIndex, temp);
}
VOID ProcUVAnimation_TextureFile(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, INT nIndex, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName, eUV->GetTextureRectFileName(nIndex), Autf8((const wchar_t*)nParameter).buf);
	eUV->SetTextureRectFile(nIndex, temp);
}

//VOID ProcUVAnimation_UCount(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2)
//{
//	int w, h;
//	eUV->GetUVAnimation(w, h);
//	eUV->SetUVAnimation(nParameter, h);
//}
//VOID ProcUVAnimation_VCount(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2)
//{
//	int w, h;
//	eUV->GetUVAnimation(w, h);
//	eUV->SetUVAnimation(w, nParameter);
//}
VOID ProcUVAnimation_SetAction(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, eUV->GetActionType(), nParameter);
	eUV->SetActionType((Phantom::ActionType)temp);
}
VOID ProcUVAnimation_SetNextAction(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, eUV->GetNextAction(), nParameter);
	eUV->SetNextAction((Phantom::ActionType)temp);
}
VOID ProcUVAnimation_SetNextActionRand(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, eUV->m_nextRand, *(float*)nParameter);
	eUV->m_nextRand = (float)temp;
}
VOID ProcUVAnimation_MoveOffset(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, eUV->m_bMoveOffset, nParameter);
	eUV->m_bMoveOffset = temp;
}
VOID ProcUVAnimation_MoveOffsetX(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, eUV->m_moveOffset.x, nParameter);
	eUV->m_moveOffset.x = temp;
}
VOID ProcUVAnimation_MoveOffsetY(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, eUV->m_moveOffset.y, nParameter);
	eUV->m_moveOffset.y = temp;
}
VOID ProcUVAnimation_MoveOffsetSpeed(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float, eUV->m_moveSpeed, *(float*)nParameter);
	eUV->m_moveSpeed = (float)temp;
}

VOID ProcUVAnimation_FrameCount(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	INT nBegin = 0, nCount = 0;
	eUV->GetUVMapIndex(nBegin, nCount);
	ADD_UR(int, nCount, nParameter);
	eUV->SetUVMapIndex(nBegin, temp);
}
VOID ProcUVAnimation_BeginIndex(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	INT nBegin = 0, nCount = 0;
	eUV->GetUVMapIndex(nBegin, nCount);
	ADD_UR(int, nBegin, nParameter);
	eUV->SetUVMapIndex(temp, nCount);
}
VOID ProcUVAnimation_LayerAdd(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, eUV->GetLayerAdd(), nParameter);
	eUV->SetLayerAdd(temp);
}
VOID ProcUVAnimation_Default(Phantom::UIControl* data, Phantom::UIElement* e, Phantom::UVAnimation* eUV, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	e->SetUVAnimationDefault(eUV);
}

VOID	ProcGroup_Name(Phantom::UIGroup* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(FileName,data->GetName(), Autf8((wchar_t*)nParameter).buf);
	data->SetName(temp);
	GCViewUIEditor* edview = static_cast<GCViewUIEditor*>(GCViewBase::s_currView);
	HTREEITEM hItem = edview->FindTreeItem(edview->m_hViewItem, GCViewUIEditor::UI_PROP_GROUP, data->GetID());
	if(hItem)
		edview->GetTreeView()->SetItemText(hItem, Wutf8(temp.t));
}

VOID	ProcGroup_Visible(Phantom::UIGroup* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int,data->GetVisible(), nParameter);
	data->SetVisible(temp);
}

VOID	ProcGroup_SleepTime(Phantom::UIGroup* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float,data->GetSleepTime(), *(float*)nParameter);
	data->SetSleepTime(temp);
}
VOID	ProcGroup_SetIsUnit(Phantom::UIGroup* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int,data->GetGroupIsUnit(), nParameter);
	data->SetGroupIsUnit(temp);
}
VOID	ProcGroup_SetEnable(Phantom::UIGroup* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int,data->GetEnabled(), nParameter);
	data->SetEnabled(temp);
}
VOID	ProcGroup_SetAngle(Phantom::UIGroup* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float,data->GetUnitAngle(), *(float*)nParameter);
	data->SetUnitAngle(temp);
}
VOID	ProcGroup_SetSpeed(Phantom::UIGroup* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(float,data->GetPlaySpeed(), *(float*)nParameter);
	data->SetPlaySpeed(temp);
}
VOID	ProcGroup_SetAction(Phantom::UIGroup* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	data->PlayAction((Phantom::ActionType)nParameter);
}
VOID	GCViewUIEditor::LoopAllDialog(ProcDialog3D proc, LPARAM nParameter, LPARAM nParameter2)
{
	this->BeginUndo();
	UndoPtr uptr;
	uptr.buff = AddUndoRedo(GCViewUIEditor::UI_PROP_MAIN, (ProcUndoRedo)proc);
	uptr.urMode = UndoRedoBuffer::URMode_Add;
	uptr.buff->m_id	=	0;
	(*proc)(this->m_dialogPtr, nParameter, nParameter2, &uptr);
}
VOID	ProcDialog_2DGame(Phantom::UIDialog* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->IsBackgroundWindow(), nParameter); 
	data->SetBackgroundWindow(temp);
}
VOID	ProcDialog_MapEnable(Phantom::UIDialog* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->GetMapEnable(), nParameter); 
	data->SetMapEnable(temp);
}
VOID	ProcDialog_Map25DMode(Phantom::UIDialog* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(int, data->m_bMap25DMode, nParameter); 
	data->m_bMap25DMode = (temp);
	data->SetMapGridCount(data->GetMapGridCount());
}
VOID	ProcDialog_MapGridSize(Phantom::UIDialog* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Size c(nParameter, nParameter2);
	ADD_UR(Phantom::Size, data->GetMapGridSize(), c); 
	data->SetMapGridSize(temp);
}
VOID	ProcDialog_MapGridCount(Phantom::UIDialog* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Size c(nParameter, nParameter2);
	ADD_UR(Phantom::Size, data->GetMapGridCount(), c); 
	data->SetMapGridCount(temp);
}
VOID	ProcDialog_MapGridOffset(Phantom::UIDialog* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	Phantom::Pixel c(nParameter, nParameter2);
	ADD_UR(Phantom::Pixel, data->m_mapGridBegin, c); 
	data->m_mapGridBegin=(temp);
}
VOID	ProcDialog_Pos(Phantom::UIDialog* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	int x,y;
	data->GetLocation(x,y);
	Phantom::Size old(x,y);
	Phantom::Size c(nParameter, nParameter2);
	ADD_UR(Phantom::Size, old, c); 
	data->SetLocation(temp.cx, temp.cy);
}
VOID	ProcDialog_Color(Phantom::UIDialog* data, LPARAM nParameter, LPARAM nParameter2, UndoPtr* ptr)
{
	ADD_UR(Phantom::color4, data->GetDialogColor(), Phantom::color4((unsigned int)nParameter)); 
	data->SetDialogColor(temp);
}

#define	Fn(v)	Prop_##v
VOID		GCViewUIEditor::SetModifyed(BOOL bModifyed)
{
	if(this->m_dialogPtr->m_pakdir)return;
	GCViewBase::SetModifyed(bModifyed);
}
//�Ƚϵ�ʱ����ʹ�� || ͳһ���ã���Ϊ�����ö����ʱ����ᵼ������Ԫ�ص�ֵ�ᱻ���ó�ͳһ�ļ����������ǵ����ı���Ǹ�
void		GCViewUIEditor::OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp)
{
	__super::OnPropertyChanged(wnd, pProp);
	if(wnd == &this->m_dlgProp)
	{
		if(pProp == m_dlgAlwaysVisible)
			m_bAlwaysVisible	=	GetPropBool(m_dlgAlwaysVisible);
		//else if(pProp == m_dlgAnimationEnable)
		//{
		//	m_dialogPtr->SetEnableDlgAnim(GetPropBool(m_dlgAnimationEnable));
		//	this->SetModifyed(true);
		//}
		//else if(pProp == m_dlgAlignLR || pProp == m_dlgAlignTB)
		//{
		//	m_dialogPtr->SetDialogAlign((DIALOG_ALIGN)GetPropOption(m_dlgAlignLR, g_typeDialogAlignLR), (DIALOG_ALIGN)GetPropOption(m_dlgAlignTB, g_typeDialogAlignTB));
		//	//
		//	int x = 0;
		//	int y = 0;
		//	m_dialogPtr->GetLocation(x,y);
		//	SetPropInt(m_dlgX, x);
		//	SetPropInt(m_dlgY, y);
		//	this->SetModifyed(true);
		//}
		//else if(pProp == m_dlgOffsetX || pProp == m_dlgOffsetY)
		//{
		//	m_dialogPtr->SetDialogAlignOffset(GetPropInt(m_dlgOffsetX), GetPropInt(m_dlgOffsetY));
		//	int x = 0;
		//	int y = 0;
		//	//int nScale	=	GetPropOption(m_dlgViewScale, g_typeViewScale);
		//	//if(nScale <= 2)
		//	{
		//		m_dialogPtr->GetLocation(x,y);
		//		SetPropInt(m_dlgX, x);
		//		SetPropInt(m_dlgY, y);
		//		this->SetModifyed(true);
		//	}
		//}
		//else if(pProp == m_dlgViewScale)
		//{
		//	DefineAuth_4();
		//	if(!CheckAuth_4(0))
		//		return;
		//	int nScale	=	GetPropOption(m_dlgViewScale, g_typeViewScale);
		//	//if(nScale > 2)
		//	//	m_dialogPtr->SetLocation(0, 0);
		//	m_dialogPtr->SetDialogScale(Phantom::float2(1.0f / (float)nScale, 1.0f / (float)nScale));
		//}
		else if(pProp == m_dlgIs2DGame)
		{
			LoopAllDialog(ProcDialog_2DGame, GetPropBool(m_dlgIs2DGame));
		}
		//else if(pProp == m_dlgViewScaleX || pProp == m_dlgViewScaleY)
		//{
		//	DefineAuth_4();
		//	if(!CheckAuth_4(0))
		//		return;
		//	m_dialogPtr->SetDialogScale(Phantom::float2(GetPropFloat(m_dlgViewScaleX), GetPropFloat(m_dlgViewScaleY)));
		//}
		else if(pProp == m_dlgMapEnable)
		{
			LoopAllDialog(ProcDialog_MapEnable, GetPropBool(m_dlgMapEnable));
			//m_dialogPtr->SetMapEnable(GetPropBool(m_dlgMapEnable));
			this->SetModifyed();
		}
		else if(pProp == m_dlgMap25DMode)
		{
			LoopAllDialog(ProcDialog_Map25DMode, GetPropBool(m_dlgMap25DMode));
			//m_dialogPtr->SetMapEnable(GetPropBool(m_dlgMapEnable));
			this->SetModifyed();
		}
		else if(pProp == m_dlgMapSizeX || pProp == m_dlgMapSizeY)
		{
			LoopAllDialog(ProcDialog_MapGridSize, GetPropInt(m_dlgMapSizeX), GetPropInt(m_dlgMapSizeY));
			//m_dialogPtr->SetMapGridSize(Phantom::Size(GetPropInt(m_dlgMapSizeX), GetPropInt(m_dlgMapSizeY)));
			this->SetModifyed();
		}
		else if(pProp == m_dlgMapCountX || pProp == m_dlgMapCountY)
		{
			LoopAllDialog(ProcDialog_MapGridCount, GetPropInt(m_dlgMapCountX), GetPropInt(m_dlgMapCountY));
			//m_dialogPtr->SetMapGridCount(Phantom::Size(GetPropInt(m_dlgMapCountX), GetPropInt(m_dlgMapCountY)));
			this->SetModifyed();
		}
		else if(pProp == m_dlgMapOffsetX || pProp == m_dlgMapOffsetY)
		{
			LoopAllDialog(ProcDialog_MapGridOffset, GetPropInt(m_dlgMapOffsetX), GetPropInt(m_dlgMapOffsetY));
			//m_dialogPtr->SetMapGridCount(Phantom::Size(GetPropInt(m_dlgMapCountX), GetPropInt(m_dlgMapCountY)));
			this->SetModifyed();
		}
		else if(pProp == m_dlgX || pProp == m_dlgY)
		{
			LoopAllDialog(ProcDialog_Pos, GetPropInt(m_dlgX), GetPropInt(m_dlgY));
			this->SetModifyed(true);
		}
		else if(pProp==m_dlgRecalcRects){
			for(int i=0;i<this->m_dialogPtr->GetControlCount();i++){
				Phantom::UIControl* c = m_dialogPtr->GetControlPtr(i);
				for(int j=0;j<c->GetElementCount();j++){
					Phantom::UIElement* e = c->GetElementPtr(j);
					e->SetTextureMode(e->GetTextureMode());
					for(int k=0;k<e->GetUVAnimationCount();k++){
						e->GetUVAnimationPtr(k)->RegetRects();
					}
				}
			}
			this->SetModifyed(true);
		}
		else if(pProp == m_dlgAlpha || pProp == m_dlgColor)
		{
			Phantom::color4 c(GetPropColor(m_dlgColor), GetPropFloat(m_dlgAlpha));
			LoopAllDialog(ProcDialog_Color, c.operator unsigned int());
			//m_dialogPtr->SetDialogColor(c);
			this->SetModifyed(true);
		}
	}
	else if(wnd == &this->m_controlProp)
	{
		//if(pProp == m_controlToolTipText)
		//{
		//	std::wstring str;
		//	GetPropText(m_controlToolTipText, str);
		//	LoopAllControls(ProcControl3D_ToolTip, (LPARAM)str.c_str(), 0);
		//}
		//else if(pProp == m_controlToolTipAlign)
		//	LoopAllControls(ProcControl3D_ToolTipPopup, GetPropOption(m_controlToolTipAlign, g_typeToolTipAlign));
		//else 
		if(pProp == m_controlName)
		{
			std::wstring str;
			GetPropText(m_controlName, str);
			LoopAllControls(ProcControl3D_ControlName, (LPARAM)str.c_str(), 0, TRUE);
		}
		else if(pProp == m_controlLeft)
			LoopAllControls(ProcControl3D_ControlRectLeft, GetPropInt(m_controlLeft), 0);
		else if(pProp == m_controlTop)
			LoopAllControls(ProcControl3D_ControlRectTop, GetPropInt(m_controlTop), 0);
		else if(pProp == m_controlWidth)
		{
			Phantom::UIControl* control = LoopAllControls(ProcControl3D_ControlRectWidth, GetPropInt(m_controlWidth), 0);
			if(control){
				int nWidth	=	control->GetElementPtr(0)->GetSourceRect().GetWidth();
				if(nWidth < 1)nWidth = 1;
				SetPropFloat(m_controlScale, (float)control->GetRenderRect().GetWidth() / (float)nWidth);
				SetPropInt(this->m_controlCenterX, control->GetRotCenter().x);
				SetPropInt(this->m_controlCenterY, control->GetRotCenter().y);
			}
		}
		else if(pProp == m_controlHeight)
		{
			Phantom::UIControl* control = LoopAllControls(ProcControl3D_ControlRectHeight, GetPropInt(m_controlHeight), 0);
			if(control){
			SetPropInt(this->m_controlCenterX, control->GetRotCenter().x);
			SetPropInt(this->m_controlCenterY, control->GetRotCenter().y);
			}
		}
		else if(pProp == m_controlScale)
		{
			Phantom::UIControl* control = LoopAllControls(ProcControl3D_ControlScale, (LPARAM)GetPropFloatPtr(m_controlScale), 0);
			if(control){
			SetPropInt(m_controlLeft, control->GetRenderRect().left);
			SetPropInt(m_controlTop, control->GetRenderRect().top);
			SetPropInt(m_controlWidth, control->GetRenderRect().GetWidth());
			SetPropInt(m_controlHeight, control->GetRenderRect().GetHeight());
			SetPropInt(this->m_controlCenterX, control->GetRotCenter().x);
			SetPropInt(this->m_controlCenterY, control->GetRotCenter().y);
			}
		}
		else if(pProp == m_controlAlignModeW || pProp == m_controlAlignModeH)
			LoopAllControls(ProcControl3D_ControlAlignMode, (LPARAM)GetPropOption(m_controlAlignModeW, g_typeAlignModeW), (LPARAM)GetPropOption(m_controlAlignModeH, g_typeAlignModeH));
		//
		else if(pProp == m_controlGroupID)
		{
			std::wstring str;
			GetPropText(m_controlGroupID, str);
			int nGroupID	=	0;
			wchar_t buf[256];
			for(int i=0;i<m_dialogPtr->GetGroupCount();i++)
			{
				swprintf(buf, L"%s[%d]", Wutf8(m_dialogPtr->GetGroupPtr(i)->GetName()).buf, m_dialogPtr->GetGroupPtr(i)->GetID());
				if(wcsicmp(buf, str.c_str()) == 0)
				{
					nGroupID	=	m_dialogPtr->GetGroupPtr(i)->GetID();
					break;
				}
			}
			LoopAllControls(ProcControl3D_GroupID, nGroupID, 0, false, true);
		}
		else if(pProp == m_controlMoveDialog)
			LoopAllControls(ProcControl3D_MoveDialog, GetPropBool(m_controlMoveDialog));
		else if(pProp == m_controlBackground)
			LoopAllControls(ProcControl3D_Background, GetPropBool(m_controlBackground));
		else if(pProp == m_controlLayer)
			LoopAllControls(ProcControl3D_Layer, GetPropOption(m_controlLayer, g_typeControlLayer));
		else if(pProp == m_controlIsGrid)
		{
			LoopAllControls(ProcControl3D_IsGrid, GetPropBool(m_controlIsGrid));
			m_controlGridOffset->Enable(GetPropBool(m_controlIsGrid));
			ResetCenter();
		}
		else if(pProp == m_controlGridOffset)
			LoopAllControls(ProcControl3D_GridOffset, GetPropInt(m_controlGridOffset));
		//else if(pProp == m_controlContext)
		//	LoopAllControls(ProcControl3D_Context, GetPropInt(m_controlContext));
		else if(pProp == m_controlTextAlignLR)
			LoopAllControls(ProcControl3D_TextAlignLR, GetPropOption(m_controlTextAlignLR, g_typeTextAlignLR));
		else if(pProp == m_controlTextAlignTB)
			LoopAllControls(ProcControl3D_TextAlignTB, GetPropOption(m_controlTextAlignTB, g_typeTextAlignTB));
		else if(pProp == m_controlVisible)
			LoopAllControls(ProcControl3D_Visible, GetPropBool(m_controlVisible));
		else if(pProp == m_controlCanActive)
			LoopAllControls(ProcControl3D_CanActive, GetPropBool(m_controlCanActive));
		else if(pProp == m_controlEnable)
			LoopAllControls(ProcControl3D_Enable, GetPropBool(m_controlEnable));
		else if(pProp == m_controlSelect)
			LoopAllControls(ProcControl3D_Select, GetPropBool(m_controlSelect));
		//else if(pProp == m_controlAniCenter)
			//LoopAllControls(ProcControl3D_AniCenter, GetPropBool(m_controlAniCenter));
		else if(pProp == m_controlEnableImgText)
		{
			LoopAllControls(ProcControl3D_EnableImgText, GetPropBool(m_controlEnableImgText));
			m_controlImgTextBegin->Enable(GetPropBool(m_controlEnableImgText));
			m_controlImgSizeAdd->Enable(GetPropBool(m_controlEnableImgText));
		}
		else if(pProp == m_controlImgTextBegin)
		{
			std::string str;
			GetPropText(m_controlImgTextBegin, str);
			LoopAllControls(ProcControl3D_ImgTextBegin, (LPARAM)str.c_str());
		}
		else if(pProp == m_controlImgSizeAdd)
		{
			LoopAllControls(ProcControl3D_ImgSizeAdd, GetPropInt(m_controlImgSizeAdd));
		}
		//else if(pProp == m_controlShadowWidth)
		//	LoopAllControls(ProcControl3D_ShadowWidth, GetPropInt(m_controlShadowWidth));
		//else if(pProp == m_controlShadowColor)
		//	LoopAllControls(ProcControl3D_ShadowColor, GetPropColor(m_controlShadowColor));
		//else if(pProp == m_controlShadowAlpha)
		//	LoopAllControls(ProcControl3D_ShadowColorA, (LPARAM)GetPropFloatPtr(m_controlShadowAlpha));
		else if(pProp == m_controlDrawFocus)
			LoopAllControls(ProcControl_DrawFocusFrame, GetPropBool(m_controlDrawFocus));
		else if(pProp == m_controlSleepTime)
			LoopAllControls(ProcControl_SleepTime, (LPARAM)GetPropFloatPtr(m_controlSleepTime));
		else if(pProp == m_controlIs2DUnit)
			LoopAllControls(ProcControl_AutoSort, (LPARAM)GetPropBool(m_controlIs2DUnit));
		else if(pProp == m_controlUnitAngle8)
		{
			LoopAllControls(ProcControl_Angle8, (LPARAM)GetPropOption(m_controlUnitAngle8, g_typeUnitAngleType), 0, 0, 0, true);
		}
		else if(pProp == m_controlText)
		{
			std::wstring str;
			GetPropText(m_controlText, str);
			LoopAllControls(ProcControl3D_ControlText, (LPARAM)str.c_str(), 0);
		}
		else if(pProp == m_controlTextColor)
			LoopAllControls(ProcControl3D_TextColor, GetPropColor(m_controlTextColor));
		else if(pProp == m_controlImageFont)
		{
			LoopAllControls(ProcControl3D_ImageFont, GetPropBool(m_controlImageFont));
			m_controlFont->Enable(!GetPropBool(m_controlImageFont));
		}
		else if(pProp == m_controlTextureColor)
			LoopAllControls(ProcControl3D_TextureColor, GetPropColor(m_controlTextureColor));
		//else if(pProp == m_controlDisableColor)
			//LoopAllControls(ProcControl3D_DisableColor, GetPropColor(m_controlDisableColor));
		else if(pProp == m_controlTextAlpha)
			LoopAllControls(ProcControl3D_TextAlpha, (LPARAM)GetPropFloatPtr(m_controlTextAlpha));
		else if(pProp == m_controlTextureAlpha)
			LoopAllControls(ProcControl3D_TextureAlpha, (LPARAM)GetPropFloatPtr(m_controlTextureAlpha));
		else if(pProp == m_controlTabIndex)
			LoopAllControls(ProcControl3D_TabIndex, (LPARAM)GetPropInt(m_controlTabIndex));
		//else if(pProp == m_controlCursorName)
		//{
		//	std::wstring str;
		//	GetPropText(m_controlCursorName, str);
		//	LoopAllControls(ProcControl3D_CursorName, (LPARAM)str.c_str(), 0);
		//}
		else if(pProp == m_controlRotation)
			LoopAllControls(ProcControl3D_Rotation, GetPropBool(m_controlRotation));
		else if(pProp == m_controlIsGroupCenter)
			LoopAllControls(ProcControl3D_GroupCenter, GetPropBool(m_controlIsGroupCenter));
		else if(pProp == m_controlPixel)
			LoopAllControls(ProcControl3D_Pixel, GetPropBool(m_controlPixel));
		else if(pProp == m_controlParent)
		{
			std::wstring ret;
			GetPropText(m_controlParent, ret);
			Phantom::UIControl* c	=	0;
			for(int i=0;i<this->m_dialogPtr->GetControlCount();i++)
			{
				wchar_t buf[256];
				swprintf(buf, L"%s[%d]", Wutf8(m_dialogPtr->GetControlPtr(i)->GetName()).buf, i + 1);
				if(wcsicmp(buf, ret.c_str()) == 0)
				{
					c	=	m_dialogPtr->GetControlPtr(i);
					break;
				}
			}
			LoopAllControls(ProcControl3D_Parent, (LPARAM)c);
		}
		else if(pProp == m_controlAngle)
			LoopAllControls(ProcControl3D_RotationAngle, (LPARAM)GetPropFloatPtr(m_controlAngle));
		else if(pProp == m_controlCenterX)
			LoopAllControls(ProcControl3D_CenterX, GetPropInt(m_controlCenterX));
		else if(pProp == m_controlCenterY)
			LoopAllControls(ProcControl3D_CenterY, GetPropInt(m_controlCenterY));
		//
		else if(pProp == m_editPassword)
			LoopAllControls(ProcEdit3D_Password, GetPropBool(m_editPassword));
		//else if(pProp == m_editEnableIME)
		//	LoopAllControls(ProcEdit3D_EnableIME, GetPropBool(m_editEnableIME));
		else if(pProp == m_editReadOnly)
			LoopAllControls(ProcEdit3D_ReadOnly, GetPropBool(m_editReadOnly));
		//else if(pProp == m_editIndicator)
		//	LoopAllControls(ProcEdit3D_Indicator, GetPropBool(m_editIndicator));
		else if(pProp == m_editSBWidth)
			LoopAllControls(ProcEdit3D_SBWidth, GetPropInt(m_editSBWidth));
		//else if(pProp == m_editCandList)
		//	LoopAllControls(ProcEdit3D_CandList, GetPropBool(m_editCandList));
		//else if(pProp == m_editBorderWidth)
		//	LoopAllControls(ProcEdit3D_BorderWidth, GetPropInt(m_editBorderWidth));
		//else if(pProp == m_editCaretColor)
		//	LoopAllControls(ProcEdit3D_CaretColor, GetPropColor(m_editCaretColor));
		//else if(pProp == m_editSelectTextColor)
		//	LoopAllControls(ProcEdit3D_SelectTextColor, GetPropColor(m_editSelectTextColor));
		//else if(pProp == m_editSelectBackColor)
		//	LoopAllControls(ProcEdit3D_SelectBackColor, GetPropColor(m_editSelectBackColor));
		//
		else if(pProp == m_progressMode)
			LoopAllControls(ProcProgress3D_Mode, GetPropOption(m_progressMode, g_typeProgress));
		else if(pProp == m_progressValue)
			LoopAllControls(ProcProgress3D_Value, (LPARAM)GetPropFloatPtr(m_progressValue));
		else if(pProp == m_progressSize)
			LoopAllControls(ProcProgress3D_Size, (LPARAM)GetPropInt(m_progressSize));
		//
		else if(pProp == m_comboDropHeight)
			LoopAllControls(ProcCombo3D_DropHeight, GetPropInt(m_comboDropHeight));
		else if(pProp == m_controlFont)
		{
			FontNode2D fontNode;
			GetPropFont(m_controlFont, fontNode);
			LoopAllControls(ProcControl_Font, (LPARAM)&fontNode);
		}
		else if(pProp == m_comboValues)
		{
			std::vector<std::wstring> lists;
			GetPropList(m_comboValues, lists);
			LoopAllControls(ProcCombo3D_Values, (LPARAM)&lists);
		}
		//
		else if(pProp == m_formatEditEventColor)
			LoopAllControls(ProcFormat_EventColor, GetPropColor(m_formatEditEventColor));
		else if(pProp == m_formatEditSelectColor)
			LoopAllControls(ProcFormat_SelectColor, GetPropColor(m_formatEditSelectColor));
		else if(pProp == m_formatEditLineHeight)
			LoopAllControls(ProcFormat_LineHeight, GetPropInt(m_formatEditLineHeight));
		//
		else if(pProp == m_listboxLineHeight)
			LoopAllControls(ProcListBox_LineHeight, GetPropInt(m_listboxLineHeight));
		else if(pProp == m_listboxTextLeft)
			LoopAllControls(ProcListBox_TextLeft, GetPropInt(m_listboxTextLeft));
		else if(pProp == m_listboxValues)
		{
			std::vector<std::wstring> lists;
			GetPropList(m_listboxValues, lists);
			LoopAllControls(ProcListBox_Values, (LPARAM)&lists);
		}
		//
		else if(pProp == m_listctrlLineHeight)
			LoopAllControls(ProcListCtrl_LineHeight, GetPropInt(m_listctrlLineHeight));
		else if(pProp == m_listctrlColumnHeight)
			LoopAllControls(ProcListCtrl_ColumnHeight, GetPropInt(m_listctrlColumnHeight));
		else if(pProp == m_listctrlTextLeft)
			LoopAllControls(ProcListCtrl_TextLeft, GetPropInt(m_listctrlTextLeft));
		else if(pProp == m_listctrlSortEnable)
			LoopAllControls(ProcListCtrl_SortEnable, GetPropBool(m_listctrlSortEnable));
		else if(pProp == m_listctrlColumns)
		{
			std::vector<std::wstring> lists;
			GetPropList(m_listctrlColumns, lists);
			LoopAllControls(ProcListCtrl_ColumnValues, (LPARAM)&lists);
		}
		else if(pProp == m_listctrlItems)
		{
			std::vector<std::wstring> lists;
			GetPropList(m_listctrlItems, lists);
			LoopAllControls(ProcListCtrl_Values, (LPARAM)&lists);
		}
		else if(pProp == m_checkboxChecked)
			LoopAllControls(ProcCheckBox_Checked, GetPropBool(m_checkboxChecked));
		else if(pProp == m_effectLoopCount)
			LoopAllControls(ProcEffect_LoopCount, GetPropInt(m_effectLoopCount));
		else if(pProp == m_effectFrameCount)
		{
			LoopAllControls(ProcEffect_FrameCount, (int)(GetPropFloat(m_effectFrameCount) * TRACK_SECOND_LENGTH));
			this->m_animationTrack.SetTrackKeyCount((int)(GetPropFloat(m_effectFrameCount) * TRACK_SECOND_LENGTH));
		}
		else if(pProp == m_effectPlaySpeed)
			LoopAllControls(ProcEffect_PlaySpeed, (LPARAM)GetPropFloatPtr(m_effectPlaySpeed));
		//
		else if(pProp == m_staticBorderWidth)
			LoopAllControls(PropStatic_BorderWidth, GetPropInt(m_staticBorderWidth));
		//else if(pProp == m_staticMouseSrcBlend)
		//	LoopAllControls(PropStatic_MouseSrcBlend, GetPropOption(m_staticMouseSrcBlend, g_typeBlend));
		//else if(pProp == m_staticMouseEnable)
		//	LoopAllControls(PropStatic_MouseEnable, GetPropBool(m_staticMouseEnable));
		//else if(pProp == m_staticMouseDestBlend)
		//	LoopAllControls(PropStatic_MouseDestBlend, GetPropOption(m_staticMouseDestBlend, g_typeBlend));
		else if(pProp == m_staticTextureColor)
			LoopAllControls(PropStatic_TextureColor, GetPropColor(m_staticTextureColor));
		else if(pProp == m_staticTextureAlpha)
			LoopAllControls(PropStatic_TextureAlpha, (LPARAM)GetPropFloatPtr(m_staticTextureAlpha));
		else if(pProp == m_buttonClickSound)
		{
			std::wstring str;
			GetPropFile(m_buttonClickSound, str);
			LoopAllControls(ProcButton_ClickSound, (LPARAM)str.c_str());
		}
		else if(pProp == m_buttonClickSoundClear)
		{
			LoopAllControls(ProcButton_ClickSound, 0);
		}
		else if(pProp == m_buttonType)
		{
			LoopAllControls(ProcButton_ButtonType, GetPropOption(m_buttonType, g_typeControlButtons));
		}
		//else if(pProp == m_buttonMouseMoveSound)
		//{
		//	std::wstring str;
		//	GetPropFile(m_buttonMouseMoveSound, str);
		//	LoopAllControls(ProcButton_MouseMoveSound, (LPARAM)str.c_str());
		//}
		//else if(pProp == m_buttonMouseMoveSoundClear)
		//{
		//	LoopAllControls(ProcButton_MouseMoveSound, 0);
		//}
		//
			return;
		this->SetModifyed(true);
	}
	else if(wnd == &m_imageProp)
	{
		if(pProp == m_imageSet)
		{
			BOOL bReset = false;
			if(!HIBYTE(GetKeyState(VK_CONTROL)))
				bReset=true;
			std::vector<ElementIn> elements;
			for(int i=0;i<this->m_treeView.GetSelectCount();i++)
			{
				HTREEITEM hItem		=	m_treeView.GetSelect(i);
				TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
				if(type)
				{
					if(type->type == this->UI_PROP_ELEMENTS)
					{
						Phantom::UIControl* c	=	this->m_dialogPtr->GetControlPtrFromID(type->p1);
						if(c && c->GetElementPtr(type->p2))
							elements.push_back(ElementIn(GetElementName(c->GetType(), type->p2), (LPARAM)c->GetElementPtr(type->p2), 0));
					}
				}
			}
			//
			if(m_imageSet->m_browser.size() > 1 && elements.size() > 1)
			{
				for(int i=0;i<m_imageSet->m_browser.size();i++)
				{
					this->GetSortFile(m_imageSet->m_browser[i], m_imageSet->m_browser[i].c_str());
				}
				CSetElementTextureDlg dlg(&this->m_imageProp);
				dlg.SetElements(elements, m_imageSet->m_browser);
				if(dlg.DoModal() == IDOK)
				{
					for(int i=0;i<dlg.m_elements.size();i++)
					{
						((Phantom::UIElement*)dlg.m_elements[i].param.param1)->SetTexture(Autf8(dlg.m_elements[i].str.c_str()).buf);
					}
				}
				m_imageSet->m_browser.clear();
			}
			else if(m_imageSet->m_browser.size() > 0)
			{
				std::wstring str;
				GetPropFile(m_imageSet, str);
				Phantom::UIElement* element = LoopAllElements(ProcElement_ImageSet, (LPARAM)str.c_str());
				if(element){
					//Phantom::CDynamicArray<Phantom::TextureRect>* rects	=	Phantom::GetDlgManager()->GetTextureRectPtr(element->GetTextureID());
					Phantom::TextureNode2D* tex = Phantom::GetDlgManager()->GetTextureNode(element->GetTextureID());
					if(tex->texturePtr){
						element->m_bWrap=false;
						element->SetSourceRect(Phantom::Rect(0, 0, tex->texturePtr->GetWidth(), tex->texturePtr->GetHeight()));
					}
				}
			}
			//
			this->OnChangeTreeSelect(&m_treeView, NULL);
			if(bReset){
				LoopAllElements(ProcElement_ImageRectReget);
				LoopAllElements(ProcElement_ImageUnitSide);
			}
		}
		//if(pProp == m_imageName)
		//{
		//	std::wstring str;
		//	GetPropText(m_imageName, str);
		//	LoopAllElements(ProcElement_ImageName, (LPARAM)str.c_str(), 0, true);
		//}
		//else 
		if(pProp == m_imageUnitSide)
		{
			LoopAllElements(ProcElement_ImageUnitSide);//, GetPropOption(m_imageUnitSide, g_type2DUnitSide));
		}
		else if(pProp == m_imageClear)
		{
			LoopAllElements(ProcElement_ImageClear);
		}
		else if(pProp == m_imageOpen)
		{
			LoopAllElements(ProcElement_ImageOpen);
		}
		else if(pProp == m_imageDefault)
		{
			LoopAllElements(ProcElement_ImageDefault, GetPropBool(m_imageDefault));
		}
		else if(pProp == m_imageScale)
		{
			BOOL	bEnable	=	GetPropBool(m_imageScale);
			LoopAllElements(ProcElement_ImageScale, GetPropBool(m_imageScale));
			m_imageContScale->Enable(bEnable);
			BOOL bCon	=	GetPropBool(m_imageContScale);
			m_imageContW->Enable(bEnable && bCon);
			m_imageContH->Enable(bEnable && bCon);
			//
			m_imageTileW->Enable(!bEnable);
			m_imageTileH->Enable(!bEnable);
			m_imageTileOffX->Enable(!bEnable);
			m_imageTileOffY->Enable(!bEnable);
			m_imageTileScaleX->Enable(!bEnable);
			m_imageTileScaleY->Enable(!bEnable);
			m_imageTileLingXing->Enable(!bEnable);
		}
		else if(pProp == m_imageContScale)
		{
			BOOL	bEnable	=	GetPropBool(m_imageContScale);
			LoopAllElements(ProcElement_ImageContScale, bEnable);
			m_imageContW->Enable(bEnable);
			m_imageContH->Enable(bEnable);
		}
		else if(pProp == m_imageContW)
		{
			LoopAllElements(ProcElement_ImageContW, GetPropInt(m_imageContW));
		}
		else if(pProp == m_imageContH)
		{
			LoopAllElements(ProcElement_ImageContH, GetPropInt(m_imageContH));
		}
		else if(pProp == m_imageTileW)
		{
			LoopAllElements(ProcElement_ImageTileW, GetPropInt(m_imageTileW));
		}
		else if(pProp == m_imageTileH)
		{
			LoopAllElements(ProcElement_ImageTileH, GetPropInt(m_imageTileH));
		}
		else if(pProp == m_imageTileOffX)
		{
			LoopAllElements(ProcElement_ImageTileOffX, GetPropInt(m_imageTileOffX));
		}
		else if(pProp == m_imageTileOffY)
		{
			LoopAllElements(ProcElement_ImageTileOffY, GetPropInt(m_imageTileOffY));
		}
		else if(pProp == m_imageTileScaleX)
		{
			LoopAllElements(ProcElement_ImageTileScaleX, (LPARAM)GetPropFloatPtr(m_imageTileScaleX));
		}
		else if(pProp == m_imageTileScaleY)
		{
			LoopAllElements(ProcElement_ImageTileScaleY, (LPARAM)GetPropFloatPtr(m_imageTileScaleY));
		}
		else if(pProp == m_imageTileLingXing)
		{
			LoopAllElements(ProcElement_ImageTileLX, GetPropBool(m_imageTileLingXing));
		}
		else if(pProp == m_imageLeft)
		{
			LoopAllElements(ProcElement_ImageRectLeft, GetPropInt(m_imageLeft));
		}
		else if(pProp == m_imageTop)
		{
			LoopAllElements(ProcElement_ImageRectTop, GetPropInt(m_imageTop));
		}
		else if(pProp == m_imageWidth)
		{
			LoopAllElements(ProcElement_ImageRectWidth, GetPropInt(m_imageWidth));
		}
		else if(pProp == m_imageHeight)
		{
			LoopAllElements(ProcElement_ImageRectHeight, GetPropInt(m_imageHeight));
		}
		else if(pProp == m_imageOffsetLeft)
		{
			LoopAllElements(ProcElement_ImageRectOffsetLeft, GetPropInt(m_imageOffsetLeft));
		}
		else if(pProp == m_imageOffsetTop)
		{
			LoopAllElements(ProcElement_ImageRectOffsetTop, GetPropInt(m_imageOffsetTop));
		}
		else if(pProp == m_imageOffsetWidth)
		{
			LoopAllElements(ProcElement_ImageRectOffsetWidth, GetPropInt(m_imageOffsetWidth));
		}
		else if(pProp == m_imageOffsetHeight)
		{
			LoopAllElements(ProcElement_ImageRectOffsetHeight, GetPropInt(m_imageOffsetHeight));
		}
		else if(pProp == m_imageLists)
		{
			std::wstring str;
			GetPropText(m_imageLists, str);
			char buf[1024];
			int len = ::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.size(), buf, 1024, 0, 0);
			buf[len] = 0;
			Phantom::UIElement* element = LoopAllElements(ProcElement_ImageMode, (LPARAM)buf);
			if(element){
				SetPropInt(m_imageLeft, element->GetSourceRect().left);
				SetPropInt(m_imageTop, element->GetSourceRect().top);
				SetPropInt(m_imageWidth, element->GetSourceRect().GetWidth());
				SetPropInt(m_imageHeight, element->GetSourceRect().GetHeight());
			}
		}
		else if(pProp == m_imageRandomMode)
		{
			Phantom::UIElement* element = LoopAllElements(ProcElement_RandomImage);
			if(element){
				SetPropInt(m_imageLeft, element->GetSourceRect().left);
				SetPropInt(m_imageTop, element->GetSourceRect().top);
				SetPropInt(m_imageWidth, element->GetSourceRect().GetWidth());
				SetPropInt(m_imageHeight, element->GetSourceRect().GetHeight());
			}
		}
		else if(pProp == m_imageRegetRect)
		{
			Phantom::UIElement* element = LoopAllElements(ProcElement_ImageRectReget);
			if(element){
				SetPropInt(m_imageLeft, element->GetSourceRect().left);
				SetPropInt(m_imageTop, element->GetSourceRect().top);
				SetPropInt(m_imageWidth, element->GetSourceRect().GetWidth());
				SetPropInt(m_imageHeight, element->GetSourceRect().GetHeight());
			}
		}
		else if(pProp == m_imageTextColor)
		{
			LoopAllElements(ProcElement_TextColor, GetPropColor(m_imageTextColor));
		}
		else if(pProp == m_imageTextAlpha)
		{
			LoopAllElements(ProcElement_TextColorA, (LPARAM)GetPropFloatPtr(m_imageTextAlpha));
		}
		//else if(pProp == m_imageShadowColor)
		//{
		//	LoopAllElements(ProcElement_ShadowColor, GetPropColor(m_imageShadowColor));
		//}
		//else if(pProp == m_imageShadowAlpha)
		//{
		//	LoopAllElements(ProcElement_ShadowColorA, (LPARAM)GetPropFloatPtr(m_imageShadowAlpha));
		//}
		else if(pProp == m_imageTextureColor)
		{
			LoopAllElements(ProcElement_TextureColor, (LPARAM)GetPropColor(m_imageTextureColor));
		}
		else if(pProp == m_imageTextureAlpha)
		{
			LoopAllElements(ProcElement_TextureColorA, (LPARAM)GetPropFloatPtr(m_imageTextureAlpha));
		}
		else if(pProp == m_imageColorOP)
		{
			LoopAllElements(ProcElement_ColorOP, GetPropOption(m_imageColorOP, g_typeColorOP));
		}
		else if(pProp == m_imageSrcBlend)
		{
			LoopAllElements(ProcElement_SrcBlend, GetPropOption(m_imageSrcBlend, g_typeBlend));
		}
		else if(pProp == m_imageDestBlend)
		{
			LoopAllElements(ProcElement_DestBlend, GetPropOption(m_imageDestBlend, g_typeBlend));
		}
		else if(pProp == m_imageFilter)
		{
			LoopAllElements(ProcElement_Filter, GetPropOption(m_imageFilter, g_typeFilter));
		}
		else if(pProp == m_imageUCount)
		{
			LoopAllElements(ProcElement_UCount, GetPropInt(m_imageUCount));
		}
		else if(pProp == m_imageVCount)
		{
			LoopAllElements(ProcElement_VCount, GetPropInt(m_imageVCount));
		}
		else if(pProp == m_imageInvW)
		{
			LoopAllElements(ProcElement_InvW, GetPropBool(m_imageInvW));
		}
		else if(pProp == m_imageInvH)
		{
			LoopAllElements(ProcElement_InvH, GetPropBool(m_imageInvH));
		}
		else if(pProp == m_imageUVPlaySpeed)
		{
			LoopAllElements(ProcElement_UVSpeed, (LPARAM)GetPropFloatPtr(m_imageUVPlaySpeed));
		}
		else
			return;
		this->SetModifyed(TRUE);
	}
	else if(wnd == &this->m_animationProp)
	{
		if(pProp == m_animationName)
		{
			std::wstring str;
			GetPropText(m_animationName, str);
			LoopAllAnimations(ProcAnimation3D_Name, (LPARAM)str.c_str(), 0, TRUE);
		}
		else if(pProp == m_animationFrameCount)
		{
			float f	=	GetPropFloat(m_animationFrameCount);
			LoopAllAnimations(ProcAnimation3D_FrameCount, (LPARAM)GetPropFloatPtr(m_animationFrameCount));
			this->m_animationTrack.SetTrackKeyCount((int)(GetPropFloat(m_animationFrameCount) * TRACK_SECOND_LENGTH));
		}
		//else if(pProp == m_animationIsDefault)
		//{
			//LoopAllAnimations(ProcAnimation3D_Default, GetPropBool(m_animationIsDefault));
		//}
		else if(pProp == m_animationSleepTime)
		{
			LoopAllAnimations(ProcAnimation3D_SleepTime, (LPARAM)GetPropFloatPtr(m_animationSleepTime));
		}
		else if(pProp == m_animationWaveSleepTime)
		{
			LoopAllAnimations(ProcAnimation3D_WaveSleepTime, (LPARAM)GetPropFloatPtr(m_animationWaveSleepTime));
		}
		else if(pProp == m_animationHideAtSleep)
		{
			LoopAllAnimations(ProcAnimation3D_HideAtSleep, (LPARAM)GetPropBool(m_animationHideAtSleep));
		}
		else if(pProp == m_animationHideOnOver)
		{
			LoopAllAnimations(ProcAnimation3D_HideOnOver, (LPARAM)GetPropBool(m_animationHideOnOver));
		}
		else if(pProp == m_animationSpeed)
		{
			float f	=	GetPropFloat(m_animationSpeed);
			LoopAllAnimations(ProcAnimation3D_Speed, (LPARAM)GetPropFloatPtr(m_animationSpeed));
			m_animationTrack.SetPlaySpeed(f);
		}
		else if(pProp == m_animationElement)
		{
			std::string str;
			GetPropText(m_animationElement, str);
			LoopAllAnimations(ProcAnimation3D_Element, (LPARAM)str.c_str());
		}
		else if(pProp == m_animationElementAni)
		{
			std::string str;
			GetPropText(m_animationElementAni, str);
			LoopAllAnimations(ProcAnimation3D_ElementAni, (LPARAM)str.c_str());
		}
		else if(pProp == m_animationLoopCount)
		{
			LoopAllAnimations(ProcAnimation3D_LoopCount, (LPARAM)GetPropInt(m_animationLoopCount));
		}
		else if(pProp == m_animationWaitEnable)
		{
			LoopAllAnimations(ProcAnimation3D_WaitEnable, (LPARAM)GetPropBool(m_animationWaitEnable));
		}
		else if(pProp == m_animationNextType)
		{
			LoopAllAnimations(ProcAnimation3D_NextID, (LPARAM)GetPropOption(m_animationNextType, g_typeUnitActionType));
		}
		else if(pProp == m_animationType)
		{
			LoopAllAnimations(ProcAnimation3D_UnitType, (LPARAM)GetPropOption(m_animationType, g_typeUnitActionType));
		}
		else if(pProp == m_animationWaveFile)
		{
			std::wstring str;
			GetPropFile(m_animationWaveFile, str);
			LoopAllAnimations(ProcAnimation3D_WaveFile, (LPARAM)A(str.c_str()).buf);
		}
		else if(pProp == m_animationWaveFileClear)
		{
			LoopAllAnimations(ProcAnimation3D_WaveFile, (LPARAM)"");
		}
		else if(pProp == m_animationWaveVolume)
		{
			LoopAllAnimations(ProcAnimation3D_WaveVolume, (LPARAM)GetPropFloatPtr(m_animationWaveVolume));
		}
		else if(pProp == m_animationWaveSpeed)
		{
			float f	=	GetPropFloat(m_animationWaveSpeed);
			LoopAllAnimations(ProcAnimation3D_WaveSpeed, (LPARAM)GetPropFloatPtr(m_animationWaveSpeed));
		}
		else
			return;
		this->SetModifyed(true);
	}
	else if(wnd == &this->m_uvmapProp)
	{
		if(pProp == m_uvmapName)
		{
			std::wstring str;
			GetPropText(m_uvmapName, str);
			LoopAllUVAnimations(ProcUVAnimation_Name, (LPARAM)str.c_str(), 0, TRUE);
		}
		else if(pProp == m_uvmapKeyLoopCount)
		{
			LoopAllUVAnimations(ProcUVAnimation_LoopCount, GetPropInt(m_uvmapKeyLoopCount), 0);
		}
		else if(pProp == m_uvmapAngle)
		{
			LoopAllUVAnimations(ProcUVAnimation_Angle, GetPropOption(m_uvmapAngle, g_type2DUnitAngle), 0, TRUE, false);
			this->m_treeView.ClearSelect();
		}
		else if(pProp == m_uvmapAutoImages)
		{
			std::wstring str;
			GetPropText(m_uvmapAutoImages, str);
			char ubuf[1024];
			int len = ::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.size(), ubuf, 1024, 0, 0);
			ubuf[len] = 0;
			LoopAllUVAnimations(ProcUVAnimation_Fills, (LPARAM)ubuf);
			SetPropText(m_uvmapAutoImages, L"");
		}
		else if(pProp == m_uvmapInvW)
		{
			LoopAllUVAnimations(ProcUVAnimation_InvW, (LPARAM)GetPropBool(m_uvmapInvW));
		}
		else if(pProp == m_uvmapInvH)
		{
			LoopAllUVAnimations(ProcUVAnimation_InvH, (LPARAM)GetPropBool(m_uvmapInvH));
		}
		else if(pProp == m_uvmapCustomEnable)
		{
			BOOL b	=	GetPropBool(m_uvmapCustomEnable);
			LoopAllUVAnimations(ProcUVAnimation_CustomEnable, b, 0, 0, true);
			this->m_uvmapCustomGroup->Enable(b);
			//
			m_uvmapSet->Enable(b);	//����ͼƬ
			m_uvmapClear->Enable(b);	//���ÿ�ͼƬ
		}
		else if(pProp == m_uvmapSet)
		{
			//
			std::wstring str;
			GetPropFile(m_uvmapSet, str);
			LoopAllUVAnimations(ProcUVAnimation_SetTextureID, (LPARAM)str.c_str(), 0);
		}
		else if(pProp == m_uvmapClear)
		{
			LoopAllUVAnimations(ProcUVAnimation_SetTextureID, 0, 0);
		}
		else if(pProp == m_uvmapRegetRects)
		{
			LoopAllUVAnimations(ProcUVAnimation_RegetRects, 0, 0);
		}
		else if(pProp == m_uvmapActionType)
		{
			LoopAllUVAnimations(ProcUVAnimation_SetAction, GetPropOption(m_uvmapActionType, g_typeUnitActionType), 0, TRUE, 0);
			this->m_treeView.ClearSelect();
		}
		else if(pProp == m_uvmapNextActionType)
		{
			LoopAllUVAnimations(ProcUVAnimation_SetNextAction, GetPropOption(m_uvmapNextActionType, g_typeUnitActionType), 0, TRUE);
		}
		else if(pProp == m_uvmapNextActionRand)
		{
			LoopAllUVAnimations(ProcUVAnimation_SetNextActionRand, (LPARAM)GetPropFloatPtr(m_uvmapNextActionRand), 0, false);
		}
		else if(pProp == m_uvmapMoveOffset)
		{
			BOOL b = GetPropBool(m_uvmapMoveOffset);
			LoopAllUVAnimations(ProcUVAnimation_MoveOffset, (LPARAM)b, 0, false);
			m_uvmapMoveOffsetX->Enable(b);
			m_uvmapMoveOffsetY->Enable(b);
			m_uvmapMoveOffsetSpeed->Enable(b);
		}
		else if(pProp == m_uvmapMoveOffsetX)
		{
			LoopAllUVAnimations(ProcUVAnimation_MoveOffsetX, (LPARAM)GetPropInt(m_uvmapMoveOffsetX), 0, false);
		}
		else if(pProp == m_uvmapMoveOffsetY)
		{
			LoopAllUVAnimations(ProcUVAnimation_MoveOffsetY, (LPARAM)GetPropInt(m_uvmapMoveOffsetY), 0, false);
		}
		else if(pProp == m_uvmapMoveOffsetSpeed)
		{
			LoopAllUVAnimations(ProcUVAnimation_MoveOffsetSpeed, (LPARAM)GetPropFloatPtr(m_uvmapMoveOffsetSpeed), 0, false);
		}

		else if(pProp == m_uvmapKeyPlaySpeed)
		{
			LoopAllUVAnimations(ProcUVAnimation_PlaySpeed, (LPARAM)GetPropFloatPtr(m_uvmapKeyPlaySpeed), 0);
		}
		else if(pProp == m_uvmapBeginIndex)
		{
			LoopAllUVAnimations(ProcUVAnimation_BeginIndex, GetPropInt(m_uvmapBeginIndex), 0);
		}
		else if(pProp == m_uvmapLayerAdd)
		{
			LoopAllUVAnimations(ProcUVAnimation_LayerAdd, GetPropInt(m_uvmapLayerAdd), 0);
		}
		else if(pProp == m_uvmapFrameCount)
		{
			int n	=	GetPropInt(m_uvmapFrameCount);
			LoopAllUVAnimations(ProcUVAnimation_FrameCount, GetPropInt(m_uvmapFrameCount), 0, 0, true);
		}
		else if(pProp == m_uvmapDefault)
		{
			LoopAllUVAnimations(ProcUVAnimation_Default, GetPropBool(m_uvmapDefault), 0, 0);
		}
		else
			return;
		this->SetModifyed(true);
	}
	else if(wnd == &m_uvmapRectProp)
	{
		if(pProp == m_uvmapLeft)
		{
			LoopAllUVAnimationsR(ProcUVAnimation_SetLeft, GetPropInt(m_uvmapLeft), 0, false);
		}
		else if(pProp == m_uvmapTop)
		{
			LoopAllUVAnimationsR(ProcUVAnimation_SetTop, GetPropInt(m_uvmapTop), 0, false);
		}
		else if(pProp == m_uvmapWidth)
		{
			LoopAllUVAnimationsR(ProcUVAnimation_SetWidth, GetPropInt(m_uvmapWidth), 0, false);
		}
		else if(pProp == m_uvmapHeight)
		{
			LoopAllUVAnimationsR(ProcUVAnimation_SetHeight, GetPropInt(m_uvmapHeight), 0, false);
		}
		else if(pProp == m_uvmapOffsetX)
		{
			LoopAllUVAnimationsR(ProcUVAnimation_OffsetX, GetPropInt(m_uvmapOffsetX), 0, false);
		}
		else if(pProp == m_uvmapOffsetY)
		{
			LoopAllUVAnimationsR(ProcUVAnimation_OffsetY, GetPropInt(m_uvmapOffsetY), 0, false);
		}
		else if(pProp == m_uvmapTexture)
		{
			std::wstring str;
			GetPropFile(m_uvmapTexture, str);
			LoopAllUVAnimationsR(ProcUVAnimation_TextureFile, (LPARAM)str.c_str());
		}
		else if(pProp == m_uvmapTextureClear)
		{
			LoopAllUVAnimationsR(ProcUVAnimation_TextureFile, (LPARAM)"");
		}
		else if(pProp == m_uvmapImageLists)
		{
			std::wstring str;
			GetPropText(m_uvmapImageLists, str);
			char buf[1024];
			int len = ::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.size(), buf, 1024, 0, 0);
			buf[len] = 0;
			LoopAllUVAnimationsR(ProcUVAnimation_ImageList, (LPARAM)buf, 0, true);
		}
		else if(pProp == m_uvmapUCount)
		{
			//LoopAllUVAnimations(ProcUVAnimation_UCount, GetPropInt(m_uvmapUCount), 0, TRUE);
		}
		else if(pProp == m_uvmapVCount)
		{
			//LoopAllUVAnimations(ProcUVAnimation_VCount, GetPropInt(m_uvmapVCount), 0, TRUE);
		}
	}
	else if(wnd == &m_groupProp)
	{
		if(pProp == m_groupName)
		{
			std::wstring str;
			GetPropText(m_groupName, str);
			LoopAllGroup(ProcGroup_Name, (LPARAM)str.c_str() , 0, TRUE);
		}
		else if(pProp == m_groupVisible)
		{
			LoopAllGroup(ProcGroup_Visible, GetPropBool(m_groupVisible));
		}
		else if(pProp == m_groupSleepTime)
		{
			LoopAllGroup(ProcGroup_SleepTime, (LPARAM)GetPropFloatPtr(m_groupSleepTime));
		}
		else if(pProp == m_groupIsUnit)
		{
			LoopAllGroup(ProcGroup_SetIsUnit, (LPARAM)GetPropBool(m_groupIsUnit));
		}
		else if(pProp == m_groupEnable)
		{
			LoopAllGroup(ProcGroup_SetEnable, (LPARAM)GetPropBool(m_groupEnable));
		}
		else if(pProp == m_groupAngle)
		{
			LoopAllGroup(ProcGroup_SetAngle, (LPARAM)GetPropFloatPtr(m_groupAngle));
		}
		else if(pProp == m_groupSpeed)
		{
			LoopAllGroup(ProcGroup_SetSpeed, (LPARAM)GetPropFloatPtr(m_groupSpeed));
		}
		else if(pProp == m_groupAction)
		{
			LoopAllGroup(ProcGroup_SetAction, (LPARAM)GetPropOption(m_groupAction, g_typeUnitActionType));
		}
	}
#ifdef USE_BOX
	else if(wnd == &m_bodyProp)
	{
		if(pProp == m_body_bodyType)
			LoopAllBodys(Box2DBody_BodyType, GetPropOption(m_body_bodyType, g_typeBox2DBodyType));
		else if(pProp == m_body_name)
		{
			std::string str;
			GetPropText(m_body_name, str);
			LoopAllBodys(Prop_m_body_name, (LPARAM)str.c_str(), 0, true);
		}
		else if(pProp == m_body_position_x )
			LoopAllBodys(Box2DBody_m_body_position_x, (LPARAM)this->GetPropFloatPtr(m_body_position_x));
		else if(pProp == m_body_position_y )
			LoopAllBodys(Box2DBody_m_body_position_y, (LPARAM)this->GetPropFloatPtr(m_body_position_y));
		else if(pProp == m_body_angle )
			LoopAllBodys(Box2DBody_m_body_angle, (LPARAM)this->GetPropFloatPtr(m_body_angle));
		else if(pProp == m_body_linearVelocity_x )
			LoopAllBodys(Box2DBody_m_body_linearVelocity_x, (LPARAM)this->GetPropFloatPtr(m_body_linearVelocity_x));
		else if(pProp == m_body_linearVelocity_y )
			LoopAllBodys(Box2DBody_m_body_linearVelocity_y, (LPARAM)this->GetPropFloatPtr(m_body_linearVelocity_y));
		else if(pProp == m_body_angularVelocity )
			LoopAllBodys(Box2DBody_m_body_angularVelocity, (LPARAM)this->GetPropFloatPtr(m_body_angularVelocity));
		else if(pProp == m_body_linearDamping )
			LoopAllBodys(Box2DBody_m_body_linearDamping, (LPARAM)this->GetPropFloatPtr(m_body_linearDamping));
		else if(pProp == m_body_angularDamping )
			LoopAllBodys(Box2DBody_m_body_angularDamping, (LPARAM)this->GetPropFloatPtr(m_body_angularDamping));
		else if(pProp == m_body_gravityScale )
			LoopAllBodys(Box2DBody_m_body_gravityScale, (LPARAM)this->GetPropFloatPtr(m_body_gravityScale));
		else if(pProp == m_body_allowSleep )
			LoopAllBodys(Box2DBody_m_body_allowSleep, (LPARAM)this->GetPropBool(m_body_allowSleep));
		else if(pProp == m_body_awake )
			LoopAllBodys(Box2DBody_m_body_awake, (LPARAM)this->GetPropBool(m_body_awake));
		else if(pProp == m_body_fixedRotation )
			LoopAllBodys(Box2DBody_m_body_fixedRotation, (LPARAM)this->GetPropBool(m_body_fixedRotation));
		else if(pProp == m_body_bullet )
			LoopAllBodys(Box2DBody_m_body_bullet, (LPARAM)this->GetPropBool(m_body_bullet));
		else if(pProp == m_body_active )
			LoopAllBodys(Box2DBody_m_body_active, (LPARAM)this->GetPropBool(m_body_active));
	}
	else if(wnd == &m_shapeProp)
	{
		if(pProp == m_shape_type)
		{
			LoopAllShapes(Box2DShape_m_shape_type, GetPropOption(m_shape_type, g_typeBox2DShapeType), 0, true);
		}
		else if(pProp == m_shape_control)
		{
			int nID	= 0;
			std::string str;
			GetPropText(m_shape_control, str);
			LoopAllShapes(Fn(m_shape_control), atoi(str.c_str()), 0, 0);
		}
		else if(pProp == m_shape_m_density)
			LoopAllShapes(Box2DShape_m_shape_m_density, (LPARAM)GetPropFloatPtr(m_shape_m_density));
		else if(pProp == m_shape_m_radius)
			LoopAllShapes(Box2DShape_m_shape_m_radius, (LPARAM)GetPropFloatPtr(m_shape_m_radius));
		else if(pProp == m_shape_m_p_x)
			LoopAllShapes(Box2DShape_m_shape_m_p_x, (LPARAM)GetPropFloatPtr(m_shape_m_p_x));
		else if(pProp == m_shape_m_p_y)
			LoopAllShapes(Box2DShape_m_shape_m_p_y, (LPARAM)GetPropFloatPtr(m_shape_m_p_y));
		else if(pProp == m_shape_m_fAngle)
			LoopAllShapes(Box2DShape_m_shape_m_fAngle, (LPARAM)GetPropFloatPtr(m_shape_m_fAngle));
		else if(pProp == m_shape_m_boxWidth)
			LoopAllShapes(Box2DShape_m_shape_m_boxWidth, (LPARAM)GetPropFloatPtr(m_shape_m_boxWidth));
		else if(pProp == m_shape_m_boxHeight)
			LoopAllShapes(Box2DShape_m_shape_m_boxHeight, (LPARAM)GetPropFloatPtr(m_shape_m_boxHeight));
		else if(pProp == m_shape_m_bChainLoop )
			LoopAllShapes(Box2DBody_m_shape_m_bChainLoop, (LPARAM)this->GetPropBool(m_shape_m_bChainLoop));
		else if(pProp == m_shape_m_hasVertex0 )
			LoopAllShapes(Box2DBody_m_shape_m_hasVertex0, (LPARAM)this->GetPropBool(m_shape_m_hasVertex0));
		else if(pProp == m_shape_m_hasVertex3 )
			LoopAllShapes(Box2DBody_m_shape_m_hasVertex3, (LPARAM)this->GetPropBool(m_shape_m_hasVertex3));
	}
	else if(wnd == &m_jointProp)
	{
		if(pProp == m_joint_jointType)
			LoopAllJoints(Box2DShape_m_joint_jointType, GetPropOption(m_joint_jointType, g_typeBox2DJointType), 0, true);
		else if(pProp == m_joint_name)
		{
			std::string str;
			GetPropText(m_joint_name, str);
			LoopAllJoints(Fn(m_joint_name), (LPARAM)str.c_str(), 0, true);
		}
		else if(pProp == m_joint_bodyA)
		{
			std::string str;
			GetPropText(m_joint_bodyA, str);
			LoopAllJoints(Fn(m_joint_bodyA), atoi(str.c_str()));
		}
		else if(pProp == m_joint_bodyB)
		{
			std::string str;
			GetPropText(m_joint_bodyB, str);
			LoopAllJoints(Fn(m_joint_bodyB), atoi(str.c_str()));
		}
		else if(pProp == m_joint_collideConnected)
			LoopAllJoints(Fn(m_joint_collideConnected), GetPropBool(m_joint_collideConnected));
		else if(pProp == m_joint_localAnchorA_x)
			LoopAllJoints(Fn(m_joint_localAnchorA_x), (LPARAM)GetPropFloatPtr(m_joint_localAnchorA_x));
		else if(pProp == m_joint_localAnchorA_y)
			LoopAllJoints(Fn(m_joint_localAnchorA_y), (LPARAM)GetPropFloatPtr(m_joint_localAnchorA_y));
		else if(pProp == m_joint_localAnchorB_x)
			LoopAllJoints(Fn(m_joint_localAnchorB_x), (LPARAM)GetPropFloatPtr(m_joint_localAnchorB_x));
		else if(pProp == m_joint_localAnchorB_y)
			LoopAllJoints(Fn(m_joint_localAnchorB_y), (LPARAM)GetPropFloatPtr(m_joint_localAnchorB_y));
		else if(pProp == m_joint_maxForce)
			LoopAllJoints(Fn(m_joint_maxForce), (LPARAM)GetPropFloatPtr(m_joint_maxForce));
		else if(pProp == m_joint_maxTorque)
			LoopAllJoints(Fn(m_joint_maxTorque), (LPARAM)GetPropFloatPtr(m_joint_maxTorque));
		else if(pProp == m_joint_joint1)
		{
			std::string str;
			GetPropText(m_joint_joint1, str);
			LoopAllJoints(Fn(m_joint_joint1), atoi(str.c_str()));
		}
		else if(pProp == m_joint_joint2)
		{
			std::string str;
			GetPropText(m_joint_joint2, str);
			LoopAllJoints(Fn(m_joint_joint2), atoi(str.c_str()));
		}
		else if(pProp == m_joint_ratio)
			LoopAllJoints(Fn(m_joint_ratio), (LPARAM)GetPropFloatPtr(m_joint_ratio));
		else if(pProp == m_joint_target_x)
			LoopAllJoints(Fn(m_joint_target_x), (LPARAM)GetPropFloatPtr(m_joint_target_x));
		else if(pProp == m_joint_target_y)
			LoopAllJoints(Fn(m_joint_target_y), (LPARAM)GetPropFloatPtr(m_joint_target_y));
		else if(pProp == m_joint_frequencyHz)
			LoopAllJoints(Fn(m_joint_frequencyHz), (LPARAM)GetPropFloatPtr(m_joint_frequencyHz));
		else if(pProp == m_joint_localAxisA_x)
			LoopAllJoints(Fn(m_joint_localAxisA_x), (LPARAM)GetPropFloatPtr(m_joint_localAxisA_x));
		else if(pProp == m_joint_localAxisA_y)
			LoopAllJoints(Fn(m_joint_localAxisA_y), (LPARAM)GetPropFloatPtr(m_joint_localAxisA_y));
		else if(pProp == m_joint_referenceAngle)
			LoopAllJoints(Fn(m_joint_referenceAngle), (LPARAM)GetPropFloatPtr(m_joint_referenceAngle));
		else if(pProp == m_joint_enableLimit)
			LoopAllJoints(Fn(m_joint_enableLimit), (LPARAM)GetPropBool(m_joint_enableLimit));
		else if(pProp == m_joint_lowerTranslation)
			LoopAllJoints(Fn(m_joint_lowerTranslation), (LPARAM)GetPropFloatPtr(m_joint_lowerTranslation));
		else if(pProp == m_joint_upperTranslation)
			LoopAllJoints(Fn(m_joint_upperTranslation), (LPARAM)GetPropFloatPtr(m_joint_upperTranslation));
		else if(pProp == m_joint_enableMotor)
			LoopAllJoints(Fn(m_joint_enableMotor), (LPARAM)GetPropBool(m_joint_enableMotor));
		else if(pProp == m_joint_maxMotorForce)
			LoopAllJoints(Fn(m_joint_maxMotorForce), (LPARAM)GetPropFloatPtr(m_joint_maxMotorForce));
		else if(pProp == m_joint_motorSpeed)
			LoopAllJoints(Fn(m_joint_motorSpeed), (LPARAM)GetPropFloatPtr(m_joint_motorSpeed));
		else if(pProp == m_joint_groundAnchorA_x)
			LoopAllJoints(Fn(m_joint_groundAnchorA_x), (LPARAM)GetPropFloatPtr(m_joint_groundAnchorA_x));
		else if(pProp == m_joint_groundAnchorA_y)
			LoopAllJoints(Fn(m_joint_groundAnchorA_y), (LPARAM)GetPropFloatPtr(m_joint_groundAnchorA_y));
		else if(pProp == m_joint_groundAnchorB_x)
			LoopAllJoints(Fn(m_joint_groundAnchorB_x), (LPARAM)GetPropFloatPtr(m_joint_groundAnchorB_x));
		else if(pProp == m_joint_groundAnchorB_y)
			LoopAllJoints(Fn(m_joint_groundAnchorB_y), (LPARAM)GetPropFloatPtr(m_joint_groundAnchorB_y));
		else if(pProp == m_joint_lengthA)
			LoopAllJoints(Fn(m_joint_lengthA), (LPARAM)GetPropFloatPtr(m_joint_lengthA));
		else if(pProp == m_joint_lengthB)
			LoopAllJoints(Fn(m_joint_lengthB), (LPARAM)GetPropFloatPtr(m_joint_lengthB));
		else if(pProp == m_joint_lowerAngle)
			LoopAllJoints(Fn(m_joint_lowerAngle), (LPARAM)GetPropFloatPtr(m_joint_lowerAngle));
		else if(pProp == m_joint_upperAngle)
			LoopAllJoints(Fn(m_joint_upperAngle), (LPARAM)GetPropFloatPtr(m_joint_upperAngle));
		else if(pProp == m_joint_maxMotorTorque)
			LoopAllJoints(Fn(m_joint_maxMotorTorque), (LPARAM)GetPropFloatPtr(m_joint_maxMotorTorque));
		else if(pProp == m_joint_maxLength)
			LoopAllJoints(Fn(m_joint_maxLength), (LPARAM)GetPropFloatPtr(m_joint_maxLength));
	}
#endif
}

VOID		GCViewUIEditor::SetShowSelectOnly(BOOL b)
{
	if(b)
	{
		m_controlVisibleMap.clear();
		for(int i=0;i<m_dialogPtr->GetControlCount();i++)
		{
			Phantom::UIControl* c	=	m_dialogPtr->GetControlPtr(i);
			m_controlVisibleMap[c->GetID()] = c->GetVisible();
		}
	}
	else
	{
		for(std::map<int, BOOL>::iterator it = m_controlVisibleMap.begin(); it != m_controlVisibleMap.end(); it++)
		{
			Phantom::UIControl* c	=	m_dialogPtr->GetControlPtrFromID(it->first);
			if(c)
				c->SetVisible(it->second);
		}
	}
}
#ifdef USE_BOX
VOID		GCViewUIEditor::OnShapeMode(Phantom::B2Shape* shape)
{
	m_shapeProp.EnableRender(false);
	SetPropFloat(m_shape_m_density, shape->m_data.m_density);
	Phantom::Pixel lv	=	m_dialogPtr->m_box2World.GetScreenPixelSize(shape->m_data.m_p);
	int		ra	=	m_dialogPtr->m_box2World.GetScreenPixelX(shape->m_data.m_radius);
	SetPropFloat(m_shape_m_radius, ra);
	SetPropFloat(m_shape_m_p_x, lv.x);
	SetPropFloat(m_shape_m_p_y, lv.y);
	SetPropFloat(m_shape_m_fAngle, shape->m_data.m_fAngle);
	//
	Phantom::Pixel box	=	m_dialogPtr->m_box2World.GetScreenPixelSize(Phantom::float2(shape->m_data.m_boxWidth, shape->m_data.m_boxHeight));
	SetPropFloat(m_shape_m_boxWidth, box.x);
	SetPropFloat(m_shape_m_boxHeight, box.y);
	SetPropBool(m_shape_m_bChainLoop, shape->m_data.m_bChainLoop);
	SetPropBool(m_shape_m_hasVertex0, shape->m_data.m_hasVertex0);
	SetPropBool(m_shape_m_hasVertex3, shape->m_data.m_hasVertex3);
	switch(shape->m_data.type)
	{
	case b2Shape::e_circle:
		{
			m_shape_m_radius->Show(true);
			m_shape_m_p_x->Show(true);
			m_shape_m_p_y->Show(true);
			m_shape_m_fAngle->Show(false);
			m_shape_m_boxWidth->Show(false);
			m_shape_m_boxHeight->Show(false);
			m_shape_m_bChainLoop->Show(false);
			m_shape_m_hasVertex0->Show(false);
			m_shape_m_hasVertex3->Show(false);
		}
		break;
	case b2Shape::e_edge:
		{
			m_shape_m_radius->Show(false);
			m_shape_m_p_x->Show(false);
			m_shape_m_p_y->Show(false);
			m_shape_m_fAngle->Show(false);
			m_shape_m_boxWidth->Show(false);
			m_shape_m_boxHeight->Show(false);
			m_shape_m_bChainLoop->Show(false);
			m_shape_m_hasVertex0->Show(true);
			m_shape_m_hasVertex3->Show(true);
		}
		break;
	case b2Shape::e_polygon:
		{
			m_shape_m_radius->Show(false);
			m_shape_m_p_x->Show(false);
			m_shape_m_p_y->Show(false);
			m_shape_m_fAngle->Show(false);
			m_shape_m_boxWidth->Show(false);
			m_shape_m_boxHeight->Show(false);
			m_shape_m_bChainLoop->Show(false);
			m_shape_m_hasVertex0->Show(false);
			m_shape_m_hasVertex3->Show(false);
		}
		break;
	case b2Shape::e_chain:
		{
			m_shape_m_radius->Show(false);
			m_shape_m_p_x->Show(false);
			m_shape_m_p_y->Show(false);
			m_shape_m_fAngle->Show(false);
			m_shape_m_boxWidth->Show(false);
			m_shape_m_boxHeight->Show(false);
			m_shape_m_bChainLoop->Show(true);
			m_shape_m_hasVertex0->Show(false);
			m_shape_m_hasVertex3->Show(false);
		}
		break;
	case Phantom::B2ShapeData::e_polygon_box:
		{
			m_shape_m_radius->Show(false);
			m_shape_m_p_x->Show(false);
			m_shape_m_p_y->Show(false);
			m_shape_m_fAngle->Show(true);
			m_shape_m_boxWidth->Show(true);
			m_shape_m_boxHeight->Show(true);
			m_shape_m_bChainLoop->Show(false);
			m_shape_m_hasVertex0->Show(false);
			m_shape_m_hasVertex3->Show(false);
		}
		break;
	}
	m_shapeProp.EnableRender(true);
}

VOID		GCViewUIEditor::OnJointMode(Phantom::B2Joint* joint)
{
	m_jointProp.EnableRender(false);
	m_joint_bodyA->RemoveAllOptions();
	m_joint_bodyB->RemoveAllOptions();
	m_joint_bodyA->AddOption(L"");
	m_joint_bodyB->AddOption(L"");
	NameW selA, selB;
	for(int i=0;i<m_dialogPtr->m_box2World.GetBodyCount();i++)
	{
		char buf[128];
		sprintf(buf, "%d[%s]", m_dialogPtr->m_box2World.GetBodyPtr(i)->m_bodyData.id, m_dialogPtr->m_box2World.GetBodyPtr(i)->m_bodyData.name.t);
		m_joint_bodyA->AddOption(W(buf));
		m_joint_bodyB->AddOption(W(buf));
		if(m_dialogPtr->m_box2World.GetBodyPtr(i)->m_bodyData.id == joint->m_data.bodyA)
			selA	=	W(buf);
		if(m_dialogPtr->m_box2World.GetBodyPtr(i)->m_bodyData.id == joint->m_data.bodyB)
			selB	=	W(buf);
	}
	SetPropText(m_joint_bodyA, selA);
	SetPropText(m_joint_bodyB, selB);
	SetPropBool(m_joint_collideConnected, joint->m_data.collideConnected);
	SetPropFloat(m_joint_localAnchorA_x, m_dialogPtr->m_box2World.GetScreenPixelX(joint->m_data.localAnchorA.x));
	SetPropFloat(m_joint_localAnchorA_y, m_dialogPtr->m_box2World.GetScreenPixelY(joint->m_data.localAnchorA.y));
	SetPropFloat(m_joint_localAnchorB_x, m_dialogPtr->m_box2World.GetScreenPixelX(joint->m_data.localAnchorB.x));
	SetPropFloat(m_joint_localAnchorB_y, m_dialogPtr->m_box2World.GetScreenPixelY(joint->m_data.localAnchorB.y));
	//
	SetPropFloat(m_joint_maxForce, joint->m_data.maxForce);
	SetPropFloat(m_joint_maxTorque, joint->m_data.maxTorque);
	//
	m_joint_joint1->RemoveAllOptions();
	m_joint_joint2->RemoveAllOptions();
	m_joint_joint1->AddOption(L"");
	m_joint_joint2->AddOption(L"");
	selA	=	L"";
	selB	=	L"";
	for(int i=0;i<m_dialogPtr->m_box2World.GetJointCount();i++)
	{
		if(m_dialogPtr->m_box2World.GetJointPtr(i) == joint)
			break;
		char buf[128];
		sprintf(buf, "%d[%s]", m_dialogPtr->m_box2World.GetJointPtr(i)->m_data.id, m_dialogPtr->m_box2World.GetJointPtr(i)->m_data.name.t);
		m_joint_joint1->AddOption(W(buf));
		m_joint_joint2->AddOption(W(buf));
		if(m_dialogPtr->m_box2World.GetJointPtr(i)->m_data.id == joint->m_data.joint1)
			selA	=	W(buf);
		if(m_dialogPtr->m_box2World.GetJointPtr(i)->m_data.id == joint->m_data.joint2)
			selB	=	W(buf);
	}
	//
	SetPropFloat(m_joint_ratio, joint->m_data.ratio);//or mouse dumping Ratio, or pulley radio
	SetPropFloat(m_joint_target_x, joint->m_data.target.x);//or mouse dumping Ratio, or pulley radio
	SetPropFloat(m_joint_target_y, joint->m_data.target.y);//or mouse dumping Ratio, or pulley radio
	SetPropFloat(m_joint_frequencyHz, joint->m_data.frequencyHz);//or mouse dumping Ratio, or pulley radio
	SetPropFloat(m_joint_localAxisA_x, joint->m_data.localAxisA.x);//or mouse dumping Ratio, or pulley radio
	SetPropFloat(m_joint_localAxisA_y, joint->m_data.localAxisA.y);//or mouse dumping Ratio, or pulley radio
	//
	SetPropFloat(m_joint_referenceAngle, joint->m_data.referenceAngle);//or mouse dumping Ratio, or pulley radio
	SetPropBool(m_joint_enableLimit, joint->m_data.enableLimit);//or mouse dumping Ratio, or pulley radio
	SetPropBool(m_joint_enableMotor, joint->m_data.enableMotor);//or mouse dumping Ratio, or pulley radio
	SetPropFloat(m_joint_lowerTranslation, joint->m_data.lowerTranslation);
	SetPropFloat(m_joint_upperTranslation, joint->m_data.upperTranslation);
	SetPropFloat(m_joint_maxMotorForce, joint->m_data.maxMotorForce);
	SetPropFloat(m_joint_motorSpeed, joint->m_data.motorSpeed);
	//
	SetPropFloat(m_joint_groundAnchorA_x, joint->m_data.groundAnchorA.x);
	SetPropFloat(m_joint_groundAnchorA_y, joint->m_data.groundAnchorA.y);
	SetPropFloat(m_joint_groundAnchorB_x, joint->m_data.groundAnchorB.x);
	SetPropFloat(m_joint_groundAnchorB_y, joint->m_data.groundAnchorB.y);
	//
	SetPropFloat(m_joint_lengthA, joint->m_data.lengthA);
	SetPropFloat(m_joint_lengthB, joint->m_data.lengthB);
	SetPropFloat(m_joint_lowerAngle, joint->m_data.lowerAngle);
	SetPropFloat(m_joint_upperAngle, joint->m_data.upperAngle);
	SetPropFloat(m_joint_maxMotorTorque, joint->m_data.maxMotorTorque);
	SetPropFloat(m_joint_maxLength, joint->m_data.maxLength);
	//
	switch(joint->m_data.jointType)
	{
	case e_revoluteJoint:
		m_joint_localAnchorA_x->Show(true);
		m_joint_localAnchorA_y->Show(true);//êand prismatic ,pulley, revolute
		m_joint_localAnchorB_x->Show(false);
		m_joint_localAnchorB_y->Show(false);//êand prismatic ,pulley, revolute
		m_joint_maxForce->Show(false);//ǿ��and mouse
		m_joint_maxTorque->Show(false);//ת��
		m_joint_joint1->Show(false);
		m_joint_joint2->Show(false);//id
		m_joint_ratio->Show(false);//or mouse dumping Ratio, or pulley radio
		m_joint_target_x->Show(false);
		m_joint_target_y->Show(false);
		m_joint_frequencyHz->Show(false);
		m_joint_localAxisA_x->Show(false);
		m_joint_localAxisA_y->Show(false);//��
		m_joint_referenceAngle->Show(true);//revolute
		m_joint_enableLimit->Show(true);//revolute
		m_joint_lowerTranslation->Show(false);
		m_joint_upperTranslation->Show(false);
		m_joint_enableMotor->Show(true);//revolute
		m_joint_maxMotorForce->Show(false);
		m_joint_motorSpeed->Show(true);//and revolute
		m_joint_groundAnchorA_x->Show(false);
		m_joint_groundAnchorA_y->Show(false);
		m_joint_groundAnchorB_x->Show(false);
		m_joint_groundAnchorB_y->Show(false);
		m_joint_lengthA->Show(false);
		m_joint_lengthB->Show(false);
		m_joint_lowerAngle->Show(true);
		m_joint_upperAngle->Show(true);
		m_joint_maxMotorTorque->Show(true);
		m_joint_maxLength->Show(false);
		break;
	case e_prismaticJoint:
		m_joint_localAnchorA_x->Show(true);
		m_joint_localAnchorA_y->Show(true);//êand prismatic ,pulley, revolute
		m_joint_localAnchorB_x->Show(false);
		m_joint_localAnchorB_y->Show(false);//êand prismatic ,pulley, revolute
		m_joint_maxForce->Show(false);//ǿ��and mouse
		m_joint_maxTorque->Show(false);//ת��
		m_joint_joint1->Show(false);
		m_joint_joint2->Show(false);//id
		m_joint_ratio->Show(false);//or mouse dumping Ratio, or pulley radio
		m_joint_target_x->Show(false);
		m_joint_target_y->Show(false);
		m_joint_frequencyHz->Show(false);
		m_joint_localAxisA_x->Show(true);
		m_joint_localAxisA_y->Show(true);//��
		m_joint_referenceAngle->Show(true);//revolute
		m_joint_enableLimit->Show(true);//revolute
		m_joint_lowerTranslation->Show(true);
		m_joint_upperTranslation->Show(true);
		m_joint_enableMotor->Show(true);//revolute
		m_joint_maxMotorForce->Show(true);
		m_joint_motorSpeed->Show(true);//and revolute
		m_joint_groundAnchorA_x->Show(false);
		m_joint_groundAnchorA_y->Show(false);
		m_joint_groundAnchorB_x->Show(false);
		m_joint_groundAnchorB_y->Show(false);
		m_joint_lengthA->Show(false);
		m_joint_lengthB->Show(false);
		m_joint_lowerAngle->Show(false);
		m_joint_upperAngle->Show(false);
		m_joint_maxMotorTorque->Show(false);
		m_joint_maxLength->Show(false);
		break;
	case e_distanceJoint:
		m_joint_localAnchorA_x->Show(true);
		m_joint_localAnchorA_y->Show(true);//êand prismatic ,pulley, revolute
		m_joint_localAnchorB_x->Show(true);
		m_joint_localAnchorB_y->Show(true);//êand prismatic ,pulley, revolute
		m_joint_maxForce->Show(false);//ǿ��and mouse
		m_joint_maxTorque->Show(false);//ת��
		m_joint_joint1->Show(false);
		m_joint_joint2->Show(false);//id
		m_joint_ratio->Show(true);//or mouse dumping Ratio, or pulley radio
		m_joint_target_x->Show(false);
		m_joint_target_y->Show(false);
		m_joint_frequencyHz->Show(true);
		m_joint_localAxisA_x->Show(false);
		m_joint_localAxisA_y->Show(false);//��
		m_joint_referenceAngle->Show(false);//revolute
		m_joint_enableLimit->Show(false);//revolute
		m_joint_lowerTranslation->Show(false);
		m_joint_upperTranslation->Show(false);
		m_joint_enableMotor->Show(false);//revolute
		m_joint_maxMotorForce->Show(false);
		m_joint_motorSpeed->Show(false);//and revolute
		m_joint_groundAnchorA_x->Show(false);
		m_joint_groundAnchorA_y->Show(false);
		m_joint_groundAnchorB_x->Show(false);
		m_joint_groundAnchorB_y->Show(false);
		m_joint_lengthA->Show(false);
		m_joint_lengthB->Show(false);
		m_joint_lowerAngle->Show(false);
		m_joint_upperAngle->Show(false);
		m_joint_maxMotorTorque->Show(false);
		m_joint_maxLength->Show(true);
		break;
	case e_pulleyJoint:
		m_joint_localAnchorA_x->Show(true);
		m_joint_localAnchorA_y->Show(true);//êand prismatic ,pulley, revolute
		m_joint_localAnchorB_x->Show(true);
		m_joint_localAnchorB_y->Show(true);//êand prismatic ,pulley, revolute
		m_joint_maxForce->Show(false);//ǿ��and mouse
		m_joint_maxTorque->Show(false);//ת��
		m_joint_joint1->Show(false);
		m_joint_joint2->Show(false);//id
		m_joint_ratio->Show(true);//or mouse dumping Ratio, or pulley radio
		m_joint_target_x->Show(false);
		m_joint_target_y->Show(false);
		m_joint_frequencyHz->Show(false);
		m_joint_localAxisA_x->Show(false);
		m_joint_localAxisA_y->Show(false);//��
		m_joint_referenceAngle->Show(false);//revolute
		m_joint_enableLimit->Show(false);//revolute
		m_joint_lowerTranslation->Show(false);
		m_joint_upperTranslation->Show(false);
		m_joint_enableMotor->Show(false);//revolute
		m_joint_maxMotorForce->Show(false);
		m_joint_motorSpeed->Show(false);//and revolute
		m_joint_groundAnchorA_x->Show(true);
		m_joint_groundAnchorA_y->Show(true);
		m_joint_groundAnchorB_x->Show(true);
		m_joint_groundAnchorB_y->Show(true);
		m_joint_lengthA->Show(false);
		m_joint_lengthB->Show(false);
		m_joint_lowerAngle->Show(false);
		m_joint_upperAngle->Show(false);
		m_joint_maxMotorTorque->Show(false);
		m_joint_maxLength->Show(false);
		break;
	case e_mouseJoint:
		m_joint_localAnchorA_x->Show(false);
		m_joint_localAnchorA_y->Show(false);//êand prismatic ,pulley, revolute
		m_joint_localAnchorB_x->Show(false);
		m_joint_localAnchorB_y->Show(false);//êand prismatic ,pulley, revolute
		m_joint_maxForce->Show(true);//ǿ��and mouse
		m_joint_maxTorque->Show(false);//ת��
		m_joint_joint1->Show(false);
		m_joint_joint2->Show(false);//id
		m_joint_ratio->Show(true);//or mouse dumping Ratio, or pulley radio
		m_joint_target_x->Show(true);
		m_joint_target_y->Show(true);
		m_joint_frequencyHz->Show(true);
		m_joint_localAxisA_x->Show(false);
		m_joint_localAxisA_y->Show(false);//��
		m_joint_referenceAngle->Show(false);//revolute
		m_joint_enableLimit->Show(false);//revolute
		m_joint_lowerTranslation->Show(false);
		m_joint_upperTranslation->Show(false);
		m_joint_enableMotor->Show(false);//revolute
		m_joint_maxMotorForce->Show(false);
		m_joint_motorSpeed->Show(false);//and revolute
		m_joint_groundAnchorA_x->Show(false);
		m_joint_groundAnchorA_y->Show(false);
		m_joint_groundAnchorB_x->Show(false);
		m_joint_groundAnchorB_y->Show(false);
		m_joint_lengthA->Show(false);
		m_joint_lengthB->Show(false);
		m_joint_lowerAngle->Show(false);
		m_joint_upperAngle->Show(false);
		m_joint_maxMotorTorque->Show(false);
		m_joint_maxLength->Show(false);
		break;
	case e_gearJoint:
		m_joint_localAnchorA_x->Show(false);
		m_joint_localAnchorA_y->Show(false);//êand prismatic ,pulley, revolute
		m_joint_localAnchorB_x->Show(false);
		m_joint_localAnchorB_y->Show(false);//êand prismatic ,pulley, revolute
		m_joint_maxForce->Show(false);//ǿ��and mouse
		m_joint_maxTorque->Show(false);//ת��
		m_joint_joint1->Show(true);
		m_joint_joint2->Show(true);//id
		m_joint_ratio->Show(true);//or mouse dumping Ratio, or pulley radio
		m_joint_target_x->Show(false);
		m_joint_target_y->Show(false);
		m_joint_frequencyHz->Show(false);
		m_joint_localAxisA_x->Show(false);
		m_joint_localAxisA_y->Show(false);//��
		m_joint_referenceAngle->Show(false);//revolute
		m_joint_enableLimit->Show(false);//revolute
		m_joint_lowerTranslation->Show(false);
		m_joint_upperTranslation->Show(false);
		m_joint_enableMotor->Show(false);//revolute
		m_joint_maxMotorForce->Show(false);
		m_joint_motorSpeed->Show(false);//and revolute
		m_joint_groundAnchorA_x->Show(false);
		m_joint_groundAnchorA_y->Show(false);
		m_joint_groundAnchorB_x->Show(false);
		m_joint_groundAnchorB_y->Show(false);
		m_joint_lengthA->Show(false);
		m_joint_lengthB->Show(false);
		m_joint_lowerAngle->Show(false);
		m_joint_upperAngle->Show(false);
		m_joint_maxMotorTorque->Show(false);
		m_joint_maxLength->Show(false);
		break;
	case e_wheelJoint:
		m_joint_localAnchorA_x->Show(true);
		m_joint_localAnchorA_y->Show(true);//êand prismatic ,pulley, revolute
		m_joint_localAnchorB_x->Show(false);
		m_joint_localAnchorB_y->Show(false);//êand prismatic ,pulley, revolute
		m_joint_maxForce->Show(false);//ǿ��and mouse
		m_joint_maxTorque->Show(false);//ת��
		m_joint_joint1->Show(false);
		m_joint_joint2->Show(false);//id
		m_joint_ratio->Show(true);//or mouse dumping Ratio, or pulley radio
		m_joint_target_x->Show(false);
		m_joint_target_y->Show(false);
		m_joint_frequencyHz->Show(true);
		m_joint_localAxisA_x->Show(true);
		m_joint_localAxisA_y->Show(true);//��
		m_joint_referenceAngle->Show(false);//revolute
		m_joint_enableLimit->Show(false);//revolute
		m_joint_lowerTranslation->Show(false);
		m_joint_upperTranslation->Show(false);
		m_joint_enableMotor->Show(true);//revolute
		m_joint_maxMotorForce->Show(false);
		m_joint_motorSpeed->Show(true);//and revolute
		m_joint_groundAnchorA_x->Show(false);
		m_joint_groundAnchorA_y->Show(false);
		m_joint_groundAnchorB_x->Show(false);
		m_joint_groundAnchorB_y->Show(false);
		m_joint_lengthA->Show(false);
		m_joint_lengthB->Show(false);
		m_joint_lowerAngle->Show(false);
		m_joint_upperAngle->Show(false);
		m_joint_maxMotorTorque->Show(true);
		m_joint_maxLength->Show(false);
		break;
	case e_weldJoint:
		m_joint_localAnchorA_x->Show(true);
		m_joint_localAnchorA_y->Show(true);//êand prismatic ,pulley, revolute
		m_joint_localAnchorB_x->Show(false);
		m_joint_localAnchorB_y->Show(false);//êand prismatic ,pulley, revolute
		m_joint_maxForce->Show(false);//ǿ��and mouse
		m_joint_maxTorque->Show(false);//ת��
		m_joint_joint1->Show(false);
		m_joint_joint2->Show(false);//id
		m_joint_ratio->Show(true);//or mouse dumping Ratio, or pulley radio
		m_joint_target_x->Show(false);
		m_joint_target_y->Show(false);
		m_joint_frequencyHz->Show(true);
		m_joint_localAxisA_x->Show(false);
		m_joint_localAxisA_y->Show(false);//��
		m_joint_referenceAngle->Show(true);//revolute
		m_joint_enableLimit->Show(false);//revolute
		m_joint_lowerTranslation->Show(false);
		m_joint_upperTranslation->Show(false);
		m_joint_enableMotor->Show(false);//revolute
		m_joint_maxMotorForce->Show(false);
		m_joint_motorSpeed->Show(false);//and revolute
		m_joint_groundAnchorA_x->Show(false);
		m_joint_groundAnchorA_y->Show(false);
		m_joint_groundAnchorB_x->Show(false);
		m_joint_groundAnchorB_y->Show(false);
		m_joint_lengthA->Show(false);
		m_joint_lengthB->Show(false);
		m_joint_lowerAngle->Show(false);
		m_joint_upperAngle->Show(false);
		m_joint_maxMotorTorque->Show(false);
		m_joint_maxLength->Show(false);
		break;
	case e_frictionJoint:
		m_joint_localAnchorA_x->Show(true);
		m_joint_localAnchorA_y->Show(true);//êand prismatic ,pulley, revolute
		m_joint_localAnchorB_x->Show(false);
		m_joint_localAnchorB_y->Show(false);//êand prismatic ,pulley, revolute
		m_joint_maxForce->Show(true);//ǿ��and mouse
		m_joint_maxTorque->Show(true);//ת��
		m_joint_joint1->Show(false);
		m_joint_joint2->Show(false);//id
		m_joint_ratio->Show(false);//or mouse dumping Ratio, or pulley radio
		m_joint_target_x->Show(false);
		m_joint_target_y->Show(false);
		m_joint_frequencyHz->Show(false);
		m_joint_localAxisA_x->Show(false);
		m_joint_localAxisA_y->Show(false);//��
		m_joint_referenceAngle->Show(false);//revolute
		m_joint_enableLimit->Show(false);//revolute
		m_joint_lowerTranslation->Show(false);
		m_joint_upperTranslation->Show(false);
		m_joint_enableMotor->Show(false);//revolute
		m_joint_maxMotorForce->Show(false);
		m_joint_motorSpeed->Show(false);//and revolute
		m_joint_groundAnchorA_x->Show(false);
		m_joint_groundAnchorA_y->Show(false);
		m_joint_groundAnchorB_x->Show(false);
		m_joint_groundAnchorB_y->Show(false);
		m_joint_lengthA->Show(false);
		m_joint_lengthB->Show(false);
		m_joint_lowerAngle->Show(false);
		m_joint_upperAngle->Show(false);
		m_joint_maxMotorTorque->Show(false);
		m_joint_maxLength->Show(false);
		break;
	case e_ropeJoint:
		m_joint_localAnchorA_x->Show(true);
		m_joint_localAnchorA_y->Show(true);//êand prismatic ,pulley, revolute
		m_joint_localAnchorB_x->Show(false);
		m_joint_localAnchorB_y->Show(false);//êand prismatic ,pulley, revolute
		m_joint_maxForce->Show(false);//ǿ��and mouse
		m_joint_maxTorque->Show(false);//ת��
		m_joint_joint1->Show(false);
		m_joint_joint2->Show(false);//id
		m_joint_ratio->Show(false);//or mouse dumping Ratio, or pulley radio
		m_joint_target_x->Show(false);
		m_joint_target_y->Show(false);
		m_joint_frequencyHz->Show(false);
		m_joint_localAxisA_x->Show(false);
		m_joint_localAxisA_y->Show(false);//��
		m_joint_referenceAngle->Show(false);//revolute
		m_joint_enableLimit->Show(false);//revolute
		m_joint_lowerTranslation->Show(false);
		m_joint_upperTranslation->Show(false);
		m_joint_enableMotor->Show(false);//revolute
		m_joint_maxMotorForce->Show(false);
		m_joint_motorSpeed->Show(false);//and revolute
		m_joint_groundAnchorA_x->Show(false);
		m_joint_groundAnchorA_y->Show(false);
		m_joint_groundAnchorB_x->Show(false);
		m_joint_groundAnchorB_y->Show(false);
		m_joint_lengthA->Show(false);
		m_joint_lengthB->Show(false);
		m_joint_lowerAngle->Show(false);
		m_joint_upperAngle->Show(false);
		m_joint_maxMotorTorque->Show(false);
		m_joint_maxLength->Show(true);
		break;
	}
	//
	m_jointProp.EnableRender(true);
}
#endif
int	sortTRect(const void* v1, const void* v2)
{
	Phantom::TextureRect* r1 = (Phantom::TextureRect*)v1;
	Phantom::TextureRect* r2 = (Phantom::TextureRect*)v2;
	return stricmp(r1->name.t, r2->name.t);
}

VOID		GCViewUIEditor::OnChangeTreeSelect()
{
	TreeItemType* type	=	this->GetSelectedItem();
	if(!type)
	{
		SetCurrentProperties(&m_viewerProps, L"�ļ�����", NULL);
		return;
	}
	switch(type->type)
	{
	case UI_PROP_ACTION_TYPE:
		{
			m_animationTrack.ClearAnimationPtr();
			this->m_dialogPtr->PlayAction((Phantom::ActionType)type->p1);
		}
		break;
#ifdef USE_BOX
	case UI_PROP_B2_BODY:
		{
			if(!m_dialogPtr->m_box2World.IsEnable())
				return;
			m_animationTrack.ClearAnimationPtr();
			if(this->m_nEditorFlags == UIEditorFlags_TrackAnimation)this->SetEditorFlags(UIControlType_NONE);
			m_bodyProp.EnableRender(false);
			SetCurrentProperties(&m_bodyProp, L"Box2D��������", 0);
			if(m_dialogPtr->m_pakdir)m_bodyProp.DisableEditor();
			//
			Phantom::B2Body* body	=	m_dialogPtr->m_box2World.GetBodyPtr(Phantom::PtrID(0, type->p1));
			if(!body)
				return;
			SetPropInt(m_body_id, body->m_bodyData.id);
			SetPropText(m_body_name, body->m_bodyData.name.t);
			SetPropOption(m_body_bodyType, g_typeBox2DBodyType, body->m_bodyData.bodyType);
			Phantom::Pixel pos	=	m_dialogPtr->m_box2World.GetScreenPixelSize(body->m_bodyData.position);
			SetPropFloat(m_body_position_x, pos.x);
			SetPropFloat(m_body_position_y, pos.y);
			SetPropFloat(m_body_angle, body->m_bodyData.angle);
			//
			Phantom::Pixel lv	=	m_dialogPtr->m_box2World.GetScreenPixelSize(body->m_bodyData.linearVelocity);
			SetPropFloat(m_body_linearVelocity_x, lv.x);
			SetPropFloat(m_body_linearVelocity_y, lv.y);
			SetPropFloat(m_body_angularVelocity, body->m_bodyData.angularVelocity);
			//
			SetPropFloat(m_body_linearDamping, body->m_bodyData.linearDamping);
			SetPropFloat(m_body_angularDamping, body->m_bodyData.angularDamping);
			SetPropFloat(m_body_gravityScale, body->m_bodyData.gravityScale);
			SetPropBool(m_body_allowSleep, body->m_bodyData.allowSleep);
			SetPropBool(m_body_awake, body->m_bodyData.awake);
			SetPropBool(m_body_fixedRotation, body->m_bodyData.fixedRotation);
			SetPropBool(m_body_bullet, body->m_bodyData.bullet);
			SetPropBool(m_body_active, body->m_bodyData.active);
			m_bodyProp.EnableRender(true);
		}
		break;
	case UI_PROP_B2_SHAPE:
		{
			if(!m_dialogPtr->m_box2World.IsEnable())
				return;
			m_animationTrack.ClearAnimationPtr();
			if(this->m_nEditorFlags == UIEditorFlags_TrackAnimation)this->SetEditorFlags(UIControlType_NONE);
			SetCurrentProperties(&m_shapeProp, L"Box2D��״����", 0);
			if(m_dialogPtr->m_pakdir)m_shapeProp.DisableEditor();
			Phantom::B2Body* body	=	m_dialogPtr->m_box2World.GetBodyPtr(Phantom::PtrID(0, type->p1));
			if(!body)
				return;
			Phantom::B2Shape* shape	=	body->GetShapePtr(Phantom::PtrID(0, type->p2));
			if(!shape)
				return;
			SetPropInt(m_shape_id, shape->m_data.id);
			SetPropOption(m_shape_type, g_typeBox2DShapeType, shape->m_data.type);
			m_shape_control->RemoveAllOptions();
			m_shape_control->AddOption(L"");
			NameW sel;
			for(int i=0;i<this->m_dialogPtr->GetControlCount();i++)
			{
				//if(m_dialogPtr->GetControlPtr(i)->GetAutoSort())
				{
					wchar_t buf[256];
					swprintf(buf, L"%d[%s]", m_dialogPtr->GetControlPtr(i)->GetID(), Wutf8(m_dialogPtr->GetControlPtr(i)->GetName()).buf);
					m_shape_control->AddOption(buf);
					if(m_dialogPtr->GetControlPtr(i)->GetID() == shape->m_data.m_bindControl.id)
						sel = buf;
				}
			}
			SetPropText(m_shape_control, sel);
			OnShapeMode(shape);
		}
		break;
	case UI_PROP_B2_JOINT:
		{
			if(!m_dialogPtr->m_box2World.IsEnable())
				return;
			m_animationTrack.ClearAnimationPtr();
			if(this->m_nEditorFlags == UIEditorFlags_TrackAnimation)this->SetEditorFlags(UIControlType_NONE);
			SetCurrentProperties(&m_jointProp, L"Box2D��״����", 0);
			if(m_dialogPtr->m_pakdir)m_jointProp.DisableEditor();
			Phantom::B2Joint* joint	=	m_dialogPtr->m_box2World.GetJointPtr(Phantom::PtrID(0, type->p1));
			if(!joint)
				return;
			SetPropInt(m_joint_id, joint->m_data.id);
			SetPropText(m_joint_name, joint->m_data.name.t);
			SetPropOption(m_joint_jointType, g_typeBox2DJointType, joint->m_data.jointType);
			OnJointMode(joint);
		}
		break;
#endif
	case UI_PROP_MAIN:
		{
			m_animationTrack.ClearAnimationPtr();
			if(this->m_nEditorFlags == UIEditorFlags_TrackAnimation)this->SetEditorFlags(UIControlType_NONE);
			m_dlgProp.EnableRender(false);
			SetCurrentProperties(&m_dlgProp, L"��������", 0);
			if(m_dialogPtr->m_pakdir)m_dlgProp.DisableEditor();
			//
			SetPropBool(m_dlgAlwaysVisible, this->m_bAlwaysVisible);
			//SetPropBool(m_dlgAnimationEnable, m_dialogPtr->IsEnableDlgAnim());
			//SetPropOption(m_dlgAlignLR, g_typeDialogAlignLR, m_dialogPtr->GetDialogAlignLR());
			//SetPropOption(m_dlgAlignTB, g_typeDialogAlignTB, m_dialogPtr->GetDialogAlignTB());
			//SetPropInt(m_dlgOffsetX, m_dialogPtr->GetDialogAlignOffsetLR());
			//SetPropInt(m_dlgOffsetY, m_dialogPtr->GetDialogAlignOffsetTB());
			{
				SetPropBool(m_dlgMapEnable, m_dialogPtr->GetMapEnable());
				SetPropBool(m_dlgMap25DMode, m_dialogPtr->m_bMap25DMode);
				SetPropInt(m_dlgMapSizeX, m_dialogPtr->GetMapGridSize().cx);
				SetPropInt(m_dlgMapSizeY, m_dialogPtr->GetMapGridSize().cy);
				SetPropInt(m_dlgMapCountX, m_dialogPtr->GetMapGridCount().cx);
				SetPropInt(m_dlgMapCountY, m_dialogPtr->GetMapGridCount().cy);
				SetPropInt(m_dlgMapOffsetX, m_dialogPtr->m_mapGridBegin.x);
				SetPropInt(m_dlgMapOffsetY, m_dialogPtr->m_mapGridBegin.y);
			}
			SetPropBool(m_dlgIs2DGame, m_dialogPtr->IsBackgroundWindow());
			int x = 0;
			int y = 0;
			m_dialogPtr->GetLocation(x,y);
			SetPropInt(m_dlgX, x);
			SetPropInt(m_dlgY, y);
			SetPropColor(m_dlgColor, m_dialogPtr->GetDialogColor().getRGB());
			SetPropFloat(m_dlgAlpha, m_dialogPtr->GetDialogColor().a);
			m_dlgProp.EnableRender(true);
			//
			for(int i=0;i<m_dialogPtr->GetControlCount();i++)
			{
				m_dialogPtr->GetControlPtr(i)->ActiveTrackByName(NULL);
			}
		}
		break;
	case UI_PROP_CONTROL:
		{
			m_animationTrack.ClearAnimationPtr();
			if(this->m_nEditorFlags == UIEditorFlags_TrackAnimation)this->SetEditorFlags(UIControlType_NONE);
			Phantom::UIControl* control	=	m_dialogPtr->GetControlPtrFromID(type->p1);
			if(control->GetType() == Phantom::UIControlType_ui2DEffect)
				SetCurrentProperties(&m_controlProp, L"�ؼ�����", &this->m_animationTrack);//&m_uiEventSet);
			else
				SetCurrentProperties(&m_controlProp, L"�ؼ�����", 0);//&m_uiEventSet);
			//
			if(m_dialogPtr->m_pakdir)m_controlProp.DisableEditor();
			m_controlProp.EnableRender(false);
			if(!control)
			{
				m_controlProp.EnableWindow(FALSE);
				m_controlProp.EnableRender(true);
				break;
			}
			m_controlProp.EnableWindow(TRUE);
			BOOL bShowText	=	true;
			BOOL bShowTip	=	true;
			BOOL bShowRot	=	true;
			//
			control->GetGroupPtr()->SetPlayTime(0);
			//m_controlCursorName->RemoveAllOptions();
			//for(int i=0;i<GetCursorManager()->GetCursorCount();i++)
			//	m_controlCursorName->AddOption(W(GetCursorManager()->GetCursorPtr(i)->GetCursorName()));
			//
			this->m_controlParent->RemoveAllOptions();
			NameW selectParent = Language(L"��");
			m_controlParent->AddOption(selectParent);
			for(int i=0;i<this->m_dialogPtr->GetControlCount();i++)
			{
				if(m_dialogPtr->GetControlPtr(i) == control)
					continue;
				wchar_t buf[256];
				swprintf(buf, L"%s[%d]", Wutf8(m_dialogPtr->GetControlPtr(i)->GetName()).buf, i + 1);
				m_controlParent->AddOption(buf);
				if(m_dialogPtr->GetControlPtr(i) == control->GetParentControl())
					selectParent	=	buf;
			}
			SetPropText(m_controlParent, selectParent);
			//
			//SetPropInt(m_controlID, control->GetID());
			//SetPropText(m_controlToolTipText, control->GetToolTipText());
			//SetPropOption(m_controlToolTipAlign, g_typeToolTipAlign, control->GetToolTipPopupType());
			SetPropText(m_controlName, Wutf8(control->GetName()));
			//
			SetPropInt(m_controlLeft, control->GetRenderRect().left);
			SetPropInt(m_controlTop, control->GetRenderRect().top);
			SetPropInt(m_controlWidth, control->GetRenderRect().GetWidth());
			SetPropInt(m_controlHeight, control->GetRenderRect().GetHeight());
			int nWidth	=	control->GetElementPtr(0)->GetSourceRect().GetWidth();
			if(nWidth < 1)nWidth = 1;
			SetPropFloat(m_controlScale, (float)control->GetRenderRect().GetWidth() / (float)nWidth);
			int amode = control->m_nAlignMode;//GetAlignMode();
			if((amode&0x01)>0)
				SetPropOption(m_controlAlignModeW, g_typeAlignModeW, 1);
			else if((amode&0x02)>0)
				SetPropOption(m_controlAlignModeW, g_typeAlignModeW, 2);
			else if((amode&0x04)>0)
				SetPropOption(m_controlAlignModeW, g_typeAlignModeW, 3);
			else if((amode&0x08)>0)
				SetPropOption(m_controlAlignModeW, g_typeAlignModeW, 4);
			else
				SetPropOption(m_controlAlignModeW, g_typeAlignModeW, 0);
			if((amode&0x10)>0)
				SetPropOption(m_controlAlignModeH, g_typeAlignModeH, 1);
			else if((amode&0x20)>0)
				SetPropOption(m_controlAlignModeH, g_typeAlignModeH, 2);
			else if((amode&0x40)>0)
				SetPropOption(m_controlAlignModeH, g_typeAlignModeH, 3);
			else if((amode&0x80)>0)
				SetPropOption(m_controlAlignModeH, g_typeAlignModeH, 4);
			else
				SetPropOption(m_controlAlignModeH, g_typeAlignModeH, 0);
			//SetPropBool(m_controlVisibleOnScript, control->GetVisibleOnScript());
			m_controlGroupID->RemoveAllOptions();
			NameW select;
			for(int i=0;i<m_dialogPtr->GetGroupCount();i++)
			{
				wchar_t buf[256];
				swprintf(buf, L"%s[%d]", Wutf8(m_dialogPtr->GetGroupPtr(i)->GetName()).buf, m_dialogPtr->GetGroupPtr(i)->GetID());
				m_controlGroupID->AddOption(buf);//m_dialogPtr->GetGroupPtr(i)->GetName());
				if(m_dialogPtr->GetGroupPtr(i)->GetID() == control->GetGroupID())
					select = buf;
			}
			SetPropText(m_controlGroupID, select);//m_dialogPtr->GetGroupPtr(control->GetGroupID())->GetName());//g_typeControlGroup, control->GetGroupID());
			//
			SetPropBool(m_controlMoveDialog, control->GetParentMove());
			SetPropBool(m_controlBackground, control->IsBackground());
			SetPropOption(m_controlLayer, g_typeControlLayer, control->GetLayer());
			SetPropBool(m_controlIsGrid, control->m_bIsGridObject);
			SetPropInt(m_controlGridOffset, control->m_sGridOffsetY);
			m_controlGridOffset->Enable(control->m_bIsGridObject);
			//SetPropInt(m_controlContext, control->GetContext());
			SetPropOption(m_controlTextAlignLR, g_typeTextAlignLR, (control->GetTextFormat() & (DT_LEFT | DT_CENTER | DT_RIGHT))>0);
			SetPropOption(m_controlTextAlignTB, g_typeTextAlignTB, (control->GetTextFormat() & (DT_TOP | DT_VCENTER | DT_BOTTOM))>0);
			//
			SetPropBool(m_controlVisible, control->GetVisible());
			SetPropBool(m_controlCanActive, control->GetCanFocus());
			SetPropBool(m_controlEnable, control->GetEnabled());
			SetPropBool(m_controlSelect, control->m_bSelect);
			//SetPropBool(m_controlAniCenter, GetControlAniCenter(control));
			SetPropBool(m_controlEnableImgText, control->IsEnableUseImageText());
			SetPropText(m_controlImgTextBegin, control->m_szNumberBegin);
			SetPropInt(m_controlImgSizeAdd, control->m_numberSizeAdd);
			m_controlImgTextBegin->Enable(control->IsEnableUseImageText());
			m_controlImgSizeAdd->Enable(control->IsEnableUseImageText());
			//SetPropInt(m_controlShadowWidth, control->ShowTextShadow());
			//SetPropColor(m_controlShadowColor, Phantom::color4(control->GetShadowColor()).getRGB());
			//SetPropFloat(m_controlShadowAlpha, Phantom::color4(control->GetShadowColor()).a);
			//
			SetPropText(m_controlText, Wutf8(control->GetText()).buf);
			SetPropColor(m_controlTextColor, control->GetTextColor().getRGB());
			SetPropColor(m_controlTextureColor, control->GetTextureColor().getRGB());
			SetPropBool(m_controlImageFont, control->m_bUseImageFont);
			SetPropFloat(m_controlTextAlpha, control->GetTextColor().a);
			SetPropFloat(m_controlTextureAlpha, control->GetTextureColor().a);
			SetPropInt(m_controlTabIndex, control->GetTabIndex());
			//SetPropText(m_controlCursorName, control->GetCursorName());
			//
			SetPropBool(m_controlIsGroupCenter, control->m_bIsGroupCenter);
			SetPropBool(m_controlRotation, control->IsRotation());
			SetPropBool(m_controlPixel, control->IsPickPixel());
			SetPropInt(m_controlCenterX, control->GetRotCenter().x);
			SetPropInt(m_controlCenterY, control->GetRotCenter().y);
			SetPropFloat(m_controlAngle, control->GetRotationAngle());
			Phantom::FontNode2D* node	=	Phantom::GetDlgManager()->GetFontNode(control->GetElementPtr(0)->GetFontID());
			SetPropFont(m_controlFont, node);
			m_controlFont->Enable(!control->m_bUseImageFont);
			//
			SetPropInt(m_editSBWidth, control->GetScrollBarWidth());
			m_editSBWidth->Enable(control->GetScrollBar() != NULL);
			if(control->GetType()==Phantom::UIControlType_EDITBOX)
			{
				m_editGroup->Show(TRUE);
				SetPropBool(m_editPassword, static_cast<Phantom::UITextBox*>(control)->m_bPassword);
				//SetPropBool(m_editEnableIME, control->GetType()==Phantom::UIControlType_EDITBOX->IsEnableIME());
				SetPropBool(m_editReadOnly, control->GetReadOnly());
				//SetPropBool(m_editIndicator, control->GetType()==Phantom::UIControlType_EDITBOX->GetRenderIndicator());
				//SetPropBool(m_editCandList, control->GetType()==Phantom::UIControlType_EDITBOX->GetRenderCandList());
				//SetPropInt(m_editBorderWidth, control->GetType()==Phantom::UIControlType_EDITBOX->GetRenderBorder());
				//m_editSBWidth->Enable(control->m_scrollBarWidth);
				//SetPropColor(m_editCaretColor, Phantom::color4(control->GetType()==Phantom::UIControlType_EDITBOX->GetCaretColor()));
				//SetPropColor(m_editSelectTextColor, Phantom::color4(control->GetType()==Phantom::UIControlType_EDITBOX->GetSelectedTextColor()));
				//SetPropColor(m_editSelectBackColor, Phantom::color4(static_cast<Phantom::UI->GetSelectedBackColor()));
			}
			else
				m_editGroup->Show(FALSE);
			if(control->GetType() == UIControlType_PROGRESS)
			{
				m_progressGroup->Show(TRUE);
				SetPropOption(m_progressMode, g_typeProgress, control->GetProgressType());
				SetPropFloat(m_progressValue, control->GetProgressValue());
				SetPropInt(m_progressSize, static_cast<Phantom::UIProgress*>(control)->m_chInnerSize);
			}
			else
				m_progressGroup->Show(FALSE);
			//
			if(control->GetType()==Phantom::UIControlType_COMBOBOX)
			{
				m_comboGroup->Show(TRUE);
				SetPropInt(m_comboDropHeight, static_cast<Phantom::UIComboBox*>(control)->GetDropHeight());
				std::vector<std::wstring> lists;
				for(int i=0;i<static_cast<Phantom::UIComboBox*>(control)->GetNumItems();i++)
					lists.push_back(Wutf8(static_cast<Phantom::UIComboBox*>(control)->GetItemText(i)).buf);
				SetPropList(m_comboValues, lists);
			}
			else
				m_comboGroup->Show(FALSE);
			//
			//if(control->GetFormatEditBox())
			//{
			//	this->m_formatEditGroup->Show(TRUE);
			//	SetPropColor(m_formatEditEventColor, Phantom::color4(control->GetFormatEditBox()->GetEventColor()));
			//	SetPropColor(m_formatEditSelectColor, Phantom::color4(control->GetFormatEditBox()->GetSelectColor()));
			//	SetPropInt(m_formatEditLineHeight, control->GetFormatEditBox()->GetLineSpacingHeight());
			//}
			//else
				this->m_formatEditGroup->Show(FALSE);
			//listbox
			if(control->GetType()==Phantom::UIControlType_LISTBOX)
			{
				m_listboxGroup->Show(TRUE);
				SetPropInt(m_listboxLineHeight, static_cast<Phantom::UIListBox*>(control)->GetLineHeight());
				SetPropInt(m_listboxTextLeft, static_cast<Phantom::UIListBox*>(control)->GetLineTextFirst());
				std::vector<std::wstring> lists;
				for(int i=0;i<static_cast<Phantom::UIListBox*>(control)->GetNumItems();i++)
					lists.push_back(Wutf8(static_cast<Phantom::UIListBox*>(control)->GetItemText(i)).buf);
				SetPropList(m_listboxValues, lists);
			}
			else
				m_listboxGroup->Show(FALSE);
			//listbox
			if(control->GetType()==Phantom::UIControlType_LISTCTRL3D)
			{
				m_listctrlGroup->Show(TRUE);
				SetPropInt(m_listctrlLineHeight, static_cast<Phantom::UIListCtrl*>(control)->GetLineHeight());
				SetPropInt(m_listctrlColumnHeight, static_cast<Phantom::UIListCtrl*>(control)->GetColumnHeight());
				SetPropInt(m_listctrlTextLeft, static_cast<Phantom::UIListCtrl*>(control)->GetLineTextFirst());
				SetPropBool(m_listctrlSortEnable, static_cast<Phantom::UIListCtrl*>(control)->IsSortEnable());
				std::vector<std::wstring> lists;
				for(int i=0;i<static_cast<Phantom::UIListCtrl*>(control)->GetColumnCount();i++)
				{
					wchar_t buf[128];
					swprintf(buf, L"%s|%d", static_cast<Phantom::UIListCtrl*>(control)->GetColumnText(i), static_cast<Phantom::UIListCtrl*>(control)->GetColumnWidth(i));
					lists.push_back(buf);
				}
				SetPropList(m_listctrlColumns, lists);
				std::vector<std::wstring> values;
				wchar_t buf[10240];
				for(int item=0;item<static_cast<Phantom::UIListCtrl*>(control)->GetNumItems();item++)
				{
					buf[0]	=	0;
					for(int i=0;i<static_cast<Phantom::UIListCtrl*>(control)->GetColumnCount();i++)
					{
						wcscat(buf, Wutf8(static_cast<Phantom::UIListCtrl*>(control)->GetItemText(item, i)).buf);
						wcscat(buf, L"|");
					}
					values.push_back(buf);
				}
				SetPropList(m_listctrlItems, values);
			}
			else
				m_listctrlGroup->Show(FALSE);
			if(control->GetType() == Phantom::UIControlType_CHECKBOX)
			{
				m_checkboxGroup->Show(TRUE);
				SetPropBool(m_checkboxChecked, control->GetChecked());
			}
			else
				m_checkboxGroup->Show(FALSE);
			if(control->GetType() == Phantom::UIControlType_ui2DEffect)
			{
				m_effectGroup->Show(TRUE);
				SetPropFloat(m_effectFrameCount, (float)static_cast<Phantom::UIEffect*>(control)->GetFrameCount() / TRACK_SECOND_LENGTH);
				SetPropInt(m_effectLoopCount, static_cast<Phantom::UIEffect*>(control)->GetLoopCount());
				SetPropFloat(m_effectPlaySpeed, control->GetPlaySpeed());
			}
			else
				m_effectGroup->Show(FALSE);
			if(control->GetType()==Phantom::UIControlType_STATIC)
			{
				m_staticGroup->Show(TRUE);
				SetPropInt(m_staticBorderWidth, static_cast<Phantom::UIStatic*>(control)->GetBorderWidth());
				//SetPropOption(m_staticMouseSrcBlend, g_typeBlend, control->m_mouse GetMouseEnterSrc());
				//SetPropBool(m_staticMouseEnable, control->GetMouseEnterEffect());
				//SetPropOption(m_staticMouseDestBlend, g_typeBlend, control->GetMouseEnterDest());
				SetPropColor(m_staticTextureColor, control->m_textureColor);
				SetPropFloat(m_staticTextureAlpha, control->m_textureColor.a);
			}
			else
				m_staticGroup->Show(FALSE);
			if(control->GetType() == Phantom::UIControlType_BUTTON)
			{
				m_buttonGroup->Show(TRUE);
				SetPropFile(this->m_buttonClickSound, control->GetSoundPlayID(Phantom::UISoundPlay_buttonDown));
				//SetPropFile(this->m_buttonMouseMoveSound, control->GetSoundPlayID(Phantom::UISoundPlay_mouseIn));
				SetPropOption(m_buttonType, g_typeControlButtons, control->GetButtonType());
			}
			else
				m_buttonGroup->Show(FALSE);
			//
			m_terrainGroup->Show(FALSE);
			//m_unit2DGroup->Show(FALSE);
			//
			m_controlTextGroup->Show(bShowText);
			m_controlRotGroup->Show(bShowRot);
			//
			SetPropBool(m_controlDrawFocus, control->IsDrawFocusFrame());
			SetPropFloat(m_controlSleepTime, control->GetSleepTime());
			SetPropOption(m_controlUnitAngle8, g_typeUnitAngleType, control->GetEnableUnitAngle());
			SetPropBool(m_controlIs2DUnit, control->GetAutoSort());
			if(control->GetActiveTrack())
			{
//				control->GetActiveTrack()->SetPlayType(Phantom::PlayAnimationType_Play);
				control->GetActiveTrack()->SetCurFrame(control->m_playdata, 0);
			}
			//
			OnTreeSelectControl(control);
			m_controlProp.EnableRender(true);
			control->ActiveTrackByName(NULL);
			//m_uiEventSet.SetControlPtr(control);
			//
			if(control->GetGroupPtr()->GetGroupIsUnit())
			{
				control->GetGroupPtr()->SetPlayTime(0);
				control->PlayAction(control->GetGroupPtr()->GetPlayAction());
				//
			}
			else if(control->GetAutoSort())
			{
				Phantom::ActionType	t	=	control->GetPlayAction();
				if(t == Phantom::ActionType_None)
					t	=	Phantom::ActionType_Idle;
				control->PlayAction(t);
			}
			if(control->GetType() == Phantom::UIControlType_ui2DEffect)
			{
				Phantom::UIEffect* effect	=	static_cast<Phantom::UIEffect*>(control);
				m_animationTrack.BeginSet();
				m_animationTrack.SetPlaySpeed(control->GetPlaySpeed());
				m_animationTrack.SetAnimationPtr(UI_VALUE_TextureColorMin, effect->GetAnimationPtr(Phantom::EffectRandom_TextureColorMin), effect->GetAnimationPtr(Phantom::EffectRandom_TextureColorMax), 0, Language(L"��ɫ���"));
				m_animationTrack.SetAnimationPtr(UI_VALUE_OffsetMin, effect->GetAnimationPtr(Phantom::EffectRandom_OffsetMin), effect->GetAnimationPtr(Phantom::EffectRandom_OffsetMax), 0, Language(L"λ�����"));
				m_animationTrack.SetAnimationPtr(UI_VALUE_SizeMin, effect->GetAnimationPtr(Phantom::EffectRandom_SizeMin), effect->GetAnimationPtr(Phantom::EffectRandom_SizeMax), 0, Language(L"��С���"));
				m_animationTrack.SetAnimationPtr(UI_VALUE_RotationMin, effect->GetAnimationPtr(Phantom::EffectRandom_RotationMin), effect->GetAnimationPtr(Phantom::EffectRandom_RotationMax), 0, Language(L"���䷽�����"));
				m_animationTrack.SetAnimationPtr(UI_VALUE_LifeMin, effect->GetAnimationPtr(Phantom::EffectRandom_LifeMin), effect->GetAnimationPtr(Phantom::EffectRandom_LifeMax), 0, Language(L"��������"));
				m_animationTrack.SetAnimationPtr(UI_VALUE_EmitCount, effect->GetAnimationPtr(Phantom::EffectRandom_EmitCount), 0, 0, Language(L"��������"));
				m_animationTrack.EndSet();
				//
			}
		}
		break;
	case UI_PROP_ELEMENTS:
		{
			m_animationTrack.ClearAnimationPtr();
			if(this->m_nEditorFlags == UIEditorFlags_TrackAnimation)this->SetEditorFlags(UIControlType_NONE);
			SetCurrentProperties(&m_imageProp, L"�ؼ�ͼƬ����", 0);
			if(m_dialogPtr->m_pakdir)m_imageProp.DisableEditor();
			//
			Phantom::UIControl* control	=	m_dialogPtr->GetControlPtrFromID(type->p1);
			m_imageProp.EnableRender(false);
			Phantom::UIElement* element = 0;
			if(!control || !(element = control->GetElementPtr(type->p2)))
			{
				m_imageProp.EnableWindow(FALSE);
				m_imageProp.EnableRender(true);
				break;
			}
			m_imageProp.EnableWindow(TRUE);
			control->GetGroupPtr()->SetPlayTime(0);
			//
			Phantom::TextureNode2D* tex	=	Phantom::GetDlgManager()->GetTextureNode(element->GetTextureID());
			Phantom::CDynamicArray<Phantom::TextureRect>* rects	=	Phantom::GetDlgManager()->GetTextureRectPtr(element->GetTextureID());
			SetPropFile(m_imageSet, tex ? Wutf8(tex->fileName.t).buf : L"");
			SetPropColor(m_imageTextureColor, element->GetTextureColor());
			SetPropFloat(m_imageTextureAlpha, element->GetTextureColor().a);
			SetPropBool(m_imageDefault, element->m_bNoTexture);
			//SetPropText(m_imageName, element->GetElementName());
			//
			SetPropOption(m_imageColorOP, g_typeColorOP, element->GetColorOP());
			SetPropOption(m_imageSrcBlend, g_typeBlend, element->GetSrcBlend());
			SetPropOption(m_imageDestBlend, g_typeBlend, element->GetDestBlend());
			SetPropOption(m_imageFilter, g_typeFilter, element->m_imageFilter);
			//
			SetPropInt(m_imageLeft, element->GetSourceRect().left);
			SetPropInt(m_imageTop, element->GetSourceRect().top);
			SetPropInt(m_imageWidth, element->GetSourceRect().GetWidth());
			SetPropInt(m_imageHeight, element->GetSourceRect().GetHeight());
			//
			SetPropInt(m_imageOffsetLeft, element->GetRectOffset().left);
			SetPropInt(m_imageOffsetTop, element->GetRectOffset().top);
			SetPropInt(m_imageOffsetWidth, element->GetRectOffset().GetWidth());
			SetPropInt(m_imageOffsetHeight, element->GetRectOffset().GetHeight());
			m_imageLists->RemoveAllOptions();
			if(rects && rects->size()>0)
			{
				const wchar_t* szName	=	Language(L"");
				m_imageLists->AddOption(szName);
				NameW select = szName;
				Phantom::CDynamicArray<Phantom::TextureRect> tempR = *rects;
				qsort(tempR.GetPtr(), tempR.size(), sizeof(Phantom::TextureRect), sortTRect);
				for(int i=0;i<tempR.size();i++)
				{
					Wutf8 w(tempR.GetPtr()[i].name);
					m_imageLists->AddOption(w.buf);
					if(stricmp(tempR.GetPtr()[i].name, element->m_textureMode.t) == 0)
						select	=	w.buf;
				}
				SetPropText(m_imageLists, select);
				bool bEnable	=	(element->m_textureMode.t[0] == 0);
				m_imageLeft->Enable(bEnable);
				m_imageTop->Enable(bEnable);
				m_imageWidth->Enable(bEnable);
				m_imageHeight->Enable(bEnable);
			}
			m_imageLists->Enable(rects!=0&&rects->size()>0);
			m_imageRandomMode->Enable(rects!=0&&rects->size()>0);
			//
			SetPropBool(m_imageScale, element->GetRenderScale());
			SetPropBool(m_imageContScale, element->GetRenderScaleAsWrap());
			RefreshImageScale();
			//
			SetPropInt(m_imageContW, element->GetWrapWidth().x);
			SetPropInt(m_imageContH, element->GetWrapWidth().y);
			//
			SetPropInt(m_imageTileW, element->GetTileWidth());
			SetPropInt(m_imageTileH, element->GetTileHeight());
			SetPropInt(m_imageTileOffX, element->m_nTileOffX);
			SetPropInt(m_imageTileOffY, element->m_nTileOffY);
			SetPropFloat(m_imageTileScaleX, element->m_nTileScaleX);
			SetPropFloat(m_imageTileScaleY, element->m_nTileScaleY);
			SetPropBool(m_imageTileLingXing, element->m_tileXieJiao);
			//
			SetPropColor(m_imageTextColor, element->GetTextColor());
			SetPropFloat(m_imageTextAlpha, element->GetTextColor().a);
			//
			//SetPropColor(m_imageShadowColor, element->GetShadowColor());
			//SetPropFloat(m_imageShadowAlpha, element->GetShadowColor().a);
			//
			m_imageContScale->Enable(element->GetRenderScale());
			m_imageContW->Enable(element->GetRenderScaleAsWrap());
			m_imageContH->Enable(element->GetRenderScaleAsWrap());
			//
			m_imageTileOffX->Enable(!element->GetRenderScale());
			m_imageTileOffY->Enable(!element->GetRenderScale());
			m_imageTileScaleX->Enable(!element->GetRenderScale());
			m_imageTileScaleY->Enable(!element->GetRenderScale());
			m_imageTileW->Enable(!element->GetRenderScale());
			m_imageTileH->Enable(!element->GetRenderScale());
			m_imageTileLingXing->Enable(!element->GetRenderScale());
			//
			int nwidth = 0, nheight = 0;
			element->GetUVAnimation(nwidth, nheight);
			SetPropInt(m_imageUCount, nwidth);
			SetPropInt(m_imageVCount, nheight);
			SetPropBool(m_imageInvW, element->IsInvW());
			SetPropBool(m_imageInvH, element->IsInvH());
			SetPropFloat(m_imageUVPlaySpeed, element->GetUVPlaySpeed());
			//
			m_imageOffsetLeft->Enable(control->GetType() == UIControlType_BUTTON);
			m_imageOffsetTop->Enable(control->GetType() == UIControlType_BUTTON);
			m_imageOffsetWidth->Enable(control->GetType() == UIControlType_BUTTON);
			m_imageOffsetHeight->Enable(control->GetType() == UIControlType_BUTTON);
			//
			BOOL bTerrain	=	false;
			m_imageScale->Enable(!bTerrain);
			m_imageContScale->Enable(!bTerrain);
			m_imageLeft->Enable(!bTerrain);
			m_imageTop->Enable(!bTerrain);
			m_imageWidth->Enable(!bTerrain);
			m_imageHeight->Enable(!bTerrain);
			m_imageRegetRect->Enable(!bTerrain && (!rects || !rects->GetPtr()));
			m_imageUCount->Enable(!bTerrain);
			m_imageVCount->Enable(!bTerrain);
			m_imageUVPlaySpeed->Enable(!bTerrain);
			OnTreeSelectControl(control);
			//
			m_imageProp.EnableRender(true);
			//this->m_controlSelects.clear();
			//m_controlSelects.push_back(control);
		}
		break;
	case UI_PROP_ANIMATION:
		{
			SetCurrentProperties(&m_animationProp, L"�ؼ�����", &m_animationTrack);
			//
			Phantom::UIControl* control	=	m_dialogPtr->GetControlPtrFromID(type->p1);
			m_animationProp.EnableRender(false);
			if(m_dialogPtr->m_pakdir)m_animationProp.DisableEditor();

			Phantom::UIAnimationTrack* ani	=	control->GetTrackPtr(type->p2);
			if(!control || !ani)
			{
				m_animationProp.EnableWindow(FALSE);
				m_animationProp.EnableRender(true);
				break;
			}
			control->GetGroupPtr()->SetPlayTime(0);
			SetPropText(m_animationName, Wutf8(ani->GetName()));
			SetPropFloat(m_animationFrameCount, (float)ani->GetFrameCount() / TRACK_SECOND_LENGTH);
			//SetPropBool(m_animationIsDefault, ani == control->GetTrackDefault());
			SetPropFloat(m_animationSpeed, ani->GetPlaySpeed());
			SetPropFloat(m_animationSleepTime, ani->GetSleepTime());
			SetPropFloat(m_animationWaveSleepTime, ani->GetWaveSleepTime());
			SetPropInt(m_animationLoopCount, ani->GetLoopCount());
			SetPropBool(m_animationWaitEnable, ani->IsWaitTimeEnable());
			SetPropBool(m_animationHideAtSleep, ani->GetSleepAtHide());
			SetPropBool(m_animationHideOnOver, ani->m_bHideOnOver);
			SetPropFloat(m_animationWaveVolume, ani->GetWaveVolume());
			SetPropFloat(m_animationWaveSpeed, ani->GetWaveSpeed());
			SetPropFile(m_animationWaveFile, ani->GetWaveFile());
			//
			SetPropOption(m_animationNextType, g_typeUnitActionType, ani->GetNextActionType());
			SetPropOption(m_animationType, g_typeUnitActionType, ani->GetActionType());
			//
			m_animationElement->RemoveAllOptions();
			NameW select;
			for(int i=0;i<control->GetElementCount();i++)
			{
				if(i == ani->GetElementIndex())
					select	=	GetElementName(control->GetType(), i);
				m_animationElement->AddOption(GetElementName(control->GetType(), i));
			}
			SetPropText(m_animationElement, select);
			//
			if(ani->GetElementIndex() >= 0 && ani->GetElementIndex() < control->GetElementCount())
			{
				m_animationElementAni->Enable(true);
				//
				Phantom::UIElement* ele	=	control->GetElementPtr(ani->GetElementIndex());
				m_animationElementAni->RemoveAllOptions();
				NameW select;
				for(int i=0;i<ele->GetUVAnimationCount();i++)
				{
					if(ele->GetUVAnimationPtr(i)->GetActionType() == ani->GetUVAnimation())
						select	=	Wutf8(ele->GetUVAnimationPtr(i)->GetName()).buf;
					m_animationElementAni->AddOption(Wutf8(ele->GetUVAnimationPtr(i)->GetName()).buf);
				}
				SetPropText(m_animationElementAni, select);
			}
			else
				m_animationElementAni->Enable(false);
			//
			m_trackType	=	GCViewUIEditor::UI_PROP_ANIMATION_FLOAT;
			m_trackP1	=	type->p1;
			m_trackP2	=	type->p2;
			m_trackP3	=	type->p3;
			m_trackP4	=	type->p4;
			m_animationTrack.BeginSet();
			m_animationTrack.SetPlaySpeed(ani->GetPlaySpeed());
			//m_animationTrack.SetAnimationPtr(UI_VALUE_TEXT_COLOR, ani->GetAnimationPtr(Phantom::ControlTrackType_TextColorR), ani->GetAnimationPtr(Phantom::ControlTrackType_TextColorG), ani->GetAnimationPtr(Phantom::ControlTrackType_TextColorB));
			//m_animationTrack.SetAnimationPtr(UI_VALUE_TEXT_ALPHA, ani->GetAnimationPtr(Phantom::ControlTrackType_TextColorA));
			m_animationTrack.SetAnimationPtr(UI_VALUE_TEXTURE_COLOR, ani->GetAnimationPtr(Phantom::ControlTrackType_TextureColorR), ani->GetAnimationPtr(Phantom::ControlTrackType_TextureColorG), ani->GetAnimationPtr(Phantom::ControlTrackType_TextureColorB), Language(L"��ɫ"));
			m_animationTrack.SetAnimationPtr(UI_VALUE_TEXTURE_ALPHA, ani->GetAnimationPtr(Phantom::ControlTrackType_TextureColorA), 0, 0, Language(L"͸��"));
			m_animationTrack.SetAnimationPtr(UI_VALUE_Position, ani->GetAnimationPtr(Phantom::ControlTrackType_RectX), ani->GetAnimationPtr(Phantom::ControlTrackType_RectY), 0, Language(L"λ��"));
			m_animationTrack.SetAnimationPtr(UI_VALUE_WidthHeight, ani->GetAnimationPtr(Phantom::ControlTrackType_RectW), ani->GetAnimationPtr(Phantom::ControlTrackType_RectH), 0, Language(L"��С"));
			m_animationTrack.SetAnimationPtr(UI_VALUE_Center, ani->GetAnimationPtr(Phantom::ControlTrackType_CenterX), ani->GetAnimationPtr(Phantom::ControlTrackType_CenterY), 0, Language(L"���ĵ�"));
			m_animationTrack.SetAnimationPtr(UI_VALUE_Rotation, ani->GetAnimationPtr(Phantom::ControlTrackType_Rotation), 0, 0, Language(L"ת����"));
			//
			//m_animationTrack.SetAnimationPtr(Phantom::ControlTrackType_UStart, ani->GetAnimationPtr(Phantom::ControlTrackType_UStart), ani->GetAnimationPtr(Phantom::ControlTrackType_UEnd));
			//m_animationTrack.SetAnimationPtr(Phantom::ControlTrackType_UEnd, ani->GetAnimationPtr(Phantom::ControlTrackType_UEnd));
			//m_animationTrack.SetAnimationPtr(Phantom::ControlTrackType_VStart, ani->GetAnimationPtr(Phantom::ControlTrackType_VStart), ani->GetAnimationPtr(Phantom::ControlTrackType_VEnd));
			//m_animationTrack.SetAnimationPtr(Phantom::ControlTrackType_SoundVolume, ani->GetAnimationPtr(Phantom::ControlTrackType_SoundVolume));
			//m_animationTrack.SetAnimationPtr(Phantom::ControlTrackType_SoundSpeed, ani->GetAnimationPtr(Phantom::ControlTrackType_SoundSpeed));
			m_animationTrack.EndSet();
			//
			Phantom::PlayAnimationType temp	=	Phantom::PlayAnimationType_Play;//ani->GetPlayType();
			OnTreeSelectControl(control);
			m_animationTrack.SetTrackKeyCount(ani->GetFrameCount());
			control->ActiveTrackByID(ani->GetID());//A(ani->GetName()));
//			ani->SetPlayType(temp);//PlayAnimationType_None);
			m_animationProp.EnableRender(true);
			m_animationProp.EnableWindow(TRUE);
			if(this->m_editorMode == MouseMode_None)
				this->SetEditorFlags(UIEditorFlags_TrackAnimation);
			this->m_controlSelects.clear();
			m_controlSelects.push_back(control);
		}
		break;
	case UI_PROP_UV_ANIMATION:
		{
			m_animationTrack.ClearAnimationPtr();
			if(this->m_nEditorFlags == UIEditorFlags_TrackAnimation)this->SetEditorFlags(UIControlType_NONE);
			SetCurrentProperties(&m_uvmapProp, L"��ͼ����", 0);
			if(m_dialogPtr->m_pakdir)m_uvmapProp.DisableEditor();
			//
			Phantom::UIControl* control	=	m_dialogPtr->GetControlPtrFromID(type->p1);
			m_uvmapProp.EnableRender(false);
			Phantom::UIElement* element		=	control ? control->GetElementPtr(type->p2) : 0;
			Phantom::UVAnimation* uv	=	element ? GetUVAniByID(element, type->p3) : 0;
			if(!control || !element || !uv)
			{
				m_uvmapProp.EnableWindow(FALSE);
				m_uvmapProp.EnableRender(true);
				break;
			}
			control->GetGroupPtr()->SetPlayTime(0);
			SetPropText(m_uvmapName, Wutf8(uv->GetName()));
			SetPropInt(m_uvmapKeyLoopCount, uv->GetLoopCount());
			SetPropFloat(m_uvmapKeyPlaySpeed, uv->GetPlaySpeed());
			SetPropBool(m_uvmapDefault, uv == element->GetUVAnimationDefault());
			m_uvmapAngle->Enable(control->GetEnableUnitAngle());//control->GetUnit2D() != NULL);
			SetPropOption(m_uvmapAngle, g_type2DUnitAngle, uv->GetAngle());
			int begin = 0;
			int frame = 0;
			uv->GetUVMapIndex(begin, frame);
			SetPropInt(m_uvmapBeginIndex, begin);
			SetPropInt(m_uvmapFrameCount, frame);
			SetPropInt(m_uvmapLayerAdd, uv->GetLayerAdd());
			m_uvmapLayerAdd->Enable(control->GetGroupPtr()->GetGroupIsUnit());
			SetPropBool(m_uvmapCustomEnable, uv->IsCustomEnable());
			SetPropBool(this->m_uvmapInvW, uv->IsInvW());
			SetPropBool(this->m_uvmapInvH, uv->IsInvH());
			m_uvmapCustomGroup->Enable(uv->IsCustomEnable());
			m_uvmapAutoImages->Enable(uv->IsCustomEnable());
			SetPropText(m_uvmapAutoImages, L"");
			//
			m_uvmapSet->Enable(uv->IsCustomEnable());	//����ͼƬ
			m_uvmapClear->Enable(uv->IsCustomEnable());	//���ÿ�ͼƬ
			//
			Phantom::TextureNode2D* tex	=	Phantom::GetDlgManager()->GetTextureNode(uv->GetTextureID());
			SetPropFile(m_uvmapSet, tex ? Wutf8(tex->fileName.t).buf : L"");
			SetPropInt(m_uvmapLeft,uv->GetSourceRect().left);
			SetPropInt(m_uvmapTop,uv->GetSourceRect().top);
			m_uvmapOffsetX->Enable(false);
			m_uvmapOffsetY->Enable(false);
			//
			SetPropOption(m_uvmapActionType, g_typeUnitActionType, uv->GetActionType());
			SetPropOption(m_uvmapNextActionType, g_typeUnitActionType, uv->GetNextAction());

			SetPropBool(m_uvmapMoveOffset, uv->m_bMoveOffset);
			SetPropInt(m_uvmapMoveOffsetX, uv->m_moveOffset.x);
			SetPropInt(m_uvmapMoveOffsetY, uv->m_moveOffset.y);
			SetPropFloat(m_uvmapMoveOffsetSpeed, uv->m_moveSpeed);
			SetPropFloat(m_uvmapNextActionRand, uv->m_nextRand);
			m_uvmapMoveOffsetX->Enable(uv->m_bMoveOffset);
			m_uvmapMoveOffsetY->Enable(uv->m_bMoveOffset);
			m_uvmapMoveOffsetSpeed->Enable(uv->m_bMoveOffset);
			//
			element->ActiveUVAnimation(uv);
			//
			OnTreeSelectControl(control);
			m_uvmapProp.EnableRender(true);
			m_uvmapProp.EnableWindow(TRUE);
			this->m_controlSelects.clear();
			m_controlSelects.push_back(control);
			//
			for(int i=0;i<this->m_treeView.GetSelectCount();i++)
			{
				HTREEITEM hItem		=	m_treeView.GetSelect(i);
				TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
				if(type && type->type == UI_PROP_UV_ANIMATION)
				{
					Phantom::UIControl* control	=	this->m_dialogPtr->GetControlPtrFromID(type->p1);
					if(!control)
						continue;
					Phantom::UIElement* e		=	control->GetElementPtr(type->p2);
					if(e)
					{
						Phantom::UVAnimation* eUV	=	GetUVAniByID(e, type->p3);
						if(eUV)
							e->ActiveUVAnimation(eUV);
							//eUV->SetPlayIndex(0);
					}
				}
			}
			//
		}
		break;
	case UI_PROP_UV_ANIMATION_RECT:
		{
			m_animationTrack.ClearAnimationPtr();
			SetCurrentProperties(&m_uvmapRectProp, L"��ͼ����", 0);
			Phantom::UIControl* control	=	m_dialogPtr->GetControlPtrFromID(type->p1);
			m_uvmapRectProp.EnableRender(false);
			if(m_dialogPtr->m_pakdir)m_uvmapRectProp.DisableEditor();
			Phantom::UIElement* element		=	control ? control->GetElementPtr(type->p2) : 0;
			Phantom::UVAnimation* uv	=	element ? GetUVAniByID(element, type->p3) : 0;
			if(!control || !element || !uv)
			{
				m_uvmapRectProp.EnableWindow(FALSE);
				m_uvmapRectProp.EnableRender(true);
				break;
			}
			const Phantom::TextureRect* rect	=	uv->GetTextureRect(type->p4);
			//
			//
			int nTexture	=	element->GetTextureID();
			if(uv->IsCustomEnable() && uv->GetTextureID() > 0)
				nTexture	=	uv->GetTextureID();
			if(uv->GetTextureRectFile(type->p4) > 0)
			{
				nTexture	=	uv->GetTextureRectFile(type->p4);
				Phantom::TextureNode2D* tex	=	Phantom::GetDlgManager()->GetTextureNode(nTexture);
				SetPropFile(m_uvmapTexture, tex ? Wutf8(tex->fileName.t).buf : L"");
			}
			else
				SetPropFile(m_uvmapTexture, L"");
			//
			uv->SetPlayTime((float)type->p4);
			//
			Phantom::CDynamicArray<Phantom::TextureRect>* rects	=	Phantom::GetDlgManager()->GetTextureRectPtr(nTexture);
			//
			SetPropInt(m_uvmapLeft, rect->rc.left);
			SetPropInt(m_uvmapTop, rect->rc.top);
			SetPropInt(m_uvmapWidth, rect->rc.GetWidth());
			SetPropInt(m_uvmapHeight, rect->rc.GetHeight());
			m_uvmapOffsetX->Enable(true);
			m_uvmapOffsetY->Enable(true);
			SetPropInt(m_uvmapOffsetX,uv->GetTextureOffset(type->p4)->x);
			SetPropInt(m_uvmapOffsetY,uv->GetTextureOffset(type->p4)->y);
			//
			m_uvmapImageLists->RemoveAllOptions();
			if(rects)
			{
				const wchar_t* szName	=	Language(L"");
				m_uvmapImageLists->AddOption(szName);
				NameW select = szName;
				for(int i=0;i<rects->size();i++)
				{
					Wutf8 w(rects->GetPtr()[i].name);
					m_uvmapImageLists->AddOption(w.buf);
					if(stricmp(rects->GetPtr()[i].name, rect->name.t) == 0)
						select	=	w.buf;
				}
				SetPropText(m_uvmapImageLists, select);
				bool bEnable	=	(rect->name.t[0] == 0);
				m_uvmapLeft->Enable(bEnable);
				m_uvmapTop->Enable(bEnable);
				m_uvmapWidth->Enable(bEnable);
				m_uvmapHeight->Enable(bEnable);
				m_uvmapOffsetX->Enable(true);
				m_uvmapOffsetY->Enable(true);
			}
			else
			{
				m_uvmapOffsetX->Enable(false);
				m_uvmapOffsetY->Enable(false);
			}
			//
			if(element->GetActiveUVAnimation() != uv)
				element->ActiveUVAnimation(uv);
			//
			OnTreeSelectControl(control);
			m_uvmapRectProp.EnableRender(true);
			m_uvmapRectProp.EnableWindow(TRUE);
			this->m_controlSelects.clear();
			m_controlSelects.push_back(control);
		}
		break;
	case UI_PROP_GROUP:
		{
			m_animationTrack.ClearAnimationPtr();
			if(this->m_nEditorFlags == UIEditorFlags_TrackAnimation)this->SetEditorFlags(UIControlType_NONE);
			SetCurrentProperties(&m_groupProp, L"������", 0);
			if(m_dialogPtr->m_pakdir)m_groupProp.DisableEditor();
			//
			Phantom::UIGroup* group	=	m_dialogPtr->FindGroupPtr(Phantom::PtrID(0, type->p1));
			m_groupProp.EnableRender(false);
			if(!group)
			{
				m_groupProp.EnableWindow(FALSE);
				m_groupProp.EnableRender(true);
				break;
			}
			for(int i=0;i<m_dialogPtr->GetControlCount();i++)
			{
				if(m_dialogPtr->GetControlPtr(i)->GetGroupID() == group->GetID())
					m_dialogPtr->GetControlPtr(i)->ActiveTrackByName(NULL);
			}
			SetPropText(m_groupName, Wutf8(group->GetName()));
			SetPropBool(m_groupVisible, group->GetVisible());
			SetPropFloat(m_groupSleepTime, group->GetSleepTime());
			SetPropBool(m_groupIsUnit, group->GetGroupIsUnit());
			SetPropBool(m_groupEnable, group->GetEnabled());
			SetPropFloat(m_groupAngle, group->GetUnitAngle());
			SetPropFloat(m_groupSpeed, group->GetPlaySpeed());
			SetPropOption(m_groupAction, g_typeUnitActionType, group->GetPlayAction());
			m_groupSpeed->Enable(group->GetGroupIsUnit());
			//
			if(group->GetGroupIsUnit())
			{
				group->SetPosition(group->GetPosition());
				Phantom::ActionType	t	=	group->GetPlayAction();
				if(t == Phantom::ActionType_None)
					t	=	Phantom::ActionType_Idle;
				group->PlayAction(t);
			}
			OnTreeSelectGroup(group);
			m_groupProp.EnableRender(true);
			m_groupProp.EnableWindow(TRUE);
		}
		break;
	//case UI_PROP_EVENT:
	//	{
	//		if(this->m_nEditorFlags == UIEditorFlags_TrackAnimation)this->SetEditorFlags(UIControlType_NONE);
	//		SetCurrentProperties(0, L"�¼�����", &m_uiEventSet);
	//		//
	//		Phantom::UIControl* control	=	m_dialogPtr->GetControlPtrFromID(type->p1);
	//		IEvent* evt	=	0;
	//		if(control)
	//		{
	//			for(int i=0;i<control->GetEventCount();i++)
	//			{
	//				if(control->GetEventPtr(i)->GetID() == type->p2)
	//				{
	//					evt	=	control->GetEventPtr(i);
	//					break;
	//				}
	//			}
	//		}
	//		if(!control || !evt)
	//		{
	//			SetCurrentProperties(0, 0, 0);
	//			break;
	//		}
	//		wchar_t name[128];
	//		char szFile[128], szExt[128];
	//		_splitpath(m_dialogPtr->GetFileName(), 0, 0, szFile, szExt);
	//		strcat(szFile, szExt);
	//		//
	//		swprintf(name, L"%s[%s]", control->GetName(), W(szFile));
	//		this->m_uiEventSet.SetUIEvent(evt->GetID(), m_dialogPtr->GetID(), control->GetID(), name);
	//		this->m_controlSelects.clear();
	//		m_controlSelects.push_back(control);
	//	}
	//	break;
	default:
		if(this->m_nEditorFlags == UIEditorFlags_TrackAnimation)this->SetEditorFlags(UIControlType_NONE);
		SetCurrentProperties(NULL, NULL, NULL);
		break;
	}
}

VOID		GCViewUIEditor::OnChangeTreeSelect(CMTreeCtrl* treePtr, HTREEITEM hAddItem)	//����ѡ�����οؼ�
{
	if(treePtr == &m_treeView)
	{
		ChangeSelectControls();
		OnChangeTreeSelect();
		return;
	}
	SetCurrentProperties(NULL, NULL, NULL);
}

VOID	GCViewUIEditor::RefreshImageScale()
{
}

VOID	GCViewUIEditor::InitDialogProp()
{
	CMFCPropertyGridProperty* group1	= new CMFCPropertyGridProperty(Language(L"��������"));
	group1->AddSubItem(m_dlgAlwaysVisible		= AddPropBool(Language(L"ʼ����ʾ"), Language(L"�Ի���_ʼ����ʾ_˵��", L"ʼ����ʾ�˶Ի��������������κ�ʱ����ʾ��")));
	//group1->AddSubItem(m_dlgAnimationEnable		= AddPropBool(Language(L"��ؼ�����"), Language(L"�Ի���_����ѡ��_˵��", L"ʹ�Ի�����Ը��ţ��ɿ��ƶԻ���ؼ�һ�𶯻���")));
	group1->AddSubItem(m_dlgColor				= AddPropColor(Language(L"������ɫ"), Language(L"�Ի���_������ɫ_˵��", L"���öԻ���ı�����ɫ��")));
	group1->AddSubItem(m_dlgAlpha				= AddPropFloat(Language(L"����͸��ֵ"), Language(L"�Ի���_����͸��ֵ_˵��", L"���öԻ���ı���͸��ֵ��"), false, 0, 1, 0.1f));
	group1->AddSubItem(m_dlgIs2DGame			= AddPropBool(Language(L"��Ϊ2D�Ի���ʹ��"), Language(L"m_dlgIs2DGame", L"������Ϊ2D�Ի���ʹ�á�")));

	CMFCPropertyGridProperty* group2	= new CMFCPropertyGridProperty(Language(L"��������"));
	//group2->AddSubItem(m_dlgAlignLR		= AddPropOption(Language(L"���Ҷ���"), Language(L"�Ի���_���Ҷ���_˵��", L"���öԻ������Ҷ���ģʽ��"), g_typeDialogAlignLR));
	//group2->AddSubItem(m_dlgAlignTB		= AddPropOption(Language(L"���¶���"), Language(L"�Ի���_���¶���_˵��", L"���öԻ������¶���ģʽ��"), g_typeDialogAlignTB));
	//group2->AddSubItem(m_dlgOffsetX		= AddPropInt(Language(L"���Ҿ����"), Language(L"�Ի���_���Ҿ����_˵��", L"���öԻ������Ҿ����Ӷ���㿪ʼ�������Ǹ�ֵ��"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	//group2->AddSubItem(m_dlgOffsetY		= AddPropInt(Language(L"���¾����"), Language(L"�Ի���_���¾����_˵��", L"���öԻ������¾����Ӷ���㿪ʼ�������Ǹ�ֵ��"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	//group2->AddSubItem(m_dlgViewScale	= AddPropOption(Language(L"���Ŵ�С"), Language(L"m_dlgViewScale", L"�������Ź۲�X��"), g_typeViewScale));
	//group2->AddSubItem(m_dlgViewScaleX	= AddPropFloat(Language(L"���ſ��"), Language(L"m_dlgViewScaleX", L"�������Ź۲�X��"), false, 0.00001f, 10.0f));
	//group2->AddSubItem(m_dlgViewScaleY	= AddPropFloat(Language(L"���Ÿ߶�"), Language(L"m_dlgViewScaleY", L"�������Ź۲�Y��"), false, 0.00001f, 10.0f));
	group2->AddSubItem(m_dlgX		= AddPropInt(Language(L"λ��X"), Language(L"�Ի���_λ��X_˵��", L"���öԻ���λ��X��"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	group2->AddSubItem(m_dlgY		= AddPropInt(Language(L"λ��Y"), Language(L"�Ի���_λ��Y_˵��", L"���öԻ���λ��Y��"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	group2->AddSubItem(m_dlgRecalcRects			= AddPropButton(Language(L"���¼���ͼƬģʽ"), Language(L"m_dlgRecalcRects", L"���¼���ͼƬģʽ��")));
	
	//
	CMFCPropertyGridProperty* map			= new CMFCPropertyGridProperty(Language(L"��ͼ����"));
	map->AddSubItem(m_dlgMapEnable			= AddPropBool(Language(L"���ڵ�ͼ"), Language(L"m_dlgMapEnable", L"2D��Ϸ���Ƿ���ڵ�ͼ��")));
	map->AddSubItem(m_dlgMap25DMode			= AddPropBool(Language(L"2.5D��ͼ"), Language(L"m_dlgMap25DMode", L"2.5D��ͼģʽ��")));
	map->AddSubItem(m_dlgMapSizeX		= AddPropInt(Language(L"���Ӵ�С[����]"), Language(L"m_dlgMapSizeX", L"���öԻ���λ��[����]��"), 8, 128, 1));
	map->AddSubItem(m_dlgMapSizeY		= AddPropInt(Language(L"���Ӵ�С[����]"), Language(L"m_dlgMapSizeY", L"���öԻ���λ��[����]��"), 8, 128, 1));
	map->AddSubItem(m_dlgMapCountX		= AddPropInt(Language(L"��������[����]"), Language(L"m_dlgMapCountX", L"���öԻ���λ��[����]��"), 1, 100000, 10));
	map->AddSubItem(m_dlgMapCountY		= AddPropInt(Language(L"��������[����]"), Language(L"m_dlgMapCountY", L"���öԻ���λ��[����]��"), 0, 100000, 10));
	map->AddSubItem(m_dlgMapOffsetX		= AddPropInt(Language(L"���ӿ�ʼ��X"), Language(L"m_dlgMapOffsetX", L"���ӿ�ʼ��X[����]��"), -100000, 100000, 10));
	map->AddSubItem(m_dlgMapOffsetY		= AddPropInt(Language(L"���ӿ�ʼ��Y"), Language(L"m_dlgMapOffsetY", L"���ӿ�ʼ��Y[����]��"), -100000, 100000, 10));
	this->m_dlgProp.AddProperty(group1);
	this->m_dlgProp.AddProperty(group2);
	this->m_dlgProp.AddProperty(map);
}

VOID	GCViewUIEditor::InitControlProp()
{
	CMFCPropertyGridProperty* group1			= new CMFCPropertyGridProperty(Language(L"��������"));
	//
	group1->AddSubItem(m_controlName			= AddPropText(Language(L"�ؼ�����"), Language(L"�ؼ�����_˵��", L"�ؼ����ƣ��������ÿؼ����ơ�"), false, 50));
	group1->AddSubItem(m_controlVisible			= AddPropBool(Language(L"�Ƿ���ʾ"), Language(L"�ؼ���ʾ_˵��", L"�ؼ���ʾ���������ÿؼ��Ƿ�ɼ���")));
	group1->AddSubItem(m_controlEnable			= AddPropBool(Language(L"�Ƿ���Ч"), Language(L"�ؼ���Ч_˵��", L"�ؼ���Ч���������ÿؼ��Ƿ���Ч��")));
	group1->AddSubItem(m_controlSelect			= AddPropBool(Language(L"�Ƿ�ɱ༭"), Language(L"�Ƿ�ɱ༭_˵��", L"�Ƿ�ɱ༭������ؼ�ʱ�Ƿ���Ա��༭��")));
	group1->AddSubItem(m_controlCanActive		= AddPropBool(Language(L"�Ƿ�ɵ��"), Language(L"�ؼ��ɱ�����_˵��", L"�ؼ��Ƿ�ɱ�������Ա�����Ŀؼ����ܵ�ѡ��")));
	group1->AddSubItem(m_controlGroupID			= AddPropText(Language(L"���ڿؼ���"), Language(L"�ؼ����ID_˵��", L"���ÿؼ����ID�������ڸ���ID������ʾ��ʱ��ʹ�á�")));
	group1->AddSubItem(m_controlIsGroupCenter	= AddPropBool(Language(L"�����Ŀռ�"), Language(L"m_controlIsGroupCenter", L"���ó������Ŀؼ�֮���������λ��ʱ��Ὣ���пؼ���������ؼ������ƶ�")));
	group1->AddSubItem(m_controlMoveDialog		= AddPropBool(Language(L"�Ի������Ŀؼ�"), Language(L"�Ի������Ŀؼ�", L"ѡ��֮������ƶ��˿ؼ���Ҳ����ͬʱ�ƶ��Ի����λ�á�")));
	group1->AddSubItem(m_controlLayer			= AddPropOption(Language(L"��ʾ�㼶"), Language(L"�ؼ����ڲ㼶_˵��", L"���ղ㼶��ʾ˳��һ����"), g_typeControlLayer));
	group1->AddSubItem(m_controlIsGrid			= AddPropBool(Language(L"2D����㼶����"), Language(L"m_controlIsGrid", L"2.5D����㼶������ʾ�㼶�̶�Ϊ20��")));
	group1->AddSubItem(m_controlGridOffset			= AddPropInt(Language(L"2D�㼶����ƫ��Y"), Language(L"m_controlGridOffset", L"�㼶��ʾ��ʱ��ƫ��")));
	CMFCPropertyGridProperty* groupnum			= new CMFCPropertyGridProperty(Language(L"ͼƬ��������"));
	groupnum->AddSubItem(m_controlEnableImgText	= AddPropBool(Language(L"����ͼƬ����"), Language(L"�ؼ���Ч_˵��", L"ʹ��ͼƬ����,�ڱ��������ô�.rect��ͼƬ��д�������ı�֮����Զ������Ǹ��ı���ͼƬ��ʾ�ı���")));
	groupnum->AddSubItem(m_controlImgTextBegin	= AddPropText(Language(L"ͼƬ����ǰ׺"), Language(L"����ͼƬ����ǰ׺_˵��", L"����ͼƬ����ǰ׺")));
	groupnum->AddSubItem(m_controlImgSizeAdd	= AddPropInt(Language(L"���ּ���"), Language(L"���ּ���_˵��", L"���ּ���"),-100, 100));
	//
	CMFCPropertyGridProperty* groupani			= new CMFCPropertyGridProperty(Language(L"������������"));
	groupani->AddSubItem(m_controlSleepTime		= AddPropFloat(Language(L"����ǰ˯��"), Language(L"m_controlSleepTime", L"��������ǰ˯��ʱ�����ã�ÿ����������ʱ�����ϴ��"), false, 0.0f, 100.0f));
	//groupani->AddSubItem(m_controlAniCenter		= AddPropBool(Language(L"�������꿪ʼ"), Language(L"���������ĵ���ɢ_˵��", L"���������ĵ���ɢ����Ҫ�������ĵ����ꡣ")));

	CMFCPropertyGridProperty* group2			= new CMFCPropertyGridProperty(Language(L"��չ����"));
	group2->AddSubItem(m_controlDrawFocus		= AddPropBool(Language(L"�Ƿ���Ⱦ�����"), Language(L"�ؼ���Ⱦ�����_˵��", L"�ؼ��Ƿ���Ⱦ�����")));
	group2->AddSubItem(m_controlBackground		= AddPropBool(Language(L"�Ƿ񱳾��ؼ�"), Language(L"�ؼ����ƶ������ؼ�_˵��", L"ʼ����Ϊ������ʾ�ڴ����С�")));
	//group2->AddSubItem(m_controlContext			= AddPropInt(Language(L"�û��Զ������"), Language(L"�û��Զ������_˵��", L"�ؼ��û��Զ������,�����ڽű���ʹ��.Context������д,����Ԥ���ڱ༭����ָ����")));
	group2->AddSubItem(m_controlTabIndex		= AddPropInt(Language(L"TAB˳��"), Language(L"�ؼ�TAB˳��_˵��", L"�ؼ�TAB˳�򣬰�TAB��ʱ����Զ���ת����һ���ؼ���")));
	//group2->AddSubItem(m_controlCursorName		= AddPropOption(Language(L"�������"), Language(L"�ؼ��������_˵��", L"�ؼ�������ã��ƶ����ؼ���ʱ���Զ�ѡ�����ꡣ"), g_typeTemplate));
	group2->AddSubItem(m_controlParent			= AddPropOption(Language(L"���ؼ�"), Language(L"�ؼ����ID_˵��", L"���ÿؼ����ID�������ڸ���ID������ʾ��ʱ��ʹ�á�"), g_typeDefault));
	group2->AddSubItem(m_editSBWidth			= AddPropInt(Language(L"���������"), Language(L"�ؼ�ED���������_˵��", L"���ÿؼ���������ȡ�"), 0, 100, 1));
	//group1->AddSubItem(m_controlVisibleOnScript	= AddPropBool(Language(L"�ڳ�����ʹ��"), Language(L"�ڴ�����ʹ��_˵��", L"ѡ��֮�󣬿����ڴ������Զ����ɶ�Ӧ�Ķ���ʹ�ã�����lua�ű��������Խű��У��������������ɽ�����������ʱ���õ���")));
	{
		std::vector<std::wstring> types;
		AddOptions(m_controlGroupID, types);
		m_controlGroupID->AllowEdit(FALSE);
	}
	CMFCPropertyGridProperty* group2d			= new CMFCPropertyGridProperty(Language(L"2D��ɫ����"));
	group2d->AddSubItem(m_controlIs2DUnit		= AddPropBool(Language(L"�Ƿ�2D����"), Language(L"m_controlIs2DUnit", L"�Ƿ�2D����")));
	group2d->AddSubItem(m_controlUnitAngle8		= AddPropOption(Language(L"2D��Ϸ8������"), Language(L"m_controlUnitAngle8", L"2D��Ϸ8������"), g_typeUnitAngleType));
	//
	//m_controlCursorName->AllowEdit(TRUE);
	//for(int i=0;i<GetCursorManager()->GetCursorCount();i++)
	//	m_controlCursorName->AddOption(W(GetCursorManager()->GetCursorPtr(i)->GetCursorName()));
	//
	//�ı�����
	m_controlTextGroup			= new CMFCPropertyGridProperty(Language(L"�ı�����"));
	m_controlTextGroup->AddSubItem(m_controlText			= AddPropText(Language(L"�����ı�"), Language(L"�ؼ��ı�_˵��", L"���ÿؼ����ı���"), TRUE));
	m_controlTextGroup->AddSubItem(m_controlImageFont	= AddPropBool(Language(L"ʹ��ͼƬ����"), Language(L"m_controlImageFont", L"���ʹ��ͼƬ��������ʾϵͳ�����ı������Ҫ��ʾ��ͬ���ԵĽ�ɫ��ʲô�ľ���Ҫʹ��ϵͳ�ı���")));
	m_controlTextGroup->AddSubItem(m_controlFont	= AddPropFont(Language(L"����ϵͳ����"), Language(L"m_controlFont", L"����ϵͳ���壬���Ҫ��ʾ��ͬ���ԵĽ�ɫ��ʲô�ľ���Ҫʹ��ϵͳ�ı���")));
	m_controlTextGroup->AddSubItem(m_controlTextColor	= AddPropColor(Language(L"�ı���ɫ"), Language(L"�ؼ��ı���ɫ_˵��", L"���ÿؼ����ı���ɫ��")));
	m_controlTextGroup->AddSubItem(m_controlTextAlpha	= AddPropFloat(Language(L"�ı�͸��ֵ"), Language(L"�ؼ��ı�͸����_˵��", L"���ÿؼ����ı�͸���ȡ�"), false, 0, 1, 0.1f));
	m_controlTextGroup->AddSubItem(m_controlTextAlignLR	= AddPropOption(Language(L"���Ҷ���"), Language(L"�ؼ��ı����Ҷ���_˵��", L"�ؼ����ı����Ҷ��뷽ʽ��ֻ�д����ı��Ŀؼ���Ч��"), g_typeTextAlignLR));
	m_controlTextGroup->AddSubItem(m_controlTextAlignTB	= AddPropOption(Language(L"���¶���"), Language(L"�ؼ��ı����¶���_˵��", L"�ؼ����ı����¶��뷽ʽ��ֻ�д����ı��Ŀؼ���Ч��"), g_typeTextAlignTB));
	//m_controlTextGroup->AddSubItem(m_controlShadowWidth	= AddPropInt(Language(L"��Ӱ"), Language(L"�ؼ��ı���Ӱ_˵��", L"���ÿؼ����ı���Ӱ��ȡ�"), 0, 10, 1));
	//m_controlTextGroup->AddSubItem(m_controlShadowColor	= AddPropColor(Language(L"��Ӱ��ɫ"), Language(L"�ؼ���Ӱ��ɫ_˵��", L"�ؼ�����Ӱ��ɫ��")));
	//m_controlTextGroup->AddSubItem(m_controlShadowAlpha	= AddPropFloat(Language(L"��Ӱ͸��ֵ"), Language(L"�ؼ���Ӱ͸��_˵��", L"�ؼ�����Ӱ͸����"), false, 0, 1.0f, 0.1f));
	//��ͼ����
	CMFCPropertyGridProperty* groupTexture		= new CMFCPropertyGridProperty(Language(L"��ͼ����"));
	groupTexture->AddSubItem(m_controlTextureColor	= AddPropColor(Language(L"��ͼ��ɫ"), Language(L"�ؼ���ͼ��ɫ_˵��", L"���ÿؼ�����ͼ��ɫ��")));
	groupTexture->AddSubItem(m_controlTextureAlpha	= AddPropFloat(Language(L"��ͼ͸��ֵ"), Language(L"�ؼ���ͼ͸����_˵��", L"���ÿؼ�����ͼ͸���ȡ�"), false, 0, 1, 0.1f));
	//groupTexture->AddSubItem(m_controlDisableColor	= AddPropColor(Language(L"��Чɫ"), Language(L"�ؼ���ͼ��Чʱ��ɫ_˵��", L"���ÿؼ�����ͼ��Чʱ��ɫ��")));
	//�ؼ�λ��
	CMFCPropertyGridProperty* groupRect			= new CMFCPropertyGridProperty(Language(L"λ�ô�С"));
	groupRect->AddSubItem(m_controlScale		= AddPropFloat(Language(L"��������"), Language(L"m_controlScale", L"�ؼ����������ŵ�����"), false, 0.01f, 100.0f ));
	groupRect->AddSubItem(m_controlLeft			= AddPropInt(Language(L"��"), Language(L"�ؼ���_˵��", L"�ؼ������λ�ã�����ڶԻ�������λ�á�"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	groupRect->AddSubItem(m_controlTop			= AddPropInt(Language(L"��"), Language(L"�ؼ���_˵��", L"�ؼ����ϱ�λ�ã�����ڶԻ�����ϱ�λ�á�"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	groupRect->AddSubItem(m_controlWidth		= AddPropInt(Language(L"��"), Language(L"�ؼ���_˵��", L"�ؼ��Ĵ�С����ȡ�"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	groupRect->AddSubItem(m_controlHeight		= AddPropInt(Language(L"��"), Language(L"�ؼ���_˵��", L"�ؼ��Ĵ�С���߶ȡ�"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	groupRect->AddSubItem(m_controlAlignModeW	= AddPropOption(Language(L"��Ϸ�ڶ���:����"), Language(L"m_controlAlignModeW", L"�ؼ����ı����¶��뷽ʽ��ֻ�д����ı��Ŀؼ���Ч��"), g_typeAlignModeW));
	groupRect->AddSubItem(m_controlAlignModeH	= AddPropOption(Language(L"��Ϸ�ڶ���:����"), Language(L"m_controlAlignModeH", L"�ؼ����ı����¶��뷽ʽ��ֻ�д����ı��Ŀؼ���Ч��"), g_typeAlignModeH));
	groupRect->AddSubItem(m_controlPixel		= AddPropBool(Language(L"���ص����Ч"), Language(L"m_controlPixel", L"�ؼ��Ƿ����ص����Ч��ֻ�а������ؾ�ȷ�����������Ч���")));
	groupRect->AddSubItem(m_controlCenterX	= AddPropInt(Language(L"���ĵ�X"), Language(L"�ؼ����е�X_˵��", L"����X���ϵĿؼ����е㡣"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	groupRect->AddSubItem(m_controlCenterY	= AddPropInt(Language(L"���ĵ�Y"), Language(L"�ؼ����е�Y_˵��", L"����Y���ϵĿؼ����е㡣"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	//��ʾ��Ϣ
	//m_controlTipGroup			= new CMFCPropertyGridProperty(Language(L"��ʾ��Ϣ"));
	//m_controlTipGroup->AddSubItem(m_controlToolTipText	= AddPropText(Language(L"��ʾ��Ϣ"), Language(L"�ؼ���ʾ��Ϣ_˵��", L"��ʾ��Ϣ��������ƶ���������ؼ���Χ��ʱ���Զ���ʾ����ʾ��"), TRUE));
	//m_controlTipGroup->AddSubItem(m_controlToolTipAlign	= AddPropOption(Language(L"��ʾ��Ϣ����"), Language(L"�ؼ���ʾ��Ϣ����_˵��", L"��ʾ��Ϣ����ģʽ��������ʾ��Ϣ��ʾ������ĸ�����"), g_typeToolTipAlign));
	//�ؼ�ת��
	m_controlRotGroup			= new CMFCPropertyGridProperty(Language(L"�ؼ�ת��"));
	m_controlRotGroup->AddSubItem(m_controlRotation	= AddPropBool(Language(L"�Ƿ�ת��"), Language(L"�ؼ��Ƿ�ת��_˵��", L"�ؼ��Ƿ����ת����")));
	m_controlRotGroup->AddSubItem(m_controlAngle		= AddPropFloat(Language(L"�Ƕ�"), Language(L"�ؼ�ת���Ƕ�_˵��", L"���ÿؼ�ת���Ƕȡ�"), false, -360.0f, 360.0f, 15.0f));
	//�༭����������
	m_editGroup			= new CMFCPropertyGridProperty(Language(L"�༭������"));
	//m_editGroup->AddSubItem(m_editShowBorder	= AddPropBool(Language(L"���ڱ߿�"), Language(L"�ؼ����ڱ߿�_˵��", L"�ؼ��Ƿ���ڱ߿�")));
	//m_editGroup->AddSubItem(m_editBorderWidth	= AddPropInt(Language(L"�߿���"), Language(L"�ؼ��߿���_˵��", L"���ÿؼ��߿��ȡ�"), 0, 100, 1));
	m_editGroup->AddSubItem(m_editPassword		= AddPropBool(Language(L"����༭��"), Language(L"�ؼ�����༭��_˵��", L"���ÿؼ��༭���Ƿ�������༭��")));
	//m_editGroup->AddSubItem(m_editEnableIME		= AddPropBool(Language(L"֧�����뷨"), Language(L"�ؼ�֧�����뷨_˵��", L"���ÿؼ��Ƿ�֧�����뷨��")));
	m_editGroup->AddSubItem(m_editReadOnly		= AddPropBool(Language(L"ֻ������"), Language(L"�ؼ�ֻ������_˵��", L"���ÿؼ��Ƿ�ֻ����")));
	//m_editGroup->AddSubItem(m_editIndicator		= AddPropBool(Language(L"��ʾ����ģʽ"), Language(L"�ؼ���ʾ����ģʽ_˵��", L"�����Ƿ���ʾ��ǰ����ģʽ��")));
	//m_editGroup->AddSubItem(m_editCandList		= AddPropBool(Language(L"��ʾ�ڲ������"), Language(L"�ؼ���ʾ�ڲ������_˵��", L"�����Ƿ���ʾ�ڲ������")));
	//
	//m_editGroup->AddSubItem(m_editCaretColor			= AddPropColor(Language(L"�����ɫ"), Language(L"�ؼ������ɫ_˵��", L"���ñ༭�������ɫ��")));
	//m_editGroup->AddSubItem(m_editSelectTextColor		= AddPropColor(Language(L"ѡ���ı���ɫ"), Language(L"�ؼ�ѡ���ı���ɫ_˵��", L"���ñ༭��ѡ���ı���ɫ��")));
	//m_editGroup->AddSubItem(m_editSelectBackColor		= AddPropColor(Language(L"ѡ���ı�������ɫ"), Language(L"�ؼ���ѡ���ı�������ɫ_˵��", L"���ñ༭��ѡ���ı�������ɫ")));
	//���ȿ�
	m_progressGroup			= new CMFCPropertyGridProperty(Language(L"����������"));
	m_progressGroup->AddSubItem(m_progressMode	= AddPropOption(Language(L"����������"), Language(L"�ؼ�����������_˵��", L"�ؼ��Ƿ���ڽ�������"), g_typeProgress));
	m_progressGroup->AddSubItem(m_progressValue	= AddPropFloat(Language(L"��ǰֵ"), Language(L"�ؼ���������ǰֵ_˵��", L"���ÿؼ���������ǰֵ��"), false, 0, 1, 0.1f));
	m_progressGroup->AddSubItem(m_progressSize	= AddPropInt(Language(L"�ڲ�����С����"), Language(L"�ؼ���������ǰֵ_˵��", L"�ڲ�����С������"),-100, 100));
	//combobox
	m_comboGroup			= new CMFCPropertyGridProperty(Language(L"��Ͽ�����"));
	m_comboGroup->AddSubItem(m_comboDropHeight	= AddPropInt(Language(L"�б�߶�"), Language(L"�ؼ���Ͽ��б�߶�_˵��", L"���ÿؼ���Ͽ��б�߶ȡ�"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	m_comboGroup->AddSubItem(m_comboValues		= AddPropList(Language(L"ֵ"), Language(L"�ؼ���Ͽ�ֵ_˵��", L"���ÿؼ���Ͽ�ֵ��")));
	//format edit
	m_formatEditGroup			= new CMFCPropertyGridProperty(Language(L"��ʽ���༭������"));
	m_formatEditGroup->AddSubItem(m_formatEditEventColor	= AddPropColor(Language(L"�¼���ɫ"), Language(L"�ؼ���ʽ���༭���¼���ɫ_˵��", L"�ؼ���ʽ���༭���¼���ɫ��")));
	m_formatEditGroup->AddSubItem(m_formatEditSelectColor	= AddPropColor(Language(L"ѡ���ı���ɫ"), Language(L"�ؼ���ʽ���༭��ѡ���ı���ɫ_˵��", L"�ؼ���ʽ���༭��ѡ���ı���ɫ��")));
	m_formatEditGroup->AddSubItem(m_formatEditLineHeight	= AddPropInt(Language(L"�и߶�"), Language(L"�ؼ���ʽ���༭���и߶�_˵��", L"���ÿؼ���ʽ���༭���и߶ȡ�"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	//listbox
	m_listboxGroup			= new CMFCPropertyGridProperty(Language(L"�б������"));
	m_listboxGroup->AddSubItem(m_listboxLineHeight	= AddPropInt(Language(L"�и߶�"), Language(L"�ؼ��б���и߶�_˵��", L"���ÿؼ��б���и߶ȡ�"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	m_listboxGroup->AddSubItem(m_listboxTextLeft	= AddPropInt(Language(L"��߱���"), Language(L"�ؼ��б����߱���_˵��", L"���ÿؼ��б����߱�����"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	m_listboxGroup->AddSubItem(m_listboxValues		= AddPropList(Language(L"ֵ"), Language(L"�ؼ��б��ֵ_˵��", L"���ÿؼ��б��ֵ��")));
	//listctrl
	m_listctrlGroup			= new CMFCPropertyGridProperty(Language(L"���п�����"));
	m_listctrlGroup->AddSubItem(m_listctrlColumnHeight	= AddPropInt(Language(L"��ͷ�߶�"), Language(L"�ؼ����п��ͷ�߶�_˵��", L"���ÿؼ����п��ͷ�߶ȡ�"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	m_listctrlGroup->AddSubItem(m_listctrlLineHeight	= AddPropInt(Language(L"�и߶�"), Language(L"�ؼ����п��и߶�_˵��", L"���ÿؼ����п��и߶ȡ�"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	m_listctrlGroup->AddSubItem(m_listctrlTextLeft		= AddPropInt(Language(L"��߱���"), Language(L"�ؼ����п���߱���_˵��", L"���ÿؼ����п���߱�����"), GetMinWindowPos(), GetMaxWindowPos(), GetWindowPosPage()));
	m_listctrlGroup->AddSubItem(m_listctrlColumns		= AddPropList(Language(L"��ͷ"), Language(L"�ؼ����п��ͷ_˵��", L"���ÿؼ����п��ͷ��")));
	m_listctrlGroup->AddSubItem(m_listctrlSortEnable	= AddPropBool(Language(L"������Ч"), Language(L"�ؼ����п�������Ч_˵��", L"���ÿؼ����п�������Ч��")));
	m_listctrlGroup->AddSubItem(m_listctrlItems			= AddPropList(Language(L"ֵ"), Language(L"�ؼ����п�ֵ_˵��", L"���ÿؼ����п�ֵ��")));
	//terrain2d
	m_terrainGroup			= new CMFCPropertyGridProperty(Language(L"2D��������"));
	m_terrainGroup->AddSubItem(m_terrainElementW		= AddPropInt(Language(L"ͼƬ����(����)"), Language(L"�ؼ�����ͼƬ����(����)_˵��", L"���ÿؼ�����ͼƬ����(����)��"), 1, 100, 1));
	m_terrainGroup->AddSubItem(m_terrainElementH		= AddPropInt(Language(L"ͼƬ����(����)"), Language(L"�ؼ�����ͼƬ����(����)_˵��", L"���ÿؼ�����ͼƬ����(����)��"), 1, 100, 1));
	m_terrainGroup->AddSubItem(m_terrainE_RenderLines	= AddPropBool(Language(L"��Ⱦ����"), Language(L"�ؼ�������Ⱦ����_˵��", L"���õ�����Ⱦ������")));
	m_terrainGroup->AddSubItem(m_terrainE_RenderBlends	= AddPropBool(Language(L"��Ⱦ����"), Language(L"�ؼ�������Ⱦ����_˵��", L"���õ�����Ⱦ���ӡ�")));
	m_terrainGroup->AddSubItem(m_terrainE_GridText		= AddPropBool(Language(L"��Ⱦ�ı�"), Language(L"�ؼ�������Ⱦ�ı�_˵��", L"���õ�����Ⱦ�ı���")));
	m_terrainGroup->AddSubItem(m_terrainE_MapTexture	= AddPropBool(Language(L"��ȾͼƬ"), Language(L"�ؼ�������ȾͼƬ_˵��", L"���õ�����ȾͼƬ��")));
	m_terrainGroup->AddSubItem(m_terrainE_AutoMoveMap	= AddPropBool(Language(L"�Զ��ƶ�"), Language(L"�ؼ������Զ��ƶ�_˵��", L"���õ����Զ��ƶ���")));
	m_terrainGroup->AddSubItem(m_terrainE_RenderObject	= AddPropBool(Language(L"��Ⱦ����"), Language(L"�ؼ�������Ⱦ����_˵��", L"���õ�����Ⱦ����")));
	m_terrainGroup->AddSubItem(m_terrainE_RenderFloor	= AddPropBool(Language(L"��Ⱦ����"), Language(L"�ؼ�������Ⱦ����_˵��", L"���õ�����Ⱦ���档")));
	m_terrainGroup->AddSubItem(m_terrainE_RenderEvent	= AddPropBool(Language(L"��Ⱦ�¼�"), Language(L"�ؼ�������Ⱦ�¼�_˵��", L"���õ�����Ⱦ�¼���")));
	m_terrainGroup->AddSubItem(m_terrainE_RenderCenters	= AddPropBool(Language(L"��Ⱦ������"), Language(L"�ؼ�������Ⱦ������_˵��", L"���õ�����Ⱦ��������")));
	//
	//m_terrainGroup->AddSubItem(m_terrainMapScale		= AddPropFloat(Language(L"��ͼ����"), Language(L"�ؼ����ε�ͼ����_˵��", L"���õ��ε�ͼ���š�"), false, 0.01f, 100.0f));
	m_terrainGroup->AddSubItem(m_terrainAutoMoveSpeed	= AddPropFloat(Language(L"�Զ��ƶ��ٶ�(����/��)"), Language(L"�ؼ������Զ��ƶ��ٶ�_˵��", L"���õ����Զ��ƶ��ٶȡ�"), false, 0.01f, 10000.0f));
	m_terrainGroup->AddSubItem(m_terrainAutoMoveSize	= AddPropInt(Language(L"�Զ��ƶ�����(����)"), Language(L"�ؼ������Զ��ƶ�����_˵��", L"���õ����Զ��ƶ����롣"), 1, 1000));
	m_terrainGroup->AddSubItem(m_terrainUnitSizeW		= AddPropInt(Language(L"��Ԫ���С(����)"), Language(L"�ؼ����ε�Ԫ���С(����)_˵��", L"���ÿؼ����ε�Ԫ���С(����)��"), 1, 10000, 1));
	m_terrainGroup->AddSubItem(m_terrainUnitSizeH		= AddPropInt(Language(L"��Ԫ���С(����)"), Language(L"�ؼ����ε�Ԫ���С(����)_˵��", L"���ÿؼ����ε�Ԫ���С(����)��"), 1, 10000, 1));
	/*/unit2d
	m_unit2DGroup			= new CMFCPropertyGridProperty(Language(L"2D��λ����"));
	m_unit2DGroup->AddSubItem(m_unit2DTextureCount		= AddPropInt(Language(L"ͼƬԪ������"), Language(L"�ؼ�2D��λͼƬԪ������_˵��", L"���ÿؼ�2D��λͼƬԪ��������"), 0, 100));
	m_unit2DGroup->AddSubItem(m_unit2DCenterPosX		= AddPropInt(Language(L"���ĵ�[����]"), Language(L"�ؼ�2D��λ���ĵ�[����]_˵��", L"���ÿؼ�2D��λ���ĵ�[����]��"), -10000, 10000));
	m_unit2DGroup->AddSubItem(m_unit2DCenterPosY		= AddPropInt(Language(L"���ĵ�[����]"), Language(L"�ؼ�2D��λ���ĵ�[����]_˵��", L"���ÿؼ�2D��λ���ĵ�[����]��"), -10000, 10000));
	m_unit2DGroup->AddSubItem(m_unit2DRenderGrid		= AddPropBool(Language(L"��Ⱦ����"), Language(L"�ؼ�2D��λ��Ⱦ����_˵��", L"���ÿؼ�2D��λ��Ⱦ���ӡ�")));
	*/
	//checkbox
	m_checkboxGroup			= new CMFCPropertyGridProperty(Language(L"��ѡ������"));
	m_checkboxGroup->AddSubItem(m_checkboxChecked	= AddPropBool(Language(L"ѡ��״̬"), Language(L"�ؼ�ѡ��״̬_˵��", L"���õ�ѡ��ؼ�ѡ��״̬��")));
	//effect
	m_effectGroup			= new CMFCPropertyGridProperty(Language(L"2D��Ч����"));
	m_effectGroup->AddSubItem(m_effectFrameCount	= AddPropFloat(Language(L"Ч������ʱ��"), Language(L"m_effectFrameCount", L"Ч������ʱ�䡣"), false, 0.01f, 100.0f));
	m_effectGroup->AddSubItem(m_effectLoopCount		= AddPropInt(Language(L"Ч��ѭ������"), Language(L"m_effectLoopCount", L"Ч��ѭ��������")));
	m_effectGroup->AddSubItem(m_effectPlaySpeed		= AddPropFloat(Language(L"Ч�������ٶ�"), Language(L"m_effectPlaySpeed", L"Ч�������ٶȡ�"), false, 0.0f, 30.0f));
	//static
	m_staticGroup			= new CMFCPropertyGridProperty(Language(L"��̬������"));
	m_staticGroup->AddSubItem(m_staticBorderWidth	= AddPropInt(Language(L"�ı��߿��С"), Language(L"�ؼ���̬���ı��߿��С_˵��", L"���ÿؼ���̬���ı��߿��С��")));
	//m_staticGroup->AddSubItem(m_staticMouseEnable		= AddPropBool(Language(L"��꾭��,��Ч��"), Language(L"m_staticMouseEnable", L"��꾭��-��Ч����")));
	//m_staticGroup->AddSubItem(m_staticMouseSrcBlend		= AddPropOption(Language(L"��꾭��-Դ���"), Language(L"m_staticMouseSrcBlend", L"��꾭��-Դ��ϡ�"), g_typeBlend));
	//m_staticGroup->AddSubItem(m_staticMouseDestBlend	= AddPropOption(Language(L"��꾭��-Ŀ����"), Language(L"m_staticMouseDestBlend", L"��꾭��-Ŀ���ϡ�"), g_typeBlend));
	m_staticGroup->AddSubItem(m_staticTextureColor		= AddPropColor(Language(L"��꾭��-��ɫ"), Language(L"m_staticTextureColor", L"��꾭��-��ɫ��")));
	m_staticGroup->AddSubItem(m_staticTextureAlpha		= AddPropFloat(Language(L"��꾭��-͸��"), Language(L"m_staticTextureAlpha", L"��꾭��-͸����"), false, 0, 1));
	//
	m_buttonGroup	= new CMFCPropertyGridProperty(Language(L"��ť����"));
	m_buttonGroup->AddSubItem(m_buttonClickSound		= AddPropFile(Language(L"����ʱ����"), Language(L"�ؼ���ť_���ʱ����_˵��", L"���õ�ǰͼƬ���ʱ���������"), GetSoundFilter()));
	//m_buttonGroup->AddSubItem(m_buttonMouseMoveSound	= AddPropFile(Language(L"�ƶ�ʱ����"), Language(L"�ؼ���ť_�ƶ�ʱ����_˵��", L"���õ�ǰͼƬ�ƶ�ʱ������"), GetSoundFilter()));
	m_buttonGroup->AddSubItem(m_buttonClickSoundClear		= AddPropButton(Language(L"ȥ�����ʱ����"), Language(L"m_buttonClickSoundClear", L"ȥ����ǰͼƬ���ʱ���������")));
	//m_buttonGroup->AddSubItem(m_buttonMouseMoveSoundClear	= AddPropButton(Language(L"ȥ���ƶ�ʱ����"), Language(L"m_buttonMouseMoveSoundClear", L"ȥ����ǰͼƬ�ƶ�ʱ������")));
	m_buttonGroup->AddSubItem(m_buttonType				= AddPropOption(Language(L"��ť����"), Language(L"�ؼ���ť����_˵��", L"��ť�ؼ����ͣ��Ƿ�Ĭ�ϰ�ť��ȡ����ť����ͨ��ť��Ĭ�ϰ�ť����Enter���Զ������ã�ȡ����ť����Esc���Զ������ã���"), g_typeControlButtons));
	//
	m_controlProp.AddProperty(group1);
	m_controlProp.AddProperty(groupRect);
	m_controlProp.AddProperty(groupTexture);
	m_controlProp.AddProperty(m_controlTextGroup);
	m_controlProp.AddProperty(groupnum);
	m_controlProp.AddProperty(groupani);
	//m_controlProp.AddProperty(m_controlTipGroup);
	m_controlProp.AddProperty(m_controlRotGroup);
	m_controlProp.AddProperty(m_editGroup);
	m_controlProp.AddProperty(m_progressGroup);
	m_controlProp.AddProperty(m_comboGroup);
	m_controlProp.AddProperty(m_formatEditGroup);
	m_controlProp.AddProperty(m_listboxGroup);
	m_controlProp.AddProperty(m_listctrlGroup);
	m_controlProp.AddProperty(m_checkboxGroup);
	m_controlProp.AddProperty(m_buttonGroup);
	m_controlProp.AddProperty(m_staticGroup);
	m_controlProp.AddProperty(m_terrainGroup);
	m_controlProp.AddProperty(group2d);
	m_controlProp.AddProperty(m_effectGroup);
	m_controlProp.AddProperty(group2);
	//
}

VOID	GCViewUIEditor::InitImageProp()
{
	//ͼƬ
	//CMFCPropertyGridProperty* groupName		= new CMFCPropertyGridProperty(Language(L"ͼƬ����"));
	//groupName->AddSubItem(m_imageName			= AddPropText(Language(L"����"), Language(L"�ؼ�ͼƬ_��������_˵��", L"���ÿؼ�ͼƬ���ơ�"), false, 49));
	//
	CMFCPropertyGridProperty* group1		= new CMFCPropertyGridProperty(Language(L"ͼƬ����"));
	group1->AddSubItem(m_imageSet			= AddPropFile(Language(L"����ͼƬ"), Language(L"�ؼ�ͼƬ_����ͼƬ_˵��", L"���ÿؼ�ͼƬ,��סCtrl�����Զ�����ͼƬ����"), GetImageFilter(), true));
	group1->AddSubItem(m_imageClear			= AddPropButton(Language(L"���ͼƬ"), Language(L"�ؼ�ͼƬ_���ͼƬ_˵��", L"��տؼ��ĵ�ǰͼƬ��")));
	group1->AddSubItem(m_imageDefault		= AddPropBool(Language(L"ʹ����ɫ"), Language(L"�ؼ�ͼƬ_ʹ����ɫ_˵��", L"�ؼ��ĵ�ǰͼƬʹ����ɫ��")));
	group1->AddSubItem(m_imageOpen			= AddPropButton(Language(L"��ͼƬ"), Language(L"�ؼ�ͼƬ_��ͼƬ_˵��", L"�򿪿ؼ��ĵ�ǰͼƬ��")));
	//
	//CMFCPropertyGridProperty* groupTexure	= new CMFCPropertyGridProperty(Language(L"ͼƬ�������"));
	group1->AddSubItem(m_imageTextureColor	= AddPropColor(Language(L"ͼƬ��ɫ"), Language(L"�ؼ�ͼƬ_ͼƬ��ɫ_˵��", L"����ͼƬ��ɫ��")));
	group1->AddSubItem(m_imageTextureAlpha	= AddPropFloat(Language(L"ͼƬ͸��ֵ"), Language(L"�ؼ�ͼƬ_ͼƬ͸��ֵ_˵��", L"����ͼƬ͸��ֵ��")));
	//
	//
	CMFCPropertyGridProperty* groupRect			= new CMFCPropertyGridProperty(Language(L"ͼƬ����"));
	groupRect->AddSubItem(m_imageLeft		= AddPropInt(Language(L"���ص�:��"), Language(L"�ؼ�ͼƬ_���_˵��", L"����ͼƬ��Ч������ߡ�")));
	groupRect->AddSubItem(m_imageTop		= AddPropInt(Language(L"���ص�:��"), Language(L"�ؼ�ͼƬ_�ϱ�_˵��", L"����ͼƬ��Ч�����ϱߡ�")));
	groupRect->AddSubItem(m_imageWidth		= AddPropInt(Language(L"���ص�:������"), Language(L"�ؼ�ͼƬ_���_˵��", L"����ͼƬ��Ч�����ȡ�"), 1, 4096));
	groupRect->AddSubItem(m_imageHeight		= AddPropInt(Language(L"���ص�:����߶�"), Language(L"�ؼ�ͼƬ_�߶�_˵��", L"����ͼƬ��Ч����߶ȡ�"), 1, 4096));
	groupRect->AddSubItem(m_imageLists		= AddPropOption(Language(L"ģ��:ѡ��һ��"), Language(L"m_imageLists", L"ͼƬ����ʹ��PngMaker���������ɣ�����ͼƬ��ģ��ѡ��shift+(���»������+�Զ����ÿؼ���С)��"), g_typeDefault));
	groupRect->AddSubItem(m_imageRandomMode	= AddPropButton(Language(L"ģ��:���һ��"), Language(L"m_imageRandomMode", L"���������ģ��ѡ��")));
	m_imageLists->AllowEdit(true);
	groupRect->AddSubItem(m_imageUnitSide		= AddPropButton(Language(L"�ؼ���� = ͼƬ���"), Language(L"m_imageUnitSide", L"�������ÿؼ���ͼƬͬ��С��")));
	groupRect->AddSubItem(m_imageRegetRect		= AddPropButton(Language(L"���ص�:��ȡͼƬ����"), Language(L"m_imageRegetRect", L"�������»��ͼƬ����")));
	//
	CMFCPropertyGridProperty* groupScale			= new CMFCPropertyGridProperty(Language(L"��������"));
	groupScale->AddSubItem(m_imageScale		= AddPropBool(Language(L"�Ƿ�����"), Language(L"�ؼ�ͼƬ_�Ƿ�����_˵��", L"����ͼƬ�Ƿ���Ա����š�")));
	groupScale->AddSubItem(m_imageContScale	= AddPropBool(Language(L"��������"), Language(L"�ؼ�ͼƬ_��������_˵��", L"������ô�������ݣ����߿�Ⱥ����߸߶�ͨ��һ��ͼƬ�Զ���������ɢ���š�")));
	groupScale->AddSubItem(m_imageContW		= AddPropInt(Language(L"���߿��"), Language(L"�ؼ�ͼƬ_���߿��_˵��", L"�������������Ч������������ã��������߸��ƵĿ�ȡ�")));
	groupScale->AddSubItem(m_imageContH		= AddPropInt(Language(L"���߸߶�"), Language(L"�ؼ�ͼƬ_���߸߶�_˵��", L"�������������Ч������������ã��������߸��Ƶĸ߶ȡ�")));
	groupScale->AddSubItem(m_imageTileW		= AddPropInt(Language(L"����ƽ��"), Language(L"�ؼ�ͼƬ_����ƽ��_˵��", L"����ͼƬ�Ƿ��������ƽ�̡�")));
	groupScale->AddSubItem(m_imageTileH		= AddPropInt(Language(L"����ƽ��"), Language(L"�ؼ�ͼƬ_����ƽ��_˵��", L"����ͼƬ�Ƿ��������ƽ�̡�")));
	groupScale->AddSubItem(m_imageTileLingXing		= AddPropBool(Language(L"����ƽ��"), Language(L"m_imageTileLingXing", L"����ͼƬ�Ƿ��������ƽ�̡�")));
	groupScale->AddSubItem(m_imageTileOffX		= AddPropInt(Language(L"����ƽ��ƫ��X"), Language(L"�ؼ�ͼƬ_����ƽ��_˵��", L"����ͼƬ�Ƿ��������ƽ��ƫ��X��")));
	groupScale->AddSubItem(m_imageTileOffY		= AddPropInt(Language(L"����ƽ��ƫ��Y"), Language(L"�ؼ�ͼƬ_����ƽ��_˵��", L"����ͼƬ�Ƿ��������ƽ��ƫ��Y��")));
	groupScale->AddSubItem(m_imageTileScaleX		= AddPropFloat(Language(L"����ƽ������X"), Language(L"�ؼ�ͼƬ_����ƽ��_˵��", L"����ͼƬ�Ƿ��������ƽ��ƫ��X��"),0, 0.01,10000));
	groupScale->AddSubItem(m_imageTileScaleY		= AddPropFloat(Language(L"����ƽ������Y"), Language(L"�ؼ�ͼƬ_����ƽ��_˵��", L"����ͼƬ�Ƿ��������ƽ��ƫ��Y��"),0, 0.01,10000));
	//
	CMFCPropertyGridProperty* groupText			= new CMFCPropertyGridProperty(Language(L"�ı�����"));
	groupText->AddSubItem(m_imageTextColor	= AddPropColor(Language(L"�ı���ɫ"), Language(L"�ؼ�ͼƬ_�ı���ɫ_˵��", L"���ؼ��ĵ�ǰͼƬ�����ı���ɫ��")));
	groupText->AddSubItem(m_imageTextAlpha	= AddPropFloat(Language(L"�ı�͸��ֵ"), Language(L"�ؼ�ͼƬ_�ı�͸��ֵ_˵��", L"���ؼ��ĵ�ǰͼƬ�����ı�͸��ֵ��")));
	//groupText->AddSubItem(m_imageShadowColor	= AddPropColor(Language(L"��Ӱ��ɫ"), Language(L"�ؼ�ͼƬ_��Ӱ��ɫ_˵��", L"���ؼ��ĵ�ǰͼƬ������Ӱ��ɫ��")));
	//groupText->AddSubItem(m_imageShadowAlpha	= AddPropFloat(Language(L"��Ӱ͸��ֵ"), Language(L"�ؼ�ͼƬ_��Ӱ͸��ֵ_˵��", L"���ؼ��ĵ�ǰͼƬ������Ӱ͸��ֵ��")));
	//
	CMFCPropertyGridProperty* groupUV			= new CMFCPropertyGridProperty(Language(L"UV��ͼ����"));
	groupUV->AddSubItem(m_imageUCount		= AddPropInt(Language(L"UV����:��������"), Language(L"�ؼ�ͼƬ_UV��������_˵��", L"����UV�����������������0���ʾû��UV������")));
	groupUV->AddSubItem(m_imageVCount		= AddPropInt(Language(L"UV����:��������"), Language(L"�ؼ�ͼƬ_UV��������_˵��", L"����UV�����������������0���ʾû��UV������")));
	groupUV->AddSubItem(m_imageUVPlaySpeed	= AddPropFloat(Language(L"UV����:�����ٶ�"), Language(L"�ؼ�ͼƬ_UV�����ٶ�_˵��", L"����UV�����ٶȣ��������0���ʾû��UV������")));
	groupUV->AddSubItem(m_imageInvW				= AddPropBool(Language(L"UV����:������"), Language(L"m_imageInvW", L"������")));
	groupUV->AddSubItem(m_imageInvH				= AddPropBool(Language(L"UV����:������"), Language(L"m_imageInvH", L"������")));
	//
	CMFCPropertyGridProperty* groupOffsetRect			= new CMFCPropertyGridProperty(Language(L"��ť�ؼ�:��С�仯"));
	groupOffsetRect->AddSubItem(m_imageOffsetLeft		= AddPropInt(Language(L"����"), Language(L"m_imageOffsetLeft", L"���ÿؼ���С�仯��ߡ�")));
	groupOffsetRect->AddSubItem(m_imageOffsetTop		= AddPropInt(Language(L"����"), Language(L"m_imageOffsetTop", L"���ÿؼ���С�仯�ϱߡ�")));
	groupOffsetRect->AddSubItem(m_imageOffsetWidth		= AddPropInt(Language(L"���ӿ��"), Language(L"m_imageOffsetWidth", L"���ÿؼ���С�仯��ȡ�")));
	groupOffsetRect->AddSubItem(m_imageOffsetHeight		= AddPropInt(Language(L"���Ӹ߶�"), Language(L"m_imageOffsetHeight", L"���ÿؼ���С�仯�߶ȡ�")));
	//
	CMFCPropertyGridProperty* groupOther			= new CMFCPropertyGridProperty(Language(L"��������"));
	groupOther->AddSubItem(m_imageColorOP		= AddPropOption(Language(L"��ͼ��ɫ���"), Language(L"�ؼ�ͼƬ_��ɫ��Ϸ�ʽ_˵��", L"������ɫ��Ϸ�ʽ��"), g_typeColorOP));
	groupOther->AddSubItem(m_imageSrcBlend		= AddPropOption(Language(L"Դ��Ϸ�ʽ"), Language(L"�ؼ�ͼƬ_Դ��Ϸ�ʽ_˵��", L"����Դ��Ϸ�ʽ��"), g_typeBlend));
	groupOther->AddSubItem(m_imageDestBlend		= AddPropOption(Language(L"Ŀ���Ϸ�ʽ"), Language(L"�ؼ�ͼƬ_Ŀ���Ϸ�ʽ_˵��", L"����Ŀ���Ϸ�ʽ��"), g_typeBlend));
	groupOther->AddSubItem(m_imageFilter		= AddPropOption(Language(L"���Ź��˷�ʽ"), Language(L"�ؼ�ͼƬ_���Ź��˷�ʽ_˵��", L"�������Ź��˷�ʽ��"), g_typeFilter));

	//this->m_imageProp.AddProperty(groupName);
	this->m_imageProp.AddProperty(group1);
	//this->m_imageProp.AddProperty(groupTexure);
	this->m_imageProp.AddProperty(groupRect);
	this->m_imageProp.AddProperty(groupScale);
	this->m_imageProp.AddProperty(groupText);
	this->m_imageProp.AddProperty(groupUV);
	this->m_imageProp.AddProperty(groupOffsetRect);
	this->m_imageProp.AddProperty(groupOther);
}

VOID	GCViewUIEditor::InitAnimationProp()
{
	CMFCPropertyGridProperty* group1			= new CMFCPropertyGridProperty(Language(L"��������"));
	group1->AddSubItem(m_animationName			= AddPropText(Language(L"��������"), Language(L"��������_˵��", L"���ÿؼ��������ơ�"), false, 50));
	group1->AddSubItem(m_animationFrameCount	= AddPropFloat(Language(L"����ʱ��"), Language(L"�ؼ�֡����_˵��", L"���ÿؼ������ؼ�֡������"), 0, 0.001f, 1000.0f));
	//group1->AddSubItem(m_animationIsDefault		= AddPropBool(Language(L"�Ƿ�Ĭ��"), Language(L"�Ƿ�Ĭ��_˵��", L"���ÿؼ������Ƿ�Ĭ�϶�����")));
	group1->AddSubItem(m_animationElement		= AddPropOption(Language(L"ͼƬ����"), Language(L"m_animationElement", L"���ÿؼ�ͼƬ���ơ�"), g_typeDefault));
	group1->AddSubItem(m_animationElementAni	= AddPropOption(Language(L"UV��������"), Language(L"m_animationElementAni", L"���ÿؼ�ͼƬUV�������ơ�"), g_typeDefault));
	//
	group1->AddSubItem(m_animationSpeed			= AddPropFloat(Language(L"�����ٶ�"), Language(L"�����ٶ�_˵��", L"���ÿؼ����������ٶȡ�"), false, 0.001f, 100.0f));
	group1->AddSubItem(m_animationLoopCount		= AddPropInt(Language(L"����ѭ������"), Language(L"m_animationLoopCount", L"���ÿؼ�����ѭ��������������ЧҲ��һ��ѭ����"), -1, 10000));
	group1->AddSubItem(m_animationType			= AddPropOption(Language(L"��������"), Language(L"m_animationType", L"���ÿؼ��������͡�"), g_typeUnitActionType));
	group1->AddSubItem(m_animationNextType		= AddPropOption(Language(L"��һ������"), Language(L"m_animationNextID", L"���ÿؼ���һ��������ѭ����Чʱ�������á�"), g_typeUnitActionType));
	group1->AddSubItem(m_animationHideOnOver	= AddPropBool(Language(L"���������ؿؼ�"), Language(L"m_animationHideOnOver˵��", L"���ò��������ؿؼ���")));
	CMFCPropertyGridProperty* groupSleep		= new CMFCPropertyGridProperty(Language(L"˯������"));
	groupSleep->AddSubItem(m_animationWaitEnable		= AddPropBool(Language(L"ǰ��˯��ʱ����Ч"), Language(L"m_animationWaitEnable", L"���ÿؼ�����ǰ��˯��ʱ����Ч��")));
	groupSleep->AddSubItem(m_animationSleepTime			= AddPropFloat(Language(L"ǰ��˯��ʱ��"), Language(L"m_animationSleepTime", L"���ÿؼ�����ǰ��˯��ʱ�䡣"), false, 0.0f, 100.0f));
	groupSleep->AddSubItem(m_animationHideAtSleep		= AddPropBool(Language(L"˯���ڼ�����"), Language(L"m_animationHideAtSleep_˵��", L"���ÿؼ�����˯���ڼ����ء�")));
	//
	CMFCPropertyGridProperty* groupWave			= new CMFCPropertyGridProperty(Language(L"��������"));
	groupWave->AddSubItem(m_animationWaveFile			= AddPropFile(Language(L"��Ч(*.wav)"), Language(L"m_animationWaveFile", L"���ÿؼ�������Ч��"), GetMusicFilter()));
	groupWave->AddSubItem(m_animationWaveFileClear		= AddPropButton(Language(L"ȥ����Ч"), Language(L"m_animationWaveFileClear", L"ȥ���ؼ�������Ч��")));
	groupWave->AddSubItem(m_animationWaveVolume			= AddPropFloat(Language(L"������С"), Language(L"m_animationWaveVolume", L"���ÿؼ�����������С��"), 0, 0.0, 1.0f));
	groupWave->AddSubItem(m_animationWaveSpeed			= AddPropFloat(Language(L"���������ٶ�"), Language(L"m_animationWaveSpeed", L"���ÿؼ��������������ٶȡ�"), 0, 0.1f, 10.0f));
	groupWave->AddSubItem(m_animationWaveSleepTime		= AddPropFloat(Language(L"ǰ������˯��ʱ��+"), Language(L"m_animationWaveSleepTime", L"���ÿؼ���������ǰ��˯��ʱ�䣬��ʱ�����϶��������˯��ʱ�䡣"), false, 0.0f, 100.0f));
	//
	this->m_animationProp.AddProperty(group1);
	this->m_animationProp.AddProperty(groupSleep);
	this->m_animationProp.AddProperty(groupWave);

	m_animationTrack.m_baseView	=	this;
	m_animationTrack.Create(m_animationTrack.IDD, GetPropertiesDlgWindowPtr());
	//m_animationTrack.AddEditor(Language(L"�ı���ɫ"), UI_VALUE_TEXT_COLOR, 0.0f, 1.0f, true);
	//m_animationTrack.AddEditor(Language(L"�ı�͸��"), UI_VALUE_TEXT_ALPHA, 0.0f, 1.0f, false);
	m_animationTrack.AddEditor(Language(L"��ɫ"), UI_VALUE_TEXTURE_COLOR, 0.0f, 1.0f, true);
	m_animationTrack.AddEditor(Language(L"͸��"), UI_VALUE_TEXTURE_ALPHA, 0.0f, 1.0f, false);
	m_animationTrack.AddEditor(Language(L"λ��"), UI_VALUE_Position, GetMinWindowPos() / 4, GetMaxWindowPos() / 4, false);
	m_animationTrack.AddEditor(Language(L"��С"), UI_VALUE_WidthHeight, GetMinWindowPos() / 4, GetMaxWindowPos() / 4, false);
	m_animationTrack.AddEditor(Language(L"���ĵ�"), UI_VALUE_Center, GetMinWindowPos() / 4, GetMaxWindowPos() / 4, false);
	m_animationTrack.AddEditor(Language(L"ת����"), UI_VALUE_Rotation, -360, 360, false);
	//m_animationTrack.AddEditor(Language(L"ͼƬUֵ"), Phantom::ControlTrackType_UStart, 0, 1.0f, false);
	//m_animationTrack.AddEditor(Language(L"ͼƬVֵ"), Phantom::ControlTrackType_VStart, 0, 1.0f, false);
	//m_animationTrack.AddEditor(Language(L"������С"), Phantom::ControlTrackType_SoundVolume, 0, 1.0f, false);
	//m_animationTrack.AddEditor(Language(L"�����ٶ�"), Phantom::ControlTrackType_SoundSpeed, 0.01f, 10.0f, false);
	//
	m_animationTrack.AddEditor(Language(L"��ɫ���"), UI_VALUE_TextureColorMin, 0.0f, 1.0f, true);
	m_animationTrack.AddEditor(Language(L"λ�����"), UI_VALUE_OffsetMin, -10.0f, 10.0f, false);
	m_animationTrack.AddEditor(Language(L"��С���"), UI_VALUE_SizeMin, 0.0f, 2.0f, false);
	m_animationTrack.AddEditor(Language(L"���䷽�����"), UI_VALUE_RotationMin, 0.0f, 360.0f, false);
	m_animationTrack.AddEditor(Language(L"��������"), UI_VALUE_LifeMin, 0.0f, 1.0f, false);
	m_animationTrack.AddEditor(Language(L"��������"), UI_VALUE_EmitCount, 0.0f, 10.0f, false);
	//
	m_animationTrack.AddEditor(Language(L"����"), Phantom::ControlTrackType_VStart, -10.0f, 10.0f, false);
}

VOID	GCViewUIEditor::InitUvmapProp()
{
	CMFCPropertyGridProperty* group1			= new CMFCPropertyGridProperty(Language(L"��������"));
	group1->AddSubItem(m_uvmapName				= AddPropText(Language(L"��������"), Language(L"UV��������_˵��", L"���ÿؼ��������ơ�"), false, 50));
	group1->AddSubItem(m_uvmapDefault			= AddPropBool(Language(L"Ĭ�϶���"), Language(L"UVĬ�϶���_˵��", L"���ÿؼ���Ĭ��UV������")));
	group1->AddSubItem(m_uvmapKeyLoopCount		= AddPropInt(Language(L"ѭ������"), Language(L"UV����ѭ������_˵��", L"���ÿؼ�������ѭ��������-1��ʾ����ѭ�����š�"), -1, 10000));
	group1->AddSubItem(m_uvmapKeyPlaySpeed		= AddPropFloat(Language(L"�����ٶ�"), Language(L"�����ٶ�_˵��", L"���ÿؼ����������ٶȡ�"), false, 0.001f, 1000.0f));
	group1->AddSubItem(m_uvmapBeginIndex		= AddPropInt(Language(L"��ʼ����"), Language(L"��ʼ����_˵��", L"���ÿؼ�������ʼ������"), 0, 10000));
	group1->AddSubItem(m_uvmapFrameCount		= AddPropInt(Language(L"����֡����"), Language(L"����֡����_˵��", L"���ÿؼ�����֡������"), 1, 10000));
	group1->AddSubItem(m_uvmapAngle				= AddPropOption(Language(L"8������-ѡ��"), Language(L"����8������-ѡ��_˵��", L"���ÿؼ�����8������-ѡ��(����2D��λ�ؼ���Ч)��"), g_type2DUnitAngle));
	//
	group1->AddSubItem(m_uvmapInvW				= AddPropBool(Language(L"������"), Language(L"m_uvmapInvW", L"������")));
	group1->AddSubItem(m_uvmapInvH				= AddPropBool(Language(L"������"), Language(L"m_uvmapInvH", L"������")));
	group1->AddSubItem(m_uvmapCustomEnable		= AddPropBool(Language(L"�Զ�����ͼ"), Language(L"m_uvmapCustomEnable", L"���ÿؼ��Զ�����ͼ��")));
	group1->AddSubItem(m_uvmapAutoImages		= AddPropText(Language(L"���ģ������"), Language(L"m_uvmapAutoImages", L"�����Զ���ģ�幹�죬�����ÿ�ʼֵ������������ֵ��")));
	group1->AddSubItem(m_uvmapLayerAdd			= AddPropInt(Language(L"�㼶��������"), Language(L"m_uvmapLayerAdd", L"���ò㼶��������,�������ͽ�ɫͬʱ��Ⱦʱ������Ⱦ�Ⱥ�����ʱ���õ���"), -10, 10));
	//
	m_uvmapCustomGroup		= new CMFCPropertyGridProperty(Language(L"�Զ�������"));
	//
	m_uvmapCustomGroup->AddSubItem(m_uvmapSet		= AddPropFile(Language(L"����ͼƬ"), Language(L"�ؼ�ͼƬ_����ͼƬ_˵��", L"���ÿؼ�ͼƬ��"), GetImageFilter()));
	m_uvmapCustomGroup->AddSubItem(m_uvmapClear		= AddPropButton(Language(L"���ͼƬ"), Language(L"�ؼ�ͼƬ_���ͼƬ_˵��", L"��տؼ��ĵ�ǰͼƬ��")));
	m_uvmapCustomGroup->AddSubItem(m_uvmapRegetRects		= AddPropButton(Language(L"����ȡ��ͼƬ����"), Language(L"m_uvmapRegetRects", L"����ȡ��ͼƬ����������ͼƬ������PngMaker���ɹ������������")));
	//m_uvmapCustomGroup->AddSubItem(m_uvmapUCount	= AddPropInt(Language(L"����ͼƬ,��������"), Language(L"�ؼ�ͼƬ_UV��������_˵��", L"����UV�����������������0���ʾû��UV������")));
	//m_uvmapCustomGroup->AddSubItem(m_uvmapVCount	= AddPropInt(Language(L"����ͼƬ,��������"), Language(L"�ؼ�ͼƬ_UV��������_˵��", L"����UV�����������������0���ʾû��UV������")));
	m_uvmapCustomGroup->AddSubItem(m_uvmapActionType		= AddPropOption(Language(L"��������"), Language(L"m_uvmapActionType", L"����UV���Ŷ������͡�"), g_typeUnitActionType));
	m_uvmapCustomGroup->AddSubItem(m_uvmapNextActionType		= AddPropOption(Language(L"��һ������"), Language(L"m_uvmapNextActionType", L"����UV��һ�����Ŷ������͡�"), g_typeUnitActionType));

	m_uvmapCustomGroup->AddSubItem(m_uvmapNextActionRand		= AddPropFloat(Language(L"��һ����������"), Language(L"m_uvmapNextActionRand", L"����UV��һ����������"), false, 0.001f, 1000.0f));
	m_uvmapCustomGroup->AddSubItem(m_uvmapMoveOffset		= AddPropBool(Language(L"�ƶ�λ����Ч"), Language(L"m_uvmapMoveOffset", L"�����ƶ�λ����Ч��")));
	m_uvmapCustomGroup->AddSubItem(m_uvmapMoveOffsetX		= AddPropInt(Language(L"�ƶ�λ��X(����)"), Language(L"m_uvmapMoveOffsetX", L"�ӿؼ�ԭʼ�㵽�ƶ�λ��X(����)��"), -10000,10000));
	m_uvmapCustomGroup->AddSubItem(m_uvmapMoveOffsetY		= AddPropInt(Language(L"�ƶ�λ��Y(����)"), Language(L"m_uvmapMoveOffsetY", L"�ӿؼ�ԭʼ�㵽�ƶ�λ��Y(����)��"), -10000,10000));
	m_uvmapCustomGroup->AddSubItem(m_uvmapMoveOffsetSpeed		= AddPropFloat(Language(L"�ƶ��ٶ�(����)"), Language(L"m_uvmapMoveOffsetSpeed", L"�����ƶ��ٶ�"), false, 0.1f, 1000.0f));
	//
	this->m_uvmapProp.AddProperty(group1);
	this->m_uvmapProp.AddProperty(m_uvmapCustomGroup);
	//
	CMFCPropertyGridProperty* uvmapRect			= new CMFCPropertyGridProperty(Language(L"��������"));
	uvmapRect->AddSubItem(m_uvmapLeft		= AddPropInt(Language(L"��"), Language(L"�ؼ�ͼƬ_���_˵��", L"����ͼƬ��Ч������ߡ�")));
	uvmapRect->AddSubItem(m_uvmapTop		= AddPropInt(Language(L"��"), Language(L"�ؼ�ͼƬ_�ϱ�_˵��", L"����ͼƬ��Ч�����ϱߡ�")));
	uvmapRect->AddSubItem(m_uvmapWidth		= AddPropInt(Language(L"���"), Language(L"�ؼ�ͼƬ_���_˵��", L"����ͼƬ��Ч�����ȡ�")));
	uvmapRect->AddSubItem(m_uvmapHeight		= AddPropInt(Language(L"�߶�"), Language(L"�ؼ�ͼƬ_�߶�_˵��", L"����ͼƬ��Ч����߶ȡ�")));
	uvmapRect->AddSubItem(m_uvmapOffsetX	= AddPropInt(Language(L"ƫ��X"), Language(L"m_uvmapOffsetX", L"����ͼƬ��Ч����ƫ��x��")));
	uvmapRect->AddSubItem(m_uvmapOffsetY	= AddPropInt(Language(L"ƫ��Y"), Language(L"m_uvmapOffsetY˵��", L"����ͼƬ��Ч��ƫ��y��")));
	uvmapRect->AddSubItem(m_uvmapTexture	= AddPropFile(Language(L"ͼƬ��������"), Language(L"m_uvmapTexture", L"���õ����ؼ�֡ͼƬ������ͼƬ����ʱʹ�á�"), GetImageFilter()));
	uvmapRect->AddSubItem(m_uvmapTextureClear	= AddPropButton(Language(L"ȥ��ͼƬ����"), Language(L"m_uvmapTextureClear", L"����ȥ��ͼƬ���á�")));
	uvmapRect->AddSubItem(m_uvmapImageLists		= AddPropOption(Language(L"��ģ��ѡ��ͼƬ"), Language(L"m_uvmapImageLists", L"���ô�ģ��ѡ��ͼƬ��"), g_typeDefault));
	m_uvmapImageLists->AllowEdit(true);
	this->m_uvmapRectProp.AddProperty(uvmapRect);
}

VOID	GCViewUIEditor::InitTexAniProp()
{
}

VOID	GCViewUIEditor::InitGroupProp()
{
	CMFCPropertyGridProperty* group1			= new CMFCPropertyGridProperty(Language(L"��������"));
	group1->AddSubItem(m_groupName				= AddPropText(Language(L"������"), Language(L"�ؼ�������_˵��", L"���ÿؼ������ơ�"), false, 50));
	group1->AddSubItem(m_groupVisible			= AddPropBool(Language(L"�Ƿ���ʾ"), Language(L"�ؼ���ʾ��ؼ�_˵��", L"�����Ƿ���ʾ��ؼ���")));
	group1->AddSubItem(m_groupEnable			= AddPropBool(Language(L"�Ƿ���Ч"), Language(L"m_groupEnable", L"�����Ƿ���Ч��")));
	group1->AddSubItem(m_groupSleepTime			= AddPropFloat(Language(L"�鶯������ǰ˯��"), Language(L"m_groupSleepTime", L"�����鶯������ǰ˯�ߡ�"), false, 0.0f, 100.0f));
	CMFCPropertyGridProperty* group2			= new CMFCPropertyGridProperty(Language(L"2D��ɫ����"));
	group2->AddSubItem(m_groupIsUnit			= AddPropBool(Language(L"��Ϊ2D��λ��ʹ��"), Language(L"m_groupIsUnit", L"������Ϊ2D��λ��ʹ��,���2D��������Ϸ��ʱ��ʹ�á�")));
	group2->AddSubItem(m_groupAngle				= AddPropFloat(Language(L"����8������Ƕ�"), Language(L"m_groupAngle", L"����8������Ƕȡ�"), false, -180, 180));
	group2->AddSubItem(m_groupSpeed				= AddPropFloat(Language(L"�����ٶ�"), Language(L"m_groupSpeed", L"��ɫ���Ʋ����ٶȡ�"), false, -50, 50));
	group2->AddSubItem(m_groupAction			= AddPropOption(Language(L"��ǰ����"), Language(L"m_groupAction", L"��ɫ��ǰ������"), g_typeUnitActionType));
	//
	this->m_groupProp.AddProperty(group1);
	this->m_groupProp.AddProperty(group2);
}
#ifdef USE_BOX
VOID	GCViewUIEditor::InitBodyProp()
{
	CMFCPropertyGridProperty* group1			= new CMFCPropertyGridProperty(Language(L"��������"));
	group1->AddSubItem(m_body_id				= AddPropInt(Language(L"ID"), Language(L"m_body_id", L"����ID��")));
	m_body_id->AllowEdit(false);
	group1->AddSubItem(m_body_name				= AddPropText(Language(L"Name"), Language(L"m_body_name", L"����Name��"), false, Name::Length));
	group1->AddSubItem(m_body_bodyType			= AddPropOption(Language(L"��������"), Language(L"m_body_bodyType", L"���ö������͡�"), g_typeBox2DBodyType));
	group1->AddSubItem(m_body_position_x		= AddPropFloat(Language(L"λ��X"), Language(L"m_body_position_x", L"���ö���λ��X��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_body_position_y		= AddPropFloat(Language(L"λ��Y"), Language(L"m_body_position_y", L"���ö���λ��Y��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_body_angle				= AddPropFloat(Language(L"�Ƕ�"), Language(L"m_body_angle", L"���ýǶȡ�"), FloatType_Angle, -360.0f, 360.0f));
	group1->AddSubItem(m_body_linearVelocity_x	= AddPropFloat(Language(L"�ƶ��ٶ�X"), Language(L"m_body_linearVelocity_x", L"�����ƶ�����X��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_body_linearVelocity_y	= AddPropFloat(Language(L"�ƶ��ٶ�Y"), Language(L"m_body_linearVelocity_y", L"�����ƶ�����X��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_body_angularVelocity	= AddPropFloat(Language(L"ת���ٶ�"), Language(L"m_body_angularVelocity", L"���ý��ٶȡ�"), false, -10000.0f, 10000.0f));
	//
	group1->AddSubItem(m_body_linearDamping		= AddPropFloat(Language(L"��������"), Language(L"m_body_linearDamping", L"�������ᡣ"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_body_angularDamping	= AddPropFloat(Language(L"ת������"), Language(L"m_body_angularDamping", L"ת�����ᡣ"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_body_gravityScale		= AddPropFloat(Language(L"������"), Language(L"m_body_gravityScale", L"�����ӡ�"), false, -10000.0f, 10000.0f));
	//
	group1->AddSubItem(m_body_allowSleep		= AddPropBool(Language(L"˯��"), Language(L"m_body_allowSleep", L"˯�ߡ�")));
	group1->AddSubItem(m_body_awake				= AddPropBool(Language(L"��"), Language(L"m_body_awake", L"�ѡ�")));
	group1->AddSubItem(m_body_fixedRotation		= AddPropBool(Language(L"�̶���ת"), Language(L"m_body_fixedRotation", L"�̶���ת��")));
	group1->AddSubItem(m_body_bullet			= AddPropBool(Language(L"�ӵ�"), Language(L"m_body_bullet", L"�ӵ���")));
	group1->AddSubItem(m_body_active			= AddPropBool(Language(L"��Ծ"), Language(L"m_body_active", L"��Ծ��")));
	//
	m_bodyProp.AddProperty(group1);
}
VOID	GCViewUIEditor::InitShapeProp()
{
	CMFCPropertyGridProperty* group1			= new CMFCPropertyGridProperty(Language(L"��������"));
	group1->AddSubItem(m_shape_id				= AddPropInt(Language(L"ID"), Language(L"m_shape_id", L"����ID��")));
	m_shape_id->AllowEdit(false);
	group1->AddSubItem(m_shape_type				= AddPropOption(Language(L"��״����"), Language(L"m_shape_type", L"������״���͡�"), g_typeBox2DShapeType));
	group1->AddSubItem(m_shape_control			= AddPropOption(Language(L"����2D�ؼ�"), Language(L"m_shape_control", L"����2D�ؼ���"), g_typeDefault));
	group1->AddSubItem(m_shape_m_density		= AddPropFloat(Language(L"�ܶ�"), Language(L"m_shape_m_density", L"�ܶȡ�"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_shape_m_radius			= AddPropFloat(Language(L"�뾶"), Language(L"m_shape_m_radius", L"�뾶��"), false, 0.01f, 10000.0f));
	group1->AddSubItem(m_shape_m_p_x			= AddPropFloat(Language(L"λ��X"), Language(L"m_shape_m_p_x", L"λ��X��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_shape_m_p_y			= AddPropFloat(Language(L"λ��Y"), Language(L"m_shape_m_p_y", L"λ��Y��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_shape_m_fAngle			= AddPropFloat(Language(L"ת����"), Language(L"m_shape_m_fAngle", L"ת���ʡ�"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_shape_m_boxWidth		= AddPropFloat(Language(L"���ӿ��"), Language(L"m_shape_m_boxWidth", L"���ӿ�ȡ�"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_shape_m_boxHeight		= AddPropFloat(Language(L"���Ӹ߶�"), Language(L"m_shape_m_boxHeight", L"���Ӹ߶ȡ�"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_shape_m_bChainLoop		= AddPropBool(Language(L"�����ر�"), Language(L"m_shape_m_bChainLoop", L"�����رա�")));
	group1->AddSubItem(m_shape_m_hasVertex0		= AddPropBool(Language(L"����0��Ч"), Language(L"m_shape_m_hasVertex0", L"����0��Ч��")));
	group1->AddSubItem(m_shape_m_hasVertex3		= AddPropBool(Language(L"����3��Ч"), Language(L"m_shape_m_hasVertex3", L"����3��Ч��")));
	//
	m_shapeProp.AddProperty(group1);
}

VOID	GCViewUIEditor::InitJointProp()
{
	CMFCPropertyGridProperty* group1			= new CMFCPropertyGridProperty(Language(L"��������"));
	group1->AddSubItem(m_joint_id				= AddPropInt(Language(L"ID"), Language(L"m_joint_id", L"������ID��")));
	group1->AddSubItem(m_joint_name				= AddPropText(Language(L"Name"), Language(L"m_body_name", L"����Name��"), false, Name::Length));
	m_joint_id->AllowEdit(false);
	group1->AddSubItem(m_joint_jointType		= AddPropOption(Language(L"����������"), Language(L"m_joint_jointType", L"jointType��"), g_typeBox2DJointType));
	group1->AddSubItem(m_joint_bodyA			= AddPropOption(Language(L"����A"), Language(L"m_joint_bodyA", L"����A��"), g_typeDefault));
	group1->AddSubItem(m_joint_bodyB			= AddPropOption(Language(L"����B"), Language(L"m_joint_bodyB", L"����B��"), g_typeDefault));
	group1->AddSubItem(m_joint_collideConnected	= AddPropBool(Language(L"collideConnected"), Language(L"m_joint_collideConnected", L"λ��X��")));
	group1->AddSubItem(m_joint_localAnchorA_x	= AddPropFloat(Language(L"êAx"), Language(L"m_joint_localAnchorA_x", L"êAx��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_localAnchorA_y	= AddPropFloat(Language(L"êAy"), Language(L"m_joint_localAnchorA_y", L"êAy��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_localAnchorB_x	= AddPropFloat(Language(L"êBx"), Language(L"m_joint_localAnchorB_x", L"êBx��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_localAnchorB_y	= AddPropFloat(Language(L"êBy"), Language(L"m_joint_localAnchorB_y", L"êBy��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_maxForce			= AddPropFloat(Language(L"ǿ��"), Language(L"m_joint_maxForce", L"ǿ�ơ�"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_maxTorque		= AddPropFloat(Language(L"ת��"), Language(L"m_joint_maxTorque", L"ת�ء�"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_joint1			= AddPropOption(Language(L"��������������A"), Language(L"m_joint_joint1", L"��������������A��"), g_typeDefault));
	group1->AddSubItem(m_joint_joint2			= AddPropOption(Language(L"��������������B"), Language(L"m_joint_joint2", L"��������������B��"), g_typeDefault));
	group1->AddSubItem(m_joint_ratio			= AddPropFloat(Language(L"ratio"), Language(L"m_joint_ratio", L"ratio��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_target_x			= AddPropFloat(Language(L"Ŀ��x"), Language(L"m_joint_target_x", L"Ŀ��x��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_target_y			= AddPropFloat(Language(L"Ŀ��y"), Language(L"m_joint_target_y", L"Ŀ��y��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_frequencyHz		= AddPropFloat(Language(L"frequencyHz"), Language(L"m_joint_frequencyHz", L"frequencyHz��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_localAxisA_x		= AddPropFloat(Language(L"localAxisAx"), Language(L"m_joint_localAxisA_x", L"localAxisAx��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_localAxisA_y		= AddPropFloat(Language(L"localAxisAy"), Language(L"m_joint_localAxisA_y", L"localAxisAy��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_referenceAngle	= AddPropFloat(Language(L"referenceAngle"), Language(L"m_joint_referenceAngle", L"referenceAngle��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_enableLimit		= AddPropBool(Language(L"enableLimit"), Language(L"m_joint_enableLimit", L"enableLimit��")));
	group1->AddSubItem(m_joint_lowerTranslation	= AddPropFloat(Language(L"lowerTranslation"), Language(L"m_joint_lowerTranslation", L"lowerTranslation��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_upperTranslation	= AddPropFloat(Language(L"upperTranslation"), Language(L"m_joint_upperTranslation", L"upperTranslation��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_enableMotor		= AddPropBool(Language(L"����Ħ��"), Language(L"m_joint_enableMotor", L"����Ħ����")));
	group1->AddSubItem(m_joint_maxMotorForce	= AddPropFloat(Language(L"���Ħ��"), Language(L"m_joint_maxMotorForce", L"���Ħ����"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_motorSpeed		= AddPropFloat(Language(L"Ħ��ϵ��"), Language(L"m_joint_motorSpeed", L"Ħ��ϵ����"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_groundAnchorA_x	= AddPropFloat(Language(L"groundAnchorAx"), Language(L"m_joint_groundAnchorA_x", L"groundAnchorAx��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_groundAnchorA_y	= AddPropFloat(Language(L"groundAnchorAy"), Language(L"m_joint_groundAnchorA_y", L"groundAnchorAy��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_groundAnchorB_x	= AddPropFloat(Language(L"groundAnchorBx"), Language(L"m_joint_groundAnchorB_x", L"groundAnchorBx��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_groundAnchorB_y	= AddPropFloat(Language(L"groundAnchorBy"), Language(L"m_joint_groundAnchorB_y", L"groundAnchorBy��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_lengthA			= AddPropFloat(Language(L"lengthA"), Language(L"m_joint_lengthA", L"lengthA��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_lengthB			= AddPropFloat(Language(L"lengthB"), Language(L"m_joint_lengthB", L"lengthB��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_lowerAngle		= AddPropFloat(Language(L"lowerAngle"), Language(L"m_joint_lowerAngle", L"lowerAngle��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_upperAngle		= AddPropFloat(Language(L"upperAngle"), Language(L"m_joint_upperAngle", L"upperAngle��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_maxMotorTorque	= AddPropFloat(Language(L"maxMotorTorque"), Language(L"m_joint_maxMotorTorque", L"maxMotorTorque��"), false, -10000.0f, 10000.0f));
	group1->AddSubItem(m_joint_maxLength		= AddPropFloat(Language(L"maxLength"), Language(L"m_joint_maxLength", L"maxLength��"), false, -10000.0f, 10000.0f));
	//
	m_jointProp.AddProperty(group1);
}
#endif
VOID	GCViewUIEditor::InitEffectProp()
{
	this->InitViewerProps();
	InitProp(m_dlgProp);
	InitProp(m_controlProp);
	InitProp(m_imageProp);
	InitProp(m_animationProp);
	InitProp(m_uvmapProp);
	InitProp(m_texAniProp);
	InitProp(m_groupProp);
	InitProp(m_uvmapRectProp);
#ifdef USE_BOX
	InitProp(m_bodyProp);
	InitProp(m_jointProp);
	InitProp(m_shapeProp);
#endif
	//
	InitDialogProp();
	InitControlProp();
	InitImageProp();
	InitAnimationProp();
	InitUvmapProp();
	InitTexAniProp();
	InitGroupProp();
#ifdef USE_BOX
	InitBodyProp();
	InitShapeProp();
	InitJointProp();
#endif
}
