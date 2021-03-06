// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// TestMultiListDlg.cpp
// The dialog : TestMultiListDlg
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Nov 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestMultiListDlg.h"
#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef TestMultiListDlg_ParameterEditorInclude
#include "CATIParameterEditorFactory.h"
#include "CATIParameterEditor.h"
#include "CATICkeParm.h"
#endif




//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestMultiListDlg::TestMultiListDlg() :
  CATDlgDialog ((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"TestMultiListDlg",CATDlgWndBtnOKCancel|CATDlgWndTitleBarHelp|CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                               )
,_bMoreUI(FALSE)
{
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _Frame002 = NULL;
 _Frame003 = NULL;
 _MultiListSelect = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _Frame001 = NULL;
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestMultiListDlg::~TestMultiListDlg()
{
//  Do not delete the control elements of your dialog: 
//     this is done automatically
//  --------------------------------------------------
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _Frame002 = NULL;
 _Frame003 = NULL;
 _MultiListSelect = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _Frame001 = NULL;
}



void TestMultiListDlg::Build()
{
//  TODO: This call builds your dialog from the layout declaration file
//  -------------------------------------------------------------------

//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 _Frame002 = new CATDlgFrame(this, "Frame002", CATDlgGridLayout);
_Frame002 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _Frame003 = new CATDlgFrame(this, "Frame003", CATDlgGridLayout);
_Frame003 -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _MultiListSelect = new CATDlgMultiList(_Frame003, "MultiListSelect");
 CATUnicodeString MultiListSelectTitles [ 3 ];
 MultiListSelectTitles[0] = CATMsgCatalog::BuildMessage("TestMultiListDlg", "Frame003.MultiListSelect.ColumnTitle1");
 MultiListSelectTitles[1] = CATMsgCatalog::BuildMessage("TestMultiListDlg", "Frame003.MultiListSelect.ColumnTitle2");
 MultiListSelectTitles[2] = CATMsgCatalog::BuildMessage("TestMultiListDlg", "Frame003.MultiListSelect.ColumnTitle3");
 _MultiListSelect -> SetColumnTitles(3, MultiListSelectTitles);
 _MultiListSelect -> SetVisibleColumnCount( 3 );
 _MultiListSelect->SetColumnTextWidth (1, 20);
 _MultiListSelect->SetColumnTextWidth (2, 20);
_MultiListSelect -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION

//CAA2 WIZARD CALLBACK DECLARATION SECTION
//END CAA2 WIZARD CALLBACK DECLARATION SECTION
SetVerticalAttachment(0,CATDlgTopOrLeft,_MultiListSelect,NULL);
AddAnalyseNotificationCB(this,
						 this->GetDiaOKNotification(),
						 (CATCommandMethod)&TestMultiListDlg::ActionShowMoreUI,
						 NULL);
}

CATDlgMultiList* TestMultiListDlg::GetMultiListSelect()
{
	return _MultiListSelect;
}

CATDlgFrame * TestMultiListDlg::GetFrame()
{
	return _Frame001;
}

CATBoolean TestMultiListDlg::ActionShowMoreUI(void * data)
{
	/*
	_Frame001 = new CATDlgFrame(this, "Frame001", NULL);
	_Frame001 -> SetGridConstraints(0, 2, 1, 1, CATGRID_4SIDES);
	//this->SetHorizontalAttachment(0,CATDlgTopOrLeftRelative,_MultiListSelect,_Frame002,_Frame001,NULL);
	this->SetVerticalAttachment(0,CATDlgTopOrLeft,_MultiListSelect,NULL);
	//this->SetHorizontalAttachment(0,CATDlgTopOrLeft,_Frame002,NULL);
	this->SetVerticalAttachment(50,CATDlgTopOrLeft,_Frame002,NULL);
	//this->SetHorizontalAttachment(0,CATDlgTopOrLeft,_Frame001,NULL);
	this->SetVerticalAttachment(100,CATDlgTopOrLeft,_Frame001,NULL);
	*/
	if( TRUE == _bMoreUI)
	{
		// To do that, reset the attachment 
		ResetAttachment(_Frame002);         

		// hide the more panel
		_Frame002->SetVisibility(CATDlgHide);         

		//pButton->SetTitle (_MoreMsg);

		_bMoreUI= FALSE;
	}
	else
	{
		// To do that, define a new tabulation
		SetVerticalAttachment(10, CATDlgTopOrLeft, _Frame002, NULL);

		// show the more panel
		_Frame002->SetVisibility(CATDlgShow);         

		//pButton->SetTitle (_LessMsg);

		_bMoreUI = TRUE;
	}
	
	return TRUE;
}