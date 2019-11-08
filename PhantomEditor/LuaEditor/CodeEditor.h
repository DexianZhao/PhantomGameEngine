/*
��Ӱ��Ϸ����, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   �Ե��� Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include <vector>
#include <string>
#include <map>
#include "LuaXmlModule.h"
#include "ToolTipDialog.h"
#include "CodeListBox.h"
#include "CodeComboBox.h"
#include "CodeAnalyse.h"
#include "GCMFCHelper.h"
// CodeEditor
class EditorCallback{
public:
	virtual VOID	SetModifyed() = 0;
	virtual VOID	SaveFile() = 0;
};
template <typename T>
class EditorCallbackT: public EditorCallback{
public:
	T* m_t;
	EditorCallbackT(T* t=0){m_t=t;}
	VOID	SetModifyed(){if(m_t)m_t->SetModifyed();}
	VOID	SaveFile(){if(m_t)m_t->SaveFile();}
};
class CodeEditor;
__interface	LuaEditorWindow: public ViewerWindow
{
	VOID							SetModifyed(CodeEditor* e, BOOL b);
	VOID							RedrawLines();
	VOID							InvalidateDlg();
	VOID							UpdateTipText(const wchar_t* str, CWnd* wnd);
	VOID							OffsetToolRect(int x, int y);
};

class CMyLuaEditor;
class CodeEditor : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CodeEditor)
public://�ⲿ�������õ�
	CodeEditor();
	virtual ~CodeEditor();
	VOID							SetInitText(const wchar_t* code, const char* szFile);//���ó�ʼ���ı���������������ݲ����³�ʼ��
	VOID							SetInitFile(const char* szFile);
	VOID							SaveFile();
	VOID							Setup(CWnd* wnd, const CRect& rc, CFont* font, INT idToolTip, INT idResIcon);
	VOID							ReplaceText(const wchar_t* text, int beginCaret = -1);//�滻ѡ���ı�
	CodeManager&					GetCodeMgr(){return m_codeMgr;}
	VOID							InitColor();
	VOID							AnalyseAllCodes();//��������lua����
	EditorCallback*					m_callback;
	NameW							m_name;
	Phantom::UIControl*				m_controlPtr;
	VOID							CheckLineColor(int nBeforeLine, int nLastLine);//���¼�����ɫ
protected:
	VOID							SetTextColor(long begin, long count, const TextColor& c);
	CodeEditor&			operator >> (const wchar_t* v);
	CodeEditor&						AddMask(MaskText::MaskType t);
	BOOL							Undo();
	BOOL							Redo();
	int								GetLineText(CDynamicArray<wchar_t>& buff, int lineIndex);//����һ���ı�
	//
	VOID							CheckLineColor(int lineIndex);//���¼�����ɫ
	VOID							CheckLineColorRange(int beginLine, int endLine);//���¼�����ɫ
	VOID							GetLineSection(std::vector<MaskSection>& rets, int nBefore = 64);//���¼�����ɫ
	VOID							GetLineSection(CDynamicArray<MaskSection>& rets, const wchar_t* text, int length, BOOL bSpace = true, BOOL bSectionToOne = false/*�������϶ζ����ó�һ��*/);
	long							GetLineSectionAtIndex(CDynamicArray<MaskSection>& rets, int lineIndex, BOOL bSpace = true, BOOL bSectionToOne = false);//���¼�����ɫ
	VOID							SetMemberToolTip(CCodeMember* m, const CPoint& pos, BOOL bAlwaysShow);
	VOID							CheckMemberTip();//����Ƿ�Ҫ��ʾ����˵��
	int								m_memberCaret;
	BOOL							SelectFromListBox(int nChar);
	VOID							AutoShowListBox();
	//
	BOOL							ReturnCheckEvent();
	VOID							CheckToolTip(int beginCaret);
	int								m_bWaitTip;
	CPoint							m_lastPos;
	CString							m_lastTip;
	//
	VOID							AutoPopup(BOOL bEquip = FALSE);
	VOID							SetCharPosTip(const CPoint& pos);
	int								GetCodeRange(long start, long end, wchar_t* buf, int length);
	int								GetThisCaretFunction(int beginCaret, wchar_t* buf);//���������꺯�����ڵĵ�һ�У����ҷ��غ�������
	//
	VOID							RefreshCombos();//ˢ����Ͽ�����
	VOID							GotoThisFunction();//��Ͽ�������ǰ����
	VOID							OnComboSelect(CWnd* combo, const wchar_t* text, int data);
	//
	BOOL							m_bIsSelect;
	//
	long							m_saveIMEBegin,m_saveIMEEnd,m_saveIMELine,m_saveIMELineBegin;
	CString							m_saveIMEStr;
	CString							m_compositionStr;
	//
	VOID							OnChangeLine(CDynamicArray<LineText>& remove, int beginRemoveLine, CDynamicArray<LineText>& insert, int beginInsertLine);//������ı����ı�
	VOID							CompareAllLines();//�Ƚ������У������richedit�Ƿ�һ��
	//
	VOID							RemoveLine(int line, const wchar_t* equip);//ɾ��һ�У��ȱȽ��Ƿ�һ��
	VOID							InsertLine(int line, const wchar_t* text);//���һ��
	int								RequestCalls(wchar_t* ret, int line, int beginCaret, int nChar);//����һ�δ����ڵĵ����б�
public:
	static MaskText::MaskType		m_currType;
	static std::vector<MaskText>	m_masks;
	static TextColor				m_maskColor[MaskText::MaskType_Count];
	CCodeListBox					m_listbox;
	//
	CString							m_strFontFace;
	CToolTipDialog					m_toolTip;
	CCodeListBox					m_lbFunctions;//�����б�
	long							m_startCombo;
	CCodeComboBox					m_cbEvents,m_cbMethods;
	int								m_rebuildCode;
	BOOL							m_bIsChanged;
	long							m_lastUndoCaret;
	//
	VOID							ClearRedos();
	VOID							BeginUndo();
	VOID							AddThisUndo();
	CDynamicArray<CCodeUndo*>		m_undos;//��������
	CDynamicArray<CCodeUndo*>		m_redos;//��������
	CCodeUndo*						m_undoPtr;
	CCodeUndo*						m_undoWritePtr;
	//
	NameT<512>						m_fileName;
	//
	VOID							OnChangeCaret();
	//
	VOID							UndoCaret();
	VOID							RedoCaret();
	CDynamicArray<long>				m_undoCaret;//�����һ��
	CDynamicArray<long>				m_redoCaret;//�����һ��
	BOOL							m_bPaintEnable;
	LuaEditorWindow*				m_dlgEditor;
	CodeManager						m_codeMgr;
	CString							m_tipText;
	int								m_firstLine;
	BOOL							m_bModifyed;
	char							m_bCharChanged;
	int								m_dblStart,m_dblEnd;
	//
	friend class	CMyLuaEditor;
	friend class	CCodeListBox;
	friend class	CCodeComboBox;
	friend class	CDlgFindReplace;
	friend class	CDlgCodeColor;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pNewWnd);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnEnVscroll();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


