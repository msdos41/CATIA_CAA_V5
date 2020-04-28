
#include "CAATreeCtrl.h"
#include <shlwapi.h>
#include "CATUnicodeString.h"
#include "CATEventSubscriber.h"
#include "CATCallbackManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CATUnicodeString G_SelectedTempName="";
CATUnicodeString G_FatherSelectedTempName="";
//--------------------------------------------------------------------------------
// CAATreeCtrl Implementation
//--------------------------------------------------------------------------------

IMPLEMENT_DYNAMIC(CAATreeCtrl, CTreeCtrl)

//--------------------------------------------------------------------------------
// Construction/Destruction
//--------------------------------------------------------------------------------

CAATreeCtrl::CAATreeCtrl():m_pCommand(NULL)
,m_pCommandDblClk(NULL)
{
	m_pCommand=new CATCommand();

	m_pCommandDblClk=new CATCommand();
}

CAATreeCtrl::~CAATreeCtrl()
{
	if(m_pCommand)
		delete m_pCommand;

	if (m_pCommandDblClk!=NULL)
	{
		delete m_pCommandDblClk;
	}
}
BEGIN_MESSAGE_MAP(CAATreeCtrl, CTreeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

//---------------------------------------------------------------------------
// Operations
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
// Message Handlers
//---------------------------------------------------------------------------

void CAATreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// mask left click if outside the real item's label
	HTREEITEM hItem = HitTest(point);
	CString strValue =  GetItemText(hItem);
	HTREEITEM hFatherItem = GetParentItem(hItem);
	while(hFatherItem!=NULL)
	{
		strValue =  GetItemText(hFatherItem)+"\\"+strValue;
		hFatherItem = GetParentItem(hFatherItem);
	}

	const wchar_t * bstr  = strValue;
	m_strSeleItem.BuildFromWChar(bstr);

	SelectTreeItemNotif * DestructionNotification = new SelectTreeItemNotif();

	GetDefaultCallbackManager(m_pCommand)->DispatchCallbacks(DestructionNotification, m_pCommand);

	delete DestructionNotification;
	DestructionNotification=NULL;

	// call standard handler	
	CTreeCtrl::OnLButtonDown(nFlags, point);

}

void CAATreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	HTREEITEM hItem = HitTest(point);
	CString strValue =  GetItemText(hItem);

	const wchar_t * bstr  = strValue;
	m_strSeleItem.BuildFromWChar(bstr);

	
	//��Ϣ�ػ񣿣� ���ֱ���ڸú�����д�봥��Ч��������Ϣ�ػ���Բ�д
	SelectTreeItemNotif * DestructionNotification = new SelectTreeItemNotif();

	GetDefaultCallbackManager(m_pCommandDblClk)->DispatchCallbacks(DestructionNotification, m_pCommandDblClk);

	delete DestructionNotification;
	DestructionNotification=NULL;

	// call standard handler	
	CTreeCtrl::OnLButtonDblClk(nFlags, point);

	//�˴�����ֱ��д��˫��ĳһitem��Ķ�����Ҳ������cmd������callback��ͬʱ��Ҫ�������Ϣ�������
	//MessageBoxA(NULL,m_strSeleItem,"Info",MB_OK);
}