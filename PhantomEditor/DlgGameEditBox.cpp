/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
// DlgGameEditBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgGameEditBox.h"
#include "DlgEditBox.h"

// DlgGameEditBox

IMPLEMENT_DYNAMIC(DlgGameEditBox, CEdit)

DlgGameEditBox::DlgGameEditBox()
{
	m_dlgEdit = 0;
}

DlgGameEditBox::~DlgGameEditBox()
{
}


BEGIN_MESSAGE_MAP(DlgGameEditBox, CEdit)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// DlgGameEditBox ��Ϣ�������




void DlgGameEditBox::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);
	m_dlgEdit->OnBnClickedOk();
	// TODO: �ڴ˴������Ϣ����������
}
