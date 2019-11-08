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
#ifndef ___BASE_XMLFILEA__H___
#define ___BASE_XMLFILEA__H___



#pragma once
#include <string>
#include <vector>

#define	XML_LOAD_TYPE_HEAD	0

struct CXmlValueA//ASCII ��ʽXml�ļ���XmlԪ�ص���������
{
	std::string			name, value;
};

class CXmlElementA;

__interface	IXmlLoaderA//���û��ṩ�Ķ�ȡXml�ļ��Ļص��ӿ�
{
	void				onElementLoader(CXmlElementA& item, const char* szElement, int loadType, void* lpParameter);
};

class CXmlAttributeA//Xml���Բ�����,�����Ҫ�û���������
{
	void*				m_pAttr;
	CXmlAttributeA(void* ptr);
	friend class CXmlElementA;
public:
	bool				isXmlOK();
	//
	bool				next();
};

class CXmlElementA//XmlԪ�ع����࣬����<xml></xml>�����Զ�ȡ���ڲ���ֵ��Ҳ����д�뵽�ڲ�
{
public:
	//
	bool				isXmlOK();//����XmlԪ���Ƿ���Ч�����û��Ч���ʾ�������е�ͬ���Ƶ���Ԫ��
	//
	CXmlElementA		insert(const char* szItem);//����һ����Ԫ��
	//
	void				write(const char* szAttr, const char* szValue);//д����ı���һ�����ԣ�szAttr��������szValueֵ
	void				write_int(const char* szAttr,int n);//д��һ���������͵�����
	void				write_float(const char* szAttr,float n);//д��һ��������������
	//
	bool				read(const char* szAttr,std::string& _out);//��ȡһ���ַ���
	bool				read(const char* szAttr,int& _out);//��ȡһ������
	bool				read(const char* szAttr,float& _out);//��ȡһ�θ�����
	bool				read(const char* szAttr,double& _out);//
	bool				read(const char* szAttr,bool& _out);//
	const char*			read(const char* szAttr, const char* szDefault);//��ȡһ���ַ���
	//
	void				enumAttr(std::vector<CXmlValueA>& rets);//ö�����е�����ֵ
	void				freeEnum(std::vector<CXmlValueA>& rets);
	//
	void				loadElement(IXmlLoaderA* ptr, const char* szElementName, int loadType, void* lpParameter);//���ݽӿڶ�ȡͬ���Ƶ�����Ԫ�أ�ptr�û��̳еĽӿ�ָ�룬szElementNameԪ����������<xml><element></element><element></element>...</xml>��loadType,�û��Զ������ͣ���onElementLoader�н����жϣ�lpParameter�û��Զ���Ĳ���
	//
	CXmlElementA		first(const char* szItem);	//���ص�һ����Ԫ�ص�λ��
	CXmlElementA		first();	//���ص�һ����Ԫ�ص�λ��
	//
	CXmlAttributeA		firstAttr();
	//
	bool				next();//�ƶ�����һ����Ԫ��
	const char*			getItemName(){return m_szItemName;}
protected:
	CXmlElementA(void* ptr, const char* szItemName, bool bAll = false);
	//
	friend class		CXmlFileA;
	void*				m_pElement;
	char				m_szItemName[60];
	bool				m_bAllChildMode;
	//
};

void	readAttr(CXmlElementA& element, const char* szName, float& f);
void	readAttr(CXmlElementA& element, const char* szName, double& f);
void	readAttr(CXmlElementA& element, const char* szName, int& f);
void	readAttr(CXmlElementA& element, const char* szName, bool& f);
void	readAttr(CXmlElementA& element, const char* szName, std::string& f);

class CXmlFileA//Ansi��ʽ��Xml������
{
public:
	CXmlFileA(void);
	CXmlFileA(const char* szFile);//���ļ�����
	~CXmlFileA(void);
	//
	bool				loadFromMemory(const char* szText);//���ڴ��xml�ļ�
	bool				loadFromFile(const char* szFile);//���ļ���xml�ļ�
	//
	bool				isXmlOK();//�Ƿ���ʹ�ô�xml
	//
	CXmlElementA		first(const char* szItem);	//���ҵ�һ��Ԫ�ص�λ��
	//
	CXmlElementA		insert(const char* szItem);//�����һ��Ԫ��
	bool				saveXml(const char* szFile);//����һ��xmlԪ��
	//
protected:
	void*				m_pdocFile;
};

#endif
