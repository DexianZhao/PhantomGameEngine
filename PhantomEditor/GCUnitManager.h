//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	�ļ�       :   GCSelectEditor.h
	�������   :   ��Ӱ��Ϸ����

	��Ʊ�д�� :   �Ե���(Ӣ��:ZhaoDexian)
	Email: yuzhou_995@hotmail.com
	
	Copyright 2009-2016 Zhao Dexian
	
	-------------------------------------------------------------------------------------------------


	-------------------------------------------------------------------------------------------------
	*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___GCSELECTEDITORBASE__H___
#define ___GCSELECTEDITORBASE__H___

#pragma once
#include <PhantomProject.h>
//
//class GCUnitEditor
//{
//public:
//	GCUnitEditor();
//	virtual	~GCUnitEditor();
//	//
//	const PRect&					GetSaveRect(){return m_saveRect;}
//	virtual	GCUnitManager*			GetUnitManager()	=	0;	//���ض��������
//	//
//public://��д����
//	virtual	VOID					SaveRect()		=	0;		//�������λ��
//	virtual	const PRect*			GetUnitRect()	=	0;		//���ض������
//	virtual	VOID					SetUnitRect(const PRect& rc)	=	0;
//	virtual	PPixel					WindowToUnit(const PPixel& p)	=	0;	//�Ӵ�������ת������������
//	virtual	PPixel					UnitToWindow(const PPixel& p)	=	0;	//�Ӷ�������ת������������
//	virtual	BOOL					IsRotation()				=	0;		//�Ƿ�֧��ת��
//	virtual	VOID					SetRotation(BOOL b)			=	0;		//����ת��֧��
//	virtual	float					GetRotationAngle()			=	0;
//	virtual	VOID					SetRotationAngle(float f)	=	0;
//public:
//	PRect							m_saveRect;
//};
//
//class GCSelectEditor
//{
//public:
//	GCSelectEditor(void);
//	virtual ~GCSelectEditor(void);
//	//
//	enum PickType
//	{
//		PickType_Body			=	1,
//		PickType_MoveSide,
//		PickType_Unit2DCenter,
//	};
//	//
//	enum MouseMode{
//		MouseMode_None	=	0,
//		MouseMode_InsertControl,
//		MouseMode_MoveControl,
//		MouseMode_TabIndex,
//		MouseMode_SelectRect,
//		MouseMode_SizeControl,
//		MouseMode_MoveCopy,
//		MouseMode_Unit2DCenterPos,
//		MouseMode_SetFloor,
//		MouseMode_InsertUnit2D,
//	};
//	//
//	enum ToAlign{
//		ToAlign_None	=	0,
//		ToAlign_Left	=	0x01,
//		ToAlign_Right	=	0x02,
//		ToAlign_Top		=	0x04,
//		ToAlign_Bottom	=	0x08,
//	};
//	enum MovePointSide{
//		MovePointSide_Left	=	0,
//		MovePointSide_Right,
//		MovePointSide_Top,
//		MovePointSide_Bottom,
//		MovePointSide_LeftTop,
//		MovePointSide_LeftBottom,
//		MovePointSide_RightTop,
//		MovePointSide_RightBottom,
//		MovePointSide_Center,
//		MovePointSide_Rotation,
//		MovePointSide_Count,
//	};
//	//
//	struct	PickInfo
//	{
//		int			nMovePointSide;
//		int			nPickType;
//	};
//	//
//	//
//	virtual	GCUnitEditor*			PickInSelect(const PPixel& pos, PickInfo& ret);	//���Ѿ�ѡ����б���ѡ��һ��
//	virtual	BOOL					IsPickIsSelect(const PPixel& pos, GCUnitEditor* c, PickInfo& ret);
//	//
//	virtual	GCUnitEditor*			PickNew(const PPixel& pos);
//	//
//	virtual	VOID					GetRectPoints(const PRect& rc, GCUnitEditor* c, PRect* rets);
//	//
//	VOID							ClearSelect();
//	VOID							AddSelect(GCUnitEditor* ed);
//public://��������д
//	virtual	GCUnitEditor*			CloneUnit(GCUnitEditor* ed);
//	virtual	GCUnitEditor*			GetUnitPtr(VOID* ptr);	//�Զ�����һ������
//	virtual	GCUnitEditor*			GetUnitPtr(INT index);
//	virtual	INT						GetUnitCount();			//���ض�������
//protected:
//	GCUnitEditor*					m_moveUnitPtr;			//�ƶ�ʱѡ��Ķ���
//	PPixel							m_downPoint;
//	PPixel							m_lastPoint;
//	//
//public:
//};



#endif
