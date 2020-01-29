// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// TestTempPointCmd.cpp
// The state chart based command: TestTempPointCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Nov 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestTempPointCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

#include "CATCreateExternalObject.h"
CATCreateClass( TestTempPointCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestTempPointCmd::TestTempPointCmd() :
  CATStateCommand ("TestTempPointCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
,_pGeneralCls(NULL)
,_pViewerFeedbackManager(NULL)
,_pSurfaceAgent(NULL),_pSurfaceFieldAgent(NULL)
,_lstBUSurface(NULL)
,_lstCellSelect(NULL)
{
	_pDlg = NULL;
	_pDlg = new TestTempPointDlg();
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);

	_pGeneralCls = new GeneralClass();

	_pISO = NULL;

	_pEditor = CATFrmEditor::GetCurrentEditor();
	_pHSO = NULL;
	if (NULL != _pEditor)
	{
		_pHSO = _pEditor->GetHSO();
		_pISO = _pEditor->GetISO();
	}

	_pViewerFeedbackManager = new YFAirventViewerFeedbackManager();
	_pViewerFeedbackManager->SetViewerFeedbackOn();

	//TestHighLight();

	cout<<"Size in CATHSO: "<<_pHSO->GetSize()<<endl;
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestTempPointCmd::~TestTempPointCmd()
{
	if (_pDlg != NULL)
	{
		_pDlg->RequestDelayedDestruction();
		_pDlg = NULL;
	}

	if (_pSurfaceAgent != NULL)
	{
		_pSurfaceAgent->RequestDelayedDestruction();
		_pSurfaceAgent = NULL;
	}

	if (_pSurfaceFieldAgent != NULL)
	{
		_pSurfaceFieldAgent->RequestDelayedDestruction();
		_pSurfaceFieldAgent = NULL;
	}

	_pISO->Empty();
	_pISO = NULL;

	_pEditor = NULL;

	_pHSO->Empty();
	_pHSO = NULL;

	if (_pGeneralCls != NULL)
	{
		delete _pGeneralCls;
		_pGeneralCls = NULL;
	}

	_pViewerFeedbackManager->SetViewerFeedbackOff();
	if (_pViewerFeedbackManager != NULL)
	{
		_pViewerFeedbackManager->Release();
		_pViewerFeedbackManager = NULL;
	}

	_lstBUSurface.RemoveAll();
	_lstBUSurface = NULL;

	_lstCellSelect.RemoveAll();
	_lstCellSelect = NULL;
}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void TestTempPointCmd::BuildGraph()
{
	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCLOSENotification(),
		(CATCommandMethod)&TestTempPointCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetWindCloseNotification(),
		(CATCommandMethod)&TestTempPointCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCANCELNotification(),
		(CATCommandMethod)&TestTempPointCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaOKNotification(),
		(CATCommandMethod)&TestTempPointCmd::ExitCmd,
		NULL);

	//Surface选择
	_pSurfaceAgent = new CATFeatureImportAgent("Select Surface");
	_pSurfaceAgent->SetElementType("CATSurface");
	//_pSurfaceAgent->SetElementType("CATCurve");
	_pSurfaceAgent->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngWithPSOHSO|CATDlgEngOneShot);

	_pSurfaceFieldAgent = new CATDialogAgent("Select Surface Field");
	_pSurfaceFieldAgent->AcceptOnNotify(_pDlg->GetSelectorListSelect(),
		_pDlg->GetSelectorListSelect()->GetListSelectNotification());

	CATDialogState *pDlgStateSurface = GetInitialState("Select");
	pDlgStateSurface->AddDialogAgent(_pSurfaceAgent);
	pDlgStateSurface->AddDialogAgent(_pSurfaceFieldAgent);

	AddTransition( pDlgStateSurface, pDlgStateSurface, 
		IsOutputSetCondition (_pSurfaceAgent),
		Action ((ActionMethod) &TestTempPointCmd::ActionSelect));

}


//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean TestTempPointCmd::ActionOne( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------

  return TRUE;
}


CATBoolean TestTempPointCmd::ExitCmd(void * data)
{
	this->RequestDelayedDestruction();
	return TRUE;
}

void TestTempPointCmd::ActionSelect(void * data)
{
	//
	_pHSO->Empty();
	_pISO->Empty();

	//
	CATBaseUnknown *pBUSelect = NULL;
	CATPathElement *pPath = _pSurfaceAgent->GetValue();
	pBUSelect = _pSurfaceAgent->GetElementValue(pPath);

	CATUnicodeString strAlias = _pGeneralCls->GetNameFromBaseUnknownFunc(pBUSelect);

	FindMechanicalToolFromPath(pPath);

	_pDlg->GetSelectorListSelect()->ClearLine();

	_pDlg->GetSelectorListSelect()->SetLine(strAlias,-1,CATDlgDataAdd);

	int iTabRow = 0;
	_pDlg->GetSelectorListSelect()->SetSelect(&iTabRow,1);

	//先获取鼠标拾取点，全局，用于虚拟点位置标识，实际用途按需转为局部点
	CATMathPoint ptScreenGlobal =_pViewerFeedbackManager->GetScreenPickedPoint();
	
	//模型上画出虚拟点，CATISO高亮
	DumITempPoint *piTempPoint = NULL;
	HRESULT rc = ::CATInstantiateComponent("DumTempPointComp", IID_DumITempPoint, (void**)&piTempPoint);
	if (SUCCEEDED(rc) && piTempPoint != NULL)
	{
		piTempPoint->SetDatas(&ptScreenGlobal);
		CATISpecObject_var spiSpecTempPoint = piTempPoint;
		_pISO->AddElement(spiSpecTempPoint);
	}

	//
	//_pGeneralCls->SetHighlight(pBUSelect);
	_pGeneralCls->SetHighlight(pBUSelect,_pEditor,_pHSO);	//此处无法用VB高亮曲面，可能由于上面用了ISO高亮了虚拟点
	//
	//ShowResults(pBUSelect);
	//PrintVariousInfo(pBUSelect);

	_pSurfaceAgent->InitializeAcquisition();
}

void TestTempPointCmd::ActionSelect2(void * data)
{
	//
	_pHSO->Empty();
	_pISO->Empty();
	//
	CATBaseUnknown *pBUSelect = NULL;
	CATPathElement *pPath = _pSurfaceAgent->GetValue();
	pBUSelect = _pSurfaceAgent->GetElementValue(pPath);
	//
	CATISpecObject_var spiSpecMechTool = _pGeneralCls->GetMechanicalToolFromPath(pPath);
	if (spiSpecMechTool == NULL_var)
	{
		return;
	}
	CATBody_var spBodyMechTool = _pGeneralCls->GetBodyFromFeature(spiSpecMechTool);
	if (spBodyMechTool == NULL_var)
	{
		return;
	}
	//
	CATBaseUnknown_var spBUObj = pBUSelect;
	if (spBUObj == NULL_var)
	{
		return;
	}
	CATBody_var spBody = _pGeneralCls->GetBodyFromFeature(spBUObj);
	if (spBody != NULL_var)
	{
		CATLISTP(CATCell) lstCell;
		spBody->GetAllCells(lstCell,2);
		for (int i=1;i<=lstCell.Size();i++)
		{
			int iOccur = _lstCellSelect.NbOccur(lstCell[i]);
			if (iOccur == 0)
			{
				_lstCellSelect.Append(lstCell[i]);
			}
			else
			{
				for (int j=1;j<=_lstCellSelect.Size();j++)
				{
					if (lstCell[i] == _lstCellSelect[j])
					{
						_lstCellSelect.RemovePosition(j);
						break;
					}
				}
			}
		}
	}
	_pGeneralCls->SetHighlightCells(spBodyMechTool,_lstCellSelect,2);

	//
	_pSurfaceAgent->InitializeAcquisition();
}


//根据选择对象的路径，找到所属的最高一级的实体body
HRESULT TestTempPointCmd::FindMechanicalToolFromPath(CATPathElement *ipPath)
{
	HRESULT rc = S_OK;
	if (ipPath!=NULL)
	{
		ipPath->InitToTopElement();
		CATBaseUnknown *pObject = ipPath->GetNextChildObject();
		for (;pObject!=NULL;pObject=ipPath->GetNextChildObject())
		{
			CATIMechanicalTool_var spiMechTool = pObject;
			if (spiMechTool != NULL_var)
			{
				CATISpecObject_var spiSpecMechTool = spiMechTool;
				if (spiSpecMechTool!=NULL_var)
				{
					CATIAlias_var spiAlias = spiSpecMechTool;
					if (spiAlias != NULL_var)
					{
						cout<<"Belong to: "<<spiAlias->GetAlias()<<endl;
						break;
					}
				}
			}
		}
	}
	//
	//CATBaseUnknown *pMechanicalTool = ipPath->FindElement(IID_CATIMechanicalTool);
	//if (pMechanicalTool != NULL)
	//{
	//	CATIMechanicalTool_var spiMechTool = pMechanicalTool;
	//	if (spiMechTool != NULL_var)
	//	{
	//		CATISpecObject_var spiSpecMechTool = spiMechTool;
	//		if (spiSpecMechTool!=NULL_var)
	//		{
	//			CATIAlias_var spiAlias = spiSpecMechTool;
	//			if (spiAlias != NULL_var)
	//			{
	//				cout<<"Belong to: "<<spiAlias->GetAlias()<<endl;
	//			}
	//		}
	//	}
	//}
	return rc;
}

//根据颜色自动高亮对应的面
void TestTempPointCmd::TestHighLight()
{
	CATIProduct_var spiProdRoot = NULL_var;
	_pGeneralCls->GetRootProductUpdate(spiProdRoot);
	if (spiProdRoot == NULL_var)
	{
		RequestDelayedDestruction();
		return;
	}
	cout<<spiProdRoot->GetPartNumber()<<endl;
	CATIPrtContainer_var  spRootContainer = _pGeneralCls->GetPrtContainer(spiProdRoot);
	if( spRootContainer == NULL_var )
	{
		cout <<"# Get Container error !" << endl;
		return;
	}

	CATISpecObject_var spiSpecOnPart = spRootContainer -> GetPart();
	if (spiSpecOnPart == NULL_var)
	{
		cout<<"Get Part Failed!"<<endl;
		return;
	}
	CATIPartRequest *piPartRequest = NULL;
	CATListValCATBaseUnknown_var lstBodies = NULL;
	HRESULT rc = spiSpecOnPart->QueryInterface(IID_CATIPartRequest,(void**) &piPartRequest);
	if (FAILED(rc) || piPartRequest == NULL)
	{
		return;
	}
	piPartRequest->GetSolidBodies("",lstBodies);
	piPartRequest->Release();
	piPartRequest = NULL;
	//获取头一个实体作为测试对象
	if (lstBodies.Size()==0)
	{
		return;
	}
	CATISpecObject_var spCurrObj = lstBodies[1];
	if (spCurrObj == NULL_var)
	{
		return;
	}
	//获取所有二维的cell
	CATBody_var spBody = _pGeneralCls->GetBodyFromFeature(spCurrObj);
	if (spBody == NULL_var)
	{
		return;
	}
	CATLISTP(CATCell) lstCell;
	spBody->GetAllCells(lstCell,2);
	if (lstCell.Size()==0)
	{
		return;
	}
	int iCountColor = 0;
	for (int i=1; i<= lstCell.Size(); i++)
	{
		CATFace_var spFace = lstCell[i];
		if (spFace == NULL_var)
		{
			continue;
		}
		CATBaseUnknown_var spBUFace = spFace;
		if (spBUFace == NULL_var)
		{
			continue;
		}
		/*
		double dblCrvRadiusMin,dblCrvRadiusMax;
		rc = _pGeneralCls->GetCrvRadiusOnSurface(spFace,dblCrvRadiusMin,dblCrvRadiusMax);
		if (SUCCEEDED(rc))
		{
			cout<<"Rmin: "<<dblCrvRadiusMin<<"   Rmax: "<<dblCrvRadiusMax<<endl;
		}
		if (dblCrvRadiusMin < 2.8 || dblCrvRadiusMin > 3.2)
		{
			continue;
		}
		*/
		//
		CATIBRepAccess_var spiBrepAcess  =NULL_var;
		spiBrepAcess = CATBRepDecodeCellInBody(spFace,spBody);
		if (spiBrepAcess == NULL_var)
		{
			continue;
		}
		unsigned int iRed,iGreen,iBlue;
		rc = _pGeneralCls->GetColorOnBRepObject(spiBrepAcess,iRed,iGreen,iBlue);
		if (SUCCEEDED(rc)&&iRed==0&&iGreen==0&&iBlue==0)
		{
			iCountColor++;
			//
			CATIFeaturize_var  spToFeaturize  =  spiBrepAcess;
			if  (NULL_var  ==  spToFeaturize)
			{
				continue;
			}
			CATISpecObject_var spiSpecOnCell  =  spToFeaturize->FeaturizeR(MfPermanentBody|MfDefaultFeatureSupport |MfRelimitedFeaturization|MfDuplicateFeature);    //目前只能按照这样的枚举值特征化，后面才能高亮
			//CATISpecObject_var spiSpecOnCell  =  spToFeaturize->FeaturizeR();
			//CATISpecObject_var spiSpecOnCell  =  spToFeaturize->FeaturizeR(MfNoDuplicateFeature | MfPermanentBody | MfSelectingFeatureSupport | MfFunctionalFeaturization);
			CATBaseUnknown *pBU = NULL;
			rc = spiSpecOnCell->QueryInterface(IID_CATBaseUnknown,(void**)&pBU);
			if (SUCCEEDED(rc)&&pBU != NULL)
			{
				_pGeneralCls->SetHighlight(pBU);	//目前只能用vb方法高亮成功，caa方法暂时都无法高亮
				//_pGeneralCls->SetGroupHighlight(pBU,_pEditor,_pHSO);
				/*
				CATPathElement *pPathElem = new CATPathElement(pBU);
				if (pPathElem!=NULL)
				{
					_pHSO->AddElements(pPathElem);
					_pHSO->EndAddElements();
				}
				*/
				//_pGeneralCls->SetGroupHighlightFromSpecObj(spiSpecOnCell,_pEditor,_pHSO);
				_lstCellSelect.Append(lstCell[i]);
			}
			/*
			CATIMechanicalFeature *piMechanicalFeature = NULL;
			rc = spiSpecOnCell->QueryInterface( IID_CATIMechanicalFeature, (void**) &piMechanicalFeature );
			if (SUCCEEDED(rc)&&piMechanicalFeature!=NULL)
			{
				CATPathElement *pPathElement = piMechanicalFeature->BuildPathElement();
				piMechanicalFeature->Release(); 			
				piMechanicalFeature = NULL ;
				if (pPathElement != NULL)
				{   // the geometrical element corresponding to the active field is now highlighted
					CATUnicodeString strPath = "";
					_pGeneralCls->PathElementString(pPathElement,strPath);
					cout<<"Highlight Path: "<<strPath<<endl;
					//
					_pHSO->AddElement(pPathElement);
					pPathElement->Release();
					pPathElement = NULL ;
				}
			}
			*/
			//
			CATISpecObject_var spiSpecFather = spiSpecOnCell->GetFather();
			if (spiSpecFather != NULL_var)
			{
				CATIAlias_var spiAlias = spiSpecFather;
				cout<<"Father Name: "<<spiAlias->GetAlias()<<endl;
			}
		}

		//rc = _pGeneralCls->GetColorOnObject(spiSpecOnCell,iRed,iGreen,iBlue);
		//if (SUCCEEDED(rc)&&iRed==0&&iGreen==0&&iBlue==0)
		//{
		//	iCountColor++;
		//}
		//AddHSO(spiSpecOnCell);
		//
	}
}