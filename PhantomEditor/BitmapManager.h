//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	�ļ�       :   BitmapManager.h
	�������   :   ��Ӱ��Ϸ����

	��Ʊ�д�� :   �Ե���(Ӣ��:ZhaoDexian)
	Email: yuzhou_995@hotmail.com
	
	Copyright 2009-2016 Zhao Dexian
	
	-------------------------------------------------------------------------------------------------


	-------------------------------------------------------------------------------------------------
	*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BITMAPMANAGER__H___
#define ___BITMAPMANAGER__H___


#pragma once
#include "IDEDefine.h"
#include "GifImagePlayer.h"

struct IDEImageData
{
	INT				nResourceID;
	CImage			vImage;
	INT				nImageID;		//��CImageList��
	INT				nImageIndex;	//��CImageList��
	CString			strFile;
	IDEImageData(){nImageID = -1; nResourceID = -1; nImageIndex = -1; }
};

enum{
	FONT_MODE_NORMAL	=	1,
	FONT_MODE_BOLD,
};

struct FontData
{
	wchar_t					fontName[32];
	INT						nHeight;
	BOOL					bBold;
	BOOL					bUnderline;
	CFont					font;
	INT						nID;
};

struct CursorData
{
	HCURSOR					hCursor;
	INT						nID;
	LPCWSTR					szWID;
	CursorData(){hCursor = 0; nID = 0; szWID = 0;}
};

#define	TREE_IMAGE_HEIGHT		17

struct HotkeyData
{
	bool			bShift, bCtrl, bAlt;
	int				vkKey;
	CMenuItem*		pMenuItem;
};

class CHotkeyManager
{
public:
	CHotkeyManager();
	~CHotkeyManager();
	VOID				RegisterHotkey(INT vkKey, bool bShift, bool bCtrl, bool bAlt, CMenuItem* pMenuItem);
	BOOL				DoHotkey(INT vkKey);
public:
	std::vector<HotkeyData>	m_hotkeys;
};

CHotkeyManager*			GetHotkeyManagerPtr();

class CResourceManager
{
public:
	CResourceManager(void);
	~CResourceManager(void);
	CImage*					GetImageByResID(INT nResID);
	INT						GetIndexByResID(INT nResID);
	//
	CImage*					GetImageByFile(LPCTSTR szFile);
	VOID					AddFromFile(LPCTSTR szFile);	//���ļ�����
	CImage*					LoadFromResToAtlImage(INT nResourceID);
	INT						LoadFromResToImageList(INT nResourceID);
	INT						LoadFromResToImageTreeList(INT nResourceID);
	//
	VOID					LoadAllResources();
	//
	CImageList*				GetImageListPtr(){return &m_imageList;}
	CImageList*				GetImageListTreePtr(){return &m_imageListTree;}
	//
	CFont*					GetFontPtr(const wchar_t* szFontName, INT nHeight, BOOL bBold, BOOL bUnderline, INT nID);
	CFont*					GetFontPtr(INT nMode);
	VOID					SetCurrentCursor(INT nResID);
	VOID					SetCurrentCursor(LPCWSTR szResID);
protected:
	std::vector<IDEImageData*>	m_images;
	std::vector<FontData*>	m_fonts;
	std::vector<CursorData>	m_cursors;
	std::vector<IDEImageData*>	m_treeImages;
	CImageList				m_imageList;//ȫ��Ψһ
	CImageList				m_imageListTree;//ȫ��Ψһ
public:
};

CResourceManager*	GetBitmapManagerPtr();

#endif
