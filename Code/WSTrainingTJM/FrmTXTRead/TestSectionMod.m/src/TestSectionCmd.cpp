// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestSectionCmd.cpp
// The state chart based command: TestSectionCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Apr 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestSectionCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

#include "CATCreateExternalObject.h"
CATCreateClass( TestSectionCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestSectionCmd::TestSectionCmd() :
  CATStateCommand ("TestSectionCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
,_pGeneralCls(NULL)
{
	_pGeneralCls = new GeneralClass();

	CATIProduct_var spiProdRoot = NULL_var;

	HRESULT rc = _pGeneralCls->GetRootProductUpdate(spiProdRoot);
	if (FAILED(rc)||spiProdRoot==NULL_var)
	{
		RequestDelayedDestruction();
		return;
	}

	//
	CreateCATIASection(spiProdRoot);

}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestSectionCmd::~TestSectionCmd()
{
	if (_pGeneralCls!=NULL)
	{
		delete _pGeneralCls;
		_pGeneralCls = NULL;
	}
}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void TestSectionCmd::BuildGraph()
{

}


//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean TestSectionCmd::ActionOne( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------

  return TRUE;
}

HRESULT TestSectionCmd::CreateCATIASection(CATIProduct_var ispiProdRoot)
{
	HRESULT rc = S_OK;
	//
	//��ʼ��ȡCATIASections
	CATIAProduct* piaCATIAPrd = NULL;
	rc = ispiProdRoot ->QueryInterface( IID_CATIAProduct, (void **)&piaCATIAPrd );
	if (FAILED(rc)||piaCATIAPrd==NULL)
	{
		return E_FAIL;
	}
	CATIASections* piaSections = NULL;
	CATUnicodeString    strname = "Sections";
	CATBSTR BSTR;
	strname.ConvertToBSTR(&BSTR );
	CATBaseDispatch* pBaseDis = NULL;
	piaCATIAPrd->GetTechnologicalObject( BSTR, pBaseDis); //��ȡObject����
	pBaseDis->QueryInterface( IID_CATIASections, (void **)&piaSections );
	//����һ��CATISection�����ӵ�CATIASections����
	CATIASection* piaSection = NULL;
	piaSections->Add( piaSection);

	//
	double arrPos[] = {1, 0, 0, 0, 0, 1, 0, -1, 0, 1500, 0, 0};

	long lngSize = 12;
	CATSafeArrayVariant* pSafeArray = BuildSafeArrayVariant(arrPos, lngSize);
	piaSection->put_Height(3000);
	piaSection->put_Width(6000);
	piaSection->put_Type(catSectionTypePlane);
	piaSection->SetPosition(*pSafeArray);

	//
	CATIADocument *piaDoc = NULL;
	piaSection->Export(piaDoc);
	if (piaDoc == NULL)
	{
		return E_FAIL;
	}
	CATBSTR bstrPath;
	piaDoc->get_FullName(bstrPath);

	CATUnicodeString strPath = "";
	strPath.BuildFromBSTR(bstrPath);

	CATSession * pSession = CATSession::GetPtrSession();
	if (pSession==NULL)
	{
		cout<<"GetPtrSession Failed"<<endl;
		return E_FAIL;
	}
	CATIIniInteractiveSession* pInteractiveSession = NULL;
	rc=pSession->QueryInterface(IID_CATIIniInteractiveSession, (void **) &pInteractiveSession);
	if (FAILED(rc)||pInteractiveSession==NULL)
	{
		cout<<"Get CATIIniInteractiveSession Failed"<<endl;
		return E_FAIL;
	}
	CATIEditor* pEditor = NULL;
	pInteractiveSession->Open(strPath, FALSE,&pEditor);
	if (pEditor == NULL)
	{
		cout<<"NewFrom Failed"<<endl;
		return E_FAIL;
	}

	return rc;
}