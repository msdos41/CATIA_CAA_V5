#include "TestCreateSWPointCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

#include "CATCreateExternalObject.h"
#include "CATIVisu.h"
#include "CATI3DGeoVisu.h"
#include "CAT3DRep.h"
#include "CAT3DManipulator.h"
#include "CATIBRepAccess.h"
#include "CATIFeaturize.h"
#include "CATExtIVisu.h"
#include "CATIVisProperties.h"
#include "CATFrmLayout.h"
#include "CATFrmWindow.h"
#include "CATViewer.h"
#include "CATViewpoint.h"
#include "CATRepPath.h"

#include "CATTopPointOperator.h"
#include "CATTopLineOperator.h"
#include "CATCreateTopIntersect.h"
#include "CATHybIntersect.h"

#include "CATVertex.h"
#include "CATPoint.h"
#include "CATGeoFactory.h"
#include "CATEdge.h"
#include "CATCurve.h"
#include "CATEdgeCurve.h"
#include "CATCrvEvalLocal.h"
#include "CATPlane.h"
#include "CATSurface.h"

#include "CATTopWire.h"

#include "CATIntersectionSurSur.h"
#include "CATCreateProjection.h"
#include "CATProjectionPtSur.h"
#include "CATCreateLocalAnalysisD.h"
#include "CATLocalAnalysis2D.h"
#include "CATIMeasurableInContext.h"

#include "iostream.h"
using namespace std;

CATCreateClass( TestCreateSWPointCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestCreateSWPointCmd::TestCreateSWPointCmd() :
	CATStateCommand ("TestCreateSWPointCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
	//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
	,_pDlg(NULL)
	,_pPartAgent(NULL)
	,_pSurfaceAgent(NULL)
	,_pOtherAgent(NULL)
	,_pSLConnectionsAgent(NULL)
	,_pSLAllCnctsAgent(NULL)
	,_pSLBaseSurfaceAgent(NULL)
	,_pCheckDisAgent(NULL)
	,_pCheckCurvatureAgent(NULL)
	,_pCheckThicknessRatioAgent(NULL)
	,_pCheckWholeThicknessAgent(NULL)
	,_pSelfWeldCBAgent(NULL)
	,_pDiaOKAgent(NULL)
	,_pDiaPREVIEWAgent(NULL)
	,_pDiaCancelAgent(NULL)
	,_pMiddlePBAgent(NULL)
	,_pDeleteNewPBAgent(NULL)
	,_bCheckDis(FALSE)
	,_bCheckCurvature(FALSE)
	,_bCheckThicknessRatio(FALSE)
	,_bCheckWholeThickness(FALSE)
	,_bSelfWeld(FALSE)
	,_pToLeft(NULL)
	,_pToRight(NULL)
	,_pEditor(NULL)
	,_pHSO(NULL)
	,_pISO(NULL)
	,_spRootPrd(NULL_var)
	,_spWeldPrd(NULL_var)
	,_spPrtContainer(NULL_var)
	,_spWeldGSMFactory(NULL_var)
	,_spCkeParmFactory(NULL_var)
	,_spSurfacePrd(NULL_var)
	,_spSpecSurface(NULL_var)
	,_spFace(NULL_var)
	,_pVisuManager(NULL)
	,_pViewer(NULL)
	,_pSelector(NULL)
	,_spTempPoint(NULL_var)
	,_bSelected(FALSE)
	,_spTempLineEdge1(NULL_var)
	,_spTempLineEdge2(NULL_var)
	,_spTempLineEdge3(NULL_var)
	,_spTempLineEdge4(NULL_var)
	,_spTempLineSWPoint(NULL_var)
	,_spTempTextForWP(NULL_var)
	,_spSpecCurrentSWPoint(NULL_var)
	,_spWeldPart(NULL_var)
{
	//_pSJDGeneralClass = new SJDGeneralClass(); 
	//_pSJDSpotWeldCheck = new TestCheckMethod(_pSJDGeneralClass);

	HRESULT rc=E_FAIL;

	_pTestPublicMethod = new TestPublicMethod();
	_pSJDGeneralClass = new SJDGeneralClass();
	_pSJDSpotWeldCheck = new TestCheckMethod(_pSJDGeneralClass,_pTestPublicMethod);

	const char * cValue = "TestXMLPath";
	char * oPath = NULL;
	CATLibStatus sStatus = CATGetEnvValue(cValue,&oPath);
	if ((sStatus ==CATLibError)||(oPath==NULL))
	{
		cout << "GetXMLEnvError"<<endl;
		_pTestPublicMethod->MessegeOutput("XML not exist，pls contact administrator","Error");
		this->RequestDelayedDestruction();
		return;
	}

	rc = _pTestPublicMethod->OpenXML(oPath);
	if (FAILED(rc))
	{
		_pTestPublicMethod->MessegeOutput("XML error，pls contact administrator","Error");
		this->RequestDelayedDestruction();
		return;
	}

	free(oPath);oPath = NULL;

	rc = _pTestPublicMethod->GetTypeOriginNameFormXML(sTypeNameList);
	rc = _pTestPublicMethod->GetTypeLevelFormXML(sTypeLevelList);
	//rc = _pTestPublicMethod->GetIdentifierFormXML(sIdentifierList);
	if (sTypeLevelList.Size()!=sTypeNameList.Size()/*||sIdentifierList.Size()!=sTypeNameList.Size()*/)
	{
		_pTestPublicMethod->MessegeOutput("XML error，pls contact administrator","Error");
		this->RequestDelayedDestruction();
		return;
	}

	//1、获得Editor和HSO
	_pEditor = CATFrmEditor::GetCurrentEditor();
	_pHSO = NULL;
	if( _pEditor != NULL )
	{
		_pHSO = _pEditor->GetHSO();
		_pISO = _pEditor->GetISO();
	}

	//2、判断当前打开的Root是否为Product，并获得CATIProduct类型
	//获得当前打开的文档的Document
	CATDocument * pDocRoot = _pEditor->GetDocument();
	if(pDocRoot==NULL)
	{
		RequestDelayedDestruction();
		return;
	}

	//获得当前的文档类型，当不是装配件时，报错
	int docType;
	 rc = _pSJDGeneralClass->SJDGetDocumentType(pDocRoot,docType);
	if(docType!=2)
	{
		_pSJDGeneralClass->CreatMsgBoxOptError("Current file is not a product,pls open a product file");
		RequestDelayedDestruction();
		return;
	}
	//获得当前打开的ReferenceProduct
	rc = _pSJDGeneralClass->SJDGetRootElementOfDocument(pDocRoot,_spRootPrd);
	if(_spRootPrd==NULL_var)
	{
		RequestDelayedDestruction();
		return;
	}

	//3、获得当前的Part
	CATPathElement pUIElem = _pEditor->GetUIActiveObject();
	CATIProduct *piActiveProduct=NULL;
	rc = pUIElem.Search(IID_CATIProduct,(void**)&piActiveProduct);

	//4、判断是否为焊点文档（命名中包含“SW”,不区分大小写）
	CATBoolean bSWPart = GeneralSWMethod.CheckSWPart(piActiveProduct);
	if(bSWPart==FALSE)
	{
		//_pSJDGeneralClass->CreatMsgBoxOptError("当前Part非焊点文件，请激活焊点文件再执行焊点创建！");
		_pSJDGeneralClass->CreatMsgBoxOptError("Current file not a WP file,pls creat WP after active a WP file");
		RequestDelayedDestruction();
		return;
	}

	//焊点文件赋给全局变量
	_spWeldPrd = piActiveProduct;

	//获得当前焊点文档的Container	
	_pSJDGeneralClass->SJDGetCurrentPrtContainer(_spPrtContainer);

	//获得当前焊点文档的GSMFactory	
	_spWeldGSMFactory = _spPrtContainer;
	_spCkeParmFactory = _spPrtContainer;

	_spWeldPart=_spPrtContainer->GetPart();

	_isContinue=true;

	if (_isContinue)
	{
		int i_VisualizationMode;  //检查cache是否激活 0: Cache no activation, 1: Cache is activation
		rc=_pSJDGeneralClass->SJDCheckCacheActivation(i_VisualizationMode);
		if( i_VisualizationMode ) 
		{
			int i_choose = _SJDMethod->MessegeOutputYesNo("Cache Mode is Active\n pls sure all parts loaded as design mode \n Click Yes to continue or No to cancel","Warning!");
			if(i_choose == 3)
			{
				_isContinue = true;
			}
			else	
				this->RequestDelayedDestruction();
		}
		else
			_isContinue = true;
	}

	if(_isContinue)
	{
		//5、打开对话框
		//Create the dialog 创建dialog
		_pDlg = new TestCreateSWPointDlg();
		_pDlg->Build();

		//Show the dialog 显示窗口
		_pDlg->SetVisibility(CATDlgShow);
		_pDlg->SetOKSensitivity(CATDlgDisable);
		_pDlg->SetPREVIEWSensitivity(CATDlgDisable);
		//_pDlg->SetPREVIEWTitle("Create");

		//6、获得当前View
		_pVisuManager = CATVisManager::GetVisManager();
		CATFrmLayout * pFrmLay = CATFrmLayout::GetCurrentLayout();
		CATFrmWindow * pFrmWin = pFrmLay->GetCurrentWindow();
		_pViewer = pFrmWin->GetViewer();

		//7、Top
		_pConfig = new CATSoftwareConfiguration();//配置指针
		_topdata =new CATTopData(_pConfig, NULL);//topdata

		//8、获得当前part的父亲Product下的所有part（排除sw零件）
		CATIProduct_var spFatherPrd = _spWeldPrd->GetFatherProduct();

		CATListValCATISpecObject_var spPartList;
		CATListValCATISpecObject_var spSWPartList;
		_pSJDSpotWeldCheck->GetPartListFromProduct(spFatherPrd, _spSpecAllPartList, spSWPartList, true);
		spSWPartList.RemoveAll();

		//获得名称
		CATIProduct_var spPrd;
		CATUnicodeString strInstName;
		for(int i=1; i<=_spSpecAllPartList.Size(); i++)
		{
			spPrd = _spSpecAllPartList[i];
			spPrd->GetPrdInstanceName(strInstName);

			_strAllPartList.Append(strInstName);
		}

		//设置到对话框
		_pDlg->SetPartNameList(2, _strAllPartList);

		//创建临时箭头
		if(_spTempLineEdge1==NULL_var)
		{
			SJDITempLineWithText * pTempLineWithText = NULL;
			rc = ::CATInstantiateComponent("SJDTempLineWithTextComp",IID_SJDITempLineWithText,(void**)&pTempLineWithText);
			if( FAILED(rc) || pTempLineWithText==NULL)
			{
				cout<<"Create SW Temp Line Failed !"<<endl;
				RequestDelayedDestruction();
				return;
			}		
			_spTempLineEdge1 = pTempLineWithText;

			pTempLineWithText->Release();
			pTempLineWithText = NULL;
		}

		if(_spTempLineEdge2==NULL_var)
		{
			SJDITempLineWithText * pTempLineWithText = NULL;
			rc = ::CATInstantiateComponent("SJDTempLineWithTextComp",IID_SJDITempLineWithText,(void**)&pTempLineWithText);
			if( FAILED(rc) || pTempLineWithText==NULL)
			{
				cout<<"Create SW Temp Line Failed !"<<endl;
				RequestDelayedDestruction();
				return;
			}
			_spTempLineEdge2 = pTempLineWithText;

			pTempLineWithText->Release();
			pTempLineWithText = NULL;
		}

		if(_spTempLineEdge3==NULL_var)
		{
			SJDITempLineWithText * pTempLineWithText = NULL;
			rc = ::CATInstantiateComponent("SJDTempLineWithTextComp",IID_SJDITempLineWithText,(void**)&pTempLineWithText);
			if( FAILED(rc) || pTempLineWithText==NULL)
			{
				cout<<"Create SW Temp Line Failed !"<<endl;
				RequestDelayedDestruction();
				return;
			}		
			_spTempLineEdge3 = pTempLineWithText;

			pTempLineWithText->Release();
			pTempLineWithText = NULL;
		}

		if(_spTempLineEdge4==NULL_var)
		{
			SJDITempLineWithText * pTempLineWithText = NULL;
			rc = ::CATInstantiateComponent("SJDTempLineWithTextComp",IID_SJDITempLineWithText,(void**)&pTempLineWithText);
			if( FAILED(rc) || pTempLineWithText==NULL)
			{
				cout<<"Create SW Temp Line Failed !"<<endl;
				RequestDelayedDestruction();
				return;
			}	
			_spTempLineEdge4 = pTempLineWithText;

			pTempLineWithText->Release();
			pTempLineWithText = NULL;
		}

		if(_spTempLineSWPoint==NULL_var)
		{
			SJDITempLineWithText * pTempLineWithText = NULL;
			rc = ::CATInstantiateComponent("SJDTempLineWithTextComp",IID_SJDITempLineWithText,(void**)&pTempLineWithText);
			if( FAILED(rc) || pTempLineWithText==NULL)
			{
				cout<<"Create SW Temp Line Failed !"<<endl;
				RequestDelayedDestruction();
				return;
			}	
			_spTempLineSWPoint = pTempLineWithText;

			pTempLineWithText->Release();
			pTempLineWithText = NULL;
		}

		if(_spTempTextForWP==NULL_var)
		{
			SJDITempTextForWP * pTempTextForWP = NULL;
			rc = ::CATInstantiateComponent("SJDTempTextForWP",IID_SJDITempTextForWP,(void**)&pTempTextForWP);
			if( FAILED(rc) || pTempTextForWP==NULL)
			{
				cout<<"Create SW Temp Line Failed !"<<endl;
				RequestDelayedDestruction();
				return;
			}	
			_spTempTextForWP = pTempTextForWP;

			pTempTextForWP->Release();
			pTempTextForWP = NULL;
		}
	}
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestCreateSWPointCmd::~TestCreateSWPointCmd()
{
	if (_pDlg != NULL) 
		_pDlg->RequestDelayedDestruction();

	if(_pPartAgent!=NULL){ _pPartAgent->RequestDelayedDestruction(); _pPartAgent=NULL;}
	if(_pSurfaceAgent!=NULL){ _pSurfaceAgent->RequestDelayedDestruction(); _pSurfaceAgent=NULL;}
	if(_pOtherAgent!=NULL){ _pOtherAgent->RequestDelayedDestruction(); _pOtherAgent=NULL;}

	if(_pSLConnectionsAgent!=NULL){ _pSLConnectionsAgent->RequestDelayedDestruction(); _pSLConnectionsAgent=NULL;}
	if(_pSLAllCnctsAgent!=NULL){ _pSLAllCnctsAgent->RequestDelayedDestruction(); _pSLAllCnctsAgent=NULL;}

	if(_pSLBaseSurfaceAgent!=NULL){ _pSLBaseSurfaceAgent->RequestDelayedDestruction(); _pSLBaseSurfaceAgent=NULL;}
	if(_pCheckDisAgent!=NULL){ _pCheckDisAgent->RequestDelayedDestruction(); _pCheckDisAgent=NULL;}
	if(_pCheckCurvatureAgent!=NULL){ _pCheckCurvatureAgent->RequestDelayedDestruction(); _pCheckCurvatureAgent=NULL;}
	if(_pCheckThicknessRatioAgent!=NULL){ _pCheckThicknessRatioAgent->RequestDelayedDestruction(); _pCheckThicknessRatioAgent=NULL;}
	if(_pCheckWholeThicknessAgent!=NULL){ _pCheckWholeThicknessAgent->RequestDelayedDestruction(); _pCheckWholeThicknessAgent=NULL;}
	if(_pSelfWeldCBAgent!=NULL){ _pSelfWeldCBAgent->RequestDelayedDestruction(); _pSelfWeldCBAgent=NULL;}

	if(_pToLeft!=NULL){ _pToLeft->RequestDelayedDestruction(); _pToLeft=NULL;}
	if(_pToRight!=NULL){ _pToRight->RequestDelayedDestruction(); _pToRight=NULL;}

	if(_pDiaOKAgent!=NULL){ _pDiaOKAgent->RequestDelayedDestruction(); _pDiaOKAgent=NULL;}
	if(_pDiaPREVIEWAgent!=NULL){ _pDiaPREVIEWAgent->RequestDelayedDestruction(); _pDiaPREVIEWAgent=NULL;}
	if(_pDiaCancelAgent!=NULL){ _pDiaCancelAgent->RequestDelayedDestruction(); _pDiaCancelAgent=NULL;}
	if(_pMiddlePBAgent!=NULL){ _pMiddlePBAgent->RequestDelayedDestruction(); _pMiddlePBAgent=NULL;}
	if(_pDeleteNewPBAgent!=NULL){ _pDeleteNewPBAgent->RequestDelayedDestruction(); _pDeleteNewPBAgent=NULL;}

	if(_spSpecListPart.Size()>0)
	{
		_spSpecListPart.RemoveAll();
		_spSpecListPart = NULL;
	}
	if(_strListPartIN.Size() >0)
	{
		_strListPartIN.RemoveAll();
		_strListPartIN = NULL;
	}
	if(_strListPartPN.Size() > 0)
	{
		_strListPartPN.RemoveAll();
		_strListPartPN = NULL;
	}

	if(_spSpecAllPartList.Size() > 0)
	{
		_spSpecAllPartList.RemoveAll();
		_spSpecAllPartList = NULL;
	}

	if(_strAllPartList.Size() > 0)
	{
		_strAllPartList.RemoveAll();
		_strAllPartList = NULL;
	}
}

//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void TestCreateSWPointCmd::BuildGraph()
{
	//选择Part
	_pPartAgent=new CATPathElementAgent("ObjectAgent");
	_pPartAgent->AddElementType("CATIProduct");
	_pPartAgent->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngOneShot);

	//Filter 过滤器，保证所选择的为Product
	CATAcquisitionFilter *pFilterPart = 
		Filter((FilterMethod) &TestCreateSWPointCmd::CheckSelectedPart,(void *)NULL);
	_pPartAgent->SetFilter(pFilterPart);

	//选择基准面
	_pSurfaceAgent = new CATPathElementAgent("Select Base Surface");
	_pSurfaceAgent ->AddElementType("CATIMfPlane");
	_pSurfaceAgent ->AddElementType("CATIRSur" );	
	_pSurfaceAgent ->AddElementType("CATSurface");
	_pSurfaceAgent ->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngOneShot);

	//Filter 过滤器，限制所选的的面必须在所选的Part中
	CATAcquisitionFilter * pFilterSurface = 
		Filter((FilterMethod) &TestCreateSWPointCmd::CheckSelectedSurface,(void *)NULL);
	_pSurfaceAgent->SetFilter(pFilterSurface);

	//其他预选择
	_pOtherAgent = new CATPathElementAgent("Select Base Surface");
	_pOtherAgent ->AddElementType("CATIMfPlane");
	_pOtherAgent ->AddElementType("CATIRSur" );	
	_pOtherAgent ->AddElementType("CATSurface");
	_pOtherAgent ->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngOneShot);

	//Filter 过滤器，限制所选的的面必须在所选的Part中
	CATAcquisitionFilter * pFilterOther = 
		Filter((FilterMethod) &TestCreateSWPointCmd::CheckSelectedOther,(void *)NULL);
	_pOtherAgent->SetFilter(pFilterOther);

	_pDiaOKAgent =new CATDialogAgent("OkAgent");
	_pDiaCancelAgent=new CATDialogAgent("CancelAgent");
	_pDiaPREVIEWAgent=new CATDialogAgent("PreviewAgent");

	_pSLBaseSurfaceAgent=new CATDialogAgent("Base Surface");
	_pSLAllCnctsAgent = new CATDialogAgent("All Connections");
	_pSLConnectionsAgent=new CATDialogAgent("Connect Part");

	_pCheckDisAgent=new CATDialogAgent("Check Dis");
	_pCheckCurvatureAgent = new CATDialogAgent("Check Curvature");
	_pCheckThicknessRatioAgent = new CATDialogAgent("Check Thickness Ratio");
	_pCheckWholeThicknessAgent = new CATDialogAgent("Check Whole Thickness");
	_pSelfWeldCBAgent = new CATDialogAgent("Self Weld");

	_pToLeft = new CATDialogAgent("PB To Left");
	_pToRight = new CATDialogAgent("PB To Right");
	_pMiddlePBAgent = new CATDialogAgent("PB Middle");
	_pDeleteNewPBAgent = new CATDialogAgent("PB Delete New");
	_pNextPBAgent = new CATDialogAgent("PB Next");

	_pDiaOKAgent->AcceptOnNotify(_pDlg,_pDlg->GetDiaOKNotification());	
	_pDiaCancelAgent->AcceptOnNotify(_pDlg,_pDlg->GetDiaCANCELNotification());
	_pDiaCancelAgent->AcceptOnNotify(_pDlg,_pDlg->GetWindCloseNotification());
	_pDiaPREVIEWAgent->AcceptOnNotify(_pDlg,_pDlg->GetDiaPREVIEWNotification());

	_pSLBaseSurfaceAgent->AcceptOnNotify(_pDlg->GetSelectorList(1),_pDlg->GetSelectorList(1)->GetListSelectNotification());
	_pSLConnectionsAgent->AcceptOnNotify(_pDlg->GetSelectorList(2),_pDlg->GetSelectorList(2)->GetListSelectNotification());
	_pSLAllCnctsAgent->AcceptOnNotify(_pDlg->GetSelectorList(3),_pDlg->GetSelectorList(3)->GetListSelectNotification());

	_pCheckDisAgent->AcceptOnNotify(_pDlg->GetCheckButton(1),_pDlg->GetCheckButton(1)->GetChkBModifyNotification());
	_pCheckCurvatureAgent->AcceptOnNotify(_pDlg->GetCheckButton(2),_pDlg->GetCheckButton(2)->GetChkBModifyNotification());
	_pCheckThicknessRatioAgent->AcceptOnNotify(_pDlg->GetCheckButton(3),_pDlg->GetCheckButton(3)->GetChkBModifyNotification());
	_pCheckWholeThicknessAgent->AcceptOnNotify(_pDlg->GetCheckButton(4),_pDlg->GetCheckButton(4)->GetChkBModifyNotification());
	_pSelfWeldCBAgent->AcceptOnNotify(_pDlg->GetCheckButton(5),_pDlg->GetCheckButton(5)->GetChkBModifyNotification());

	_pToLeft->AcceptOnNotify(_pDlg->GetPushButton(2), _pDlg->GetPushButton(2)->GetPushBActivateNotification());
	_pToRight->AcceptOnNotify(_pDlg->GetPushButton(1), _pDlg->GetPushButton(1)->GetPushBActivateNotification());
	_pMiddlePBAgent->AcceptOnNotify(_pDlg->GetPushButton(3), _pDlg->GetPushButton(3)->GetPushBActivateNotification());
	_pDeleteNewPBAgent->AcceptOnNotify(_pDlg->GetPushButton(4), _pDlg->GetPushButton(4)->GetPushBActivateNotification());
	_pNextPBAgent->AcceptOnNotify(_pDlg->GetPushButton(5), _pDlg->GetPushButton(5)->GetPushBActivateNotification());

	//State Define
	CATDialogState * pPrtState=GetInitialState("prtState");	
	pPrtState->AddDialogAgent(_pPartAgent);
	pPrtState->AddDialogAgent(_pDiaOKAgent);
	pPrtState->AddDialogAgent(_pDiaCancelAgent);
	pPrtState->AddDialogAgent(_pDiaPREVIEWAgent);	
	pPrtState->AddDialogAgent(_pSLBaseSurfaceAgent);
	pPrtState->AddDialogAgent(_pSLConnectionsAgent);
	pPrtState->AddDialogAgent(_pSLAllCnctsAgent);	
	pPrtState->AddDialogAgent(_pCheckDisAgent);
	pPrtState->AddDialogAgent(_pCheckCurvatureAgent);
	pPrtState->AddDialogAgent(_pCheckThicknessRatioAgent);
	pPrtState->AddDialogAgent(_pCheckWholeThicknessAgent);
	pPrtState->AddDialogAgent(_pSelfWeldCBAgent);
	pPrtState->AddDialogAgent(_pToLeft);
	pPrtState->AddDialogAgent(_pToRight);
	pPrtState->AddDialogAgent(_pMiddlePBAgent);
	pPrtState->AddDialogAgent(_pDeleteNewPBAgent);
	pPrtState->AddDialogAgent(_pNextPBAgent);


	CATDialogState * pSurfaceState = AddDialogState("surfaceState");
	pSurfaceState->AddDialogAgent(_pSurfaceAgent);
	pSurfaceState->AddDialogAgent(_pDiaOKAgent);
	pSurfaceState->AddDialogAgent(_pDiaCancelAgent);
	pSurfaceState->AddDialogAgent(_pDiaPREVIEWAgent);	
	pSurfaceState->AddDialogAgent(_pSLBaseSurfaceAgent);
	pSurfaceState->AddDialogAgent(_pSLConnectionsAgent);	
	pSurfaceState->AddDialogAgent(_pSLAllCnctsAgent);	
	pSurfaceState->AddDialogAgent(_pCheckDisAgent);
	pSurfaceState->AddDialogAgent(_pCheckCurvatureAgent);
	pSurfaceState->AddDialogAgent(_pCheckThicknessRatioAgent);
	pSurfaceState->AddDialogAgent(_pCheckWholeThicknessAgent);
	pSurfaceState->AddDialogAgent(_pSelfWeldCBAgent);
	pSurfaceState->AddDialogAgent(_pToLeft);
	pSurfaceState->AddDialogAgent(_pToRight);
	pSurfaceState->AddDialogAgent(_pMiddlePBAgent);
	pSurfaceState->AddDialogAgent(_pDeleteNewPBAgent);
	pSurfaceState->AddDialogAgent(_pNextPBAgent);


	CATDialogState * pOtherState = AddDialogState("");
	pOtherState->AddDialogAgent(_pOtherAgent);
	pOtherState->AddDialogAgent(_pDiaOKAgent);
	pOtherState->AddDialogAgent(_pDiaCancelAgent);
	pOtherState->AddDialogAgent(_pDiaPREVIEWAgent);	
	pOtherState->AddDialogAgent(_pSLBaseSurfaceAgent);
	pOtherState->AddDialogAgent(_pSLConnectionsAgent);	
	pOtherState->AddDialogAgent(_pSLAllCnctsAgent);	
	pOtherState->AddDialogAgent(_pCheckDisAgent);
	pOtherState->AddDialogAgent(_pCheckCurvatureAgent);
	pOtherState->AddDialogAgent(_pCheckThicknessRatioAgent);
	pOtherState->AddDialogAgent(_pCheckWholeThicknessAgent);
	pOtherState->AddDialogAgent(_pSelfWeldCBAgent);
	pOtherState->AddDialogAgent(_pToLeft);
	pOtherState->AddDialogAgent(_pToRight);
	pOtherState->AddDialogAgent(_pMiddlePBAgent);
	pOtherState->AddDialogAgent(_pDeleteNewPBAgent);
	pOtherState->AddDialogAgent(_pNextPBAgent);


	//select prt
	AddTransition( pPrtState, pPrtState, IsOutputSetCondition (_pPartAgent),
		Action ((ActionMethod) &TestCreateSWPointCmd::SelectPart));
	AddTransition( pSurfaceState, pPrtState, IsOutputSetCondition (_pPartAgent),
		Action ((ActionMethod) &TestCreateSWPointCmd::SelectPart));
	AddTransition( pOtherState, pPrtState, IsOutputSetCondition (_pPartAgent),
		Action ((ActionMethod) &TestCreateSWPointCmd::SelectPart));

	//prt field selected
	AddTransition( pPrtState, pPrtState, IsOutputSetCondition (_pSLConnectionsAgent),
		Action ((ActionMethod) &TestCreateSWPointCmd::ConnectionsFieldSelected));
	AddTransition( pSurfaceState, pPrtState, IsOutputSetCondition (_pSLConnectionsAgent),
		Action ((ActionMethod) &TestCreateSWPointCmd::ConnectionsFieldSelected));
	AddTransition( pOtherState, pPrtState, IsOutputSetCondition (_pSLConnectionsAgent),
		Action ((ActionMethod) &TestCreateSWPointCmd::ConnectionsFieldSelected));

	//Surface
	AddTransition(pSurfaceState,pSurfaceState,	IsOutputSetCondition(_pSurfaceAgent),
		Action((ActionMethod) &TestCreateSWPointCmd::SelectSurface));
	AddTransition(pPrtState,pSurfaceState,	IsOutputSetCondition(_pSurfaceAgent),
		Action((ActionMethod) &TestCreateSWPointCmd::SelectSurface));
	AddTransition(pOtherState,pSurfaceState,	IsOutputSetCondition(_pSurfaceAgent),
		Action((ActionMethod) &TestCreateSWPointCmd::SelectSurface));

	//Base Surface field selected
	AddTransition(pSurfaceState,pSurfaceState,	IsOutputSetCondition(_pSLBaseSurfaceAgent),
		Action((ActionMethod) &TestCreateSWPointCmd::BaseSurfaceFieldSelected));
	AddTransition(pPrtState,pSurfaceState,	IsOutputSetCondition(_pSLBaseSurfaceAgent),
		Action((ActionMethod) &TestCreateSWPointCmd::BaseSurfaceFieldSelected));
	AddTransition(pOtherState,pSurfaceState,	IsOutputSetCondition(_pSLBaseSurfaceAgent),
		Action((ActionMethod) &TestCreateSWPointCmd::BaseSurfaceFieldSelected));

	//Check
	//_pCheckDisAgent
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pCheckDisAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pCheckDisAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pCheckDisAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));

	//_pCheckCurvatureAgent
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pCheckCurvatureAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pCheckCurvatureAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pCheckCurvatureAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));

	//_pCheckThicknessRatioAgent
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pCheckThicknessRatioAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pCheckThicknessRatioAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pCheckThicknessRatioAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));

	//_pCheckWholeThicknessAgent
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pCheckWholeThicknessAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pCheckWholeThicknessAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pCheckWholeThicknessAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));

	//_pSelfWeldCBAgent
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pSelfWeldCBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pSelfWeldCBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pSelfWeldCBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::CheckButtonModify));

	//_pSLAllCnctsAgent
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pSLAllCnctsAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::AllCnctsSelected));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pSLAllCnctsAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::AllCnctsSelected));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pSLAllCnctsAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::AllCnctsSelected));

	//_pToLeft
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pToLeft),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionToLeft));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pToLeft),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionToLeft));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pToLeft),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionToLeft));

	//_pToRight
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pToRight),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionToRight));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pToRight),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionToRight));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pToRight),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionToRight));

	//_pMiddlePBAgent
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pMiddlePBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionMiddlePB));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pMiddlePBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionMiddlePB));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pMiddlePBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionMiddlePB));

	//_pDeleteNewPBAgent
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pDeleteNewPBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionDeleteNewPB));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pDeleteNewPBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionDeleteNewPB));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pDeleteNewPBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionDeleteNewPB));

	//_pNextPBAgent
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pNextPBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionNextPB));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pNextPBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionNextPB));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pNextPBAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionNextPB));

	//Cancel
	AddTransition(pPrtState,NULL, IsOutputSetCondition(_pDiaCancelAgent), 
		Action((ActionMethod) &TestCreateSWPointCmd::ActionCancel));
	AddTransition(pSurfaceState,NULL, IsOutputSetCondition(_pDiaCancelAgent), 
		Action((ActionMethod) &TestCreateSWPointCmd::ActionCancel));
	AddTransition(pOtherState,NULL, IsOutputSetCondition(_pDiaCancelAgent), 
		Action((ActionMethod) &TestCreateSWPointCmd::ActionCancel));

	//OK
	AddTransition(pPrtState,NULL, IsOutputSetCondition(_pDiaOKAgent),
		Action((ActionMethod) &TestCreateSWPointCmd::ActionOK));
	AddTransition(pSurfaceState,NULL, IsOutputSetCondition(_pDiaOKAgent),
		Action((ActionMethod) &TestCreateSWPointCmd::ActionOK));
	AddTransition(pOtherState,NULL, IsOutputSetCondition(_pDiaOKAgent),
		Action((ActionMethod) &TestCreateSWPointCmd::ActionOK));

	//PREVIEW
	AddTransition(pPrtState,pPrtState, IsOutputSetCondition(_pDiaPREVIEWAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionPreview));
	AddTransition(pSurfaceState,pSurfaceState, IsOutputSetCondition(_pDiaPREVIEWAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionPreview));
	AddTransition(pOtherState,pOtherState, IsOutputSetCondition(_pDiaPREVIEWAgent),	
		Action((ActionMethod) &TestCreateSWPointCmd::ActionPreview));
}
void TestCreateSWPointCmd::UpdateHSO(CATISpecObject_var spSpecObj)
{
	_pHSO->Empty();
	HRESULT rc;

	if(spSpecObj!=NULL_var)
	{
		CATIBuildPath *pBuildPath =NULL;
		rc=spSpecObj->QueryInterface(IID_CATIBuildPath,(void**)&pBuildPath);
		if ( SUCCEEDED(rc)&&pBuildPath!=NULL )
		{
			CATPathElement context = _pEditor->GetUIActiveObject();
			CATPathElement *pPathElement = NULL;
			rc=pBuildPath->ExtractPathElement(&context,&pPathElement);

			if (pPathElement != NULL)
			{   // the geometrical element corresponding to the active field is now highlighted
				_pHSO->AddElement(pPathElement);                
				pPathElement->Release();
				pPathElement = NULL ;
			}
			pBuildPath->Release(); 
			pBuildPath = NULL ;
		}
	}
}
void TestCreateSWPointCmd::UpdateHSO(CATLISTV(CATISpecObject_var) piSpecOnGeomElemList)
{
	_pHSO->Empty();
	HRESULT rc;

	CATISpecObject_var spSpecOnGeomElem = NULL_var;
	if( piSpecOnGeomElemList.Size() != 0 )
	{
		for( int i = 1; i <= piSpecOnGeomElemList.Size(); i++ )
		{
			spSpecOnGeomElem = piSpecOnGeomElemList[i];
			if(spSpecOnGeomElem!=NULL_var)
			{
				CATIBuildPath *pBuildPath =NULL;
				rc=spSpecOnGeomElem->QueryInterface(IID_CATIBuildPath,(void**)&pBuildPath);
				if ( SUCCEEDED(rc)&&pBuildPath!=NULL )
				{
					CATPathElement context = _pEditor->GetUIActiveObject();
					CATPathElement *pPathElement = NULL;
					rc=pBuildPath->ExtractPathElement(&context,&pPathElement);

					if (pPathElement != NULL)
					{   // the geometrical element corresponding to the active field is now highlighted
						_pHSO->AddElement(pPathElement);                
						pPathElement->Release();
						pPathElement = NULL ;
					}
					pBuildPath->Release(); 
					pBuildPath = NULL ;
				}
			}
		}
	}
}
//-------------------------------------------------------------------------
// ActionOK ()
//-------------------------------------------------------------------------
CATBoolean TestCreateSWPointCmd::ActionOK( void *data )
{
	_pISO->Empty();

	return TRUE;
}

//-------------------------------------------------------------------------
// ActionCancel ()
//-------------------------------------------------------------------------
CATBoolean TestCreateSWPointCmd::ActionCancel( void *data )
{
	// TODO: Define the action associated with the transition 
	// ------------------------------------------------------

	ExecuteUndoAtEnd();
	_pISO->Empty();

	return TRUE;
}

//-------------------------------------------------------------------------
// ActionPreview ()
//-------------------------------------------------------------------------
CATBoolean TestCreateSWPointCmd::ActionPreview( void *data )
{
	// TODO: Define the action associated with the transition 
	// ------------------------------------------------------
	_pDiaPREVIEWAgent->InitializeAcquisition();

	_pDlg->SetOKSensitivity(CATDlgEnable);

	_pDlg->GetPushButton(3)->SetSensitivity(CATDlgDisable);

	CATMathPoint mathPt;
	_spTempLineSWPoint->SetDatas(mathPt, mathPt, "", 1);
	_spTempLineEdge1->SetDatas(mathPt, mathPt, "", 1);
	_spTempLineEdge2->SetDatas(mathPt, mathPt, "", 1);
	_spTempLineEdge3->SetDatas(mathPt, mathPt, "", 1);
	_spTempLineEdge4->SetDatas(mathPt, mathPt, "", 1);
	_spTempTextForWP->SetDatas(mathPt, NULL, NULL);

	CreateSWPoint();

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::CreateSWPoint()
{
	HRESULT rc = S_OK;

	CATMathTransformation pTransToLocal;
	CATMathTransformation pTransToGlobal;

	//1、获得临时点的坐标（Global）
	CATMathPoint mathPtOnSurfaceG;
	rc = _spTempPoint->GetPosition(&mathPtOnSurfaceG);
	if(FAILED(rc))
	{
		return FALSE;
	}

	//2、坐标变换，将临时点坐标转换到BaseSurface所在的Part的Local坐标
	//获得全局向局部转换的坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, _spSurfacePrd);

	//计算Local点坐标
	CATMathPoint mathPtOnSurfaceL = pTransToLocal*mathPtOnSurfaceG;

	//3、获得临时点处Base曲面的法线方向	
	//获得临时点在所选曲面处的法线方向，local
	CATMathVector normalVector;
	double oDis=0;
	_pSJDGeneralClass->SJDGetMinDistanceBetweenPointAndFace(_spFace, mathPtOnSurfaceL, oDis, normalVector);

	//将该方向转为Global
	pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(_spSurfacePrd, _spRootPrd);
	CATMathVector oNormalVG = pTransToGlobal*normalVector;

	CATListValCATISpecObject_var spSpecListPart;
	CATListValCATUnicodeString	strListPartIN;
	CATListValCATUnicodeString strListPartPN;

	for (int i=1;i<=_strListPartPN.Size();i++)
	{
		cout<<_strListPartPN[i]<<endl;
	}

	//将连接件排序
	if (_spSpecListPart.Size()==2)
	{
		_pSJDSpotWeldCheck->GetOrderofTwo(_spSpecListPart,_strListPartIN,_strListPartPN,spSpecListPart,strListPartIN,strListPartPN);		
		_spSpecListPart.RemoveAll();
		_strListPartIN.RemoveAll();
		_strListPartPN.RemoveAll();
		_spSpecListPart=spSpecListPart;
		_strListPartIN=strListPartIN;
		_strListPartPN=strListPartPN;
		if (_spSpecListPart.Size()!=2)
		{
			cout<<"GetOrderofTwo Failed"<<endl;
			return FALSE;
		}

	}
	else if (_spSpecListPart.Size()==3)
	{
		_pSJDSpotWeldCheck->GetOrderofThree(mathPtOnSurfaceG,_spSurfacePrd,oNormalVG,_spRootPrd,_spSpecListPart,_strListPartIN,_strListPartPN,spSpecListPart,strListPartIN,strListPartPN);
		_spSpecListPart.RemoveAll();
		_strListPartIN.RemoveAll();
		_strListPartPN.RemoveAll();
		_spSpecListPart=spSpecListPart;
		_strListPartIN=strListPartIN;
		_strListPartPN=strListPartPN;
		if (_spSpecListPart.Size()!=3)
		{
			cout<<"GetOrderofTwo Failed"<<endl;
			return FALSE;
		}

	}
	else if (_spSpecListPart.Size()==4)
	{
		_pSJDSpotWeldCheck->GetOrderofFour(mathPtOnSurfaceG,_spSurfacePrd,oNormalVG,_spRootPrd,_spSpecListPart,_strListPartIN,_strListPartPN,spSpecListPart,strListPartIN,strListPartPN);
		_spSpecListPart.RemoveAll();
		_strListPartIN.RemoveAll();
		_strListPartPN.RemoveAll();
		_spSpecListPart=spSpecListPart;
		_strListPartIN=strListPartIN;
		_strListPartPN=strListPartPN;
		if (_spSpecListPart.Size()!=4)
		{
			cout<<"GetOrderofTwo Failed"<<endl;
			return FALSE;
		}

	}
	else 
	{
		//_pSJDGeneralClass->CreatMsgBoxOnWarning("连接件个数少于2或多于4，请重新选择连接件！");
		_pSJDGeneralClass->CreatMsgBoxOnWarning("the connection part is less than two or greater than four");
		_bSelected = FALSE;
		return FALSE;

	}

	for (int i=1;i<=_strListPartPN.Size();i++)
	{
		cout<<_strListPartPN[i]<<endl;
	}

	//1、判断当前点焊类型 焊点内部标识：两层焊 2T SpotWelds 三层焊 3T SpotWelds 四层焊 4T SpotWelds
	CATUnicodeString strweldType;
	//WeldType weldType;
	int location=0;
	if(_spSpecListPart.Size()==2)	
	{
		//location=sIdentifierList.Locate("2T SpotWelds");
		strweldType ="2T SpotWelds";

	}
	else if(_spSpecListPart.Size()==3)
	{
		//location=sIdentifierList.Locate("3T SpotWelds");
		strweldType ="3T SpotWelds";

	}
	else if(_spSpecListPart.Size()==4)
	{
		//location=sIdentifierList.Locate("4T SpotWelds");
		strweldType ="4T SpotWelds";
	}
	else
	{
		//_pSJDGeneralClass->CreatMsgBoxOnWarning("连接件个数少于2或多于4，请重新选择连接件！");
		_pSJDGeneralClass->CreatMsgBoxOnWarning("the connection part is less than two or greater than four");
		_bSelected = FALSE;
		return FALSE;
	}

	//if (location<=0)
	//{
	//	_pSJDGeneralClass->CreatMsgBoxOnWarning("获取焊点内部标识失败，请检查配置文件！");
	//	return FALSE;
	//}

	//strweldType =sTypeNameList[location] ;

	//WeldType weldType;
	//if(_spSpecListPart.Size()==2)	
	//	weldType = SpotWelds2T;	
	//else if(_spSpecListPart.Size()==3)	
	//	weldType = SpotWelds3T;
	//else if(_spSpecListPart.Size()==4)
	//	weldType = SpotWelds4T;
	//else
	//{
	//	_pSJDGeneralClass->CreatMsgBoxOnWarning("连接件个数少于2或多于4，请重新选择连接件！");

	//	_bSelected = FALSE;
	//	return FALSE;
	//}

	//2、判断所选Surface的Part是否在连接件列表中
	CATBoolean bCheckSurface = FALSE;
	for(int i=1; i<=_spSpecListPart.Size(); i++)
	{
		if(_spSurfacePrd->IsEqual(_spSpecListPart[i]))
		{
			bCheckSurface = TRUE;
			break;
		}
	}
	if(bCheckSurface==FALSE)
	{
		//_pSJDGeneralClass->CreatMsgBoxOptError("所选曲面不在连接件所在的part中，请重新选择曲面！");
		_pSJDGeneralClass->CreatMsgBoxOptError("The selected surface not lie on connection part,pls reselect");
		_bSelected = FALSE;
		return FALSE;
	}

	//3、获得当前点焊类型所在的几何集
	CATISpecObject_var spSpecGeoSet = NULL_var;
	//rc = GeneralSWMethod.GetGeoSet(_spWeldPrd, weldType, spSpecGeoSet);
	rc = GeneralSWMethod.GetGeoSet(_spWeldPrd, strweldType, spSpecGeoSet);
	if(FAILED(rc) || spSpecGeoSet==NULL_var)
	{
		//_pSJDGeneralClass->CreatMsgBoxOptError("获得焊点文件中的几何集失败，请确认当前焊点文件中已经创建相应几何集！");
		_pSJDGeneralClass->CreatMsgBoxOptError("Failed to get the geometric set in WP,pls confirm the geometric set has already exist");
		_bSelected = FALSE;
		return FALSE;
	}

	//4、判断是否为自焊件
	CATBoolean bSelfWeld = FALSE;
	CATBaseUnknown_var spBaseTemp1;
	CATBaseUnknown_var spBaseTemp2;
	for(int i=1; i<_spSpecListPart.Size(); i++)
	{
		for(int j=i+1; j<=_spSpecListPart.Size(); j++)
		{
			spBaseTemp1 = _spSpecListPart[i];
			spBaseTemp2 = _spSpecListPart[j];

			if(spBaseTemp1->IsEqual(spBaseTemp2))
			{
				bSelfWeld = TRUE;
				break;
			}
		}
		if(bSelfWeld == TRUE)
			break;
	}

	//5、计算焊点位置，同时获得四个点的坐标，并生成临时元素
	//曲率半径计算结果
	//板材厚度比检查结果
	//到其他焊点的距离检查结果
	switch(_spSpecListPart.Size())
	{
	case 2:
		if(bSelfWeld == FALSE)
			rc = this->GetSWPointt2T(_mathPtMid, _mathPtOnEdge1, _mathPtOnEdge2, _mathPtOnEdge3, _mathPtOnEdge4);
		else
			rc = this->GetSelfWeldSWPoint2T(_mathPtMid, _mathPtOnEdge1, _mathPtOnEdge2, _mathPtOnEdge3, _mathPtOnEdge4);
		break;
	case 3:
		if(bSelfWeld == FALSE)
			rc = this->GetSWPointt3T(_mathPtMid, _mathPtOnEdge1, _mathPtOnEdge2, _mathPtOnEdge3, _mathPtOnEdge4);
		else
			rc = this->GetSelfWeldSWPoint3T(_mathPtMid, _mathPtOnEdge1, _mathPtOnEdge2, _mathPtOnEdge3, _mathPtOnEdge4);
		break;
	case 4:
		if(bSelfWeld == FALSE)
			rc = this->GetSWPointt4T(_mathPtMid, _mathPtOnEdge1, _mathPtOnEdge2, _mathPtOnEdge3, _mathPtOnEdge4);
		else
			rc = this->GetSelfWeldSWPoint4T(_mathPtMid, _mathPtOnEdge1, _mathPtOnEdge2, _mathPtOnEdge3, _mathPtOnEdge4);
		break;
	}

	//计算焊点位置失败？失败信息已经在子函数中输出
	if(FAILED(rc))
	{
		_bSelected = FALSE;
		return FALSE;
	}

	cout<<"mathPtOnSurface: "<<_mathPtMid.GetX()<<", "<<_mathPtMid.GetY()<<", "<<_mathPtMid.GetZ()<<endl;
	cout<<"mathPtOnEdge1: "<<_mathPtOnEdge1.GetX()<<", "<<_mathPtOnEdge1.GetY()<<", "<<_mathPtOnEdge1.GetZ()<<endl;
	cout<<"mathPtOnEdge2: "<<_mathPtOnEdge2.GetX()<<", "<<_mathPtOnEdge2.GetY()<<", "<<_mathPtOnEdge2.GetZ()<<endl;
	cout<<"mathPtOnEdge3: "<<_mathPtOnEdge3.GetX()<<", "<<_mathPtOnEdge3.GetY()<<", "<<_mathPtOnEdge3.GetZ()<<endl;
	cout<<"mathPtOnEdge4: "<<_mathPtOnEdge4.GetX()<<", "<<_mathPtOnEdge4.GetY()<<", "<<_mathPtOnEdge4.GetZ()<<endl;	

	//6、检查当前焊点是否合格
	//全局到焊点文件下的坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, _spWeldPrd);
	CATMathPoint mathPtMidLocal = pTransToLocal * _mathPtMid;
	CATUnicodeString ostrError;

	//检查并创建临时元素
	rc = CheckSWPoint(mathPtMidLocal, ostrError);

	//输出错误信息
	if(rc==S_FALSE || rc==E_FAIL)
	{
		////创建输出信息，判断执行OK还是Cancel？
		//ostrError = ostrError;
		//int ifContinue = this->MessageOutPutYesNo(ostrError,"Error");

		_pDlg->SetPREVIEWSensitivity(CATDlgDisable);

		_pDlg->GetPushButton(4)->SetSensitivity(CATDlgDisable);
		_pDlg->GetPushButton(5)->SetSensitivity(CATDlgDisable);

		//if(rc==E_FAIL)
		//	return FALSE;

		//创建输出信息，判断执行OK还是Cancel？
		//ostrError = ostrError + "\n是否继续创建？";
		ostrError = ostrError + "\n is contiue to create？";

		int ifContinue = this->MessageOutPutYesNo(ostrError,"Error");
		//cout<<"ifContinue: "<<ifContinue<<endl;
		if(ifContinue==4)//No
		{
			return FALSE;
		}
	}

	//获取零件属性定义，若为空，则获取零件号
	_pSJDSpotWeldCheck->GetConnectorListName(_spSpecListPart,_strListPartPN);

	//7、创建焊点
	//获得当前焊点几何集下的子几何集，并根据Connections的PartNumber查找，找到返回，找不到创建之
	CATISpecObject_var spSpecSubGeoSet = NULL_var;
	rc = GeneralSWMethod.GetSubGeoSet(_spPrtContainer, spSpecGeoSet, _strListPartPN, spSpecSubGeoSet);	

	//在子几何集下创建焊点
	CATIPrtPart_var spPrtPart = _spPrtContainer->GetPart();
	spPrtPart->SetCurrentFeature(spSpecSubGeoSet);	

	//在当前几何集下创建该点
	CATICkeParm_var spPoint1 = _spCkeParmFactory->CreateReal("X",mathPtMidLocal.GetX());
	CATICkeParm_var spPoint2 = _spCkeParmFactory->CreateReal("Y",mathPtMidLocal.GetY());
	CATICkeParm_var spPoint3 = _spCkeParmFactory->CreateReal("Z",mathPtMidLocal.GetZ());
	CATIGSMPointCoord_var  spiGSMPoint = _spWeldGSMFactory->CreatePoint(spPoint1, spPoint2, spPoint3);
	if(spiGSMPoint==NULL_var)
		return FALSE;

	//添加到结构树上
	CATISpecObject_var  spiVertexPoint = spiGSMPoint;	
	rc=GeneralSWMethod.InsertInProceduralView(spiVertexPoint);
	if (FAILED(rc))
	{
		//_bSelected = FALSE;
		return FALSE;
	}

	spiVertexPoint->Update();
	_spSpecCurrentSWPoint = spiVertexPoint;

	////8、执行Preview后，将PreviewDisable并设为未选择，为下一个焊点选择做准备
	_pDlg->SetPREVIEWSensitivity(CATDlgDisable);
	//_bSelected = FALSE;

	if(_pDlg->GetCheckButton(1)->GetState()==CATDlgCheck)
		_pDlg->GetPushButton(3)->SetSensitivity(CATDlgEnable);

	_pDlg->GetPushButton(4)->SetSensitivity(CATDlgEnable);
	_pDlg->GetPushButton(5)->SetSensitivity(CATDlgEnable);

	//刷新焊点文件
	CATISpecObject_var spPartObject=_spWeldPart;
	if (spPartObject!=NULL_var)
		spPartObject->Update();

	_pSJDSpotWeldCheck->UpdateWeldPart(_spWeldPrd);

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::DeleteNewSWPoint()
{
	_pDlg->GetPushButton(4)->SetSensitivity(CATDlgDisable);
	_pDlg->GetPushButton(3)->SetSensitivity(CATDlgDisable);

	if(_spSpecCurrentSWPoint==NULL_var)
		return TRUE;

	CATISpecObject_var spSpecFather = _spSpecCurrentSWPoint->GetFather();
	spSpecFather->RemoveComponent(_spSpecCurrentSWPoint);

	GeneralSWMethod.UpdateTreeAndRedraw(spSpecFather);

	_spSpecCurrentSWPoint = NULL_var;

	return TRUE;
}

void TestCreateSWPointCmd::CheckPreviewOKSensitivity()
{
	CATBoolean bOK = FALSE;
	if(_spSpecListPart.Size() > 0)
	{
		_pDlg->GetSelectorList(1)->SetSensitivity(CATDlgEnable);
	}
	else
	{
		_pDlg->GetSelectorList(1)->SetSensitivity(CATDlgDisable);
	}
}

//检查点焊
HRESULT TestCreateSWPointCmd::CheckSWPoint(CATMathPoint iMidMathPtL, CATUnicodeString & ostrError)
{
	HRESULT rc = S_OK;

	_strCheckResultList.RemoveAll();
	_bCheckResultList.RemoveAll();

	//1、距离检查
	//边距，搭接面，增加居中的按钮；
	HRESULT rc1 = S_OK;
	if(_pDlg->GetCheckButton(1)->GetState()==CATDlgCheck)
	{
		CATUnicodeString ostrEdgeError;
		rc1 = this->CheckSWPointEdgeDistance(ostrEdgeError);
		if(FAILED(rc1))
		{
			ostrError = ostrEdgeError;
		}
	}

	//2、曲率检查
	//曲率，math点在catsurface上的曲率，曲率半径达不到标准就报错小于200，小于400警告；
	HRESULT rc2 = S_OK;
	if(_pDlg->GetCheckButton(2)->GetState()==CATDlgCheck)
	{
		CATUnicodeString ostrCurvatureError;
		rc2 = this->CheckSWPointCurvature(ostrCurvatureError);
		if(FAILED(rc2))
		{
			ostrError = ostrError + ostrCurvatureError;
		}
	}

	//3、板材厚度比检查，和最厚板材检查
	HRESULT rc3 = S_OK;
	if(_pDlg->GetCheckButton(3)->GetState()==CATDlgCheck)
	{
		CATUnicodeString ostrThicknessError;
		rc3 = this->CheckThicknessRatio(ostrThicknessError);
		if(FAILED(rc3))
		{
			ostrError = ostrError + ostrThicknessError;
		}
	}

	//4、到其他焊点的距离检查？
	HRESULT rc4 = S_OK;
	if(_pDlg->GetCheckButton(4)->GetState()==CATDlgCheck)
	{
		CATUnicodeString ostrSWPtDistanceError;
		rc4 = this->CheckSWPointDistance(iMidMathPtL, ostrSWPtDistanceError);
		if(FAILED(rc4))
		{
			ostrError = ostrError + ostrSWPtDistanceError;
		}
	}

	CATMathTransformation pTransToG = _pSJDGeneralClass->GetMatrixTransformation(_spWeldPrd, _spRootPrd);
	CATMathPoint mathPtMidG = pTransToG * iMidMathPtL;
	_spTempTextForWP->SetDatas(mathPtMidG, _strCheckResultList, _bCheckResultList);

	if(FAILED(rc1) || FAILED(rc2))
		rc = E_FAIL;
	else
	{
		if(FAILED(rc3) || FAILED(rc4))
			rc = S_FALSE;
	}

	return rc;
}

//检查边距
//边距，搭接面，增加居中的按钮；
//四个边都要（生成十字）；
//居中：十字的短边当中；
HRESULT TestCreateSWPointCmd::CheckSWPointEdgeDistance(CATUnicodeString & ostrError)
{
	HRESULT rc = S_OK;

	ostrError = "";

	double dis1 = _mathPtMid.DistanceTo(_mathPtOnEdge1);
	double dis2 = _mathPtMid.DistanceTo(_mathPtOnEdge2);
	double dis3 = _mathPtMid.DistanceTo(_mathPtOnEdge3);
	double dis4 = _mathPtMid.DistanceTo(_mathPtOnEdge4);
	CATUnicodeString strTemp;	

	//1代表颜色为GREEN
	int iColor;
	if((dis1 + dis2) < 16.0)
	{
		rc = E_FAIL;
		//ostrError = "边距检查不合格！";
		ostrError = "Margin check is not qualified！";
		iColor = 2;
	}
	else
	{
		iColor = 1;
	}

	strTemp.BuildFromNum(dis1, "%g");	
	_spTempLineEdge1->SetDatas(_mathPtMid, _mathPtOnEdge1, (char *)strTemp.ConvertToChar(), iColor);

	strTemp.BuildFromNum(dis2, "%g");
	_spTempLineEdge2->SetDatas(_mathPtMid, _mathPtOnEdge2, (char *)strTemp.ConvertToChar(), iColor);

	if((dis3 + dis4) < 16.0)
	{
		rc = E_FAIL;
		//ostrError = "边距检查不合格！";
		ostrError = "Margin check is not qualified！";
		iColor = 2;
	}
	else
	{
		iColor = 1;	
	}
	strTemp.BuildFromNum(dis3, "%g");
	_spTempLineEdge3->SetDatas(_mathPtMid, _mathPtOnEdge3, (char *)strTemp.ConvertToChar(), iColor);

	strTemp.BuildFromNum(dis4, "%g");
	_spTempLineEdge4->SetDatas(_mathPtMid, _mathPtOnEdge4, (char *)strTemp.ConvertToChar(), iColor);

	return rc;
}

//曲率检查
HRESULT TestCreateSWPointCmd::CheckSWPointCurvature(CATUnicodeString & ostrError)
{
	HRESULT rc = S_OK;
	ostrError = "";

	//不需要设置太大，只要大于400即可
	double minCurvature = 999.;	
	for(int i=1; i<=_curvatureRList.Size(); i++)
	{
		if(minCurvature > _curvatureRList[i])
			minCurvature = _curvatureRList[i];
	}

	ostrError.BuildFromNum(minCurvature, "%g");

	CATUnicodeString strInfo;
	int bResult = 1;
	//strInfo = "曲率半径：" + ostrError + "mm；";
	strInfo = "radius of curvature:" + ostrError + "mm；";
	ostrError = "";

	//曲率半径小于200报错，小于400警告
	if(minCurvature <= 200.)
	{
		rc = E_FAIL;		
		//ostrError = "\n错误： 当前焊点处的曲率半径为" + ostrError + "，小于200！";
		ostrError = "\n Error: current radius of curvature is " + ostrError + "，less than 200！";

		bResult = 0;
	}
	else if(minCurvature <= 400.)
	{
		rc = E_FAIL;
		//ostrError = "\n警告： 当前焊点处的曲率半径为" + ostrError + "，小于400！";
		ostrError = "\n Notice:  current radius of curvature is " + ostrError + "，less than 400！";
		bResult = 0;
	}	

	_strCheckResultList.Append(strInfo);
	_bCheckResultList.Append(bResult);

	return rc;
}

//检查板材厚度比
HRESULT TestCreateSWPointCmd::CheckThicknessRatio(CATUnicodeString & ostrError)
{
	HRESULT rc = S_OK;
	ostrError = "";

	//板材厚度比，1/2.5警告，1/3报错,提示信息体现，最大厚度超过5.6，报错，单位mm；
	CATListOfDouble listThickness;
	double oThickness;
	//CATUnicodeString strThickness;
	for(int i=1; i<=_spSpecListPart.Size(); i++)
	{
		_pSJDSpotWeldCheck->GetThicknessFromAPart(_spSpecListPart[i], oThickness);
		listThickness.Append(oThickness);

		if(oThickness==0)
		{
			CATIProduct_var spPrd = _spSpecListPart[i];
			CATUnicodeString strInstName;
			spPrd->GetPrdInstanceName(strInstName);

			//ostrError = "获得厚度失败，请检查模型: "+ strInstName + "；";
			ostrError = "Get thickness failed,pls check the model "+ strInstName + ";";

			_strCheckResultList.Append(ostrError);
			_bCheckResultList.Append(0);

			return E_FAIL;			
		}
	}

	double minThickness, maxThickness;
	minThickness = listThickness[1];
	maxThickness = listThickness[2];
	for(int i=2; i<=listThickness.Size(); i++)
	{
		if(minThickness > listThickness[i])
			minThickness = listThickness[i];

		if(maxThickness < listThickness[i])
			maxThickness = listThickness[i];
	}

	ostrError = "";

	CATUnicodeString strTemp;
	CATUnicodeString strInfo;
	int bResult = 1;
	strTemp.BuildFromNum(maxThickness, "%g");
	//strInfo = "最大厚度：" + strTemp;
	strInfo = "max thickness:" + strTemp;
	strTemp.BuildFromNum(maxThickness/minThickness, "%g");
	//strInfo = strInfo + "; 板材厚度比：" + strTemp + "；";
	strInfo = strInfo + "; Sheet thickness ratio:" + strTemp + ";";

	if(maxThickness>5.6)
	{
		rc = E_FAIL;
		//ostrError = "\n错误：板材最大厚度超过5.6mm！";
		ostrError = "\n Error：max thickness greater than 5.6mm！";
		bResult = 0;
	}

	double ratio = minThickness/maxThickness;
	cout<<"minThickness: "<<minThickness<<endl;
	cout<<"maxThickness: "<<maxThickness<<endl;
	cout<<"ratio: "<<ratio<<endl;
	if((minThickness/maxThickness) < (1/3))
	{
		rc = E_FAIL;
		//ostrError = ostrError + "\n错误：板材厚度比大于3：1！";
		ostrError = ostrError + "\n Error：Sheet thickness ratio greater than 3:1！";
		bResult = 0;
	}
	else if((minThickness/maxThickness) < (1/2.5))
	{
		rc = E_FAIL;
		//ostrError = ostrError + "\n警告：板材厚度比大于2.5：1！";
		ostrError = ostrError + "\n Notice：Sheet thickness ratio greater than 2.5:1！";
		bResult = 0;
	}

	_strCheckResultList.Append(strInfo);
	_bCheckResultList.Append(bResult);

	return rc;
}

//检查到其他焊点的距离
HRESULT TestCreateSWPointCmd::CheckSWPointDistance(CATMathPoint iMidMathPtL, 
													CATUnicodeString & ostrError)
{
	HRESULT rc = S_OK;
	ostrError = "";

	//到其他焊点的距离，检查当前part下的2T\3T\4T下的点，找出最近的距离，
	//临时特征显示出来（两点连线，中点偏5左右显示文字）；小于60mm的报错；

	//获得焊点part下的焊点几何集（2T\3T\4T几何集）
	CATISpecObject_var spSpecGeoSet2T = NULL_var;
	CATISpecObject_var spSpecGeoSet3T = NULL_var;
	CATISpecObject_var spSpecGeoSet4T = NULL_var;
	//rc = GeneralSWMethod.GetGeoSet(_spWeldPrd, SpotWelds2T, spSpecGeoSet2T);	
	//rc = GeneralSWMethod.GetGeoSet(_spWeldPrd, SpotWelds3T, spSpecGeoSet3T);
	//rc = GeneralSWMethod.GetGeoSet(_spWeldPrd, SpotWelds4T, spSpecGeoSet4T);

	rc = GeneralSWMethod.GetGeoSet(_spWeldPrd, "2T Spotwelds", spSpecGeoSet2T);	
	rc = GeneralSWMethod.GetGeoSet(_spWeldPrd, "3T Spotwelds", spSpecGeoSet3T);
	rc = GeneralSWMethod.GetGeoSet(_spWeldPrd, "4T Spotwelds", spSpecGeoSet4T);

	//获得焊点part下几何集中的点
	CATListValCATISpecObject_var splistPts1;
	CATListValCATISpecObject_var splistPts2;
	CATListValCATISpecObject_var splistPts3;
	CATIDescendants *piDescPart=NULL;
	if(spSpecGeoSet2T!=NULL_var)
	{		
		rc = spSpecGeoSet2T->QueryInterface(IID_CATIDescendants, (void**)&piDescPart);
		if(piDescPart!=NULL)
		{
			piDescPart->GetAllChildren("CATIMfZeroDimResult",splistPts1);
		}		
	}
	if(spSpecGeoSet3T!=NULL_var)
	{		
		rc = spSpecGeoSet3T->QueryInterface(IID_CATIDescendants, (void**)&piDescPart);
		if(piDescPart!=NULL)
		{
			piDescPart->GetAllChildren("CATIMfZeroDimResult",splistPts2);
		}		
	}
	if(spSpecGeoSet4T!=NULL_var)
	{		
		rc = spSpecGeoSet4T->QueryInterface(IID_CATIDescendants, (void**)&piDescPart);
		if(piDescPart!=NULL)
		{
			piDescPart->GetAllChildren("CATIMfZeroDimResult",splistPts3);
		}		
	}
	CATLISTV(CATMathPoint) listMathPt;
	CATIGSMPointCoord * pGSMPtCoord = NULL;
	CATICkeParm_var xParm, yParm, zParm;
	CATMathPoint mathPtTemp;
	CATIMeasurableInContext_var spMeasurableInContext = NULL_var;
	if(splistPts1.Size()>0)
	{
		for(int i=1; i<=splistPts1.Size(); i++)
		{
			spMeasurableInContext = splistPts1[i];
			spMeasurableInContext->GetPoint(mathPtTemp);

			listMathPt.Append(mathPtTemp);
		}
	}
	if(splistPts2.Size()>0)
	{
		for(int i=1; i<=splistPts2.Size(); i++)
		{
			spMeasurableInContext = splistPts2[i];
			spMeasurableInContext->GetPoint(mathPtTemp);

			listMathPt.Append(mathPtTemp);
		}
	}
	if(splistPts3.Size()>0)
	{
		for(int i=1; i<=splistPts3.Size(); i++)
		{
			spMeasurableInContext = splistPts3[i];
			spMeasurableInContext->GetPoint(mathPtTemp);

			listMathPt.Append(mathPtTemp);
		}
	}	

	if(listMathPt.Size()<=0)
		return S_OK;

	//判断距离
	double dis;
	double minDis;
	CATMathPoint minMathPt;
	for(int i=1; i<=listMathPt.Size(); i++)
	{
		dis = iMidMathPtL.DistanceTo(listMathPt[i]);
		if(i==1)
		{
			minDis = dis;
			minMathPt = listMathPt[i];
			continue;
		}

		if(dis < minDis)
		{
			minDis = dis;
			minMathPt = listMathPt[i];
		}
	}

	CATMathTransformation pTransToG = _pSJDGeneralClass->GetMatrixTransformation(_spWeldPrd, _spRootPrd);
	CATMathPoint mathPtMidG = pTransToG * iMidMathPtL;
	CATMathPoint mathPtMinG = pTransToG * minMathPt;

	CATUnicodeString strTemp;
	strTemp.BuildFromNum(minDis, "%g");	

	CATUnicodeString strInfo;
	int bResult = 1;
	//strInfo = "和其他焊点的距离：" + strTemp + "mm；";
	strInfo = "the distance between other spot is " + strTemp + "mm；";

	if(minDis<60.)
	{	
		_spTempLineSWPoint->SetDatas(mathPtMidG, mathPtMinG, (char *)strTemp.ConvertToChar(),2);

		//ostrError = "\n错误： 当前焊点距离其他焊点距离为" + strTemp + "，小于60mm！";
		ostrError = "\n Error: the distance between other spot is " + strTemp + "，less than 60mm！";

		bResult = 0;
		rc = E_FAIL;
	}
	else
	{
		_spTempLineSWPoint->SetDatas(mathPtMidG, mathPtMinG, (char *)strTemp.ConvertToChar(),1);
		rc = S_OK;
	}

	_strCheckResultList.Append(strInfo);
	_bCheckResultList.Append(bResult);

	return rc;
}

//Get2TPositionOfSW
HRESULT TestCreateSWPointCmd::GetSWPointt2T(CATMathPoint & oMidSWPt,
											 CATMathPoint & oMathPt1,
											 CATMathPoint & oMathPt2,
											 CATMathPoint & oMathPt3,
											 CATMathPoint & oMathPt4)
{
	HRESULT rc=S_OK;

	CATMathTransformation pTransToLocal;
	CATMathTransformation pTransToGlobal;

	//1、获得临时点的坐标（Global）
	CATMathPoint mathPtOnSurfaceG;
	rc = _spTempPoint->GetPosition(&mathPtOnSurfaceG);
	if(FAILED(rc))
	{
		return E_FAIL;
	}

	//2、坐标变换，将临时点坐标转换到BaseSurface所在的Part的Local坐标
	//获得全局向局部转换的坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, _spSurfacePrd);
	//计算Local点坐标
	CATMathPoint mathPtOnSurfaceL = pTransToLocal*mathPtOnSurfaceG;

	//3、获得临时点处Base曲面的法线方向	
	//获得临时点在所选曲面处的法线方向，local
	CATMathVector normalVector;
	double oDis;
	_pSJDGeneralClass->SJDGetMinDistanceBetweenPointAndFace(_spFace, mathPtOnSurfaceL, oDis, normalVector);

	//将该方向转为Global
	pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(_spSurfacePrd, _spRootPrd);
	CATMathVector oNormalVG = pTransToGlobal*normalVector;

	//4、法线方向和每个连接件PartBody相交，得到交点列表（每个件取离临时点较近的两个点）
	CATIProduct_var spConnectionPrd = NULL_var;
	CATMathPoint mathPointL;//所选的点转到connection局部
	CATMathVector mathNormalVectorL;//所选点处的Normal方向转到Connection局部
	CATLISTV(CATMathPoint) resultPointList;
	CATLISTV(CATMathPoint) ConnectionsPointList;
	for(int i=1; i<=_spSpecListPart.Size(); i++)
	{
		//connection prd
		spConnectionPrd = _spSpecListPart[i];

		//全局转为connection坐标变换
		pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, spConnectionPrd);
		pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(spConnectionPrd, _spRootPrd);

		//局部
		mathPointL = pTransToLocal * mathPtOnSurfaceG;
		mathNormalVectorL = pTransToLocal * oNormalVG;

		//获得由在该点和方向线组成的直线和该连接件PartBody的交点列表（取最近的两个点）
		rc = _pSJDSpotWeldCheck->GetInsertPointInPart(spConnectionPrd, mathPointL, mathNormalVectorL,ConnectionsPointList);		
		if(FAILED(rc) || ConnectionsPointList.Size()!=2)
		{
			return E_FAIL;
		}

		//将所获得的点转为全局坐标
		for(int j=1; j<=2; j++)
		{
			CATMathPoint mathPtG = pTransToGlobal*ConnectionsPointList[j];
			resultPointList.Append(mathPtG);
		}

		ConnectionsPointList.RemoveAll();		
	}

	//5、获得两个件中距离最近的两个点
	int iFlag1;
	int iFlag2;
	double minDis = 1000;
	double dis1, dis2;
	for(int i=1; i<=2; i++)
	{
		dis1 = resultPointList[i].DistanceTo(resultPointList[3]);
		if(dis1<minDis)
		{
			minDis = dis1;
			iFlag1 = i;
			iFlag2 = 3;
		}
		dis2 = resultPointList[i].DistanceTo(resultPointList[4]);
		if(dis2<minDis)
		{
			minDis = dis2;
			iFlag1 = i;
			iFlag2 = 4;
		}
	}

	//6、取中点
	CATMathPoint mathPtMid = 0.5*(resultPointList[iFlag1] + resultPointList[iFlag2]);

	////全局到焊点文件下的坐标变换
	//pTransToLocal = _pGeneralClass->GetMatrixTransformation(_spRootPrd, _spWeldPrd);
	//mathPtMid = pTransToLocal * mathPtMid;

	//7、中点输出
	oMidSWPt = mathPtMid;

	//8、获得贴合面上的四个点数据
	CATLISTV(CATMathPoint) mathPtList;
	CATListValCATISpecObject_var spSpecListPart;
	mathPtList.Append(resultPointList[iFlag1]);
	mathPtList.Append(resultPointList[iFlag2]);
	spSpecListPart.Append(_spSpecListPart[1]);
	spSpecListPart.Append(_spSpecListPart[2]);

	_curvatureRList.RemoveAll();
	this->GetNearestPtsAll(oMidSWPt, mathPtList, spSpecListPart, oMathPt1, oMathPt2, oMathPt3, oMathPt4, 
		_centerMathPtG, _curvatureRList);

	//删除列表
	resultPointList.RemoveAll();
	mathPtList.RemoveAll();
	spSpecListPart.RemoveAll();

	return rc;
}

//自焊件
HRESULT TestCreateSWPointCmd::GetSelfWeldSWPoint2T(CATMathPoint & oMidSWPt, 
													CATMathPoint & oMathPt1, 
													CATMathPoint & oMathPt2, 
													CATMathPoint & oMathPt3, 
													CATMathPoint & oMathPt4)
{
	HRESULT rc = S_OK;
	CATMathTransformation pTransToLocal;
	CATMathTransformation pTransToGlobal;

	//1、获得临时点的坐标（Global）
	CATMathPoint mathPtOnSurfaceG;
	rc = _spTempPoint->GetPosition(&mathPtOnSurfaceG);
	if(FAILED(rc))
	{
		return E_FAIL;
	}

	//2、坐标变换，将临时点坐标转换到BaseSurface所在的Part的Local坐标
	//获得全局向局部转换的坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, _spSurfacePrd);
	//计算Local点坐标
	CATMathPoint mathPtOnSurfaceL = pTransToLocal*mathPtOnSurfaceG;

	//3、获得临时点处Base曲面的法线方向	
	//获得临时点在所选曲面处的法线方向，local
	CATMathVector normalVector;
	double oDis;
	_pSJDGeneralClass->SJDGetMinDistanceBetweenPointAndFace(_spFace, mathPtOnSurfaceL, oDis, normalVector);

	CATMathPoint nearPt;
	this->GetMinDistanceBetweenPointAndFace(_spFace, mathPtOnSurfaceL, oDis, normalVector, nearPt);
	
	//将该方向转为Global
	pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(_spSurfacePrd, _spRootPrd);
	CATMathVector oNormalVG = pTransToGlobal*normalVector;

	//4、法线方向和每个连接件PartBody相交，得到交点列表（每个件取离临时点较近的两个点）
	//自焊件，只需要计算一个零件
	CATIProduct_var spConnectionPrd = _spSpecListPart[1];

	//全局转为connection坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, spConnectionPrd);
	pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(spConnectionPrd, _spRootPrd);

	//局部
	CATMathPoint mathPointL = pTransToLocal * mathPtOnSurfaceG;
	CATMathVector mathNormalVectorL = pTransToLocal * oNormalVG;

	//获得由在该点和方向线组成的直线和该连接件PartBody的交点列表（取最近的四个点）
	CATLISTV(CATMathPoint) ConnectionsPointList;
	rc = this->GetInsertPointInPartWithNum(4, spConnectionPrd, mathPointL, mathNormalVectorL, ConnectionsPointList);
	if(FAILED(rc) || ConnectionsPointList.Size()!=4)
	{
		return E_FAIL;
	}

	//将所获得的点转为全局坐标
	CATLISTV(CATMathPoint) resultPointList;
	for(int j=1; j<=4; j++)
	{
		CATMathPoint mathPtG = pTransToGlobal*ConnectionsPointList[j];
		resultPointList.Append(mathPtG);
	}
	ConnectionsPointList.RemoveAll();

	//5、获得四个点中距离最近的两个点
	int iFlag1;
	int iFlag2;
	double minDis = 1000;
	double disTemp;
	for(int i=1; i<=3; i++)
	{
		for(int j=i+1; j<=4; j++)
		{
			disTemp = resultPointList[i].DistanceTo(resultPointList[j]);
			if(disTemp < minDis)
			{
				minDis = disTemp;
				iFlag1 = i;
				iFlag2 = j;
			}
		}
	}

	//6、取中点
	CATMathPoint mathPt1 = resultPointList[iFlag1];
	CATMathPoint mathPt2 = resultPointList[iFlag2];
	CATMathPoint mathPtMid = 0.5*(resultPointList[iFlag1] + resultPointList[iFlag2]);
	////全局到焊点文件下的坐标变换
	//pTransToLocal = _pGeneralClass->GetMatrixTransformation(_spRootPrd, _spWeldPrd);
	//mathPtMid = pTransToLocal * mathPtMid;

	//7、中点输出
	oMidSWPt = mathPtMid;

	//8、获得贴合面上的四个点数据
	CATLISTV(CATMathPoint) mathPtList;
	CATListValCATISpecObject_var spSpecListPart;
	CATListOfInt listNum;
	mathPtList.Append(resultPointList[iFlag1]);
	//mathPtList.Append(resultPointList[iFlag2]);
	spSpecListPart.Append(_spSpecListPart[1]);
	//spSpecListPart.Append(_spSpecListPart[2]);
	listNum.Append(2);

	_curvatureRList.RemoveAll();
	this->GetSelfWeldNearestPtsAll(oMidSWPt, mathPtList, listNum, spSpecListPart, oMathPt1, oMathPt2, oMathPt3, oMathPt4, _centerMathPtG, _curvatureRList);

	//删除列表
	resultPointList.RemoveAll();
	mathPtList.RemoveAll();
	spSpecListPart.RemoveAll();

	return rc;
}

//Get3TPositionOfSW
HRESULT TestCreateSWPointCmd::GetSWPointt3T(CATMathPoint & oMidSWPt,
											 CATMathPoint & oMathPt1,
											 CATMathPoint & oMathPt2,
											 CATMathPoint & oMathPt3,
											 CATMathPoint & oMathPt4)
{ 
	HRESULT rc=S_OK;

	CATMathTransformation pTransToLocal;
	CATMathTransformation pTransToGlobal;


	//1、获得临时点的坐标（Global）
	CATMathPoint mathPtOnSurfaceG;
	rc = _spTempPoint->GetPosition(&mathPtOnSurfaceG);
	if(FAILED(rc))
	{
		return E_FAIL;
	}

	//2、坐标变换，将临时点坐标转换到BaseSurface所在的Part的Local坐标
	//获得全局向局部转换的坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, _spSurfacePrd);
	//计算Local点坐标
	CATMathPoint mathPtOnSurfaceL = pTransToLocal*mathPtOnSurfaceG;

	//3、获得临时点处Base曲面的法线方向	
	//获得临时点在所选曲面处的法线方向，local
	CATMathVector normalVector;
	double oDis;
	_pSJDGeneralClass->SJDGetMinDistanceBetweenPointAndFace(_spFace, mathPtOnSurfaceL, oDis, normalVector);
	//将该方向转为Global
	pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(_spSurfacePrd, _spRootPrd);
	CATMathVector oNormalVG = pTransToGlobal*normalVector;


	//4、法线方向和每个连接件PartBody相交，得到交点列表（每个件取离临时点较近的两个点）
	CATIProduct_var spConnectionPrd = NULL_var;
	CATMathPoint mathPointL;//所选的点转到connection局部
	CATMathVector mathNormalVectorL;//所选点处的Normal方向转到Connection局部
	CATLISTV(CATMathPoint) resultPointList;//全局坐标
	CATLISTV(CATMathPoint) resultMidPointList;//全局坐标
	CATLISTV(CATMathPoint) ConnectionsPointList;//全局坐标
	for(int i=1; i<=_spSpecListPart.Size(); i++)
	{
		//connection prd
		spConnectionPrd = _spSpecListPart[i];

		//全局转为connection坐标变换
		pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, spConnectionPrd);
		pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(spConnectionPrd, _spRootPrd);

		//局部
		mathPointL = pTransToLocal * mathPtOnSurfaceG;
		mathNormalVectorL = pTransToLocal * oNormalVG;

		//获得由在该点和方向线组成的直线和该连接件PartBody的交点列表（取最近的两个点）
		rc = _pSJDSpotWeldCheck->GetInsertPointInPart(spConnectionPrd, mathPointL, mathNormalVectorL,ConnectionsPointList);		
		if(FAILED(rc) || ConnectionsPointList.Size()!=2)
		{
			return E_FAIL;
		}

		//将所获得的两点取中点，转为全局，保存
		CATMathPoint mathPtMid = 0.5*(ConnectionsPointList[1] + ConnectionsPointList[2]);
		mathPtMid = pTransToGlobal*mathPtMid;		
		CATMathPoint mathPointG1 = pTransToGlobal*ConnectionsPointList[1];
		CATMathPoint mathPointG2 = pTransToGlobal*ConnectionsPointList[2];
		resultMidPointList.Append(mathPtMid);		
		resultPointList.Append(mathPointG1);
		resultPointList.Append(mathPointG2);

		ConnectionsPointList.RemoveAll();		
	}

	//4、计算所选点到三个件的中点的向量和曲面法向向量点乘
	CATMathVector vecTemp;
	CATListOfDouble listDis;
	for(int i=1; i<=3; i++)
	{
		vecTemp = resultMidPointList[i] - mathPtOnSurfaceG;
		oDis = vecTemp * oNormalVG;
		listDis.Append(oDis);
	}

	//5、取中点
	CATListOfDouble listDisTemp = listDis;
	listDisTemp.QuickSort();	
	CATMathPoint mathPtMid;
	int iFlag;
	for(int i=1; i<=3; i++)
	{
		//找到中间的点
		if(listDisTemp[2] == listDis[i])
		{
			iFlag = i;
			mathPtMid = resultMidPointList[i];
			break;
		}
	}
	////全局到焊点文件下的坐标变换
	//pTransToLocal = _pGeneralClass->GetMatrixTransformation(_spRootPrd, _spWeldPrd);
	//mathPtMid = pTransToLocal * mathPtMid;
	//删除列表
	listDis.RemoveAll();
	listDisTemp.RemoveAll();	

	//6、中点输出
	oMidSWPt = mathPtMid;

	//7、获得贴合面上的四个点数据
	CATLISTV(CATMathPoint) mathPtList;
	CATListValCATISpecObject_var spSpecListPart;
	for(int i=1; i<=3; i++)
	{
		if(iFlag != i)
		{
			if(mathPtMid.DistanceTo(resultPointList[2*i-1]) < mathPtMid.DistanceTo(resultPointList[2*i]))
				mathPtList.Append(resultPointList[2*i-1]);
			else
				mathPtList.Append(resultPointList[2*i]);
			spSpecListPart.Append(_spSpecListPart[i]);
		}
		else
		{
			mathPtList.Append(resultPointList[i*2-1]);
			mathPtList.Append(resultPointList[i*2]);
			spSpecListPart.Append(_spSpecListPart[i]);
			spSpecListPart.Append(_spSpecListPart[i]);
		}
	}

	_curvatureRList.RemoveAll();
	this->GetNearestPtsAll(oMidSWPt, mathPtList, spSpecListPart, oMathPt1, oMathPt2, oMathPt3, oMathPt4, 
		_centerMathPtG, _curvatureRList);

	//删除列表
	resultPointList.RemoveAll();
	resultMidPointList.RemoveAll();
	mathPtList.RemoveAll();
	spSpecListPart.RemoveAll();

	return rc;
}

//自焊件
HRESULT TestCreateSWPointCmd::GetSelfWeldSWPoint3T(CATMathPoint & oMidSWPt, 
													CATMathPoint & oMathPt1, 
													CATMathPoint & oMathPt2, 
													CATMathPoint & oMathPt3, 
													CATMathPoint & oMathPt4)
{
	HRESULT rc=S_OK;

	CATMathTransformation pTransToLocal;
	CATMathTransformation pTransToGlobal;

	//1、获得临时点的坐标（Global）
	CATMathPoint mathPtOnSurfaceG;
	rc = _spTempPoint->GetPosition(&mathPtOnSurfaceG);
	if(FAILED(rc))
	{
		return E_FAIL;
	}

	//2、坐标变换，将临时点坐标转换到BaseSurface所在的Part的Local坐标
	//获得全局向局部转换的坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, _spSurfacePrd);
	//计算Local点坐标
	CATMathPoint mathPtOnSurfaceL = pTransToLocal*mathPtOnSurfaceG;

	//3、获得临时点处Base曲面的法线方向	
	//获得临时点在所选曲面处的法线方向，local
	CATMathVector normalVector;
	double oDis;
	_pSJDGeneralClass->SJDGetMinDistanceBetweenPointAndFace(_spFace, mathPtOnSurfaceL, oDis, normalVector);
	//将该方向转为Global
	pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(_spSurfacePrd, _spRootPrd);
	CATMathVector oNormalVG = pTransToGlobal*normalVector;

	//4、判断零件重复次数
	CATBoolean bExist;
	CATBaseUnknown_var spBase1;
	CATBaseUnknown_var spBase2;
	CATListValCATISpecObject_var spSpecListPart;
	CATListOfInt listPartNum;
	spSpecListPart.Append(_spSpecListPart[1]);
	for(int i=2; i<=_spSpecListPart.Size(); i++)
	{
		bExist = FALSE;
		for(int j=1; j<=spSpecListPart.Size(); j++)
		{
			spBase1 = _spSpecListPart[i];
			spBase2 = spSpecListPart[j];
			if(spBase1->IsEqual(spBase2))
			{
				bExist = TRUE;
				break;
			}
		}
		if(bExist == FALSE)
			spSpecListPart.Append(_spSpecListPart[i]);
	}
	int num;
	for(int i=1; i<=spSpecListPart.Size(); i++)
	{
		spBase1 = spSpecListPart[i];
		num = 0;

		for(int j=1; j<=_spSpecListPart.Size(); j++)
		{

			spBase2 = _spSpecListPart[j];
			if(spBase1->IsEqual(spBase2))
			{
				num++;
			}
		}
		listPartNum.Append(num);
	}

	//4、法线方向和每个连接件PartBody相交，得到交点列表（每个件取离临时点较近的两个点）
	CATIProduct_var spConnectionPrd = NULL_var;
	CATMathPoint mathPointL;//所选的点转到connection局部
	CATMathVector mathNormalVectorL;//所选点处的Normal方向转到Connection局部
	CATLISTV(CATMathPoint) resultPointList;//全局坐标
	CATLISTV(CATMathPoint) resultMidPointList;//全局坐标
	CATLISTV(CATMathPoint) ConnectionsPointList;//全局坐标
	CATListValCATISpecObject_var ConnectionsList;//零件列表
	for(int i=1; i<=spSpecListPart.Size(); i++)
	{
		//connection prd
		spConnectionPrd = spSpecListPart[i];
		num = listPartNum[i];

		//全局转为connection坐标变换
		pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, spConnectionPrd);
		pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(spConnectionPrd, _spRootPrd);

		//局部
		mathPointL = pTransToLocal * mathPtOnSurfaceG;
		mathNormalVectorL = pTransToLocal * oNormalVG;

		//获得由在该点和方向线组成的直线和该连接件PartBody的交点列表（取最近的两个点）
		rc = this->GetInsertPointInPartWithNum(2*num, spConnectionPrd, mathPointL, mathNormalVectorL, ConnectionsPointList);
		if(FAILED(rc) || ConnectionsPointList.Size()!=2*num)
		{
			return E_FAIL;
		}

		//将所获得的两点取中点，转为全局，保存
		//对点排序
		_pSJDSpotWeldCheck->SortMathPtWithDistance(mathPointL, ConnectionsPointList);

		//计算中点
		CATMathPoint mathPtMid;
		CATMathPoint mathPtG1;
		CATMathPoint mathPtG2;
		for(int i=1; i<=num; i=i++)
		{
			mathPtMid = 0.5*(ConnectionsPointList[2*i-1] + ConnectionsPointList[2*i]);
			mathPtMid = pTransToGlobal*mathPtMid;
			mathPtG1 = pTransToGlobal*ConnectionsPointList[2*i-1];
			mathPtG2 = pTransToGlobal*ConnectionsPointList[2*i];
			resultMidPointList.Append(mathPtMid);		
			resultPointList.Append(mathPtG1);
			resultPointList.Append(mathPtG2);
			ConnectionsList.Append(spConnectionPrd);
		}

		ConnectionsPointList.RemoveAll();
	}
	spSpecListPart.RemoveAll();
	listPartNum.RemoveAll();

	//4、计算所选点到三个件的中点的向量和曲面法向向量点乘
	CATMathVector vecTemp;
	CATListOfDouble listDis;
	for(int i=1; i<=3; i++)
	{
		vecTemp = resultMidPointList[i] - mathPtOnSurfaceG;
		oDis = vecTemp * oNormalVG;
		listDis.Append(oDis);
	}

	//5、取中点
	CATListOfDouble listDisTemp = listDis;
	listDisTemp.QuickSort();	
	CATMathPoint mathPtMid;
	int iFlag;
	for(int i=1; i<=3; i++)
	{
		//找到中间的点
		if(listDisTemp[2] == listDis[i])
		{
			iFlag = i;
			mathPtMid = resultMidPointList[i];
			break;
		}
	}
	////全局到焊点文件下的坐标变换
	//pTransToLocal = _pGeneralClass->GetMatrixTransformation(_spRootPrd, _spWeldPrd);
	//mathPtMid = pTransToLocal * mathPtMid;
	//删除列表
	listDis.RemoveAll();
	listDisTemp.RemoveAll();	

	//6、中点输出
	oMidSWPt = mathPtMid;

	//7、获得贴合面上的四个点数据
	CATLISTV(CATMathPoint) mathPtList;
	CATListOfInt listNum;
	for(int i=1; i<=3; i++)
	{
		if(iFlag != i)
		{
			if(mathPtMid.DistanceTo(resultPointList[2*i-1]) < mathPtMid.DistanceTo(resultPointList[2*i]))
				mathPtList.Append(resultPointList[2*i-1]);
			else
				mathPtList.Append(resultPointList[2*i]);
			spSpecListPart.Append(ConnectionsList[i]);
			listNum.Append(1);
		}
		else
		{
			mathPtList.Append(resultPointList[i*2-1]);
			mathPtList.Append(resultPointList[i*2]);
			spSpecListPart.Append(ConnectionsList[i]);
			spSpecListPart.Append(ConnectionsList[i]);
			listNum.Append(1);
			listNum.Append(1);
		}
	}

	//获得距离为0的两个点
	int iFlag1;
	int iFlag2;
	CATBoolean bFind = FALSE;
	for(int i=1; i<=mathPtList.Size()-1; i++)
	{
		for(int j=i+1; j<=mathPtList.Size(); j++)
		{
			if(mathPtList[i].DistanceTo(mathPtList[j]) == 0)
			{
				iFlag1 = i;
				iFlag2 = j;
				bFind = TRUE;
				break;
			}
		}
		if(bFind == TRUE)
			break;
	}
	listNum[iFlag1] = 2;

	CATLISTV(CATMathPoint) mathPtListNew;
	CATListOfInt listNumNew;
	CATListValCATISpecObject_var spSpecListPartNew;
	if(bFind == TRUE)
	{
		for(int i=1; i<=mathPtList.Size(); i++)
		{
			if(i==iFlag2) 
				continue;

			mathPtListNew.Append(mathPtList[i]);
			listNumNew.Append(listNum[i]);
			spSpecListPartNew.Append(spSpecListPart[i]);
		}
	}
	else
	{
		for(int i=1; i<=mathPtList.Size(); i++)
		{
			mathPtListNew.Append(mathPtList[i]);
			listNumNew.Append(listNum[i]);
			spSpecListPartNew.Append(spSpecListPart[i]);
		}
	}
	mathPtList.RemoveAll();
	listNum.RemoveAll();
	spSpecListPart.RemoveAll();

	_curvatureRList.RemoveAll();
	this->GetSelfWeldNearestPtsAll(oMidSWPt, mathPtListNew, listNumNew, spSpecListPartNew, oMathPt1, oMathPt2, oMathPt3, oMathPt4, _centerMathPtG, _curvatureRList);

	//删除列表
	resultPointList.RemoveAll();
	resultMidPointList.RemoveAll();
	ConnectionsList.RemoveAll();

	mathPtListNew.RemoveAll();
	listNumNew.RemoveAll();
	spSpecListPartNew.RemoveAll();

	return rc;
}

//Get4TPositionOfSW
HRESULT TestCreateSWPointCmd::GetSWPointt4T(CATMathPoint & oMidSWPt,
											 CATMathPoint & oMathPt1,
											 CATMathPoint & oMathPt2,
											 CATMathPoint & oMathPt3,
											 CATMathPoint & oMathPt4)
{
	HRESULT rc=S_OK;

	CATMathTransformation pTransToLocal;
	CATMathTransformation pTransToGlobal;

	//1、获得临时点的坐标（Global）
	CATMathPoint mathPtOnSurfaceG;
	rc = _spTempPoint->GetPosition(&mathPtOnSurfaceG);
	if(FAILED(rc))
	{
		return E_FAIL;
	}

	//2、坐标变换，将临时点坐标转换到BaseSurface所在的Part的Local坐标
	//获得全局向局部转换的坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, _spSurfacePrd);
	//计算Local点坐标
	CATMathPoint mathPtOnSurfaceL = pTransToLocal*mathPtOnSurfaceG;

	//3、获得临时点处Base曲面的法线方向	
	//获得临时点在所选曲面处的法线方向，local
	CATMathVector normalVector;
	double oDis;
	_pSJDGeneralClass->SJDGetMinDistanceBetweenPointAndFace(_spFace, mathPtOnSurfaceL, oDis, normalVector);
	//将该方向转为Global
	pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(_spSurfacePrd, _spRootPrd);
	CATMathVector oNormalVG = pTransToGlobal*normalVector;

	//4、法线方向和每个连接件PartBody相交，得到交点列表（每个件取离临时点较近的两个点）
	CATIProduct_var spConnectionPrd = NULL_var;
	CATMathPoint mathPointL;//所选的点转到connection局部
	CATMathVector mathNormalVectorL;//所选点处的Normal方向转到Connection局部
	CATLISTV(CATMathPoint) resultPointList;
	CATLISTV(CATMathPoint) resultMidPointList;
	CATLISTV(CATMathPoint) ConnectionsPointList;
	for(int i=1; i<=_spSpecListPart.Size(); i++)
	{
		//connection prd
		spConnectionPrd = _spSpecListPart[i];

		//全局转为connection坐标变换
		pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, spConnectionPrd);
		pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(spConnectionPrd, _spRootPrd);

		//局部
		mathPointL = pTransToLocal * mathPtOnSurfaceG;
		mathNormalVectorL = pTransToLocal * oNormalVG;

		//获得由在该点和方向线组成的直线和该连接件PartBody的交点列表（取最近的两个点）
		rc = _pSJDSpotWeldCheck->GetInsertPointInPart(spConnectionPrd, mathPointL, mathNormalVectorL, ConnectionsPointList);
		if(FAILED(rc) || ConnectionsPointList.Size()!=2)
		{
			return E_FAIL;
		}

		//将所获得的点转为全局坐标
		for(int j=1; j<=2; j++)
		{
			CATMathPoint mathPtG = pTransToGlobal*ConnectionsPointList[j];
			resultPointList.Append(mathPtG);
		}
		CATMathPoint mathPtMid = 0.5*(ConnectionsPointList[1] + ConnectionsPointList[2]);
		mathPtMid = pTransToGlobal*mathPtMid;
		resultMidPointList.Append(mathPtMid);

		ConnectionsPointList.RemoveAll();
	}

	////4、计算所选点到四个件的中点的向量和曲面法向向量点乘
	CATMathVector vecTemp;
	CATListOfDouble listDis;
	for(int i=1; i<=4; i++)
	{
		vecTemp = resultMidPointList[i] - mathPtOnSurfaceG;
		oDis = vecTemp * oNormalVG;
		listDis.Append(oDis);
	}

	//5、取中间两个Part的编号
	CATListOfDouble listDisTemp = listDis;
	listDisTemp.QuickSort();
	int iFlagPart1;//第二个件的两点在resultPointList中的列表序号为iFlagPart1*2-1, iFlagPart1*2
	int iFlagPart2;//第三个件的两点在resultPointList中的列表序号为iFlagPart2*2-1, iFlagPart2*2
	for(int i=1; i<=4; i++)
	{
		//找到第二个点
		if(listDisTemp[2] == listDis[i])
		{
			iFlagPart1 = i;
		}

		//找到第三个点
		if(listDisTemp[3] == listDis[i])
		{
			iFlagPart2 = i;
		}
	}
	listDisTemp.RemoveAll();
	listDis.RemoveAll();

	//6、获得中间两个件四个点中距离较近的两个点
	int iFlagPt1;
	int iFlagPt2;
	double minDis = 1000;
	double dis1, dis2;
	for(int i=iFlagPart1*2-1; i<=iFlagPart1*2; i++)
	{
		dis1 = resultPointList[i].DistanceTo(resultPointList[iFlagPart2*2-1]);
		if(dis1<minDis)
		{
			minDis = dis1;
			iFlagPt1 = i;
			iFlagPt2 = iFlagPart2*2-1;
		}
		dis2 = resultPointList[i].DistanceTo(resultPointList[iFlagPart2*2]);
		if(dis2<minDis)
		{
			minDis = dis2;
			iFlagPt1 = i;
			iFlagPt2 = iFlagPart2*2;
		}
	}

	//7、取中点
	CATMathPoint mathPtMid = 0.5*(resultPointList[iFlagPt1] + resultPointList[iFlagPt2]);
	////全局到焊点文件下的坐标变换
	//pTransToLocal = _pGeneralClass->GetMatrixTransformation(_spRootPrd, _spWeldPrd);
	//mathPtMid = pTransToLocal * mathPtMid;	

	//8、中点输出
	oMidSWPt = mathPtMid;

	//9、获得贴合面上的四个点数据
	CATLISTV(CATMathPoint) mathPtList;
	CATListValCATISpecObject_var spSpecListPart;
	for(int i=1; i<=4; i++)
	{
		if(iFlagPart1 == i ||  iFlagPart2 == i)
		{
			mathPtList.Append(resultPointList[i*2-1]);
			spSpecListPart.Append(_spSpecListPart[i]);

			mathPtList.Append(resultPointList[i*2]);			
			spSpecListPart.Append(_spSpecListPart[i]);
		}
		else
		{
			if(mathPtMid.DistanceTo(resultPointList[2*i-1]) < mathPtMid.DistanceTo(resultPointList[2*i]))
				mathPtList.Append(resultPointList[2*i-1]);
			else
				mathPtList.Append(resultPointList[2*i]);

			spSpecListPart.Append(_spSpecListPart[i]);
		}
	}

	_curvatureRList.RemoveAll();
	this->GetNearestPtsAll(oMidSWPt, mathPtList, spSpecListPart, oMathPt1, oMathPt2, oMathPt3, oMathPt4,
		_centerMathPtG, _curvatureRList);

	//删除列表
	resultMidPointList.RemoveAll();
	resultPointList.RemoveAll();
	mathPtList.RemoveAll();
	spSpecListPart.RemoveAll();

	return rc;
}

//自焊件
HRESULT TestCreateSWPointCmd::GetSelfWeldSWPoint4T(CATMathPoint & oMidSWPt, 
													CATMathPoint & oMathPt1, 
													CATMathPoint & oMathPt2, 
													CATMathPoint & oMathPt3, 
													CATMathPoint & oMathPt4)
{
	HRESULT rc=S_OK;

	CATMathTransformation pTransToLocal;
	CATMathTransformation pTransToGlobal;

	//1、获得临时点的坐标（Global）
	CATMathPoint mathPtOnSurfaceG;
	rc = _spTempPoint->GetPosition(&mathPtOnSurfaceG);
	if(FAILED(rc))
	{
		return E_FAIL;
	}

	//2、坐标变换，将临时点坐标转换到BaseSurface所在的Part的Local坐标
	//获得全局向局部转换的坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, _spSurfacePrd);
	//计算Local点坐标
	CATMathPoint mathPtOnSurfaceL = pTransToLocal*mathPtOnSurfaceG;

	//3、获得临时点处Base曲面的法线方向	
	//获得临时点在所选曲面处的法线方向，local
	CATMathVector normalVector;
	double oDis;
	_pSJDGeneralClass->SJDGetMinDistanceBetweenPointAndFace(_spFace, mathPtOnSurfaceL, oDis, normalVector);
	//将该方向转为Global
	pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(_spSurfacePrd, _spRootPrd);
	CATMathVector oNormalVG = pTransToGlobal*normalVector;

	//4、判断零件重复次数
	CATBoolean bExist;
	CATBaseUnknown_var spBase1;
	CATBaseUnknown_var spBase2;
	CATListValCATISpecObject_var spSpecListPart;
	CATListOfInt listPartNum;
	spSpecListPart.Append(_spSpecListPart[1]);
	for(int i=2; i<=_spSpecListPart.Size(); i++)
	{
		bExist = FALSE;
		for(int j=1; j<=spSpecListPart.Size(); j++)
		{
			spBase1 = _spSpecListPart[i];
			spBase2 = spSpecListPart[j];
			if(spBase1->IsEqual(spBase2))
			{
				bExist = TRUE;
				break;
			}
		}
		if(bExist == FALSE)
			spSpecListPart.Append(_spSpecListPart[i]);
	}
	int num;
	for(int i=1; i<=spSpecListPart.Size(); i++)
	{
		spBase1 = spSpecListPart[i];
		num = 0;

		for(int j=1; j<=_spSpecListPart.Size(); j++)
		{

			spBase2 = _spSpecListPart[j];
			if(spBase1->IsEqual(spBase2))
			{
				num++;
			}
		}
		listPartNum.Append(num);
	}

	//4、法线方向和每个连接件PartBody相交，得到交点列表（每个件取离临时点较近的两个点）
	CATIProduct_var spConnectionPrd = NULL_var;
	CATMathPoint mathPointL;//所选的点转到connection局部
	CATMathVector mathNormalVectorL;//所选点处的Normal方向转到Connection局部
	CATLISTV(CATMathPoint) resultPointList;
	CATLISTV(CATMathPoint) resultMidPointList;
	CATLISTV(CATMathPoint) ConnectionsPointList;
	CATListValCATISpecObject_var ConnectionsList;//零件列表
	for(int i=1; i<=spSpecListPart.Size(); i++)
	{
		//connection prd
		spConnectionPrd = spSpecListPart[i];
		num = listPartNum[i];

		//全局转为connection坐标变换
		pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, spConnectionPrd);
		pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(spConnectionPrd, _spRootPrd);

		//局部
		mathPointL = pTransToLocal * mathPtOnSurfaceG;
		mathNormalVectorL = pTransToLocal * oNormalVG;

		//获得由在该点和方向线组成的直线和该连接件PartBody的交点列表（取最近的两个点）
		rc = this->GetInsertPointInPartWithNum(2*num, spConnectionPrd, mathPointL, mathNormalVectorL, ConnectionsPointList);
		if(FAILED(rc) || ConnectionsPointList.Size()!=2*num)
		{
			return E_FAIL;
		}

		//将所获得的两点取中点，转为全局，保存
		//对点排序
		_pSJDSpotWeldCheck->SortMathPtWithDistance(mathPointL, ConnectionsPointList);

		//计算中点
		CATMathPoint mathPtMid;
		CATMathPoint mathPtG1;
		CATMathPoint mathPtG2;
		for(int i=1; i<=num; i=i++)
		{
			mathPtMid = 0.5*(ConnectionsPointList[2*i-1] + ConnectionsPointList[2*i]);
			mathPtMid = pTransToGlobal*mathPtMid;
			mathPtG1 = pTransToGlobal*ConnectionsPointList[2*i-1];
			mathPtG2 = pTransToGlobal*ConnectionsPointList[2*i];
			resultMidPointList.Append(mathPtMid);		
			resultPointList.Append(mathPtG1);
			resultPointList.Append(mathPtG2);
			ConnectionsList.Append(spConnectionPrd);
		}

		ConnectionsPointList.RemoveAll();
	}
	spSpecListPart.RemoveAll();
	listPartNum.RemoveAll();

	//4、计算所选点到四个件的中点的向量和曲面法向向量点乘
	CATMathVector vecTemp;
	CATListOfDouble listDis;
	for(int i=1; i<=4; i++)
	{
		vecTemp = resultMidPointList[i] - mathPtOnSurfaceG;
		oDis = vecTemp * oNormalVG;
		listDis.Append(oDis);
	}

	//5、取中间两个Part的编号
	CATListOfDouble listDisTemp = listDis;
	listDisTemp.QuickSort();	
	int iFlagPart1;//第二个件的两点在resultCnctPointList中的列表序号为iFlagPart1*2-1, iFlagPart1*2
	int iFlagPart2;//第三个件的两点在resultCnctPointList中的列表序号为iFlagPart2*2-1, iFlagPart2*2
	for(int i=1; i<=4; i++)
	{
		//找到第二个点
		if(listDisTemp[2] == listDis[i])
		{
			iFlagPart1 = i;
		}

		//找到第三个点
		if(listDisTemp[3] == listDis[i])
		{
			iFlagPart2 = i;
		}
	}
	listDisTemp.RemoveAll();
	listDis.RemoveAll();

	//6、获得中间两个件四个点中距离较近的两个点
	int iFlagPt1;
	int iFlagPt2;
	double minDis = 1000;
	double dis1, dis2;
	for(int i=iFlagPart1*2-1; i<=iFlagPart1*2; i++)
	{
		dis1 = resultPointList[i].DistanceTo(resultPointList[iFlagPart2*2-1]);
		if(dis1<minDis)
		{
			minDis = dis1;
			iFlagPt1 = i;
			iFlagPt2 = iFlagPart2*2-1;
		}
		dis2 = resultPointList[i].DistanceTo(resultPointList[iFlagPart2*2]);
		if(dis2<minDis)
		{
			minDis = dis2;
			iFlagPt1 = i;
			iFlagPt2 = iFlagPart2*2;
		}
	}

	//取中点
	CATMathPoint mathPtMid = 0.5*(resultPointList[iFlagPt1] + resultPointList[iFlagPt2]);
	////全局到焊点文件下的坐标变换
	//pTransToLocal = _pGeneralClass->GetMatrixTransformation(_spRootPrd, _spWeldPrd);
	//mathPtMid = pTransToLocal * mathPtMid;

	//6、中点输出
	oMidSWPt = mathPtMid;

	//7、获得贴合面上的六个点数据
	//获得resultPointList中最近和最远的两个点，排除，其他点都要计算
	for(int i=1; i<=resultPointList.Size(); i++)
	{
		vecTemp = resultPointList[i] - mathPtOnSurfaceG;
		oDis = vecTemp * oNormalVG;
		listDis.Append(oDis);
	}
	listDisTemp = listDis;
	listDisTemp.QuickSort();
	//找到最小和最大的点
	for(int i=1; i<=resultPointList.Size(); i++)
	{
		//找到最近的点
		if(listDisTemp[1] == listDis[i])
		{
			iFlagPart1 = i;
		}

		//找到最远的点
		if(listDisTemp[resultPointList.Size()] == listDis[i])
		{
			iFlagPart2 = i;
		}
	}

	CATLISTV(CATMathPoint) mathPtList;
	CATListOfInt listNum;
	int iNum1;
	int iNum2;
	for(int i=1; i<=4; i++)
	{
		iNum1 = 2*i - 1;		
		if(iNum1!=iFlagPart1 && iNum1!=iFlagPart2)
		{
			mathPtList.Append(resultPointList[iNum1]);
			spSpecListPart.Append(_spSpecListPart[i]);
			listNum.Append(1);
		}

		iNum2 = 2*i;
		if(iNum2!=iFlagPart1 && iNum2!=iFlagPart2)
		{
			mathPtList.Append(resultPointList[iNum2]);
			spSpecListPart.Append(_spSpecListPart[i]);
			listNum.Append(1);
		}
	}

	//获得距离为0的两个点
	int iFlag1;
	int iFlag2;
	CATBoolean bFind = FALSE;
	for(int i=1; i<=mathPtList.Size()-1; i++)
	{
		for(int j=i+1; j<=mathPtList.Size(); j++)
		{
			if(mathPtList[i].DistanceTo(mathPtList[j]) == 0)
			{
				if(spSpecListPart[i]->IsEqual(spSpecListPart[j]))
				{
					iFlag1 = i;
					iFlag2 = j;
					bFind = TRUE;
					break;
				}				
			}
		}
		if(bFind == TRUE)
			break;
	}
	listNum[iFlag1] = 2;

	CATLISTV(CATMathPoint) mathPtListNew;
	CATListOfInt listNumNew;
	CATListValCATISpecObject_var spSpecListPartNew;
	if(bFind == TRUE)
	{
		for(int i=1; i<=mathPtList.Size(); i++)
		{
			if(i==iFlag2) 
				continue;

			mathPtListNew.Append(mathPtList[i]);
			listNumNew.Append(listNum[i]);
			spSpecListPartNew.Append(spSpecListPart[i]);
		}
	}
	else
	{
		for(int i=1; i<=mathPtList.Size(); i++)
		{
			mathPtListNew.Append(mathPtList[i]);
			listNumNew.Append(listNum[i]);
			spSpecListPartNew.Append(spSpecListPart[i]);
		}
	}
	mathPtList.RemoveAll();
	listNum.RemoveAll();
	spSpecListPart.RemoveAll();

	_curvatureRList.RemoveAll();
	//this->GetNearestPtsAll(oMidSWPt, mathPtList, spSpecListPart, oMathPt1, oMathPt2, oMathPt3, oMathPt4, _centerMathPtG, _curvatureRList);
	this->GetSelfWeldNearestPtsAll(oMidSWPt, mathPtListNew, listNumNew, spSpecListPartNew, oMathPt1, oMathPt2, oMathPt3, oMathPt4, _centerMathPtG, _curvatureRList);

	//删除列表
	resultPointList.RemoveAll();
	resultMidPointList.RemoveAll();
	ConnectionsList.RemoveAll();


	mathPtListNew.RemoveAll();
	listNumNew.RemoveAll();
	spSpecListPartNew.RemoveAll();

	return rc;
}

//获得所选择的点在所选择的曲面处的法线方向
HRESULT TestCreateSWPointCmd::GetNormalDirOnSurface(CATISpecObject_var ispSpecSurface,
													 CATMathPoint iMathPt,
													 double & oDis,
													 CATMathVector & oNormalMathVector)
{
	//获得BaseSurface的Body
	CATBody_var spSurfaceBody = NULL_var;
	_pSJDGeneralClass->SJDGetBodyFromSpecObject(ispSpecSurface, spSurfaceBody);

	//获得BaseSurface离临时特征点最近的点，并获得该点处的法线方向
	CATLISTP(CATCell) listCell;
	spSurfaceBody->GetAllCells(listCell,2);

	CATFace_var spFace=NULL_var;
	double dis;
	double oMinDis;
	CATMathVector oNormalVector;
	oMinDis = 1000.;
	for(int i=1; i<=listCell.Size(); i++)
	{
		spFace = listCell[i];

		_pSJDGeneralClass->SJDGetMinDistanceBetweenPointAndFace(spFace, iMathPt, dis, oNormalVector);

		//获得local点到face的距离
		if(dis<oMinDis)
		{
			oMinDis = dis;
			oNormalMathVector = oNormalVector;
		}
	}

	oDis = oMinDis;
	return S_OK;
}
HRESULT TestCreateSWPointCmd::GetInsertPointInPartWithNum(int iIntersectNum,//所取得的交点个数
														   CATIProduct_var ispInstPrd, 
														   CATMathPoint imathPt, 
														   CATMathVector iMathVector, 
														   CATLISTV(CATMathPoint) & oMathPtList)
{
	HRESULT rc = S_OK;

	CATUnicodeString strError;

	//获得connections的PartBody	
	CATBody_var spConnectionPartBody = NULL_var;
	//_pGeneralClass->SJDGetMainBodyInProduct(ispInstPrd, spConnectionPartBody);

	CATUnicodeString strsinglebody;
	CATBoolean ismetal=_pSJDSpotWeldCheck->IsSHEET_METAL(ispInstPrd,strsinglebody);
	if (ismetal==TRUE&&strsinglebody=="MultiBody")
	{
		//钣金件，且多实体的，取离选择点最近的实体
		_pSJDSpotWeldCheck->SJDGetSHEETMETALBodyInProduct(ispInstPrd,imathPt,spConnectionPartBody);
	}
	else
	{
		_pSJDSpotWeldCheck->SJDGetMainBodyInProduct(ispInstPrd, spConnectionPartBody);
	}

	if(spConnectionPartBody == NULL_var)
	{
		cout<<"GetInsertPointInPart: spConnectionPartBody == NULL"<<endl;

		CATUnicodeString strInstanceName;
		ispInstPrd->GetPrdInstanceName(strInstanceName);

		//strError = "零件“" + strInstanceName +"”零件几何体（PartBody）无实体，请检查模型！";
		strError = "Part“" + strInstanceName +"”has no solid body，pls check";

		_pSJDGeneralClass->CreatMsgBoxOptError(strError);

		return E_FAIL;
	}

	//根据方向线构建直线
	CATMathPoint mathPtStart = imathPt - 100*iMathVector;
	CATMathPoint mathPtEnd = imathPt + 100*iMathVector;

	//创建拓扑直线
	CATGeoFactory * piGeomFactory = spConnectionPartBody->GetContainer();

	CATBody * pStartPtBody = ::CATCreateTopPointXYZ(piGeomFactory,_topdata,mathPtStart.GetX(), mathPtStart.GetY(), mathPtStart.GetZ());
	CATBody * pEndPtBody = ::CATCreateTopPointXYZ(piGeomFactory,_topdata,mathPtEnd.GetX(), mathPtEnd.GetY(), mathPtEnd.GetZ());

	CATBody * pLineBody = ::CATCreateTopLineFromPoints(piGeomFactory, _topdata,pStartPtBody, pEndPtBody); 

	//创建相交
	CATHybIntersect * pIntersect = ::CATCreateTopIntersect( piGeomFactory,_topdata, spConnectionPartBody, pLineBody);

	CATLISTV(CATMathPoint) mathPtListTemp;
	if ( NULL != pIntersect )
	{
		//得到相交结果
		pIntersect->Run();

		CATUnicodeString strInstanceName;
		ispInstPrd->GetPrdInstanceName(strInstanceName);

		CATBody * pResultBody = pIntersect->GetResult ();	
		if(pResultBody == NULL)
		{
			cout<<"GetInsertPointInPart: pResultBody == NULL"<<endl;

			//strError = "在所选点的法线方向上与“" + strInstanceName +"”无交点，不合格！";
			strError = "The normal direction of select point“" + strInstanceName +"” has no intersection";

			_pSJDGeneralClass->CreatMsgBoxOptError(strError);

			return E_FAIL;
		}

		CATLISTP(CATCell) listCell;
		pResultBody->GetAllCells(listCell, 0);

		//不进行交点个数的判断
		//在所选点的normal方向上的点个数
		if(iIntersectNum>3)
			iIntersectNum = 3;

		if(listCell.Size() < iIntersectNum)
		{		
			strError.BuildFromNum(iIntersectNum, "%d");

			//strError = "在所选点的法线方向上与“" + strInstanceName +"”的交点小于" + strError + "个，不合格！";
			
			strError = "The normal direction of select point“" + strInstanceName +"”intersection number less than" + strError ;

			_pSJDGeneralClass->CreatMsgBoxOptError(strError);
			
			delete pIntersect;
			pIntersect = NULL;
			
			piGeomFactory->Remove(pStartPtBody);
			piGeomFactory->Remove(pEndPtBody);
			piGeomFactory->Remove(pLineBody);
			return E_FAIL;
		}
		delete pIntersect;
		pIntersect = NULL;

		//获得相交点的点坐标, 保存
		CATVertex_var spVertex = NULL_var;
		CATPoint_var spPoint = NULL_var;
		for(int i=1; i<=listCell.Size(); i++)
		{
			spVertex = listCell[i];
			spPoint = spVertex->GetPoint();
			CATMathPoint mathPt;
			spPoint->GetMathPoint(mathPt);

			mathPtListTemp.Append(mathPt);
		}

		//多于两点需要筛选，取离所选择的点最近的两个点
		if(mathPtListTemp.Size() > 2)
		{
			rc = _pSJDSpotWeldCheck->SortMathPtWithDistance(imathPt, mathPtListTemp);
		}
	}

	if(mathPtListTemp.Size() == 3)
	{
		oMathPtList.Append(mathPtListTemp[1]);
		oMathPtList.Append(mathPtListTemp[2]);
		oMathPtList.Append(mathPtListTemp[2]);
		oMathPtList.Append(mathPtListTemp[3]);
	}
	else
	{
		//只保留最小的四个
		for(int i=1; i<=iIntersectNum; i++)
			oMathPtList.Append(mathPtListTemp[i]);
	}
	CATMathPoint mathPtTemp;
	for(int i=1; i<=oMathPtList.Size(); i++)
	{
		mathPtTemp = oMathPtList[i];
		cout<<"Point"<<i<<", "<< mathPtTemp.GetX() << ", " <<mathPtTemp.GetY() << "," << mathPtTemp.GetZ() <<endl;

	}
	//Remove or Release		
	mathPtListTemp.RemoveAll();
	piGeomFactory->Remove(pStartPtBody);
	piGeomFactory->Remove(pEndPtBody);
	piGeomFactory->Remove(pLineBody);

	return rc;
}

////对点坐标根据距离远近排序（从近到远）
//HRESULT TestCreateSWPointCmd::SortMathPtWithDistance(CATMathPoint iMathPt, CATLISTV(CATMathPoint) &ioMathPtList)
//													  
//{
//	HRESULT rc = S_OK;
//
//	if(ioMathPtList.Size()>=2)
//	{
//		//计算点之间的距离
//		double dis;
//		CATListOfDouble disList;
//		for(int i=1; i<=ioMathPtList.Size(); i++)
//		{
//			dis = iMathPt.DistanceTo(ioMathPtList[i]);
//			disList.Append(dis);
//		}
//
//		//排序
//		disList.QuickSort();
//
//		//
//		CATLISTV(CATMathPoint) mathPtListTemp = ioMathPtList;
//		ioMathPtList.RemoveAll();
//		for(int i=1; i<=disList.Size(); i++)
//		{
//			for(int j=1; j<=mathPtListTemp.Size(); j++)
//			{
//				dis = iMathPt.DistanceTo(mathPtListTemp[j]);
//
//				if(dis == disList[i])
//				{
//					ioMathPtList.Append(mathPtListTemp[j]);
//					break;
//				}
//			}
//		}
//		mathPtListTemp.RemoveAll();
//	}
//
//	return rc;
//}

HRESULT TestCreateSWPointCmd::GetNearestPtsAll(CATMathPoint iSWMathPtG,
												CATLISTV(CATMathPoint) iMathPtList,//需要计算的点，点为和零件的交点（全局坐标）
												CATListValCATISpecObject_var ispSpecListPart,//该点所对应的part
												CATMathPoint & oMathPt1,
												CATMathPoint & oMathPt2,
												CATMathPoint & oMathPt3,
												CATMathPoint & oMathPt4,
												CATMathPoint & oMidMathPt,
												CATListOfDouble & listCurvature)
{
	HRESULT rc = S_OK;

	CATMathPoint mathPt;
	CATIProduct_var spInstPrd = NULL_var;
	CATMathPoint mathPtOnEdgeG;//离焊点最近的边上的点
	CATMathVector normalVecG;
	double curvatureRadius;//曲率半径
	double minDisAll = 9999.;
	double minDis;

	CATMathPoint oMathPointOnFaceL;//Face上焊点坐标（Local）
	CATMathPoint oNearestMathPtG;//最近边上的最近点（Global）
	CATMathVector oNormalVecG;//第一个零件最近面上焊点投影点处normal方向
	CATLISTP(CATFace) listFace;
	CATLISTV(CATMathPoint) listPtOnFace;

	for(int i=1; i<=iMathPtList.Size(); i++)
	{
		//需要计算的点
		mathPt = iMathPtList[i];
		//需要计算的点所在的product
		spInstPrd = ispSpecListPart[i];

		//计算
		CATFace_var ospFace = NULL_var;//焊点在该part下最近的Face
		this->GetNearestPts(spInstPrd, mathPt, ospFace, oMathPointOnFaceL, normalVecG, curvatureRadius, mathPtOnEdgeG, minDis);
		if(i==1)
			oNormalVecG = normalVecG;

		//记录曲率半径
		listCurvature.Append(curvatureRadius);

		//记录Face，为下一步计算十字边做准备
		//记录Face上的点，为下一步计算十字边做准备

		listFace.Append(ospFace);
		listPtOnFace.Append(oMathPointOnFaceL);	

		//输出离点最近的边的相关结果
		if(minDis<minDisAll)
		{
			minDisAll = minDis;

			//记录最近边上的点，为下一步计算十字边做准备
			oNearestMathPtG = mathPtOnEdgeG;
		}
	}

	//通过最近边的点，来计算贴合面上的四个边，从而获得所有的最近的点
	CATMathPoint mathPt1, mathPt2, mathPt3, mathPt4;
	CATFace_var spFace = NULL_var;
	CATMathPoint mathPtOnFaceL;
	////第一个plane的垂直方向
	//
	//CATMathVector vec1 = oNearestMathPtG - iMathPtList[1];
	//CATMathVector vecToPlane1 = vec1^normalVecG;
	double dis1, dis2, dis3, dis4, disTemp;
	CATMathVector vec1, vec2, vec3, vec4, vecTemp;
	for(int i=1; i<=listFace.Size(); i++)
	{
		//需要计算的点所在的product
		spInstPrd = ispSpecListPart[i];
		//face
		spFace = listFace[i];
		//point
		mathPtOnFaceL = listPtOnFace[i];

		this->GetCrossLinePts(spInstPrd, spFace, mathPtOnFaceL, oNormalVecG, oNearestMathPtG, mathPt1, mathPt2, mathPt3, mathPt4);
		cout<<"mathPt1: "<<mathPt1.GetX()<<", "<<mathPt1.GetY()<<", "<<mathPt1.GetZ()<<endl;
		cout<<"mathPt2: "<<mathPt2.GetX()<<", "<<mathPt2.GetY()<<", "<<mathPt2.GetZ()<<endl;
		cout<<"mathPt3: "<<mathPt3.GetX()<<", "<<mathPt3.GetY()<<", "<<mathPt3.GetZ()<<endl;
		cout<<"mathPt4: "<<mathPt4.GetX()<<", "<<mathPt4.GetY()<<", "<<mathPt4.GetZ()<<endl;
		cout<<endl;
		if(i==1)
		{
			oMathPt1 = mathPt1;//第一个平面
			oMathPt2 = mathPt2;//第一个平面
			oMathPt3 = mathPt3;//第二个平面
			oMathPt4 = mathPt4;//第二个平面
		}
		else
		{
			vec1 = oMathPt1 - iSWMathPtG;
			vec2 = oMathPt2 - iSWMathPtG;
			vec3 = oMathPt3 - iSWMathPtG;
			vec4 = oMathPt4 - iSWMathPtG;
			dis1 = oMathPt1.DistanceTo(iSWMathPtG);
			dis2 = oMathPt2.DistanceTo(iSWMathPtG);
			dis3 = oMathPt3.DistanceTo(iSWMathPtG);
			dis4 = oMathPt4.DistanceTo(iSWMathPtG);

			vecTemp = mathPt1 - iSWMathPtG;
			disTemp = mathPt1.DistanceTo(iSWMathPtG);
			if(vec1*vecTemp > 0)
			{
				if(dis1 > disTemp)
					oMathPt1 = mathPt1;

				disTemp = mathPt2.DistanceTo(iSWMathPtG);
				if(dis2 > disTemp)
					oMathPt2 = mathPt2;
			}
			else
			{
				if(dis2 > disTemp)
					oMathPt2 = mathPt1;

				disTemp = mathPt2.DistanceTo(iSWMathPtG);
				if(dis1 > disTemp)
					oMathPt1 = mathPt2;
			}

			vecTemp = mathPt3 - iSWMathPtG;
			disTemp = mathPt3.DistanceTo(iSWMathPtG);
			if(vec3*vecTemp > 0)
			{
				if(dis3 > disTemp)
					oMathPt3 = mathPt3;

				disTemp = mathPt4.DistanceTo(iSWMathPtG);
				if(dis4 > disTemp)
					oMathPt4 = mathPt4;
			}
			else
			{
				if(dis4 > disTemp)
					oMathPt4 = mathPt3;

				disTemp = mathPt4.DistanceTo(iSWMathPtG);
				if(dis3 > disTemp)
					oMathPt3 = mathPt4;
			}
		}
	}

	if(oMathPt1.DistanceTo(oMathPt2) < oMathPt3.DistanceTo(oMathPt4))
	{
		oMidMathPt = 0.5*(oMathPt1 + oMathPt2);
	}
	else
	{
		oMidMathPt = 0.5*(oMathPt3 + oMathPt4);
	}

	return rc;
}

//获得焊点离贴合面最近的点及其他三个点坐标
HRESULT TestCreateSWPointCmd::GetSelfWeldNearestPtsAll(CATMathPoint iSWMathPtG,
														CATLISTV(CATMathPoint) iMathPtList,//需要计算的点
														CATListOfInt iNumList,//需要计算的点所对应的面的个数
														CATListValCATISpecObject_var ispSpecListPart,//该点所对应的part
														CATMathPoint & oMathPt1G,//十字线点（离点最近的点所在边）
														CATMathPoint & oMathPt2G,//十字线点（离点最近的点所在边）
														CATMathPoint & oMathPt3G,//十字线点（垂直的另一条边）
														CATMathPoint & oMathPt4G,//十字线点（垂直的另一条边）
														CATMathPoint & oMidMathPtG,//十字线短边中点
														CATListOfDouble & listCurvature)//曲率半径列表
{
	HRESULT rc = S_OK;

	CATMathPoint mathPt;
	CATIProduct_var spInstPrd = NULL_var;
	CATMathPoint mathPtOnEdgeG;//离焊点最近的边上的点
	CATMathVector normalVecG;

	double minDisAll = 9999.;
	double minDis;


	CATMathPoint oNearestMathPtG;//最近边上的最近点（Global）
	CATMathVector oNormalVecG;//第一个零件最近面上焊点投影点处normal方向
	CATLISTP(CATFace) listFace;
	CATLISTV(CATMathPoint) listPtOnFace;
	CATListValCATISpecObject_var listPrt;

	for(int i=1; i<=iMathPtList.Size(); i++)
	{
		//需要计算的点
		mathPt = iMathPtList[i];
		//需要计算的点所在的product
		spInstPrd = ispSpecListPart[i];

		//计算

		if(iNumList[i] == 1)
		{
			CATFace_var ospFace = NULL_var;//焊点在该part下最近的Face
			CATMathPoint oMathPointOnFaceL;//Face上焊点坐标（Local）
			double curvatureRadius;//曲率半径
			this->GetNearestPts(spInstPrd, mathPt, ospFace, oMathPointOnFaceL, normalVecG, curvatureRadius, mathPtOnEdgeG, minDis);

			//记录曲率半径
			listCurvature.Append(curvatureRadius);

			//记录Face，为下一步计算十字边做准备
			//记录Face上的点，为下一步计算十字边做准备
			listFace.Append(ospFace);
			listPtOnFace.Append(oMathPointOnFaceL);	
			listPrt.Append(spInstPrd);
		}
		else
		{
			CATFace_var ospFace1 = NULL_var;//焊点在该part下最近的Face
			CATFace_var ospFace2 = NULL_var;//焊点在该part下最近的Face
			CATMathPoint oMathPointOnFaceL1;//Face上焊点坐标（Local）
			CATMathPoint oMathPointOnFaceL2;//Face上焊点坐标（Local）
			double curvatureRadius1;//曲率半径
			double curvatureRadius2;//曲率半径
			this->GetSelfWeldNearestPts(spInstPrd, mathPt, ospFace1, ospFace2, oMathPointOnFaceL1, oMathPointOnFaceL2, normalVecG, curvatureRadius1, curvatureRadius2, mathPtOnEdgeG, minDis);

			//记录Face，为下一步计算十字边做准备
			//记录Face上的点，为下一步计算十字边做准备
			listFace.Append(ospFace1);
			listPtOnFace.Append(oMathPointOnFaceL1);	
			listPrt.Append(spInstPrd);

			listFace.Append(ospFace2);
			listPtOnFace.Append(oMathPointOnFaceL2);
			listPrt.Append(spInstPrd);
		}
		if(i==1)
			oNormalVecG = normalVecG;		

		//输出离点最近的边的相关结果
		if(minDis<minDisAll)
		{
			minDisAll = minDis;

			//记录最近边上的点，为下一步计算十字边做准备
			oNearestMathPtG = mathPtOnEdgeG;
		}
	}

	//通过最近边的点，来计算贴合面上的四个边，从而获得所有的最近的点
	CATMathPoint mathPt1, mathPt2, mathPt3, mathPt4;
	CATFace_var spFace = NULL_var;
	CATMathPoint mathPtOnFaceL;
	////第一个plane的垂直方向
	//
	//CATMathVector vec1 = oNearestMathPtG - iMathPtList[1];
	//CATMathVector vecToPlane1 = vec1^normalVecG;
	double dis1, dis2, dis3, dis4, disTemp;
	CATMathVector vec1, vec2, vec3, vec4, vecTemp;
	for(int i=1; i<=listFace.Size(); i++)
	{
		//需要计算的点所在的product
		spInstPrd = listPrt[i];
		//face
		spFace = listFace[i];
		//point
		mathPtOnFaceL = listPtOnFace[i];

		this->GetCrossLinePts(spInstPrd, spFace, mathPtOnFaceL, oNormalVecG, oNearestMathPtG, mathPt1, mathPt2, mathPt3, mathPt4);
		cout<<"mathPt1: "<<mathPt1.GetX()<<", "<<mathPt1.GetY()<<", "<<mathPt1.GetZ()<<endl;
		cout<<"mathPt2: "<<mathPt2.GetX()<<", "<<mathPt2.GetY()<<", "<<mathPt2.GetZ()<<endl;
		cout<<"mathPt3: "<<mathPt3.GetX()<<", "<<mathPt3.GetY()<<", "<<mathPt3.GetZ()<<endl;
		cout<<"mathPt4: "<<mathPt4.GetX()<<", "<<mathPt4.GetY()<<", "<<mathPt4.GetZ()<<endl;
		cout<<endl;
		if(i==1)
		{
			oMathPt1G = mathPt1;//第一个平面
			oMathPt2G = mathPt2;//第一个平面
			oMathPt3G = mathPt3;//第二个平面
			oMathPt4G = mathPt4;//第二个平面
		}
		else
		{
			vec1 = oMathPt1G - iSWMathPtG;
			vec2 = oMathPt2G - iSWMathPtG;
			vec3 = oMathPt3G - iSWMathPtG;
			vec4 = oMathPt4G - iSWMathPtG;
			dis1 = oMathPt1G.DistanceTo(iSWMathPtG);
			dis2 = oMathPt2G.DistanceTo(iSWMathPtG);
			dis3 = oMathPt3G.DistanceTo(iSWMathPtG);
			dis4 = oMathPt4G.DistanceTo(iSWMathPtG);

			vecTemp = mathPt1 - iSWMathPtG;
			disTemp = mathPt1.DistanceTo(iSWMathPtG);
			if(vec1*vecTemp > 0)
			{
				if(dis1 > disTemp)
					oMathPt1G = mathPt1;

				disTemp = mathPt2.DistanceTo(iSWMathPtG);
				if(dis2 > disTemp)
					oMathPt2G = mathPt2;
			}
			else
			{
				if(dis2 > disTemp)
					oMathPt2G = mathPt1;

				disTemp = mathPt2.DistanceTo(iSWMathPtG);
				if(dis1 > disTemp)
					oMathPt1G = mathPt2;
			}

			vecTemp = mathPt3 - iSWMathPtG;
			disTemp = mathPt3.DistanceTo(iSWMathPtG);
			if(vec3*vecTemp > 0)
			{
				if(dis3 > disTemp)
					oMathPt3G = mathPt3;

				disTemp = mathPt4.DistanceTo(iSWMathPtG);
				if(dis4 > disTemp)
					oMathPt4G = mathPt4;
			}
			else
			{
				if(dis4 > disTemp)
					oMathPt4G = mathPt3;

				disTemp = mathPt4.DistanceTo(iSWMathPtG);
				if(dis3 > disTemp)
					oMathPt3G = mathPt4;
			}
		}
	}

	if(oMathPt1G.DistanceTo(oMathPt2G) < oMathPt3G.DistanceTo(oMathPt4G))
	{
		oMidMathPtG = 0.5*(oMathPt1G + oMathPt2G);
	}
	else
	{
		oMidMathPtG = 0.5*(oMathPt3G + oMathPt4G);
	}

	listFace.RemoveAll();
	listPtOnFace.RemoveAll();
	listPrt.RemoveAll();

	return rc;
}

//获得焊点到连接件贴合面的最近面、最近面上的投影点、投影点到贴合面最近边上的点，最小距离等
HRESULT TestCreateSWPointCmd::GetNearestPts(CATIProduct_var ispInstPrd,
											 CATMathPoint imathPtG, 
											 CATFace_var & ospNearestFace,//焊点在该product下的body上最近的face											 
											 CATMathPoint & oMathPointOnFaceL,//焊点在最近face上的投影点
											 CATMathVector & oNormalVectorG,//焊点在最近face上投影点处的normal方向
											 double & oCurvatureRadius,//投影点处的曲率半径
											 CATMathPoint & oNearestMathPtG,//离投影点最近的边上的点，该点实现最小距离
											 double & oMinDisBtEdgeAndPt)//离投影点最近的边的最小距离
{
	HRESULT rc = S_OK;

	CATMathTransformation pTransToLocal;
	CATMathTransformation pTransToGlobal;

	//全局转为局部坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, ispInstPrd);
	pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(ispInstPrd, _spRootPrd);

	//将全局点转为local
	CATMathPoint mathPt = pTransToLocal * imathPtG;

	////获得connections的PartBody	
	CATBody_var spConnectionPartBody = NULL_var;
	//_pGeneralClass->SJDGetMainBodyInProduct(ispInstPrd, spConnectionPartBody);

	//获得connections的PartBody	
	CATUnicodeString strsinglebody;
	CATBoolean ismetal=_pSJDSpotWeldCheck->IsSHEET_METAL(ispInstPrd,strsinglebody);
	if (ismetal==TRUE&&strsinglebody=="MultiBody")
	{
		//钣金件，且多实体的，取离选择点最近的实体
		_pSJDSpotWeldCheck->SJDGetSHEETMETALBodyInProduct(ispInstPrd,mathPt,spConnectionPartBody);
	}
	else
	{
		_pSJDSpotWeldCheck->SJDGetMainBodyInProduct(ispInstPrd, spConnectionPartBody);
	}

	if(spConnectionPartBody == NULL_var)
	{
		cout<<"GetInsertPointInPart: spConnectionPartBody == NULL"<<endl;

		CATUnicodeString strInstanceName;
		ispInstPrd->GetPrdInstanceName(strInstanceName);

		//CATUnicodeString strError = "零件“" + strInstanceName +"”零件几何体（PartBody）无实体，请检查模型！";
		CATUnicodeString strError = "Part“" + strInstanceName +"”has no solid body,pls check";
		_pSJDGeneralClass->CreatMsgBoxOptError(strError);
		return E_FAIL;
	}

	CATGeoFactory * ipiGeomFactory = spConnectionPartBody->GetFactory();

	//查找贴合面
	CATLISTP(CATCell) faceCell;
	spConnectionPartBody->GetAllCells(faceCell,2);
	double minDis = 9999.;
	double oDistance = 0.;
	CATMathVector TempVector;
	CATMathPoint TempPoint;
	CATMathPoint mathPtOnFace;
	CATMathVector normalVOnFace;
	for (int i = 1; i<=faceCell.Size();i++)
	{
		CATFace * pFace = (CATFace *)faceCell[i];

		this->GetMinDistanceBetweenPointAndFace(pFace,mathPt,oDistance,TempVector, TempPoint);
		if (minDis> oDistance)
		{
			minDis = oDistance;
			ospNearestFace = pFace;
			mathPtOnFace = TempPoint;
			normalVOnFace = TempVector;
		}
	}	
	//贴合面上的点
	oMathPointOnFaceL = mathPtOnFace;
	oNormalVectorG = pTransToGlobal * normalVOnFace;

	//计算face在点处的曲率半径
	CATSurface * pSurface = ospNearestFace->GetSurface();
	double curvature;
	rc = this->GetCurvetureOfPointOnFace(ipiGeomFactory, _pConfig, oMathPointOnFaceL, pSurface, curvature);
	cout<<"curvature: "<<curvature<<endl;
	oCurvatureRadius = 1.0/curvature;

	//查找face上离mathPtOnFace最近的边
	CATMathPoint nearestMathPt;
	CATLISTP(CATCell) edgeCells;
	ospNearestFace->GetAllCells(edgeCells, 1);
	CATCrvParam CrvParStart;
	CATCrvParam CrvParEnd;
	oMinDisBtEdgeAndPt = 9999.;
	CATMathPoint mathPtMin1;
	for(int i=1; i<=edgeCells.Size(); i++)
	{
		CATEdge * pEdge = (CATEdge *)edgeCells[i];

		CATCurve * pCircleCurve = pEdge->GetCurve();
		pEdge->GetVerticesParamsOnEdgeCurve(&CrvParStart, &CrvParEnd);
		CATCrvLimits crvLimits(CrvParStart,CrvParEnd);
		pCircleCurve->SetLimits(crvLimits);

		rc = GetMinDistanceBetweenPointAndEdge(pCircleCurve, mathPtOnFace, oDistance, mathPtMin1);

		if (oDistance<oMinDisBtEdgeAndPt)
		{
			oMinDisBtEdgeAndPt = oDistance;
			nearestMathPt = mathPtMin1;
		}
	}
	cout<<"nearestMathPt: "<<nearestMathPt.GetX()<<", "<<nearestMathPt.GetY()<<", "<<nearestMathPt.GetZ()<<endl;
	cout<<"minDis: "<<oMinDisBtEdgeAndPt<<endl;

	oNearestMathPtG = pTransToGlobal*nearestMathPt;

	return S_OK;
}


//获得焊点到连接件贴合面的最近面、最近面上的投影点、投影点到贴合面最近边上的点，最小距离等
HRESULT TestCreateSWPointCmd::GetSelfWeldNearestPts(CATIProduct_var ispInstPrd,
													 CATMathPoint imathPtG, 
													 CATFace_var & ospNearestFace1,//焊点在该product下的body上最近的face		
													 CATFace_var & ospNearestFace2,//自焊件焊点的另一个最近的face
													 CATMathPoint & oMathPointOnFaceL1,//焊点在最近face上的投影点
													 CATMathPoint & oMathPointOnFaceL2,//另一个投影点
													 CATMathVector & oNormalVectorG,//焊点在最近face上投影点处的normal方向
													 double & oCurvatureRadius1,//投影点处的曲率半径
													 double & oCurvatureRadius2,//另一个曲率半径
													 CATMathPoint & oNearestMathPtG,//离投影点最近的边上的点，该点实现最小距离
													 double & oMinDisBtEdgeAndPt)//离投影点最近的边的最小距离
{
	HRESULT rc = S_OK;

	CATMathTransformation pTransToLocal;
	CATMathTransformation pTransToGlobal;

	//全局转为局部坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, ispInstPrd);
	pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(ispInstPrd, _spRootPrd);

	//将全局点转为local
	CATMathPoint mathPt = pTransToLocal * imathPtG;

	////获得connections的PartBody	
	CATBody_var spConnectionPartBody = NULL_var;
	//_pGeneralClass->SJDGetMainBodyInProduct(ispInstPrd, spConnectionPartBody);

	//获得connections的PartBody	
	CATUnicodeString strsinglebody;
	CATBoolean ismetal=_pSJDSpotWeldCheck->IsSHEET_METAL(ispInstPrd,strsinglebody);
	if (ismetal==TRUE&&strsinglebody=="MultiBody")
	{
		//钣金件，且多实体的，取离选择点最近的实体
		_pSJDSpotWeldCheck->SJDGetSHEETMETALBodyInProduct(ispInstPrd,mathPt,spConnectionPartBody);
	}
	else
	{
		_pSJDSpotWeldCheck->SJDGetMainBodyInProduct(ispInstPrd, spConnectionPartBody);
	}

	if(spConnectionPartBody == NULL_var)
	{
		cout<<"GetInsertPointInPart: spConnectionPartBody == NULL"<<endl;

		CATUnicodeString strInstanceName;
		ispInstPrd->GetPrdInstanceName(strInstanceName);

		//CATUnicodeString strError = "零件“" + strInstanceName +"”零件几何体（PartBody）无实体，请检查模型！";
		CATUnicodeString strError = "Part“" + strInstanceName +"”has no solid body,pls check";
		_pSJDGeneralClass->CreatMsgBoxOptError(strError);
		return E_FAIL;
	}

	CATGeoFactory * ipiGeomFactory = spConnectionPartBody->GetFactory();

	//查找贴合面
	CATLISTP(CATCell) faceCell;
	spConnectionPartBody->GetAllCells(faceCell,2);
	double minDis1 = 9999.;//最小
	double minDis2 = 9999.;//第二小
	double oDistance = 0.;
	CATMathVector TempVector;
	CATMathPoint TempPoint;
	CATMathVector normalVOnFace;
	for (int i = 1; i<=faceCell.Size();i++)
	{
		CATFace * pFace = (CATFace *)faceCell[i];

		this->GetMinDistanceBetweenPointAndFace(pFace,mathPt,oDistance,TempVector, TempPoint);
		if (minDis1> oDistance)
		{
			minDis2 = minDis1;
			ospNearestFace2 = ospNearestFace1;
			oMathPointOnFaceL2 = oMathPointOnFaceL1;

			minDis1 = oDistance;
			ospNearestFace1 = pFace;
			oMathPointOnFaceL1 = TempPoint;

			normalVOnFace = TempVector;
		}
		else if(minDis2 > oDistance)
		{
			minDis2 = oDistance;
			ospNearestFace2 = pFace;
			oMathPointOnFaceL2 = TempPoint;
		}
	}	
	//贴合面上的点
	oNormalVectorG = pTransToGlobal * normalVOnFace;

	//计算face在点处的曲率半径
	CATSurface * pSurface = ospNearestFace1->GetSurface();
	double curvature;
	rc = this->GetCurvetureOfPointOnFace(ipiGeomFactory, _pConfig, oMathPointOnFaceL1, pSurface, curvature);
	cout<<"curvature: "<<curvature<<endl;
	oCurvatureRadius1 = 1.0/curvature;

	pSurface = ospNearestFace2->GetSurface();
	rc = this->GetCurvetureOfPointOnFace(ipiGeomFactory, _pConfig, oMathPointOnFaceL2, pSurface, curvature);
	cout<<"curvature: "<<curvature<<endl;
	oCurvatureRadius2 = 1.0/curvature;

	//查找face上离mathPtOnFace1最近的边
	CATMathPoint nearestMathPt;
	CATLISTP(CATCell) edgeCells;
	ospNearestFace1->GetAllCells(edgeCells, 1);
	CATCrvParam CrvParStart;
	CATCrvParam CrvParEnd;
	oMinDisBtEdgeAndPt = 9999.;
	CATMathPoint mathPtMin1;
	for(int i=1; i<=edgeCells.Size(); i++)
	{
		CATEdge * pEdge = (CATEdge *)edgeCells[i];

		CATCurve * pCircleCurve = pEdge->GetCurve();
		pEdge->GetVerticesParamsOnEdgeCurve(&CrvParStart, &CrvParEnd);
		CATCrvLimits crvLimits(CrvParStart,CrvParEnd);
		pCircleCurve->SetLimits(crvLimits);

		rc = GetMinDistanceBetweenPointAndEdge(pCircleCurve, oMathPointOnFaceL1, oDistance, mathPtMin1);

		if (oDistance<oMinDisBtEdgeAndPt)
		{
			oMinDisBtEdgeAndPt = oDistance;
			nearestMathPt = mathPtMin1;
		}
	}
	cout<<"nearestMathPt: "<<nearestMathPt.GetX()<<", "<<nearestMathPt.GetY()<<", "<<nearestMathPt.GetZ()<<endl;
	cout<<"minDis: "<<oMinDisBtEdgeAndPt<<endl;

	ospNearestFace2->GetAllCells(edgeCells, 1);
	for(int i=1; i<=edgeCells.Size(); i++)
	{
		CATEdge * pEdge = (CATEdge *)edgeCells[i];

		CATCurve * pCircleCurve = pEdge->GetCurve();
		pEdge->GetVerticesParamsOnEdgeCurve(&CrvParStart, &CrvParEnd);
		CATCrvLimits crvLimits(CrvParStart,CrvParEnd);
		pCircleCurve->SetLimits(crvLimits);

		rc = GetMinDistanceBetweenPointAndEdge(pCircleCurve, oMathPointOnFaceL2, oDistance, mathPtMin1);

		if (oDistance<oMinDisBtEdgeAndPt)
		{
			oMinDisBtEdgeAndPt = oDistance;
			nearestMathPt = mathPtMin1;
		}
	}
	cout<<"nearestMathPt: "<<nearestMathPt.GetX()<<", "<<nearestMathPt.GetY()<<", "<<nearestMathPt.GetZ()<<endl;
	cout<<"minDis: "<<oMinDisBtEdgeAndPt<<endl;

	oNearestMathPtG = pTransToGlobal*nearestMathPt;

	return S_OK;
}

//通过Face上一点和一个方向，获得十字方向的四个点坐标
HRESULT TestCreateSWPointCmd::GetCrossLinePts(CATIProduct_var ispInstPrd,//Face所在的instPrd
											   CATFace_var ispFace,//Face
											   CATMathPoint iMathPtOnFaceL,//Face上的焊点投影local
											   CATMathVector iNormalVecG,//第一个连接件最近Face处的Normal方向G
											   CATMathPoint iMathPtOnNearestEdgeG,//最近边上最近点Global
											   CATMathPoint & oMathPt1,
											   CATMathPoint & oMathPt2,
											   CATMathPoint & oMathPt3,
											   CATMathPoint & oMathPt4)
{
	HRESULT rc = S_OK;

	CATMathTransformation pTransToLocal;
	CATMathTransformation pTransToGlobal;

	//全局转为局部坐标变换
	pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, ispInstPrd);
	pTransToGlobal = _pSJDGeneralClass->GetMatrixTransformation(ispInstPrd, _spRootPrd);

	//将全局点转为local
	CATMathPoint mathPtOnNearestEdgeL = pTransToLocal * iMathPtOnNearestEdgeG;

	//获得该点在面上的normal方向
	double minDis;
	CATMathVector normalDir;
	CATMathPoint mathPtOnFace;
	this->GetMinDistanceBetweenPointAndFace(ispFace,iMathPtOnFaceL,minDis,normalDir,mathPtOnFace);

	//创建GSMPlane
	CATIPrtContainer_var  spiSpecContainer = NULL_var;
	rc = _pSJDGeneralClass->SJDGetPrtContainer(ispInstPrd,spiSpecContainer);
	CATIGSMFactory_var spGSMFactory = spiSpecContainer;

	//计算其他三条边
	//创建一个CATPlane，然后跟所有的Edge相交，获得交点
	CATMathVector VecZ = normalDir;
	CATMathVector VecX = mathPtOnNearestEdgeL - mathPtOnFace;
	CATMathVector VecY = VecZ^VecX;
	VecX = VecY^VecZ;
	VecX.Normalize();
	VecY.Normalize();
	VecZ.Normalize();

	double * origin = new double[3];
	double * xVec = new double[3];
	double * yVec = new double[3];
	double * zVec = new double[3];
	origin[0] = mathPtOnFace.GetX();
	origin[1] = mathPtOnFace.GetY();
	origin[2] = mathPtOnFace.GetZ();

	xVec[0] = VecX.GetX();
	xVec[1] = VecX.GetY();
	xVec[2] = VecX.GetZ();

	yVec[0] = VecY.GetX();
	yVec[1] = VecY.GetY();
	yVec[2] = VecY.GetZ();

	zVec[0] = VecZ.GetX();
	zVec[1] = VecZ.GetY();
	zVec[2] = VecZ.GetZ();

	CATIGSMPlane_var spGSMPlane1 = spGSMFactory->CreatePlane(origin, zVec, xVec);
	CATIGSMPlane_var spGSMPlane2 = spGSMFactory->CreatePlane(origin, yVec, zVec);
	CATISpecObject_var spSpecPlane1 = spGSMPlane1;
	spSpecPlane1->Update();
	CATISpecObject_var spSpecPlane2 = spGSMPlane2;
	spSpecPlane2->Update();

	//获得最小距离方向的两个点
	this->GetMinPtsOnCurveBySurSur(ispInstPrd, ispFace, spSpecPlane1, mathPtOnFace, oMathPt1, oMathPt2);

	//垂直于最小距离方向的方向	
	this->GetMinPtsOnCurveBySurSur(ispInstPrd, ispFace, spSpecPlane2, mathPtOnFace, oMathPt3, oMathPt4);

	//将点坐标转为Global
	oMathPt1 = pTransToGlobal*oMathPt1;
	oMathPt2 = pTransToGlobal*oMathPt2;
	oMathPt3 = pTransToGlobal*oMathPt3;
	oMathPt4 = pTransToGlobal*oMathPt4;

	return rc;
}

//获得点和Face的最小距离，最小距离实现点，最小距离实现点处的法线方向
HRESULT TestCreateSWPointCmd::GetMinDistanceBetweenPointAndFace(CATFace_var ispFace,
																 CATMathPoint iMathPoint,
																 double &oDistance,
																 CATMathVector &oNormalDirection,
																 CATMathPoint & oNearPt)
{
	HRESULT rc=E_FAIL;

	oDistance = 0.;

	if( !ispFace ) return rc;

	CATSurface *pSurface=ispFace->GetSurface();

	CATGeoFactory *pGeoFactory=pSurface->GetContainer();
	CATSoftwareConfiguration *pConf=new CATSoftwareConfiguration();
	CATDistanceMinPtSur * Operation =::CATCreateDistanceMin(pGeoFactory,pConf,iMathPoint,pSurface, TRUE, ADVANCED);
	const CATSurLimits * pSurLimits = ispFace->Get2DBoundingBox();
	Operation->SetLimits((CATSurLimits)(*pSurLimits));
	Operation->Run();

	oDistance = Operation->GetDistance();
	CATSurParam pSurParam=Operation->GetSurParam();


	CATPositionPtFaceOperator * pPosPtFaceOpe = ::CATCreatePositionPtFaceOperator(pGeoFactory,pConf,pSurParam,ispFace);//CATCreatePositionPtFaceOperator
	if( !!pPosPtFaceOpe ) 
	{
		pPosPtFaceOpe->Run();
		if ( CATLocationInner != pPosPtFaceOpe->GetOneResult() )
			oDistance = 999.;
		delete pPosPtFaceOpe;  pPosPtFaceOpe = NULL;
	}

	oNormalDirection = pSurface->EvalNormal(pSurParam);
	oNearPt = pSurface->EvalPoint(pSurParam);

	delete Operation;  Operation = NULL;
	pConf->Release();  pConf = NULL;
	pGeoFactory = NULL;

	pSurface = NULL;

	oNormalDirection.Normalize();

	return S_OK;
}

//获得点和边的最小距离
HRESULT TestCreateSWPointCmd::GetMinDistanceBetweenPointAndEdge(CATCurve * pCircleCurve,
																 CATMathPoint iMathPoint,
																 double &oDistance,
																 CATMathPoint & oMinPt)
{
	HRESULT rc = S_OK;	

	CATGeoFactory * ipiGeomFactory = pCircleCurve->GetContainer();

	//计算最小距离
	CATDistanceMinPtCrv * pDisMinOpr = CATCreateDistanceMin(ipiGeomFactory, _pConfig, 
		iMathPoint, pCircleCurve, ADVANCED );

	//获得edge的起始终止param
	CATCrvParam CrvParStart = pCircleCurve->GetStartLimit();
	CATCrvParam CrvParEnd = pCircleCurve->GetEndLimit();	

	CATCrvLimits limits(CrvParStart, CrvParEnd);
	pDisMinOpr->SetLimits(limits);
	pDisMinOpr->Run();

	//获得最小距离
	oDistance = pDisMinOpr->GetDistance();	
	//获得param
	CATCrvParam pCrvParam = pDisMinOpr->GetCrvParam();

	//获得最下距离实现点
	CATCrvEvalLocal  EvalResult;
	pCircleCurve->Eval(pCrvParam, CATCrvEvalCommand::EvalPoint, EvalResult);
	EvalResult.GetPoint(oMinPt);

	delete pDisMinOpr; 
	pDisMinOpr=NULL;

	return rc;	
}
HRESULT TestCreateSWPointCmd::GetMinPtsOnCurveBySurSur(CATIProduct_var ispInstPrd,
														CATFace_var ipFace,
														CATISpecObject_var ispSpecPlane,
														CATMathPoint iMathPtOnSurface,
														CATMathPoint & oMathPt1, 
														CATMathPoint & oMathPt2)
{
	HRESULT rc = S_OK;

	CATGeoFactory * ipiGeomFactory = ipFace->GetContainer();

	//body1 Face
	CATBody * pBody1 = ipiGeomFactory->CreateBody();
	CATDomain * pFaceDomain = pBody1->CreateDomain(2); // domain for face
	pFaceDomain->AddCell(ipFace);
	pBody1->AddDomain(pFaceDomain);

	//body2 plane
	CATBody_var spBody2 = NULL_var;
	_pSJDGeneralClass->SJDGetBodyFromSpecObject(ispSpecPlane, spBody2);

	//创建相交
	CATHybIntersect * pIntersect = ::CATCreateTopIntersect( ipiGeomFactory, _topdata, pBody1, spBody2);

	//CATLISTV(CATMathPoint) mathPtListTemp;
	if ( NULL == pIntersect )
		return E_FAIL;

	//得到相交结果
	pIntersect->Run();

	CATBody * pResultBody = pIntersect->GetResult ();
	if(pResultBody==NULL)
		return E_FAIL;

	CATLISTP(CATCell) edgeCells;
	pResultBody->GetAllCells(edgeCells, 1);

	delete pIntersect;
	pIntersect = NULL;

	if(edgeCells.Size()<=0)
		return E_FAIL;

	double distance;
	CATMathPoint mathPt;
	double minDis = 999.;
	CATCrvParam CrvParStart;
	CATCrvParam CrvParEnd;
	CATCrvParam CrvParMid;
	for(int i=1; i<=edgeCells.Size(); i++)
	{
		CATEdge * pEdge = (CATEdge *)edgeCells[i];

		pEdge->GetVerticesParamsOnEdgeCurve(&CrvParStart, &CrvParEnd);
		CATCrvLimits crvLimits(CrvParStart,CrvParEnd);		

		CATCurve * pCircleCurve = pEdge->GetCurve();
		pCircleCurve->SetLimits(crvLimits);

		//获得该curve和math点的距离
		rc = GetMinDistanceBetweenPointAndEdge(pCircleCurve, iMathPtOnSurface, distance, mathPt);		

		if (distance<minDis)
		{
			minDis = distance;

			oMathPt1 = pCircleCurve->EvalPoint(CrvParStart);
			oMathPt2 = pCircleCurve->EvalPoint(CrvParEnd);

			//CrvParMid.SetParam(0.5, crvLimits);
			//oMidPoint = pCircleCurve->EvalPoint(CrvParMid);
		}
	}

	//double minDis;
	//CATMathPoint mathPtMin;
	//if (0 != nbCurves) 
	//{
	//	//循环获得相交的curve
	//	pIntersectionSurSur->BeginningCurve();
	//	while(TRUE== (pIntersectionSurSur->NextCurve()) )
	//	{
	//		//创建相交的线和其端点
	//		CATEdgeCurve * pEdgeCurve = pIntersectionSurSur->GetEdgeCurve();
	//		//double x = oP1->GetX();
	//		//oP1->GetMathPoint(oMathPt1);
	//		//oP2->GetMathPoint(oMathPt2);
	//		oMathPt1 = pEdgeCurve->EvalPoint(pEdgeCurve->GetStartLimit());
	//		oMathPt2 = pEdgeCurve->EvalPoint(pEdgeCurve->GetEndLimit());

	//		
	//		//ipiGeomFactory->Remove(pEdgeCurve,CATICGMContainer::RemoveDependancies);

	//		//int iNum = 1;
	//		//CATCurve ** ListOfCurves = new CATCurve * [iNum];
	//		//CATCrvLimits * curLimits = new CATCrvLimits[iNum];
	//		//short * wireOrientations = new short[iNum];
	//		//ListOfCurves[0] = pEdgeCurve;
	//		//pEdgeCurve->GetLimits(curLimits[0]);
	//		//wireOrientations[0]=short(1);
	//		//CATTopWire * pWire = ::CATCreateTopWire(ipiGeomFactory, 
	//		//	_topdata,
	//		//	iNum,
	//		//	ListOfCurves,
	//		//	curLimits,
	//		//	wireOrientations);
	//		//pWire->Run();

	//		//CATBody * pBody = pWire->GetResult();
	//		//delete pWire; pWire = NULL;

	//		//CATIPrtContainer_var  spiSpecContainer = NULL_var;
	//		//rc = _pGeneralClass->SJDGetPrtContainer(ispInstPrd,spiSpecContainer);
	//		//CATIDatumFactory_var spDatumFactory = spiSpecContainer;

	//		//CATISpecObject * pResult = NULL;
	//		//GeneralSWMethod.CreateSpecObjectFromBody(ipiGeomFactory, spDatumFactory, pBody, pResult);
	//		//if(pResult==NULL)
	//		//{
	//		//	cout<<"CreateSpecObjectFromBody Failed"<<endl;
	//		//	return E_FAIL;
	//		//}

	//		////添加到结构树上
	//		//rc=GeneralSWMethod.InsertInProceduralView(pResult);
	//		//if (FAILED(rc))
	//		//{
	//		//	return E_FAIL;
	//		//}

	//		if(minDis<0.001)
	//			break;			
	//	}
	//}


	return rc;
}

// CheckButtonModify ()
CATBoolean TestCreateSWPointCmd::CheckButtonModify( void *data )
{
	// TODO: Define the action associated with the transition 
	// ------------------------------------------------------
	_pCheckDisAgent->InitializeAcquisition();
	_pCheckCurvatureAgent->InitializeAcquisition();
	_pCheckThicknessRatioAgent->InitializeAcquisition();
	_pCheckWholeThicknessAgent->InitializeAcquisition();
	_pSelfWeldCBAgent->InitializeAcquisition();

	if(_pDlg->GetCheckButton(1)->GetState() == CATDlgCheck)
		_bCheckDis = TRUE;
	else
		_bCheckDis = FALSE;

	if(_pDlg->GetCheckButton(2)->GetState() == CATDlgCheck)
		_bCheckCurvature = TRUE;
	else
		_bCheckCurvature = FALSE;

	if(_pDlg->GetCheckButton(3)->GetState() == CATDlgCheck)
		_bCheckThicknessRatio = TRUE;
	else
		_bCheckThicknessRatio = FALSE;

	if(_pDlg->GetCheckButton(4)->GetState() == CATDlgCheck)
		_bCheckWholeThickness = TRUE;
	else
		_bCheckWholeThickness = FALSE;

	if(_pDlg->GetCheckButton(5)->GetState() == CATDlgCheck)
		_bSelfWeld = TRUE;
	else
		_bSelfWeld = FALSE;

	return TRUE;
}

// SelectPart ()
CATBoolean TestCreateSWPointCmd::SelectPart( void *data )
{
	if (_pHSO)
		_pHSO->Empty();

	// TODO: Define the action associated with the transition 
	// ------------------------------------------------------
	if(_pPartAgent==NULL)
	{
		cout<<"_pPartAgent is NULL"<<endl;
		return TRUE;
	}

	CATPathElement *pPath = _pPartAgent->GetValue();
	if(pPath == NULL)
	{
		cout<<"Failed to Get PathElement."<<endl;

		_pPartAgent->InitializeAcquisition(); 
		return FALSE;
	}

	CATBaseUnknown *piUnProduct = _pPartAgent->GetElementValue();

	_pPartAgent->InitializeAcquisition();

	CATIProduct_var spPrd = piUnProduct;
	if ((_pSJDSpotWeldCheck->CheckConnectorDefinition(spPrd))==FALSE)
	{
		_pTestPublicMethod->MessegeOutput("the property of definition can not be null","Error");
		RequestDelayedDestruction();
		return FALSE;
	}

	//获得PartNumber
	CATUnicodeString strPartNumber = spPrd->GetPartNumber();

	//获得instance name	
	CATUnicodeString strInstanceName;
	spPrd->GetPrdInstanceName(strInstanceName);
	GeneralSWMethod.PathElementString(pPath, strInstanceName);	

	if(_bSelfWeld==TRUE)
	{
		_spSpecListPart.Append(spPrd);
		_strListPartIN.Append(strInstanceName);
		_strListPartPN.Append(strPartNumber);
	}
	else
	{
		CATBoolean bExist = FALSE;
		int iPos = 0;
		if(_spSpecListPart.Size()== 0)
		{
			_spSpecListPart.Append(spPrd);
			_strListPartIN.Append(strInstanceName);
			_strListPartPN.Append(strPartNumber);
		}
		else
		{
			for(int i=1; i<=_spSpecListPart.Size(); i++)
			{
				if(spPrd->IsEqual(_spSpecListPart[i]))
				{
					bExist = TRUE;
					iPos = i;
					break;
				}
			}
			if(bExist == FALSE)
			{
				_spSpecListPart.Append(spPrd);
				_strListPartIN.Append(strInstanceName);
				_strListPartPN.Append(strPartNumber);
			}
			else
			{
				_spSpecListPart.RemovePosition(iPos);
				_strListPartIN.RemovePosition(iPos);
				_strListPartPN.RemovePosition(iPos);
			}
		}
	}

	UpdateHSO(spPrd);

	//显示到对话框
	//UpdateHSO(_spSpecListPart);

	_pDlg->SetPartNameList(1, _strListPartIN);

	CheckPreviewOKSensitivity();

	return TRUE;
}

//规定只能选择part
CATBoolean TestCreateSWPointCmd::CheckSelectedPart(CATDialogAgent *iAgent,void *data)
{
	CATBoolean isOK=TRUE;

	if(_iActiveField!=1)
		return FALSE;

	if(iAgent==NULL)
		return FALSE;

	CATBaseUnknown *piUnProduct=((CATPathElementAgent *)iAgent)->GetElementValue();
	if(piUnProduct==NULL)
		return FALSE;

	CATIProduct_var spiProduct=piUnProduct;
	if(spiProduct==NULL)
		return FALSE;

	if(GeneralSWMethod.IsPart(spiProduct)==FALSE)
		return FALSE;

	CATBoolean bExist = FALSE;
	for(int i=1; i<=_spSpecAllPartList.Size(); i++)
	{
		if(spiProduct->IsEqual(_spSpecAllPartList[i]))
		{
			bExist = TRUE;
			break;
		}
	}

	if(bExist == FALSE)
		return FALSE;

	return isOK;
}

// SelectSurface ()
CATBoolean TestCreateSWPointCmd::SelectSurface( void *data )
{
	cout<<"SelectSurface"<<endl;

	if (_pHSO)
		_pHSO->Empty();

	_bSelected = FALSE;

	// TODO: Define the action associated with the transition 
	// ------------------------------------------------------
	CATBaseUnknown * pSelection = _pSurfaceAgent->GetElementValue();
	if(pSelection == NULL)
	{
		_pSJDGeneralClass->CreatMsgBoxOptError("Select Surface Failed");
		_pSurfaceAgent->InitializeAcquisition(); 
		return FALSE;
	}

	CATPathElement * pPathElement=_pSurfaceAgent->GetValue();
	if(pPathElement == NULL)
	{
		_pSJDGeneralClass->CreatMsgBoxOptError("Select Surface Failed");
		_pSurfaceAgent->InitializeAcquisition(); 
		return FALSE;
	}

	_pSurfaceAgent->InitializeAcquisition();

	HRESULT rc;	

	//获取选择Surface所在的Product**********************	
	CATBaseUnknown * pBase = pPathElement->FindElement(IID_CATIProduct);
	if(pBase == NULL)
	{
		_pSJDGeneralClass->CreatMsgBoxOptError("Select Surface Failed");
		return FALSE;
	}

	_spSurfacePrd = pBase;
	_pTransToSurfaceL = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, _spSurfacePrd);

	CATISpecObject * piSpecOnSurface=NULL;
	CATUnicodeString strPathName;
	rc=pSelection->QueryInterface(IID_CATISpecObject,(void **)&piSpecOnSurface);	
	if(piSpecOnSurface == NULL)
	{
		CATIBRepAccess *pBRepAccess = NULL;
		HRESULT rc = pSelection -> QueryInterface(IID_CATIBRepAccess, (void**) & pBRepAccess);

		CATIFeaturize_var spToFeaturize = pBRepAccess;
		if (NULL_var != spToFeaturize)
			piSpecOnSurface = spToFeaturize->FeaturizeR(MfDuplicateFeature | MfPermanentBody | MfSelectingFeatureSupport | MfFunctionalFeaturization);

		GeneralSWMethod.PathElementString(pPathElement, strPathName);
	}
	else
	{
		CATIAlias_var aliasOnCurElt = piSpecOnSurface;
		strPathName = aliasOnCurElt->GetAlias();
	}

	_spSpecSurface = piSpecOnSurface;

	_pDlg->SetSurfaceName(strPathName);

	//获得BaseSurface的Body
	CATBody_var spSurfaceBody = NULL_var;
	_pSJDGeneralClass->SJDGetBodyFromSpecObject(_spSpecSurface, spSurfaceBody);

	//获得BaseSurface的CATFace
	CATLISTP(CATCell) listCell;
	spSurfaceBody->GetAllCells(listCell,2);
	_spFace = listCell[1];

	//可以获得SurfaceProduct的Rep，通过3DVisu接口，尝试

	//获得当前的window
	CATFrmLayout * pFrmLay=CATFrmLayout::GetCurrentLayout();
	CATFrmWindow * pFrmWin = pFrmLay->GetCurrentWindow();
	CATViewer * pViewer = pFrmWin->GetViewer();
	CATViewpoint * pViewpoint = NULL;
	pViewpoint = (CATViewpoint*) &(pViewer->GetMainViewpoint());

	CATRepPath pRepPath;
	_pVisuManager->GenerateRepPathFromPathElement((*pPathElement), pViewpoint ,pRepPath);

	CATRep * pRep = pRepPath.GetCurrentRep();
	CAT3DRep * p3DRep = (CAT3DRep *)pRep;

	_pSelector = new CATSelector (this,"Selector", p3DRep);

	_pDlg->SetActiveField(3);
	_iActiveField = 3;

	//定义响应函数
	AddAnalyseNotificationCB(_pSelector,
		_pSelector->GetCATPreactivate(), 
		(CATCommandMethod)&TestCreateSWPointCmd::Preactivate, 
		(void **)NULL);

	AddAnalyseNotificationCB(_pSelector,
		_pSelector->GetCATMove(), 
		(CATCommandMethod)&TestCreateSWPointCmd::Move, 
		(void **)NULL);

	AddAnalyseNotificationCB(_pSelector,
		_pSelector->GetCATEndPreactivate(), 
		(CATCommandMethod)&TestCreateSWPointCmd::EndPreactivate, 
		(void **)NULL);

	AddAnalyseNotificationCB(_pSelector,
		_pSelector->GetCATEndActivate(), 
		(CATCommandMethod)&TestCreateSWPointCmd::EndActivate, 
		(void **)NULL);

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::Preactivate(CATCommand * iCommand,
											  CATNotification * iNotification,
											  CATCommandClientData iUsefulData)
{
	//cout<<"Preactivate"<<endl;

	HRESULT rc;

	if(_bSelected==FALSE)
	{
		//获得PSO的对象
		//判断是否为所选择的曲面
		//为所选择的曲面，获得相交点
		//创建临时点（如果不存在，否则更新临时点）
		if(_spTempPoint==NULL_var)
		{
			SJDITempPoint * pTempPoint = NULL;
			rc = ::CATInstantiateComponent("SJDTempPointComp",IID_SJDITempPoint,(void**)&pTempPoint);
			if( FAILED(rc) || pTempPoint==NULL)
			{
				cout<<"Create SW TempPoint Failed !"<<endl;
				return FALSE;
			}
			_spTempPoint = pTempPoint;
			pTempPoint->Release();
			pTempPoint = NULL;
		}

		EndPreactivate (iCommand,iNotification,iUsefulData);

		CATGraphicElementIntersection* Intersection = NULL;
		if (NULL != _pSelector)
		{
			Intersection = (CATGraphicElementIntersection*) 
				_pSelector->SendCommandSpecificObject (CATGraphicElementIntersection::ClassName(), iNotification);
		}
		if (!Intersection) 
			return FALSE; 

		//Global点
		CATMathPoint point = Intersection->point;
		Intersection->Release();

		//获得该点到所选BaseSurface上的最近的点
		double oDis;
		CATMathVector oNormalV;
		CATMathPoint oTempPoint;

		cout<<point.GetX() <<", " <<point.GetY() <<", "<<point.GetZ();

		CATMathPoint mathPtL = _pTransToSurfaceL * point;
		//cout<<mathPtL.GetX() <<", " <<mathPtL.GetY() <<", "<<mathPtL.GetZ();

		this->GetMinDistanceBetweenPointAndFace(_spFace,mathPtL,oDis,oNormalV, oTempPoint);
		//_pGeneralClass->SJDGetMinDistanceBetweenPointAndFace(_spFace, point, oDis, oNormalV);
		if(oDis<2.0)
			_spTempPoint->SetDatas(&point);
		else
			cout<<"not on"<<endl;

		//将Preview设为可执行
		_pDlg->SetPREVIEWSensitivity(CATDlgEnable);

		//cout<<"oDis: "<<oDis<<endl;
	}

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::Move(CATCommand * iCommand,
									   CATNotification * iNotification,
									   CATCommandClientData iUsefulData)
{
	//cout<<"Move"<<endl;
	//获得PSO的对象
	//判断是否为所选择的曲面
	//如果为所选择的曲面，获得相交点
	//创建临时点（如果不存在，否则更新临时点）

	Preactivate (iCommand,iNotification,iUsefulData);

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::EndPreactivate(CATCommand * iCommand,
												 CATNotification * iNotification,
												 CATCommandClientData iUsefulData)
{
	//cout<<"EndPreactivate"<<endl;
	//获得PSO的对象
	//判断是否为所选择的曲面
	//如果为所选择的曲面，获得相交点
	//创建临时点（如果不存在，否则更新临时点）

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::EndActivate(CATCommand * iCommand,
											  CATNotification * iNotification,
											  CATCommandClientData iUsefulData)
{
	//cout<<"EndActivate"<<endl;

	//获得PSO的对象
	//判断是否为所选择的曲面
	//如果为所选择的曲面，获得相交点
	//创建临时点（如果不存在，否则更新临时点）
	//结束Selector

	_bSelected = TRUE;



	return TRUE;
}

//规定选择的点必须在门的模型中，如果门的模型未选择，则退出
CATBoolean  TestCreateSWPointCmd::CheckSelectedSurface(CATDialogAgent *iAgent,void *data)
{
	CATBoolean isOK = TRUE;

	//判断当前的ActiveField
	if(_iActiveField!=2)
		return FALSE;

	if(iAgent==NULL)
		return FALSE;

	//part未选择
	if(_spSpecListPart.Size()<=0)
	{
		//_pSJDGeneralClass->CreatMsgBoxOptError("请在选择连接件后，再选择参考面！");
		_pSJDGeneralClass->CreatMsgBoxOptError("pls select a connection part,then select the reference face");
		return FALSE;
	}

	//获得所选择的元素
	CATPathElement *pPath = _pSurfaceAgent->GetValue();
	if(pPath == NULL)
	{
		cout<<"Failed to Get PathElement."<<endl;
		_pSurfaceAgent->InitializeAcquisition(); 
		return FALSE;
	}

	_pSurfaceAgent->InitializeAcquisition();

	//获取选择Point所在的Product**********************
	CATBaseUnknown * pBase = pPath->FindElement(IID_CATIProduct);
	if(pBase == NULL)
	{
		cout<<"Failed to FindElement."<<endl;
		return FALSE;
	}

	//判断该点所在的product和已经选择的part是否一致
	CATBoolean bFind = FALSE;
	for(int i=1; i<=_spSpecListPart.Size(); i++)
	{
		if(pBase->IsEqual(_spSpecListPart[i]))
		{
			bFind = TRUE;
			break;
		}
	}
	if(bFind == TRUE)
		return TRUE;
	else
		return FALSE;	

	return isOK;
}

//规定选择的点必须在门的模型中，如果门的模型未选择，则退出
CATBoolean  TestCreateSWPointCmd::CheckSelectedOther(CATDialogAgent *iAgent,void *data)
{
	CATBoolean isOK = TRUE;

	//判断当前的ActiveField
	if(_iActiveField!=3)
		return FALSE;

	return TRUE;
}

// ConnectionsSelectorSelected ()
CATBoolean TestCreateSWPointCmd::ConnectionsFieldSelected( void *data )
{
	// TODO: Define the action associated with the transition 
	// ------------------------------------------------------

	_pSLConnectionsAgent->InitializeAcquisition();

	_pDlg->SetActiveField(1);
	_iActiveField = 1;

	_pHSO->Empty();

	//列表为空返回
	if(_strListPartPN.Size()==0)
		return TRUE;

	//获得该selectorlist中所选择的内容
	CATDlgSelectorList * pSelectListCncts = _pDlg->GetSelectorList(2);
	int count = pSelectListCncts->GetSelectCount();

	//未选择，返回
	if(count<=0)
		return TRUE;	

	int * ioTabRow = new int[count];
	pSelectListCncts->GetSelect(ioTabRow, count);//获取选中行

	//获得所选择的内容
	CATListValCATISpecObject_var spSpecListUpdate;
	for(int i=0; i<count; i++)
	{		
		spSpecListUpdate.Append(_spSpecListPart[ioTabRow[i]+1]);
	}

	//高亮所选择的内容
	UpdateHSO(spSpecListUpdate);

	spSpecListUpdate.RemoveAll();

	return TRUE;
}

// SurfaceSelectorSelected ()
CATBoolean TestCreateSWPointCmd::BaseSurfaceFieldSelected( void *data )
{
	// TODO: Define the action associated with the transition 
	// ------------------------------------------------------

	_pSLBaseSurfaceAgent->InitializeAcquisition();

	_pDlg->SetActiveField(2);
	_iActiveField = 2;

	_pHSO->Empty();

	if(_spSpecSurface!=NULL_var)
	{
		//获得所选择的内容
		CATListValCATISpecObject_var spSpecListUpdate;
		spSpecListUpdate.Append(_spSpecSurface);

		//高亮所选择的内容
		UpdateHSO(spSpecListUpdate);
		spSpecListUpdate.RemoveAll();
	}		

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::AllCnctsSelected(void * data)
{
	_pSLAllCnctsAgent->InitializeAcquisition();

	_pDlg->SetActiveField(3);
	_iActiveField = 3;

	_pHSO->Empty();

	if(_spSpecAllPartList.Size()<1)
		return FALSE;

	//获得该selectorlist中所选择的内容
	CATDlgSelectorList * pSelectListAll = _pDlg->GetSelectorList(3);
	int count = pSelectListAll->GetSelectCount();
	if(count<=0)
		return TRUE;

	int * ioTabRow = new int[count];
	pSelectListAll->GetSelect(ioTabRow, count);//获取选中行

	//获得所选择的内容
	CATListValCATISpecObject_var spSpecListUpdate;
	for(int i=0; i<count; i++)
	{
		spSpecListUpdate.Append(_spSpecAllPartList[ioTabRow[i]+1]);
	}

	//高亮所选择的内容
	UpdateHSO(spSpecListUpdate);
	spSpecListUpdate.RemoveAll();

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::ActionToLeft(void * data)
{
	_pToLeft->InitializeAcquisition();

	//获得右边所选择的列表
	if(_spSpecAllPartList.Size()<1)
		return FALSE;

	//获得该selectorlist中所选择的内容
	CATDlgSelectorList * pSelectListAll = _pDlg->GetSelectorList(3);
	int count = pSelectListAll->GetSelectCount();
	if(count<=0)
		return TRUE;

	int * ioTabRow = new int[count];
	pSelectListAll->GetSelect(ioTabRow, count);//获取选中行

	//加入到左边列表
	CATISpecObject_var spSpecTemp;
	CATIProduct_var spPrd;
	CATUnicodeString strPartNumber;
	if(_bSelfWeld==TRUE)
	{
		for(int i=0; i<count; i++)
		{
			spSpecTemp = _spSpecAllPartList[ioTabRow[i] + 1];
			spPrd = spSpecTemp;

			if ((_pSJDSpotWeldCheck->CheckConnectorDefinition(spPrd))==FALSE)
			{
				_pTestPublicMethod->MessegeOutput("the property of definition can not be null","Error");
				continue;
			}

			strPartNumber = spPrd->GetPartNumber();

			_spSpecListPart.Append(spSpecTemp);
			_strListPartPN.Append(strPartNumber);
			_strListPartIN.Append(_strAllPartList[ioTabRow[i] + 1]);
		}
	}
	else
	{
		//获得所选择的内容
		CATBoolean bExist;
		for(int i=0; i<count; i++)
		{
			spSpecTemp = _spSpecAllPartList[ioTabRow[i] + 1];
			bExist = FALSE;
			for(int j=1; j<=_spSpecListPart.Size(); j++)
			{
				if(spSpecTemp->IsEqual(_spSpecListPart[j]))
				{
					bExist = TRUE;
					break;
				}
			}

			if(bExist == FALSE)
			{
				spPrd = spSpecTemp;
				if ((_pSJDSpotWeldCheck->CheckConnectorDefinition(spPrd))==FALSE)
				{
					_pTestPublicMethod->MessegeOutput("the property of definition can not be null","Error");
					continue;
				}

				strPartNumber = spPrd->GetPartNumber();

				_spSpecListPart.Append(spSpecTemp);
				_strListPartPN.Append(strPartNumber);
				_strListPartIN.Append(_strAllPartList[ioTabRow[i] + 1]);
			}
		}
	}

	_pDlg->SetPartNameList(1, _strListPartIN);

	CheckPreviewOKSensitivity();

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::ActionToRight(void * data)
{
	_pToRight->InitializeAcquisition();

	if(_spSpecListPart.Size()<1)
		return FALSE;

	//获得左边所选择的列表

	//获得该selectorlist中所选择的内容
	CATDlgSelectorList * pSelectListCncts = _pDlg->GetSelectorList(2);
	int count = pSelectListCncts->GetSelectCount();
	if(count<=0)
		return TRUE;

	int * ioTabRow = new int[count];
	pSelectListCncts->GetSelect(ioTabRow, count);//获取选中行

	//将所选择的列表去除
	int iFlag;
	for(int i=count; i>0; i--)
	{
		iFlag = ioTabRow[i-1] + 1;
		_spSpecListPart.RemovePosition(iFlag);
		_strListPartIN.RemovePosition(iFlag);
		_strListPartPN.RemovePosition(iFlag);
	}
	delete ioTabRow;

	_pDlg->SetPartNameList(1, _strListPartIN);

	CheckPreviewOKSensitivity();

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::ActionMiddlePB(void * data)
{
	cout<<"ActionMiddlePB"<<endl;

	_pMiddlePBAgent->InitializeAcquisition();

	//计算_centerMathPtG在面上的投影
	//转到曲面local点
	CATMathTransformation pTransToLocal = _pSJDGeneralClass->GetMatrixTransformation(_spRootPrd, _spSurfacePrd);
	CATMathPoint mathPtL = pTransToLocal * _centerMathPtG;

	//投影
	double oDis;
	CATMathDirection oNormalDir;
	CATMathPoint oNearPt;
	this->GetMinDistanceBetweenPointAndFace(_spFace, mathPtL, oDis, oNormalDir, oNearPt);

	//转为G
	CATMathTransformation pTransToG = _pSJDGeneralClass->GetMatrixTransformation(_spSurfacePrd, _spRootPrd);
	_centerMathPtG = pTransToG * oNearPt;

	_spTempPoint->SetDatas(&_centerMathPtG);

	//删除上一个焊点
	DeleteNewSWPoint();

	//创建焊点
	CreateSWPoint();

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::ActionDeleteNewPB(void * data)
{
	cout<<"ActionDeleteNewPB"<<endl;

	_pDeleteNewPBAgent->InitializeAcquisition();

	DeleteNewSWPoint();

	return TRUE;
}

CATBoolean TestCreateSWPointCmd::ActionNextPB(void * data)
{
	cout<<"ActionNextPB"<<endl;

	_bSelected = FALSE;

	_pDlg->GetPushButton(5)->SetSensitivity(CATDlgDisable);

	_pNextPBAgent->InitializeAcquisition();

	return TRUE;
}

HRESULT TestCreateSWPointCmd::GetCurvetureOfPointOnFace(CATGeoFactory *ipiGeomFactory,
														 CATSoftwareConfiguration *ipConfig,
														 CATMathPoint iPoint,
														 CATSurface * ipSurface,
														 double & oCurveture3)
{
	HRESULT rc = E_FAIL;
	if( !ipiGeomFactory )  
		return rc;

	CATPoint *pPoint=NULL;
	pPoint = (CATPoint *)ipiGeomFactory->CreateCartesianPoint(iPoint);
	if( !pPoint ) 
		return rc;

	CATProjectionPtSur *pPtProjectOpe=::CATCreateProjection(ipiGeomFactory,ipConfig,pPoint,ipSurface);

	if (pPtProjectOpe == NULL)			
		return E_FAIL;

	CATTry
	{
		CATSurParam sParm =pPtProjectOpe->GetParam();
		//CATMathPoint pTryPoint = pSurface->EvalPoint(sParm);
		// 		iPoint.Dump();
		// 		pTryPoint.Dump();
		if( !!pPtProjectOpe ) { delete pPtProjectOpe;  pPtProjectOpe = NULL;  }

		CATLocalAnalysis2D * pAnalysis = CATCreateLocalAnalysis(ipConfig, ipSurface,sParm);
		if (!pAnalysis)
		{
			return E_FAIL;
		}

		double GaussianCurvature,MeanCurvature ,MinCurvature,MaxCurvature,realMinCurvature,realMaxCurvature = 0.;

		if (pAnalysis!=NULL)
		{
			GaussianCurvature = pAnalysis->GetGaussianCurvature();
			MeanCurvature = pAnalysis->GetMeanCurvature();
			pAnalysis->GetMinMaxCurvature(MinCurvature,MaxCurvature);
			if (fabs(MinCurvature)<fabs(MaxCurvature))
			{
				realMinCurvature = fabs(MinCurvature);
				realMaxCurvature = fabs(MaxCurvature);
			}
			else
			{
				realMinCurvature = fabs(MaxCurvature);
				realMaxCurvature = fabs(MinCurvature);
			}

			//	oCurveture1 = abs(GaussianCurvature);//1/
			//	oCurveture2 = abs(MeanCurvature);//1/
			//oCurveture3 = realMaxCurvature;//1/
			//oCurveture4 = realMinCurvature;//1/
			oCurveture3 =realMaxCurvature;
			//iPoint.Dump();
			//cout<<"  GaussianCurvature:"<<GaussianCurvature;
			//cout<<"  MeanCurvature:"<<MeanCurvature;
			//cout<<"  MinCurvature:"<<MinCurvature;
			//cout<<"  MaxCurvature:"<<MaxCurvature<<endl;
			//cout<<"  G1:"<<oCurveture1;
			//cout<<"  M1:"<<oCurveture2;
			//cout<<"  Min1:"<<oCurveture3;
			//cout<<"  Max1:"<<oCurveture4<<endl;
		}
	}
	CATCatch(CATMfErrUpdate , pUpdateError)
	{
		return E_FAIL;
	}
	CATCatch(CATError , pError)
	{
		cout<<"Error!";
		return E_FAIL;

	}
	CATEndTry;
	return S_OK;
}

//========================================
// MessageOutPutYesNo()
//========================================
int  TestCreateSWPointCmd::MessageOutPutYesNo(CATUnicodeString iString,CATUnicodeString iTopString)
{
	int sign=0;
	CATApplicationFrame *pApplication = CATApplicationFrame::GetFrame(); 
	if (NULL != pApplication) {
		CATDlgWindow * pMainWindow = pApplication->GetMainWindow();
		//CATDlgNotify *pNotifyDlg = new CATDlgNotify(pMainWindow, "............", CATDlgNfyError);
		CATDlgNotify *pNotifyDlg = new CATDlgNotify(pMainWindow, "............", CATDlgNfyYesNo|CATDlgNfyError);		
		if(NULL != pNotifyDlg) {
			sign = pNotifyDlg->DisplayBlocked(iString,iTopString);
			pNotifyDlg->RequestDelayedDestruction();
			pNotifyDlg->Release();
			pNotifyDlg = NULL;
		}
	}
	return sign;
}