/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#include "StdAfx.h"
#include "GCMFCHelper.h"
#include "GCLanguage.h"
#include "PhantomManager.h"
#include "GCViewBase.h"

VOID	AddTool(CToolTipCtrl& toolTip, CWnd& wnd, const wchar_t* szText)
{
	wnd.EnableToolTips(TRUE);
	toolTip.AddTool(&wnd, szText);
}

VOID	InitTool(CToolTipCtrl& toolTip, CWnd* dlg)
{
	toolTip.Create(dlg);
	toolTip.Activate(TRUE);
	toolTip.SetMaxTipWidth(500);
	toolTip.SetDelayTime(10000, 0);
}

struct MfcConfig
{
	char	name[128];
	int		nValue;
	double	dValue;
	std::string	texts;
};

std::vector<MfcConfig*>		g_configs;

VOID	DestroyConfigs()
{
	for(int i=0;i<g_configs.size();i++)
		delete g_configs[i];
	g_configs.clear();
}

MfcConfig*	FindMfcConfig(const char* szName, BOOL bAdd)
{
	for(int i=0;i<g_configs.size();i++)
	{
		if(stricmp(g_configs[i]->name, szName) == 0)
			return g_configs[i];
	}
	if(!bAdd)
		return 0;
	MfcConfig* mfc = new MfcConfig();
	strcpy(mfc->name, szName);
	mfc->dValue	=	0;
	mfc->nValue	=	0;
	g_configs.push_back(mfc);
	return mfc;
}

BOOL	GetConfigBool(const char* szName, BOOL bDefault)
{
	MfcConfig* mfc	=	FindMfcConfig(szName, FALSE);
	if(!mfc)
		return bDefault;
	return mfc->nValue;
}

VOID	SetConfigBool(const char* szName, BOOL b)
{
	MfcConfig* mfc	=	FindMfcConfig(szName, TRUE);
	mfc->nValue	=	b;
}

INT		GetConfigInt(const char* szName, INT nDefault)
{
	MfcConfig* mfc	=	FindMfcConfig(szName, FALSE);
	if(!mfc)
		return nDefault;
	return mfc->nValue;
}

VOID	SetConfigInt(const char* szName, INT b)
{
	MfcConfig* mfc	=	FindMfcConfig(szName, TRUE);
	mfc->nValue	=	b;
}

double	GetConfigDouble(const char* szName, double dDefault)
{
	MfcConfig* mfc	=	FindMfcConfig(szName, FALSE);
	if(!mfc)
		return dDefault;
	return mfc->dValue;
}

VOID	SetConfigDouble(const char* szName, double b)
{
	MfcConfig* mfc	=	FindMfcConfig(szName, TRUE);
	mfc->dValue	=	b;
}

BOOL	GetConfigText(const char* szName, std::string& ret, const char* szDefault)
{
	MfcConfig* mfc	=	FindMfcConfig(szName, FALSE);
	if(!mfc)
	{
		ret	=	szDefault;
		return false;
	}
	ret	=	mfc->texts.c_str();
	return true;
}

VOID	SetConfigText(const char* szName, const char* szRet)
{
	MfcConfig* mfc	=	FindMfcConfig(szName, TRUE);
	mfc->texts	=	szRet;
}

//
VOID	SaveConfigs(const char* szPath)
{
	FILE* f	=	fopen(szPath, "wb");
	if(!f)
		return;
	const char* szHead	=	"name\tint\tdouble\ttext\r\n";
	fwrite(szHead, strlen(szHead), 1, f);
	char buf[10240];
	for(int i=0;i<g_configs.size();i++)
	{
		MfcConfig* mfc	=	g_configs[i];
		sprintf(buf, "\"%s\"\t%d\t%.08f\t\"%s\"\r\n", mfc->name, mfc->nValue, mfc->dValue, mfc->texts.c_str());
		fwrite(buf, strlen(buf), 1, f);
	}
	fclose(f);
}

VOID	LoadConfigs(const char* szPath)
{
	TableTxt* r = Phantom::loadTable_s(szPath);
	if(!r)
		return;
	for(int i=0;i<r->getNumLine();i++)
	{
		const char* szName	=	r->getLineItem(i, "name");
		const char* szInt	=	r->getLineItem(i, "int");
		const char* szDouble	=	r->getLineItem(i, "double");
		const char* szText	=	r->getLineItem(i, "text");
		if(!szName || !szInt || !szDouble || !szText)
			break;
		MfcConfig* mfc	=	FindMfcConfig(szName, TRUE);
		mfc->nValue		=	atoi(szInt);
		mfc->dValue		=	atof(szDouble);
		mfc->texts		=	szText;
	}
	safe_release(r);
}

VOID	OnMfcScroll(HWND hWnd, INT scBar, INT nSBCode, INT nPos)
{
	int minpos;
	int maxpos;
	GetScrollRange(hWnd, scBar, &minpos, &maxpos); 
	int curpos = GetScrollPos(hWnd, scBar);
	switch (nSBCode)
	{
	case SB_LEFT:
		curpos = minpos;
		break;
	case SB_RIGHT:
		curpos = maxpos;
		break;
	case SB_ENDSCROLL:
		break;
	case SB_LINELEFT:
		if (curpos > minpos)
			curpos--;
		break;
	case SB_LINERIGHT:
		if (curpos < maxpos)
			curpos++;
		break;
	case SB_PAGELEFT:
		{
			SCROLLINFO   info;
			memset(&info, 0, sizeof(info));
			info.cbSize	=	sizeof(info);
			info.fMask	=	SIF_ALL;
			GetScrollInfo(hWnd, scBar, &info);
			if (curpos > minpos)
				curpos = max(minpos, curpos - 100);
		}
		break;
	case SB_PAGERIGHT:
		{
			SCROLLINFO   info;
			memset(&info, 0, sizeof(info));
			info.cbSize	=	sizeof(info);
			info.fMask	=	SIF_ALL;
			GetScrollInfo(hWnd, scBar, &info);
			if (curpos < maxpos)
				curpos = min(maxpos, curpos + 100);
		}
		break;
	case SB_THUMBPOSITION:
		curpos = nPos;
		break;
	case SB_THUMBTRACK:
		curpos = nPos;
		break;
	}
	if(curpos < minpos)
		curpos = minpos;
	else if(curpos >= maxpos)
		curpos	=	maxpos;
	SetScrollPos(hWnd, scBar, curpos, TRUE);
}

VOID	RenderRect(CDC* pDC, const CRect& rc)
{
	pDC->MoveTo(rc.left, rc.top);
	pDC->LineTo(rc.right, rc.top);
	pDC->MoveTo(rc.right, rc.top);
	pDC->LineTo(rc.right, rc.bottom);
	pDC->MoveTo(rc.right, rc.bottom);
	pDC->LineTo(rc.left, rc.bottom);
	pDC->MoveTo(rc.left, rc.bottom);
	pDC->LineTo(rc.left, rc.top);
}

VOID	CopyTextToClipboard(const char* szText)
{
	if( OpenClipboard( NULL ))
	{
		int len	=	(int)strlen(szText) + 1;
		EmptyClipboard();
		HGLOBAL hBlock = GlobalAlloc( GMEM_MOVEABLE, len );
		if( hBlock )
		{
			char *pwszText = (char*)GlobalLock( hBlock );
			memcpy(pwszText, szText, len);
			GlobalUnlock( hBlock );
			SetClipboardData( CF_TEXT, hBlock );
		}
		CloseClipboard();
		if( hBlock )
			GlobalFree( hBlock );
	}
}

const wchar_t*	AToW(const char* szText, wchar_t * buffer, int bufferLength)
{
	buffer[::MultiByteToWideChar(CP_ACP, 0, szText, -1, buffer, bufferLength)] = 0;
	return buffer;
}

const char*		WToA(const wchar_t* szText, char * buffer, int bufferLength)
{
	buffer[::WideCharToMultiByte(CP_ACP, 0, szText, -1, buffer, bufferLength, 0, 0)] = 0;
	return buffer;
}

const wchar_t*	GetImageFilter()
{
	return /*Language(L"ͼƬ�ļ���ʽ_˵��",*/ (L"����ͼƬ�ļ�(*.dds;*.tga;*.png;*.jpg;*.bmp;*.gif;*.locki)|*.dds;*.tga;*.png;*.jpg;*.bmp;*.gif;*.locki|DDS�ļ�(*.dds)|*.dds|tga�ļ�(*.tga)|*.tga|png�ļ�(*.png)|*.png|jpg�ļ�(*.jpg)|*.jpg|bmp�ļ�(*.bmp)|*.bmp|bmp�ļ�(*.gif)|*.gif|locki�ļ�(*.locki)|*.locki||");
}

const wchar_t*	GetSoundFilter()
{
	return /*Language(L"�����ļ���ʽ_˵��",*/ (L"����ý���ļ�(*.wav;*.ogg;)|*.wav;*.ogg|WAV�ļ�(*.wav)|*.wav|OGG�ļ�(*.ogg)|*.ogg||");
}

const wchar_t*	GetMusicFilter()
{
	return /*Language(L"�����ļ���ʽ_˵��",*/ (L"����ý���ļ�(*.wav;*.ogg;*.mp3;*.mid)|*.wav;*.ogg;*.mp3;*.mid|WAV�ļ�(*.wav)|*.wav|OGG�ļ�(*.ogg)|*.ogg|MP3�ļ�(*.mp3)|*.mp3||MID�ļ�(*.mid)|*.mid||");
}

const wchar_t*	GetMeshFilter()
{
	return /*Language(L"ģ���ļ���ʽ_˵��",*/ (L"����ý���ļ�(*.rpgmesh;*.geoms;*.pakmesh)|*.rpgmesh;*.geoms;*.pakmesh||");
}

const wchar_t*	GetSceneObjectFilter()
{
	return /*Language(L"���������ļ�_˵��",*/ (L"���������ļ�(*.wav;*.ogg;*.rpg2D;*.z_rpg2D)|*.wav;*.ogg;*.rpg2D;*.z_rpg2D||");
}

const wchar_t*	GetScene3DObjectFilter()
{
	return /*Language(L"���������ļ�_˵��",*/ (L"���������ļ�(*.wav;*.ogg;*.rpgmesh;*.pakmesh;*.mp3;*.mid;*.wmv;*.geoms;*.rpgunit;*.z_rpg3D)|*.wav;*.ogg;*.rpgmesh;*.pakmesh;*.mp3;*.mid;*.wmv;*.geoms;*.rpgunit;*.z_rpg3D||");
}

const wchar_t*	GetPhantomFilters()
{
	static wchar_t szPath[1024] = {0};
	if(!szPath[0])
	{
		swprintf(szPath, L"%s|*.pakmesh;*.pakui;*.rpgmesh;*.rpgui;*.rpgscene;*.lua|%s|*.pakmesh;*rpgunit;*.geoms;*.rpgExp;logic_system.txt;*.rpgProj;*.rpg2d;*.rpg2ds;*.obj;*.zui;*.lua;*.pakui;*.z_rpg3D;*.z_rpg2D;*.z_rpgLogic;*.z_rpg3Ds;*.z_rpg2Ds;*.z_rpgCur|%s|*.rpgmesh;*.geoms;*.obj_xml;*.ogg;*.mp3;*.wav;*.mid;*.rpgEffect;*.obj|%s|*.zui;*.rpgui|%s|*.rpg2D|%s|*.rpgunit|logic_system.txt|logic_system.txt|*.*|*.*||"
			, Language(L"AllOpenFiles", L"�����ļ�"), Language(L"ReportFileType", L"�򿪷������ļ�(ֻ��)"), Language(L"GeometryFileType", L"ģ���ļ�")
			, Language(L"UIFileType", L"�����ļ�"), Language(L"Unit2DFileType", L"2D�����ļ�"), Language(L"Unit3DFileType", L"3D�����ļ�"));
	}
	return szPath;
}

CTypeOption::CTypeOption()
{
}

VOID				CTypeOption::AddOption(const wchar_t* szText, INT nType, BOOL bDefault)
{
	this->m_options.push_back(TypeOption(szText, nType));
	if(bDefault)
		m_default	=	TypeOption(szText, nType);
}

INT					CTypeOption::operator[](const wchar_t* szText)
{
	for(int i=0;i<m_options.size();i++)
		if(wcsicmp(m_options[i].text, szText) == 0)
			return m_options[i].index;
	return m_default.index;
}

const wchar_t*		CTypeOption::operator[](INT nIndex)
{
	for(int i=0;i<m_options.size();i++)
		if(m_options[i].index == nIndex)
			return m_options[i].text;
	return m_default.text;
}

VOID				CTypeOption::RemoveAll()
{
	m_options.clear();
}

CTypeOption		g_typeTemplate;
CTypeOption		g_typeFilter;
CTypeOption		g_typeCull;
CTypeOption		g_typeAlpha;
CTypeOption		g_typeBlend;
CTypeOption		g_typeLodLevel;
CTypeOption		g_typeCallIndex;
CTypeOption		g_typeDialogAlignLR;
CTypeOption		g_typeDialogAlignTB;
CTypeOption		g_typeToolTipAlign;
CTypeOption		g_typeControlLayer;
CTypeOption		g_typeTextAlignLR;
CTypeOption		g_typeTextAlignTB;
CTypeOption		g_typeAlignModeW;
CTypeOption		g_typeAlignModeH;
CTypeOption		g_typeProgress;
CTypeOption		g_typeColorOP;
CTypeOption		g_typeControlGroup;
CTypeOption		g_typeControlButtons;
CTypeOption		g_type2DUnitAngle;
CTypeOption		g_type2DUnitSide;
CTypeOption		g_type2DPickEnable;
CTypeOption		g_typeDefault;
CTypeOption		g_typeLightType;
CTypeOption		g_typeMouseButton;
CTypeOption		g_typeInputKey;
CTypeOption		g_typeParticleType;
CTypeOption		g_typeEmissionType;
CTypeOption		g_typeUnitActionType;
CTypeOption		g_typeShaderType;
CTypeOption		g_typeShadowMap;
CTypeOption		g_typeSoftPCF;
CTypeOption		g_typeSoftBlur;
CTypeOption		g_typeCascadeMap;
CTypeOption		g_typeViewScale;
CTypeOption		g_typeBox2DBodyType;
CTypeOption		g_typeBox2DShapeType;
CTypeOption		g_typeBox2DJointType;
CTypeOption		g_typeUnitAngleType;
//
CTypeOption		g_typeEffectCreate;
CTypeOption		g_typeEffectStart;
CTypeOption		g_typeEffectMove;
CTypeOption		g_typeEffectAlpha;
CTypeOption		g_typeGroupType;
CTypeOption		g_typeGroupDiffuse;
CTypeOption		g_typeTableEvents;
CTypeOption		g_typeTableRoles;
CTypeOption		g_typeFogMode;
CTypeOption		g_typeCenterObj;
enum DIALOG_ALIGN{
	DIALOG_ALIGN_NONE	=	1,
	DIALOG_ALIGN_LEFT,
	DIALOG_ALIGN_CENTER,
	DIALOG_ALIGN_RIGHT,
	DIALOG_ALIGN_TOP,
	DIALOG_ALIGN_BOTTOM,
};
VOID			InitTypeOptions()
{
	Phantom::Config* cfg = Phantom::GetGameMgr()->SearchConfig("event_table");
	if(cfg){
		for(int i=0;i<cfg->GetLineCount();i++){
			Phantom::ConfigLine* line = cfg->GetLine(i);
			g_typeTableEvents.AddOption(Wutf8(line->GetLineName()), line->GetLineID());
		}
	}
	cfg = Phantom::GetGameMgr()->SearchConfig("role_table");
	if(cfg){
		for(int i=0;i<cfg->GetLineCount();i++){
			Phantom::ConfigLine* line = cfg->GetLine(i);
			g_typeTableRoles.AddOption(Wutf8(line->GetLineName()), line->GetLineID());
		}
	}
	g_typeFilter.AddOption(Language(L"��"), Phantom::TextureFilter_Point, TRUE);
	g_typeFilter.AddOption(Language(L"����"), Phantom::TextureFilter_Linear);
	//g_typeFilter.AddOption(Language(L"��������"), Enum::TEXF_ANISOTROPIC);
	g_typeFogMode.AddOption(Language(L"3D����"), Phantom::FogMode_Fog3D, TRUE);
	g_typeFogMode.AddOption(Language(L"3D����+�Ҷȱ仯"), Phantom::FogMode_Fog3DGray);
	g_typeFogMode.AddOption(Language(L"3D����-��ֵ"), Phantom::FogMode_Fog3DSub);
	g_typeFogMode.AddOption(Language(L"3D����-���ض���"), Phantom::FogMode_Fog3DHide);
	g_typeFogMode.AddOption(Language(L"2D����"), Phantom::FogMode_Fog2D);
	g_typeFogMode.AddOption(Language(L"2D����+�Ҷȱ仯"), Phantom::FogMode_Fog2DGray);
	g_typeFogMode.AddOption(Language(L"2D����-��ֵ"), Phantom::FogMode_Fog2DSub);
	g_typeFogMode.AddOption(Language(L"2D����-���ض���"), Phantom::FogMode_Fog2DHide);
	//
	g_typeLightType.AddOption(Language(L"���"), Phantom::SceneLight::LightType_Omni, TRUE);
	g_typeLightType.AddOption(Language(L"�����"), Phantom::SceneLight::LightType_Spot);
	//g_typeLightType.AddOption(Language(L"����"), Phantom::SceneLight::LightType_Direction);
	//ETIME_CREATE, EONECREATE, ECONTINUE
	//g_typeEffectCreate.AddOption(Language(L"��ʱ�䴴��"), Phantom::ETIME_CREATE, TRUE);
	//g_typeEffectCreate.AddOption(Language(L"����һ��"), Phantom::EONECREATE);
	//g_typeEffectCreate.AddOption(Language(L"��������"), Phantom::ECONTINUE);
	////EPOINT_EF, ELINE_EF, EPLANE_EF, ESPACE_EF
	//g_typeEffectStart.AddOption(Language(L"��"), Phantom::EPOINT_EF, TRUE);
	//g_typeEffectStart.AddOption(Language(L"��"), Phantom::ELINE_EF);
	//g_typeEffectStart.AddOption(Language(L"��"), Phantom::EPLANE_EF);
	//g_typeEffectStart.AddOption(Language(L"��"), Phantom::ESPACE_EF);
	////EEXPANSION, ECONCENTRATION, ERANDOM, EUSER
	//g_typeEffectMove.AddOption(Language(L"����"), Phantom::EEXPANSION);
	//g_typeEffectMove.AddOption(Language(L"Ũ��"), Phantom::ECONCENTRATION);
	//g_typeEffectMove.AddOption(Language(L"���"), Phantom::ERANDOM);
	////EBLEND_NORMAL, EBLEND_ALPHAKEY, EBLEND_ALPHA, EBLEND_ALPHA_ADD, EBLEND_MODULATE, EBLEND_FORCE_ADD, EBLEND_FORCE_SUBTRACT
	//g_typeEffectAlpha.AddOption(Language(L"����"), Phantom::EBLEND_NORMAL);
	//g_typeEffectAlpha.AddOption(Language(L"ALPHAKEY"), Phantom::EBLEND_ALPHAKEY);
	//g_typeEffectAlpha.AddOption(Language(L"ALPHA"), Phantom::EBLEND_ALPHA);
	//g_typeEffectAlpha.AddOption(Language(L"ALPHA_ADD"), Phantom::EBLEND_ALPHA_ADD);
	//g_typeEffectAlpha.AddOption(Language(L"MODULATE"), Phantom::EBLEND_MODULATE);
	//g_typeEffectAlpha.AddOption(Language(L"FORCE_ADD"), Phantom::EBLEND_FORCE_ADD);
	//g_typeEffectAlpha.AddOption(Language(L"FORCE_SUBTRACT"), Phantom::EBLEND_FORCE_SUBTRACT);
	//
	g_typeCull.AddOption(Language(L"A��"), Phantom::CullMode_CCW);
	g_typeCull.AddOption(Language(L"B��"), Phantom::CullMode_CW);
	g_typeCull.AddOption(Language(L"˫��"), Phantom::CullMode_Double, TRUE);
	//
	g_typeAlpha.AddOption(Language(L"�ر�"), Phantom::AlphaMode_None, TRUE);
	g_typeAlpha.AddOption(Language(L"0,1����"), Phantom::AlphaMode_Test);
	g_typeAlpha.AddOption(Language(L"���"), Phantom::AlphaMode_Blend);
	//
	//g_typeShaderType.AddOption(Language(L"Ĭ��"),		GeometryShaderType_Default, true);
	//g_typeShaderType.AddOption(Language(L"��չ1"),		GeometryShaderType_Extend1);
	//g_typeShaderType.AddOption(Language(L"��չ2"),		GeometryShaderType_Extend2);
	//g_typeShaderType.AddOption(Language(L"��չ3"),		GeometryShaderType_Extend3);
	//g_typeShaderType.AddOption(Language(L"��չ4"),		GeometryShaderType_Extend4);
	//g_typeShaderType.AddOption(Language(L"��չ5"),		GeometryShaderType_Extend5);
	//g_typeShaderType.AddOption(Language(L"��չ6"),		GeometryShaderType_Extend6);
	//g_typeShaderType.AddOption(Language(L"��չ7"),		GeometryShaderType_Extend7);
	//g_typeShaderType.AddOption(Language(L"��չ8"),		GeometryShaderType_Extend8);
	//
	g_typeMouseButton.AddOption(Language(L"��"), MouseButton_None, TRUE);
	g_typeMouseButton.AddOption(Language(L"���"), MouseButton_Left);
	g_typeMouseButton.AddOption(Language(L"�Ҽ�"), MouseButton_Right);
	g_typeMouseButton.AddOption(Language(L"�м�"), MouseButton_Middle);
	//
	g_typeGroupType.AddOption(Language(L"װ��ģ��"), Phantom::MeshData::MeshType_StaticMesh, TRUE);
	g_typeGroupType.AddOption(Language(L"��������"), Phantom::MeshData::MeshType_SceneUnit);
	g_typeGroupType.AddOption(Language(L"��ɫ"), Phantom::MeshData::MeshType_Role);
	//
	g_typeUnitActionType.AddOption(Language(L"��"),			Phantom::ActionType_None, TRUE);
	g_typeUnitActionType.AddOption(Language(L"Ĭ��"),		Phantom::ActionType_Idle);
	g_typeUnitActionType.AddOption(Language(L"��·"),		Phantom::ActionType_Walk);
	g_typeUnitActionType.AddOption(Language(L"�ܲ�"),		Phantom::ActionType_Run);
	g_typeUnitActionType.AddOption(Language(L"��Ծ"),		Phantom::ActionType_Jump);
	g_typeUnitActionType.AddOption(Language(L"������"),		Phantom::ActionType_Hit);
	g_typeUnitActionType.AddOption(Language(L"����"),		Phantom::ActionType_Die);
	g_typeUnitActionType.AddOption(Language(L"����"),		Phantom::ActionType_Attack);
	g_typeUnitActionType.AddOption(Language(L"����"),		Phantom::ActionType_Hide);
	g_typeUnitActionType.AddOption(Language(L"����"),		Phantom::ActionType_Down);

	g_typeUnitActionType.AddOption(Language(L"Ĭ��2"),		Phantom::ActionType_Idle2);
	g_typeUnitActionType.AddOption(Language(L"��·2"),		Phantom::ActionType_Walk2);
	g_typeUnitActionType.AddOption(Language(L"�ܲ�2"),		Phantom::ActionType_Run2);
	g_typeUnitActionType.AddOption(Language(L"��Ծ2"),		Phantom::ActionType_Jump2);
	g_typeUnitActionType.AddOption(Language(L"������2"),		Phantom::ActionType_Hit2);
	g_typeUnitActionType.AddOption(Language(L"����2"),		Phantom::ActionType_Die2);
	g_typeUnitActionType.AddOption(Language(L"����2"),		Phantom::ActionType_Attack2);

	g_typeUnitActionType.AddOption(Language(L"Ĭ��3"),		Phantom::ActionType_Idle3);
	g_typeUnitActionType.AddOption(Language(L"��·3"),		Phantom::ActionType_Walk3);
	g_typeUnitActionType.AddOption(Language(L"�ܲ�3"),		Phantom::ActionType_Run3);
	g_typeUnitActionType.AddOption(Language(L"��Ծ3"),		Phantom::ActionType_Jump3);
	g_typeUnitActionType.AddOption(Language(L"������3"),		Phantom::ActionType_Hit3);
	g_typeUnitActionType.AddOption(Language(L"����3"),		Phantom::ActionType_Die3);
	g_typeUnitActionType.AddOption(Language(L"����3"),		Phantom::ActionType_Attack3);

	g_typeUnitActionType.AddOption(Language(L"����1"),		Phantom::ActionType_Other1);
	g_typeUnitActionType.AddOption(Language(L"����2"),		Phantom::ActionType_Other2);
	g_typeUnitActionType.AddOption(Language(L"����3"),		Phantom::ActionType_Other3);
	g_typeUnitActionType.AddOption(Language(L"����4"),		Phantom::ActionType_Other4);
	g_typeUnitActionType.AddOption(Language(L"����5"),		Phantom::ActionType_Other5);
	g_typeUnitActionType.AddOption(Language(L"����6"),		Phantom::ActionType_Other6);
	g_typeUnitActionType.AddOption(Language(L"����7"),		Phantom::ActionType_Other7);
	g_typeUnitActionType.AddOption(Language(L"����8"),		Phantom::ActionType_Other8);
	g_typeUnitActionType.AddOption(Language(L"����9"),		Phantom::ActionType_Other9);
	for(int i=0;i<=DIFFUSE_TEXTURE_COUNT;i++)
	{
		wchar_t buf[128];
		swprintf(buf, L"%s %d", Language(L"����"), i);
		g_typeGroupDiffuse.AddOption(buf, i);
	}
	//
	g_typeBlend.AddOption(Language(L"Zero"), Phantom::BlendMode_ZERO, TRUE);
	g_typeBlend.AddOption(Language(L"One"), Phantom::BlendMode_ONE);
	g_typeBlend.AddOption(Language(L"SrcColor"), Phantom::BlendMode_SRCCOLOR);
	g_typeBlend.AddOption(Language(L"InvSrcColor"), Phantom::BlendMode_INVSRCCOLOR);
	g_typeBlend.AddOption(Language(L"SrcAlpha"), Phantom::BlendMode_SRCALPHA);
	g_typeBlend.AddOption(Language(L"InvSrcAlpha"), Phantom::BlendMode_INVSRCALPHA);
	g_typeBlend.AddOption(Language(L"DestAlpha"), Phantom::BlendMode_DESTALPHA);
	g_typeBlend.AddOption(Language(L"InvDestAlpha"), Phantom::BlendMode_INVDESTALPHA);
	g_typeBlend.AddOption(Language(L"DestColor"), Phantom::BlendMode_DESTCOLOR);
	g_typeBlend.AddOption(Language(L"InvDestColor"), Phantom::BlendMode_INVDESTCOLOR);
	g_typeBlend.AddOption(Language(L"SrcAlphaSat"), Phantom::BlendMode_SRCALPHASAT);
	g_typeBlend.AddOption(Language(L"BothSrcAlpha"), Phantom::BlendMode_BOTHSRCALPHA);
	g_typeBlend.AddOption(Language(L"BothInvSrcAlpha"), Phantom::BlendMode_BOTHINVSRCALPHA);
	//g_typeBlend.AddOption(Language(L"BlendFactor"), Phantom::BlendMode_BLENDFACTOR);
	//g_typeBlend.AddOption(Language(L"InvBlendFactor"), Phantom::BlendMode_INVBLENDFACTOR);
	//
	g_typeLodLevel.AddOption(Language(L"�Զ�"), -1, TRUE);
	g_typeLodLevel.AddOption(Language(L"����-1"), 0);
	g_typeLodLevel.AddOption(Language(L"����-2"), 1);
	g_typeLodLevel.AddOption(Language(L"����-3"), 2);
	g_typeLodLevel.AddOption(Language(L"����-4"), 3);
	g_typeLodLevel.AddOption(Language(L"����-5"), 4);
	g_typeLodLevel.AddOption(Language(L"����-6"), 5);
	//
	g_typeViewScale.AddOption(Language(L"1"), 1, TRUE);
	g_typeViewScale.AddOption(Language(L"1/2"), 2);
	g_typeViewScale.AddOption(Language(L"1/4"), 4);
	g_typeViewScale.AddOption(Language(L"1/8"), 8);
	g_typeViewScale.AddOption(Language(L"1/16"), 16);
	g_typeViewScale.AddOption(Language(L"1/32"), 32);
	//
	g_typeShadowMap.AddOption(Language(L"512x512"), 512);
	g_typeShadowMap.AddOption(Language(L"1024x1024"), 1024, true);
	g_typeShadowMap.AddOption(Language(L"2048x2048"), 2048);
	g_typeShadowMap.AddOption(Language(L"4096x4096"), 4096);
	g_typeShadowMap.AddOption(Language(L"8192x8192"), 8192);
	//
	g_typeSoftPCF.AddOption(Language(L"�ر�"), 0, true);
	g_typeSoftPCF.AddOption(Language(L"9�ι���"), 1);
	g_typeSoftPCF.AddOption(Language(L"25�ι���"), 2);
	//g_typeSoftPCF.AddOption(Language(L"49�ι���"), Phantom::PCF_7x7);
	//
#ifdef USE_BOX
	g_typeBox2DBodyType.AddOption(Language(L"��̬����"), b2_staticBody);
	g_typeBox2DBodyType.AddOption(Language(L"�˶�����"), b2_kinematicBody);
	g_typeBox2DBodyType.AddOption(Language(L"��̬����"), b2_dynamicBody);

	g_typeBox2DShapeType.AddOption(Language(L"Բ"), b2Shape::e_circle);
	g_typeBox2DShapeType.AddOption(Language(L"����"), b2Shape::e_edge);
	g_typeBox2DShapeType.AddOption(Language(L"�����"), b2Shape::e_polygon);
	g_typeBox2DShapeType.AddOption(Language(L"����"), b2Shape::e_chain);
	g_typeBox2DShapeType.AddOption(Language(L"����"), Phantom::B2ShapeData::e_polygon_box);
	//
	g_typeBox2DJointType.AddOption(Language(L"��ת����revolute"), e_revoluteJoint);
	g_typeBox2DJointType.AddOption(Language(L"�⾵����prismatic"), e_prismaticJoint);
	g_typeBox2DJointType.AddOption(Language(L"�������distance"), e_distanceJoint);
	g_typeBox2DJointType.AddOption(Language(L"���ֿ���pulley"), e_pulleyJoint);
	g_typeBox2DJointType.AddOption(Language(L"������mouse"), e_mouseJoint);
	g_typeBox2DJointType.AddOption(Language(L"���ֿ���gear"), e_gearJoint);
	g_typeBox2DJointType.AddOption(Language(L"�ֿ���wheel"), e_wheelJoint);
	g_typeBox2DJointType.AddOption(Language(L"���ӿ���weld"), e_weldJoint);
	g_typeBox2DJointType.AddOption(Language(L"Ħ������friction"), e_frictionJoint);
	g_typeBox2DJointType.AddOption(Language(L"������rope"), e_ropeJoint);
#endif
	//
	//g_typeSoftBlur.AddOption(Language(L"�ر�"), SHADOW_BLUR_DISABLE, true);
	//g_typeSoftBlur.AddOption(Language(L"1��"), SHADOW_BLUR_1);
	//g_typeSoftBlur.AddOption(Language(L"2��"), SHADOW_BLUR_2);
	//g_typeSoftBlur.AddOption(Language(L"3��"), SHADOW_BLUR_3);
	//
	g_typeCascadeMap.AddOption(Language(L"����Ӱ[�Ϳ���]"), 0, true);
	g_typeCascadeMap.AddOption(Language(L"������Ӱ[�߿���]"), 1);
	g_typeCascadeMap.AddOption(Language(L"������Ӱ[���߿���]"), 2);
	//
	g_typeDialogAlignLR.AddOption(Language(L"��"), DIALOG_ALIGN_NONE, TRUE);
	g_typeDialogAlignLR.AddOption(Language(L"��"), DIALOG_ALIGN_LEFT);
	g_typeDialogAlignLR.AddOption(Language(L"����"), DIALOG_ALIGN_CENTER);
	g_typeDialogAlignLR.AddOption(Language(L"��"), DIALOG_ALIGN_RIGHT);
	//
	g_typeDialogAlignTB.AddOption(Language(L"��"), DIALOG_ALIGN_NONE, TRUE);
	g_typeDialogAlignTB.AddOption(Language(L"��"), DIALOG_ALIGN_TOP);
	g_typeDialogAlignTB.AddOption(Language(L"����"), DIALOG_ALIGN_CENTER);
	g_typeDialogAlignTB.AddOption(Language(L"��"), DIALOG_ALIGN_BOTTOM);
	//
	g_typeUnitAngleType.AddOption(Language(L"��"), Phantom::UIControl::AngleMode_None);
	g_typeUnitAngleType.AddOption(Language(L"8��������Ч"), Phantom::UIControl::AngleMode_8);
	g_typeUnitAngleType.AddOption(Language(L"��������"), Phantom::UIControl::AngleMode_LRTB);
	g_typeUnitAngleType.AddOption(Language(L"���ϣ����£����ϣ�����"), Phantom::UIControl::AngleMode_XLRTB);
	//g_typeToolTipAlign.AddOption(Language(L"��"), POPUP_LEFT);
	//g_typeToolTipAlign.AddOption(Language(L"��"), POPUP_TOP, TRUE);
	//g_typeToolTipAlign.AddOption(Language(L"��"), POPUP_RIGHT);
	//g_typeToolTipAlign.AddOption(Language(L"��"), POPUP_BOTTOM);
	//g_typeToolTipAlign.AddOption(Language(L"��"), POPUP_NONE);
	//g_typeToolTipAlign.AddOption(Language(L"����"), POPUP_LEFT_TOP);
	//g_typeToolTipAlign.AddOption(Language(L"����"), POPUP_RIGHT_TOP);
	//g_typeToolTipAlign.AddOption(Language(L"����"), POPUP_LEFT_BOTTOM);
	//g_typeToolTipAlign.AddOption(Language(L"����"), POPUP_RIGHT_BOTTOM);
	//
	for(int i=0;i<20;i++)
	{
		wchar_t buf[128];
		swprintf(buf, L"LayerLow%d", i + 1);
		g_typeControlLayer.AddOption(buf, i, i==0);
	}
	for(int i=20;i<50;i++)
	{
		wchar_t buf[128];
		swprintf(buf, L"Layer%d", i + 1);
		g_typeControlLayer.AddOption(buf, i, i==0);
	}
	//
	for(int i=0;i<50;i++)
	{
		wchar_t buf[128];
		swprintf(buf, L"Group%d", i + 1);
		g_typeControlGroup.AddOption(buf, i, i==0);
	}
	//
	g_typeCallIndex.AddOption(Language(L"���Զ�����"), -1, true);
	for(int i=0;i<50;i++)
	{
		wchar_t buf[128];
		swprintf(buf, L"index%d", i + 1);
		g_typeCallIndex.AddOption(buf, i);
	}
	//
	g_typeTextAlignLR.AddOption(Language(L"��"), DT_LEFT, TRUE);
	g_typeTextAlignLR.AddOption(Language(L"����"), DT_CENTER);
	g_typeTextAlignLR.AddOption(Language(L"��"), DT_RIGHT);
	g_typeTextAlignTB.AddOption(Language(L"��"), DT_TOP, TRUE);
	g_typeTextAlignTB.AddOption(Language(L"����"), DT_VCENTER);
	g_typeTextAlignTB.AddOption(Language(L"��"), DT_BOTTOM);
	g_typeAlignModeW.AddOption(Language(L"��������"), 0);
	g_typeAlignModeW.AddOption(Language(L"�����"), 1);
	g_typeAlignModeW.AddOption(Language(L"���ж���"), 2);
	g_typeAlignModeW.AddOption(Language(L"�Ҷ���"), 3);
	g_typeAlignModeW.AddOption(Language(L"�����߶���"), 4);
	g_typeAlignModeH.AddOption(Language(L"��������"), 0);
	g_typeAlignModeH.AddOption(Language(L"�϶���"), 1);
	g_typeAlignModeH.AddOption(Language(L"���ж���"), 2);
	g_typeAlignModeH.AddOption(Language(L"�¶���"), 3);
	g_typeAlignModeH.AddOption(Language(L"�����߶���"), 4);
	//
	g_typeProgress.AddOption(Language(L"����"), Phantom::UIProgressType_HORZ, TRUE);
	g_typeProgress.AddOption(Language(L"����"), Phantom::UIProgressType_VERT);
	g_typeProgress.AddOption(Language(L"ת��"), Phantom::UIProgressType_SKILL);
	//
	g_typeControlButtons.AddOption(Language(L"��ͨ��ť"), BUTTON_TYPE_NORMAL, TRUE);
	g_typeControlButtons.AddOption(Language(L"Ĭ�ϰ�ť"), BUTTON_TYPE_OK);
	g_typeControlButtons.AddOption(Language(L"ȡ����ť"), BUTTON_TYPE_CANCEL);
	//
	//g_typeColorOP.AddOption(Language(L"DISABLE"), Phantom::TOP_DISABLE, TRUE);
	//g_typeColorOP.AddOption(Language(L"SELECTARG1 "), Phantom::TOP_SELECTARG1 );
	//g_typeColorOP.AddOption(Language(L"SELECTARG2 "), Phantom::TOP_SELECTARG2 );
	//g_typeColorOP.AddOption(Language(L"MODULATE "), Phantom::TOP_MODULATE );
	//g_typeColorOP.AddOption(Language(L"MODULATE2X "), Phantom::TOP_MODULATE2X );
	//g_typeColorOP.AddOption(Language(L"MODULATE4X "), Phantom::TOP_MODULATE4X );
	//g_typeColorOP.AddOption(Language(L"ADD "), Phantom::TOP_ADD );
	//g_typeColorOP.AddOption(Language(L"ADDSIGNED "), Phantom::TOP_ADDSIGNED );
	//g_typeColorOP.AddOption(Language(L"ADDSIGNED2X "), Phantom::TOP_ADDSIGNED2X );
	//g_typeColorOP.AddOption(Language(L"SUBTRACT "), Phantom::TOP_SUBTRACT );
	//g_typeColorOP.AddOption(Language(L"ADDSMOOTH "), Phantom::TOP_ADDSMOOTH );
	//g_typeColorOP.AddOption(Language(L"BLENDDIFFUSEALPHA "), Phantom::TOP_BLENDDIFFUSEALPHA );
	//g_typeColorOP.AddOption(Language(L"BLENDTEXTUREALPHA "), Phantom::TOP_BLENDTEXTUREALPHA );
	//g_typeColorOP.AddOption(Language(L"BLENDFACTORALPHA "), Phantom::TOP_BLENDFACTORALPHA );
	//g_typeColorOP.AddOption(Language(L"BLENDTEXTUREALPHAPM "), Phantom::TOP_BLENDTEXTUREALPHAPM );
	//g_typeColorOP.AddOption(Language(L"BLENDCURRENTALPHA "), Phantom::TOP_BLENDCURRENTALPHA );
	//g_typeColorOP.AddOption(Language(L"PREMODULATE "), Phantom::TOP_PREMODULATE );
	//g_typeColorOP.AddOption(Language(L"MODULATEALPHA_ADDCOLOR "), Phantom::TOP_MODULATEALPHA_ADDCOLOR );
	//g_typeColorOP.AddOption(Language(L"MODULATECOLOR_ADDALPHA "), Phantom::TOP_MODULATECOLOR_ADDALPHA );
	//g_typeColorOP.AddOption(Language(L"MODULATEINVALPHA_ADDCOLOR "), Phantom::TOP_MODULATEINVALPHA_ADDCOLOR );
	//g_typeColorOP.AddOption(Language(L"MODULATEINVCOLOR_ADDALPHA "), Phantom::TOP_MODULATEINVCOLOR_ADDALPHA );
	//g_typeColorOP.AddOption(Language(L"BUMPENVMAP "), Phantom::TOP_BUMPENVMAP );
	//g_typeColorOP.AddOption(Language(L"BUMPENVMAPLUMINANCE "), Phantom::TOP_BUMPENVMAPLUMINANCE );
	//g_typeColorOP.AddOption(Language(L"DOTPRODUCT3 "), Phantom::TOP_DOTPRODUCT3 );
	//g_typeColorOP.AddOption(Language(L"MULTIPLYADD "), Phantom::TOP_MULTIPLYADD );
	//g_typeColorOP.AddOption(Language(L"LERP "), Phantom::TOP_LERP );
	//
	g_type2DUnitAngle.AddOption(Language(L"��"), Phantom::Unit2DAngle_Bottom, true );
	g_type2DUnitAngle.AddOption(Language(L"����"), Phantom::Unit2DAngle_LeftBottom);
	g_type2DUnitAngle.AddOption(Language(L"��"), Phantom::Unit2DAngle_Left);
	g_type2DUnitAngle.AddOption(Language(L"����"), Phantom::Unit2DAngle_LeftTop);
	g_type2DUnitAngle.AddOption(Language(L"��"), Phantom::Unit2DAngle_Top);
	g_type2DUnitAngle.AddOption(Language(L"����"), Phantom::Unit2DAngle_RightTop);
	g_type2DUnitAngle.AddOption(Language(L"��"), Phantom::Unit2DAngle_Right);
	g_type2DUnitAngle.AddOption(Language(L"����"), Phantom::Unit2DAngle_RightBottom);
	////
	//g_type2DUnitSide.AddOption(Language(L"ʵ���"), UnitRenderSide_Body, true );
	//g_type2DUnitSide.AddOption(Language(L"���ز�"), UnitRenderSide_Bottom);
	//g_type2DUnitSide.AddOption(Language(L"��߲�"), UnitRenderSide_Top);
	//
	//g_type2DPickEnable.AddOption(Language(L"�����Ч"), Phantom::Unit2DPick_None, true );
	//g_type2DPickEnable.AddOption(Language(L"�����������"), Unit2DPick_Rect);
	//g_type2DPickEnable.AddOption(Language(L"���ͼƬ����"), Unit2DPick_Pixel);
	//
	g_typeParticleType.AddOption(Language(L"Billboard"), SHOW_Particle_Billboard, true );
	g_typeParticleType.AddOption(Language(L"Cameraboard"), SHOW_Particle_Cameraboard);
	g_typeParticleType.AddOption(Language(L"XBoard"), SHOW_Particle_XBoard);
	g_typeParticleType.AddOption(Language(L"YBoard"), SHOW_Particle_YBoard);
	g_typeParticleType.AddOption(Language(L"ZBoard"), SHOW_Particle_ZBoard);
	g_typeParticleType.AddOption(Language(L"ZBoardScene"), SHOW_Particle_ZBoardScene);
	g_typeParticleType.AddOption(Language(L"DirectionXY"), SHOW_Particle_DirectionXY);
	g_typeParticleType.AddOption(Language(L"DirectionYZ"), SHOW_Particle_DirectionYZ);
	g_typeParticleType.AddOption(Language(L"DirectionZX"), SHOW_Particle_DirectionZX);
	g_typeParticleType.AddOption(Language(L"DirectionXYZ"), SHOW_Particle_DirectionXYZ);
	g_typeParticleType.AddOption(Language(L"BillboardXY"), SHOW_Particle_BillboardXY);
	//g_typeParticleType.AddOption(Language(L"BindDirection"), SHOW_Particle_BindDirection);
	//
	g_typeEmissionType.AddOption(Language(L"ʹ�þ������"), Phantom::EmissionType_Matrix, true);
	g_typeEmissionType.AddOption(Language(L"������������"), Phantom::EmissionType_Self);
	//g_typeEmissionType.AddOption(Language(L"�󶨵�֮���γ�һ����"), EmissionType_BindPoint);
	//
}
