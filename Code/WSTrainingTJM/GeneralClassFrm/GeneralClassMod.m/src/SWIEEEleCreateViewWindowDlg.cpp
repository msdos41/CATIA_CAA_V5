//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
//=============================================================================
// Local Framework
#include "SWIEEEleCreateViewWindowDlg.h"

// Dialog Framework
#include "CATInteractiveApplication.h"    // For the current application to destroy

// Visualization Framework
#include "CATNavigation3DViewer.h"        // the window
#include "CAT3DRep.h"                     // the visualisation rep
#include "CAT3DBagRep.h"                  // the visualisation rep
#include "CAT3DBoundingSphere.h"          // bounding sphere

// C++ Standard library
#include "iostream.h"
#include "fstream.h"
#include "CATErrorMacros.h"
#include "CATCommand.h"


//--------------------------------------------------------------------------------------
SWIEEEleCreateViewWindowDlg::SWIEEEleCreateViewWindowDlg(CATDialog* iParentCommand, const CATString& iName,CATBaseUnknown_var spViewOccurrence)                              
    : CATDlgDialog((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(), "ViewWindow",CATDlgWndNoResize|CATDlgWndCLOSE|CATDlgWndBtnClose)	                    
{
	_spViewOccurrence=spViewOccurrence;
	_p3DBagRep=NULL;
	_p3DViewer=NULL;
	_pNavigController= NULL ;
	_pNavigBox= NULL ;
}

//--------------------------------------------------------------------------------------

SWIEEEleCreateViewWindowDlg::~SWIEEEleCreateViewWindowDlg()
{ 
  if ( NULL != _p3DBagRep )
  {
     _p3DBagRep->Destroy();
     _p3DBagRep = NULL ;
  }
  _p3DViewer    = NULL ;
  _pApplication = NULL ;
  _spViewOccurrence=NULL_var;
  _pNavigController= NULL ;
  _pNavigBox= NULL ;

}

//--------------------------------------------------------------------------------------

void SWIEEEleCreateViewWindowDlg::Build()
{
	CreateViewer();

	CreateModelRepresentation();

	VisualizeModel();

	CreateNavigBox(this);

	AddAnalyseNotificationCB(this,GetDiaCLOSENotification(),(CATCommandMethod)&SWIEEEleCreateViewWindowDlg::Close, NULL);
	AddAnalyseNotificationCB(this,GetWindCloseNotification(),(CATCommandMethod)&SWIEEEleCreateViewWindowDlg::Close, NULL);

}
void SWIEEEleCreateViewWindowDlg::Close(CATCommand* iSendingCommand, 
										CATNotification    * iSentNotification, 
										CATCommandClientData iUsefulData)
{
	SetVisibility(CATDlgHide);
	//SendNotification(GetFather(),iSentNotification);
	//RequestDelayedDestruction();
}

//--------------------------------------------------------------------------------------
void SWIEEEleCreateViewWindowDlg::CreateViewer()
{

  // The window contains a 3DViewer which allows the user to do 3D Manipulations 
  _p3DViewer = new CATNavigation3DViewer( this, "3DViewerId",CATDlgFraNoTitle, 800, 450);

  // Changes the color of the background
  _p3DViewer->SetBackgroundColor(0.2f,0.2f,0.6f);

  // The Viewer is attached to the 4 sides of the Window.
  Attach4Sides( _p3DViewer);

  _p3DViewer->Reframe();

}
//--------------------------------------------------------------------------------------                 
void SWIEEEleCreateViewWindowDlg::CreateModelRepresentation()
{
  // The Top of the graphic representation tree

	if (_spViewOccurrence==NULL_var||_p3DViewer==NULL)
		return;

	if (NULL== _p3DBagRep) 
		//_p3DBagRep = CAT3DBagRep::CreateRep();
		//----------V5
		_p3DBagRep = new CAT3DBagRep();

	  CATVisManager * pVisuManager = CATVisManager::GetVisManager();

	  // Retrieves the viewpoint 
	  CATViewpoint  * pViewPoint = NULL ;
	  pViewPoint = (CATViewpoint*) &(_p3DViewer->GetMain3DViewpoint());

	  CATPathElement * pRootObjectPath1 =NULL;
	  pRootObjectPath1 = new CATPathElement(_spViewOccurrence);

	  //CATPathElement pRootObjectPath ;
	  //pRootObjectPath.AddChildElement(_spViewOccurrence);

	  CATFrmEditor * pEditor = CATFrmEditor::GetCurrentEditor();
	  CATPSO * pPSO = pEditor->GetPSO() ;   
	  CATHSO * pHSO = pEditor->GetHSO() ; 
	  CATISO * pISO = pEditor->GetISO() ; 

	  list<IID> ListIVisu3d;
	  IID visu3d = IID_CATI3DGeoVisu ;
	  ListIVisu3d.fastadd(&visu3d);

	  CATCommand * pCommandSelector = (CATCommand*) pEditor->GetCommandSelector();
	  pVisuManager->AttachTo(pRootObjectPath1,pViewPoint,ListIVisu3d,pCommandSelector);

	  pVisuManager->AttachPSOTo( pPSO,pViewPoint);
	  pVisuManager->AttachHSOTo( pHSO,pViewPoint);

	  // The returned path 
	  CATRepPath RepPath  ;
	  CATPathElement pRootObjectPath2 ;
	  pRootObjectPath2.AddChildElement(_spViewOccurrence);
	  pVisuManager->GenerateRepPathFromPathElement(pRootObjectPath2,pViewPoint,RepPath);

	  if ( RepPath.Size() >= 1 )
	  {    
		  CAT3DRep * pRep =NULL;
		  pRep = (CAT3DRep*) RepPath[RepPath.Size()-1];
		  if ( NULL != pRep )
		  {
			  _p3DBagRep->AddChild(*pRep);
		  }
	  }

	  pISO->AddViewer(_p3DViewer);


}

//----------------------------------------------------------------------- 
// VisualizeModel
//-----------------------------------------------------------------------                
void SWIEEEleCreateViewWindowDlg::VisualizeModel()
{
   if ( (NULL != _p3DViewer) && ( NULL != _p3DBagRep) )
   {    
      // Instruction to do once 
      _p3DViewer->AddRep((CAT3DRep*)_p3DBagRep);

      // Reframe on the current bouding sphere
      const CAT3DBoundingSphere boundingSphere = _p3DBagRep->GetBoundingElement(); 
      _p3DViewer->ReframeOn(boundingSphere);

      // Instruction to do at each  representation modification 
      _p3DViewer->Draw();
   }

}
HRESULT SWIEEEleCreateViewWindowDlg::GetNavigBox(CATNavigController *&pNavigController,CATNavigBox *&pNavigBox)
{
	pNavigController=_pNavigController;

	pNavigBox=_pNavigBox;

	return S_OK;
}
HRESULT SWIEEEleCreateViewWindowDlg::CreateNavigBox( CATDialog *iDialog)
{
	HRESULT hr = E_FAIL;

	//获取高亮接口
	CATFrmEditor * iFrmEditor=NULL;
	iFrmEditor=CATFrmEditor::GetCurrentEditor();
	if(NULL == iFrmEditor)
	{
		return E_FAIL;
	}
	CATHSO *pHSO = iFrmEditor->GetHSO();
	if (NULL == pHSO)
	{
		return E_FAIL;
	}

	CATViewer *iViewer = NULL;
	CAT2DViewpoint *iViewPoint = NULL; 
	CATString iName = "NavBox"; 
	CATGraphStyle iStyle = Indented; 
	CATClassId id = "ObjNavDefault";
	int width = 300;
	int height = 200; 
	int ivisibility = 1;
	int idepth = 1; 
	int mode = 0 ;

	_pNavigBox=NULL;
	_pNavigBox =new CATNavigBox(iDialog, iName, iFrmEditor, iStyle, id, width, height, _p3DViewer, iViewPoint );
	if (NULL == _pNavigBox)
	{
		return E_FAIL;
	}

	_pNavigBox->AddRoot(_spViewOccurrence);

	//获取CATNavigController
	_pNavigController = NULL;
	_pNavigController=_pNavigBox->GetController();	
	if  (NULL == _pNavigController)
	{
		return E_FAIL;
	}

	//设定结构树相关参数
	_pNavigController->SetActivatorsVisibility(1);
	_pNavigController->SetDepth(1);
	_pNavigController->SetDereferenceMode(0);

	_pNavigController->AttachToHSO(pHSO);

	ExpandCollapseNode(_pNavigController,_spViewOccurrence);

	_p3DViewer->Draw();

	return S_OK;
}

void SWIEEEleCreateViewWindowDlg::ExpandAllNode(CATNavigController *pNavigController,CATBaseUnknown_var iRootObject,CATBaseUnknown_var iExpendObject)
{

	if ( (NULL_var != iRootObject) && (NULL != pNavigController) )
	{	
		CATListValCATBaseUnknown_var * pNodeList = NULL ;
		pNodeList = pNavigController->GetAssociatedElements(iRootObject);

		if ( NULL != pNodeList )
		{
			int nbNodes = pNodeList->Size();
			for ( int i= 1 ; i <= nbNodes ; i++ )
			{
				CATIGraphNode_var graphNode = (*pNodeList)[i];
				if ( NULL_var != graphNode )
				{
					// To be expanded
					if ( 0 == graphNode->IsExpanded() )
					{
						CATINavigElement_var spNavigElement = graphNode ;

						if ( NULL_var != spNavigElement )
						{
							spNavigElement->ProcessAfterExpand();//ProcessAfterSelect
							spNavigElement->Update( ); 
						}
					}
				}
			}

			delete pNodeList ;
			pNodeList = NULL ;
		}

		// Processes the children
		CATINavigateObject_var spNavigateObject = iRootObject ;
		if ( NULL_var != spNavigateObject )
		{
			CATListValCATBaseUnknown_var* pListChild = NULL ;
			pListChild = spNavigateObject->GetChildren();

			if ( NULL != pListChild )
			{
				for ( int t = 1 ; t <= pListChild->Size() ; t++)
				{
					CATBaseUnknown_var spOnChild = (*pListChild)[t];
					if (iExpendObject)
					{
						if (spOnChild->IsEqual(iExpendObject))
						{
							ExpandAllNode(pNavigController,spOnChild,iExpendObject);
						}
						else
						{
							ExpandAllNode(pNavigController,spOnChild,iExpendObject);
						}

					}
					else
					{
						ExpandAllNode(pNavigController,spOnChild,NULL_var);
					}
				}

				delete pListChild ;
				pListChild = NULL ;
			}
		}

	}
}
void SWIEEEleCreateViewWindowDlg::ExpandCollapseNode(CATNavigController *pNavigController,CATBaseUnknown_var iObject)
{
	cout << "SWIEEEleCreateViewWindowDlg::ExpandCollapseNode" << endl ;

	if ( (NULL_var != iObject) && (NULL != pNavigController) )
	{
		CATListValCATBaseUnknown_var * pNodeList = NULL ;
		pNodeList = _pNavigController->GetAssociatedElements(iObject);

		if ( NULL != pNodeList )
		{
			int nbNodes = pNodeList->Size();
			for ( int i= 1 ; i <= nbNodes ; i++ )
			{
				CATIGraphNode_var spNode = (*pNodeList)[i];

				if ( NULL_var != spNode )
				{
					CATINavigElement_var spNavigElement = spNode ;

					if ( NULL_var != spNavigElement )
					{
						spNavigElement->ProcessAfterExpand();  //ProcessAfterExpand  
						spNavigElement->Update(); 
					}
				}
			}

			delete pNodeList ;
			pNodeList = NULL ;
		}
	}
}
void SWIEEEleCreateViewWindowDlg::DeleteWindow()
{
	CATFrmEditor * pEditor = CATFrmEditor::GetCurrentEditor();
	CATPSO * pPSO = pEditor->GetPSO() ;   
	CATHSO * pHSO = pEditor->GetHSO() ; 
	CATISO * pISO = pEditor->GetISO()  ; 

	CATPathElement pRootObjectPath ;
	pRootObjectPath.AddChildElement(_spViewOccurrence);

	if  (NULL != pISO)   pISO->RemoveViewer(_p3DViewer);

	CATViewpoint  * pViewPoint = NULL ;
	pViewPoint = (CATViewpoint*) &(_p3DViewer->GetMain3DViewpoint());

	CATVisManager * pVisuManager = CATVisManager::GetVisManager();
	if ( NULL != pViewPoint)
	{
		pVisuManager->DetachPSOFrom(pViewPoint);
		pVisuManager->DetachHSOFrom(pViewPoint);
		pVisuManager->DetachFrom(&pRootObjectPath,pViewPoint);
	}

}
