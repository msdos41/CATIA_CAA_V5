// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestProgressBarCmd.cpp
// The state chart based command: TestProgressBarCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Jan 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestProgressBarCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

#include "CATCreateExternalObject.h"
CATCreateClass( TestProgressBarCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestProgressBarCmd::TestProgressBarCmd() :
  CATStateCommand ("TestProgressBarCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
,_iCountClick(0)
{
	_pDlg = NULL;
	_pDlg = new TestProgressBarDlg();
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);

	_pDlg->GetProgressBar()->SetRange(0,10);//一共1到10格
	_pDlg->GetProgressBar()->SetStep(2);	//每一步走几格
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestProgressBarCmd::~TestProgressBarCmd()
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
void TestProgressBarCmd::BuildGraph()
{
	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCLOSENotification(),
		(CATCommandMethod)&TestProgressBarCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetWindCloseNotification(),
		(CATCommandMethod)&TestProgressBarCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCANCELNotification(),
		(CATCommandMethod)&TestProgressBarCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaOKNotification(),
		(CATCommandMethod)&TestProgressBarCmd::ActionOK,
		NULL);
}


//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean TestProgressBarCmd::ActionOne( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------

  return TRUE;
}

CATBoolean TestProgressBarCmd::ExitCmd(void * data)
{
	RequestDelayedDestruction();
	return TRUE;
}

CATBoolean TestProgressBarCmd::ActionOK(void * data)
{

	if (10 == _pDlg->GetProgressBar()->GetPos())
	{
		_pDlg->GetProgressBar()->SetPos(0);
		return TRUE;
	}

	_pDlg->GetProgressBar()->StepIt();
	
	return TRUE;
}