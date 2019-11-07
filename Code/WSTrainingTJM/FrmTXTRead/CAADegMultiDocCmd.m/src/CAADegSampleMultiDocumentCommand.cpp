// DialogEngine Framework
#include "CATOtherDocumentAgent.h"

// LocalFramework
#include "CAADegSampleMultiDocumentCommand.h"

// C++ Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegSampleMultiDocumentCommand);


//-------------------------------------------------------------------------

CAADegSampleMultiDocumentCommand::CAADegSampleMultiDocumentCommand() :
_AcquisitionAgent ("CAADegSampleMultiDocumentCommandId")
{
}

//-------------------------------------------------------------------------

CAADegSampleMultiDocumentCommand::~CAADegSampleMultiDocumentCommand()
{
}

//-------------------------------------------------------------------------

void CAADegSampleMultiDocumentCommand::BuildGraph()
{

	// -------------
	// Agent Creation
	// -------------

	// _fromCommand is a data of CATMultiDocumentCommand
	//
	if( NULL != _fromCommand )
	{
		// This agent has the same behavior that the behavior of the 
		// CATOtherDocumentAgent defined in the YFJCCreateJoinCmdCmd command
		// 
		_AcquisitionAgent.SetBehavior(_fromCommand->GetBehavior() | CATDlgEngWithPSOHSO);
		int iEleTypeSize = _fromCommand->GetElementTypeSize();
		if (iEleTypeSize > 0)
		{
			for (int i=1; i<=iEleTypeSize; i++)
			{
				_AcquisitionAgent.SetElementType(_fromCommand->GetElementType(i));
			}
		}
		
	}
	else
	{
		_AcquisitionAgent.SetBehavior(CATDlgEngWithPSOHSO);
	}

	//_AcquisitionAgent.SetBehavior(CATDlgEngMultiAcquisition);

	//AddCSOClient(_AcquisitionAgent);

	// This agent allows the end user to select circles
	//_AcquisitionAgent.SetElementType("CATIProduct");
	//_AcquisitionAgent.SetElementType("CATIPrtPart");
	//_AcquisitionAgent.SetElementType("CATSurface");

	// --------------
	// State Creation
	// --------------

	CATDialogState * pInitialState = GetInitialState("Select Surface");
	pInitialState->AddDialogAgent(&_AcquisitionAgent); 

	// -------------------
	// Transition Creation
	// --------------------

	CATDialogTransition *pTransition= AddTransition
		(
		pInitialState,
		NULL,
		NULL,
		Action((ActionMethod) &CAADegSampleMultiDocumentCommand::SelectionDone)
		) ;

}

//-------------------------------------------------------------------------

CATBoolean CAADegSampleMultiDocumentCommand::SelectionDone(void * iDummy)
{
	cout << "CAADegSampleMultiDocumentCommand::SelectionDone"<< endl;

	CATBoolean OKCode = FALSE;

	// The CATOtherDocumentAgent will be valuated
	//
	if (_AcquisitionAgent.GetBehavior() & CATDlgEngMultiAcquisition)
	{
		// The agent instantiated in the YFJCCreateJoinCmd command 
		// will be valuated 
		ReturnListOfValues(_AcquisitionAgent.GetListOfValues());
	}
	else
	{
		// The agent instantiated in the YFJCCreateJoinCmd command 
		// will be valuated 
		ReturnValue(_AcquisitionAgent.GetValue());
	}

	OKCode = TRUE;

	return OKCode;
}

//-------------------------------------------------------------------------
