//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	�ļ�       :   ViewImageManager.h
	�������   :   ��Ӱ��Ϸ���棨www.aixspace.com��

	��Ʊ�д�� :   �Ե���(Ӣ��:ZhaoDexian)
	Email: yuzhou_995@hotmail.com
	Copyright 2009-2016 Zhao Dexian
	
	
	
	
	

	
	-------------------------------------------------------------------------------------------------


	-------------------------------------------------------------------------------------------------
	*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___VIEWIMAGEMANAGER__H___
#define ___VIEWIMAGEMANAGER__H___


#pragma once
#include "atlimage.h"
#include <vector>
#include "resource.h"
struct	PFileName
{
	char	szRealName[255];	//��ʵ�ļ�·��
	char	szFileName[255];	//���·��
	PFileName(const char* sz){strncpy(szFileName,sz,254);strncpy(szRealName,sz,254);}
	PFileName(){szRealName[0] = 0; szFileName[0] = 0;}
};

struct	PMyFileList
{
	std::vector<PFileName>	vFiles;
};
void	enum_files(const char* path,std::vector<PFileName>& _out, int subFolderLevel, std::string* szFindType,int numFindTypes);
void	destroyFileList(PMyFileList* fList);
PMyFileList*	enum_files(const char* path, int subFolderLevel,std::string* szFindTypes,int numFindTypes);

struct ImageItem
{
	Phantom::FileName		filePath;
	Phantom::Name			name;
	Phantom::Name			fileName;
	CImage			img;
};

class CViewImageManager
{
public:
	CViewImageManager(void);
	~CViewImageManager(void);
	void						addImage(const char* strFile);
	void						reloadImages();
	//
	ImageItem*					findImageByName(const char* szName);
	ImageItem*					findImageByFile(const char* szFile);
	ImageItem*					findImageByFileName(const char* szFileName);
	ImageItem*					getDefaultImage(){return m_imageMap.at(0);}
	int							getImageCount(){return (int)m_imageMap.size();}
	ImageItem*					getImagePtr(int index){if(index < 0 || index >= (int)m_imageMap.size())return NULL; return m_imageMap.at(index);}
protected:
	std::vector<ImageItem*>		m_imageMap;
};

#endif
