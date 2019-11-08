#include "StdAfx.h"
#include "GCViewEffect.h"
#include "MainFrm.h"
#include "PropertiesDialogWnd.h"

GCViewEffectEditor::GCViewEffectEditor(CPhantomGCDoc* docPtr)
	:GCViewBase(docPtr, Language(L"��Ч�༭"), IDB_UI_VIEW_BMP)
{
	this->m_effectPtr	=	0;
}
VOID		GCViewEffectEditor::CloseFile(){
	GetEffectMgr()->StopEffect(m_effectPlay);
	safe_delete(m_effectPtr);
}
GCViewEffectEditor::~GCViewEffectEditor(void)
{
	CloseFile();
}

HICON		GCViewEffectEditor::GetViewerIcon()
{
	static HICON	hIcon	=	AfxGetApp()->LoadIcon(IDI_TEXTURE_FILE_ICON);
	return hIcon;
}

#define	SET_PROP_F(v) if(pProp == v){p.v = GetPropFloat(v);}
#define	SET_PROP_F2(v,v2) if(pProp == v){p.v2 = GetPropFloat(v);}
#define	SET_PROP_B(v) if(pProp == v){p.v = GetPropBool(v);}
#define	SET_PROP_I(v) if(pProp == v){p.v = GetPropInt(v);}
#define	SET_PROP_O(v,o) if(pProp == v){p.v = GetPropOption(v, o);}
void		GCViewEffectEditor::OnPropertyChanged(const GCPropertyBase* wnd, const CMFCPropertyGridProperty* pProp)
{
	__super::OnPropertyChanged(wnd, pProp);

	std::map<HTREEITEM,TreeItemType*> selectTypes;
	for(int i=0;i<this->m_treeView.GetSelectCount();i++)
	{
		HTREEITEM hItem		=	m_treeView.GetSelect(i);
		TreeItemType* type	=	this->GetTreeItem(this->m_treeView.GetItemData(hItem));
		if(type)
		{
			selectTypes[hItem]	=	type;
		}
	}
	BOOL bRefresh = false;
	for(std::map<HTREEITEM,TreeItemType*>::iterator it = selectTypes.begin();it != selectTypes.end(); it++)
	{
		TreeItemType* type	=	it->second;
		if(!type)
			continue;
		if(type->type == EFFECT_NODE)
		{
			
			CEffectNode* node = this->m_effectPtr->FindNode(type->p1);
			SProperty& p = node->m_pPro;
			SetModifyed(true);
			//
			if(pProp == NULL){
				break;
			}
			SET_PROP_F(fDelayTime);
			SET_PROP_F(fCreateTime);
			SET_PROP_F(fLifeTime);
			SET_PROP_F(fScalarMax);
			SET_PROP_F(fScalarMin);
			SET_PROP_F(fAngleMax);
			SET_PROP_F(fAngleMin);
			SET_PROP_F(fMoveSpeedMax);
			SET_PROP_F(fMoveSpeedMin);
			SET_PROP_F2(sStartPosX, sStartPos.x);
			SET_PROP_F2(sStartPosY, sStartPos.y);
			SET_PROP_F2(sStartPosZ, sStartPos.z);
			SET_PROP_F2(sEndPosX, sEndPos.x);
			SET_PROP_F2(sEndPosY, sEndPos.y);
			SET_PROP_F2(sEndPosZ, sEndPos.z);
			SET_PROP_F(fStraightMoveSpeed);
			SET_PROP_F(fStraightAccelSpeed);
			SET_PROP_F2(sStraightDirX,sStraightDir.x);
			SET_PROP_F2(sStraightDirY,sStraightDir.y);
			SET_PROP_F2(sStraightDirZ,sStraightDir.z);
			SET_PROP_F(fRotateRadius);
			SET_PROP_F(fRotateAngleSpeed);
			SET_PROP_F2(sRotateDirX, sRotateDir.x);
			SET_PROP_F2(sRotateDirY, sRotateDir.y);
			SET_PROP_F2(sRotateDirZ, sRotateDir.z);
			SET_PROP_F(fGravityStart);
			SET_PROP_F(fGravitySpeed);
			SET_PROP_F2(sGravityDirX, sGravityDir.x);
			SET_PROP_F2(sGravityDirY, sGravityDir.y);
			SET_PROP_F2(sGravityDirZ, sGravityDir.z);
			SET_PROP_F(fFollowingRangeStart);
			SET_PROP_F(fFollowingRangeAccel);
			SET_PROP_F2(sDirStartX, sDirStart.x);
			SET_PROP_F2(sDirStartY, sDirStart.y);
			SET_PROP_F2(sDirStartZ, sDirStart.z);
			SET_PROP_F(fDirRotateSpeedX);
			SET_PROP_F(fDirRotateSpeedY);
			SET_PROP_F(fDirRotateSpeedZ);
			SET_PROP_F2(sDirChildStartX, sDirChildStart.x);
			SET_PROP_F2(sDirChildStartY, sDirChildStart.y);
			SET_PROP_F2(sDirChildStartZ, sDirChildStart.z);
			SET_PROP_F(fDirChildRotateSpeedX);
			SET_PROP_F(fDirChildRotateSpeedY);
			SET_PROP_F(fDirChildRotateSpeedZ);
			SET_PROP_F(fScaleBaseRegularStart);
			SET_PROP_F(fScaleBaseRegularSpeed);
			SET_PROP_F(fScaleBaseSinStart);
			SET_PROP_F(fScaleBaseSinEnd);
			SET_PROP_F(fScaleBaseSinPeriodicTime);
			SET_PROP_F(fScaleAdditionRegularStart);
			SET_PROP_F(fScaleAdditionRegularSpeed);
			SET_PROP_F(fScaleAdditionSinStart);
			SET_PROP_F(fScaleAdditionSinEnd);
			SET_PROP_F(fScaleAdditionSinPeriodicTime);
			SET_PROP_F(fAlphaRegularStart);
			SET_PROP_F(fAlphaRegularEnd);
			SET_PROP_F(fAlphaSinStart);
			SET_PROP_F(fAlphaSinEnd);
			SET_PROP_F(fAlphaSinPeriodicTime);
			SET_PROP_F(fAtomicInstAniTime);
			//
			SET_PROP_B(bScalarRegular);
			SET_PROP_B(bAngleRegular);
			SET_PROP_B(bInheritMatrix);
			SET_PROP_B(bMoveMode);
			SET_PROP_B(bExpansionMatrix);
			SET_PROP_B(bStartPos);
			SET_PROP_B(bEndPos);
			SET_PROP_B(bBoundCheck);
			SET_PROP_B(bInheritEndPos);
			SET_PROP_B(bPosRevers);
			SET_PROP_B(bStraight);
			SET_PROP_B(bRotate);
			SET_PROP_B(bGravity);
			SET_PROP_B(bFollowing);
			SET_PROP_B(bDirStart);
			SET_PROP_B(bDirRotate);
			SET_PROP_B(bDirBillBoard);
			SET_PROP_B(bDirEqualNodeDir);
			SET_PROP_B(bDirChildStart);
			SET_PROP_B(bDirChildRotate);
			SET_PROP_B(bDirChildRandomRotateX);
			SET_PROP_B(bDirChildRandomRotateY);
			SET_PROP_B(bDirChildRandomRotateZ);
			SET_PROP_B(bDirChildBillBoard);
			SET_PROP_B(bDirChildEqualNodeDir);
			SET_PROP_B(bScale);
			SET_PROP_B(bScaleBaseRegular);
			SET_PROP_B(bScaleBaseSin);
			SET_PROP_B(bScaleAdditionX);
			SET_PROP_B(bScaleAdditionY);
			SET_PROP_B(bScaleAdditionZ);
			SET_PROP_B(bScaleAdditionRegular);
			SET_PROP_B(bScaleAdditionSin);
			SET_PROP_B(bAlphaZBuffer);
			SET_PROP_B(bAlphaRegular);
			SET_PROP_B(bAlphaSin);
			SET_PROP_B(bAlphaColor);
			SET_PROP_B(bAtomicInstAnimation);
			SET_PROP_B(bAtomicInstTwoSide);
			SET_PROP_B(bAtomicInstAniTime);
			SET_PROP_O(eCreate, g_typeEffectCreate);
			SET_PROP_O(eStart, g_typeEffectStart);
			SET_PROP_O(eMove, g_typeEffectMove);
			SET_PROP_O(eAlphaBlend, g_typeEffectAlpha);
			SET_PROP_I(nNumNode);
			if(pProp == sAlphaColor)
			{
				color4 c;
				c.from(GetPropColor(sAlphaColor), 1);
				p.sAlphaColor.setxyz(c.r, c.g, c.b);
			}
			if(pProp == textureFile)
			{
				std::wstring str;
				GetPropFile(textureFile, str);
				A a(str.c_str());
				char szFile[256], szExt[128];
				_splitpath(a.buf, 0, 0, szFile, szExt);
				strcat(szFile, szExt);
				node->SetTextureFile(szFile);
			}
			bRefresh = true;
		}
	}
	if(bRefresh)
	{
		this->RefreshEnable();
		GetEffectMgr()->PlayEffect(m_effectPtr->m_effectName, float3(0, 0, 0), float3(2000, -2000, 0));
	}
}

VOID		GCViewEffectEditor::OnChangeTreeSelect(CMTreeCtrl* treePtr, HTREEITEM hAddItem)	//����ѡ�����οؼ�
{
	if(treePtr == &m_treeView)
	{
		TreeItemType* type	=	this->GetSelectedItem();
		if(!type)
		{
			SetCurrentProperties(&m_viewerProps, L"�ļ�����", NULL);
			return;
		}
		switch(type->type)
		{
		case EFFECT_MAIN:
			{
				SetCurrentProperties(NULL, NULL, NULL);
				GetEffectMgr()->PlayEffect(m_effectPtr->m_effectName, float3(0, 0, 0), float3(2000, -2000, 0));
			}
			break;
		case EFFECT_NODE:
			{
				SetCurrentProperties(&this->m_nodeProp, L"��������", NULL);
				m_nodeProp.EnableRender(false);
				CEffectNode* node = this->m_effectPtr->FindNode(type->p1);
				if(!node){
					m_nodeProp.EnableWindow(false);
					m_nodeProp.EnableRender(true);
					return;
				}
				SProperty& p = node->m_pPro;
				//
				SetPropFloat(fDelayTime, p.fDelayTime);
				SetPropFloat(fCreateTime, p.fCreateTime);
				SetPropFloat(fLifeTime, p.fLifeTime);
				SetPropFloat(fScalarMax, p.fScalarMax);
				SetPropFloat(fScalarMin, p.fScalarMin);
				SetPropFloat(fAngleMax, p.fAngleMax);
				SetPropFloat(fAngleMin, p.fAngleMin);
				SetPropFloat(fMoveSpeedMax, p.fMoveSpeedMax);
				SetPropFloat(fMoveSpeedMin, p.fMoveSpeedMin);
				SetPropFloat(sStartPosX, p.sStartPos.x);
				SetPropFloat(sStartPosY, p.sStartPos.y);
				SetPropFloat(sStartPosZ, p.sStartPos.z);
				SetPropFloat(sEndPosX, p.sEndPos.x);
				SetPropFloat(sEndPosY, p.sEndPos.y);
				SetPropFloat(sEndPosZ, p.sEndPos.z);
				SetPropFloat(fStraightMoveSpeed, p.fStraightMoveSpeed);
				SetPropFloat(fStraightAccelSpeed, p.fStraightAccelSpeed);
				SetPropFloat(sStraightDirX, p.sStraightDir.x);
				SetPropFloat(sStraightDirY, p.sStraightDir.y);
				SetPropFloat(sStraightDirZ, p.sStraightDir.z);
				SetPropFloat(fRotateRadius, p.fRotateRadius);
				SetPropFloat(fRotateAngleSpeed, p.fRotateAngleSpeed);
				SetPropFloat(sRotateDirX, p.sRotateDir.x);
				SetPropFloat(sRotateDirY, p.sRotateDir.y);
				SetPropFloat(sRotateDirZ, p.sRotateDir.z);
				//
				SetPropFloat(fGravityStart, p.fGravityStart);
				SetPropFloat(fGravitySpeed, p.fGravitySpeed);
				SetPropFloat(sGravityDirX, p.sGravityDir.x);
				SetPropFloat(sGravityDirY, p.sGravityDir.y);
				SetPropFloat(sGravityDirZ, p.sGravityDir.z);
				SetPropFloat(fFollowingRangeStart, p.fFollowingRangeStart);
				SetPropFloat(fFollowingRangeAccel, p.fFollowingRangeAccel);
				SetPropFloat(sDirStartX, p.sDirStart.x);
				SetPropFloat(sDirStartY, p.sDirStart.y);
				SetPropFloat(sDirStartZ, p.sDirStart.z);
				//
				SetPropFloat(fDirRotateSpeedX, p.fDirRotateSpeedX);
				SetPropFloat(fDirRotateSpeedY, p.fDirRotateSpeedY);
				SetPropFloat(fDirRotateSpeedZ, p.fDirRotateSpeedZ);
				SetPropFloat(sDirChildStartX, p.sDirChildStart.x);
				SetPropFloat(sDirChildStartY, p.sDirChildStart.y);
				SetPropFloat(sDirChildStartZ, p.sDirChildStart.z);
				SetPropFloat(fDirChildRotateSpeedX, p.fDirChildRotateSpeedX);
				SetPropFloat(fDirChildRotateSpeedY, p.fDirChildRotateSpeedY);
				SetPropFloat(fDirChildRotateSpeedZ, p.fDirChildRotateSpeedZ);
				SetPropFloat(fScaleBaseRegularStart, p.fScaleBaseRegularStart);
				SetPropFloat(fScaleBaseRegularSpeed, p.fScaleBaseRegularSpeed);
				SetPropFloat(fScaleBaseSinStart, p.fScaleBaseSinStart);
				SetPropFloat(fScaleBaseSinEnd, p.fScaleBaseSinEnd);
				//
				SetPropFloat(fScaleBaseSinPeriodicTime, p.fScaleBaseSinPeriodicTime);
				SetPropFloat(fScaleAdditionRegularStart, p.fScaleAdditionRegularStart);
				SetPropFloat(fScaleAdditionRegularSpeed, p.fScaleAdditionRegularSpeed);
				SetPropFloat(fScaleAdditionSinStart, p.fScaleAdditionSinStart);
				SetPropFloat(fScaleAdditionSinEnd, p.fScaleAdditionSinEnd);
				SetPropFloat(fScaleAdditionSinPeriodicTime, p.fScaleAdditionSinPeriodicTime);
				SetPropFloat(fAlphaRegularStart, p.fAlphaRegularStart);
				SetPropFloat(fAlphaRegularEnd, p.fAlphaRegularEnd);
				SetPropFloat(fAlphaSinStart, p.fAlphaSinStart);
				SetPropFloat(fAlphaSinEnd, p.fAlphaSinEnd);
				SetPropFloat(fAlphaSinPeriodicTime, p.fAlphaSinPeriodicTime);
				SetPropFloat(fAtomicInstAniTime, p.fAtomicInstAniTime);
				//
				SetPropBool(bScalarRegular, p.bScalarRegular);
				SetPropBool(bAngleRegular, p.bAngleRegular);
				SetPropBool(bInheritMatrix, p.bInheritMatrix);
				SetPropBool(bMoveMode, p.bMoveMode);
				SetPropBool(bExpansionMatrix, p.bExpansionMatrix);
				SetPropBool(bStartPos, p.bStartPos);
				SetPropBool(bEndPos, p.bEndPos);
				SetPropBool(bBoundCheck, p.bBoundCheck);
				SetPropBool(bInheritEndPos, p.bInheritEndPos);
				SetPropBool(bPosRevers, p.bPosRevers);
				SetPropBool(bStraight, p.bStraight);
				SetPropBool(bRotate, p.bRotate);
				SetPropBool(bGravity, p.bGravity);
				SetPropBool(bFollowing, p.bFollowing);
				SetPropBool(bDirStart, p.bDirStart);
				SetPropBool(bDirRotate, p.bDirRotate);
				SetPropBool(bDirBillBoard, p.bDirBillBoard);
				SetPropBool(bDirEqualNodeDir, p.bDirEqualNodeDir);
				//
				SetPropBool(bDirChildStart, p.bDirChildStart);
				SetPropBool(bDirChildRotate, p.bDirChildRotate);
				SetPropBool(bDirChildRandomRotateX, p.bDirChildRandomRotateX);
				SetPropBool(bDirChildRandomRotateY, p.bDirChildRandomRotateY);
				SetPropBool(bDirChildRandomRotateZ, p.bDirChildRandomRotateZ);
				SetPropBool(bDirChildBillBoard, p.bDirChildBillBoard);
				SetPropBool(bDirChildEqualNodeDir, p.bDirChildEqualNodeDir);
				SetPropBool(bScale, p.bScale);
				SetPropBool(bScaleBaseRegular, p.bScaleBaseRegular);
				SetPropBool(bScaleBaseSin, p.bScaleBaseSin);
				SetPropBool(bScaleAdditionX, p.bScaleAdditionX);
				SetPropBool(bScaleAdditionY, p.bScaleAdditionY);
				SetPropBool(bScaleAdditionZ, p.bScaleAdditionZ);
				SetPropBool(bScaleAdditionRegular, p.bScaleAdditionRegular);
				SetPropBool(bScaleAdditionSin, p.bScaleAdditionSin);
				SetPropBool(bAlphaZBuffer, p.bAlphaZBuffer);
				SetPropBool(bAlphaRegular, p.bAlphaRegular);
				SetPropBool(bAlphaSin, p.bAlphaSin);
				//
				SetPropBool(bAlphaColor, p.bAlphaColor);
				SetPropBool(bAtomicInstAnimation, p.bAtomicInstAnimation);
				SetPropBool(bAtomicInstTwoSide, p.bAtomicInstTwoSide);
				SetPropBool(bAtomicInstAniTime, p.bAtomicInstAniTime);
				//
				SetPropColor(sAlphaColor, RGB(p.sAlphaColor.x*255.0f, p.sAlphaColor.y*255.0f, p.sAlphaColor.z*255.0f));
				//
				SetPropOption(eCreate, g_typeEffectCreate, p.eCreate);
				SetPropOption(eAlphaBlend, g_typeEffectAlpha, p.eAlphaBlend);
				SetPropOption(eMove, g_typeEffectMove, p.eMove);
				SetPropOption(eStart, g_typeEffectStart, p.eStart);
				SetPropInt(nNumNode, p.nNumNode);
				SetPropFile(textureFile, node->GetTextureFile());
				RefreshEnable();
				//
				m_nodeProp.EnableWindow(TRUE);
				m_nodeProp.EnableRender(true);
			}
			break;
		default:
			SetCurrentProperties(NULL, NULL, NULL);
			break;
		}
		return;
	}
	SetCurrentProperties(NULL, NULL, NULL);
}

VOID		GCViewEffectEditor::RefreshEnable()
{
	BOOL bTemp = 0;
	bTemp = GetPropBool(bScalarRegular);
	fScalarMax->Enable(bTemp);
	fScalarMin->Enable(bTemp);
	bTemp = GetPropBool(bAngleRegular);
	fAngleMax->Enable(bTemp);
	fAngleMin->Enable(bTemp);
	// MoveMode
	bTemp = GetPropBool(bMoveMode);
	fMoveSpeedMax->Enable(bTemp);
	fMoveSpeedMin->Enable(bTemp);
	// MoveMode
	bTemp = GetPropBool(bStartPos);
	sStartPosX->Enable(bTemp);
	sStartPosY->Enable(bTemp);
	sStartPosZ->Enable(bTemp);
	// MoveMode
	bTemp = GetPropBool(bEndPos);
	sEndPosX->Enable(bTemp);
	sEndPosY->Enable(bTemp);
	sEndPosZ->Enable(bTemp);
	// Straight
	bTemp = GetPropBool(bStraight);
	fStraightMoveSpeed->Enable(bTemp);
	fStraightAccelSpeed->Enable(bTemp);
	sStraightDirX->Enable(bTemp);
	sStraightDirY->Enable(bTemp);
	sStraightDirZ->Enable(bTemp);
	// Rotate
	bTemp = GetPropBool(bRotate);
	fRotateRadius->Enable(bTemp);
	fRotateAngleSpeed->Enable(bTemp);
	sRotateDirX->Enable(bTemp);
	sRotateDirY->Enable(bTemp);
	sRotateDirZ->Enable(bTemp);
	// Gravity
	bTemp = GetPropBool(bGravity);
	fGravityStart->Enable(bTemp);
	fGravitySpeed->Enable(bTemp);
	sGravityDirX->Enable(bTemp);
	sGravityDirY->Enable(bTemp);
	sGravityDirZ->Enable(bTemp);
	// Following
	bTemp = GetPropBool(bFollowing);
	fFollowingRangeStart->Enable(bTemp);
	fFollowingRangeAccel->Enable(bTemp);
	// Dir
	bTemp = GetPropBool(bDirStart);
	sDirStartX->Enable(bTemp);
	sDirStartY->Enable(bTemp);
	sDirStartZ->Enable(bTemp);
	bTemp = GetPropBool(bDirRotate);
	fDirRotateSpeedX->Enable(bTemp);
	fDirRotateSpeedY->Enable(bTemp);
	fDirRotateSpeedZ->Enable(bTemp);
	bTemp = GetPropBool(bDirChildStart);
	sDirChildStartX->Enable(bTemp);
	sDirChildStartY->Enable(bTemp);
	sDirChildStartZ->Enable(bTemp);
	bTemp = GetPropBool(bDirChildRotate);
	fDirChildRotateSpeedX->Enable(bTemp);
	fDirChildRotateSpeedY->Enable(bTemp);
	fDirChildRotateSpeedZ->Enable(bTemp);

	bTemp = GetPropBool(bScaleBaseRegular);
	fScaleBaseRegularStart->Enable(bTemp);
	fScaleBaseRegularSpeed->Enable(bTemp);

	bTemp = GetPropBool(bScaleBaseSin);
	fScaleBaseSinStart->Enable(bTemp);
	fScaleBaseSinEnd->Enable(bTemp);
	fScaleBaseSinPeriodicTime->Enable(bTemp);

	bTemp = GetPropBool(bScaleAdditionRegular);
	fScaleAdditionRegularStart->Enable(bTemp);
	fScaleAdditionRegularSpeed->Enable(bTemp);
	bTemp = GetPropBool(bScaleAdditionSin);
	fScaleAdditionSinStart->Enable(bTemp);
	fScaleAdditionSinEnd->Enable(bTemp);
	fScaleAdditionSinPeriodicTime->Enable(bTemp);

	bTemp = GetPropBool(bAlphaRegular);
	fAlphaRegularStart->Enable(bTemp);
	fAlphaRegularEnd->Enable(bTemp);

	bTemp = GetPropBool(bAlphaSin);
	fAlphaSinStart->Enable(bTemp);
	fAlphaSinEnd->Enable(bTemp);
	fAlphaSinPeriodicTime->Enable(bTemp);

	bTemp = GetPropBool(bAlphaColor);
	sAlphaColor->Enable(bTemp);
}

BOOL		GCViewEffectEditor::OpenFile(const wchar_t* szFile)	//���ļ�,���ʧ������Զ�ɾ��
{
	if(GetEffectMgr())
		GetEffectMgr()->ClearEffect();
	safe_delete(m_effectPtr);
	this->m_strFile	=	szFile;
	if(!__super::OpenFile(szFile))
		return false;
	if(!m_viewerProps.m_hWnd)
		this->m_treeView.InsertItem(Language(L"TextureViewer", L"ͼƬ�쿴��"), 25, 25);
	CreateEffectMgr();
	wchar_t dir[512];
	GetCurrentDirectory(512, dir);
	m_effectPtr = GetEffectMgr()->LoadEffect(A(m_strFile.c_str()));
	m_effectPlay = GetEffectMgr()->PlayEffect(m_effectPtr->m_effectName, float3(0, 0, 0), float3(2000, -2000, 0));
	//
	this->m_bShowUIGrid = true;
	RebuildTrees();
	if(!m_viewerProps.m_hWnd)
	{
		InitViewerProps();
		InitNodeProp();
	}
	return true;
}

VOID		GCViewEffectEditor::RebuildTrees()
{
	if(m_hViewItem)
		m_treeView.DeleteItem(m_hViewItem);
	wchar_t wFileName[256], wExt[256];
	_wsplitpath(m_strFile.c_str(), 0, 0, wFileName, wExt);
	wcscat(wFileName, wExt);
	m_hViewItem = m_treeView.InsertItem(wFileName, 18, 18);
	m_treeView.SetItemState(m_hViewItem, TVIS_BOLD, TVIS_BOLD);
	m_treeView.Expand(m_hViewItem, TVE_EXPAND);
	//
	this->ClearTreeItem();
	BuildAll();
	//
	m_treeView.m_callback	=	this;
}

VOID		GCViewEffectEditor::BuildAll(HTREEITEM hItem, CEffectNode* n)
{
	for(int i=0;i<n->m_vNodeInst.size();i++)
	{
		HTREEITEM hCursor		=	m_treeView.InsertItem(W(n->m_vNodeInst[i]->m_pPro.szNodeName), 18, 18, m_hViewItem);
		m_treeView.SetItemData(hCursor, AddTreeItem(EFFECT_NODE, n->m_vNodeInst[i]->m_nID));
		if(n->m_vNodeInst[i]->m_vNodeInst.size() > 0)
			BuildAll(hCursor, n->m_vNodeInst[i]);
	}
}

VOID		GCViewEffectEditor::BuildAll()
{
	m_treeView.SelectItem(m_hViewItem);
	DeleteChildItems(m_hViewItem);
	m_treeView.SetItemData(m_hViewItem, AddTreeItem(EFFECT_MAIN));
	BuildAll(m_hViewItem, m_effectPtr);
}

VOID		GCViewEffectEditor::OnActive()		//������
{
	__super::OnActive();
}

VOID		GCViewEffectEditor::OnDeActive()		//ʧȥ����
{
	__super::OnDeActive();
}

void		GCViewEffectEditor::OnFrameMove(const RenderParameter& r)	//ÿ�θ���
{
	GetEffectMgr()->FrameMove();
}

void		GCViewEffectEditor::OnPushRenderObjects(const RenderParameter& r)	//��Ⱦ
{
	GetEffectMgr()->Render();
}

BOOL		GCViewEffectEditor::SaveFile(BOOL bSaveAs)	//�����ļ�
{
	bool bNew	=	false;
	if(bSaveAs || m_strFile.size() == 0)
	{
		bNew	=	true;
		CFileDialog dlg(FALSE, 0, 0, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, formatw(L"%s|*.rpgmesh||", Language(L"EffectFile", L"��Ч�ļ�") ), GetMainFrame());
		wchar_t buffer[1024];
		dlg.m_pOFN->lpstrInitialDir	=	AToW(GetProjectPath(), buffer, 1024);
		if(dlg.DoModal() != IDOK)
			return false;
		SetProjectPath();
		wchar_t szPath[256], szFile[256], szDir[256];
		_wsplitpath(dlg.GetPathName(), szPath, szDir, szFile, 0);
		wcscat(szPath, szDir);
		wcscat(szPath, szFile);
		wcscat(szPath, L".rpgmesh");
		m_strFile	=	szPath;
	}
	//if(m_effectPtr)
		//m_effectPtr->Save(A(m_strFile.c_str()));
	return __super::SaveFile(bSaveAs);
}

void		GCViewEffectEditor::OnRendering(const RenderParameter& r)	//��Ⱦ
{
	if(IsShowUIGrid())
	{
		GetRenderHelperPtr()->SetZWriteEnable(false);
		GetRenderHelperPtr()->SetAlphaMode(ALPHAMODE_ALPHABLEND);
		GetRenderHelperPtr()->SetTexture(0, 0);
		GetRenderHelperPtr()->SetSrcBlend(Enum::BLEND_SRCALPHA);
		GetRenderHelperPtr()->SetDestBlend(Enum::BLEND_INVSRCALPHA);
		GetRenderHelperPtr()->drawGrid(GetCameraPtr()->GetEye(), 0x3f3f3f3f, To3DValue(5.0f), 5, 5);
		GetRenderHelperPtr()->SetZWriteEnable(true);
	}
}

void		GCViewEffectEditor::OnRenderingEnd(const RenderParameter& r)
{
}
//��Ⱦ
void		GCViewEffectEditor::OnUpdateUI(INT nMenuID, CCmdUI* pCmdUI)
{
	switch(nMenuID)
	{
	default:
		pCmdUI->Enable(false);
		break;
	}
}


void		GCViewEffectEditor::OnCommandUI(INT nMenuID)
{
}

VOID		GCViewEffectEditor::InitNodeProp()
{
	InitProp(m_nodeProp);
	CMFCPropertyGridProperty* create	= new CMFCPropertyGridProperty(Language(L"��������"));
	create->AddSubItem(textureFile		=	AddPropFile(Language(L"[����]��ͼ"), Language(L"textureFile", L"����������ͼ"), GetImageFilter()));
	create->AddSubItem(fDelayTime		= AddPropFloat(Language(L"�ӳ�ʱ��"), Language(L"fDelayTime", L"�ӳ�ʱ�䡣"), false, 0.000f, 10000.0f));
	create->AddSubItem(fCreateTime		= AddPropFloat(Language(L"����ʱ��"), Language(L"fCreateTime", L"����ʱ�䡣"), false, 0.000f, 10000.0f));
	create->AddSubItem(fLifeTime		= AddPropFloat(Language(L"��������"), Language(L"fLifeTime", L"�������ڡ�"), false, 0.000f, 10000.0f));
	create->AddSubItem(nNumNode			= AddPropInt(Language(L"�ڵ�����"), Language(L"nNumNode", L"�ڵ�������"), 0, 1000));
	create->AddSubItem(eCreate			= AddPropOption(Language(L"������ʽ"), Language(L"eCreate", L"������ʽ"), g_typeEffectCreate));
	// StartMode
	CMFCPropertyGridProperty* start		= new CMFCPropertyGridProperty(Language(L"��ʼ����"));
	start->AddSubItem(eStart			= AddPropOption(Language(L"��ʼ��ʽ"), Language(L"eStart", L"��ʼ��ʽ"), g_typeEffectStart));
	start->AddSubItem(bScalarRegular	= AddPropBool(Language(L"��������"), Language(L"bScalarRegular", L"�������š�")));
	start->AddSubItem(fScalarMax		= AddPropFloat(Language(L"�������"), Language(L"fScalarMax", L"������š�"), false, -10000.0f, 10000.0f));
	start->AddSubItem(fScalarMin		= AddPropFloat(Language(L"��С����"), Language(L"fScalarMin", L"��С���š�"), false, -10000.0f, 10000.0f));
	start->AddSubItem(bAngleRegular	= AddPropBool(Language(L"����ת��"), Language(L"bAngleRegular", L"����ת����")));
	start->AddSubItem(fAngleMax		= AddPropFloat(Language(L"���Ƕ�"), Language(L"fAngleMax", L"���Ƕȡ�"), false, -10000.0f, 10000.0f));
	start->AddSubItem(fAngleMin		= AddPropFloat(Language(L"��С�Ƕ�"), Language(L"fAngleMin", L"��С�Ƕȡ�"), false, -10000.0f, 10000.0f));
	start->AddSubItem(bInheritMatrix	= AddPropBool(Language(L"�̳о���"), Language(L"bInheritMatrix", L"�̳о���")));
	// MoveMode
	CMFCPropertyGridProperty* movemode		= new CMFCPropertyGridProperty(Language(L"�ƶ�����"));
	movemode->AddSubItem(bMoveMode			= AddPropBool(Language(L"�Ƿ��ƶ�"), Language(L"bMoveMode", L"�Ƿ��ƶ���")));
	movemode->AddSubItem(eMove				= AddPropOption(Language(L"�ƶ�ģʽ"), Language(L"eMove", L"�ƶ�ģʽ"), g_typeEffectMove));
	movemode->AddSubItem(fMoveSpeedMax		= AddPropFloat(Language(L"�ƶ��ٶ����"), Language(L"fMoveSpeedMax", L"�ƶ��ٶ����"), false, -10000.0f, 10000.0f));
	movemode->AddSubItem(fMoveSpeedMin		= AddPropFloat(Language(L"�ƶ��ٶ���С"), Language(L"fMoveSpeedMin", L"�ƶ��ٶ���С��"), false, -10000.0f, 10000.0f));
	movemode->AddSubItem(bExpansionMatrix	= AddPropBool(Language(L"��չ����"), Language(L"bExpansionMatrix", L"��չ����")));
	// Pos
	CMFCPropertyGridProperty* startPos		= new CMFCPropertyGridProperty(Language(L"��ʼλ��"));
	startPos->AddSubItem(bStartPos			= AddPropBool(Language(L"��ʼλ����Ч"), Language(L"bStartPos", L"��ʼλ����Ч��")));
	startPos->AddSubItem(sStartPosX			= AddPropFloat(Language(L"��ʼλ��X"), Language(L"sStartPosX", L"��ʼλ��X��"), false, -100000.0f, 100000.0f));
	startPos->AddSubItem(sStartPosY			= AddPropFloat(Language(L"��ʼλ��Y"), Language(L"sStartPosY", L"��ʼλ��Y��"), false, -100000.0f, 100000.0f));
	startPos->AddSubItem(sStartPosZ			= AddPropFloat(Language(L"��ʼλ��Z"), Language(L"sStartPosZ", L"��ʼλ��Z��"), false, -100000.0f, 100000.0f));
	startPos->AddSubItem(bEndPos			= AddPropBool(Language(L"����λ����Ч"), Language(L"bEndPos", L"����λ����Ч��")));
	startPos->AddSubItem(sEndPosX			= AddPropFloat(Language(L"����λ��X"), Language(L"sEndPosX", L"����λ��X��"), false, -100000.0f, 100000.0f));
	startPos->AddSubItem(sEndPosY			= AddPropFloat(Language(L"����λ��Y"), Language(L"sEndPosY", L"����λ��Y��"), false, -100000.0f, 100000.0f));
	startPos->AddSubItem(sEndPosZ			= AddPropFloat(Language(L"����λ��Z"), Language(L"sEndPosZ", L"����λ��Z��"), false, -100000.0f, 100000.0f));
	startPos->AddSubItem(bBoundCheck	= AddPropBool(Language(L"Լ�����"), Language(L"bBoundCheck", L"Լ����顣")));
	startPos->AddSubItem(bInheritEndPos	= AddPropBool(Language(L"�̳н���λ��"), Language(L"bInheritEndPos", L"�̳н���λ�á�")));
	startPos->AddSubItem(bPosRevers	= AddPropBool(Language(L"λ�÷���"), Language(L"bPosRevers", L"λ�÷���")));
	// Straight
	CMFCPropertyGridProperty* straight		= new CMFCPropertyGridProperty(Language(L"ֱ������"));
	straight->AddSubItem(bStraight			= AddPropBool(Language(L"ֱ����Ч"), Language(L"bStraight", L"ֱ����Ч��")));
	straight->AddSubItem(fStraightMoveSpeed		= AddPropFloat(Language(L"�ƶ��ٶ�ֵ"), Language(L"sEndPosX", L"�ƶ��ٶ�ֵ��"), false, -100000.0f, 100000.0f));
	straight->AddSubItem(fStraightAccelSpeed	= AddPropFloat(Language(L"ֱ�߼����ٶ�"), Language(L"sEndPosX", L"ֱ�߼����ٶȡ�"), false, -100000.0f, 100000.0f));
	straight->AddSubItem(sStraightDirX			= AddPropFloat(Language(L"ֱ�߷���X"), Language(L"sEndPosX", L"ֱ�߷���X��"), false, -100000.0f, 100000.0f));
	straight->AddSubItem(sStraightDirY			= AddPropFloat(Language(L"ֱ�߷���Y"), Language(L"sEndPosX", L"ֱ�߷���Y��"), false, -100000.0f, 100000.0f));
	straight->AddSubItem(sStraightDirZ			= AddPropFloat(Language(L"ֱ�߷���Z"), Language(L"sEndPosX", L"ֱ�߷���Z��"), false, -100000.0f, 100000.0f));
	// Rotate
	CMFCPropertyGridProperty* rotate		= new CMFCPropertyGridProperty(Language(L"ת������"));
	rotate->AddSubItem(bRotate			= AddPropBool(Language(L"ת����Ч"), Language(L"bRotate", L"ת����Ч��")));
	rotate->AddSubItem(fRotateRadius		= AddPropFloat(Language(L"ת���Ƕ�"), Language(L"fRotateRadius", L"ת���Ƕȡ�"), false, -100000.0f, 100000.0f));
	rotate->AddSubItem(fRotateAngleSpeed	= AddPropFloat(Language(L"ת���Ƕ��ٶ�"), Language(L"fRotateAngleSpeed", L"ת���Ƕ��ٶȡ�"), false, -100000.0f, 100000.0f));
	rotate->AddSubItem(sRotateDirX			= AddPropFloat(Language(L"ת������X"), Language(L"sRotateDirX", L"ת������X��"), false, -100000.0f, 100000.0f));
	rotate->AddSubItem(sRotateDirY			= AddPropFloat(Language(L"ת������Y"), Language(L"sRotateDirY", L"ת������Y��"), false, -100000.0f, 100000.0f));
	rotate->AddSubItem(sRotateDirZ			= AddPropFloat(Language(L"ת������Z"), Language(L"sRotateDirZ", L"ת������Z��"), false, -100000.0f, 100000.0f));
	// Gravity
	CMFCPropertyGridProperty* gravity		= new CMFCPropertyGridProperty(Language(L"��������"));
	gravity->AddSubItem(bGravity			= AddPropBool(Language(L"������Ч"), Language(L"bGravity", L"������Ч��")));
	gravity->AddSubItem(fGravityStart		= AddPropFloat(Language(L"������ʼ"), Language(L"fGravityStart", L"������ʼ��"), false, -100000.0f, 100000.0f));
	gravity->AddSubItem(fGravitySpeed		= AddPropFloat(Language(L"�����ٶ�"), Language(L"fGravitySpeed", L"�����ٶȡ�"), false, -100000.0f, 100000.0f));
	gravity->AddSubItem(sGravityDirX			= AddPropFloat(Language(L"��������X"), Language(L"sGravityDirX", L"��������X��"), false, -100000.0f, 100000.0f));
	gravity->AddSubItem(sGravityDirY			= AddPropFloat(Language(L"��������Y"), Language(L"sGravityDirY", L"��������Y��"), false, -100000.0f, 100000.0f));
	gravity->AddSubItem(sGravityDirZ			= AddPropFloat(Language(L"��������Z"), Language(L"sGravityDirZ", L"��������Z��"), false, -100000.0f, 100000.0f));
	// Following
	CMFCPropertyGridProperty* following		= new CMFCPropertyGridProperty(Language(L"��������"));
	following->AddSubItem(bFollowing			= AddPropBool(Language(L"������Ч"), Language(L"bFollowing", L"������Ч��")));
	following->AddSubItem(fFollowingRangeStart		= AddPropFloat(Language(L"���濪ʼ"), Language(L"fFollowingRangeStart", L"���濪ʼ��"), false, -100000.0f, 100000.0f));
	following->AddSubItem(fFollowingRangeAccel		= AddPropFloat(Language(L"�������"), Language(L"fFollowingRangeAccel", L"������١�"), false, -100000.0f, 100000.0f));
	// Dir
	CMFCPropertyGridProperty* dirstart		= new CMFCPropertyGridProperty(Language(L"��������"));
	dirstart->AddSubItem(bDirStart			= AddPropBool(Language(L"��ʼ������Ч"), Language(L"bDirStart", L"��ʼ������Ч��")));
	dirstart->AddSubItem(sDirStartX			= AddPropFloat(Language(L"��ʼ����X"), Language(L"sDirStartX", L"��ʼ����X��"), false, -100000.0f, 100000.0f));
	dirstart->AddSubItem(sDirStartY			= AddPropFloat(Language(L"��ʼ����Y"), Language(L"sDirStartY", L"��ʼ����Y��"), false, -100000.0f, 100000.0f));
	dirstart->AddSubItem(sDirStartZ			= AddPropFloat(Language(L"��ʼ����Z"), Language(L"sDirStartZ", L"��ʼ����Z��"), false, -100000.0f, 100000.0f));
	dirstart->AddSubItem(bDirRotate			= AddPropBool(Language(L"ת���ٶ���Ч"), Language(L"bDirRotate", L"ת��������Ч��")));
	dirstart->AddSubItem(fDirRotateSpeedX			= AddPropFloat(Language(L"ת���ٶ�X"), Language(L"fDirRotateSpeedX", L"ת���ٶ�X��"), false, -100000.0f, 100000.0f));
	dirstart->AddSubItem(fDirRotateSpeedY			= AddPropFloat(Language(L"ת���ٶ�Y"), Language(L"fDirRotateSpeedY", L"ת���ٶ�Y��"), false, -100000.0f, 100000.0f));
	dirstart->AddSubItem(fDirRotateSpeedZ			= AddPropFloat(Language(L"ת���ٶ�Z"), Language(L"fDirRotateSpeedZ", L"ת���ٶ�Z��"), false, -100000.0f, 100000.0f));
	dirstart->AddSubItem(bDirBillBoard			= AddPropBool(Language(L"Billboard"), Language(L"bDirBillBoard", L"Billboard��")));
	dirstart->AddSubItem(bDirEqualNodeDir			= AddPropBool(Language(L"ǰ������"), Language(L"bDirEqualNodeDir", L"ǰ������")));
	// DirChild
	CMFCPropertyGridProperty* dirchild		= new CMFCPropertyGridProperty(Language(L"�ӷ�������"));
	dirchild->AddSubItem(bDirChildStart			= AddPropBool(Language(L"�ӷ�����Ч"), Language(L"bDirChildStart", L"�ӷ�����Ч��")));
	dirchild->AddSubItem(sDirChildStartX			= AddPropFloat(Language(L"�ӷ���X"), Language(L"sDirChildStartX", L"�ӷ���X��"), false, -100000.0f, 100000.0f));
	dirchild->AddSubItem(sDirChildStartY			= AddPropFloat(Language(L"�ӷ���Y"), Language(L"sDirChildStartY", L"�ӷ���Y��"), false, -100000.0f, 100000.0f));
	dirchild->AddSubItem(sDirChildStartZ			= AddPropFloat(Language(L"�ӷ���Z"), Language(L"sDirChildStartZ", L"�ӷ���Z��"), false, -100000.0f, 100000.0f));
	dirchild->AddSubItem(bDirChildRotate			= AddPropBool(Language(L"��ת����Ч"), Language(L"bDirChildRotate", L"��ת����Ч��")));
	dirchild->AddSubItem(fDirChildRotateSpeedX			= AddPropFloat(Language(L"��ת���ٶ�X"), Language(L"fDirChildRotateSpeedX", L"��ת���ٶ�X��"), false, -100000.0f, 100000.0f));
	dirchild->AddSubItem(fDirChildRotateSpeedY			= AddPropFloat(Language(L"��ת���ٶ�Y"), Language(L"fDirChildRotateSpeedY", L"��ת���ٶ�Y��"), false, -100000.0f, 100000.0f));
	dirchild->AddSubItem(fDirChildRotateSpeedZ			= AddPropFloat(Language(L"��ת���ٶ�Z"), Language(L"fDirChildRotateSpeedZ", L"��ת���ٶ�Z��"), false, -100000.0f, 100000.0f));
	dirchild->AddSubItem(bDirChildRandomRotateX			= AddPropBool(Language(L"�������X"), Language(L"bDirChildRandomRotateX", L"�������X��")));
	dirchild->AddSubItem(bDirChildRandomRotateY			= AddPropBool(Language(L"�������Y"), Language(L"bDirChildRandomRotateY", L"�������Y��")));
	dirchild->AddSubItem(bDirChildRandomRotateZ			= AddPropBool(Language(L"�������Z"), Language(L"bDirChildRandomRotateZ", L"�������Z��")));
	dirchild->AddSubItem(bDirChildBillBoard				= AddPropBool(Language(L"�Ӷ���Billbaord"), Language(L"bDirChildBillBoard", L"�Ӷ���Billbaord��")));
	dirchild->AddSubItem(bDirChildEqualNodeDir			= AddPropBool(Language(L"�Ӷ���ǰ������"), Language(L"bDirChildEqualNodeDir", L"�Ӷ���ǰ������")));
	// Scale
	CMFCPropertyGridProperty* scale			= new CMFCPropertyGridProperty(Language(L"��������"));
	scale->AddSubItem(bScale				= AddPropBool(Language(L"������Ч"), Language(L"bScale", L"������Ч��")));
	scale->AddSubItem(bScaleBaseRegular			= AddPropBool(Language(L"��������"), Language(L"bScaleBaseRegular", L"�������š�")));
	scale->AddSubItem(fScaleBaseRegularStart			= AddPropFloat(Language(L"���ڿ�ʼ"), Language(L"fScaleBaseRegularStart", L"���ڿ�ʼ��"), false, -100000.0f, 100000.0f));
	scale->AddSubItem(fScaleBaseRegularSpeed			= AddPropFloat(Language(L"�����ٶ�"), Language(L"fScaleBaseRegularSpeed", L"�����ٶȡ�"), false, -100000.0f, 100000.0f));
	scale->AddSubItem(bScaleBaseSin			= AddPropBool(Language(L"����Sin"), Language(L"bScaleBaseSin", L"����Sin��")));
	scale->AddSubItem(fScaleBaseSinStart			= AddPropFloat(Language(L"Sin��ʼ"), Language(L"fScaleBaseSinStart", L"Sin��ʼ��"), false, -100000.0f, 100000.0f));
	scale->AddSubItem(fScaleBaseSinEnd			= AddPropFloat(Language(L"Sin����"), Language(L"fScaleBaseSinEnd", L"Sin������"), false, -100000.0f, 100000.0f));
	scale->AddSubItem(fScaleBaseSinPeriodicTime	= AddPropFloat(Language(L"Sin����ʱ��"), Language(L"fScaleBaseSinPeriodicTime", L"Sin����ʱ�䡣"), false, -100000.0f, 100000.0f));
	//
	scale->AddSubItem(bScaleAdditionX			= AddPropBool(Language(L"��������X"), Language(L"bScaleAdditionX", L"��������X��")));
	scale->AddSubItem(bScaleAdditionY			= AddPropBool(Language(L"��������Y"), Language(L"bScaleAdditionY", L"��������Y��")));
	scale->AddSubItem(bScaleAdditionZ			= AddPropBool(Language(L"��������Z"), Language(L"bScaleAdditionZ", L"��������Z��")));
	scale->AddSubItem(bScaleAdditionRegular			= AddPropBool(Language(L"���Ŷ�������"), Language(L"bScaleAdditionRegular", L"���Ŷ������ӡ�")));
	scale->AddSubItem(fScaleAdditionRegularStart	= AddPropFloat(Language(L"���Ŷ������ӿ�ʼ"), Language(L"fScaleAdditionRegularStart", L"���Ŷ������ӿ�ʼ��"), false, -100000.0f, 100000.0f));
	scale->AddSubItem(fScaleAdditionRegularSpeed	= AddPropFloat(Language(L"���Ŷ��������ٶ�"), Language(L"fScaleAdditionRegularSpeed", L"���Ŷ��������ٶȡ�"), false, -100000.0f, 100000.0f));
	//
	scale->AddSubItem(bScaleAdditionSin			= AddPropBool(Language(L"��������Sin"), Language(L"bScaleAdditionSin", L"��������Sin��")));
	scale->AddSubItem(fScaleAdditionSinStart			= AddPropFloat(Language(L"Sin���ӿ�ʼ"), Language(L"fScaleAdditionSinStart", L"Sin���ӿ�ʼ��"), false, -100000.0f, 100000.0f));
	scale->AddSubItem(fScaleAdditionSinEnd			= AddPropFloat(Language(L"Sin���ӽ���"), Language(L"fScaleAdditionSinEnd", L"Sin���ӽ�����"), false, -100000.0f, 100000.0f));
	scale->AddSubItem(fScaleAdditionSinPeriodicTime	= AddPropFloat(Language(L"Sin���Ӷ���ʱ��"), Language(L"fScaleAdditionSinPeriodicTime", L"Sin���Ӷ���ʱ�䡣"), false, -100000.0f, 100000.0f));
	// Alpha
	CMFCPropertyGridProperty* alpha			= new CMFCPropertyGridProperty(Language(L"͸������"));
	alpha->AddSubItem(eAlphaBlend			= AddPropOption(Language(L"͸��ģʽ"), Language(L"eAlphaBlend", L"͸��ģʽ"), g_typeEffectAlpha));
	alpha->AddSubItem(bAlphaZBuffer			= AddPropBool(Language(L"Z���忪��"), Language(L"bAlphaZBuffer", L"Z���忪����")));
	alpha->AddSubItem(bAlphaRegular			= AddPropBool(Language(L"����͸��"), Language(L"bAlphaRegular", L"����͸����")));
	alpha->AddSubItem(fAlphaRegularStart	= AddPropFloat(Language(L"͸����ʼ"), Language(L"fAlphaRegularStart", L"͸����ʼ��"), false, -100000.0f, 100000.0f));
	alpha->AddSubItem(fAlphaRegularEnd	= AddPropFloat(Language(L"͸������"), Language(L"fAlphaRegularEnd", L"͸��������"), false, -100000.0f, 100000.0f));
	//
	alpha->AddSubItem(bAlphaSin			= AddPropBool(Language(L"͸��Sin"), Language(L"bAlphaSin", L"͸��Sin��")));
	alpha->AddSubItem(fAlphaSinStart	= AddPropFloat(Language(L"͸��Sin��ʼ"), Language(L"fAlphaSinStart", L"͸��Sin��ʼ��"), false, -100000.0f, 100000.0f));
	alpha->AddSubItem(fAlphaSinEnd	= AddPropFloat(Language(L"͸��Sin����"), Language(L"fAlphaSinEnd", L"͸��Sin������"), false, -100000.0f, 100000.0f));
	alpha->AddSubItem(fAlphaSinPeriodicTime	= AddPropFloat(Language(L"͸��Sin����ʱ��"), Language(L"fAlphaSinPeriodicTime", L"͸��Sin����ʱ�䡣"), false, -100000.0f, 100000.0f));
	alpha->AddSubItem(bAlphaColor			= AddPropBool(Language(L"͸����ɫ��Ч"), Language(L"bAlphaColor", L"͸����ɫ��Ч��")));
	alpha->AddSubItem(sAlphaColor			= AddPropColor(Language(L"͸����ɫ"), Language(L"sAlphaColor", L"͸����ɫ��")));
	// AtomicInst
	CMFCPropertyGridProperty* atomic			= new CMFCPropertyGridProperty(Language(L"��������"));
	atomic->AddSubItem(bAtomicInstAnimation			= AddPropBool(Language(L"���ӿ�¡��Ч"), Language(L"bAtomicInstAnimation", L"���ӿ�¡��Ч")));
	atomic->AddSubItem(bAtomicInstTwoSide			= AddPropBool(Language(L"����˫����Ⱦ"), Language(L"bAtomicInstTwoSide", L"����˫����Ⱦ")));
	atomic->AddSubItem(bAtomicInstAniTime			= AddPropBool(Language(L"���Ӷ���ʱ����Ч"), Language(L"bAtomicInstAniTime", L"���Ӷ���ʱ����Ч")));
	atomic->AddSubItem(fAtomicInstAniTime	= AddPropFloat(Language(L"���Ӷ���ʱ��"), Language(L"fAtomicInstAniTime", L"���Ӷ���ʱ�䡣"), false, -100000.0f, 100000.0f));
	m_nodeProp.AddProperty(create);
	m_nodeProp.AddProperty(start);
	m_nodeProp.AddProperty(movemode);
	m_nodeProp.AddProperty(startPos);
	m_nodeProp.AddProperty(straight);
	m_nodeProp.AddProperty(rotate);
	m_nodeProp.AddProperty(gravity);
	m_nodeProp.AddProperty(following);
	m_nodeProp.AddProperty(dirstart);
	m_nodeProp.AddProperty(dirchild);
	m_nodeProp.AddProperty(scale);
	m_nodeProp.AddProperty(alpha);
	m_nodeProp.AddProperty(atomic);
}
