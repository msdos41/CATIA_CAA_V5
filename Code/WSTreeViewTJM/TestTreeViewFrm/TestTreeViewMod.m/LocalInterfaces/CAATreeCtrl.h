#ifdef _WINDOWS_
#undef _WINDOWS_
#endif

#include "afx.h"
#include <afxwin.h>
#include <afxext.h>
#include <afxdisp.h>
#include <afxdtctl.h>
#include <afxcmn.h>
#pragma once
#include "CATCommand.h"
#include "SelectTreeItemNotif.h"
#include "CATUnicodeString.h"

class CAATreeCtrl : public CTreeCtrl//�̳�CTreeCtrl
{
	DECLARE_DYNAMIC(CAATreeCtrl)

public:

	CAATreeCtrl();
	virtual ~CAATreeCtrl();
	CATCommand * m_pCommand;

	CATCommand * m_pCommandDblClk;	//˫�����������ֵ��������Զ��ⴴ��ȫ�ֱ���������cmd��callback������Ҫ�����

	CATUnicodeString m_strSeleItem;

protected:
	DECLARE_MESSAGE_MAP()

	int m_nFirstColumnWidth; // the width of the first column 
	int m_nOffsetX;      	 // offset of this window inside the parent 
	LVBKIMAGE m_bkImage;	 // information about background image
	CImageList m_imgBtns;	 // tree buttons images (IDB_TREEBTNS)

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};