// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestTessellationCmd.cpp
// The state chart based command: TestTessellationCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Mar 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestTessellationCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

#include "CATCreateExternalObject.h"
CATCreateClass( TestTessellationCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestTessellationCmd::TestTessellationCmd() :
  CATStateCommand ("TestTessellationCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
,_pDlg(NULL)
,_pGeneralCls(NULL)
,_pSurfaceAgent(NULL),_pSurfaceFieldAgent(NULL)
,_pHSO(NULL),_pISO(NULL)
,_pEditor(NULL)
,_pViewer(NULL)
,_p3DBagRep(NULL)
{
	_pDlg = new TestTessellationDlg();
	_pDlg->Build();
	_pDlg->SetVisibility(CATDlgShow);

	_pGeneralCls = new GeneralClass();

	_pEditor = CATFrmEditor::GetCurrentEditor();
	if (NULL != _pEditor)
	{
		_pHSO = _pEditor->GetHSO();
		_pISO = _pEditor->GetISO();
	}

	CATFrmLayout *pFrmLayout = CATFrmLayout::GetCurrentLayout();
	CATFrmWindow *pFrmWindow=pFrmLayout->GetCurrentWindow();
	_pViewer=pFrmWindow->GetViewer();

	_p3DBagRep = new CAT3DBagRep();

}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestTessellationCmd::~TestTessellationCmd()
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

	

	if (_p3DBagRep!=NULL)
	{
		_p3DBagRep->Empty();
		delete _p3DBagRep;
		_p3DBagRep = NULL;
	}

	_pViewer=NULL;
}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void TestTessellationCmd::BuildGraph()
{
	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCLOSENotification(),
		(CATCommandMethod)&TestTessellationCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetWindCloseNotification(),
		(CATCommandMethod)&TestTessellationCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaCANCELNotification(),
		(CATCommandMethod)&TestTessellationCmd::ExitCmd,
		NULL);

	AddAnalyseNotificationCB(_pDlg,
		_pDlg->GetDiaOKNotification(),
		(CATCommandMethod)&TestTessellationCmd::ActionOK,
		NULL);


	//Surface选择
	_pSurfaceAgent = new CATFeatureImportAgent("Select Surface");
	_pSurfaceAgent->SetElementType("CATSurface");
	//_pSurfaceAgent->SetElementType("CATCurve");
	_pSurfaceAgent->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngWithPSOHSO|CATDlgEngOneShot);

	_pSurfaceFieldAgent = new CATDialogAgent("Select Surface Field");
	_pSurfaceFieldAgent->AcceptOnNotify(_pDlg->GetSelectorListSurface(),
		_pDlg->GetSelectorListSurface()->GetListSelectNotification());

	CATDialogState *pDlgStateSurface = GetInitialState("Select");
	pDlgStateSurface->AddDialogAgent(_pSurfaceAgent);
	pDlgStateSurface->AddDialogAgent(_pSurfaceFieldAgent);

	AddTransition( pDlgStateSurface, pDlgStateSurface, 
		IsOutputSetCondition (_pSurfaceAgent),
		Action ((ActionMethod) &TestTessellationCmd::ActionSurfaceSelect));
}


//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean TestTessellationCmd::ActionOne( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------

  return TRUE;
}

CATBoolean TestTessellationCmd::ExitCmd(void * data)
{
	this->RequestDelayedDestruction();
	return TRUE;
}

CATBoolean TestTessellationCmd::ActionOK(void * data)
{
	if (_pHSO!=NULL)
	{
		_pHSO->Empty();
	}
	if (_pISO!=NULL)
	{
		_pISO->Empty();
	}
	this->CreateTessellation(_spBUSurface);
	return TRUE;
}

void TestTessellationCmd::ActionSurfaceSelect(void * data)
{
	//
	CATFrmEditor *pEditor = CATFrmEditor::GetCurrentEditor();
	if (pEditor!=NULL)
	{
		CATHSO *pHSO = pEditor->GetHSO();
		pHSO->Empty();
	}

	//
	CATBaseUnknown *pBUSelect = NULL;
	CATPathElement *pPath = _pSurfaceAgent->GetValue();
	pBUSelect = _pSurfaceAgent->GetElementValue(pPath);
	if (pBUSelect!=NULL)
	{
		_spBUSurface = pBUSelect;

		CATUnicodeString strAlias = _pGeneralCls->GetNameFromBaseUnknownFunc(pBUSelect);

		_pDlg->GetSelectorListSurface()->ClearLine();

		_pDlg->GetSelectorListSurface()->SetLine(strAlias,-1,CATDlgDataAdd);

		int iTabRow = 0;
		_pDlg->GetSelectorListSurface()->SetSelect(&iTabRow,1);

		//
		_pGeneralCls->SetHighlight(pBUSelect);
	}

	//
	_pSurfaceAgent->InitializeAcquisition();
}

HRESULT TestTessellationCmd::CreateTessellation(CATBaseUnknown_var ispBUElement)
{
	HRESULT rc = S_OK;
	//
	if (ispBUElement==NULL_var)
	{
		return E_FAIL;
	}
	CATBody_var spBody = _pGeneralCls->GetBodyFromFeature(ispBUElement);
	if (spBody==NULL_var)
	{
		return E_FAIL;
	}
	CAT3DBagRep* pBagRep = new CAT3DBagRep();
	//Tessleate the body
	double iStep   = 1;
	double sag=	10;
	//CATBodyTessellator * pTessellator = new CATBodyTessellator(spBody,sag);
	CATCellTessellator * pTessellator = new CATCellTessellator(sag);
	if( NULL == pTessellator ) 
	{
		cout << "==> Create CATCellTessellator error !" << endl;
		return E_FAIL;
	}
	//Set the step to the CATCellTessellator.
	pTessellator->SetStep(iStep);
	cout << "==> The step is: " << iStep << endl;

	//Add face to the CATCellTessellator.
	CATLISTP(CATCell) cells;
	spBody->GetAllCells( cells,2); 
	int numberOfCells = cells.Size();
	cout <<"==> Number of face: " << numberOfCells << endl;
	for (int ifa=1 ; ifa<=numberOfCells ; ifa++)
	{
		pTessellator->AddFace((CATFace *)(cells[ifa]));
	}
	//Run the CATCellTessellator
	pTessellator->Run();



	//CATISpecObject_var spLine;
	// For every face.
	for(int i=1;i<=numberOfCells;i++) {
		cout << "==> Face: " << i << endl;
		// for each face, retrieve the tessellation results.
		CATFace * piFace = (CATFace*) cells[i];
		if( NULL == piFace )
		{
			return E_FAIL;
		}
		//Get the result.
		CATBoolean isPlanar;
		CATTessPointIter *    pVertices  = NULL;
		CATTessStripeIter *   pStrips    = NULL;
		CATTessFanIter *      pFans      = NULL;
		CATTessPolyIter *     pPolygons  = NULL;
		CATTessTrianIter *    pTriangles = NULL;
		short side;
		pTessellator->GetFace(piFace,isPlanar,&pVertices,&pStrips,&pFans,&pPolygons,&pTriangles,&side);		//获得的点都是局部坐标，按需转成全局

		if (NULL==pVertices)
		{
			continue;
		}

		//获取所有点和法向的基础信息
		float  (* aCoord)[3] = NULL;
		float  (* aNormal)[3] = NULL;
		int     * aNuPts     = NULL;
		CATLONG32 nbp = 0;

		nbp=pVertices->GetNbPoint();
		aCoord = new float[nbp][3];
		aNormal = new float[nbp][3];
		pVertices->GetPointXyzAll(aCoord);	//获得所有的离散点
		pVertices->GetPointNorAll(aNormal);	//获得每个离散点处的法向

		//2维列表变成1维列表
		int verticesArraySize=3*nbp;
		int normalsArraySize=3*nbp;

		cout << "  ==> Total point: " << nbp << endl;

		float *vertices=new float[verticesArraySize];
		float *normals=new float[normalsArraySize];
		for(int j=0;j<nbp;j++) {
			for(int k=0;k<3;k++) {
				vertices[3*j+k] = aCoord[j][k];
				normals[3*j+k] = aNormal[j][k];
			}
		}

		/*   循环画点
		int iNum = 0;
		while (0 == (pVertices->IsExhausted()))
		{
			const double *aCoord = pVertices->GetPointXyz();
			//模型上画出虚拟点，CATISO高亮
			DumITempPoint *piTempPoint = NULL;
			HRESULT rc = ::CATInstantiateComponent("DumTempPointComp", IID_DumITempPoint, (void**)&piTempPoint);
			if (SUCCEEDED(rc) && piTempPoint != NULL)
			{
				piTempPoint->SetDatas(&CATMathPoint(*aCoord,*(aCoord+1),*(aCoord+2)));
				_pISO->AddElement(piTempPoint);
			}
			pVertices->GoToNext();
			iNum++;
		}

		cout<<"==> Vertex number: "<<iNum<<endl;
		*/


		//Create GP for every three points.
		CAT3DCustomRep * pSurfacicRep = new CAT3DCustomRep();
		CATGraphicAttributeSet ag;
		int red,green,blue;
		ag.SetType(2);
		ag.SetColor(TRUECOLOR);
		
		if (NULL!=pStrips)		//注：strip点的顺序为从一端开始z字型
		{
			// size of the maximum allocation
			CATLONG32 nbs=0;
			while (0==(pStrips->IsExhausted()))
			{
				nbs=CATMax(nbs,pStrips->GetStriNbPts());
				pStrips->GoToNext();
			}
			//
			// allocation
			//
			aNuPts=new int[nbs];
			//
			// from the beginning again to retrieve the results
			//
			int iNumStrips = 0;
			pStrips->Reset();
			while (0==(pStrips->IsExhausted()))
			{	
				nbs=pStrips->GetStriNbPts();

				pStrips->GetStriNuPts(aNuPts);		//获得strip的按顺序的每个点在所有点的列表里面的rank位置
				// interior lines of the strip
				for (int j=0;j<nbs-1;j++)
				{
					DumITempLine *piTempLine = NULL;
					rc = ::CATInstantiateComponent("DumTempLineComp", IID_DumITempLine, (void**)&piTempLine);
					if (SUCCEEDED(rc) && piTempLine != NULL)
					{
						CATMathPoint mathPt1( aCoord[aNuPts[j]][0]  ,aCoord[aNuPts[j]][1]  ,aCoord[aNuPts[j]][2]);
						CATMathPoint mathPt2( aCoord[aNuPts[j+1]][0],aCoord[aNuPts[j+1]][1],aCoord[aNuPts[j+1]][2]);
						piTempLine->SetDatas(&mathPt1,&mathPt2,4,0,0,0,1);
						_pISO->AddElement(piTempLine);
					}

					cout<<"Point Rank: "<<aNuPts[j]<<endl;
					
				}
				// boundary of the strip

				for (j=0;j<nbs-2;j=j+2)
				{
					DumITempLine *piTempLine = NULL;
					rc = ::CATInstantiateComponent("DumTempLineComp", IID_DumITempLine, (void**)&piTempLine);
					if (SUCCEEDED(rc) && piTempLine != NULL)
					{
						CATMathPoint mathPt1( aCoord[aNuPts[j]][0]  ,aCoord[aNuPts[j]][1]  ,aCoord[aNuPts[j]][2]);
						CATMathPoint mathPt2( aCoord[aNuPts[j+2]][0],aCoord[aNuPts[j+2]][1],aCoord[aNuPts[j+2]][2]);
						piTempLine->SetDatas(&mathPt1,&mathPt2,4,0,0,0,1);
						_pISO->AddElement(piTempLine);
					}
				}


				for (j=1;j<nbs-2;j=j+2)
				{
					DumITempLine *piTempLine = NULL;
					rc = ::CATInstantiateComponent("DumTempLineComp", IID_DumITempLine, (void**)&piTempLine);
					if (SUCCEEDED(rc) && piTempLine != NULL)
					{
						CATMathPoint mathPt1( aCoord[aNuPts[j]][0]  ,aCoord[aNuPts[j]][1]  ,aCoord[aNuPts[j]][2]);
						CATMathPoint mathPt2( aCoord[aNuPts[j+2]][0],aCoord[aNuPts[j+2]][1],aCoord[aNuPts[j+2]][2]);
						piTempLine->SetDatas(&mathPt1,&mathPt2,4,0,0,0,1);
						_pISO->AddElement(piTempLine);
					}
				}

				pStrips->GoToNext();
				iNumStrips++;

				//循环创建三角形face GP
				for (int j=0;j<nbs-2;j++)
				{
					int triangleArraySize = 3;
					int triangle[3];	//三角形面的3个顶点，每个顶点对应vertices列表里面的x坐标的序号，然后会依次往后推出y和z，因为xyz都放在一个列表中，所以是3倍的关系
					triangle[0] = 3*aNuPts[j];
					triangle[1] = 3*aNuPts[j+1];
					triangle[2] = 3*aNuPts[j+2];
					//Create the GP
					CAT3DFaceGP *faceGP=NULL;
					faceGP = new CAT3DFaceGP(vertices,verticesArraySize,normals,normalsArraySize,triangle,triangleArraySize,NULL,0,NULL,NULL,0,NULL,
											NULL,3,GET_VERTICES|GET_NORMALS,NULL);
					if (NULL==faceGP)
					{
						cout << "==> Create CAT3DFaceGP error !" << endl;
						continue;
					}
					red = 0;
					green = 0;
					blue = 0;
					ag.SetColorRGBA(red,green,blue,255);

					//
					pSurfacicRep->AddGP(faceGP,ag);

				}
				
			}
			delete [] aNuPts;
			aNuPts = NULL;

			cout<<"==> Strip number: "<<iNumStrips<<endl;
		}

		/*
		if(NULL != pTriangles)
		{
			int iNumTriangles = 0;
			pTriangles->Reset();
			while (0==(pTriangles->IsExhausted()))
			{	
				int aNuP[3];
				pTriangles->GetTrianNuPts(aNuP);

				DumITempLine *piTempLine1 = NULL;
				rc = ::CATInstantiateComponent("DumTempLineComp", IID_DumITempLine, (void**)&piTempLine1);
				if (SUCCEEDED(rc) && piTempLine1 != NULL)
				{
					CATMathPoint mathPt1( aCoord[aNuP[0]][0],aCoord[aNuP[0]][1],aCoord[aNuP[0]][2]);
					CATMathPoint mathPt2( aCoord[aNuP[1]][0],aCoord[aNuP[1]][1],aCoord[aNuP[1]][2]);
					piTempLine1->SetDatas(&mathPt1,&mathPt2,4,0,0,0,1);
					_pISO->AddElement(piTempLine1);
				}

				DumITempLine *piTempLine2 = NULL;
				rc = ::CATInstantiateComponent("DumTempLineComp", IID_DumITempLine, (void**)&piTempLine2);
				if (SUCCEEDED(rc) && piTempLine2 != NULL)
				{
					CATMathPoint mathPt1( aCoord[aNuP[1]][0],aCoord[aNuP[1]][1],aCoord[aNuP[1]][2]);
					CATMathPoint mathPt2( aCoord[aNuP[2]][0],aCoord[aNuP[2]][1],aCoord[aNuP[2]][2]);
					piTempLine2->SetDatas(&mathPt1,&mathPt2,4,0,0,0,1);
					_pISO->AddElement(piTempLine2);
				}

				DumITempLine *piTempLine3 = NULL;
				rc = ::CATInstantiateComponent("DumTempLineComp", IID_DumITempLine, (void**)&piTempLine3);
				if (SUCCEEDED(rc) && piTempLine3 != NULL)
				{
					CATMathPoint mathPt1( aCoord[aNuP[0]][0],aCoord[aNuP[0]][1],aCoord[aNuP[0]][2]);
					CATMathPoint mathPt2( aCoord[aNuP[2]][0],aCoord[aNuP[2]][1],aCoord[aNuP[2]][2]);
					piTempLine3->SetDatas(&mathPt1,&mathPt2,4,0,0,0,1);
					_pISO->AddElement(piTempLine3);
				}

				pTriangles->GoToNext();
				iNumTriangles++;
			}
			cout<<"==> Triangle number: "<<iNumTriangles<<endl;

		}
		

		//Fans
		if(NULL != pFans)		//注：fan的形状是以列表中第一个点位中心点，然后分别朝其他的放射连接；当fan是封闭的类似电风扇的形状时，第二个点和最后一个点坐标是一样的，但是是算作2个点
		{
			// size of the maximum allocation
			CATLONG32 nbs=0;
			while (0==(pFans->IsExhausted()))
			{
				cout << pFans->GetFanNbPts() << endl;
				nbs=CATMax(nbs,pFans->GetFanNbPts());
				pFans->GoToNext();
			}
			//
			// allocation
			//
			aNuPts=new int[nbs];

			// from the beginning again to retrieve the results
			//
			int iNumFans = 0;
			pFans->Reset();
			while (0==(pFans->IsExhausted()))
			{	
				nbs=pFans->GetFanNbPts();

				pFans->GetFanNuPts(aNuPts);
				// 
				int iNumLines = 0;
				for (int j=0;j<nbs-2;j++)
				{
					DumITempLine *piTempLine1 = NULL;
					rc = ::CATInstantiateComponent("DumTempLineComp", IID_DumITempLine, (void**)&piTempLine1);
					if (SUCCEEDED(rc) && piTempLine1 != NULL)
					{
						CATMathPoint mathPt1( aCoord[aNuPts[0]][0],aCoord[aNuPts[0]][1]  ,aCoord[aNuPts[0]][2]);
						CATMathPoint mathPt2( aCoord[aNuPts[j+1]][0],aCoord[aNuPts[j+1]][1],aCoord[aNuPts[j+1]][2]);
						piTempLine1->SetDatas(&mathPt1,&mathPt2,4,0,0,0,1);
						_pISO->AddElement(piTempLine1);
						iNumLines++;
					}

					DumITempLine *piTempLine2 = NULL;
					rc = ::CATInstantiateComponent("DumTempLineComp", IID_DumITempLine, (void**)&piTempLine2);
					if (SUCCEEDED(rc) && piTempLine2 != NULL)
					{
						CATMathPoint mathPt1( aCoord[aNuPts[j+1]][0]  ,aCoord[aNuPts[j+1]][1]  ,aCoord[aNuPts[j+1]][2]);
						CATMathPoint mathPt2( aCoord[aNuPts[j+2]][0],aCoord[aNuPts[j+2]][1],aCoord[aNuPts[j+2]][2]);
						piTempLine2->SetDatas(&mathPt1,&mathPt2,4,0,0,0,1);
						_pISO->AddElement(piTempLine2);
						iNumLines++;
					}
				}
				DumITempLine *piTempLine = NULL;
				rc = ::CATInstantiateComponent("DumTempLineComp", IID_DumITempLine, (void**)&piTempLine);
				if (SUCCEEDED(rc) && piTempLine != NULL)
				{
					CATMathPoint mathPt1( aCoord[aNuPts[0]][0]  ,aCoord[aNuPts[0]][1]  ,aCoord[aNuPts[0]][2]);
					CATMathPoint mathPt2( aCoord[aNuPts[nbs-1]][0],aCoord[aNuPts[nbs-1]][1],aCoord[aNuPts[nbs-1]][2]);
					piTempLine->SetDatas(&mathPt1,&mathPt2,4,0,0,0,1);
					_pISO->AddElement(piTempLine);
					iNumLines++;
				}

				pFans->GoToNext();

				iNumFans++;

				cout<<"No. "<<i<<" Fan Line Number: "<<iNumLines<<endl;
			}
			delete [] aNuPts;
			aNuPts = NULL;

			cout<<"==> Fan number: "<<iNumFans<<endl;
		}
		*/

		//CAT3DRep * pRep=NULL;
		//CreateSurfaceRep(isPlanar,side, pVertices, pStrips,pFans, pPolygons, pTriangles,pRep);

		//if (NULL!=pRep)
		//{
		//	if (NULL== pBagRep) pBagRep = new CAT3DBagRep();
		//	pBagRep->AddChild(*pRep);
		//}

		CAT3DRep *p3DRep = pSurfacicRep;

		_p3DBagRep->AddChild(*p3DRep);

		if (NULL!=aCoord)
		{
			delete []aCoord;
		}
		if (NULL!=aNormal)
		{
			delete []aNormal;
		}
	}
	delete pTessellator;   pTessellator = NULL;


	//Display the surface by real model.
	if( _p3DBagRep == NULL )
	{
		return E_FAIL;
	}

	//Remove the old CATRep
	//CATI3DGeometricalElement_var spGeoEle=ispBUElement;
	//CATI3DGeoVisu_var spGeoVis = spGeoEle;
	//if( spGeoVis == NULL_var ) {
	//	cout << "==> Get CATI3DGeoVisu error !" << endl;
	//	return E_FAIL;
	//}
	//CATRep *pOldRep=spGeoVis->GiveRep();
	//if( pOldRep == NULL ) {
	//	cout << "==> Get CATRep error !" << endl;
	//	return E_FAIL;
	//}
	//CATRep *pParentRep = pOldRep->GetRepParents(0);
	//pParentRep->RemoveChild(*pOldRep);

	//Remove 2
	CATPathElement *pPathObj = NULL;
	rc = this->GetPathElemFromBU(ispBUElement,_pEditor,pPathObj);
	if (FAILED(rc)||pPathObj==NULL)
	{
		cout<<"==> Get PathElement from BU error !"<<endl;
		return E_FAIL;
	}
	CATUnicodeString strPathElem = "";
	_pGeneralCls->PathElementString(pPathObj,strPathElem);
	cout<<"==> PathElement: "<<strPathElem<<endl;

	CAT3DRep *pOldRep = NULL;
	CATRepPath oRepPath;
	rc = this->Get3DRep(pPathObj,&pOldRep,oRepPath);
	if (FAILED(rc)||pOldRep==NULL)
	{
		cout<<"==> Get 3DRep from PathElement error !"<<endl;
		return E_FAIL;
	}
	pOldRep->SetShowMode(1,0);
	//CATRep *pParentRep = pOldRep->GetRepParents(0);
	//pParentRep->RemoveChild(*pOldRep);

	//Remove 3
	//CATRepPath oRepPath;
	//CATRep *pOldRep = NULL;
	//rc = this->GetRepFromBU(ispBUElement,_pEditor,&pOldRep,oRepPath);
	//if (FAILED(rc)||pOldRep==NULL)
	//{
	//	cout<<"==> Get 3DRep from BU error !"<<endl;
	//	return E_FAIL;
	//}
	//CATRep *pParentRep = pOldRep->GetRepParents(0);
	//pParentRep->RemoveChild(*pOldRep);


	//We can noshow the old CATRep
	//pOldRep->SetShowMode(1,0);

	//Show the new CATRep.
	
	_pViewer->AddRep(_p3DBagRep);  
	_pViewer->Draw();

	return rc;
}

HRESULT TestTessellationCmd::Get3DRep(CATPathElement *iObject, CAT3DRep ** oRep,CATRepPath &oRepPath)
{
	HRESULT rc = E_FAIL ;

	if ( NULL == oRep ) return rc ;

	CATVisManager * pVisManager = CATVisManager::GetVisManager();

	if ( NULL != pVisManager )
	{
		CATViewpoint *pViewpoint=NULL;
		CATFrmLayout * pLayout = CATFrmLayout::GetCurrentLayout();
		if ( NULL !=  pLayout )
		{
			CATFrmWindow * pWindow = pLayout->GetCurrentWindow();
			if ( NULL !=  pWindow )
			{
				CATViewer * pViewer = pWindow->GetViewer();

				if ( NULL != pViewer )
				{
					CAT3DViewpoint & Main3DViewpoint = pViewer->GetMain3DViewpoint();
					pViewpoint = (CATViewpoint*)(& Main3DViewpoint);
				}
			}
		}

		// Generation of the rep
		pVisManager->GenerateRepPathFromPathElement(*iObject,pViewpoint,oRepPath);

		if ( oRepPath.Size() >= 1 )
		{                   
			//*oRep = (CAT3DRep*) oRepPath[oRepPath.Size()-1];
			*oRep = (CAT3DRep*) oRepPath[0];
			if ( NULL != *oRep )
			{
				rc = S_OK ;
			}
		}
	}
	return rc ;
}

HRESULT TestTessellationCmd::GetRepFromBU(CATBaseUnknown *ipBU, CATFrmEditor *ipEditor,CATRep ** oRep,CATRepPath &oRepPath)
{
	HRESULT rc = E_FAIL ;

	if ( NULL == oRep ) return rc ;

	CATVisManager * pVisManager = CATVisManager::GetVisManager();

	if ( NULL != pVisManager )
	{
		CATViewpoint *pViewpoint=NULL;
		CATFrmLayout * pLayout = CATFrmLayout::GetCurrentLayout();
		if ( NULL !=  pLayout )
		{
			CATFrmWindow * pWindow = pLayout->GetCurrentWindow();
			if ( NULL !=  pWindow )
			{
				CATViewer * pViewer = pWindow->GetViewer();

				if ( NULL != pViewer )
				{
					CAT3DViewpoint & Main3DViewpoint = pViewer->GetMain3DViewpoint();
					pViewpoint = (CATViewpoint*)(& Main3DViewpoint);
				}
			}
		}

		CATPathElement *iObject = NULL;
		rc = GetPathElemFromBU(ipBU,ipEditor,iObject);
		if (FAILED(rc)||iObject==NULL)
		{
			return E_FAIL;
		}

		CATUnicodeString strPathElem = "";
		_pGeneralCls->PathElementString(iObject,strPathElem);
		cout<<"==> PathElement: "<<strPathElem<<endl;
		cout<<"==> PathElement Num: "<<iObject->GetSize()<<endl;

		// Generation of the rep
		pVisManager->GenerateRepPathFromPathElement(*iObject,pViewpoint,oRepPath);

		if ( oRepPath.Size() >= 1 )
		{                   
			CATUnicodeString strPathName = "";
			int NumOfPath = oRepPath.Size();
			for(int i=0;i<NumOfPath;i++)  
			{
				CATRep *pRep =(CATRep*)(oRepPath)[i];
				if (pRep == NULL)
				{
					continue;
				}
				CATBaseUnknown *pElt = NULL; 
				rc = pRep->QueryInterface(IID_CATBaseUnknown,(void**)&pElt);
				if(pElt != NULL) 
				{
					CATIAlias *piAlias = NULL;
					rc = pElt->QueryInterface (IID_CATIAlias, (void**) &piAlias);
					if(SUCCEEDED(rc) && piAlias!=NULL)
					{
						CATUnicodeString Name = piAlias->GetAlias();
						strPathName.Append(Name) ;
						if(i<=(NumOfPath-2)) 
						{
							strPathName.Append("/");
						}
						piAlias->Release(); piAlias = NULL;
					}
				}
				if (pElt == ipBU)
				{
					*oRep = (CATRep*) oRepPath[i];
				}
			}

			cout<<"==> RepPath: "<<strPathName<<endl;
			
			//*oRep = (CAT3DRep*) oRepPath[oRepPath.Size()-1];
			//*oRep = (CAT3DRep*) oRepPath[0];
			if ( NULL != *oRep )
			{
				rc = S_OK ;
			}
		}
	}
	return rc ;
}

HRESULT TestTessellationCmd::GetPathElemFromBU(CATBaseUnknown_var ispBU,CATFrmEditor *ipEditor,CATPathElement *&opPathElem)
{

	CATIBuildPath *piBuildPath = NULL;
	HRESULT rc = ispBU->QueryInterface(IID_CATIBuildPath,(void**) &piBuildPath);
	if (SUCCEEDED(rc))
	{
		CATPathElement context = ipEditor->GetUIActiveObject();
		CATPathElement *pPathElement = NULL;

		rc = piBuildPath->ExtractPathElement(&context,&pPathElement);
		if (pPathElement != NULL)
		{
			opPathElem = pPathElement;
			return S_OK;
		}
	}

	return E_FAIL;
}

HRESULT TestTessellationCmd::GetRepFromBU(CATBaseUnknown_var ispBU,CATRep **opRep)
{
	HRESULT rc = S_OK;
	//特征化
	CATISpecObject_var spiSpecObj = _pGeneralCls->GetSpecFromBaseUnknownFunc(ispBU);
	if (spiSpecObj==NULL_var)
	{
		return E_FAIL;
	}
	//CATVisManager * pVisuManager = CATVisManager::GetVisManager();
	//CATModelIdentificator Ident(spiSpecObj);
	//CAT3DRep * pRepChild = (CAT3DRep *) pVisuManager->BuildRep(Ident);

	//CATIVisu *piVisu = NULL;
	//rc = spiSpecObj->QueryInterface(IID_CATIVisu,(void**)&piVisu);
	//if (FAILED(rc)||piVisu==NULL)
	//{
	//	return E_FAIL;
	//}
	//CATRep *pRep = piVisu->BuildRep();

	CATI3DGeoVisu *pi3DGeoVisu = NULL;
	rc = spiSpecObj->QueryInterface(IID_CATI3DGeoVisu,(void**)&pi3DGeoVisu);
	if (FAILED(rc)||pi3DGeoVisu==NULL)
	{
		return E_FAIL;
	}
	CATRep *pRep = pi3DGeoVisu->GiveRep();

	*opRep = pRep;
	//
	return E_FAIL;
}