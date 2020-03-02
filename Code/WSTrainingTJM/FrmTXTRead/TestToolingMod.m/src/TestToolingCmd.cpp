// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestToolingCmd.cpp
// The state chart based command: TestToolingCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Jan 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestToolingCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

#include "CATCreateExternalObject.h"
CATCreateClass( TestToolingCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestToolingCmd::TestToolingCmd() :
  CATStateCommand ("TestToolingCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
,_pGeneralCls(NULL)
,_pEditor(NULL)
,_pHSO(NULL)
{
	_pDlg = NULL;
	_pDlg = new TestToolingDlg();
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
TestToolingCmd::~TestToolingCmd()
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
void TestToolingCmd::BuildGraph()
{
	//对话框
	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCLOSENotification(),
		(CATCommandMethod)&TestToolingCmd::ActionExit,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetWindCloseNotification(),
		(CATCommandMethod)&TestToolingCmd::ActionExit,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCANCELNotification(),
		(CATCommandMethod)&TestToolingCmd::ActionExit,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaOKNotification(),
		(CATCommandMethod)&TestToolingCmd::ActionOK3,
		NULL);
	//PointField
	_pSelAFieldAgent = new CATDialogAgent("Select A");
	_pSelAFieldAgent->AcceptOnNotify(_pDlg->GetSelectorListLine(),
		_pDlg->GetSelectorListLine()->GetListSelectNotification());
	//SolidField
	_pSelBFieldAgent = new CATDialogAgent("Select B");
	_pSelBFieldAgent->AcceptOnNotify(_pDlg->GetSelectorListSurface(),
		_pDlg->GetSelectorListSurface()->GetListSelectNotification());
	//选择Point
	_pSelAAgent = new CATFeatureImportAgent("Select A");
	//_pPointAgent->AddElementType("CATIGSMPoint");
	_pSelAAgent->AddElementType("CATCurve");
	_pSelAAgent->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngOneShot);

	//选择Solid
	_pSelBAgent = new CATFeatureImportAgent("Select B");
	_pSelBAgent->AddElementType("CATSurface");
	//_pSolidAgent->AddElementType("CATSurface");
	//_pSolidAgent->AddElementType("CATIMechanicalTool");
	//_pSolidAgent->AddElementType("CATIMfBiDimResult");
	_pSelBAgent->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngOneShot);

	//
	CATDialogState *pSelAState = GetInitialState("Select Line");
	pSelAState->AddDialogAgent(_pSelAAgent);
	pSelAState->AddDialogAgent(_pSelAFieldAgent);
	pSelAState->AddDialogAgent(_pSelBFieldAgent);

	CATDialogState *pSelBState = AddDialogState("Select Surface");
	pSelBState->AddDialogAgent(_pSelBAgent);
	pSelBState->AddDialogAgent(_pSelAFieldAgent);
	pSelBState->AddDialogAgent(_pSelBFieldAgent);

	//
	AddTransition(pSelAState,pSelAState,
		IsOutputSetCondition(_pSelAAgent),
		Action((ActionMethod)& TestToolingCmd::selectCurveFunc));

	AddTransition(pSelBState,pSelBState,
		IsOutputSetCondition(_pSelBAgent),
		Action((ActionMethod)& TestToolingCmd::selectSurfaceFunc));

	AddTransition(pSelAState,pSelBState,
		IsOutputSetCondition(_pSelBFieldAgent),
		Action((ActionMethod)& TestToolingCmd::TransToSelectB));

	AddTransition(pSelBState,pSelAState,
		IsOutputSetCondition(_pSelAFieldAgent),
		Action((ActionMethod)& TestToolingCmd::TransToSelectA));

	////选中高亮
	//AddAnalyseNotificationCB(_pDlg->GetSelectorListPoint(),
	//	_pDlg->GetSelectorListPoint()->GetListSelectNotification(),
	//	(CATCommandMethod)&TestProjectionCmd::ActionHighlightPoint,
	//	NULL);

	//AddAnalyseNotificationCB(_pDlg->GetSelectorListSolid(),
	//	_pDlg->GetSelectorListSolid()->GetListSelectNotification(),
	//	(CATCommandMethod)&TestProjectionCmd::ActionHighlightSolid,
	//	NULL);
}


//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean TestToolingCmd::ActionOne( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------

  return TRUE;
}

CATBoolean TestToolingCmd::ActionExit(void * data)
{
	RequestDelayedDestruction();
	return TRUE;
}

CATBoolean TestToolingCmd::ActionOK(void * data)
{
	if (_spBUSelectA ==NULL_var || _spBUSelectB==NULL_var)
	{
		return FALSE;
	}
	//获取工厂
	CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();//配置指针
	CATTopData * topdata =new CATTopData(pConfig, NULL);//topdata
	CATIPrtContainer_var ospiCont=NULL_var;
	CATGeoFactory*  pGeoFactory=_pGeneralCls->GetProductGeoFactoryAndPrtCont(_spiProdSelA,ospiCont);
	if (topdata == NULL || pGeoFactory == NULL)
	{
		return FALSE;
	}
	//
	CATMathPoint pt1,pt2;
	_pGeneralCls->GetPointFromCurve(_spBUSelectA,pt1,pt2);
	CATMathVector vecDir = pt1 - pt2;
	vecDir.Normalize();
	//
	CATBody_var spBodySurface = _pGeneralCls->GetBodyFromFeature(_spBUSelectB);
	if (spBodySurface == NULL_var)
	{
		return FALSE;
	}
	//
	CATTopReflectLine *pTopReflectLine = NULL;
	CATTry
	{
		pTopReflectLine = CATCreateTopReflectLine(pGeoFactory,spBodySurface,vecDir,CATPIBY2,topdata);
		if (pTopReflectLine==NULL)
		{
			return FALSE;
		}
		pTopReflectLine->OptimizeDomainStructure();
	//CATTry
	//{
		int iValue = pTopReflectLine->Run();
		cout<<"Run Value: "<<iValue<<endl;
	}
	CATCatch(CATMfErrUpdate , pUpdateError)
	{
		return FALSE;
	}
	CATCatch(CATError , error)
	{
		delete pTopReflectLine;
		pTopReflectLine = NULL;
		CATReturnError(error);
		return FALSE;
	}
	CATEndTry;

	CATBody *pBodyResult = pTopReflectLine->GetResult();
	delete pTopReflectLine;
	pTopReflectLine = NULL;
	if (pBodyResult == NULL)
	{
		return FALSE;
	}
	//
	CATISpecObject_var spiSpecGeoSet = NULL_var;
	HRESULT rc = _pGeneralCls->CreateNewGeoSet(_spiProdSelA,"Created_By_CAA",spiSpecGeoSet);
	if (FAILED(rc)||spiSpecGeoSet==NULL_var)
	{
		return FALSE;
	}
	CATISpecObject_var spiSpecReflectLine = NULL_var;
	rc = _pGeneralCls->InsertObjOnTree(_spiProdSelA,spiSpecGeoSet,"Curve",pBodyResult,spiSpecReflectLine);
	if (FAILED(rc)||spiSpecReflectLine==NULL_var)
	{
		return FALSE;
	}
	return TRUE;
}

CATBoolean TestToolingCmd::ActionOK2(void * data)
{
	if (_spBUSelectA ==NULL_var || _spBUSelectB==NULL_var)
	{
		return FALSE;
	}
	//获取工厂
	CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();//配置指针
	CATTopData * topdata =new CATTopData(pConfig, NULL);//topdata
	CATIPrtContainer_var ospiCont=NULL_var;
	CATGeoFactory*  pGeoFactory=_pGeneralCls->GetProductGeoFactoryAndPrtCont(_spiProdSelA,ospiCont);
	if (topdata == NULL || pGeoFactory == NULL)
	{
		return FALSE;
	}
	//
	CATMathPoint pt1,pt2;
	_pGeneralCls->GetPointFromCurve(_spBUSelectA,pt1,pt2);
	CATMathVector vecDir = pt1 - pt2;
	vecDir.Normalize();
	CATMathDirection mathDir(vecDir);
	//
	CATBody_var spBodySurface = _pGeneralCls->GetBodyFromFeature(_spBUSelectB);
	if (spBodySurface == NULL_var)
	{
		return FALSE;
	}
	CATLISTP(CATSurface) lstSurface;
	HRESULT rc = _pGeneralCls->GetSurfaceFromBody(spBodySurface,lstSurface);
	for (int i=1;i<=lstSurface.Size();i++)
	{
		CATReflectCurve *pReflectCurve = NULL;
		CATCurve *pCurve = NULL;
		pReflectCurve = CATCreateReflectCurve(pGeoFactory,pConfig,lstSurface[i],mathDir,0.5*CATPI);
		if (pReflectCurve==NULL)
		{
			continue;
		}
		CATTry
		{
			pReflectCurve->Run();
			
		}
		CATCatch(CATError , error)
		{
			delete pReflectCurve;
			pReflectCurve = NULL;
			CATReturnError(error);
			continue;
		}
		CATEndTry;

		CATLONG32 lNum = pReflectCurve->GetNumberOfPCurves();
		if (0==lNum)
		{
			continue;
		}
		pReflectCurve->BeginningCurve();
		CATPCurve *pPCurve = pReflectCurve->GetPCurve();
		
		pCurve = pReflectCurve->GetCurve();
		delete pReflectCurve;
		pReflectCurve = NULL;
		if (pCurve == NULL)
		{
			continue;
		}
		CATBody *pBodyResult = NULL;
		rc = _pGeneralCls->GetBodyFromCurve(pCurve,pGeoFactory,topdata,pBodyResult);
		if (FAILED(rc)||pBodyResult==NULL)
		{
			continue;
		}
		//
		CATISpecObject_var spiSpecGeoSet = NULL_var;
		HRESULT rc = _pGeneralCls->CreateNewGeoSet(_spiProdSelA,"Created_By_CAA",spiSpecGeoSet);
		if (FAILED(rc)||spiSpecGeoSet==NULL_var)
		{
			continue;
		}
		CATISpecObject_var spiSpecReflectLine = NULL_var;
		rc = _pGeneralCls->InsertObjOnTree(_spiProdSelA,spiSpecGeoSet,"Curve",pBodyResult,spiSpecReflectLine);
		if (FAILED(rc)||spiSpecReflectLine==NULL_var)
		{
			continue;
		}
	}
	return TRUE;
}

CATBoolean TestToolingCmd::ActionOK3(void * data)
{
	if (_spBUSelectA ==NULL_var || _spBUSelectB==NULL_var)
	{
		return FALSE;
	}
	//
	CATBody *pBodyReflect = NULL;
	CATBoolean bReflect = GetReflectCurves(_spiProdSelA,_spBUSelectA,_spBUSelectB,pBodyReflect);
	if (pBodyReflect==NULL)
	{
		_pGeneralCls->MessageOutputWarning("No reflect curve result.","Warning");
		return TRUE;
	}
	CATISpecObject_var spiSpecGeoSet = NULL_var;
	HRESULT rc = _pGeneralCls->CreateNewGeoSet(_spiProdSelA,"Created_By_CAA",spiSpecGeoSet);
	if (FAILED(rc)||spiSpecGeoSet==NULL_var)
	{
		return FALSE;
	}
	CATISpecObject_var spiSpecReflectLine = NULL_var;
	rc = _pGeneralCls->InsertObjOnTree(_spiProdSelA,spiSpecGeoSet,"Curve",pBodyReflect,spiSpecReflectLine);
	if (FAILED(rc)||spiSpecReflectLine==NULL_var)
	{
		return FALSE;
	}
	return TRUE;
}

void TestToolingCmd::selectCurveFunc(void * data)
{
	CATBaseUnknown *pBUSelect = NULL;
	CATIProduct_var spiProdSelect = NULL_var;
	_pGeneralCls->TransferSelectToBU(_pSelAAgent,pBUSelect,spiProdSelect);
	if (pBUSelect == NULL || spiProdSelect == NULL_var)
	{
		_pSelAAgent->InitializeAcquisition();
		return;
	}
	_pDlg->GetSelectorListLine()->ClearLine();
	CATUnicodeString strAlias = _pGeneralCls->GetNameFromBaseUnknownFunc(pBUSelect);
	_pDlg->GetSelectorListLine()->SetLine(strAlias,-1,CATDlgDataAdd);
	int iTabRow = 0;
	_pDlg->GetSelectorListLine()->SetSelect(&iTabRow,1);
	//
	_spBUSelectA = pBUSelect;
	_spiProdSelA = spiProdSelect;
	//
	_pSelAAgent->InitializeAcquisition();
}

void TestToolingCmd::selectSurfaceFunc(void * data)
{
	CATBaseUnknown *pBUSelect = NULL;
	CATIProduct_var spiProdSelect = NULL_var;
	_pGeneralCls->TransferSelectToBU(_pSelBAgent,pBUSelect,spiProdSelect);
	if (pBUSelect == NULL || spiProdSelect == NULL_var)
	{
		_pSelBAgent->InitializeAcquisition();
		return;
	}
	_pDlg->GetSelectorListSurface()->ClearLine();
	CATUnicodeString strAlias = _pGeneralCls->GetNameFromBaseUnknownFunc(pBUSelect);
	_pDlg->GetSelectorListSurface()->SetLine(strAlias,-1,CATDlgDataAdd);
	int iTabRow = 0;
	_pDlg->GetSelectorListSurface()->SetSelect(&iTabRow,1);

	//
	_spBUSelectB = pBUSelect;
	//
	_pSelBAgent->InitializeAcquisition();
}

void TestToolingCmd::TransToSelectA(void * data)
{
	_pSelAFieldAgent->InitializeAcquisition();
	_pSelBFieldAgent->InitializeAcquisition();
	_pDlg->GetSelectorListSurface()->ClearSelect();
}

void TestToolingCmd::TransToSelectB(void * data)
{
	_pSelAFieldAgent->InitializeAcquisition();
	_pSelBFieldAgent->InitializeAcquisition();
	_pDlg->GetSelectorListLine()->ClearSelect();
}

CATBoolean TestToolingCmd::GetReflectCurves(CATIProduct_var ispiProd, CATBaseUnknown_var ispBULine, CATBaseUnknown_var ispBUSurface,CATBody* &opBodyReflect)
{
	//获取工厂
	CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();//配置指针
	CATTopData * topdata =new CATTopData(pConfig, NULL);//topdata
	CATIPrtContainer_var ospiCont=NULL_var;
	CATGeoFactory*  pGeoFactory=_pGeneralCls->GetProductGeoFactoryAndPrtCont(ispiProd,ospiCont);
	if (topdata == NULL || pGeoFactory == NULL)
	{
		return FALSE;
	}
	//根据curve获取方向
	CATMathPoint pt1,pt2;
	_pGeneralCls->GetPointFromCurve(_spBUSelectA,pt1,pt2);
	CATMathVector vecDir = pt1 - pt2;
	vecDir.Normalize();
	CATMathDirection mathDir(vecDir);
	//根据surface获取body
	CATBody_var spBodySurface = _pGeneralCls->GetBodyFromFeature(ispBUSurface);
	if (spBodySurface == NULL_var)
	{
		return FALSE;
	}
	/*
	//先用CATCreateReflectCurve判断有没有反射线的结果
	CATBoolean bFind = FALSE;
	CATLISTP(CATSurface) lstSurface;
	HRESULT rc = _pGeneralCls->GetSurfaceFromBody(spBodySurface,lstSurface);
	for (int i=1;i<=lstSurface.Size();i++)
	{
		CATReflectCurve *pReflectCurve = NULL;
		CATCurve *pCurve = NULL;
		pReflectCurve = CATCreateReflectCurve(pGeoFactory,pConfig,lstSurface[i],mathDir,CATPIBY2-0.001);
		if (pReflectCurve==NULL)
		{
			continue;
		}
		//CATTry
		//{
		//	pReflectCurve->Run();
		//}
		//CATCatch(CATError , error)
		//{
		//	delete pReflectCurve;
		//	pReflectCurve = NULL;
		//	CATReturnError(error);
		//	continue;
		//}
		//CATEndTry;

		CATLONG32 lNum = pReflectCurve->GetNumberOfPCurves();
		if (0<lNum)
		{
			bFind = TRUE;
			break;
		}
	}
	*/
	//如果有结果，用CATCreateTopReflectLine求出结果
	if (1)
	{
		CATTopReflectLine *pTopReflectLine = NULL;
		pTopReflectLine = CATCreateTopReflectLine(pGeoFactory,spBodySurface,vecDir,CATPIBY2,topdata);
		if (pTopReflectLine==NULL)
		{
			return FALSE;
		}
		pTopReflectLine->OptimizeDomainStructure();
		CATTry
		{
			int iValue = pTopReflectLine->Run();
			cout<<"Run Value: "<<iValue<<endl;
		}
		CATCatch(CATMfErrUpdate , pUpdateError)
		{
			return FALSE;
		}
		CATCatch(CATError , error)
		{
			delete pTopReflectLine;
			pTopReflectLine = NULL;
			CATReturnError(error);
			return FALSE;
		}
		CATEndTry;

		CATBody *pBodyResult = pTopReflectLine->GetResult();
		delete pTopReflectLine;
		pTopReflectLine = NULL;
		if (pBodyResult == NULL)
		{
			return FALSE;
		}
		//
		opBodyReflect = pBodyResult;
	}
	return TRUE;
}