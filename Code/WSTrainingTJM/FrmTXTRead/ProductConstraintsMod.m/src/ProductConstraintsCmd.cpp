// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// ProductConstraintsCmd.cpp
// The state chart based command: ProductConstraintsCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Jan 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "ProductConstraintsCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

#include "CATCreateExternalObject.h"
#include "CATIPrtPart.h"





CATCreateClass( ProductConstraintsCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
ProductConstraintsCmd::ProductConstraintsCmd() :
  CATStateCommand ("ProductConstraintsCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
  ,_Indication(NULL)
{
	_pDlg = NULL;
	_pDlg = new ProductConstraintsDlg();
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);

	_pFeaImpAgtLine = NULL;
	_pFeaImpAgtFace = NULL;
	_pDlgAgtLine = NULL;
	_pDlgAgtFace = NULL;

	_pEditor = CATFrmEditor::GetCurrentEditor();
	_pHSO = NULL;
	if (NULL != _pEditor)
	{
		_pHSO = _pEditor->GetHSO();
	}

	_spiProductLine = NULL_var;
	_spiProductFace = NULL_var;
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
ProductConstraintsCmd::~ProductConstraintsCmd()
{
   if (_Indication != NULL) 
      _Indication->RequestDelayedDestruction();

   if (_pDlg != NULL)
   {
	   _pDlg->RequestDelayedDestruction();
	   _pDlg = NULL;
   }

   if (_pFeaImpAgtLine != NULL)
   {
	   _pFeaImpAgtLine->RequestDelayedDestruction();
	   _pFeaImpAgtLine = NULL;
   }

   if (_pFeaImpAgtFace != NULL)
   {
	   _pFeaImpAgtFace->RequestDelayedDestruction();
	   _pFeaImpAgtFace = NULL;
   }

   if (_pDlgAgtLine != NULL)
   {
	   _pDlgAgtLine->RequestDelayedDestruction();
	   _pDlgAgtLine = NULL;
   }

   if (_pDlgAgtFace != NULL)
   {
	   _pDlgAgtFace->RequestDelayedDestruction();
	   _pDlgAgtFace = NULL;
   }

   _pEditor = NULL;

   _pHSO = NULL;

   _spSpecLine = NULL_var;
   _spSpecFace = NULL_var;

   

}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void ProductConstraintsCmd::BuildGraph()
{
	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCLOSENotification(),
		(CATCommandMethod)&ProductConstraintsCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetWindCloseNotification(),
		(CATCommandMethod)&ProductConstraintsCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCANCELNotification(),
		(CATCommandMethod)&ProductConstraintsCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaOKNotification(),
		(CATCommandMethod)&ProductConstraintsCmd::ActionOK,
		NULL);
	//点选选择框高亮相关元素
	AddAnalyseNotificationCB(_pDlg->GetSelectorListSelectLine(),
		_pDlg->GetSelectorListSelectLine()->GetListSelectNotification(),
		(CATCommandMethod)&ProductConstraintsCmd::ActionHightlightLine,
		NULL);
	//点选选择框高亮相关元素
	AddAnalyseNotificationCB(_pDlg->GetSelectorListSelectFace(),
		_pDlg->GetSelectorListSelectFace()->GetListSelectNotification(),
		(CATCommandMethod)&ProductConstraintsCmd::ActionHightlightFace,
		NULL);

	//
	_pFeaImpAgtLine = new CATFeatureImportAgent("Select a Line",NULL,NULL,MfNoDuplicateFeature);
	_pFeaImpAgtFace = new CATFeatureImportAgent("Select a Face");

	_pDlgAgtLine = new CATDialogAgent("Select Dialog Agent Line");
	_pDlgAgtFace = new CATDialogAgent("Select Dialog Agent Face");

	//
	_pFeaImpAgtLine->SetOrderedElementType("CATIGSMLine"); //可以选取模型树上的直线
	_pFeaImpAgtLine->AddOrderedElementType("CATLine"); // 可以选取实体上的边线或者孔的轴线

	_pFeaImpAgtFace->SetOrderedElementType("CATIGSMPlane");
	_pFeaImpAgtFace->AddOrderedElementType("CATPlane");
	//
	_pFeaImpAgtLine->SetBehavior(CATDlgEngWithPrevaluation | CATDlgEngWithCSO     | CATDlgEngOneShot);
	_pFeaImpAgtLine->SetAgentBehavior(MfPermanentBody     | MfLastFeatureSupport      | MfRelimitedFeaturization   );

	_pFeaImpAgtFace->SetBehavior(CATDlgEngWithPrevaluation | CATDlgEngWithCSO     | CATDlgEngOneShot);
	_pFeaImpAgtFace->SetAgentBehavior(MfPermanentBody     | MfLastFeatureSupport      | MfRelimitedFeaturization   );
	//
	_pDlgAgtLine->AcceptOnNotify(_pDlg->GetSelectorListSelectLine(),_pDlg->GetSelectorListSelectLine()->GetListSelectNotification());
	_pDlgAgtFace->AcceptOnNotify(_pDlg->GetSelectorListSelectFace(),_pDlg->GetSelectorListSelectFace()->GetListSelectNotification());
	//
	CATDialogState *pDlgStateLine = GetInitialState("Select a Line");
	pDlgStateLine->AddDialogAgent(_pFeaImpAgtLine);
	pDlgStateLine->AddDialogAgent(_pDlgAgtLine);
	pDlgStateLine->AddDialogAgent(_pDlgAgtFace);

	CATDialogState *pDlgStateFace = AddDialogState("Select a Face");
	pDlgStateFace->AddDialogAgent(_pFeaImpAgtFace);
	pDlgStateFace->AddDialogAgent(_pDlgAgtLine);
	pDlgStateFace->AddDialogAgent(_pDlgAgtFace);

	//
	AddTransition(pDlgStateLine,pDlgStateLine,
		IsOutputSetCondition(_pFeaImpAgtLine),
		Action((ActionMethod)& ProductConstraintsCmd::ActionSelectLine));

	AddTransition(pDlgStateFace,pDlgStateFace,
		IsOutputSetCondition(_pFeaImpAgtFace),
		Action((ActionMethod)& ProductConstraintsCmd::ActionSelectFace));

	AddTransition(pDlgStateLine,pDlgStateFace,
		IsOutputSetCondition(_pDlgAgtFace),
		Action((ActionMethod)& ProductConstraintsCmd::SwitchToFaceSelect));

	AddTransition(pDlgStateFace,pDlgStateLine,
		IsOutputSetCondition(_pDlgAgtLine),
		Action((ActionMethod)& ProductConstraintsCmd::SwitchToLineSelect));
}


//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean ProductConstraintsCmd::ActionOne( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------

  return TRUE;
}

void ProductConstraintsCmd::ExitCmd(void * data)
{
	this->RequestDelayedDestruction();
}

void ProductConstraintsCmd::ActionOK(void * data)
{
	////获取根product
	//CATIProduct *piRootProduct = NULL;
	//HRESULT rc = GetRootProduct(piRootProduct);
	//if (FAILED(rc) || piRootProduct == NULL)
	//{
	//	return;
	//}
	//获得插入Part的路径
	CATUnicodeString strFolderName = "Template";
	CATUnicodeString strFileName = "Screw.CATPart";
	CATUnicodeString strFilePath = "";
	HRESULT rc = GetResourseFile(strFilePath,strFileName,strFolderName);
	if (strFilePath == "")
	{
		return;
	}
	//在当前所选元素所在的Product平级插入Part
	CATIProduct_var spFatherProduct = _spiProductLine->GetFatherProduct();
	CATIProduct *piProductInsert = NULL;
	rc = Import(spFatherProduct,strFilePath,piProductInsert);
	if (FAILED(rc))
	{
		return;
	}
	cout<<piProductInsert->GetPartNumber()<<endl;
	//获取该Part下的两个发布元素
	CATISpecObject_var spSpecPubLine = NULL_var;
	CATISpecObject_var spSpecPubFace = NULL_var;
	rc = GetPublications(piProductInsert,spSpecPubLine,spSpecPubFace);
	if (spSpecPubLine == NULL_var || spSpecPubFace == NULL_var)
	{
		return;
	}
	CATIAlias_var spAliasLine = spSpecPubLine;
	CATUnicodeString strAliasLine = spAliasLine->GetAlias();
	cout<<"Publications:  "<<strAliasLine<<endl;
	//先做Fix约束
	rc = ConstraintFix(spFatherProduct,_spiProductLine);
	if (FAILED(rc))
	{
		return;
	}
	//和用户鼠标选取的两个元素进行约束
	rc = ConstraintCoincidence(spFatherProduct,_spiProductLine,_spSpecLine,piProductInsert,spSpecPubLine);
	if (FAILED(rc))
	{
		return;
	}
	rc = ConstraintCoincidence(spFatherProduct,_spiProductLine,_spSpecFace,piProductInsert,spSpecPubFace);
	if (FAILED(rc))
	{
		return;
	}
	//刷新模型树
	//CATIProduct_var spRootProduct = piRootProduct;
	rc = RedrawSpecTree(spFatherProduct);

	cout<<_spiProductLine->GetPartNumber()<<endl;
	ExitCmd(data);
}

void ProductConstraintsCmd::ActionSelectLine()
{
	//
	if (_pHSO != NULL)
	{
		_pHSO->Empty();
	}
	//
	//SelectElement(_pFeaImpAgtLine,_spSpecLine);
	SelectElementUpdate(_pFeaImpAgtLine,_spSpecLine,_spiProductLine);
	//
	CATIAlias_var spAlias = _spSpecLine;
	CATUnicodeString strAlias = "";
	if (spAlias != NULL_var)
	{
		strAlias = spAlias->GetAlias();
	}
	_pDlg->GetSelectorListSelectLine()->ClearLine();
	_pDlg->GetSelectorListSelectLine()->SetLine(strAlias,-1,CATDlgDataAdd);
	//
	SetHighlight(_pFeaImpAgtLine);
	//
	_pFeaImpAgtLine->InitializeAcquisition();
	//
	if (_spSpecFace == NULL_var)
	{
		int iTabRow = 0;
		_pDlg->GetSelectorListSelectFace()->SetSelect(&iTabRow,1);
	}
	return;
}

void ProductConstraintsCmd::ActionSelectFace()
{
	//
	if (_pHSO != NULL)
	{
		_pHSO->Empty();
	} 
	//
	SelectElement(_pFeaImpAgtFace,_spSpecFace);
	//
	CATIAlias_var spAlias = _spSpecFace;
	CATUnicodeString strAlias = "";
	if (spAlias != NULL_var)
	{
		strAlias = spAlias->GetAlias();
	}
	_pDlg->GetSelectorListSelectFace()->ClearLine();
	_pDlg->GetSelectorListSelectFace()->SetLine(strAlias,-1,CATDlgDataAdd);
	//
	SetHighlight(_pFeaImpAgtFace);
	//
	_pFeaImpAgtFace->InitializeAcquisition();
	//
		if (_spSpecLine == NULL_var)
	{
		int iTabRow = 0;
		_pDlg->GetSelectorListSelectLine()->SetSelect(&iTabRow,1);
	}
	return;
}

void ProductConstraintsCmd::ActionHightlightLine()
{
	//SetHighlight(_pFeaImpAgtLine);
	SetHighlightUpdate(_spSpecLine);
	_pDlgAgtLine->InitializeAcquisition();
	_pDlg->GetSelectorListSelectFace()->ClearSelect();
}

void ProductConstraintsCmd::ActionHightlightFace()
{
	//SetHighlight(_pFeaImpAgtFace);
	SetHighlightUpdate(_spSpecFace);
	_pFeaImpAgtFace->InitializeAcquisition();
	_pDlg->GetSelectorListSelectLine()->ClearSelect();
}

void ProductConstraintsCmd::SwitchToFaceSelect()
{
	_pDlgAgtFace->InitializeAcquisition();
	_pDlgAgtLine->InitializeAcquisition();
	_pDlg->GetSelectorListSelectLine()->ClearSelect();

	return;
}

void ProductConstraintsCmd::SwitchToLineSelect()
{
	_pDlgAgtFace->InitializeAcquisition();
	_pDlgAgtLine->InitializeAcquisition();
	_pDlg->GetSelectorListSelectFace()->ClearSelect();

	return;
}

//选择元素，转换成SpecObj
void ProductConstraintsCmd::SelectElement(CATFeatureImportAgent *pFeatAgent,CATISpecObject_var &spSpecOnSelection) 
{
	HRESULT rc = E_FAIL;

	if (pFeatAgent == NULL)
	{
		return;
	}
	CATISpecObject *piSpecOnSelection = NULL;
	CATPathElement *pPath = pFeatAgent->GetValue();
	CATBaseUnknown *pSelection = pFeatAgent->GetElementValue(pPath);
	//CATBaseUnknown *pSelection = pFeatAgent->GetElementValue(pFeatAgent->GetValue());
	if (NULL != pSelection)
	{
		rc = pSelection->QueryInterface(IID_CATISpecObject,(void**)&piSpecOnSelection);
		//转换为空时，说明选择的是Brep元素，需要特征化
		if (piSpecOnSelection == NULL)
		{
			CATIBRepAccess *pBRepAccess = NULL;
			rc = pSelection -> QueryInterface(IID_CATIBRepAccess, (void**) & pBRepAccess);
			CATIFeaturize_var spToFeaturize = pBRepAccess;
			if (NULL_var != spToFeaturize)
			{
				piSpecOnSelection = spToFeaturize->FeaturizeR(MfNoDuplicateFeature | MfTemporaryBody | MfSelectingFeatureSupport | MfFunctionalFeaturization);
			}
		}
		spSpecOnSelection = piSpecOnSelection;
	}
}

//选择元素，转换成SpecObj，并同时返回所属Product
void ProductConstraintsCmd::SelectElementUpdate(CATFeatureImportAgent *pFeatAgent,CATISpecObject_var &spSpecOnSelection, CATIProduct_var &ospProductSeletion) 
{
	HRESULT rc = E_FAIL;

	if (pFeatAgent == NULL)
	{
		return;
	}
	CATISpecObject *piSpecOnSelection = NULL;
	CATPathElement *pPath = pFeatAgent->GetValue();
	CATBaseUnknown *pSelection = pFeatAgent->GetElementValue(pPath);
	//CATBaseUnknown *pSelection = pFeatAgent->GetElementValue(pFeatAgent->GetValue());
	//转换成SpecObj
	if (NULL != pSelection)
	{
		rc = pSelection->QueryInterface(IID_CATISpecObject,(void**)&piSpecOnSelection);
		//转换为空时，说明选择的是Brep元素，需要特征化
		if (piSpecOnSelection == NULL)
		{
			CATIBRepAccess *pBRepAccess = NULL;
			rc = pSelection -> QueryInterface(IID_CATIBRepAccess, (void**) & pBRepAccess);
			CATIFeaturize_var spToFeaturize = pBRepAccess;
			if (NULL_var != spToFeaturize)
			{
				piSpecOnSelection = spToFeaturize->FeaturizeR(MfNoDuplicateFeature | MfTemporaryBody | MfSelectingFeatureSupport | MfFunctionalFeaturization);
			}
		}
		spSpecOnSelection = piSpecOnSelection;
	}
	//返回所属Product
	CATBaseUnknown *pProduct = pPath->FindElement(IID_CATIProduct);
	if (pProduct == NULL)
	{
		pProduct = pPath->FindElement(IID_CATIPrtPart);
		if (pProduct == NULL)
		{
			return;
		}
		CATIPrtPart_var spPart = pProduct;
		if (spPart == NULL_var)
		{
			return;
		}
		CATISpecObject_var spPartObject = spPart->GetProduct();
		if (spPartObject == NULL_var)
		{
			return;
		}
		ospProductSeletion = spPartObject;
	}
	ospProductSeletion = pProduct;
}

//
void ProductConstraintsCmd::SetHighlight(CATFeatureImportAgent *ipFeatImpAgt)
{

	CATPathElement* pPathEle = NULL;
	pPathEle = ipFeatImpAgt->GetValue();
	if (pPathEle != NULL)
	{
		_pHSO->Empty();
		_pHSO->AddElements(pPathEle);
		_pHSO->EndAddElements();
	}
}

//点击Selectorlist后高亮选择元素
void ProductConstraintsCmd::SetHighlightUpdate(CATISpecObject_var ispSpecSelect)
{
	if (_pHSO != NULL)
	{
		_pHSO->Empty();
	}

	if ((ispSpecSelect != NULL_var) && (_pEditor != NULL) && (_pHSO != NULL))
	{
		CATIBuildPath *piBuildPath = NULL;
		HRESULT rc = ispSpecSelect->QueryInterface(IID_CATIBuildPath,(void**) &piBuildPath);
		if (SUCCEEDED(rc))
		{
			CATPathElement context = _pEditor->GetUIActiveObject();
			CATPathElement *pPathElement = NULL;

			rc = piBuildPath->ExtractPathElement(&context,&pPathElement);
			if (pPathElement != NULL)
			{
				_pHSO->AddElement(pPathElement);
				pPathElement->Release();
				pPathElement = NULL;
			}
			piBuildPath->Release();
			piBuildPath = NULL;
		}
	}

}

/* Fix约束示例
void ProductConstraintsCmd::ActionOK(void * data)
{
	////Fix约束试验
	//获取根product
	CATIProduct *piRootProduct = NULL;
	HRESULT rc = GetRootProduct(piRootProduct);
	if (FAILED(rc) || piRootProduct == NULL)
	{
		return;
	}
	//获得头一个child
	CATListValCATBaseUnknown_var *lstChildren = NULL;
	lstChildren = piRootProduct->GetChildren();
	if (lstChildren->Size() == 0)
	{
		return;
	}
	CATIProduct_var spChild = (*lstChildren)[1];
	CATIProduct_var spRefChild = spChild->GetReferenceProduct();
	CATIProduct *piChild = NULL;
	rc = spRefChild->QueryInterface(IID_CATIProduct,(void**)&piChild);
	if (piChild == NULL)
	{
		return;
	}
	//建立connector
	CATILinkableObject *pGeom = NULL;
	rc = spRefChild->QueryInterface(IID_CATILinkableObject,(void**)&pGeom);
	if (FAILED(rc))
	{
		return;
	}
	CATIConnector *pConnector = NULL;
	int iCreation = 0;
	::GetProductConnector(pGeom,piChild,piRootProduct,0,pConnector,iCreation);
	if (pConnector == NULL)
	{
		return;
	}
	//创建Fix约束
	CATICst *pCstFix = NULL;
	CATLISTV(CATBaseUnknown_var) lstConnector = NULL;
	lstConnector.Append(pConnector);
	rc = ::CreateConstraint(catCstTypeReference,lstConnector,NULL,piRootProduct,&pCstFix);
	if (FAILED(rc))
	{
		return;
	}
	ExitCmd(data);
}
*/
HRESULT ProductConstraintsCmd::GetRootProduct(CATIProduct *&opiRootProduct)
{
	//获取Document
	CATFrmEditor *pEditor = CATFrmEditor::GetCurrentEditor();
	if (pEditor == NULL)
	{
		return E_FAIL;
	}
	CATDocument *pDoc = pEditor->GetDocument();
	if (pDoc == NULL)
	{
		return E_FAIL;
	}

	//获取根元素集合的第一个，就是根product,最终要转到CATIProduct
	CATIDocRoots *piDocRootsOnDoc = NULL;
	HRESULT rc = pDoc->QueryInterface(IID_CATIDocRoots,(void**)&piDocRootsOnDoc);
	if (FAILED(rc))
	{
		return E_FAIL;
	}
	CATListValCATBaseUnknown_var *pRootProducts = piDocRootsOnDoc->GiveDocRoots();
	CATIProduct_var spRootProduct = NULL_var;
	if (pRootProducts->Size())
	{
		spRootProduct = (*pRootProducts)[1];
		delete pRootProducts;
		pRootProducts = NULL;
	}

	piDocRootsOnDoc->Release();

	//CATIProduct *piProductOnRoot = NULL;
	rc = spRootProduct->QueryInterface(IID_CATIProduct, (void**)&opiRootProduct);
	if (FAILED(rc) || piDocRootsOnDoc == NULL)
	{
		return E_FAIL;
	}

	return S_OK;
}

//获取插入的Screw的路径
HRESULT ProductConstraintsCmd::GetResourseFile(CATUnicodeString &CATEnvPath,CATUnicodeString FileFullName,CATUnicodeString folderName)
{
	if(CATUnicodeString("") == FileFullName)
	{
		return E_FAIL;
	}

	//从环境变量中获取路径
	CATUnicodeString strSearchPath("");
	char* value = NULL;
	if ( CATLibSuccess == CATGetEnvValue("CATGraphicPath", &value ))//通过读取环境变量中参数值
	{
		strSearchPath = value;
		CATUnicodeString strName = "";
		strName.Append(folderName);
		strName.Append("\\");
		strName.Append(FileFullName);
		const char * pFilePath = ::CATFindPath(strName,value);	  

		if (value!=NULL)
		{
			delete value;
			value = NULL;
		}
		CATEnvPath = pFilePath;
		return S_OK;
	}
	else
	{		 
		return E_FAIL;
	}
}

//插入指定路径下的Product到当前某一Product下
HRESULT ProductConstraintsCmd::Import (const CATIProduct_var& ihProductTarget, const CATUnicodeString& strPath, CATIProduct *& oProduct)
{

	HRESULT rc = S_OK;

	CATDocument* ptDocument = NULL;
	rc = CATDocumentServices::OpenDocument(strPath, ptDocument, TRUE);

	if ( FAILED (rc) || !ptDocument ) 
	{
		return rc; // if method failed exit
	} 
	if (ptDocument) 
	{
		CATIAProducts_var hRootProducts (ihProductTarget);  
		if(NULL_var == hRootProducts) 
		{
			return rc;
		}

		CATIADocument *pCAADocument = NULL;
		rc = ptDocument->QueryInterface(IID_CATIADocument, (void **)&pCAADocument);
		if ( FAILED (rc) || !pCAADocument ) 
		{
			return rc;
		}

		CATIAProduct * pInstantiatedProduct = NULL;
		rc = hRootProducts->AddExternalComponent(pCAADocument, pInstantiatedProduct);
		if ( FAILED (rc) || !pInstantiatedProduct ) 
		{
			return rc;
		}
		pCAADocument->Release();       
		rc = pInstantiatedProduct->QueryInterface(IID_CATIProduct, (void**)& oProduct);
		if ( FAILED (rc) || !oProduct )
		{
			return rc;
		}
		pInstantiatedProduct->Release();
	}
	return rc;
}

//刷新模型树
HRESULT ProductConstraintsCmd::RedrawSpecTree(CATIProduct_var& iNodeProd)
{
	if(iNodeProd == NULL_var)return E_FAIL;

	CATIModelEvents_var spModleEventOnProduct(iNodeProd);
	if (spModleEventOnProduct == NULL_var)
	{
		return E_FAIL;
	}
	CATModify event(iNodeProd);

	spModleEventOnProduct->Dispatch(event);

	CATIRedrawEvent_var spRedrawEventOnProduct(iNodeProd);
	if (spRedrawEventOnProduct == NULL_var)
	{
		return E_FAIL;
	}
	spRedrawEventOnProduct->Redraw();

	return S_OK;
}

//获得product下的publish元素
//获取的CATBaseUnknown先转connecotr，再获取linkableobj，最后转到SpecObj
HRESULT ProductConstraintsCmd::GetPublications(CATIProduct_var ispProduct, CATISpecObject_var &ospLine, CATISpecObject_var &ospFace)
{
	HRESULT rc = S_OK;
	CATIPrdObjectPublisher *piPublisher = NULL;
	rc = ispProduct->QueryInterface(IID_CATIPrdObjectPublisher,(void**)&piPublisher);
	if (FAILED(rc) || piPublisher == NULL)
	{
		return E_FAIL;
	}
	//
	CATBaseUnknown *pPubLine = NULL;
	CATUnicodeString strSubPubLine = "";
	//int iReturn = piPublisher->GetDirectObject("Axis",pPubLine,strSubPubLine);
	pPubLine = piPublisher->GetFinalObject("Axis");
	//获取的CATBaseUnknown先转connecotr，再获取linkableobj，最后转到SpecObj
	CATIConnector_var spiConnectorLine = pPubLine;
	if (spiConnectorLine == NULL_var)
	{
		return E_FAIL;
	}
	CATILinkableObject_var spiLinkObjLine = spiConnectorLine->GiveReferenceObject();
	if (spiLinkObjLine == NULL_var)
	{
		return E_FAIL;
	}
	ospLine = spiLinkObjLine;
	//
	CATBaseUnknown *pPubFace = NULL;
	CATUnicodeString strSubPubFace = "";
	//iReturn = piPublisher->GetDirectObject("Plane",pPubFace,strSubPubFace);
	pPubFace = piPublisher->GetFinalObject("Plane");
	CATIConnector_var spiConnectorFace = pPubFace;
	if (spiConnectorFace == NULL_var)
	{
		return E_FAIL;
	}
	CATILinkableObject_var spiLinkObjFace = spiConnectorFace->GiveReferenceObject();
	if (spiLinkObjFace == NULL_var)
	{
		return E_FAIL;
	}
	ospFace = spiLinkObjFace;
	return rc;
}

//进行Coincidence约束
HRESULT ProductConstraintsCmd::ConstraintCoincidence(CATIProduct_var ispFatherProduct, CATIProduct_var ispProduct1 ,CATISpecObject_var ispSpecElem1, CATIProduct_var ispProduct2, CATISpecObject_var ispSpecElem2)
{
	HRESULT rc = S_OK;
	//创建connector1
	CATIConnector *piConnector1 = NULL;
	CATILinkableObject *piLinkObj1 = NULL;
	rc = ispSpecElem1->QueryInterface(IID_CATILinkableObject, (void**)&piLinkObj1);
	if (piLinkObj1 == NULL)
	{
		return E_FAIL;
	}
	int iCreation1 = 0;
	rc = ::GetProductConnector(piLinkObj1,ispProduct1,ispFatherProduct,0,piConnector1,iCreation1);
	if (piConnector1 == NULL)
	{
		return E_FAIL;
	}
	//创建connector2
	CATIConnector *piConnector2 = NULL;
	CATILinkableObject *piLinkObj2 = NULL;
	rc = ispSpecElem2->QueryInterface(IID_CATILinkableObject, (void**)&piLinkObj2);
	if (piLinkObj2 == NULL)
	{
		return E_FAIL;
	}
	int iCreation2 = 0;
	rc = ::GetProductConnector(piLinkObj2,ispProduct2,ispFatherProduct,0,piConnector2,iCreation2);
	if (piConnector2 == NULL)
	{
		return E_FAIL;
	}
	//创建相合约束
	CATLISTV(CATBaseUnknown_var) lstConnector = NULL;
	lstConnector.Append(piConnector1);
	lstConnector.Append(piConnector2);
	CATICst *piCstCoin = NULL;
	rc = ::CreateConstraint(catCstTypeOn,lstConnector,NULL,ispFatherProduct,&piCstCoin);
	if (FAILED(rc) || piCstCoin == NULL)
	{
		return E_FAIL;
	}
	//刷新
	CATISpecObject_var spSpecObj = ispFatherProduct;
	spSpecObj->Update();
	return rc;
}

HRESULT ProductConstraintsCmd::ConstraintFix(CATIProduct_var ispiFatherProduct, CATIProduct_var ispiProductFix)
{
	HRESULT rc = S_OK;
	//建立connector
	CATILinkableObject *pGeom = NULL;
	rc = ispiProductFix->QueryInterface(IID_CATILinkableObject,(void**)&pGeom);
	if (FAILED(rc))
	{
		return E_FAIL;
	}
	CATIConnector *pConnector = NULL;
	int iCreation = 0;
	::GetProductConnector(pGeom,ispiProductFix,ispiFatherProduct,0,pConnector,iCreation);
	if (pConnector == NULL)
	{
		return E_FAIL;
	}
	//创建Fix约束
	CATICst *pCstFix = NULL;
	CATLISTV(CATBaseUnknown_var) lstConnector = NULL;
	lstConnector.Append(pConnector);
	rc = ::CreateConstraint(catCstTypeReference,lstConnector,NULL,ispiFatherProduct,&pCstFix);
	if (FAILED(rc))
	{
		return E_FAIL;
	}
	return rc;
}

//从模型树上的元素返回出FatherProduct
HRESULT ProductConstraintsCmd::GetRootFatherProduct(CATISpecObject_var ispSpecElem, CATIProduct_var &ospRootFatherProduct)
{
	HRESULT rc = S_OK;
	CATISpecObject *piRoot = NULL;
	piRoot = ispSpecElem->GetRootFather();
	if (piRoot == NULL)
	{
		return E_FAIL;
	}
	CATIPrtPart_var spPart = NULL_var;
	rc = piRoot->QueryInterface(IID_CATIPrtPart,(void**)&spPart);
	if (FAILED(rc) || spPart == NULL_var)
	{
		return E_FAIL;
	}
	CATIProduct_var spProduct = spPart->GetProduct();
	ospRootFatherProduct = spProduct;
	piRoot->Release();
	piRoot = NULL;
	return rc;
}

//通过PathElement返回所属的FatherProduct
////返回不出，pPath为空，所以直接写在了选择里面
HRESULT ProductConstraintsCmd::GetRootFatherProductFromPathElement(CATFeatureImportAgent *ipFeatImpAgent, CATIProduct_var &ospiRootFatherProduct)
{
	HRESULT rc = S_OK;
	CATPathElement *pPath = ipFeatImpAgent->GetValue();
	if (pPath == NULL)
	{
		return E_FAIL;
	}
	CATIProduct *piProduct = NULL;
	pPath->Search(IID_CATIProduct,(void**)&piProduct);
	if (piProduct == NULL)
	{
		return E_FAIL;
	}
	ospiRootFatherProduct = piProduct;

	return rc;
}