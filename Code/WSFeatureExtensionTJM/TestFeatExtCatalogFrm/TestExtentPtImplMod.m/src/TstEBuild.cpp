// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TstEBuild.cpp
// Provide implementation to interface
//    CATIBuild
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Apr 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TstEBuild.h"
 
CATImplementClass(TstEBuild,
                  DataExtension,
                  CATBaseUnknown,
                  TestExtendPT );	//最后一个参数需要给的是catalog里面的startuptype
 

//-----------------------------------------------------------------------------
// TstEBuild : constructor
//-----------------------------------------------------------------------------
TstEBuild::TstEBuild():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// TstEBuild : destructor
//-----------------------------------------------------------------------------
TstEBuild::~TstEBuild()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATIBuild.h"
TIE_CATIBuild( TstEBuild);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATIBuild::Build
//-----------------------------------------------------------------------------
HRESULT TstEBuild::Build ()
{
	//删除该特征实例的所有更新错误信息
	CATIUpdateError *piUpdateError=NULL;
	HRESULT rc = this->QueryInterface(IID_CATIUpdateError,(void**)&piUpdateError);
	if (FAILED(rc)||piUpdateError==NULL)
	{
		return E_FAIL;
	}
	piUpdateError->UnsetUpdateError();
	CATIMfResultManagement_var spMfResultManagement(this);
	if (NULL_var!=spMfResultManagement)
	{
		spMfResultManagement->DeleteScopeResult();
	}
	//获取该特征实例的输入参数
	TstIPoint *piTstPoint=NULL;
	rc = this->QueryInterface(IID_TstIPoint,(void**)&piTstPoint);
	if (FAILED(rc)||piTstPoint==NULL)
	{
		return E_FAIL;
	}
	double _x,_y,_z;
	HRESULT rc1= piTstPoint->GetX(_x);
	HRESULT rc2= piTstPoint->GetY(_y);
	HRESULT rc3= piTstPoint->GetZ(_z);
	if (FAILED(rc1)||FAILED(rc2)||FAILED(rc3))
	{
		return E_FAIL;
	}
	//定义一个程序报告 procedural report
	CATIMfProcReport *piProcReport=NULL;
	rc=piTstPoint->QueryInterface(IID_CATIMfProcReport,(void**)&piProcReport);
	if (FAILED(rc)||piProcReport==NULL)
	{
		return E_FAIL;
	}
	CATLISTV(CATBaseUnknown_var) lstSpec;
	CATListOfCATUnicodeString lstKeys;
	piProcReport->CreateProcReport(lstSpec,lstKeys);
	CATCGMJournalList *pCGMJournalList=piProcReport->GetCGMJournalList();
	//获取工厂
	CATGeoFactory *pGeoFactory = this->GetGeoFactory();
	CATIDatumFactory *piDatumFactory = this->GetDatumFactory();
	if (pGeoFactory==NULL||piDatumFactory==NULL)
	{
		return E_FAIL;
	}
	CATSoftwareConfiguration *pConfig=new CATSoftwareConfiguration();
	CATTopData *topdata=new CATTopData(pConfig,pCGMJournalList);
	CATTry
	{
		CATBody *pBody = ::CATCreateTopPointXYZ(pGeoFactory,topdata,_x,_y,_z);
		pGeoFactory->Release();
		pGeoFactory=NULL;
		if (pBody!=NULL)
		{
			piProcReport->StoreProcReport(pBody);
		}
		else
		{
			CATMfErrUpdate *pErrorUpdate = new CATMfErrUpdate();
			CATUnicodeString strDiagnostic("Create TestExtendPt Failed.");
			pErrorUpdate->SetDiagnostic(1,strDiagnostic);
			CATThrow(pErrorUpdate);
		}
	}
	CATCatch(CATMfErrUpdate,pUpdateError)
	{
		CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
		pErrorToThrow->SetDiagnostic(1,pUpdateError->GetDiagnostic());
		::Flush(pUpdateError);

		if (piUpdateError!=NULL)
		{
			piUpdateError->SetUpdateError(pErrorToThrow);
		}

		if (NULL != piUpdateError)
		{
			piUpdateError->Release();
			piUpdateError=NULL;
		}
		if (NULL!=piProcReport)
		{
			piProcReport->Release();
			piProcReport=NULL;
		}

		CATThrow(pErrorToThrow);
	}
	CATCatch(CATError,pError)
	{
		CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
		pErrorToThrow->SetDiagnostic(1,pError->GetNLSMessage());
		::Flush(pError);
		if (piUpdateError!=NULL)
		{
			piUpdateError->SetUpdateError(pErrorToThrow);
		}

		if (piUpdateError!=NULL)
		{
			piUpdateError->Release();
			piUpdateError=NULL;
		}
		if (piProcReport!=NULL)
		{
			piProcReport->Release();
			piProcReport=NULL;
		}

		CATThrow(pErrorToThrow);
	}
	CATEndTry;

	//释放指针
	if (pConfig!=NULL)
	{
		pConfig->Release();
		pConfig=NULL;
	}
	if (topdata!=NULL)
	{
		delete topdata;
		topdata=NULL;
	}
	if (piUpdateError!=NULL)
	{
		piUpdateError->Release();
		piUpdateError=NULL;
	}
	if (piProcReport!=NULL)
	{
		piProcReport->Release();
		piProcReport=NULL;
	}
	if (piTstPoint!=NULL)
	{
		piTstPoint->Release();
		piTstPoint=NULL;
	}

   return S_OK;
}

CATGeoFactory *TstEBuild::GetGeoFactory()
{
	CATGeoFactory *opGeoFactory = NULL;

	// Gets a pointer on CATISpecObject.
	CATILinkableObject *piLinkableObject = NULL;
	HRESULT rc = this->QueryInterface( IID_CATILinkableObject, (void**)& piLinkableObject );

	if ( SUCCEEDED(rc) )
	{
		// Do not release this pointer
		CATDocument * pDocument = NULL ;
		pDocument = piLinkableObject->GetDocument();

		if ( NULL != pDocument )
		{
			CATIContainerOfDocument * pIContainerOfDocument = NULL ;
			rc = pDocument->QueryInterface(IID_CATIContainerOfDocument,(void**)& pIContainerOfDocument );
			if ( SUCCEEDED(rc) )
			{
				CATIContainer * pIContainerOnGeomContainer = NULL ;
				rc = pIContainerOfDocument->GetResultContainer(pIContainerOnGeomContainer);
				if ( SUCCEEDED(rc) )
				{
					CATGeoFactory *piGeomFactory = NULL;
					rc = pIContainerOnGeomContainer->QueryInterface( IID_CATGeoFactory , (void**) &piGeomFactory );
					pIContainerOnGeomContainer->Release();
					pIContainerOnGeomContainer = NULL ;
					if (SUCCEEDED(rc)&&piGeomFactory!=NULL)
					{
						opGeoFactory = piGeomFactory;
					}
				}
				pIContainerOfDocument->Release();
				pIContainerOfDocument = NULL ;
			}
		}
		piLinkableObject->Release();
		piLinkableObject = NULL ;
	}

	return opGeoFactory;
}

CATIDatumFactory *TstEBuild::GetDatumFactory()
{
	CATIDatumFactory *opiDatumFactory=NULL;
	// Gets a pointer on CATISpecObject.
	CATILinkableObject *piLinkableObject = NULL;
	HRESULT rc = this->QueryInterface( IID_CATILinkableObject, (void**)& piLinkableObject );

	if ( SUCCEEDED(rc) )
	{
		// Do not release this pointer
		CATDocument * pDocument = NULL ;
		pDocument = piLinkableObject->GetDocument();
		if ( NULL != pDocument )
		{
			CATInit_var spInit = pDocument;
			if (spInit!=NULL_var)
			{
				CATIPrtContainer *piPrtContainer=(CATIPrtContainer *)spInit->GetRootContainer("CATIPrtContainer");
				if (piPrtContainer!= NULL)
				{
					CATIDatumFactory *piDatumFactory =NULL;
					rc = piPrtContainer->QueryInterface(IID_CATIDatumFactory,(void**) &piDatumFactory);
					if (SUCCEEDED(rc)&&piDatumFactory!=NULL)
					{
						opiDatumFactory=piDatumFactory;
					}
				}
			}
		}
		piLinkableObject->Release();
		piLinkableObject = NULL ;
	}
	return opiDatumFactory;
}