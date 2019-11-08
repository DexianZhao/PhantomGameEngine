/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include <string>
#include "GCRenderSystem.h"
#include "GCLanguage.h"
#include "GCViewTreeBase.h"
#include "GCDefine.h"
#include "GCPropertyBase.h"
#include "MyMFCPropertyGridProperty.h"
#include "PhantomManager.h"
#include "PhantomScene3D.h"

enum FileViewerType{
	FileViewerType_Unknown	=	0,
	FileViewerType_GeometryEditor,	//ģ�ͱ༭����
	FileViewerType_Unit3D,	//��Ч�༭����
	FileViewerType_UI,				//����༭����
	FileViewerType_Texture,			//ͼƬ�༭����
	FileViewerType_Unit2D,			//2D����༭����
	FileViewerType_CursorEditor,	//���༭����
	FileViewerType_Scene,			//�����༭����
	FileViewerType_GameProject,		//��Ϸ�༭����
	FileViewerType_GCSceneEditor3D,	//3D�����༭����
	FileViewerType_LogicSystem,		//�߼����ݱ༭����
	FileViewerType_HomeViewer,		//�߼����ݱ༭����
	FileViewerType_Effect,			//��Ч�༭��
	FileViewerType_Lua,				//�ű����ı��༭��
};
enum FloatType
{
	FloatType_None	=	0,
	FloatType_Meter,
	FloatType_Angle,
};

typedef	INT	(*ProcGridOption)(const wchar_t* szText);

class CMyPropertyGridProperty: public CMFCPropertyGridProperty
{
public:
	inline	VOID		SetWndList(CMFCPropertyGridCtrl* s){m_pWndList = s;}
	inline	CMFCPropertyGridCtrl*	GetWndList(){return m_pWndList;}
};
typedef	CMFCPropertyGridProperty*		PropertyPtr;
typedef	CMFCPropertyGridColorProperty*	PropertyColorPtr;
typedef	CMFCPropertyGridMyFileProperty*	PropertyFilePtr;
typedef	MFCPropertyGridListProperty*	PropertyListPtr;
typedef	CMFCPropertyGridFontProperty*	PropertyFontPtr;
typedef	CMFCPropertyGridFloatProperty*	PropertyFloatPtr;
typedef	MFCPropertyGridListSelProperty*	PropertySelListPtr;

struct TreeItemType
{
	int				type;
	int				p1,p2,p3,p4,p5;
	int				id;
	wchar_t			path[256];
	TreeItemType()
	{
		type = p1 = p2 = p3 = p4 = p5 = id = 0;
		path[0]	=	0;
	}
};
class	GCViewBase;
struct	UndoRedoBuffer;
typedef	VOID	(*ProcUndoRedo)(GCViewBase* view, UndoRedoBuffer& buff, int urMode);

struct	UndoRedoBuffer
{
	enum URMode{
		URMode_None	=	0,
		URMode_Add,
		URMode_Undo,
		URMode_Redo,
	};
	int				type;	//����ʱ�������
	ProcUndoRedo	proc;//����
	void*			param;//����
	int				m_point;
	int				m_id;
	int				m_id2;
	int				m_id3;
	int				m_id4;
	int				m_undoIndex;
	int				m_bEnabled;
	Phantom::FloatAnimation*		m_oldAni[3];//ÿ�����3��floatani
	Phantom::FloatAnimation*		m_newAni[3];//ÿ�����3��floatani
	Phantom::FloatAnimation*		m_aniPtr[3];//ÿ�����3��floatani
	Phantom::CDynamicArray<char>	allocPtr;//���128�ֽڲ�����Ҫ���·����ڴ�
	//
	UndoRedoBuffer(){
		m_undoIndex	=	0;
		m_point		=	0;
		type		=	0;
		param		=	0;
		proc		=	0;
		m_id		=	0;
		m_id2		=	0;
		m_id3		=	0;
		m_id4		=	0;
		m_bEnabled	=	0;
		memset(m_oldAni, 0, sizeof(m_oldAni));
		memset(m_newAni, 0, sizeof(m_newAni));
		memset(m_aniPtr, 0, sizeof(m_aniPtr));
	}
	~UndoRedoBuffer()
	{
		for(int i=0;i<3;i++)
		{
			if(m_oldAni[i])
				delete m_oldAni[i];
			if(m_newAni[i])
				delete m_newAni[i];
		}
	}
	inline		void			write(const void* ptr, int length){
		int newlen = m_point + length;
		if(newlen>=allocPtr.size())
			allocPtr.resize(newlen);
		memcpy(allocPtr.GetPtr() + m_point, ptr, length);
		m_point			+=	length;
	}
	template	<class	_type>	inline	UndoRedoBuffer&	operator << (const _type& t){write(&t,sizeof(_type));return *this;}
	inline		void			reset(){m_point = 0;}
	inline		void			read(void* ptr, int length){
		if(m_point + length > allocPtr.size())return;
		memcpy(ptr, allocPtr.GetPtr() + m_point, length);
		m_point			+=	length;
	}
	template	<class	_type>	inline	UndoRedoBuffer&	operator >>(_type& t){read(&t,sizeof(_type));return *this;}
	//PropertyPtr		prop;
};

struct	UndoPtr{
	UndoRedoBuffer* buff;
	int				urMode;
};

class CPhantomGCDoc;
class CPhantomGCView;
class CChildFrame;
class GCViewBase: public IViewBaseCallback
{
public:
	GCViewBase(CPhantomGCDoc* docPtr, const wchar_t* szEditorMode, INT nImageListID);
	virtual	~GCViewBase(void);
	CPhantomGCDoc*		GetActiveDoc(){return m_docPtr;}
	CPhantomGCView*		GetActiveView();	//����Viewָ��
	CChildFrame*		GetActiveFrame();	//����Viewָ��
	VOID				SetActiveFrame(CChildFrame* f);
	virtual	HICON		GetViewerIcon() = 0;
	HWND				GetViewHandle();
	//
	virtual	BOOL		IsExistLua(){return false;}
	virtual	BOOL		IsLuaVisible(){return false;}
	virtual	VOID		ShowLuaVisible(BOOL b){}
	//
	virtual	VOID		OnCopyTree(){}
	virtual	VOID		OnPasteTree(){}
	virtual	BOOL		IsCopyTree(){return false;}
	virtual	BOOL		IsPasteTree(){return false;}
	//���Ų���
	virtual	VOID		PlayAnimation(){}
	virtual	VOID		StopAnimation(){}
	virtual	VOID		PauseAnimation(BOOL bPause){}
	virtual	VOID		SetAnimationLoop(BOOL bLoop){}
	//
	virtual	BOOL		IsAnimationCanPlayStop(){return false;}
	virtual	BOOL		IsAnimationCanPause(){return false;}
	virtual	BOOL		IsAnimationCanLoop(){return false;}
	//
	virtual	BOOL		IsAnimationPlaying(){return false;}
	virtual	BOOL		IsAnimationPause(){return false;}
	virtual	BOOL		IsAnimationLoop(){return false;}
	//
	virtual	VOID		OnDeleteTree(){}
	virtual	BOOL		IsDeleteTree(){return false;}//�Ƿ����ɾ������
	//
	virtual	VOID		AlignObjects(AlignType type, int value){}
	virtual	INT			GetAlignValue(AlignType type){return -1;}
	virtual	BOOL		IsAlignEnable(){return false;}//�Ƿ���Խ��ж���
	//�������пؼ�
	virtual	VOID		AlignRCObjects(const Phantom::Size& space, INT nCount, BOOL bVert, BOOL bIsRename = false, const wchar_t* szRename = L""){}
	//
	virtual	BOOL		IsCanHotkey();
	virtual	VOID		CloseFile();
	virtual	BOOL		OpenFile(const wchar_t* szFile);	//���ļ�,���ʧ������Զ�ɾ��
	virtual	BOOL		SaveFile(BOOL bSaveAs = FALSE);	//�����ļ�
	virtual	VOID		OnActive();		//������
	virtual	VOID		OnSetFocus(){}
	virtual	VOID		OnDeActive();	//ʧȥ����
	virtual	FileViewerType	GetViewerType()	=	0;
	virtual	INT			GetPopupMenuID(){return 0;}
	virtual	BOOL		OnDragDropFile(const wchar_t* szFile){return false;}	//���ⲿ�ļ����϶����������ڲ���ʱ������
	//
	virtual	Phantom::Scene3D*	GetStateScene(){return 0;}
	BOOL				IsShowUIGrid();
	VOID				ShowUIGrid(BOOL b);
	BOOL				m_bShowUIGrid;
	//
	virtual	int			GetEditorMode(){return -1;}
	virtual	VOID		SetEditorMode(int mode){}
	//
	virtual	BOOL		IsExportPak(){return false;}
	virtual	VOID		ExportPak(){}
	//
	virtual void		OnFrameMove(){}
	virtual void		OnRenderingBegin(){}	//��Ⱦ
	virtual void		OnRendering(){}	//��Ⱦ
	virtual void		OnPushRenderObjects(){}	//��Ⱦ
	virtual void		OnRenderingEnd(){}	//��Ⱦ
	virtual	void		OnRenderEndUI(){}	//������Ⱦ֮��
	virtual	bool		OnWindowProc(HWND hWnd, unsigned int uMsg, unsigned int wParam, unsigned int lParam){return true;}
	//
	void				OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp);
	VOID				OnChangeTreeSelect(CMTreeCtrl* treePtr, HTREEITEM hAddItem){}	//����ѡ�����οؼ�
	void				OnTreeViewKeyDown(INT nChar){}
	void				OnDoubleClick(CMTreeCtrl* treePtr, HTREEITEM hItem){}	//����ѡ�����οؼ�
	//
	virtual	VOID		SetModifyed(BOOL bModifyed = TRUE);	//�����޸�״̬
	BOOL				IsModifyed();
	const wchar_t*		GetFileViewName();
	GCViewTreeBase*		GetTreeView(){return &m_treeView;}
	VOID				InitProp(GCPropertyBase& p);
	VOID				InitPropWnd(CDialogEx* propWnd, UINT nDialogID);
	//
	VOID				UpdateMainTitle();
	virtual	VOID		GetNewFileName(wchar_t* szFile){}
	//
	//���һ��Ԫ������
	std::vector<TreeItemType>	m_treeItems;
	int					AddTreeItem(int type, int p1 = 0, int p2 = 0, int p3 = 0, int p4 = 0, int p5 = 0, const wchar_t* szText = 0);
	VOID				ClearTreeItem();
	TreeItemType*		GetTreeItem(int id);
	HTREEITEM			FindTreeItem(HTREEITEM hParent, int type, int p1 = 0, int p2 = 0, int p3 = 0, int p4 = 0, int p5 = 0);
	//
	BOOL				GetSortFile(std::wstring& ret, const wchar_t* szFile, BOOL bInFilePath = false);
	//
	VOID				SetPropInt(PropertyPtr p, int v);
	VOID				SetPropFloat(PropertyPtr p, float v);
	VOID				SetPropBool(PropertyPtr p, BOOL b);
	VOID				SetPropText(PropertyPtr p, const wchar_t* szText);
	VOID				SetPropText(PropertyPtr p, const char* szText);
	VOID				SetPropColor(PropertyColorPtr p, COLORREF v);
	//VOID				SetPropColor(PropertyColorPtr p, const color4& c);
	VOID				SetPropColor(PropertyColorPtr p, const Phantom::color4& c);
	VOID				SetPropFile(PropertyFilePtr p, const char* szFile);
	VOID				SetPropFile(PropertyFilePtr p, const wchar_t* szFile);
	//
	INT					GetPropInt(PropertyPtr p);
	float				GetPropFloat(PropertyPtr p);
	float*				GetPropFloatPtr(PropertyPtr p);
	BOOL				GetPropBool(PropertyPtr p);
	VOID				GetPropText(PropertyPtr p, std::wstring& ret);
	VOID				GetPropText(PropertyPtr p, std::string& ret);
	//
	VOID				GetPropFile(PropertyFilePtr p, std::wstring& ret, BOOL bInFilePath = false);
	//
	COLORREF			GetPropColor(PropertyColorPtr p);
	//VOID				GetPropFont(PropertyFontPtr p, FontNode2D& nRet);
	//VOID				SetPropFont(PropertyFontPtr p, const FontNode2D* node);
	VOID				SetPropFont(PropertyFontPtr p, INT nFontID);
	VOID				GetPropFont(PropertyFontPtr p, Phantom::FontNode2D& nRet);
	VOID				SetPropFont(PropertyFontPtr p, const Phantom::FontNode2D* node);
	//
	VOID				SetPropList(PropertyListPtr p, std::vector<std::wstring>& lists);
	VOID				GetPropList(PropertyListPtr p, std::vector<std::wstring>& lists);
	VOID				SetPropList(PropertySelListPtr p, std::vector<int>& lists);
	VOID				GetPropList(PropertySelListPtr p, std::vector<int>& lists);
	//
	INT					GetPropOption(PropertyPtr p, CTypeOption& opt);
	VOID				SetPropOption(PropertyPtr p, CTypeOption& opt, INT nIndex);
	//
	PropertyPtr			AddPropOption(const wchar_t* szName, const wchar_t* szDesc, CTypeOption& opt);
	PropertyListPtr		AddPropList(const wchar_t* szName, const wchar_t* szDesc);	//, BOOL bIsMultilineText = FALSE�����Ƿ�����ı�
	PropertyPtr			AddPropInt(const wchar_t* szName, const wchar_t* szDesc, INT nMin = INT_MIN, INT nMax = INT_MAX, INT nPage = 1);
	PropertyFloatPtr	AddPropFloat(const wchar_t* szName, const wchar_t* szDesc, int bFloatType = 0, float fMin = FLT_MIN, float fMax = FLT_MAX, float fPage = 0.1f);
	PropertyPtr			AddPropBool(const wchar_t* szName, const wchar_t* szDesc);
	PropertyPtr			AddPropText(const wchar_t* szName, const wchar_t* szDesc, BOOL bIsMultilineText = FALSE, INT nMaxTextLength = 100000);	//, BOOL bIsMultilineText = FALSE�����Ƿ�����ı�
	PropertyPtr			AddPropButton(const wchar_t* szName, const wchar_t* szDesc);
	PropertyColorPtr	AddPropColor(const wchar_t* szName, const wchar_t* szDesc);
	PropertyFontPtr		AddPropFont(const wchar_t* szName, const wchar_t* szDesc);
	PropertyFilePtr		AddPropFile(const wchar_t* szName, const wchar_t* szDesc, const wchar_t* szFilter, BOOL bMultiSelect = false);
	VOID				AddOptions(PropertyPtr p, std::vector<std::wstring>& texts);
	PropertySelListPtr	AddPropSelList(const wchar_t* szName, const wchar_t* szDesc);
	//
	virtual	void		OnUpdateUI(INT nMenuID, CCmdUI* pCmdUI) = 0;
	virtual	void		OnCommandUI(INT nMenuID) = 0;
	VOID				SelectTreeByType(INT type, HTREEITEM hItem);	//�������Ͷ�ѡ
	VOID				DeleteChildItems(HTREEITEM hItem);	//�������Ͷ�ѡ
	//
	virtual	BOOL		IsShowSelectOnly(){return m_bShowSelectOnly;}
	virtual	VOID		SetShowSelectOnly(BOOL b){m_bShowSelectOnly = b;}
	//
	TreeItemType*		GetSelectedItem();
	VOID				InitViewerProps();
	GCPropertyBase		m_viewerProps;
	PropertyPtr			m_viewerFile;
	PropertyPtr			m_viewerBrowser;
	BOOL				m_bShowSelectOnly;
	//
	VOID				BeginUndo(){m_undoIndex++;}
	UndoRedoBuffer*		AddUndoRedo(int type, ProcUndoRedo proc);
	UndoRedoBuffer*			m_currBuffer;
	UndoRedoBuffer::URMode	m_currMode;
	static GCViewBase*		s_currView;
	//
	virtual	VOID		BeginUndoFloat(Phantom::FloatAnimation* a1, Phantom::FloatAnimation* a2, Phantom::FloatAnimation* a3){}
	virtual	VOID		EndUndoFloat(Phantom::FloatAnimation* a1, Phantom::FloatAnimation* a2, Phantom::FloatAnimation* a3){}
	virtual	BOOL		IsCanUndo();
	virtual	BOOL		IsCanRedo();
	virtual	VOID		OnUndo();
	virtual	VOID		OnRedo();
	//
	VOID				AddPropertieWindow(CWnd* wnd);
	const wchar_t*		GetFileName(){return m_strFile.c_str();}
	inline	BOOL		IsReadOnly(){return m_bIsReadOnly;}
	HTREEITEM			m_hViewItem;
	//
	CMFCPropertyGridFloatProperty*	FindFloatPtr(CMFCPropertyGridProperty* g);
	CMFCPropertyGridIntProperty*	FindIntPtr(CMFCPropertyGridProperty* g);
protected:
	virtual	VOID		OnUndoRedo(UndoRedoBuffer* buffer, int ur_mode);
protected:
	BOOL				OnSelectTreeByType(INT type, HTREEITEM hItem);	//�������Ͷ�ѡ
	virtual	VOID		BuildFileViewText();
	//
	GCViewTreeBase		m_treeView;
	//
	std::map<PropertyPtr, int> m_floatMap;
	BOOL				m_bIsReadOnly;
	std::vector<CMFCPropertyGridFloatProperty*> m_floats;
	std::vector<CMFCPropertyGridIntProperty*>	m_ints;
	//
	std::vector<PropertyPtr>					m_grids;
	std::vector<UndoRedoBuffer*>		m_undos;
	std::vector<UndoRedoBuffer*>		m_redos;
	int					m_undoIndex;
protected:
	std::vector<CWnd*>	m_properties;
	std::vector<HWND>				m_propertyWnds;
	CChildFrame*		m_childFrame;
	std::wstring		m_strFile;
	std::wstring		m_strFileView;
	CPhantomGCDoc*		m_docPtr;
	Phantom::CameraDataLocal	m_savedCamera;
	std::wstring		m_szEditorMode;
};

void		SetCurrentProperties(GCPropertyBase* base, const wchar_t* szPropertyName, CDialogEx* dlgProp);
GCPropertyBase*	GetCurrentProperties();
void		SetCurrentPropertiesW(CDialogEx* base, const wchar_t* szPropertyName, CDialogEx* dlgProp);
extern		VOID	UsePhantom3D(BOOL b);

#define	ADD_UR(ptype,pold,pnew)	ptype temp,nnew,nold; UndoRedoBuffer& buff = *ptr->buff; buff.m_bEnabled=true; \
	if(ptr->urMode==UndoRedoBuffer::URMode_Add){ \
		nnew = pnew;nold = pold;buff << nold << nnew; temp = nnew;} \
	else if(ptr->urMode==UndoRedoBuffer::URMode_Undo){\
		buff >> nold >> nnew; temp = nold; }\
	else if(ptr->urMode==UndoRedoBuffer::URMode_Redo){\
		buff >> nold >> nnew; temp = nnew;}

#define	IF_ADD()	if(ptr->urMode==UndoRedoBuffer::URMode_Add)

