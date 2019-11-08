// SmallMapInfoDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include ".\SmallMapInfoDialog.h"

CSmallMapInfoDialog*	g_pSmallMapInfo = 0;
CSmallMapInfoDialog*	GetSmallMapInfoDlg()
{
	return g_pSmallMapInfo;
}

// CSmallMapInfoDialog �Ի���

IMPLEMENT_DYNAMIC(CSmallMapInfoDialog, CDialogBase)
CSmallMapInfoDialog::CSmallMapInfoDialog(CWnd* pParent /*=NULL*/)
	: CDialogBase(CSmallMapInfoDialog::IDD, pParent)
{
	g_pSmallMapInfo	=	this;
	m_scene3D		=	0;
}

CSmallMapInfoDialog::~CSmallMapInfoDialog()
{
}

void CSmallMapInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SMALL_MAP_ENABLE, m_chkSmallMapEnable);
	DDX_Control(pDX, IDC_SMALL_MAP_RENDER_OBJECTS, m_chkSmallMapRenderObjects);
	DDX_Control(pDX, IDC_OBJECT_RENDERS, m_cbIncludes);
	DDX_Control(pDX, IDC_OBJECT_RENDER_MAP, m_lbIncludes);
	DDX_Control(pDX, IDC_ADD_INCLUDE, m_btAddInclude);
	DDX_Control(pDX, IDC_REMOVE_INCLUDE, m_btRemoveInclude);
	DDX_Control(pDX, IDC_SMALL_MAP_PLANE_DISTANCE, m_edSmalMapPlaneDistance);
	DDX_Control(pDX, IDC_SMALL_MAP_REBUILD_INTERVAL, m_edSmallMapRebuildInterval);
}


BEGIN_MESSAGE_MAP(CSmallMapInfoDialog, CDialogBase)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_ADD_INCLUDE, OnBnClickedAddInclude)
	ON_BN_CLICKED(IDC_REMOVE_INCLUDE, OnBnClickedRemoveInclude)
	ON_BN_CLICKED(IDC_ALL_ALL, OnBnClickedAllAll)
	ON_BN_CLICKED(IDC_SMALL_MAP_ENABLE, OnBnClickedSmallMapEnable)
	ON_BN_CLICKED(IDC_SMALL_MAP_RENDER_OBJECTS, OnBnClickedSmallMapRenderObjects)
	ON_BN_CLICKED(IDC_SET_MPD, OnBnClickedSetMpd)
	ON_BN_CLICKED(IDC_SET_MRI, OnBnClickedSetMri)
END_MESSAGE_MAP()


// CSmallMapInfoDialog ��Ϣ�������

BOOL CSmallMapInfoDialog::OnInitDialog()
{
	CDialogBase::OnInitDialog();
	{
		ITableReader* table = LoadTableFile(0, "./geometry_types.editor");
		if(!table)return false;
		for(int i=0;i<table->getNumLine();i++)
		{
			const char* id		=	table->getLineItem(i, "value");
			const char* name	=	table->getLineItem(i, "name");
			this->m_geometryTypes[atoi(id)] = name;
			m_cbIncludes.SetItemData(m_cbIncludes.AddString(W(name)), atoi(id));
		}
		table->Release();
	}
	//
	AddTool(m_chkSmallMapEnable, Language(L"����С��ͼ��̬����ģʽ"));
	AddTool(m_chkSmallMapRenderObjects, Language(L"�Ƿ���Ⱦ���е����壬������ɫģ�͡�NPCģ�͵ȵȣ����ʹ�ô�����ȽϺ�Ч��"));
	AddTool(m_cbIncludes, Language(L"С��ͼ��Ⱦʱ��ģ�ģ�����ͣ���geometry_types.editor�ж���"));
	AddTool(m_lbIncludes, Language(L"��ǰ����С��ͼ��Ⱦ��ģ������"));
	AddTool(m_btAddInclude, Language(L"���һ��ģ������֧��"));
	AddTool(m_btRemoveInclude, Language(L"ɾ��һ��ģ������֧��"));
	AddTool(m_edSmalMapPlaneDistance, Language(L"�ڱ༭������Ԥ��һ��С��ͼ��С,��������ʱ���Ե����������, ��С��ͼ����ʾ��С���е���."));
	AddTool(m_edSmallMapRebuildInterval, Language(L"С��ͼ���¹���ʱ����"));
	return TRUE;
}

VOID CSmallMapInfoDialog::OnChangeScene()
{
	if(m_scene3D)
	{
		m_chkSmallMapEnable.SetCheck(m_scene3D->GetSmallMapEnable());
		m_chkSmallMapRenderObjects.SetCheck(m_scene3D->GetSmallMapRenderAllObjects());
		this->RebuildIncludes();
		wchar_t buf[128];
		swprintf(buf, L"%.03f", m_scene3D->GetSmallMapRebuildInterval());
		m_edSmallMapRebuildInterval.SetWindowText(buf);
		swprintf(buf, L"%d", m_scene3D->GetSmallMapOrthoWidth());
		m_edSmalMapPlaneDistance.SetWindowText(buf);
	}
}

void CSmallMapInfoDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogBase::OnShowWindow(bShow, nStatus);
}

void	CSmallMapInfoDialog::RebuildIncludes()
{
	if(!m_scene3D)
		return;
	this->m_lbIncludes.ResetContent();
	unsigned int nTypes	=	m_scene3D->GetSmallMapGeometryTypes();
	for(int i=0;i<32;i++)
	{
		unsigned int t = 1 << i;
		if((t & nTypes) > 0)
			m_lbIncludes.SetItemData(m_lbIncludes.AddString(W(m_geometryTypes[t].c_str())), t);
	}
}

void CSmallMapInfoDialog::OnBnClickedAddInclude()
{
	if(!m_scene3D)
		return;
	if(m_cbIncludes.GetCurSel() < 0)return;
	unsigned int nT	=	m_cbIncludes.GetItemData(m_cbIncludes.GetCurSel());
	m_scene3D->SetSmallMapGeometryTypes(m_scene3D->GetSmallMapGeometryTypes() | nT);
	RebuildIncludes();
}

void CSmallMapInfoDialog::OnBnClickedRemoveInclude()
{
	if(!m_scene3D)
		return;
	if(m_lbIncludes.GetCurSel() < 0)return;
	unsigned int nTypes	=	m_scene3D->GetSmallMapGeometryTypes();
	INT sels[128];
	int count = m_lbIncludes.GetSelItems(128, sels);
	for(int i=0;i<count;i++)
	{
		unsigned int type = m_lbIncludes.GetItemData(sels[i]);
		if((nTypes & type) > 0)
			nTypes ^= type;
	}
	m_scene3D->SetSmallMapGeometryTypes(nTypes);
	RebuildIncludes();
}

void CSmallMapInfoDialog::OnBnClickedAllAll()
{
	if(!m_scene3D)return;
	m_scene3D->SetSmallMapGeometryTypes(0xFFFFFFFF);
	RebuildIncludes();
}

void CSmallMapInfoDialog::OnBnClickedSmallMapEnable()
{
	if(!m_scene3D)return;
	m_scene3D->SetSmallMapEnable(this->m_chkSmallMapEnable.GetCheck());
}

void CSmallMapInfoDialog::OnBnClickedSmallMapRenderObjects()
{
	if(!m_scene3D)return;
	m_scene3D->SetSmallMapRenderAllObjects(this->m_chkSmallMapRenderObjects.GetCheck());
}

void CSmallMapInfoDialog::OnBnClickedSetMpd()
{
	if(!m_scene3D)return;
	CString str;
	this->m_edSmalMapPlaneDistance.GetWindowText(str);
	m_scene3D->SetSmallMapOrthoWidth(_wtoi(str));
}

void CSmallMapInfoDialog::OnBnClickedSetMri()
{
	if(!m_scene3D)return;
	CString str;
	this->m_edSmallMapRebuildInterval.GetWindowText(str);
	m_scene3D->SetSmallMapRebuildInterval(_wtof(str));
}
