/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include "PhantomManager.h"
class	CCodeClass;

class	CCodeMember
{
public:
	CCodeMember(){classPtr = 0; returnPtr = 0; funcPtr = 0; isEventIndex=-1;m_bIsModule=false;}
	//
	Phantom::NameW			name;
	Phantom::NameW			returnClass;	//��������
	int				isEventIndex;//�Ƿ��¼��󶨺���
	Phantom::NameW			eventName;
	Phantom::TextW	eventText;//�¼��ı�
	BOOL			IsExistEvent(){return isEventIndex>=0;}
public:
	BOOL			m_bIsModule;
	CCodeClass*		returnPtr;
	CCodeClass*		classPtr;
	CCodeMember*	funcPtr;
	Phantom::TextW	args;
	Phantom::TextW	description;
	virtual	BOOL	IsClassMember(){return false;}
	virtual	BOOL	IsEnumMember(){return false;}
	//
	enum CodeMemberType{
		CodeMemberType_Void	=	0,
		CodeMemberType_Variant,
		CodeMemberType_Class,
		CodeMemberType_Module,
		CodeMemberType_Struct,	//����
		CodeMemberType_Enum_Value,
		CodeMemberType_Enum,
		CodeMemberType_Event,
		CodeMemberType_Table,
		CodeMemberType_Keywords,
	};
	CodeMemberType	type;
};

class	CCodeClass: public CCodeMember
{
public:
	virtual	BOOL	IsClassMember(){return true;}
	CCodeClass();
	~CCodeClass();
	VOID		SearchReturnMembers();
	BOOL		IsEquip(CCodeClass& c);
	std::vector<CCodeMember*>				members;
	std::vector<CCodeClass*>				groups;
	CCodeMember*							FindMember(const wchar_t* szName);
	CCodeMember*							AddMember(const wchar_t* szName, const wchar_t* description, const wchar_t* returnClass, const wchar_t* args, CCodeMember::CodeMemberType type, BOOL bIsModule=false);
	VOID									SortMembers();
	virtual	BOOL	IsEnumMember(){return m_bIsEnum;}
public:
	BOOL		m_bIsLoad;//������������
	BOOL		m_bIsEnum;
};

class CCodeXmlManager
{
public:
	CCodeXmlManager(void);
	~CCodeXmlManager(void);
	VOID							LoadContent(CDynamicArray<char>& codeXml);
	VOID							ResetGameContent();
	CCodeClass*						FindClass(const wchar_t* szClass);
	BOOL							AddMyClass(CCodeClass* cc);
	CCodeMember*					FindMethod(const wchar_t* m);
	CCodeMember*					FindVariant(const wchar_t* m);
	//
	CCodeClass*						m_globalClass;
	//
	VOID							SortMembers();
	VOID							ResetBaseClass();
	VOID							ResetVariants();
	VOID							AddMyMethod(CCodeMember* m);
	CCodeMember*					AddMyVariant(const wchar_t* name);
	VOID							AddUIClass(const wchar_t* fileName);//���ݶԻ����ļ���ȡ������
	VOID							AddUIClass(Phantom::UIDialog* dlg);//���³�ʼ��ĳ���Ի���ı����б�,���Զ����浽�����ļ���
	VOID							UpdateUIClass(CCodeClass* classPtr, Phantom::UIDialog* dlg);//���³�ʼ��ĳ���Ի���ı����б�,���Զ����浽�����ļ���
	//
	std::vector<CCodeMember*>		m_methods;//ȫ�ֿ��Ա����õķ����ͱ���
	std::vector<CCodeMember*>		m_variants;
	std::vector<CCodeMember*>		m_savemethods;//ȫ�ֿ��Ա����õķ����ͱ���
	std::vector<CCodeMember*>		m_savevariants;
	std::vector<CCodeClass*>		m_uiclass;//UI�Ի�����,һ���Ի����Ӧһ����
	//
	std::vector<CCodeClass*>		m_saveClass;	//�����б�
	std::vector<CCodeClass*>		m_baseClass;	//�����б�
	std::vector<CCodeMember*>		m_dataTypes;
	//��Ϸ���
	CCodeClass*						m_globalGame;
	std::vector<CCodeClass*>		m_gameClass;	//��Ϸ��,����������
	std::vector<CCodeMember*>		m_gameMethods;	//��Ϸ����,�������ݺ���
	std::vector<CCodeMember*>		m_gameVariants;	//��Ϸ����,�������ݱ���
};

CCodeXmlManager*		GetCodeXmlManager();

