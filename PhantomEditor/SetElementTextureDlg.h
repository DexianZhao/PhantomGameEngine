/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include "afxpropertygridctrl.h"
#include "GCPropertyBase.h"

// CSetElementTextureDlg �Ի���

struct	ElementIn
{
	LPARAM						param1;
	LPARAM						param2;
	std::wstring					name;
	ElementIn()
	{
		param1	=	param2	=	0;
	}
	ElementIn(const wchar_t* n, LPARAM p1, LPARAM p2)
	{
		name	=	n;
		param1	=	p1;
		param2	=	p2;
	}
};

struct	ElementTexture
{
	ElementIn					param;
	std::wstring				str;
	CMFCPropertyGridProperty*	prop;
};

class CSetElementTextureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetElementTextureDlg)

public:
	CSetElementTextureDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetElementTextureDlg();

	VOID			SetElements(std::vector<ElementIn>& elements, std::vector<std::wstring>& textures);
	//
// �Ի�������
	enum { IDD = IDD_ELEMENT_TEXTURE_SET };

	std::vector<std::wstring>		m_textures;
	std::vector<ElementTexture>		m_elements;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	GCPropertyBase m_eleTex;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
