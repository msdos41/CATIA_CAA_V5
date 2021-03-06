// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestCATIAReferenceDlg.cpp
// The dialog : TestCATIAReferenceDlg
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Mar 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestCATIAReferenceDlg.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef TestCATIAReferenceDlg_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif




//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestCATIAReferenceDlg::TestCATIAReferenceDlg() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"TestCATIAReferenceDlg",CATDlgWndBtnOKApplyClose|CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                               )
{
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _Label001 = NULL;
 _SelectorListSurface = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestCATIAReferenceDlg::~TestCATIAReferenceDlg()
{
//  Do not delete the control elements of your dialog: 
//     this is done automatically
//  --------------------------------------------------
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _Label001 = NULL;
 _SelectorListSurface = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
}



void TestCATIAReferenceDlg::Build()
{
//  TODO: This call builds your dialog from the layout declaration file
//  -------------------------------------------------------------------

//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 _Label001 = new CATDlgLabel(this, "Label001");
_Label001 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _SelectorListSurface = new CATDlgSelectorList(this, "SelectorListSurface");
 _SelectorListSurface -> SetVisibleTextHeight(1);
 _SelectorListSurface -> SetVisibleTextWidth(25);
_SelectorListSurface -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION

//CAA2 WIZARD CALLBACK DECLARATION SECTION
//END CAA2 WIZARD CALLBACK DECLARATION SECTION

CATUnicodeString strDefault = "No Selection";
_SelectorListSurface->SetLine(strDefault);

}

CATDlgSelectorList *TestCATIAReferenceDlg::GetSelectorListSurface()
{
	return _SelectorListSurface;
}