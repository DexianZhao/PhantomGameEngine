/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include <vector>
#include <string>
#include <map>
#include "LuaXmlModule.h"
// CodeEditor
#pragma pack(push,1)
struct	MaskEvent{//�¼�
	Phantom::NameTW<32>	name;
	Phantom::NameTW<256>	fulls;
	char		bExist;//�Ƿ��������¼�
	int			type,index;
};

struct MaskSection{
	Phantom::NameTW<32>	name;//��󲻻ᳬ��function
	long		begin;
	long		count;
	enum MS{
		Normal = 0,//�����ı���������������
		Section = 1,//�Ƕ���
		Comment = 2,//��ע��
	};
	char		type;//0=����,1=section
//	MaskType	mask;//�ؼ�������
};
struct MaskVariant{
	Phantom::NameTW<32>		name;//�������ߺ�����
	Phantom::NameTW<256>	classname;//��Ӧ�����������ָ�������ı������ߺ���������ٷ�������
	char			classset;
	char			isLocal;//�Ƿ�local����
	long			lineBegin;
};
struct MaskText//ÿһ���ո���߶�����ֶ�
{
	enum MaskType
	{
		MaskType_None	=	0,
		MaskType_Keywords,		//�ؼ���
		MaskType_Token,	//����
		MaskType_Variant,
		MaskType_Method,
		MaskType_Text,
		MaskType_Comment,
		MaskType_Enum,
		MaskType_Number,	//����
		MaskType_PhantomAPI,//��ӰAPI����
		MaskType_LuaAPI,//lua��API����
		MaskType_Normal,//�����ı���ɫ
		MaskType_BackColor,//������ɫ
		MaskType_LineText,//���ı���ɫ
		MaskType_LineBack,//�б�����ɫ
		MaskType_Count,
	};
	Phantom::NameW		name;//����
	MaskType	type;
	MaskText(const wchar_t* _name = 0, MaskType t = MaskType_None);
	static COLORREF	Read(int mask, COLORREF c);
	static VOID		Write(int mask, COLORREF c);
};
class CCodeFunction{
public:
	CCodeFunction(const wchar_t* name, long lineBegin);
	~CCodeFunction();
	BOOL						AddVar(const wchar_t* name, const wchar_t* classname, long lineEnd, BOOL bLocal);
	VOID						SetReturn(const wchar_t* classname);//����ֵ
	const MaskVariant*			SearchVar(const wchar_t* name);
	BOOL						SearchInVar(NameW& ret, const wchar_t* var, int nLine);//�ӱ�������
public:
	char						m_isEvent;
	Phantom::NameTW<32>					m_name;//����
	Phantom::NameTW<256>					m_classname;
	long						m_lineBegin;//������ʼλ��
	long						m_lineEnd;//��������λ��
	Phantom::CDynamicArray<MaskVariant>	m_vars;
};
#pragma pack(pop)

struct	TextColor
{
	COLORREF	c;
	BOOL		bBold;
	TextColor(COLORREF cc = 0, BOOL b = false){c = cc; bBold = b;}
	VOID	Setup(COLORREF cc, BOOL b){c = cc; bBold = b;}
};
struct	LineText{
	int						lineBegin;
	wchar_t				*	text;
};
class CCodeUndo{
public:
	CCodeUndo();
	~CCodeUndo();
	VOID		Begin(CRichEditCtrl* rec);//��richedit����������Ҫ����
	VOID		End(CRichEditCtrl* rec);//������һ�������������
public:
	int			m_oldBegin;//�ɵ�ѡ��
	int			m_oldEnd;
	int			m_oldLineBegin;//�ɵ��п�ʼ
	int			m_oldLineEnd;//�ɵ��н���
	Phantom::CDynamicArray<LineText>		m_oldLineTexts;//�ɵ��������ı�����
public:
	int			m_newBegin;//�µ�ѡ��
	int			m_newEnd;
	int			m_newLineBegin;//�µ��п�ʼ
	int			m_newLineEnd;//�µ��н���
	Phantom::CDynamicArray<LineText>		m_newLineTexts;//�µ������и���
};

class CCodeLine{//�����ݣ�����ݱ༭���䶯
public:
	CCodeLine();
	~CCodeLine();
	enum CL{
		CL_Normal = 0,//������
		CL_VarSet,//������ֵ
		CL_If,//if����else
		CL_ElseIf,
		CL_Else,
		CL_Do,
		CL_End,
		CL_Function,
		CL_For,
		CL_Return,
		//CL_Until,
		//CL_While,
	};
	VOID						SetText(const wchar_t* str);//�����ı�,���Զ��ָ��ַ���
	inline	BOOL				IsLocalVar(){return m_bLocalVar;}//�Ƿ���local��ʽ�����˱���
	inline	CL					GetType(){return m_type;}
	inline	BOOL				HasName(){return m_name.t[0];}
	inline	BOOL				HasClassName(){return m_classname.t[0];}
	//
	static BOOL					CommentClass(const wchar_t* text, int length, Phantom::NameTW<256>& rets);
	static VOID					RemoveSection(Phantom::CDynamicArray<MaskSection>& secs, wchar_t tbegin, wchar_t tend, int beginCaret = 0);//�ڶ�����ɾ�����ж�Ӧ�ı�ʶ�����ݣ�����tbegin='(',tend=')'ɾ����������ݺͷ���
	static BOOL					GetSection(Phantom::CDynamicArray<MaskSection>& rets, Phantom::CDynamicArray<MaskSection>& fulls, wchar_t tbegin, wchar_t tend);//����tbegin��tend֮�������,�����������������tbegin���͵����ݣ������
	static VOID					SplitSection(Phantom::CDynamicArray<MaskSection>* fulls, const wchar_t* text, int length, Phantom::CDynamicArray<MaskSection>* codes = 0);
	static BOOL					SectionClassList(Phantom::CDynamicArray<MaskSection>& secs, int begin, wchar_t* ret);//�Ӷ����б��з��������࣬����a.b.c:e().f�Ȼ᷵��a.b.c:e.f
public:
	Phantom::CDynamicArray<MaskSection>	m_codes;//���䣬���벿��
	Phantom::CDynamicArray<MaskSection>	m_fulls;//���䣬���벿�֣������в���
	CString						m_text;//������ı�

	Phantom::NameTW<32>					m_name;//������,������
	Phantom::NameTW<256>					m_classname;//����
	CCodeClass*					m_class;//��������������������������,��xmlcode�в����Զ�ɾ������������Զ�ɾ��
	CCodeMember*				m_member;
	Phantom::CDynamicArray<CCodeMember*>	m_args;//�����б�
protected:
	VOID						CheckMyClass(const wchar_t* name);//��{}�д���һ���µ���
protected:
	bool						m_bLocalVar;
	CL							m_type;//����
	//line������richeditʼ�ն���Ӧ�ϣ�Ҫ��Ȼ���Ի����
};

class CodeManager{//���������
public:
	CodeManager();
	~CodeManager();
	VOID							ClearAllLines();//���������д��룬�����ɺ�����ͱ�����,Reset��pushclass
	VOID							AnalyseAllLines();//���������д��룬�����ɺ�����ͱ�����,Reset��pushclass
	VOID							AddEvent(const wchar_t* w, const wchar_t* fulls, int type, int index);
	CCodeLine*						GetLine(int lineIndex){if(lineIndex<0||lineIndex>=m_lines.size())return 0; return m_lines[lineIndex];}
	CCodeClass*						GetVariantClassPtr(const wchar_t* vars, int nLine, BOOL bOther=true);//����һ������������
	CCodeMember*					GetFunctionMemberPtr(const wchar_t* vars, int nLine);//����һ�������ķ���ָ��
	void							RefreshVariantList(int nLine);//���ص�ǰ���ڿ��Ե��õı����б�
	void							RefreshVariantListL(int nLine);//���ص�ǰ���ڿ��Ե��õı����б�
	//
	BOOL							SearchInGlobalVar(NameW& ret, const wchar_t* var, int nLine);//��ȫ�ֱ�������
	CCodeFunction*					GetFunctionInLine(int line);
	CCodeMember*					SearchFunction(const wchar_t* func);
	//
	VOID							Reset();
public://
	VOID							OnInsertLine(int lineIndex, const wchar_t* text);//�²���һ�е�����
	VOID							OnRemoveLine(int lineIndex);//ɾ��һ��
	BOOL							SplitAllCalls(std::vector<NameW>& rets, NameW& first/*��һ������*/, const wchar_t* vars, int nLine);//��������ָ��
public:
	std::vector<CCodeLine*>			m_lines;
	Phantom::CDynamicArray<CCodeFunction*>	m_functions;//���غ����б�����˳�����
	Phantom::CDynamicArray<MaskVariant>		m_variants;//ȫ�ֺ����б�,������ֻ��ȫ�ֱ��local�����û������local�ı�������ȫ�ֱ��д���
	Phantom::CDynamicArray<MaskEvent>		m_events;//���Ա���ӵ��¼��б�,���ⲿ����
protected:
	int								LoopForEnd(int beginLine, CCodeFunction* func);//��������п�ʼ�Ľ�������end��Ӧ
};
