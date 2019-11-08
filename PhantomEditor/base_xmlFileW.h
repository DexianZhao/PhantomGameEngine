//////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	�ļ�       :   base.h
	�������   :   ��Ӱ��Ϸ���棨www.aixspace.com��

	��Ʊ�д�� :   �Ե���(Ӣ��:ZhaoDexian)
	Email: yuzhou_995@hotmail.com
	

	
	-------------------------------------------------------------------------------------------------


	-------------------------------------------------------------------------------------------------
	*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___BASE_XMLFILEW__H___
#define ___BASE_XMLFILEW__H___



#pragma once
#include <string>

class CXmlAttributeW//Xml���Բ�����,�����Ҫ�û���������
{
	void*				m_pAttr;
	CXmlAttributeW(void* ptr);
	friend class CXmlElementW;
public:
	bool				isXmlOK();
	//
	bool				next();
};

class CXmlElementW;

__interface	IXmlLoaderW//���û��ṩ�Ķ�ȡXml�ļ��Ľӿ�
{
	void				onElementLoader(CXmlElementW& item, const wchar_t* szElement, int loadType, void* lpParameter);
};

class CXmlElementW//XmlԪ�ع����࣬����<xml></xml>�����Զ�ȡ���ڲ���ֵ��Ҳ����д�뵽�ڲ�
{
	void*				m_pElement;
	wchar_t				m_szItemName[60];
	//
	CXmlElementW(void* ptr, const wchar_t* szItemName, bool bAll = false);
	bool				m_bAllChildMode;
	//
	friend class		CXmlFileW;
public:
	//
	bool				isXmlOK();//����XmlԪ���Ƿ���Ч�����û��Ч���ʾ�������е�ͬ���Ƶ���Ԫ��
	//
	CXmlElementW		insert(const wchar_t* szItem);//����һ����Ԫ��
	//
	void				write(const wchar_t* szAttr, const wchar_t* szValue);//д����ı���һ�����ԣ�szAttr��������szValueֵ
	void				write_int(const wchar_t* szAttr,int n);//д��һ���������͵�����
	void				write_float(const wchar_t* szAttr,float n);//д��һ��������������
	//
	bool				read(const wchar_t* szAttr,std::wstring& _out);//��ȡһ���ַ���
	bool				read(const wchar_t* szAttr,int& _out);//��ȡһ������
	bool				read(const wchar_t* szAttr,float& _out);//��ȡһ�θ�����
	const wchar_t*		read(const wchar_t* szAttr, const wchar_t* szDefault = L"");//��ȡһ���ַ���
	//
	void				loadElement(IXmlLoaderW* ptr, const wchar_t* szElementName, int loadType, void* lpParameter);//���ݽӿڶ�ȡͬ���Ƶ�����Ԫ�أ�ptr�û��̳еĽӿ�ָ�룬szElementNameԪ����������<xml><element></element><element></element>...</xml>��loadType,�û��Զ������ͣ���onElementLoader�н����жϣ�lpParameter�û��Զ���Ĳ���
	CXmlElementW		first(const wchar_t* szItem);	//���ص�һ����Ԫ�ص�λ��
	CXmlElementW		first();	//���ص�һ����Ԫ�ص�λ��
	//
	CXmlAttributeW			firstAttr();
	//
	bool				next();//�ƶ�����һ����Ԫ��
};

class CXmlFileW//Unicode��ʽ��Xml������
{
	void*				m_pdocFile;
public:
	CXmlFileW(void);
	CXmlFileW(const wchar_t* szFile);//���ļ�����
	~CXmlFileW(void);
	//
	bool				loadFromFile(const char* szFile);//���ڴ��xml�ļ�
	bool				loadFromMemory(const wchar_t* szText);//���ļ���xml�ļ�
	//
	bool				isXmlOK();//�Ƿ���ʹ�ô�xml
	//
	CXmlElementW		first(const wchar_t* szItem);	//���ҵ�һ��Ԫ�ص�λ��
	//
	CXmlElementW		insert(const wchar_t* szItem);//�����һ��Ԫ��
	bool				saveXml(const wchar_t* szFile);//����һ��xmlԪ��
	//
};

#endif
