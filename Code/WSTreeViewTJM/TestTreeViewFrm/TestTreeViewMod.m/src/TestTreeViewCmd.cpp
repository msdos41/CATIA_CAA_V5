// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestTreeViewCmd.cpp
// The state chart based command: TestTreeViewCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Apr 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestTreeViewCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

#include "CATCreateExternalObject.h"
CATCreateClass( TestTreeViewCmd);


#define  TreeControlID 0x0201

//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestTreeViewCmd::TestTreeViewCmd() :
  CATStateCommand ("TestTreeViewCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
,_pDlg(NULL)
{
	_pDlg = new TestTreeViewDlg();
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);
	_pDlg->GetDlgFrame()->SetVisibility(CATDlgHide);

	//CATIProduct_var spiProdRoot = NULL_var;
	//GetRootProduct(spiProdRoot);

	//this->InitTreeView(spiProdRoot);

	CATUnicodeString strTest = "aaaa";
	CATListOfCATUnicodeString lstString;
	SplitStringUpdate(strTest,"/",lstString);
	for (int i=1;i<=lstString.Size();i++)
	{
		cout<<i<<"  "<<lstString[i]<<endl;
	}
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestTreeViewCmd::~TestTreeViewCmd()
{
	if (_pDlg != NULL)
	{
		_pDlg->RequestDelayedDestruction();
		_pDlg = NULL;
	}
}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void TestTreeViewCmd::BuildGraph()
{
	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCLOSENotification(),
		(CATCommandMethod)&TestTreeViewCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetWindCloseNotification(),
		(CATCommandMethod)&TestTreeViewCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCANCELNotification(),
		(CATCommandMethod)&TestTreeViewCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaOKNotification(),
		(CATCommandMethod)&TestTreeViewCmd::ActionOK,
		NULL);

	//树形结构只能在 GetWindSizeNotif的回调函数中才能实现 窗口打开的同时加载树形控件，
	//单纯的在构造函数中增加加载方法无法实现
	//同时，使用该回调函数，需要在dlg的cpp中构造中增加CATDlgWndNoResize
	//否则当更改窗口大小时，树形控件点击后无法展开
	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetWindSizeNotification(),
		(CATCommandMethod)&TestTreeViewCmd::InitTreeView,
		NULL);

	//额外增加tree控件下对item双击的效果，CATCommand需要看清楚调用，可能会定义了多个操作的CATCommand
	AddCallback(m_testTree.m_pCommandDblClk, SelectTreeItemNotif::ClassName(),
		(CATSubscriberMethod)&TestTreeViewCmd::ONtreeDBLClick,NULL);

	AddCallback(m_testTree.m_pCommand, SelectTreeItemNotif::ClassName(),
		(CATSubscriberMethod)&TestTreeViewCmd::ONtreeLClick,NULL);
}


//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean TestTreeViewCmd::ActionOne( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------

  return TRUE;
}

CATBoolean TestTreeViewCmd::ExitCmd(void * data)
{
	this->RequestDelayedDestruction();
	return TRUE;
}

CATBoolean TestTreeViewCmd::ActionOK(void * data)
{
	//_pDlg->GetDlgFrame()->SetVisibility(CATDlgHide);
	//
	//CATIProduct_var spiProdRoot = NULL_var;
	//GetRootProduct(spiProdRoot);

	//this->InitTreeView(spiProdRoot);
	
	return TRUE;
}

//单纯的创建TreeView，可以直接调用CTreeCtrl，不需要专门写class继承CTreeCtrl，但是如果需要用到相关触发消息，则需要重写class
HRESULT TestTreeViewCmd::InitTreeView()
{
	HRESULT rc = S_OK;

	CATIProduct_var spiProdRoot = NULL_var;
	GetRootProduct(spiProdRoot);
	if (spiProdRoot==NULL_var)
	{
		return E_FAIL;
	}

	DRECT drct1;
	_pDlg->GetDlgFrame()->GetRectDimensions(&drct1);

	CATUnicodeString strTitle = _pDlg->GetTitle();

	BSTR bstrTitle;
	strTitle.ConvertToBSTR(&bstrTitle);

	HWND hwnd = FindWindow(NULL, bstrTitle);
	if(hwnd==NULL)
		return E_FAIL;

	CWnd * pCWnd;
	pCWnd= CWnd::FromHandle(hwnd);

	RECT rct1;
	rct1.left=drct1.x+10;
	rct1.top=drct1.y+10;
	rct1.right=drct1.dx;
	rct1.bottom=drct1.dy+10;

	UINT Uid1=TreeControlID;

	BOOL flag1=m_testTree.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
		| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES| TVS_DISABLEDRAGDROP 
		| TVS_NOTOOLTIPS |TVS_SHOWSELALWAYS ,rct1,pCWnd,Uid1);
	if(flag1)
	{
		CATUnicodeString strRootName = spiProdRoot->GetPartNumber();
		BSTR bstrRoot;
		strRootName.ConvertToBSTR(&bstrRoot);
		
		TVINSERTSTRUCT tvRootInst;
		tvRootInst.item.mask = TVIF_TEXT;
		tvRootInst.hInsertAfter = TVI_LAST;
		tvRootInst.hParent = NULL;
		tvRootInst.item.pszText =bstrRoot;

		HTREEITEM hNodeRoot = m_testTree.InsertItem(&tvRootInst);
		if(hNodeRoot)
		{
			//for(int ii=1;ii<5;ii++)
			//{
			//	CATUnicodeString strII;
			//	strII.BuildFromNum(ii);

			//	BSTR bstrII;
			//	strII.ConvertToBSTR(&bstrII);

			//	TVINSERTSTRUCT tvChildInst;
			//	tvChildInst.item.mask = TVIF_TEXT;
			//	tvChildInst.hInsertAfter = TVI_LAST;
			//	tvChildInst.hParent = hNodeRoot;
			//	tvChildInst.item.pszText =bstrII;

			//	HTREEITEM hNodeFath1 = m_testTree.InsertItem(&tvChildInst);
			//	for(int jj=1;jj<5;jj++)
			//	{
			//		CATUnicodeString strjj;
			//		strjj.BuildFromNum(jj);
			//		strjj = strII+"."+strjj;

			//		BSTR bstrJJ;
			//		strjj.ConvertToBSTR(&bstrJJ);

			//		TVINSERTSTRUCT tvInst2;
			//		tvInst2.item.mask = TVIF_TEXT;
			//		tvInst2.hInsertAfter = TVI_LAST;
			//		tvInst2.hParent = hNodeFath1;
			//		tvInst2.item.pszText =bstrJJ;

			//		HTREEITEM hNodeFath2 = m_testTree.InsertItem(&tvInst2);
			//	}
			//}

			if (IsProduct(spiProdRoot))
			{
				this->InsertItemOnTree(spiProdRoot,hNodeRoot);
			} 
			else
			{
				CATIPrtContainer_var spiPrtCont = GetPrtContainer(spiProdRoot);
				if (spiPrtCont!=NULL_var)
				{
					CATISpecObject_var spiSpecPart = spiPrtCont->GetPart();

					this->InsertPartItemOnTree(spiSpecPart,hNodeRoot);
				}
			}
			
		}
	}

	return rc;
}

void TestTreeViewCmd::InsertItemOnTree(CATIProduct_var spiProd, HTREEITEM ihNodeFather)
{
	CATListValCATBaseUnknown_var *listDirectChildren = spiProd->GetChildren();
	if (listDirectChildren == NULL)
	{
		return;
	}
	CATIProduct_var spDirectChild = NULL_var;
	for (int i=1; i<=listDirectChildren->Size(); i++)
	{

		spDirectChild = (*listDirectChildren)[i];

		CATUnicodeString strInstName;
		spDirectChild->GetPrdInstanceName(strInstName);
		BSTR bstrInstName;
		strInstName.ConvertToBSTR(&bstrInstName);

		TVINSERTSTRUCT tvChildInst;
		tvChildInst.item.mask = TVIF_TEXT;
		tvChildInst.hInsertAfter = TVI_LAST;
		tvChildInst.hParent = ihNodeFather;
		tvChildInst.item.pszText =bstrInstName;
		HTREEITEM hNode = m_testTree.InsertItem(&tvChildInst);
		//

		InsertItemOnTree(spDirectChild,hNode);
	}
}
//遍历结构树----CATINavigateObject
void TestTreeViewCmd::InsertPartItemOnTree(CATISpecObject_var ispiSpecObj, HTREEITEM ihNode)
{
	//CATIDescendants_var spiDesc = ispiSpecObj;
	//if (spiDesc==NULL_var)
	//{
	//	return;
	//}
	//CATListValCATISpecObject_var lstSpecChildren;
	//spiDesc->GetDirectChildren("CATISpecObject",lstSpecChildren);
	//for (int i=1;i<=lstSpecChildren.Size();i++)
	//{
	//	CATISpecObject_var spiSpec = lstSpecChildren[i];
	//	CATIAlias_var spiAlias = spiSpec;
	//	CATUnicodeString strAlias = spiAlias->GetAlias();
	//	BSTR bstrAlias;
	//	strAlias.ConvertToBSTR(&bstrAlias);

	//	TVINSERTSTRUCT tvChildInst;
	//	tvChildInst.item.mask = TVIF_TEXT;
	//	tvChildInst.hInsertAfter = TVI_LAST;
	//	tvChildInst.hParent = ihNode;
	//	tvChildInst.item.pszText =bstrAlias;
	//	HTREEITEM hNode = m_testTree.InsertItem(&tvChildInst);
	//	//

	//	InsertPartItemOnTree(spiSpec,hNode);
	//}

	CATINavigateObject_var spiNavigateObject = ispiSpecObj;
	if (spiNavigateObject==NULL_var)
	{
		return;
	}
	CATListValCATBaseUnknown_var* plstChildren = spiNavigateObject->GetChildren();
	if (plstChildren!=NULL)
	{
		for (int i=1;i<=plstChildren->Size();i++)
		{
			CATISpecObject_var spChild = (*plstChildren)[i];
			if (spChild==NULL_var)
			{
				continue;
			}
			CATIAlias_var spiAlias = spChild;
			CATUnicodeString strAlias = spiAlias->GetAlias();
			BSTR bstrAlias;
			strAlias.ConvertToBSTR(&bstrAlias);

			TVINSERTSTRUCT tvChildInst;
			tvChildInst.item.mask = TVIF_TEXT;
			tvChildInst.hInsertAfter = TVI_LAST;
			tvChildInst.hParent = ihNode;
			tvChildInst.item.pszText =bstrAlias;
			HTREEITEM hNode = m_testTree.InsertItem(&tvChildInst);
			//
			InsertPartItemOnTree(spChild,hNode);

		}
	}
}

void TestTreeViewCmd::ONtreeDBLClick(CATCallbackEvent   iDestructCmdEvent,
									 void             * iDestructCmd,
									 CATNotification  * iDestructCmdNotification,
									 CATSubscriberData  iCLCmdData,
									 CATCallback        iCallbackId)
{
	CATUnicodeString strInfo = m_testTree.m_strSeleItem;
	CAAMessageBox(strInfo,"Info",CATDlgNfyInformation);
}

void TestTreeViewCmd::ONtreeLClick(CATCallbackEvent   iDestructCmdEvent,
									 void             * iDestructCmd,
									 CATNotification  * iDestructCmdNotification,
									 CATSubscriberData  iCLCmdData,
									 CATCallback        iCallbackId)
{
	CATUnicodeString strInfo = m_testTree.m_strSeleItem;
	//CAAMessageBox(strInfo,"Info",CATDlgNfyInformation);
	CATListOfCATUnicodeString lstAlias;
	SplitStringUpdate(strInfo,"\\",lstAlias);

	CATIProduct_var spiProdRoot = NULL_var;
	GetRootProduct(spiProdRoot);
	if (spiProdRoot==NULL_var)
	{
		return;
	}

	if (IsProduct(spiProdRoot))
	{
	} 
	else
	{
		CATIPrtContainer_var spiPrtCont = GetPrtContainer(spiProdRoot);
		if (spiPrtCont!=NULL_var)
		{
			CATISpecObject_var spiSpecPart = spiPrtCont->GetPart();
			CATISpecObject_var spiSpecSelect = this->GetSpecObjFromNode(spiSpecPart,lstAlias);

			if (spiSpecSelect!=NULL_var)
			{
				//模型树对应节点选中高亮并居中显示
				AddHSO(spiSpecSelect);
				CenterGraphObject(spiSpecSelect,2,true);
				
			}
		}
	}
}
//根据节点列表顺序逐层找到所选的元素
CATISpecObject_var TestTreeViewCmd::GetSpecObjFromNode(CATISpecObject_var ispiSpecFather,CATListOfCATUnicodeString ilstNode)
{
	CATISpecObject_var spiSpecFather = ispiSpecFather;

	CATISpecObject_var spiSpecChild = NULL_var;

	for (int i=1;i<ilstNode.Size();i++)
	{
		CATIDescendants_var spiDesc = spiSpecFather;
		if (spiDesc==NULL_var)
		{
			return NULL_var;
		}
		CATUnicodeString strAliasCurrent = ilstNode[i+1];
		CATListValCATISpecObject_var lstSpecChildren;
		spiDesc->GetDirectChildren("CATISpecObject",lstSpecChildren);
		for (int j=1;j<=lstSpecChildren.Size();j++)
		{
			CATISpecObject_var spiSpec = lstSpecChildren[j];
			CATIAlias_var spiAlias = spiSpec;
			CATUnicodeString strAlias = spiAlias->GetAlias();
			if (strAlias == strAliasCurrent)
			{
				spiSpecFather = spiSpec;
				spiSpecChild = spiSpec;
			}
		}
	}

	return spiSpecChild;
}