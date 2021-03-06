// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// TestCrvRadiusDlg.cpp
// The dialog : TestCrvRadiusDlg
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Nov 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestCrvRadiusDlg.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef TestCrvRadiusDlg_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif




//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestCrvRadiusDlg::TestCrvRadiusDlg() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"TestCrvRadiusDlg",CATDlgWndBtnOKCancel|CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                               )
{
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _LabelSurface = NULL;
 _SelectorListSurface = NULL;
 _Container003 = NULL;
 _EditorResult = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestCrvRadiusDlg::~TestCrvRadiusDlg()
{
//  Do not delete the control elements of your dialog: 
//     this is done automatically
//  --------------------------------------------------
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _LabelSurface = NULL;
 _SelectorListSurface = NULL;
 _Container003 = NULL;
 _EditorResult = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
}



void TestCrvRadiusDlg::Build()
{
//  TODO: This call builds your dialog from the layout declaration file
//  -------------------------------------------------------------------

//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 _LabelSurface = new CATDlgLabel(this, "LabelSurface");
_LabelSurface -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _SelectorListSurface = new CATDlgSelectorList(this, "SelectorListSurface");
 _SelectorListSurface -> SetVisibleTextHeight(1);
 _SelectorListSurface -> SetVisibleTextWidth(30);
_SelectorListSurface -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Container003 = new CATDlgContainer(this, "Container003");
 _Container003 -> SetRectDimensions(1, 1, 5, 5);
_Container003 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _EditorResult = new CATDlgEditor(this, "EditorResult", CATDlgEdtMultiline);
 _EditorResult -> SetVisibleTextHeight(2);
_EditorResult -> SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION

//CAA2 WIZARD CALLBACK DECLARATION SECTION
//END CAA2 WIZARD CALLBACK DECLARATION SECTION

_SelectorListSurface->SetLine("No Selection");
}

CATDlgSelectorList* TestCrvRadiusDlg::GetSelectorListSurface()
{
	return _SelectorListSurface;
}

CATDlgEditor* TestCrvRadiusDlg::GetEditorResult()
{
	return _EditorResult;
}