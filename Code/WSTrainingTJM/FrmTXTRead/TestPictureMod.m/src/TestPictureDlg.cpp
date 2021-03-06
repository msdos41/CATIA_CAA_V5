// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestPictureDlg.cpp
// The dialog : TestPictureDlg
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Sep 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestPictureDlg.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef TestPictureDlg_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif




//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestPictureDlg::TestPictureDlg() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"TestPictureDlg",CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                               )
{
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _Label001 = NULL;
 _Label002 = NULL;
 _Label003 = NULL;
 _Label004 = NULL;
 _Editor005 = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestPictureDlg::~TestPictureDlg()
{
//  Do not delete the control elements of your dialog: 
//     this is done automatically
//  --------------------------------------------------
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _Label001 = NULL;
 _Label002 = NULL;
 _Label003 = NULL;
 _Label004 = NULL;
 _Editor005 = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
}



void TestPictureDlg::Build()
{
//  TODO: This call builds your dialog from the layout declaration file
//  -------------------------------------------------------------------

//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 _Label001 = new CATDlgLabel(this, "Label001");
_Label001 -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _Label002 = new CATDlgLabel(this, "Label002");
_Label002 -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _Label003 = new CATDlgLabel(this, "Label003");
_Label003 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Label004 = new CATDlgLabel(this, "Label004");
_Label004 -> SetGridConstraints(1, 2, 1, 1, CATGRID_4SIDES);
 _Editor005 = new CATDlgEditor(this, "Editor005");
_Editor005 -> SetGridConstraints(1, 3, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION

//CAA2 WIZARD CALLBACK DECLARATION SECTION
//END CAA2 WIZARD CALLBACK DECLARATION SECTION

}

