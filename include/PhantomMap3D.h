#ifndef __PHANTOM_MAP3D_H__
#define	__PHANTOM_MAP3D_H__
#include "PhantomMapBase.h"
#include "PhantomUIManager.h"
#include "PhantomAStarPath.h"

#define	MAP3D_REGION_GRIDs		32	//ÿһ������̶���������

namespace Phantom{
	enum 
	{
		TileProp_HIDE		= 0x00000001, //����
		TileProp_BLOCK		= 0x00000002, //�Ƿ����
		TileProp_TEXROT0	= 0x00000040, 
		TileProp_TEXROT1	= 0x00000080, 
		TileProp_TEXROT2	= 0x00000100, 
		TileProp_TEXROT3	= 0x00000200, // ת��
		TileProp_TEXINV		= 0x00000400, // ��תͼƬ
		TileProp_REST_STAND = 0x00000800,
		TileProp_REST_SIT	= 0x00001000,
		TileProp_SAFEZONE	= 0x00002000,
		TileProp_PLAYERKILL = 0x00004000,
		TileProp_FIGHTZONE	= 0x00008000
	};
#pragma pack(push,1)

	struct	MapTile
	{
		unsigned int	attr;//������
		unsigned char	texID;//ͼƬID
	};
	struct	MapObjectData
	{
		int				id;
		int				objID;
		int				type;
		int				subtype;
		float3			pos;
		int				rot;//angle
	};

	struct	MapTrigger//������
	{
		int				id;
		Name			name;
		Rect			rect;//��������
	};
#pragma pack(pop)
	class Map3DQuadBox;
	class CMapObject: public RenderBase
	{
	public:
		CMapObject();
		~CMapObject();
		virtual	void				Render();
		virtual	void				drawObject(const matrix4x4* matPtr = 0);
		virtual	void				drawObjectShadow(const matrix4x4* matPtr = 0){}
		virtual	char				IsAffectByShadowMap(){return false;}
		virtual	void				drawToShadowMap(const matrix4x4* matPtr, Program* vsps, int nDrawState = RenderNode_SetState){}
		virtual	const matrix4x4&	GetWorldMatrix(){return m_mat;}
		VOID						onChange();
		VOID						FrameMove();
		BOOL						GetSizeZ(float& _retmin, float& _retmax);//������ߺ����zֵ
		BOOL						GetHeight(IntersectData* intersect);		//ȡ�õ�ǰ��ĸ߶�
		BOOL						Intersect(IntersectData* intersect, BOOL bCollisionOnly = true);		//ȡ�õ�ǰ��ĸ߶�
		VOID						GetAABox(AABox& _ret);
	public:
		MapObjectData				m_obj;
		Map3DQuadBox*				m_pCurrentRegion;
		PSphereData					m_sphere;
		Rect						m_rect;
		matrix4x4					m_mat;
		CMapObject*					m_pNext;
		Mesh*						m_mesh;//ģ�Ͷ���
	};
	struct	MapTextureFile
	{
		FileName		file;
		BOOL			bFail;//����ʧ��
		Texture*		texture;//ͼƬ����
	};
	struct	MapObjectFile
	{
		int				id;
		FileName		file;
		Mesh*			mesh;//ģ�Ͷ���
		BOOL			bFail;
	};
	//�Ĳ���������
	class Map3DQuadBox
	{
	public:
		Map3DQuadBox(void);
		virtual ~Map3DQuadBox(void);
		//
		VOID			Setup(Map3DQuadBox* pParent, INT nLevel, INT nBeginX, INT nBeginY, INT nRegionWidth, float fRegionSize, INT nLevelIndex);	//����
		VOID			DestroyData();	//�������
		//
		BOOL			InsertObject(CMapObject* obj);
		//
		BOOL			IsBoxInRegion(const Rect& rc);	//���Ժ����Ƿ���������
		BOOL			IsBoxCollision(const Rect& rc);//���Ժ����Ƿ񽻲�
		BOOL			IsPointInBoxXY(const float3& pos);//���Ժ����Ƿ񽻲�
		//��Ⱦ����
		//VOID			RenderTerrain(Camera* c,  INT nRenderLevel = -1);
		//
		CMapObject*		Intersect(IntersectData* intersect, BOOL bCollisionOnly = true);
		VOID			Intersects(CDynamicArray<CMapObject*>& rets, IntersectData* intersect);
		//��ѡһ��ģ��
		VOID			SelectObjects(CDynamicArray<CMapObject*>& rets, const Rect& rc);
		//
		BOOL			GetHeight(IntersectData* intersect);		//ȡ�õ�ǰ��ĸ߶�
		//
		CMapObject*		GetFirstObject(){return m_pSceneFirst;}
		CMapObject*		GetNextObject(CMapObject* obj){if(!obj)return NULL; return obj->m_pNext;}
		Map3DQuadBox*		GetChildRegion(INT nIndex){if(nIndex < 0 || nIndex >= QUAD_BOX_COUNT)return NULL; return m_childRegion[nIndex];}
		//
		VOID			InsertToRenderList(float fRegionSize, Map3DQuadBox** renderList, INT& renderCount, INT maxRenderCount, INT minX, INT minY, INT maxX, INT maxY);
		//
		VOID			RecalcRegionBox();
		//
		const AABox&	GetRegionBox(){return m_regionBox;}	//�������򷽿�
		//
	protected:
		VOID			RenderAllLevels(Camera* c);
		VOID			FrameMoveAllLevels( Camera* c, INT nRenderLevel = -1);
		//��Ⱦ��������
		VOID			RenderBox( Camera* c, INT nSelectType = 0);
		//
		virtual	VOID	Render( Camera* c );
		VOID			FrameMove( Camera* c, INT nRenderLevel = -1);
		BOOL			AutoDestroyObject(const AABox& box);
		//���볡������
		VOID			InsertSceneNode(CMapObject* obj);
		//�Ƴ���������
		VOID			RemoveSceneNode(CMapObject* obj);
		//
		VOID			AddObjectCount(INT nCountAdd);
		//
		BOOL			OnChangeSceneObject(CMapObject* obj);
		//
		VOID			ForseVisible(BOOL bVisible);//ǿ����ʾ������
		VOID			ResetClipVisible(BOOL bHideOnly = FALSE);//���¼�����������,�Ƿ�ֻ���㲻�ɼ�����
		//
		friend class	Map3D;
		friend class	CMapObject;
		friend class	PhantomTerrainBox;
	protected:
		Map3D*				m_mapPtr;
		Map3DQuadBox*		m_childRegion[QUAD_BOX_COUNT];	//�Ӻ�������
		Map3DQuadBox*		m_pParent;
		CMapObject*			m_pSceneFirst;			//�����������
		//
		int					m_nChildObjectCount;
		Rect				m_rect;
		AABox				m_regionBox;
		short				m_nMaxLevel;
		char				m_nLevelIndex;
		friend class		Map3D;
	};
	class	Map3DQuadBoxScene: public Map3DQuadBox
	{
	public:
		Map3DQuadBoxScene();
		~Map3DQuadBoxScene();
		VOID							SetTile(unsigned int x, unsigned int y, const MapTile& t);
		VOID							SetHeight(unsigned int x, unsigned int y, unsigned char height);
	protected:
		virtual	VOID	Render( Camera* c );
	protected:
		AutoPtr<DeviceMesh>				m_terrain;
		//MapTile*						m_tiles;
		//unsigned char*					m_heights;
		friend class					Map3D;
	};
	class	Map3D
	{
	public:
		Map3D();
		~Map3D();
		VOID							Save(const char* szFileName);
		BOOL							Load(const char* szFileName);//����
		VOID							Destroy();
		inline	const Pixel&			GetCameraPos(){return m_cameraPos;}
		VOID							SetCameraPos(const Pixel& p);
		//
		VOID							OnFrameMove();
		VOID							Render();
		Texture*						GetTexturePtr(int id);
		Mesh*							LoadMesh(MapObjectData& id);
		Mesh*							GetObjectPtr(MapObjectData& id);
		Map3DQuadBox*					GetSceneRegion(INT xRegion, INT yRegion);	//���ص�������
		inline	int						GetMaxRegionWidth(){return m_nMaxRegionWidth;}
		VOID							BuildRegions(Map3DQuadBox* pRegion, Map3DQuadBox* pRegionParent, INT& nIndex, INT nLevel, INT nBeginX, INT nBeginY, INT nLevelIndex);
		CMapObject*						InsertObject(const MapObjectData& data);
		CMapObject*						Intersect(IntersectData* intersect, BOOL bCollisionOnly = true);
	public://runtime datas
		BOOL							m_bShowTerrain;
		BOOL							m_bShowObject;
		BOOL							m_bShowBlock;
		CDynamicArray<MapTextureFile>	m_textureFiles;
		CDynamicArray<MapObjectFile>	m_objectFiles;
		FileName						m_mapFile;
		//float2						m_brightContrast;
		float							m_fCameraLength;
	protected:
		Map3DQuadBox*					m_pRegionPtr;
		Map3DQuadBox*					m_regions;
		Map3DQuadBoxScene*				m_sceneRegions;
		int								m_nMaxRegionWidth;
	protected://save data
		Pixel							m_cameraPos;
		int								m_id;
		Size							m_mapSize;//������С
		int								m_tileSize;//���Ӵ�С
		CDynamicArray<MapTile>			m_tiles;
		CDynamicArray<unsigned char>	m_heights;
		CDynamicArray<CMapObject*>		m_objects;
		CDynamicArray<MapTrigger>		m_triggers;
		//
		friend class					Map3DQuadBox;
		friend class					Map3DQuadBoxScene;
	};


};

#endif
