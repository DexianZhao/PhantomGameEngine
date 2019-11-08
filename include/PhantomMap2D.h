#ifndef __PHANTOM_MAP2D_H__
#define	__PHANTOM_MAP2D_H__
#include "PhantomMapBase.h"
#include "PhantomUIManager.h"
#include "PhantomAStarPath.h"

namespace Phantom{

//class	PhantomMapCross2D: public MapBase//б�ǵĵ�ͼ,��׼2D��ͼ
//{
//public:
//	PhantomMapCross2D();
//	virtual ~PhantomMapCross2D();
//	VOID							SetGridSize(const Size& s);//���Ӵ�С����Ҫ����ͼƬ��С���趨
//public://����̳еĺ���
//	Pixel							PixelToTPixel(const Pixel& pixel);//�����ص�ת���ɵ�ͼ��Ⱦ�����
//	Pixel							TPixelToPixel(const Pixel& tilePixel);//����Ⱦ�����ת���������
//	virtual	VOID					RenderTexture(Texture* tex, const Rect& rc, const Pixel& pixel);
//	virtual	VOID					Render();//��Ⱦ
//	VOID							SetMapTexture(Texture* tex);	//���õ�ͼ����
//protected:
//	virtual	VOID					OnCreateMap();//������ͼ
//	float2							m_trot,m_rot;
//	Size							m_gridSize;	//���Ӵ�С
//	CDynamicArray<Pixel>			m_tilesIds;	//������Ⱦ˳��
//	Texture*					m_textureMap;//��ͼ����
//	Rect							m_mapRect;//��ͼ��������
//	Rect							m_renderRect;//��Ⱦ����
//};
#pragma pack(push,1)
struct PathPoint{
	short	gx,gy;
	enum pp_type{
		type_none = 0,
		type_enable = 1,
		type_door = 2,
	};
	short	type;
	unsigned short objid;
};
#pragma pack(pop)
struct MapItemData;
class	Map2D_2x1;
#define	ItemType_2x1	1
#define	ItemType_Unit	2
class	MapItem_2x1: public MapItem
{
public:
	MapItem_2x1(Map2D_2x1* m, const MapItemData* d);
	MapItem_2x1(Map2D_2x1* m, BOOL bPush = true);
	~MapItem_2x1();
	BOOL					FrameMove(const Pixel& pixel);//����Ҫ���㵱ǰҪ��Ⱦ�ľ���
	VOID					Render();	//��Ⱦ�����λ����,���ص�
	VOID					SetTexture(const PtrID& texID, const Rect& textureRect, const Pixel& center);
	int						GetItemType(){return ItemType_2x1;}
	VOID					Save(CSafeFileHelperW& w);
	VOID					Load(CSafeFileHelperR& r);
	BOOL					PickPixel(int pixelX, int pixelY);//���ؼ������������,������Ļ���ص�
	virtual	VOID			SetPos(const Pixel& pos);
	//
	VOID					AddEvent(int id, LPCSTR szFunc);
	//
	VOID					AddDrawMgr(UIDrawMgr* mgr);
	VOID					RenderAllMgrs();
	INT						m_bRenderMode;
	BOOL					m_bPush;
public:
	Pixel					m_centerPos;	//���ĵ�
	Rect					m_textureRc;
	int						m_scale;
	int						m_downScale;
	int						m_type;
	int						m_runtimeid;
public://runtime data
	Map2D_2x1*				m_mapPtr;
	std::vector<UILuaEvent>	m_events;
	std::vector<UIDrawMgr*> m_binds;
};
class	WayPoints;
struct	MapUnit_Data;



class	MapItem_Unit: public MapItem_2x1
{
public:
	MapItem_Unit(Map2D_2x1* m, MapUnit_Data* data);
	~MapItem_Unit();
	VOID					OnUnitFrameMove();//����Ҫ���㵱ǰҪ��Ⱦ�ľ���
	BOOL					FrameMove(const Pixel& pixel);//����Ҫ���㵱ǰҪ��Ⱦ�ľ���
	VOID					Render();	//��Ⱦ�����λ����,���ص�
	//
	virtual	VOID			SetPos(const Pixel& pos);
	VOID					SetActionByIndex(int index);//���Ŷ���
	VOID					SetActionByName(const char* action);//���Ŷ���
	VOID					SetAngleDir(const Pixel& dir);//����ת��
	VOID					SetAngle(float a);
	BOOL					AddMoveTo(int mapx, int mapy);//�Զ�Ѱ·������ͼĿ���
	BOOL					AddMoveTo(int mapx, int mapy, LPCSTR szFunc);//�Զ�Ѱ·������ͼĿ��㣬������
	VOID					AddStandTo(float fTime);//��Ӿ�ֹ
	int						GetItemType(){return ItemType_Unit;}
	LPCSTR					GetActionName();
public:
	GridIndex				m_last;
	float					m_fSpeed;
	float					m_fActionSpeed;
	int						m_currentAction;
	float					m_currentAni;
	int						m_currentAngle;
	Pixel					m_currentDir;
	CDynamicArray<WayPoint2D>	m_ways;
	Name					m_moveEndFunc;//�ƶ�����֮����
	float					m_fPlayLength;
	int						m_nPlayIndex;
	MapUnit_Data*			m_unitPtr;
};

struct	MapUnitAction
{
	FileName				textureFile;
	int						w,h;
	Name					name;//��������
	struct TexIndex{
		short	begin,end;
		void				set(short _b, short _e){begin = _b; end = _e;}
	};
	TexIndex				ani[Unit2DAngle_Count];//x=begin,y=end
	PtrID					texid;
	Pixel					center;//���ĵ�����
};
struct	MapUnit_Data
{
	int							id;
	Name						name;
	int							type;//�Զ�������
	int							layer;//��Ӧ��
	CDynamicArray<MapUnitAction>	actions;
	int							action_move;
	int							action_stand;
};

struct	MapTexture
{
	Texture*		tex;
	Rect			destRect;
	Rect			textureRect;
};
struct PathIndex{
	short x,y;
};

class Map2DAstar: public AstarCallback
{
public:
	virtual	int				IsAstarMoveEnable(int x, int y);
	virtual	int				GetAstarWidth();
	virtual	int				GetAstarHeight();
	Map2D_2x1*				m_mapPtr;
};

//�¼���
class	Map2D_Event: public Base
{
public:
	Map2D_Event(Map2D_2x1* ptr);
	~Map2D_Event();
	VOID						SetPos(const Pixel& pos);
public:
	int							m_id;
	Name						m_name;
	int							m_type;
	GridIndex					m_grid;
	Pixel						m_pos;//λ��
	Map2D_2x1*					m_mapPtr;
	//CDynamicArray<EventInvoke>	m_invokes;
};

class Map2D_2x1: public MapBase//б�Ƿǹ���ֲ�
{
public:
	Map2D_2x1();
	virtual ~Map2D_2x1();
	inline	Size&					GetGridSize(){return m_gridSize;}
	VOID							SetGridSize(const Size& s);//���Ӵ�С����Ҫ����ͼƬ��С���趨
	virtual	VOID					Destroy();
public://����̳еĺ���
	Pixel							GetPixelGridCenter(int gridX, int gridY);
	Pixel							GetMapGridCenter(int gridX, int gridY);
	virtual	VOID					RenderTexture(Texture* tex, const Rect& rc, const Pixel& pixel, const color4* c = 0, int offsetX = 0, int offsetY = 0);
	virtual	VOID					RenderTexture2(Texture* tex, const Rect& rc, const Pixel& pixel, const color4* c = 0, int offsetX = 0, int offsetY = 0, int drawMode = 0);
	virtual	VOID					Render();//��Ⱦ
	VOID							AddMap(Texture* tex);	//���õ�ͼ����
	VOID							RemoveMap(int nIndex);//ɾ��һ��ͼƬ
	VOID							SetMapRect(int nIndex, const Rect& renderRect, const Rect& textureRect);//��Ⱦλ��
	//
	//const MapGrid_2x1*				GetGrid_2x1(int nGridX, int nGridY, int layer = 0);//
	const MapItemData*				GetGrid_Item(int nGridX, int nGridY, int layer = 0);//
	//Size							GetBoxSize(){return Size(m_gridSize.cx, m_gridSize.cy);}
	//
	VOID							SetAllMove(INT bMove);
	VOID							SetTextureAllMove(MapGrid_2x1& t, INT bMove);
	inline	const MapTexture*		GetMap(int nIndex){if(nIndex < 0 || nIndex >= m_textureMaps.size())return 0; return &m_textureMaps[nIndex];}
	inline	int						GetMapCount(){return m_textureMaps.size();}
	//
	const Size&						GetTextureExtend(){return m_textureExtend;}
	VOID							SetTextureExtend(const Size& s){m_textureExtend = s;}
	BOOL							IsItemIn(int pixelX, int pixelY, GridIndex& itemGrid, MapItem* item);//�����Ƿ񱻵��
	//BOOL							PickBox(GridIndex& ret, int pixelX, int pixelY);//�������,��ǰ��Ļ����λ�ÿ�ʼ����
	BOOL							PickGrid(GridIndex& ret, int pixelX, int pixelY);//�������,��ǰ��Ļ����λ�ÿ�ʼ����
	MapItem*						PickItem(int pixelX, int pixelY, int layer = 0);//��������ڵĵ��ζ���,��ǰ��Ļ����λ�ÿ�ʼ����
	MapItem*						PickItemPixel(int pixelX, int pixelY, int layer = 0);//��������ڵĵ��ζ���,��ǰ��Ļ����λ�ÿ�ʼ����
	BOOL							GetGridInMapPoint(GridIndex& ret, int x, int y);//�������ο�ʼ�㿪ʼ����
	//
	VOID							MapToWindow(Rect& windowRect, const Rect& mapRect);
	VOID							WindowToMap(Rect& mapRect, const Rect& windowRect);
	MapItem_Unit*					AddUnit(int unitid, const GridIndex& g);//����һ����ɫ
	MapItem_Unit*					AddUnit(LPCSTR szUnitName, const GridIndex& g);//����һ����ɫ
	VOID							DeleteUnit(MapItem_Unit* unit);//����һ����ɫ
	VOID							DeleteFromUnitID(int unitid);//ɾ�����ж�Ӧ�Ľ�ɫ
	//
	VOID							RecalcGridStates();//���¼������еĿ��߸�����Ϣ
	BOOL							IsItemCanInsert(int gridX, int gridY, MapItem* item);
	VOID							RenderDrawGrid(int gridX, int gridY, MapItem* item, const color4* color);
	VOID							RenderOneGrid(int gridX, int gridY, const color4* color);
	VOID							SetWhiteTexture(const char* szWhiteTexture);
	const Pixel&					GetMapOffset(){return m_mapOffset;}
	VOID							SetMapOffset(const Pixel& p){m_mapOffset = p;}
	//
	const Rect&						GetRenderRect(){return m_renderRect;}
	//
	VOID							RemoveAllItems();
	VOID							CommitAllItems(const MapItemData* data);//ˢ�����еĶ������ݵı仯
	int								GetCreateCount(int id);
	Name							m_funcClick;
	//Ѱ·����
	VOID							SetPathAlign(const GridIndex& g);//���ÿ��ƶ����ӳ�ʼ����λ��
	VOID							SetGridMoveEnable(int gridx, int gridy, int state);//���ÿ��߸�������
	INT								GetGridMoveEnable(int gridx, int gridy);
	BOOL							PathFromGrid(PathIndex& ret, const GridIndex& g);
	BOOL							PathFromPixel(PathIndex& ret, int pixelX, int pixelY);
	BOOL							PathFromMap(PathIndex& ret, int mapX, int mapY);
	Pixel							MapPointFromPixel(const Pixel& p){return Pixel(p.x+m_renderRect.left,p.y+m_renderRect.top);}
	//
	BOOL							FindPath(CDynamicArray<WayPoint2D>& ways, const Pixel& mapFrom, const Pixel& mapTo);
	BOOL							GridFromPath(GridIndex& ret, const PathIndex& p);
	VOID							SetPathSize(int w,int h);//���ÿ��ƶ����Ӵ�С
	VOID							RecalcMoveStates();
	Size							m_pathSize;
	CDynamicArray<PathPoint>		m_pathPoints;//���ƶ���������
	GridIndex						m_pathalign;
	//
	Map2D_Event*					AddEvent(const char* name, const Pixel& mapPos);//
	VOID							RemovePoint(Map2D_Event* e);
	Map2D_Event*					SearchEvent(const char* name);
	CDynamicArray<Map2D_Event*>		m_events;
public:
	BOOL							m_bShowFloor;//��ʾ�ذ�
	BOOL							m_bShowBuilding;//��ʾ������
	BOOL							m_bShowBackTexture;//��ʾ����ͼƬ
	BOOL							m_bShowUnits;
	BOOL							m_bWhiteGrid;//�Ƿ���Ⱦ��ɫ����
	BOOL							m_bWhiteCanMove;//�Ƿ���ʾ���߸���
	color4							m_colorWhiteGrid;//�װ���ɫ
	//
	CDynamicArray<MapItemData>		m_projItems;//���󷽰��б�
	CDynamicArray<MapGrid_2x1>		m_projGrids;//����ͼƬ����
	CDynamicArray<MapUnit_Data*>	m_projUnits;//��λ�����б�
	MapItem_2x1*					m_downItem;
	AStarPath						m_astar;
	Map2DAstar						m_astarcb;
public:
	virtual	BOOL					LoadR(CSafeFileHelperR& r);
	virtual	VOID					SaveW(CSafeFileHelperW& w);
	virtual	MapItem*				CreateMapItem(int type);	//�������ʹ�������
	//
	VOID							PushItem(MapItem_2x1* item);
	VOID							PopItem(MapItem_2x1* item);
	CDynamicArray<MapItem_2x1*>		m_items;
	CDynamicArray<MapItem_Unit*>	m_units;
protected:
	virtual	VOID					OnCreateMap();//������ͼ
	Size							m_gridSize;	//���Ӵ�С
	CDynamicArray<MapTexture>		m_textureMaps;//��ͼ����
	Texture*						m_textureWhite;//��ͼ����
	Pixel							m_mapOffset;//��ͼ��������
	Rect							m_renderRect;//��Ⱦ����
	Size							m_textureExtend;
	friend class					MapItem_2x1;
	friend class					MapItem_Unit;
};

class	MyMap2D: public Map2D_2x1
{
public:
	MyMap2D();
	~MyMap2D();
	virtual	BOOL			OnInputEvent(Phantom::InputEventID evt, int x, int y, unsigned int touchIndex);
	virtual	VOID			OnRender(double dElapsedTime);
	BOOL					m_bVisible;
	BOOL					m_bEnableMove;
	BOOL					m_bIsButtonDown;
	BOOL					m_bMouseMove;
	Pixel					m_downPos;
public:
};

};

#endif
