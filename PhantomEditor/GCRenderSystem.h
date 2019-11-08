/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once

#define	VIEW_TOP_RESERVED	18
#define	VIEW_LEFT_RESERVED	6
//��ʼ����Ⱦϵͳ
BOOL	InitRenderSystem(HWND hWndMain);
VOID	DestroyRenderSystem();
VOID	SetRenderParent(HWND hWndParent);
VOID	ShowRender(BOOL bShow);
INT		GetRenderWindowWidth();
INT		GetRenderWindowHeight();
VOID	MoveRenderWindow(HWND hWndCurrent, INT w, INT h);
VOID	SetBackgroundColor(const Phantom::color4& c);
VOID	SetRenderWindowSize(INT w, INT h);
