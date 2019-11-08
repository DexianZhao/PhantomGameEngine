#ifndef __PHANTOM_MAPBASE_H__
#define	__PHANTOM_MAPBASE_H__
#include "PhantomManager.h"

namespace Phantom{

#pragma pack(push, 1)
#define	MAX_ITEM_INMAP_SIZE			256//�������ռ�������������ᳬ�����������Ҳ����16x16����������С
struct	MapItemData
{
	int									id;
	Name								name;
	FileName							textureFile;
	Rect								textureRect;//ͼƬ����
	int									scale;//�����еĴ�С����,100=1������,0=��ʹ��
	int									gridCount;//ռ����������1��2��3��4��5��6//6=ռ6x6������
	Pixel								center;//���ĵ�����
	int									layer;//��Ӧ�Ĳ�
	int									type;//�Զ�������
	Size								offset;
	int									alignBottom;//����ͼ�½Ƕ���
	Pixel								door;//�ŵ�λ��
	BOOL								bDoorExist;//�Ƿ������
};
struct	MapGrid_2x1
{
	int									id;
	Name								name;
	FileName							textureFile;
	Rect								textureRect;//ͼƬ����
	int									layer;//��Ӧ�Ĳ�
	int									offsetX;//����
	int									type;//�Զ�������
	int									offsetY;//����
	int									drawMode;//��Ⱦģʽ
};

#pragma pack(pop)

#define	MAX_GRID_LAYER				3	//һ���������3����
struct	GridIndex
{
	short		x,y;
	inline	void		Set(short _x, short _y){x = _x; y = _y;}
	inline	bool		exist(){return (x>0&&y>0);}
	GridIndex(short _x, short _y){x = _x; y = _y;}
	GridIndex(){x = y = -1;}
};
class MapBase;
class	MapItem: public Base
{
public:
	ImplementComValue();
	MapItem();
	virtual ~MapItem(){}
	inline	const GridIndex&		GetGridInMap(){return m_inMap;}//�����ڵ�ͼ��������ĳ������λ��
	inline	int						GetGridCount(){return m_gridCount;}
	color4							m_color;
	int								m_projid;
	Rect							m_itemRect;
	PtrID							m_texID;//ͼƬ����
	Size							m_offset;
	BOOL							m_bEnabled;
	BOOL							m_bVisible;
	Name							m_name;
	int								m_alignBottom;
	//
	BOOL							m_bDoorExist;//�Ƿ������
	Pixel							m_door;
	Pixel							m_pos;
public://����̳еĺ���
	virtual	int						GetItemType() = 0;
	virtual	BOOL					FrameMove(const Pixel& pixel) = 0;//����Ҫ���㵱ǰҪ��Ⱦ�ľ���
	virtual	VOID					Render(){}	//��Ⱦ�����λ����,���ص�
	virtual	VOID					Save(CSafeFileHelperW& w){}
	virtual	VOID					Load(CSafeFileHelperR& r){}
	MapItem*						m_next;
protected:
	int								m_gridCount;
protected:
	GridIndex						m_inMap;//��һ�ε�λ��
	friend class MapBase;
	friend class Map2D_2x1;
};

#define	MAX_GRID_TEXTURE_LAYER		2
struct	MapGrid
{
	MapItem*						item[MAX_GRID_LAYER];
	MapItem*						units[MAX_GRID_LAYER];//��λ����
	int								data;
	enum GridState{
		GridState_Normal = 0,
		GridState_DisableMove,
	};
	GridIndex						state;//����״̬���Ƿ���ߵ�GridState
	struct	MapGridTexture
	{
		int							id;//����id
		Rect						textureRc;//ͼƬ����
		PtrID						texID;
		short						offsetX,offsetY;//100=1��
		short						drawMode;//0=���ж��룬1=���ϽǶ���
	};
	char							moveEnable;//�Ƿ�����ƶ���,-1���ɼ�����Ч
	int								pathIndex;//��̬����
	MapGridTexture					tex[MAX_GRID_TEXTURE_LAYER];
	//
	VOID							AddUnit(MapItem* item, int layer);
	BOOL							RemoveUnit(MapItem* item, int layer);
};

class	MapBase: public Base
{
public:
	MapBase();
	virtual ~MapBase();
	ImplementComValue();
	virtual	VOID					Create(Size& mapSize/*��ͼ���ش�С*/, Size& tiledCount/*��ͼ��������*/);	//����һ����ͼ
	virtual	VOID					Destroy();
	//������ܱ������򷵻�false��������nLayer�㼶��0����Ч��0�㼶��Ϊ���ر���������������Ƿ���Ч
	virtual	BOOL					SetGridItem(int nGridX, int nGridY, MapItem* item, int nLayer = 0);//����ĳ�����ӵĶ��󣬲㼶���3�㣬���������������µ�λ��������Զ�����һ�ε�λ����ɾ������������item��0���ԭ���Ķ���Ҳɾ��
	virtual	VOID					RemoveGridItem(MapItem* item);	//���������Ӹ��Ӷ�����ȥ��
	virtual	MapItem*				GetGridItem(int nGridX, int nGridY, int nLayer = 0);//����ĳ�����ԵĶ��󣬲㼶���3��
	//
	virtual	BOOL					SetUnit(int nGridX, int nGridY, MapItem* item, int nLayer = 0);//����ĳ�����ӵĶ��󣬲㼶���3�㣬���������������µ�λ��������Զ�����һ�ε�λ����ɾ������������item��0���ԭ���Ķ���Ҳɾ��
	virtual	VOID					RemoveUnit(MapItem* item);	//���������Ӹ��Ӷ�����ȥ��
	//
	virtual	VOID					SetGridTexture(int nGridX, int nGridY, int id, const PtrID* texID, const Rect* textureRect = 0, int offsetX = 0, int layer = 0, int offsetY = 0, int drawMode = 0);//����ĳ�����ӵ�ͼƬ,�����0���ȥ��ԭ����ͼƬ
	virtual	VOID					SetGridTexture(int nGridX, int nGridY, const MapGrid_2x1* m);//����ĳ�����ӵ�ͼƬ,�����0���ȥ��ԭ����ͼƬ
	int								GetGridTextureID(int nGridX, int nGridY, int layer = 0);//
	virtual	VOID					SetGridData(int nGridX, int nGridY, int data);//����ĳ�����ӵ��û�����
	virtual	INT						GetGridData(int nGridX, int nGridY);	//����ĳ�����ӵ��û�����
	virtual	VOID					SetCameraPos(const Pixel& center);	//��������ͷ
	const Pixel&					GetCameraPos(){return m_cameraPos;}	//��������ͷλ��
	inline	const Size&				GetMapPixelSize(){return m_mapPixelSize;}
	VOID							SetMapSize(int width, int height);
	VOID							SetOffsetAll(int x, int y);//ȫ������ƫ��
	inline	const Size&				GetTileCount(){return m_tileCount;}
	//inline	const Size&				GetBoxTile(){return m_tileCount;}//Size(m_tileCount.cx*2, m_tileCount.cy/2);}
	virtual	BOOL					IsItemCanInsert(int gridX, int gridY, MapItem* item){return true;}//�����λ���Ƿ���Լ������
	virtual	VOID					SetTileCount(const Size& size);//���ø�������
	//
	VOID							Save(const char* szFileName);
	BOOL							Load(const char* szFileName);//����
	virtual	BOOL					LoadR(CSafeFileHelperR& r);
	virtual	VOID					SaveW(CSafeFileHelperW& w);
	FileName						m_fileName;
	PtrID							GetTexture(const char* szFileName);
	Texture*						GetTexturePtr(PtrID& id);
	inline	int						GetNewID(){return (m_autoid++);}
public://����̳еĺ���
	virtual	VOID					RenderTexture(Texture* tex, const Rect& rc, const Pixel& pixel, const color4* c = 0, int offsetX = 0, int offsetY = 0) = 0;
	virtual	VOID					Render() = 0;//��Ⱦ
	virtual	MapItem*				CreateMapItem(int type) = 0;	//�������ʹ�������
protected:
	virtual	VOID					OnCreateMap(){};//������ͼ
protected:
	struct MapTextureData
	{
		int							id;
		FileName					file;
		Texture*					tex;
		MapTextureData(){tex = 0;}
	};
	int								m_autoid;
	CDynamicArray<MapTextureData>	m_textures;
	CDynamicArray<MapGrid>			m_mapGrids;
	//CDynamicArray<MapBoxTexture>	m_mapBoxTextures;
	Size							m_mapPixelSize;
	Size							m_tileCount;
	Pixel							m_cameraPos;
};

};

#endif
