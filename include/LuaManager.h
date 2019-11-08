#ifndef __LUA_MANAGER_H__
#define	__LUA_MANAGER_H__
#include "PhantomManager.h"
#include "PhantomEffect.h"
#include "PhantomAction.h"
#include "PhantomHttp.h"

extern "C"
{
	#include "lua/lua.h"
	#include "lua/lualib.h"
	#include "lua/lauxlib.h"
};
#include "lua/lua_tinker.h"

namespace Phantom{


class GameState;
class CLuaFile;
class CLuaFile
{
public:
	CLuaFile();
	~CLuaFile();
	BOOL					Load(FileName& f);//���ļ�����
	BOOL					Load(const char* szText, FileName& f);//���ļ�����
	BOOL					LoadText(const char* szText, int len);//���ı�����
	char					isExcuted;
protected:
	friend class			CLuaFileMgr;
	std::string				m_script;
	FileName				m_file;
};

struct LuaDefine
{
	Name					name;
	std::string				text;
};

class	CLuaCallback: public Base
{
public:
	ImplementComValue();
	virtual	const char*		OnCall(Name& methods, LPCSTR* params, int numParams) = 0;//��lua�ڲ������Զ��庯�������������ȫ�������ַ�������
};

struct	LuaCreat
{
	int					fileIndex;
	PtrID				id;
};
struct	LuaTimeData
{
	enum TimeType{
		TT_Timeout	=	0,
		TT_Interval =	1,
		TT_FrameMove=	2,
	};
	char				type;
	int					id;
	char				pause;
	Name				name;
	NameT<32>			params;
	double				dTime;
	double				dInitTime;//
	double				dMaxInterval;
	double				dMaxIntervalSave;
	double				dCurrentTime;
	//
	unsigned char		id_type;
	unsigned char		id_t;
	INT					id_ptr;
	INT					id_idx;
	enum{
		IDT_Global		=	0,//���κζ����ȫ��
		IDT_GameID		=	1,//��Ϸ����ID,GameObject
		IDT_Control		=	2,
		IDT_Group		=	3,
		IDT_Dialog		=	4,
	};
	VOID				Init(TimeType _type, int _id, const char* _name, int millisecond, int nMaxInterval = -1, const char* params = 0, unsigned char _idtype = 0, unsigned char _idt = 0, int _idptr = 0, int _ididx = 0);
};

class LuaAction;
struct ActionVal
{
	float4				next;
	double				dTime;
	int					loop;
	int					currentloop;
};
class LuaAction: public Base
{
public:
	LuaAction();
	~LuaAction();
	VOID				OnFrameMove(double dElapsedTime);
	VOID				AddNext(const float4& end, float fTimeLength, int loopCount);
	BOOL				m_bEnabled;
	double				m_dLastTime;
public:
	CDynamicArray<ActionVal>	m_vals;
	int					m_currentIndex;
	double				m_dTime;
	Name				m_luaFunc;
};
class CLuaState{
public:
	lua_State*			m_luaState;
};

class CLuaFileMgr: public RenderNodeManager
{
public:
	CLuaFileMgr();
	~CLuaFileMgr();
	VOID				Destroy();//�������е�lua�趨,�������µ���Create
	BOOL				Create(BOOL bUsePhantomSystem, BOOL bDebugMode);	//��ʼ���нű�ϵͳ���������³�ʼ��
	BOOL				callFile(const char* szMainFile);	//����ĳ���ļ�
	BOOL				call(const char* szLuaCode, const char* szFile);	//���ô���
	VOID				SetCallback(CLuaCallback* cb);
	inline	lua_State*	GetLuaState(){return m_luaState;}
	//
	int					GetFileIndex(const char* file);
	const char*			GetFileName(int index);
	//
	BOOL				loadAndExecute(const char* szLuaCode, const char* szFile);	//��ӽű�����,�ļ������Բ��ǽű�
	//
	VOID				OnJsonAnalyse(JsonObject& obj);
	VOID				OnJsonAnalyseFail(const char* type, const char* szFailText);
	VOID				Push(const PtrID& id);
	VOID				Push(const SoundID& id);
	VOID				Pop(const PtrID& id);
	VOID				Pop(const SoundID& id);
	VOID				Push(LuaAction*a);
	VOID				Pop(LuaAction*a);
	//
	INT					AddTimeout(int millisecond, const char* name, const char* params = 0, unsigned char _idtype = 0, unsigned char _idt = 0, int _idptr = 0, int _ididx = 0);
	INT					AddInterval(int millisecond, int nMaxMillisecond, const char* name, const char* params = 0, unsigned char _idtype = 0, unsigned char _idt = 0, int _idptr = 0, int _ididx = 0);
	INT					AddFramemove(int nMaxMillisecond, const char* name, const char* params = 0, unsigned char _idtype = 0, unsigned char _idt = 0, int _idptr = 0, int _ididx = 0);
	VOID				ClearTime(const char* name, const char* params);
	VOID				ClearTime(int id);
	VOID				ClearTimeAll(){m_times.SetArrayCount(0);}
	VOID				BreakTime();
	VOID				PauseTime(BOOL bPause);
	//
	VOID				OnFrameMove(double dElapsedTime, double dRealElapsedTime);
	VOID				OnRender(float dElapsedTime);
	//����¼�
	VOID				OnInputEvent(Phantom::InputEventID btn, int x, int y, unsigned int touchIndex);
	VOID				OnInputSize(Pixel centerPos, float fSize, int nBegin);
	Name				m_downFunc;
	Name				m_upFunc;
	Name				m_moveFunc;
	Name				m_mainName;
	Name				m_doubleDownFunc;
	Name				m_doubleMoveFunc;
	Name				m_doubleUpFunc;
	BOOL				m_bDoubleDown;
	BOOL				m_bOneDown;
	float				m_dblDownLength;
	CDynamicArray<LuaAction*>	m_actions;
	CLuaCallback*		m_callback;

	HttpRequest			m_http;
	struct LuaBindName{
		int				id;
		Name			name;
	};
	CDynamicArray<LuaBindName>	m_luaBindIDs;
	JsonObject*			m_luaJson;
	JsonObject			m_luaSend;
	int					m_lastTouchIndex;
	GameState*			m_memvals;
	Name				m_funcRender;
protected:
	int					m_currentTime;
	lua_State*			m_luaState;
	friend class CLuaFile;
	VOID				AddMacroText(const char* szName, const char* szText);	//��Ӻ����
	CLuaFile*			Load(const char* szFile);//����ļ�������ֱ�ӷ���true�������ظ�����ͬһ���ļ�
	CDynamicArray<LuaDefine*>	m_defines;//lua��
	CDynamicArray<CLuaFile*>	m_files;//lua�ļ��б�
	CDynamicArray<CLuaFile*>	m_runlist;//�����б�
	CDynamicArray<LuaCreat>		m_creats;
	CDynamicArray<LuaTimeData>	m_times;
	int							m_timeID;
};
extern	CLuaFileMgr		g_luamanager;
}
extern	void	SetCurrentLuaFileIndex(int n);

#endif
