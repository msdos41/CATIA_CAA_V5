// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestTessellationDlg.cpp
// The dialog : TestTessellationDlg
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Mar 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestTessellationDlg.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef TestTessellationDlg_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif




//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestTessellationDlg::TestTessellationDlg() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"TestTessellationDlg",CATDlgWndBtnOKCancel|CATDlgWndTitleBarHelp|CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                               )
{
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _Label001 = NULL;
 _SelectorListSurface = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION

 _pRightCLKMenu = NULL;
 _pRightCLKClear = NULL;
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestTessellationDlg::~TestTessellationDlg()
{
//  Do not delete the control elements of your dialog: 
//     this is done automatically
//  --------------------------------------------------
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _Label001 = NULL;
 _SelectorListSurface = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION

 _pRightCLKMenu = NULL;
 _pRightCLKClear = NULL;
}



void TestTessellationDlg::Build()
{
//  TODO: This call builds your dialog from the layout declaration file
//  -------------------------------------------------------------------

//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 _Label001 = new CATDlgLabel(this, "Label001");
_Label001 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _SelectorListSurface = new CATDlgSelectorList(this, "SelectorListSurface");
 _SelectorListSurface -> SetVisibleTextHeight(1);
 _SelectorListSurface -> SetVisibleTextWidth(20);
_SelectorListSurface -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION

//CAA2 WIZARD CALLBACK DECLARATION SECTION
//END CAA2 WIZARD CALLBACK DECLARATION SECTION
CATUnicodeString strDefault = "No selection";
_SelectorListSurface->SetLine(strDefault,-1,CATDlgDataAdd);

_pRightCLKMenu = new CATDlgContextualMenu(this,"RightClick",NULL);
_pRightCLKClear = new CATDlgPushItem(_pRightCLKMenu,"RightClickClear");
_pRightCLKClear->SetTitle("Clear selection");
}

CATDlgSelectorList* TestTessellationDlg::GetSelectorListSurface()
{
	return _SelectorListSurface;
}

CATDlgPushItem* TestTessellationDlg::GetRightClickClear()
{
	return _pRightCLKClear;
}