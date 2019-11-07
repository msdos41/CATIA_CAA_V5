// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// TestDrwDimensionDlg.cpp
// The dialog : TestDrwDimensionDlg
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Oct 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestDrwDimensionDlg.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef TestDrwDimensionDlg_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif




//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestDrwDimensionDlg::TestDrwDimensionDlg() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"TestDrwDimensionDlg",CATDlgWndBtnOKCancel|CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                               )
{
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _Label001 = NULL;
 _SelectorListLine = NULL;
 _Frame002 = NULL;
 _PushButtonClear = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestDrwDimensionDlg::~TestDrwDimensionDlg()
{
//  Do not delete the control elements of your dialog: 
//     this is done automatically
//  --------------------------------------------------
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _Label001 = NULL;
 _SelectorListLine = NULL;
 _Frame002 = NULL;
 _PushButtonClear = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
}



void TestDrwDimensionDlg::Build()
{
//  TODO: This call builds your dialog from the layout declaration file
//  -------------------------------------------------------------------

//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 _Label001 = new CATDlgLabel(this, "Label001");
_Label001 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _SelectorListLine = new CATDlgSelectorList(this, "SelectorListLine");
 _SelectorListLine -> SetVisibleTextWidth(30);
_SelectorListLine -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Frame002 = new CATDlgFrame(this, "Frame002", CATDlgFraNoTitle|CATDlgGridLayout);
_Frame002 -> SetGridConstraints(0, 2, 1, 1, CATGRID_4SIDES);
 _PushButtonClear = new CATDlgPushButton(_Frame002, "PushButtonClear");
_PushButtonClear -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION

//CAA2 WIZARD CALLBACK DECLARATION SECTION
//END CAA2 WIZARD CALLBACK DECLARATION SECTION

}

CATDlgSelectorList* TestDrwDimensionDlg::GetSelectorListLine()
{
	return _SelectorListLine;
}

CATDlgPushButton* TestDrwDimensionDlg::GetPushButtonClear()
{
	return _PushButtonClear;
}