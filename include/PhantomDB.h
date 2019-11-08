
#ifndef __PHANTOM_DB_H__
#define	__PHANTOM_DB_H__
#include "sqlite3.h"
#include "PhantomBase.h"
#include "PhantomFile.h"

namespace Phantom{
	class	Config;
	struct	ConfigHeader
	{
		Name		name;
		NameT<32>	type_s;
		Text		desc;//˵��
		unsigned short	listcount;//�������������Ч�����鳤��
		Config*		classPtr;//�����class����Ҫ�����
		VOID		SetName(const char* n);
		VOID		ResetType();
		enum type_num{
			type_int	=	1,
			type_float	=	2,
			type_text	=	3,//
			type_class	=	4,//�������е�ĳ����
			type_boolean=	5,
		};
		int		type;
		ConfigHeader(){
			classPtr = 0;
			type = 0;
			listcount = 0;
		}
		~ConfigHeader(){
			desc.clear();
		}
	};
#pragma pack(push,1)
	struct	ConfigVal{
		float		fval;
		int			ival;
		char*		text;//�ı�ָ��
		ConfigVal*	list;//�����������������count-1������
		//
		const char*	getText();
		void		setText(const char* t);
		void		freeText();
		void	operator = (const ConfigVal& v);
		ConfigVal(){fval = 0; ival = 0; text = 0; list = 0;}
		~ConfigVal();
	};
#pragma pack(pop)

	const char*			ReadText(CFileHelperR& r, char* buf);
	struct DBColumn
	{
		DBColumn(const char* szName){name = szName; index = -1;}
		Name		name;
		int			index;
	};

	class	Sqlite3
	{
	public:
		Sqlite3();
		virtual ~Sqlite3();
	public:
		BOOL			OpenDB(const char* szFile);		//�����ݿ��ļ�
		VOID			CloseDB();
		sqlite3_stmt*	Select(const char* szExec);	//ѡ��һ�����ݿ�����
		BOOL			MoveNext(sqlite3_stmt* stmt);//�������true��ʾ���Լ���ѭ��
		INT				ReadInt(sqlite3_stmt* stmt, DBColumn& col);
		double			ReadDouble(sqlite3_stmt* stmt, DBColumn& col);
		const char*		ReadText(sqlite3_stmt* stmt, DBColumn& col);
		VOID			Execute(const char* szExec, BOOL bTransMode = TRUE/*���Transmode��ʹ��һ���Դ������*/);//ִ�в�����������
	protected:
		BOOL			InitColumn(sqlite3_stmt* stmt, DBColumn& col);//�Զ���ʼ����
		BOOL			ExecuteDB(const char* szExec);
	protected:
		sqlite3*	m_sqlite;
	};

	struct	ID
	{
		unsigned int id;
		int index;
		ID(){id = 0; index = -1;}
	};
	template <typename type>
	class DBManager
	{
	public:
		DBManager(){}
		~DBManager(){}
		inline	int			size(){return m_list.size();}
		inline	type&		operator[](int index){return m_list[index];}
		type*				operator[](ID& id)
		{
			if(id.index == -2)//��������Ҳ���
				return 0;
			if(id.index >= 0 && id.index < m_list.size() && id.id == m_list[id.index].id)
				return &m_list[id.index];
			for(int i=0;i<m_list.size();i++)
			{
				if(m_list[i].id == id.id)
				{
					id.index = i;
					return &m_list[i];
				}
			}
			id.index = -2;
			return 0;
		}
		type*				Find(unsigned int id)//����ID����
		{
			for(int i=0;i<m_list.size();i++)
			{
				if(m_list[i].id == id)
					return &m_list[i];
			}
			return 0;
		}
		unsigned int		Insert(type& t)//�½�һ��������ID
		{
			int idMax = 0;
			for(int i=0;i<m_list.size();i++)
			{
				idMax = getmax(idMax, m_list[i].id);
			}
			t.id = idMax;
			m_list.push_back(&t);
			//OnInsert(t);
			return idMax;
		}
		BOOL				Remove(unsigned int id)//�½�һ��������ID
		{
			for(int i=0;i<m_list.size();i++)
			{
				if(m_list[i].id == id)
				{
					m_list.eraseByIndex(i);
					//OnRemove(id);
					return true;
				}
			}
			return false;
		}
	//protected:
	//	virtual	void		OnInsert(type& t) = 0;
	//	virtual	void		OnRemove(unsigned int id) = 0;
		CDynamicArray<type>	m_list;
	};
#pragma pack(push, 1)
	struct	StateValue
	{
		char			isNumber;//
		double			value;
		char*			ptr;
		void			setText(const char* t);
		const char*		getText();
		void			freeText();
		//
		StateValue();
		~StateValue();
	};
	struct	NameState: StateValue
	{
		NameT<31>		name;//���15�������ı�,���һ����0
	};
#pragma pack(pop)
	struct	GenuineGUID;
	class GameState: public Base
	{
	public:
		GameState();
		~GameState();
		const char*					readt(const char* name, const char* szDefault = "");
		double						readf(const char* name, double dDefault = 0);
		int							readi(const char* name, int nDefault = 0);
		void						write(const char* name, const char* text);
		void						writef(const char* name, double d);
		void						writei(const char* name, int n);
		//
		int							find(const char* name);
		//
		const char*					lreadt(int index, const char* szDefault = "");
		double						lreadf(int index, double dDefault = 0);
		int							lreadi(int index, int nDefault = 0);
		void						lwritet(int index, const char* text);
		void						lwritef(int index, double d);
		void						lwritei(int index, int n);
		void						SetArrayCount(int cnt);
		//
		GameState*					addChild(const char* name);//�����������Ҳ������Զ�����
		GameState*					searchChild(const char* name);//��������
		void						removeChild(GameState* s);
		void						removeChild(const char* name);
		VOID						Destroy();
		VOID						initState(const char* szFile);
		void						OnChanged();
		//
		void						save(streamWrite& w);
		bool						load(streamRead& r);
		void						save(LPCSTR szFile, GenuineGUID* guid);
		bool						load(LPCSTR szFile, GenuineGUID* guid);
	public:
		char							m_bCanSave;//�Ƿ���Ա�����
		NameT<32>						m_name;
		CDynamicArrayS<GameState*,5>	m_childs;//����
		CDynamicArrayS<NameState,5>		m_states;
		CDynamicArrayS<StateValue,1>	m_arrays;
		//
		static NameT<32>&				GetTemp();
	};
	VOID							reloadState();
    VOID							saveStateNow();
	GameState*						GetStateMgr();//
	void							initState(const char* szFile, unsigned int* guid, int length);//guid���ڼ���
	void							saveState(const char* szFile);//guid���ڼ���
	bool							loadState(const char* szFile);
	void							EncryptData(CDynamicArray<char>& rets, const char* ptr, int length);
	char*							DecryptData(char* inptr, int length, int& realsize);
	//

	class	ConfigMgr;
	class	Config;
	class	ScriptBase;
	class	ConfigLine{
	public:
		ConfigLine();
		virtual ~ConfigLine();
		//���index>0������������������������������ӵ�һ�����ݻ��
		int						GetIntVal(int col, int index = 0);
		void					SetIntVal(int col, int val, int index = 0);
		float					GetDoubleVal(int col, int index = 0);
		void					SetDoubleVal(int col, float val, int index = 0);
		const char*				GetTextVal(int col, int index = 0);
		void					SetTextVal(int col, const char* text, int index = 0);

		int						GetIntVal(GameID& id, const char* name);
		float					GetDoubleVal(GameID& id, const char* name);
		const char*				GetTextVal(GameID& id, const char* name);
		ConfigLine*				GetOtherLinePtr(GameID& id, const char* name);//�����ָ����������,�����������Ӧ����,û���򷵻�0
		BOOL					SearchID(GameID& id, const char* name);

		ConfigLine*				GetOtherLinePtr(int col, int index = 0);//�����ָ����������,�����������Ӧ����,û���򷵻�0
		VOID					SetOtherLinePtr(int col, ConfigLine* line, int index = 0);
		VOID					SetOtherLineID(int col, int otherid, int index = 0);
		int						GetOtherLineID(int col, int index = 0);//����id
		//
		inline	bool			GetVal(int col, int index, bool& b){return (GetIntVal(col, index)!=0);}
		inline	int				GetVal(int col, int index, int& b){return GetIntVal(col, index);}
		inline	float			GetVal(int col, int index, float& b){return (float)GetDoubleVal(col, index);}
		inline	const char*		GetVal(int col, int index, const char*& b){return GetTextVal(col, index);}
		inline	ConfigLine*		GetVal(int col, int index, ConfigLine*& b){return GetOtherLinePtr(col, index);}
		inline	void			SetVal(int col, int index, bool& b){SetIntVal(col, b?1:0, index);}
		inline	void			SetVal(int col, int index, int& b){SetIntVal(col, b, index);}
		inline	void			SetVal(int col, int index, float& b){SetDoubleVal(col, b, index);}
		inline	void			SetVal(int col, int index, const char*& b){SetTextVal(col, b, index);}
		inline	void			SetVal(int col, int index, ConfigLine*& b){SetOtherLinePtr(col, b, index);}
		//
		VOID					Setup(Config* c);
		int						SearchCol(const char* columnName);
		const char*				GetTableName();
		const char*				GetLineName();
		VOID					SetLineName(const char* name);
		int						GetLineID();
		VOID					SetLineID(int id);
		inline	const GameID&	GetID(){return m_id;}
		Config*					GetConfigPtr(){return m_config;}
		ConfigLine*				Clone(ConfigMgr* mgr);//��¡һ��
		inline	int				GetLineIndex(){return m_index;}
		inline	ScriptBase*		GetScriptPtr(){return m_script;}
	protected:
		friend class			Config;
		friend class			ConfigMgr;
		friend class			GameMgr;
		GameID					m_id;
		int						m_index;
		ConfigVal*				m_data;//������
		Config*					m_config;
		ScriptBase*				m_script;//��Ӧ�Ľű�ָ��,������ڽű��Ļ�
	};
	class	Config
	{
	public:
		Config();
		~Config();
		int						GetLineCount();
		ConfigLine*				GetLine(int lineIndex);
		int						SearchCol(const char* columnName);
		const char*				GetTableName();
		BOOL					IsExistLine(int id);//�Ƿ�������ID
		ConfigLine*				GetLineFromID(int id);//����lineindex
		inline	int				GetNumCol(){return m_numCol;}
		inline	ConfigHeader*	GetCol(int col){if(col<0||col>=m_numCol)return 0;return &m_cols[col];}
		inline	int				GetConfigIndex(){return m_index;}
		Name					m_tableName;//�������
		//
		VOID					RebuildListIndexs();
		int						GetArrayCol(int listIndex);//�������������е�������
		int						GetArrayCount(){return m_arrayCount;}
	protected://��һ���϶���id,�ڶ����϶���name
		friend class			ConfigMgr;
		friend class			ConfigLine;
		friend class			GameMgr;
		BOOL					Load(ConfigMgr* mgr, const char* szFileName);
		int						m_id;
		int						m_index;
		ConfigHeader*			m_cols;//��ͷ����
		unsigned short*			m_arrayIndex;//���������б�
		unsigned short			m_arrayCount;//����������һ������е�����������ܳ���10��
		ConfigLine*				m_lines;//������,i,f
		int						m_numLine,m_numCol;
	};
#define	MAX_CONFIG_FILE			20//���֧��20�������ļ�+һ��role_table
	class	ConfigMgr
	{
	public:
		ConfigMgr();
		~ConfigMgr();
		Config*						SearchConfig(const char* szTableName);//�������
		Config*						GetConfigPtr(PtrID& id, const char* szTableName);
		BOOL						ResearchAllFiles();//�����ļ��е����б����������
		VOID						Destroy();
		//
		VOID						RegisterAllLuaClass();//ע������lua�����б�,ÿ�γ�ʼ���ű�����Ҫ����һ��,���֧��52�����Ķ����luaע��
		ConfigLine*					SearchLine(GameID& id);
		ConfigLine*					SearchLineC(const GameID& id);
		//
		GameID						GetLineOther(GameID& id, int col, int index = 0);//��������е�ָ����
		VOID						SetLineOther(GameID& id, int col, GameID& otherID, int index = 0);
		VOID						SetLineOtherC(GameID& id, int col, const GameID& otherID, int index = 0);
		//
		inline Config*				GetRoleTable(){return m_tblRoles;}
		inline	int					GetNewIdentity(){return m_id++;}
		VOID						OnDeleteLine(ConfigLine* l);
	public:
		CDynamicArray<Config*>		m_configLua;
		enum{
			Table_AI = 0,
			Table_Scene = 1,
			Table_City = 2,
			Table_Mission = 3,
			Table_Skill = 4,
		};
	protected:
		CDynamicArray<Config*>		m_configs;//�����ļ��б�û�г�ʼ��
		CDynamicArray<ConfigLine*>	m_lines;//����������,�����̶��кͶ�̬��
		//
		friend class				Config;
		int							m_id;
	public:
		Config*						m_tblRoles;//��ɫ���
		Config*						m_tblAI;//AI���
		Config*						m_tblScene;//�����б�
		Config*						m_tblCity;//�����б�
		Config*						m_tblMission;//�����б�
		Config*						m_tblSkill;//�����б�
		Config*						m_tblLeader;//�����趨���
		Config*						m_tblText;//�ı��б�
		Config*						m_tblSceneUnit;//������λ
		char						m_colTextDesc;//�ı��б�˵��
	};
	void						enum_files(const char* path,CDynamicArray<FileName>& _out, int subFolderLevel, NameT<16>* szFindType,int numFindTypes);
};

#endif
