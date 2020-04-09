// System Framework
#include "CATUnicodeString.h"

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session

//ObjectSpecsModeler Framework
#include "CATCatalogFactoryServices.h"   // CreateCatalog et SaveCatalog global functions
#include "CATICatalog.h"                 // CreateSUInCatalog, SetClientId
#include "CATISpecObject.h"              // AddAttribute
#include "CATISpecAttribute.h"           // Result of AddAttribute

#include "CATOsmSUFactory.h"

//Other includes
#include <iostream.h>

int main()
{
	/*------------------------------------------------------------------*/
	/* Create Session:  CreateCatalog will create a session in case     */
	/* it has not already been created.  You need to delete it at the   */
	/* end regardless of who has created it.                            */
	/*------------------------------------------------------------------*/

	char *sessionName = "Test_Create_Catalog_Sample";
	CATSession *pSession = NULL;
	HRESULT rc = ::Create_Session(sessionName, pSession);
	if ((FAILED(rc)) || (NULL == pSession))
	{
		cout << "ERROR in creating session" << endl << flush;
		return 1;
	}

	/*-----------------------------------------------*/
	/* Create the Catalog that will contain StartUps */
	/*-----------------------------------------------*/

	CATICatalog *piCatalog = NULL;
	CATUnicodeString storageName("TestCatalog.CATfct");
	rc = ::CreateCatalog(&storageName, &piCatalog);
	if (NULL == piCatalog) 
	{
		cout << "ERROR in creating Catalog" << endl << flush;
		return 2;
	}
	else cout << "Catalog created OK" << endl << flush;	

	// Add a client identification to the catalog.  This is a mandatory step. 
	CATUnicodeString clientId("TestFeatExtId");
	rc = piCatalog -> SetClientId(&clientId);
	if (NULL == rc) cout << "ClientID setOK" << endl << flush;
	else cout << "ERROR in setting ClientID" << endl << flush;

	//
	CATUnicodeString StartUpType = "TestExtendPT";
	CATUnicodeString CatalogName = "CATHybridShape";
	CATUnicodeString superTypeName = "GSMGeom";
	CATISpecObject *piSpecOnStartUp = NULL;
	rc = ::CATOsmSUFactory(&piSpecOnStartUp,&StartUpType,piCatalog,&superTypeName,&CatalogName,TRUE,TRUE);
	if (FAILED(rc)||piSpecOnStartUp==NULL)
	{
		cout<<"ERROR in creating Specobj of StartUp"<<endl<<flush;
		return 3;
	}
	//
	CATUnicodeString AttName1("ptX");
	CATISpecAttribute *piAttr1 = NULL;
	piAttr1 = piSpecOnStartUp->AddAttribute(AttName1,tk_double,sp_IN);	//���������������Ҫ�����Ͽ������û����ĵĻ�����Ҫ���Ÿò����仯���ҲҪ�仯�ģ���IN�����ֻ��չʾ������ĵģ���Neutral�����Ҫ���ⵥ���Ҳ�����֮��ģ���OUT
	if (piAttr1!=NULL)
	{
		piAttr1->Release();
		piAttr1=NULL;
	}
	else
	{
		cout<<"==> Create Attribute1 Failed"<<endl;
		return 4;
	}
	CATUnicodeString AttName2("ptY");
	CATISpecAttribute *piAttr2 = NULL;
	piAttr2 = piSpecOnStartUp->AddAttribute(AttName2,tk_double,sp_IN);
	if (piAttr2!=NULL)
	{
		piAttr2->Release();
		piAttr2=NULL;
	}
	else
	{
		cout<<"==> Create Attribute2 Failed"<<endl;
		return 4;
	}
	CATUnicodeString AttName3("ptZ");
	CATISpecAttribute *piAttr3 = NULL;
	piAttr3 = piSpecOnStartUp->AddAttribute(AttName3,tk_double,sp_IN);
	if (piAttr3!=NULL)
	{
		piAttr3->Release();
		piAttr3=NULL;
	}
	else
	{
		cout<<"==> Create Attribute3 Failed"<<endl;
		return 4;
	}

	// Save catalog

	rc = ::SaveCatalog(&piCatalog,&storageName);
	if (NULL != piCatalog)
	{
		piCatalog -> Release();
		piCatalog = NULL;
	}
	if (FAILED(rc))
	{
		cout << "ERROR in saving catalog document" << endl << flush;
		return 5;
	}

	// Delete session

	rc = ::Delete_Session(sessionName);
	if (FAILED(rc))
	{
		cout << "ERROR in deleting session" << endl << flush;
		return 7;
	}

	return 0;

}