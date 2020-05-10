// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestMeasurementCmd.cpp
// The state chart based command: TestMeasurementCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  May 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestMeasurementCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

#include "CATCreateExternalObject.h"
CATCreateClass( TestMeasurementCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestMeasurementCmd::TestMeasurementCmd() :
  CATStateCommand ("TestMeasurementCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
,_pGeneralCls(NULL)
,_pEditor(NULL)
,_pHSO(NULL)
{
	_pDlg = NULL;
	_pDlg = new TestMeasurementDlg();
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);

	_pSelAAgent = NULL;
	_pSelBAgent = NULL;
	_pSelAFieldAgent = NULL;
	_pSelBFieldAgent = NULL;

	_pGeneralCls = new GeneralClass();

	_pEditor = CATFrmEditor::GetCurrentEditor();

	if (NULL!=_pEditor)
	{
		_pHSO = _pEditor->GetHSO();
	}
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestMeasurementCmd::~TestMeasurementCmd()
{
	if (_pDlg != NULL)
	{
		_pDlg->RequestDelayedDestruction();
		_pDlg = NULL;
	}

	if (_pGeneralCls != NULL)
	{
		delete _pGeneralCls;
		_pGeneralCls = NULL;
	}

	_pEditor = NULL;

	_pHSO->Empty();
	_pHSO = NULL;

	if (_pSelAAgent != NULL)
	{
		_pSelAAgent->RequestDelayedDestruction();
		_pSelAAgent = NULL;
	}

	if (_pSelAFieldAgent != NULL)
	{
		_pSelAFieldAgent->RequestDelayedDestruction();
		_pSelAFieldAgent = NULL;
	}

	if (_pSelBAgent != NULL)
	{
		_pSelBAgent->RequestDelayedDestruction();
		_pSelBAgent = NULL;
	}

	if (_pSelBFieldAgent != NULL)
	{
		_pSelBFieldAgent->RequestDelayedDestruction();
		_pSelBFieldAgent = NULL;
	}
}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void TestMeasurementCmd::BuildGraph()
{
	//对话框
	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCLOSENotification(),
		(CATCommandMethod)&TestMeasurementCmd::ActionExit,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetWindCloseNotification(),
		(CATCommandMethod)&TestMeasurementCmd::ActionExit,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCANCELNotification(),
		(CATCommandMethod)&TestMeasurementCmd::ActionExit,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaOKNotification(),
		(CATCommandMethod)&TestMeasurementCmd::ActionOK,
		NULL);
	//
	_pSelAFieldAgent = new CATDialogAgent("Select A");
	_pSelAFieldAgent->AcceptOnNotify(_pDlg->GetSelectorListObjA(),
		_pDlg->GetSelectorListObjA()->GetListSelectNotification());
	//
	_pSelBFieldAgent = new CATDialogAgent("Select B");
	_pSelBFieldAgent->AcceptOnNotify(_pDlg->GetSelectorListObjB(),
		_pDlg->GetSelectorListObjB()->GetListSelectNotification());
	//选择Point
	_pSelAAgent = new CATFeatureImportAgent("Select A");
	//_pPointAgent->AddElementType("CATIGSMPoint");
	_pSelAAgent->AddElementType("CATIProduct");
	_pSelAAgent->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngOneShot);

	//选择Solid
	_pSelBAgent = new CATFeatureImportAgent("Select B");
	_pSelBAgent->AddElementType("CATIProduct");
	//_pSolidAgent->AddElementType("CATSurface");
	//_pSolidAgent->AddElementType("CATIMechanicalTool");
	//_pSolidAgent->AddElementType("CATIMfBiDimResult");
	_pSelBAgent->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngOneShot);

	//
	CATDialogState *pSelAState = GetInitialState("Select A");
	pSelAState->AddDialogAgent(_pSelAAgent);
	pSelAState->AddDialogAgent(_pSelAFieldAgent);
	pSelAState->AddDialogAgent(_pSelBFieldAgent);

	CATDialogState *pSelBState = AddDialogState("Select B");
	pSelBState->AddDialogAgent(_pSelBAgent);
	pSelBState->AddDialogAgent(_pSelAFieldAgent);
	pSelBState->AddDialogAgent(_pSelBFieldAgent);

	//
	AddTransition(pSelAState,pSelAState,
		IsOutputSetCondition(_pSelAAgent),
		Action((ActionMethod)& TestMeasurementCmd::selectObjAFunc));

	AddTransition(pSelBState,pSelBState,
		IsOutputSetCondition(_pSelBAgent),
		Action((ActionMethod)& TestMeasurementCmd::selectObjBFunc));

	AddTransition(pSelAState,pSelBState,
		IsOutputSetCondition(_pSelBFieldAgent),
		Action((ActionMethod)& TestMeasurementCmd::TransToSelectB));

	AddTransition(pSelBState,pSelAState,
		IsOutputSetCondition(_pSelAFieldAgent),
		Action((ActionMethod)& TestMeasurementCmd::TransToSelectA));
}


//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean TestMeasurementCmd::ActionOne( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------

  return TRUE;
}

CATBoolean TestMeasurementCmd::ActionExit(void * data)
{
	RequestDelayedDestruction();
	return TRUE;
}

CATBoolean TestMeasurementCmd::ActionOK(void * data)
{
	CATMathPoint oPt1,oPt2;
	double oDist = 9999;

	HRESULT rc = this->GetMinDistanceByMeasure(_spBUSelectA,_spiProdSelA,_spBUSelectB,_spiProdSelB,oPt1,oPt2,oDist);

	cout<<"Min. Distance: "<<oDist<<endl;
	
	return TRUE;
}

void TestMeasurementCmd::selectObjAFunc(void * data)
{
	CATBaseUnknown *pBUSelect = NULL;
	CATIProduct_var spiProdSelect = NULL_var;
	_pGeneralCls->TransferSelectToBU(_pSelAAgent,pBUSelect,spiProdSelect);
	if (pBUSelect == NULL || spiProdSelect == NULL_var)
	{
		_pSelAAgent->InitializeAcquisition();
		return;
	}
	_pDlg->GetSelectorListObjA()->ClearLine();
	CATUnicodeString strAlias = _pGeneralCls->GetNameFromBaseUnknownFunc(pBUSelect);
	_pDlg->GetSelectorListObjA()->SetLine(strAlias,-1,CATDlgDataAdd);
	int iTabRow = 0;
	_pDlg->GetSelectorListObjA()->SetSelect(&iTabRow,1);
	//
	_spBUSelectA = pBUSelect;
	_spiProdSelA = spiProdSelect;
	//
	_pSelAAgent->InitializeAcquisition();
}

void TestMeasurementCmd::selectObjBFunc(void * data)
{
	CATBaseUnknown *pBUSelect = NULL;
	CATIProduct_var spiProdSelect = NULL_var;
	_pGeneralCls->TransferSelectToBU(_pSelBAgent,pBUSelect,spiProdSelect);
	if (pBUSelect == NULL || spiProdSelect == NULL_var)
	{
		_pSelBAgent->InitializeAcquisition();
		return;
	}
	_pDlg->GetSelectorListObjB()->ClearLine();
	CATUnicodeString strAlias = _pGeneralCls->GetNameFromBaseUnknownFunc(pBUSelect);
	_pDlg->GetSelectorListObjB()->SetLine(strAlias,-1,CATDlgDataAdd);
	int iTabRow = 0;
	_pDlg->GetSelectorListObjB()->SetSelect(&iTabRow,1);

	//
	_spBUSelectB = pBUSelect;
	_spiProdSelB = spiProdSelect;
	//
	_pSelBAgent->InitializeAcquisition();
}

void TestMeasurementCmd::TransToSelectA(void * data)
{
	_pSelAFieldAgent->InitializeAcquisition();
	_pSelBFieldAgent->InitializeAcquisition();
	_pDlg->GetSelectorListObjB()->ClearSelect();
}

void TestMeasurementCmd::TransToSelectB(void * data)
{
	_pSelAFieldAgent->InitializeAcquisition();
	_pSelBFieldAgent->InitializeAcquisition();
	_pDlg->GetSelectorListObjA()->ClearSelect();
}

//使用specobj的测量方法测量，带坐标变换
HRESULT TestMeasurementCmd::GetMinDistanceByMeasure(CATISpecObject_var ispiSpec1,CATIProduct_var ispiProd1,CATISpecObject_var ispiSpec2,CATIProduct_var ispiProd2,CATMathPoint &omathPt1,CATMathPoint &omathPt2,double &oDistance)
{
	CATIMeasurableInContext_var spMeasurableInContext1 = ispiSpec1;
	CATIMeasurableInContext_var spMeasurableInContext2 = ispiSpec2;
	CATIMeasurable_var spMeasurable2 = ispiSpec2;
	if (spMeasurableInContext1 == NULL_var) return E_FAIL;
	if (spMeasurableInContext2 == NULL_var) return E_FAIL;
	if (spMeasurable2 == NULL_var) return E_FAIL;

	CATMathTransformation transAbsObj1 = this->GetAbsTransformation(ispiProd1);
	CATMathTransformation transAbsObj2 = this->GetAbsTransformation(ispiProd2);
	CATMathAxis axisAbsObj1 = transAbsObj1 * CATMathOIJK;
	CATMathAxis axisAbsObj2 = transAbsObj2 * CATMathOIJK;

	CATMathTransformation transObj2ToObj1 = CATMathTransformation(axisAbsObj1,CATMathOIJK) * CATMathTransformation(CATMathOIJK,axisAbsObj2);

	//关键步骤，需要把测量元素1先set到全局坐标系下
	spMeasurableInContext1->SetAxisSystemOnMeasurable(axisAbsObj1);

	CATMathAxis ioAxis;
	double oMinDis = 9999.0;

	ioAxis = transObj2ToObj1 * axisAbsObj1;
	//spMeasurableInContext2->GetAxisSystemFromMeasurable(ioAxis);
	//
	//CATMathTransformation transAxis = this->GetMatrixTransformation(ispiProd2,ispiProd1);		//注意，该处坐标需要从2变换到1内
	//ioAxis = transAxis * ioAxis;

	//该处输入的坐标系是测量元素2的全局坐标系
	spMeasurableInContext1->MinimumDistance(spMeasurable2,axisAbsObj2,oMinDis,omathPt1,omathPt2);	//这里输出的两个点坐标都是在1内的坐标，后续可以按需变换到全局或变换到2
	oDistance = oMinDis;

	return S_OK;
}

CATMathTransformation TestMeasurementCmd::GetMatrixTransformation( CATISpecObject_var spSpecOne, CATISpecObject_var spSpecTwo )
{
	CATIMovable_var spiMovableOne(spSpecOne);
	if(spiMovableOne == NULL_var) 
	{
		cout<<"Failed to Get Movable."<<endl;
		return NULL;
	}

	CATIMovable_var spiMovableTwo(spSpecTwo);
	if(spiMovableTwo == NULL_var) {
		cout<<"Failed to Get Movable."<<endl;
		return NULL;
	}

	CATMathTransformation pMathTrans = spiMovableOne->GetPosition(spiMovableTwo, CATPrd3D, TRUE);

	return pMathTrans;
}

CATMathTransformation TestMeasurementCmd::GetAbsTransformation( CATISpecObject_var ispSpecOne )
{
	CATMathTransformation pMathTrans;

	if(ispSpecOne==NULL_var)
		return pMathTrans;

	CATIMovable_var spiMovableOne(ispSpecOne);
	if(spiMovableOne == NULL_var) 
	{
		cout<<"Failed to Get Movable."<<endl;
		return NULL;
	}

	spiMovableOne->GetAbsPosition(pMathTrans);

	return pMathTrans;
}