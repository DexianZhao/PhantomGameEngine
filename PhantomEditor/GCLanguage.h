/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include "GCMFCHelper.h"

enum LanguagesType
{
	Languages_Current	=	0,
	Languages_Chiness,	//����
	Languages_English,	//Ӣ��
	Languages_Korean,	//����
	Languages_Japan,	//����
	Languages_Russia,	//����
	Languages_ChinessF,	//����
};

//ת���ɵ�ǰ��ָ���Ĺ�������
const wchar_t*	Language(const wchar_t* szID, const wchar_t* szDefault);
const wchar_t*	Language(const wchar_t* szIDAndDefault);
INT				GetLanguageFontSize(LanguagesType type = Languages_Current);
const char*		Language(const char* szID, const char* szDefault);

BOOL			IsChiness();

struct ConfigText
{
	std::wstring				id;
	std::wstring				value;
	VOID						Destroy()
	{
		id.clear();
		value.clear();
	}
	ConfigText(){}
	~ConfigText(){Destroy();}
};

class CIDEConfigFile
{
public:
	CIDEConfigFile(void);
	~CIDEConfigFile(void);
	//
	const wchar_t*				GetText(const wchar_t* szID, const wchar_t* szDefaultValue);	//����һ��������Ϣ
	VOID						SetText(const wchar_t* szID, const wchar_t* szDefaultValue);	//����һ��������Ϣ
	//
	VOID						SetChildsText(HWND hWnd);
	VOID						SetMenusText(HMENU hMenu);
	//
	VOID						SaveToFile();							//����ļ�����
	VOID						LoadFromFile();							//��ȡ�ļ�
	VOID						LoadDebug();							//��ȡ�ļ�
	VOID						ChangeLanguage(LanguagesType type);		//�л�����
	VOID						Destroy();
public:
	LanguagesType				m_language;
	std::string					m_configFile;
	bool						m_added;
	std::vector<ConfigText*>	m_texts;
};

wchar_t*			ConvertUnicodeAB(wchar_t* w);
CIDEConfigFile*		GetLanguagesPtr();
CIDEConfigFile*		GetLanguagesDebug();
