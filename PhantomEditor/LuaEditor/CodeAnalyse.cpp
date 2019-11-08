/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
// CodeEditor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CodeAnalyse.h"
bool isspace(wchar_t c){return (c == L' ' || c == L'\t');}
wchar_t s_codesymbol[] = {L' ',L'\t',L'+',L'-',L'*',L'/',L'\"',L'\\',L'*',L'%',L'^',L'#',L'=',L'~',L'!',L'<',L'>',L'(',L')',L'{',L'}',L'[',L']',L';',L':',L',',L'.',L'\r',L'\n',L'\'', L'\"', L'\r', L'\n', 0};
BOOL	issection(wchar_t c)
{
	int len	=	sizeof(s_codesymbol) / sizeof(wchar_t);
	for(int i=0;i<len;i++)
		if(c == s_codesymbol[i])
			return true;
	return false;
}


CCodeUndo::CCodeUndo()
{
	m_oldBegin = m_oldEnd = -1;
	m_oldLineBegin = m_oldLineEnd = -1;
	m_newBegin = m_newEnd = -1;
	m_newLineBegin = m_newLineEnd = -1;
}
CCodeUndo::~CCodeUndo()
{
	for(int i=0;i<m_newLineTexts.size();i++)
		delete m_newLineTexts[i].text;
	for(int i=0;i<m_oldLineTexts.size();i++)
		delete m_oldLineTexts[i].text;
}
VOID		CCodeUndo::Begin(CRichEditCtrl* rec)//��richedit����������Ҫ����
{
	for(int i=0;i<m_oldLineTexts.size();i++)
		delete m_oldLineTexts[i].text;
	m_oldLineTexts.clear();
	long b,e;
	rec->GetSel(b,e);
	m_oldBegin = b;
	m_oldEnd = e;
	m_oldLineBegin = rec->LineFromChar(m_oldBegin);
	m_oldLineEnd = rec->LineFromChar(m_oldEnd);
	int count = (m_oldLineEnd-m_oldLineBegin)+1;
	m_oldLineTexts.SetArrayCount(count);
	Phantom::CDynamicArray<wchar_t> buff;
	for(int i=0;i<count;i++){
		int line = i + m_oldLineBegin;
		int length = rec->LineLength(line);
		if(length<1024)length=1024;
		buff.SetArrayCount(length+1);
		length = rec->GetLine(line, buff.GetPtr(), length);
		if(rec->LineIndex(line+1)==-1&&length>0)length--;
		assert(length>=0);
		buff.GetPtr()[length] = 0;
		m_oldLineTexts[i].text = new wchar_t[length+1];
		m_oldLineTexts[i].lineBegin = line;
		memcpy(m_oldLineTexts[i].text, buff.GetPtr(), sizeof(wchar_t)*(length+1));
	}
}
VOID		CCodeUndo::End(CRichEditCtrl* rec)//������һ�������������
{
	for(int i=0;i<m_newLineTexts.size();i++)
		delete m_newLineTexts[i].text;
	m_newLineTexts.clear();
	long b,e;
	rec->GetSel(b,e);
	m_newBegin = b;
	m_newEnd = e;
	m_newLineBegin = rec->LineFromChar(m_newBegin);
	m_newLineEnd = rec->LineFromChar(m_newEnd);
	int count = (m_newLineEnd-m_newLineBegin)+1;
	m_newLineTexts.SetArrayCount(count);
	Phantom::CDynamicArray<wchar_t> buff;
	for(int i=0;i<count;i++){
		int line = i + m_newLineBegin;
		int length = rec->LineLength(line);
		if(length<1024)length=1024;
		buff.SetArrayCount(length+1);
		length = rec->GetLine(line, buff.GetPtr(), length);
		if(rec->LineIndex(line+1)==-1&&length>0)length--;
		assert(length>=0);
		buff.GetPtr()[length] = 0;
		m_newLineTexts[i].text = new wchar_t[length+1];
		m_newLineTexts[i].lineBegin = line;
		memcpy(m_newLineTexts[i].text, buff.GetPtr(), sizeof(wchar_t)*(length+1));
	}
}

MaskText::MaskText(const wchar_t* _name, MaskText::MaskType t)
{
	name = _name;
	type	=	t;
}
CCodeLine::CCodeLine(){
	m_bLocalVar	=	false;
	m_type		=	CL_Normal;//����
	m_class		=	0;
	m_member	=	0;
}
CCodeLine::~CCodeLine(){
	if(m_class)
		delete m_class;
	if(m_member)
		delete m_member;
	for(int i=0;i<m_args.size();i++)
		delete m_args[i];
	m_args.clear();
}
BOOL CCodeLine::GetSection(Phantom::CDynamicArray<MaskSection>& rets, Phantom::CDynamicArray<MaskSection>& fulls, wchar_t tbegin, wchar_t tend)//����tbegin��tend֮�������,�����������������tbegin���͵����ݣ������
{
	BOOL bAdd = false;
	for(int i=0;i<fulls.size();i++)
	{
		if(fulls[i].type==MaskSection::Section && fulls[i].name[0] == tbegin){
			bAdd = true;
		}
		else if(fulls[i].type==MaskSection::Section && fulls[i].name[0] == tend){
			return true;
		}
		else if(bAdd){
			rets.push_back(fulls[i]);
		}
	}
	return false;
}
VOID CCodeLine::RemoveSection(Phantom::CDynamicArray<MaskSection>& secs, wchar_t tbegin, wchar_t tend, int beginCaret)//�ڶ�����ɾ�����ж�Ӧ�ı�ʶ�����ݣ�����tbegin='(',tend=')'ɾ����������ݺͷ���
{
	int sec = 0;
	int beginS = -1;
	for(int i=0;i<secs.size();i++)
	{
		if((secs[i].begin+secs[i].count)<beginCaret)
		{
			continue;
		}
		if(beginS==-1)
			beginS = i;
		if(secs[i].type==MaskSection::Section){
			if(secs[i].name[0] == tbegin)
			{
				sec++;
			}
			else if(secs[i].name[0] == tend&&sec>0)
			{
				sec--;
				if(sec<=0)
				{
					secs.eraseByIndex(i);
					i--;
					continue;
				}
			}
		}
		if(sec>0){
			secs.eraseByIndex(i);
			i--;
		}
	}
	sec = 0;
	if(beginS>=secs.size())
		beginS = secs.size()-1;
	for(int i=beginS;i>=0;i--)
	{
		if(secs[i].type==MaskSection::Section){
			if(secs[i].name[0] == tend)
			{
				sec++;
			}
			else if(secs[i].name[0] == tbegin&&sec>0)
			{
				sec--;
				if(sec<=0)
				{
					secs.eraseByIndex(i);
					continue;
				}
			}
		}
		if(sec>0){
			secs.eraseByIndex(i);
		}
	}
}
VOID CCodeLine::SplitSection(Phantom::CDynamicArray<MaskSection>* fulls, const wchar_t* text, int length, Phantom::CDynamicArray<MaskSection>* nospace)
{
	int before = 0;
	for(int i=0;i<=length;i++){
		if(issection(text[i]))
		{
			if(text[i]==L'-'&&text[i+1]==L'-'){//�����ע����ȫ������
				MaskSection s;
				memset(&s, 0, sizeof(MaskSection));
				s.name = text+before;
				s.begin = before;
				s.count = length-before;
				if(s.count<32)s.name.t[s.count] = 0;
				s.type = MaskSection::Comment;
				if(fulls)fulls->push_back(s);
				if(nospace)nospace->push_back(s);
				break;
			}
			int len = i-before;
			if(len>0){
				MaskSection s;
				memset(&s, 0, sizeof(MaskSection));
				s.name = text+before;
				s.begin = before;
				s.count = len;
				if(s.count<32)s.name.t[s.count] = 0;
				if(fulls)fulls->push_back(s);
				if(nospace)nospace->push_back(s);
			}
			if(text[i]==L'\"'){
				before = i;
				i++;
				for(;i<length;i++){
					if(text[i]==L'\"')
					{
						i++;
						break;
					}
				}
				MaskSection s;
				memset(&s, 0, sizeof(MaskSection));
				s.name = text+before;
				s.begin = before;
				s.count = i-before;
				if(s.count<32)s.name.t[s.count] = 0;
				if(fulls)fulls->push_back(s);
				if(nospace)nospace->push_back(s);
				if(i==length){
					break;
				}
				before = i;
				i--;
				continue;
			}
			//if(text[i]>20){
			MaskSection s;
			memset(&s, 0, sizeof(MaskSection));
			s.name.t[0] = text[i];
			s.name.t[1] = 0;
			s.begin = i;
			s.count = 1;
			s.type = 1;
			BOOL bAdd = true;
			if(s.name[0]==L' ' || s.name[0]==L'\t' || s.name[0] == L'\r' || s.name[0] == L'\n')
				bAdd = false;
			if(!text[i])
				break;
			if(fulls)fulls->push_back(s);
			if(bAdd){
				if(nospace)nospace->push_back(s);
			}
			before = i+1;
		}
	}
}
BOOL CCodeLine::CommentClass(const wchar_t* text, int length, NameTW<256>& rets)
{
	Phantom::CDynamicArray<MaskSection> secs;
	SplitSection(0, text, length, &secs);
	if(secs.size()>=3){
		if(secs[0].name[0] == L'(' && secs[2].name[0]==L')'&&secs[1].type==MaskSection::Normal)
		{
			rets = secs[1].name;//������Ӧ����
			return true;
		}
	}
	return false;
}

VOID CCodeLine::CheckMyClass(const wchar_t* name)//��{}�д���һ���µ���
{
	Phantom::CDynamicArray<MaskSection> secs;
	GetSection(secs, m_codes, L'{', L'}');
	m_classname = name;
	m_class = new CCodeClass();
	m_class->name = name;//�����return����Ҫ���óɺ�����
	if(m_codes[m_codes.size()-1].type == MaskSection::Comment)
		m_class->description = (const wchar_t*)m_text + m_codes[m_codes.size()-1].begin + 2;
	for(int k=0;k<secs.size();k++)
	{
		if(secs[k].type==MaskSection::Section&&secs[k].name[0]==L'=')//����ǵȺ�
		{
			if(k>0&&k<(secs.size()-1))
				m_class->AddMember(secs[k-1].name, secs[k-1].name, secs[k+1].name, L"", CCodeMember::CodeMemberType_Variant);
		}
	}
	if(m_class->members.size()==0){
		delete m_class;
		m_class = 0;
	}
	else
		m_class->SortMembers();
}
BOOL CCodeLine::SectionClassList(Phantom::CDynamicArray<MaskSection>& secs, int begin, wchar_t* ret)//�Ӷ����б��з��������࣬����a.b.c:e().f�Ȼ᷵��a.b.c:e.f
{
	ret[0] = 0;
	for(int i=begin;i<secs.size();i++)
	{
		wchar_t w = secs[i].name[0];
		if(secs[i].type==MaskSection::Section&&!(w=='.'||w==':'))
		{
			if(secs[i].type==MaskSection::Section&&(secs[i].name[0]==L';'||secs[i].name[0]==L'+'||secs[i].name[0]==L'-'||secs[i].name[0]==L'*'||secs[i].name[0]==L'/'))
			{
				return true;
			}
			return false;
		}
		//if(!(w=='.'||w==':'))
		//	wcscat(ret, secs[i].name);
		//else
		wcscat(ret, secs[i].name);
		if(_wtoi(ret)!=0||ret[0]=='0')
			return false;
	}
	return false;
}
const wchar_t*	RequestArgs(const wchar_t* str)
{
	static CString temp;
	temp = str;
	temp.Replace(L"self,",L"");
	temp.Replace(L"self",L"");
	return temp;
}
VOID CCodeLine::SetText(const wchar_t* str)
{
	BOOL bSpace = false;
	m_text = str;
	const wchar_t* text = m_text;
	int length = m_text.GetLength();
	this->m_name.t[0] = 0;
	this->m_classname.t[0] = 0;
	m_bLocalVar = false;//���³�ʼ������
	if(m_class)
		delete m_class;
	m_class = 0;
	if(m_member)
		delete m_member;
	m_member = 0;
	for(int i=0;i<m_args.size();i++)
		delete m_args[i];
	m_args.clear();
	if(length==0)
		return;
	m_fulls.SetArrayCount(0);
	m_codes.SetArrayCount(0);
	Phantom::CDynamicArray<MaskSection> tempCodes;
	SplitSection(&m_fulls, m_text, length, &m_codes);
	tempCodes = m_codes;
	RemoveSection(m_codes, L'[', L']');
	RemoveSection(m_codes, L'(', L')');
	if(m_codes.size()>0){
		if(m_codes[0].name==L"function")
		{
			m_type = CCodeLine::CL_Function;
			if(m_codes.size()>1)
			{
				m_name = m_codes[1].name;
				m_member = new CCodeMember();
				m_member->name = m_name;
				m_member->type = CCodeMember::CodeMemberType_Void;
				m_member->args = RequestArgs(str);
				
				bool begin=false;
				CDynamicArray<NameW> args;
				for(int k=0;k<tempCodes.size();k++){
					if(tempCodes[k].type==MaskSection::Section&&tempCodes[k].name[0]==L'('){
						begin = true;
					}
					else if(begin){
						if(tempCodes[k].type==MaskSection::Section&&tempCodes[k].name[0]==L')')
							break;
						if(tempCodes[k].type==MaskSection::Section&&tempCodes[k].name[0]==L',')
							continue;
						Phantom::NameW n = tempCodes[k].name;
						args.push_back(n);
					}
				}
				if(m_fulls[m_fulls.size()-1].type==MaskSection::Comment){//�����ע����
					MaskSection& comment = m_fulls[m_fulls.size()-1];
					//CommentClass(text + comment.begin + 2, length - comment.begin - 2, m_classname);
					Phantom::CDynamicArray<MaskSection> secs;
					SplitSection(0, text + comment.begin + 2, length - comment.begin - 2, &secs);
					if(secs.size()>0&&secs[0].name[0] == L'(')// && secs[2].name[0]==L')'&&secs[1].type==MaskSection::Normal)
					{
						bool bReset = true;
						for(int k=1;k<secs.size();k++){
							if(secs[k].name[0]==L',')
							{
								bReset = true;
							}
							else if(bReset&&(k+1)<secs.size()){
								const wchar_t* name1 = secs[k].name;
								k++;
								if(secs[k].name[0]==L'=')//����ǵȺŲ�����������,�����Ǻ�������ֵ
								{
									k++;
									if(k>=secs.size())
										break;
									const wchar_t* class1 = secs[k].name;
									for(int m=0;m<args.size();m++){
										if(wcsicmp(name1, args[m]) == 0){//����������������������
											//
											CCodeMember* member = new CCodeMember();
											member->name = name1;
											member->type = CCodeMember::CodeMemberType_Variant;
											member->args = class1;
											member->returnClass = class1;
											member->returnPtr = GetCodeXmlManager()->FindClass(class1);
											m_args.push_back(member);
											break;
										}
									}
								}
								else
								{
									m_classname = name1;
									m_member->returnClass = name1;
									m_member->returnPtr = GetCodeXmlManager()->FindClass(name1);
								}
							}
							if(secs[k].name[0]==L')')
								break;
						}
					}
				}
				else
				{
				}
				m_member->returnClass =this->m_classname;
			}
		}
		else if(m_codes[0].name==L"if")
			m_type = CCodeLine::CL_If;
		else if(m_codes[0].name==L"elseif")
			m_type = CCodeLine::CL_ElseIf;
		else if(m_codes[0].name==L"else")
			m_type = CCodeLine::CL_Else;
		else if(m_codes[0].name==L"do")
			m_type = CCodeLine::CL_Do;
		else if(m_codes[0].name==L"end")
			m_type = CCodeLine::CL_End;
		else if(m_codes[0].name==L"for")
			m_type = CCodeLine::CL_For;
		else if(m_codes[0].name==L"return")
		{
			m_type		=	CCodeLine::CL_Return;
			if(m_codes.size()>1){
				if(m_codes[1].type==MaskSection::Normal)//�������������
				{
					wchar_t cname[256];
					if(SectionClassList(m_codes, 1, cname)){
						m_classname =	cname;
					}
				}
				else if(m_codes[1].type==MaskSection::Section&&m_codes[1].name[0]==L'{')//�������������
					CheckMyClass(L"");
			}
		}
		else
		{
			if(m_codes[0].name==L"local")
			{
				this->m_bLocalVar = true;
				m_codes.eraseByIndex(0);//ɾ��local
			}
			if(m_codes.size()>2 && m_codes[1].type==MaskSection::Section&&m_codes[1].name[0] == L'='){//����Ǹ�ֵ�������ʾֻ�б����ܱ���ֵ
				m_type = CL_VarSet;
				m_name = m_codes[0].name;
				if(m_codes[2].type==MaskSection::Section&&m_codes[2].name[0]==L'{'){//�������������
					CheckMyClass(m_name);
				}
				else{
					if(m_codes[2].type==MaskSection::Normal){
						wchar_t cname[256];
						if(SectionClassList(m_codes, 2, cname))
							m_classname =	cname;
						else{
							m_classname =	L"int";
							//m_type = this->CL_Normal;
							//return;
						}
					}
					if(m_fulls[m_fulls.size()-1].type==MaskSection::Comment){//�����ע����
						MaskSection& comment = m_fulls[m_fulls.size()-1];
						CommentClass(text + comment.begin + 2, length - comment.begin - 2, m_classname);
					}
				}
				//
				if(!m_bLocalVar){
					m_member = new CCodeMember();
					m_member->name = m_name;
					m_member->type = CCodeMember::CodeMemberType_Variant;
					m_member->args = str;
					if(wcsnicmp(m_classname.t, L"init_", 5)==0&&wcsstr(m_classname.t, L"_vars")){
						wchar_t tname[128];
						wcscpy(tname, m_classname.t + 5);
						int len = wcslen(tname);
						tname[len-5] = 0;
						GetCodeXmlManager()->AddUIClass(tname);
						m_classname = L"dlgs_";
						m_classname += tname;
					}
					m_member->returnClass = m_classname;
				}
			}
			else if(m_codes.size()>=2){
				if(m_codes[1].name[0]==L';')
				{
					m_type = CL_VarSet;
					m_name = m_codes[0].name;
					if(m_fulls[m_fulls.size()-1].type==MaskSection::Comment){//�����ע����
						MaskSection& comment = m_fulls[m_fulls.size()-1];
						CommentClass(text + comment.begin + 2, length - comment.begin - 2, m_classname);
					}
				}
			}
		}
	}
}
CCodeFunction::CCodeFunction(const wchar_t* name, long lineBegin)
{
	m_lineBegin	=	lineBegin;//������ʼλ��
	m_lineEnd	=	0;//��������λ��
	this->m_isEvent	=	0;
	this->m_name = name;
}
CCodeFunction::~CCodeFunction()
{
}
const MaskVariant*		CCodeFunction::SearchVar(const wchar_t* name)
{
	for(int i=0;i<m_vars.size();i++)
	{
		if(m_vars[i].name == name){//����Ǳ����������ñ���������
			return &m_vars[i];
		}
	}
	return 0;
}
VOID		CCodeFunction::SetReturn(const wchar_t* classname)//����ֵ
{
	m_classname = classname;
}
BOOL		CCodeFunction::AddVar(const wchar_t* name, const wchar_t* classname, long lineBegin, BOOL bLocal)
{
	for(int i=0;i<m_vars.size();i++)
	{
		if(m_vars[i].name == name)//��������¸�ֵ�򷵻����µ���������
		{
			if(!m_vars[i].classname[0])
				m_vars[i].classname = classname;
			//m_vars[i].classset=true;
			return true;
		}
	}
	if(!bLocal)
		return false;//������Ǳ��ر����򷵻�
	MaskVariant var;
	var.name = name;
	var.classset = false;
	var.classname = classname;
	var.lineBegin = lineBegin;
	var.isLocal = bLocal;
	m_vars.push_back(var);
	return true;
}
std::vector<CodeManager*>	g_codes;
CodeManager::CodeManager(){
	g_codes.push_back(this);
}
CodeManager::~CodeManager(){
	for(int i=0;i<m_lines.size();i++){
		delete m_lines[i];
	}
	for(int i=0;i<m_functions.size();i++)
		delete m_functions[i];
	for(int i=0;i<g_codes.size();i++){
		if(g_codes[i]==this){
			g_codes.erase(g_codes.begin()+i);
			break;
		}
	}
}
VOID		CodeManager::Reset()
{
	for(int i=0;i<m_lines.size();i++){
		delete m_lines[i];
	}
	for(int i=0;i<m_functions.size();i++)
		delete m_functions[i];
	m_lines.clear();
	m_functions.clear();
	m_variants.clear();
	m_events.clear();
}
int			CodeManager::LoopForEnd(int beginLine, CCodeFunction* fun)//��������п�ʼ�Ľ�������end��Ӧ
{
	int iline=beginLine;
	for(;iline<this->m_lines.size();iline++)
	{
		CCodeLine* line = m_lines[iline];
		switch(line->GetType()){
		case CCodeLine::CL_If:
		//case CCodeLine::CL_ElseIf:
		//case CCodeLine::CL_Else:
		case CCodeLine::CL_Do:
		case CCodeLine::CL_For://������������Ŀ�ʼ������Ҫ������������
			iline = LoopForEnd(iline+1, fun);
			iline--;
			break;
		case CCodeLine::CL_End:
			return iline;
		case CCodeLine::CL_VarSet:
			{
				if(line->HasName()&&line->HasClassName()){
					if(line->m_class)
						GetCodeXmlManager()->AddMyClass(line->m_class);
					BOOL bGlobal = true;
					if(fun)//����ں�����
					{
						if(fun->AddVar(line->m_name, line->m_classname, iline, line->IsLocalVar())){
							bGlobal = false;
						}
					}
					if(bGlobal){
						for(int k=0;k<m_variants.size();k++){
							if(m_variants[k].name == line->m_name)//���ȫ�ֱ�����������������������ó������
							{
								m_variants[k].classname = line->m_classname;
								bGlobal = false;
								break;
							}
						}
						if(bGlobal){//���ȫ�ֱ���������û������������Զ�����
							MaskVariant var;
							memset(&var, 0, sizeof(MaskVariant));
							var.name = line->m_name;
							var.classname = line->m_classname;
							var.lineBegin = iline;
							m_variants.push_back(var);
						}
					}
				}
			}
		}
	}
	return iline;
}

int	OnFunctionSort(const void* v1, const void* v2){
	CCodeFunction* m1 = (CCodeFunction*)v1;
	CCodeFunction* m2 = (CCodeFunction*)v2;
	return wcsicmp(m1->m_name, m2->m_name);
}
VOID		CodeManager::ClearAllLines()//���������д��룬�����ɺ�����ͱ�����,Reset��pushclass
{
	for(int i=0;i<m_functions.size();i++)
		delete m_functions[i];
	m_functions.clear();
	m_variants.SetArrayCount(0);
	for(int i=0;i<m_events.size();i++)
		m_events[i].bExist = false;
}
VOID		CodeManager::AnalyseAllLines()//���������д��룬�����ɺ�����ͱ�����
{
	CCodeFunction* fun = 0;
	for(int iline=0;iline<this->m_lines.size();iline++)
	{
		CCodeLine* line = m_lines[iline];
		Phantom::CDynamicArray<MaskSection>& codes = line->m_codes;
		switch(line->GetType()){
		case CCodeLine::CL_Function://����Ǻ�����ͷ
			{
				if(line->HasName())
				{
					if(line->m_member)
						GetCodeXmlManager()->AddMyMethod(line->m_member);
					if(fun)
					{
						this->m_functions.push_back(fun);
						fun->m_lineEnd = iline-1;
						//delete fun;
					}
					fun = new CCodeFunction(line->m_name, iline);
					if(line->HasClassName())
						fun->m_classname = line->m_classname;
					else
						fun->m_classname = line->m_name;
					//
					for(int k=0;k<line->m_args.size();k++){
						fun->AddVar(line->m_args[k]->name, line->m_args[k]->returnClass, iline, true);
					}
				}
			}
			break;
		case CCodeLine::CL_If:
		//case CCodeLine::CL_ElseIf:
		//case CCodeLine::CL_Else:
		case CCodeLine::CL_Do:
		case CCodeLine::CL_For://������������Ŀ�ʼ������Ҫ������������
			{
				iline = LoopForEnd(iline+1, fun);
				//iline++;
				//iline--;
			}
			break;
		case CCodeLine::CL_End://����������
			{
				if(fun){
					this->m_functions.push_back(fun);
					fun->m_lineEnd = iline+1;
				}
				fun = 0;
			}
			break;
		case CCodeLine::CL_Return:
			{
				if(fun&&fun->m_classname.t[0]){
					fun->SetReturn(fun->m_classname);
					line->m_classname = fun->m_classname;
					if(line->m_class)
					{
						for(int k=0;k<line->m_class->members.size();k++){
							if(line->m_class->members[k]->returnClass.t[0])//����Ƿ��������ں����������Ƿ������ֵ;
							{
								fun->SearchInVar(line->m_class->members[k]->returnClass, line->m_class->members[k]->returnClass, iline-1);
							}
						}
						line->m_class->name = fun->m_classname;
						GetCodeXmlManager()->AddMyClass(line->m_class);
					}
					if(m_lines[fun->m_lineBegin]->m_member)
					{
						m_lines[fun->m_lineBegin]->m_member->returnClass = line->m_classname;
						m_lines[fun->m_lineBegin]->m_member->returnPtr = GetCodeXmlManager()->FindClass(line->m_classname);
					}
				}
			}
			break;
		case CCodeLine::CL_VarSet:
			{
				if((line->HasName()&&line->HasClassName())||line->IsLocalVar()){
					if(line->m_class)
						GetCodeXmlManager()->AddMyClass(line->m_class);
					BOOL bGlobal = true;
					if(fun)//����ں�����
					{
						if(fun->AddVar(line->m_name, line->m_classname, iline, line->IsLocalVar())){
							bGlobal = false;
						}
					}
					if(bGlobal){
						for(int k=0;k<m_variants.size();k++){
							if(m_variants[k].name == line->m_name)//���ȫ�ֱ�����������������������ó������
							{
								m_variants[k].classname = line->m_classname;
								if(fun){
								for(int l=0;l<fun->m_vars.size();l++){
									if(fun->m_vars[l].name==m_variants[k].classname){
										m_variants[k].classname = fun->m_vars[l].classname;
									}
								}
								}
								bGlobal = false;
								break;
							}
						}
						if(bGlobal){//���ȫ�ֱ���������û������������Զ�����
							MaskVariant var;
							memset(&var, 0, sizeof(MaskVariant));
							var.name = line->m_name;
							var.classname = line->m_classname;
							var.lineBegin = iline;
							m_variants.push_back(var);
						}
					}
				}
			}
			break;
		}
	}
	if(fun)//���fun����ֵ�ͱ���ɾ��
		delete fun;
	//if(m_functions.size()>1)
	//	qsort(m_functions.GetPtr(), m_functions.size(), sizeof(CCodeFunction*), OnFunctionSort);
	for(int j=0;j<m_events.size();j++){
		m_events[j].bExist = false;
		for(int i=0;i<m_functions.size();i++){
			if(m_events[j].name==m_functions[i]->m_name){
				m_events[j].bExist = true;
				break;
			}
		}
	}
	for(int i=0;i<m_lines.size();i++){
		if(m_lines[i]->m_class){
			for(int j=0;j<m_lines[i]->m_class->members.size();j++){
				CCodeMember* m = m_lines[i]->m_class->members[j];
				if(m)
					m->funcPtr = 0;
				if(m&&m->returnClass.t[0]){
					CCodeMember* func = this->SearchFunction(m->returnClass);
					if(func){
						m->type=m->CodeMemberType_Void;
						m->funcPtr = func;
					}
				}
			}
		}
	}
}
CCodeMember*	CodeManager::SearchFunction(const wchar_t* func)
{
	for(int i=0;i<m_lines.size();i++){
		if(m_lines[i]->m_member&&m_lines[i]->m_member->name==func)
			return m_lines[i]->m_member;
	}
	return 0;
}
BOOL		CCodeFunction::SearchInVar(Phantom::NameW& ret, const wchar_t* var, int nLine)//��ȫ�ֱ�������
{
	for(int i=0;i<this->m_vars.size();i++)
	{
		if(m_vars[i].name == var&&m_vars[i].lineBegin<=nLine){
			ret = m_vars[i].classname;
			return true;
		}
		else if(m_vars[i].lineBegin>nLine)
			break;
	}
	return false;
}
CCodeFunction*		CodeManager::GetFunctionInLine(int line)
{
	for(int i=0;i<m_functions.size();i++){
		if(line>=m_functions[i]->m_lineBegin&&line<=m_functions[i]->m_lineEnd)
			return m_functions[i];
	}
	return 0;
}
BOOL		CodeManager::SearchInGlobalVar(Phantom::NameW& ret, const wchar_t* var, int nLine)//��ȫ�ֱ�������
{
	for(int i=0;i<this->m_variants.size();i++)
	{
		if(m_variants[i].name == var&&m_variants[i].lineBegin<=nLine){
			ret = m_variants[i].classname;
			return true;
		}
		else if(m_variants[i].lineBegin>nLine)
			break;
	}
	return false;
}
VOID		SplitClassName(Phantom::CDynamicArray<Phantom::NameW>& rets, const wchar_t* ch){
	int len = wcslen(ch);
	int begin = 0;
	for(int i=0;i<=len;i++){
		if(ch[i]==L'.'||ch[i]==L':'||ch[i]==0){
			NameW v;
			memset(&v, 0, sizeof(NameW));
			wcsncpy(v.t, ch+begin, i-begin);
			begin = i+1;
			rets.push_back(v);
		}
	}
}
BOOL			CodeManager::SplitAllCalls(std::vector<NameW>& fulls, NameW& first/*��һ������*/, const wchar_t* vars, int nLine)//��������ָ��
{
	NameW temp;
	NameW tempVar;
	CCodeFunction * fun = 0;
	CDynamicArray<NameW> lists;
	SplitClassName(lists, vars);//�и����еı�������
	if(lists.size()==0)
		return false;
	tempVar = lists[0].t;
	for(int i=1;i<lists.size();i++)
		fulls.push_back(lists[i]);
	for(int i=0;i<m_functions.size();i++)
	{
		if(nLine>=m_functions[i]->m_lineBegin&&nLine<=m_functions[i]->m_lineEnd){
			fun = m_functions[i];
			break;
		}
	}
	int listIndex = 0;
	nLine--;
	BOOL bGlobal = false;
	while(true){
		BOOL bOK = false;
		if(!bGlobal){
			bGlobal = true;
			if(SearchInGlobalVar(temp, tempVar, this->m_lines.size()))//ȫ�ֱ�����������
				bOK = true;
		}
		if(temp==tempVar)
			break;
		if(fun){
			if(fun->SearchInVar(temp, tempVar, nLine))//����������
				bOK = true;
		}
		nLine--;
		if(bOK)
		{
			CDynamicArray<NameW> newLists;
			SplitClassName(newLists, temp);//�и����еı�������
			if(newLists.size()>0){
				tempVar = newLists[0].t;//����Ѿ��������ˣ���ô�ظ��������ж��ǲ���Ҳ��һ������
				for(int i=(newLists.size()-1);i>0;i--)
					fulls.insert(fulls.begin(), newLists[i]);//�����ָ�����������б���һ���Ǳ�����֮��������
			}
			else
				break;
		}
		else
			break;
		if(nLine<0)break;
	}
	first = tempVar;
	return true;
}
BOOL	FindMethod(const wchar_t* m)
{
	for(int i=0;i<g_codes.size();i++){
		for(int j=0;j<g_codes[i]->m_functions.size();j++){
			if(g_codes[i]->m_functions[j]->m_name==m)
				return true;
		}
	}
	return false;
}
CCodeMember*	CodeManager::GetFunctionMemberPtr(const wchar_t* vars, int nLine)//����һ�������ķ���ָ��
{
	std::vector<NameW> fulls;
	NameW tempVar;
	if(!SplitAllCalls(fulls, tempVar, vars, nLine))
		return 0;
	if(fulls.size()==0){
		CCodeMember* m = GetCodeXmlManager()->FindMethod(tempVar);
		if(m)
			return m;
	}
	CCodeClass* c = GetCodeXmlManager()->FindClass(tempVar);
	if(!c)//�������������Ļ�����
	{
		CCodeMember* m = GetCodeXmlManager()->FindMethod(tempVar);
		if(m)
			c = m->returnPtr;
		if(!c)
		{
			m = GetCodeXmlManager()->FindVariant(tempVar);
			if(m)
				c = m->returnPtr;
			if(!c)
			{
				for(int j=0;j<g_codes.size();j++){
					if(g_codes[j]==this)
						continue;
					CCodeClass* temp = g_codes[j]->GetVariantClassPtr(tempVar, g_codes[j]->m_lines.size()-1, false);
					if(temp)
					{
						for(int i=0;i<fulls.size();i++){//��������������
							if(!temp)
								return 0;
							CCodeMember* m = temp->FindMember(fulls[i]);
							if(i==(fulls.size()-1))
								return m;
							if(!m)return 0;
							temp = m->returnPtr;
						}
					}
				}
				return 0;
			}
		}
	}
	for(int i=0;i<fulls.size();i++){//��������������
		CCodeMember* m = c->FindMember(fulls[i]);
		if(!m||!m->returnPtr||i==(fulls.size()-1))//��������Ҳ��������Ա����û�з����κ���Ļ�����
		{
			if(m&&m->funcPtr)
				return m->funcPtr;
			return m;
		}
		c = m->returnPtr;
	}
	return 0;
}
void			CodeManager::RefreshVariantList(int nLine)
{
	RefreshVariantListL(nLine);
	for(int j=0;j<g_codes.size();j++){
		if(g_codes[j]==this)
			continue;
		g_codes[j]->RefreshVariantListL(-1);
	}
}

void			CodeManager::RefreshVariantListL(int nLine)
{
	for(int i=0;i<m_variants.size();i++){
		CCodeMember* m = GetCodeXmlManager()->AddMyVariant(m_variants[i].name.t);
		m->type = CCodeMember::CodeMemberType_Class;
		m->description = m_variants[i].name.t;
	}
	CCodeFunction * fun = 0;
	for(int i=0;i<m_functions.size();i++)
	{
		if(nLine>=m_functions[i]->m_lineBegin&&nLine<=m_functions[i]->m_lineEnd){
			fun = m_functions[i];
			break;
		}
	}
	if(fun){
		for(int i=0;i<fun->m_vars.size();i++)
		{
			if(fun->m_vars[i].lineBegin<=nLine){
				CCodeMember* m = GetCodeXmlManager()->AddMyVariant(fun->m_vars[i].name.t);
				m->type = CCodeMember::CodeMemberType_Class;
				m->description = fun->m_vars[i].name.t;
			}
			else if(fun->m_vars[i].lineBegin>nLine)
				break;
		}
	}
}
CCodeClass*		CodeManager::GetVariantClassPtr(const wchar_t* vars, int nLine, BOOL bOther)//����һ������������
{
	std::vector<NameW> fulls;
	NameW tempVar;
	if(!SplitAllCalls(fulls, tempVar, vars, nLine))
		return 0;
	CCodeClass* c = GetCodeXmlManager()->FindClass(tempVar);
	if(!c)//�������������Ļ�����
	{
		CCodeMember* m = GetCodeXmlManager()->FindMethod(tempVar);
		if(m)
			c = m->returnPtr;
		if(!c)
		{
			m = GetCodeXmlManager()->FindVariant(tempVar);
			if(m)
				c = m->returnPtr;
			if(!c)
			{
				if(bOther){
					for(int j=0;j<g_codes.size();j++){
						if(g_codes[j]==this)
							continue;
						CCodeClass* temp = g_codes[j]->GetVariantClassPtr(tempVar, g_codes[j]->m_lines.size()-1, false);
						if(temp)
						{
							for(int i=0;i<fulls.size();i++){//��������������
								CCodeMember* m = temp->FindMember(fulls[i]);
								if(!m||!m->returnPtr)//��������Ҳ��������Ա����û�з����κ���Ļ�����
									return false;
								temp = m->returnPtr;
							}
							return temp;
						}
					}
				}
				return 0;
			}
		}
	}
	for(int i=0;i<fulls.size();i++){//��������������
		CCodeMember* m = c->FindMember(fulls[i]);
		if(!m||!m->returnPtr)//��������Ҳ��������Ա����û�з����κ���Ļ�����
			return false;
		c = m->returnPtr;
	}
	return c;
}
VOID		CodeManager::AddEvent(const wchar_t* w, const wchar_t* fulls, int type, int index)
{
	MaskEvent e;
	memset(&e, 0, sizeof(MaskEvent));
	e.name = w;
	e.fulls = fulls;
	e.type = type;
	e.index = index;
	this->m_events.push_back(e);
}

VOID		CodeManager::OnInsertLine(int lineIndex, const wchar_t* text)//�²���һ�е�����
{
	CCodeLine* cl = new CCodeLine();
	if(lineIndex<0||lineIndex>=m_lines.size())
		m_lines.push_back(cl);
	else
		m_lines.insert(m_lines.begin()+lineIndex, cl);
	cl->SetText(text);
}
VOID		CodeManager::OnRemoveLine(int lineIndex)//ɾ��һ��
{
	if(lineIndex<0||lineIndex>=m_lines.size())
		return;
	m_lines.erase(m_lines.begin()+lineIndex);
}


