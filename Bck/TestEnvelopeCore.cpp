//C++-----------------
#include "iostream.h"
#include <string.h>
//-----------------
#include "TestEnvelopeCore.h"
//CAA-----------------

using namespace std;
TestEnvelopeCore::TestEnvelopeCore()
:m_pParamBase(NULL)
{	
}
//--------------------------------------------------------------------------
TestEnvelopeCore::~TestEnvelopeCore()
{
	m_pParamBase = NULL;
}

CATIProduct_var TestEnvelopeCore::GetDMURootProduct()
{
	cout<<"get dmu doc"<<endl;
	CATDocument		*pCataDoc = NULL;
	char* docPath = "TestPATH";										//保存模版的环境变量名
	char* docPathValue = NULL;										//保存莫班的环境变量对应的路径
	CATLibStatus envState = CATGetEnvValue(docPath,&docPathValue);	//获得保存模版的环境变量的值
	CATUnicodeString strModulePath = docPathValue;
	strModulePath.Append("\\Envelope\\DMU_B.CATProduct");
	cout<<"dmu path:"<<strModulePath<<endl;
	HRESULT hr = CATDocumentServices::OpenDocument(strModulePath,pCataDoc);
	CATIProduct_var piRootProduct = GetRootProduct(pCataDoc);
	return piRootProduct;
}

void TestEnvelopeCore::InsertAndReplaceMovePrd(CATIProduct_var iDMURootProduct,CATIProduct_var iSpMoveProduct,CATIProduct_var &oInstanceProduct)
{
	cout<<"insert moveprd"<<endl;
	HRESULT hr = E_FAIL;

	CATIProduct_var refmoveprd = iSpMoveProduct->GetReferenceProduct();
	cout<<"name:"<<iSpMoveProduct->GetPartNumber()<<endl;
	cout<<"dmu name:"<<iDMURootProduct->GetPartNumber()<<endl;
	CATUnicodeString partname;
	CATListValCATBaseUnknown_var *pChildList=NULL;
	pChildList = iDMURootProduct->GetAllChildren();
	for (int i=1;i<=pChildList->Size();i++)
	{
		CATIProduct_var spTempProduct = (*pChildList)[i];
		partname = spTempProduct->GetPartNumber();
		if (partname=="ChangePart")
		{
			CATIProduct_var refprd = spTempProduct->GetReferenceProduct();
			CATIProduct_var instanceprd = refprd->FindInstance(iDMURootProduct);
			//CATIProduct_var instanceprd2 = NULL_var;
			iDMURootProduct->ReplaceProduct(instanceprd,refmoveprd,oInstanceProduct);
			CATIProductInSession_var spInsession = oInstanceProduct;
			spInsession->SetActiveShapeRep(1,TRUE,FALSE);
			break;
		}
	}
	CATISpecObject_var spObject = iDMURootProduct;
	spObject->Update();
	hr = TestRefreshView3D(spObject);

}

void TestEnvelopeCore::GetAndSetOriginalPoint(CATIProduct_var iDMURootProduct,CATIProduct_var iInstanceProduct)
{
	cout<<"get set original"<<endl;
	CATListValCATISpecObject_var objectList;
	CATIDescendants *pPartAsDescendant=NULL;
	CATISpecObject_var parmset;
	HRESULT rc = iInstanceProduct->QueryInterface(IID_CATIDescendants, (void**)&pPartAsDescendant);
	if( FAILED(rc) || !pPartAsDescendant ) {
		cout << "Error ! Get IID_CATIDescendants interface !" << endl;
	}
	pPartAsDescendant->GetAllChildren("CATISpecObject", objectList);

	//pPartAsDescendant->Release();       pPartAsDescendant = NULL;
	CATIAlias_var spTempAlias;
	for (int j=1;j<=objectList.Size();j++)
	{
		spTempAlias = objectList[j];
		//cout<<spTempAlias->GetAlias()<<endl;
		if (spTempAlias->GetAlias()=="change")
		{
			parmset = objectList[j];
			break;
		}
	}

	objectList.RemoveAll();
	double ix = 0.0;
	double iy = 0.0;
	double iz = 0.0;

	if (parmset!=NULL_var)
	{
		rc = parmset->QueryInterface(IID_CATIDescendants, (void**)&pPartAsDescendant);
		if( FAILED(rc) || !pPartAsDescendant ) {
			cout << "Error ! Get IID_CATIDescendants interface !" << endl;
		}
		pPartAsDescendant->GetAllChildren("CATISpecObject", objectList);

		pPartAsDescendant->Release();       pPartAsDescendant = NULL;
		for (int j=objectList.Size();j>=1;j--)
		{
			spTempAlias = objectList[j];
			if (spTempAlias->GetAlias()=="Original point A")
			{
				CATPoint_var spPoint = TransferPoint(objectList[j]);
				ix = spPoint->GetX();
				iy = spPoint->GetY();
				iz = spPoint->GetZ();
				//cout<<spTempAlias->GetAlias()<<endl;
				break;
			}

		}

	}

	objectList.RemoveAll();
	CATUnicodeString partname;
	CATICkeParm_var spParm=NULL_var;
	CATListValCATBaseUnknown_var *pChildList=NULL;
	pChildList = iDMURootProduct->GetAllChildren();
	for (int i=1;i<=pChildList->Size();i++)
	{
		CATIProduct_var spTempProduct = (*pChildList)[i];
		partname = spTempProduct->GetPartNumber();
		if (partname=="original point A")
		{
			cout<<partname<<endl;
			rc = spTempProduct->QueryInterface(IID_CATIDescendants, (void**)&pPartAsDescendant);
			if( FAILED(rc) || !pPartAsDescendant ) {
				cout << "Error ! Get IID_CATIDescendants interface !" << endl;
			}
			pPartAsDescendant->GetAllChildren("CATISpecObject", objectList);
			cout<<objectList.Size()<<endl;
			for (int k=1;k<=objectList.Size();k++)
			{
				spTempAlias = objectList[k];
				spParm = objectList[k];
				
				if (spTempAlias->GetAlias()=="original point A_X")
				{
					spParm->Valuate(ix/1000);
				}
				if (spTempAlias->GetAlias()=="original point A_Y")
				{
					spParm->Valuate(iy/1000);
				}
				if (spTempAlias->GetAlias()=="original point A_Z")
				{
					spParm->Valuate(iz/1000);
				}
			}
			CATISpecObject_var sptmp = spTempProduct->GetReferenceProduct();
			TestRefreshView3D(sptmp);
			//sptmp->Update();
			break;
		}
	}
}

void TestEnvelopeCore::GetAndSetControlLines(CATIProduct_var iDMURootProduct,CATIProduct_var iInstanceProduct)
{
	cout<<"get set controlline"<<endl;
	CATListValCATISpecObject_var objectList;
	CATIDescendants *pPartAsDescendant=NULL;
	CATISpecObject_var parmset;
	CATISpecObject_var spInputGS;
	CATUnicodeString partname;
	CATICkeParm_var spParm=NULL_var;
	CATIProduct_var spDMUOriginalPrd;
	CATBoolean boolLink=FALSE;
	CATISpecObject_var spSpecYLine=NULL_var;
	CATISpecObject_var spSpecZLine=NULL_var;
	CATISpecObject_var spYLineOriginal;
	CATISpecObject_var spZLineOriginal;
	CATListValCATBaseUnknown_var *pChildList=NULL;
	pChildList = iDMURootProduct->GetAllChildren();
	for (int i=1;i<=pChildList->Size();i++)
	{
		CATIProduct_var spTempProduct = (*pChildList)[i];
		partname = spTempProduct->GetPartNumber();
		if (partname=="original point A")
		{
			spDMUOriginalPrd = spTempProduct;
			break;
		}
	}

	HRESULT rc = spDMUOriginalPrd->QueryInterface(IID_CATIDescendants, (void**)&pPartAsDescendant);
	if( FAILED(rc) || !pPartAsDescendant ) {
		cout << "Error ! Get IID_CATIDescendants interface !" << endl;
	}
	pPartAsDescendant->GetAllChildren("CATISpecObject", objectList);

	//pPartAsDescendant->Release();       pPartAsDescendant = NULL;
	CATIAlias_var spTempAlias;
	for (int j=1;j<=objectList.Size();j++)
	{
		spTempAlias = objectList[j];
		//cout<<spTempAlias->GetAlias()<<endl;
		if (spTempAlias->GetAlias()=="change")
		{
			spInputGS = objectList[j];
			break;
		}
	}

	objectList.RemoveAll();

	rc = iInstanceProduct->QueryInterface(IID_CATIDescendants, (void**)&pPartAsDescendant);
	if( FAILED(rc) || !pPartAsDescendant ) {
		cout << "Error ! Get IID_CATIDescendants interface !" << endl;
	}
	pPartAsDescendant->GetAllChildren("CATISpecObject", objectList);

	//pPartAsDescendant->Release();       pPartAsDescendant = NULL;
	//CATIAlias_var spTempAlias;
	for (int j=1;j<=objectList.Size();j++)
	{
		spTempAlias = objectList[j];
		//cout<<spTempAlias->GetAlias()<<endl;
		if (spTempAlias->GetAlias()=="change")
		{
			parmset = objectList[j];
			break;
		}
	}

	objectList.RemoveAll();

	if (parmset!=NULL_var)
	{
		rc = parmset->QueryInterface(IID_CATIDescendants, (void**)&pPartAsDescendant);
		if( FAILED(rc) || !pPartAsDescendant ) {
			cout << "Error ! Get IID_CATIDescendants interface !" << endl;
		}
		pPartAsDescendant->GetAllChildren("CATISpecObject", objectList);

		pPartAsDescendant->Release();       pPartAsDescendant = NULL;
		for (int j=objectList.Size();j>=1;j--)
		{
			spTempAlias = objectList[j];
			if (spTempAlias->GetAlias()=="Y")
			{
				cout<<"copy Y"<<endl;
				CopyBodyToPart(objectList[j],spInputGS,iInstanceProduct,spDMUOriginalPrd,FALSE,spSpecYLine);
			
			cout<<spTempAlias->GetAlias()<<endl;
			break;
			}
		}

		for (int k=objectList.Size();k>=1;k--)
		{
			spTempAlias = objectList[k];
			if (spTempAlias->GetAlias()=="Z")
			{
				//spZLineOriginal = objectList[j];
				cout<<"copy Z"<<endl;
				CopyBodyToPart(objectList[k],spInputGS,iInstanceProduct,spDMUOriginalPrd,FALSE,spSpecZLine);
			
			cout<<spTempAlias->GetAlias()<<endl;
			break;
			}
		}
	}

	if (spInputGS!=NULL_var)
	{
		rc = spInputGS->QueryInterface(IID_CATIDescendants, (void**)&pPartAsDescendant);
		if( FAILED(rc) || !pPartAsDescendant ) {
			cout << "Error ! Get IID_CATIDescendants interface !" << endl;
		}
		pPartAsDescendant->GetAllChildren("CATISpecObject", objectList);

		pPartAsDescendant->Release();       pPartAsDescendant = NULL;
		for (int j=objectList.Size();j>=1;j--)
		{
			spTempAlias = objectList[j];
			if (spTempAlias->GetAlias()=="Y")
			{
				spYLineOriginal = objectList[j];
				ReplaceFeature(spYLineOriginal,spSpecYLine);
			
			cout<<"replace:"<<spTempAlias->GetAlias()<<endl;
			break;
			}
		}

		for (int k=objectList.Size();k>=1;k--)
		{
			spTempAlias = objectList[k];
			if (spTempAlias->GetAlias()=="Z")
			{
				spZLineOriginal = objectList[k];
				ReplaceFeature(spZLineOriginal,spSpecZLine);
			
			cout<<"replace:"<<spTempAlias->GetAlias()<<endl;
			break;
			}
		}
	}
	TestRefreshView3D(spInputGS);
	TestRefreshView3D(spDMUOriginalPrd);
}

CATIProduct_var TestEnvelopeCore::GetRootProduct(CATDocument * piDocument)
{
	HRESULT rc = S_FALSE;
	CATIProduct_var spRootProduct = NULL_var;
	if ( NULL != piDocument)
	{
		CATIDocRoots *piDocRootsOnDoc = NULL;
		rc = piDocument->QueryInterface(IID_CATIDocRoots,(void**) &piDocRootsOnDoc);

		if ( FAILED(rc) )
		{
			cout << "Querry on CATIDocRoots interface failed " << endl<< flush;
			return NULL_var;
		}

		CATListValCATBaseUnknown_var *pRootProducts = piDocRootsOnDoc->GiveDocRoots();
		if ( NULL != pRootProducts)
			if (pRootProducts->Size())
			{  
				spRootProduct = (*pRootProducts)[1];//取得链表的第一个元素就是root的顶元素
				delete pRootProducts;
				pRootProducts = NULL;
			}
			piDocRootsOnDoc->Release();
			piDocRootsOnDoc=NULL;
	}
	return spRootProduct;
}

HRESULT TestEnvelopeCore::TestRefreshView3D(CATISpecObject_var ispiSpecOnObject)
{
	HRESULT rc=E_FAIL;

	if( !ispiSpecOnObject ) return rc;

	ispiSpecOnObject->Update();

	CATISpecObject *piFather=NULL;
	piFather = ispiSpecOnObject->GetFather();

	CATModify pModifyOnFather(piFather);
	CATIModelEvents_var spiModelEvents(piFather);
	if( !!spiModelEvents ) {
		spiModelEvents->Dispatch(pModifyOnFather);
		rc = S_OK;
	}

	CATIRedrawEvent_var spRedraw(piFather);
	if(spRedraw != NULL_var) {
		spRedraw->Redraw();
	}	

	if( !!piFather ) { piFather->Release();  piFather = NULL; }

	return rc;
}

CATPoint_var TestEnvelopeCore::TransferPoint(const CATISpecObject_var& ispPoint)
{
	CATPoint_var spPoint = NULL_var;
	CATBody_var PointBody = NULL_var;
	PointBody = GetBodyFromFeature(ispPoint);
	CATLISTP(CATCell) LISTCell; 
	PointBody->GetAllCells( LISTCell, 0 ); 
	//cout<<LISTCell.Size()<<endl<<flush;
	for( int index = 1; index <= LISTCell.Size(); index++ ){ 
		CATCell *pPointCell = LISTCell[index]; 
		if(!pPointCell){ 
			continue; 
		} 
		CATCell_var spPointCell = pPointCell; 
		if(!spPointCell){ 
			continue; 
		};
		CATVertex_var spVertex=spPointCell;
		spPoint = spVertex ->GetPoint();
		//HRESULT rc = spVertex ->QueryInterface(IID_CATPoint,(void**)&spPoint);
		if( !spPoint ){ 
			continue; 
		} 
	}
	return spPoint;
}

CATBody_var TestEnvelopeCore::GetBodyFromFeature(const CATISpecObject_var& ispFeature)
{
	CATBody_var spBody = NULL_var;
	do {
		if( !ispFeature ) {
			break;
		}
		CATIMfBRep_var spBRepOnFeature = ispFeature;
		if( !!spBRepOnFeature ) {
			spBody = spBRepOnFeature->GetBody();
		}
		else {
			CATIGeometricalElement_var spGeometricalElementOnFeature = ispFeature;
			if( !spGeometricalElementOnFeature ) {
				break;
			}
			spBody = spGeometricalElementOnFeature->GetBodyResult();
		}
		if( !spBody ) {
			break;
		}
	} while(FALSE);
	return spBody;


}

HRESULT TestEnvelopeCore::ReplaceFeature(CATISpecObject_var ispSpecObjectOrigin,CATISpecObject_var ispSpecObjectToReplace)
{
	HRESULT hr=E_FAIL;

	CATIReplace_var spReplace=NULL_var;
	CATISpecAttrAccess_var spSpecAttrAccess=NULL_var;
	CATListValCATBaseUnknown_var *pListBU=NULL;
	CATListValCATISpecAttrKey_var listValCATISpecAttrKey;
	CATListValCATUnicodeString *pNameList=NULL;

	spSpecAttrAccess=ispSpecObjectOrigin;
	//CATIAlias_var spAlias=ispSpecObjectOrigin;
	//cout<<"object:"<<spAlias->GetAlias()<<endl;
	pListBU=spSpecAttrAccess->ListPointingObjects(IID_CATISpecObject);
	pNameList = spSpecAttrAccess->ListAttrNames();

	for(int i=1;i<=pListBU->Size();i++)
	{
		CATIAlias_var spAlias=(*pListBU)[i];
		//cout<<"object:"<<spAlias->GetAlias()<<endl;
		if(spAlias->GetAlias()=="BaseBody") continue;

		CATUnicodeString strAttrName="";
		CATISpecObject_var spSpecInput=NULL_var;
		CATISpecObject_var spSpecReplace=(*pListBU)[i];
		cout << i << "\t" << spAlias->GetAlias() << "\t" << spSpecReplace->GetType() << endl;
		//OutputPathOfFeature(spSpecReplace);

		CATBoolean isFind=FALSE;
		spSpecAttrAccess=spSpecReplace;
		hr=spSpecAttrAccess->ListAttrKeys(listValCATISpecAttrKey);
		for(int n=1;n<=listValCATISpecAttrKey.Size();n++)
		{
			CATISpecAttrKey_var spAttrKey=listValCATISpecAttrKey[n];
			if(NULL_var==spAttrKey) continue;

			CATAttrKind attrKind=spAttrKey->GetType();
			if(attrKind==tk_specobject)
			{
				spSpecInput=spSpecAttrAccess->GetSpecObject(spAttrKey);
				if(NULL_var==spSpecInput) continue;

				CATIAlias_var spAlias=spSpecInput;
				cout<<"object input:"<<spAlias->GetAlias()<<endl;
				if(spSpecInput->IsEqual(ispSpecObjectOrigin)==1)
				{				
					strAttrName=spAttrKey->GetName();
					isFind=TRUE;break;
				}
			}
			if(attrKind==tk_string)
			{
				CATUnicodeString Input=spSpecAttrAccess->GetString(spAttrKey);

			}
		}
		if(isFind)
		{
			CATIAlias_var spAlias = spSpecReplace;
			cout<<"replace obj:"<<spAlias->GetAlias()<<endl;
			spReplace=spSpecReplace;
			hr=spReplace->Replace(strAttrName,ispSpecObjectToReplace);
			if(SUCCEEDED(hr))
			{
				cout << "\tReplace OK!" << endl;
				//spSpecReplace->Update();
			}
			else cout << "\tReplace Failed!" << endl;
			continue;
		}
	
	}
	delete pListBU;pListBU=NULL;

	return S_OK;
}

HRESULT TestEnvelopeCore::CopyBodyToPart(CATISpecObject_var ispSpec,CATISpecObject_var ispTarget,CATIProduct_var ispSP,CATIProduct_var ispTP,CATBoolean iLink,CATISpecObject_var& ospSpec)
{
	HRESULT rc=S_OK;
	ospSpec=NULL_var;
	CATMmrInterPartCopy * ptCATMmrInterPartCopy = NULL ;

	ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (ispSpec,ispTarget) ;
	ptCATMmrInterPartCopy ->SetSourceInstance(ispSP);
	ptCATMmrInterPartCopy ->SetTargetInstance(ispTP);
	ptCATMmrInterPartCopy ->SetLinkMode(iLink) ;
	ptCATMmrInterPartCopy ->SetAttributeMode(3);

	// Executes the copy
	CATUnicodeString ErrorMsg ;
	rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
	if ( FAILED(rc) )
	{
		cout << "SKMouldCorPinCmd::CopyBodyToPart ==> " << ErrorMsg << endl;
		return E_FAIL;
	}

	rc = ptCATMmrInterPartCopy ->GetResult(ospSpec);
	return rc;
}

HRESULT TestEnvelopeCore::CreateSweptVolume(CATDocument *ipDoc)
{

	//CATUnicodeString strModulePath = "E:\\tmp\\envelope\\DMU.CATProduct";
	//rc = CATDocumentServices::SaveAs(*ipDoc,strModulePath);
	//CATDocument *ipDoc = NULL;
	//HRESULT rc = CATDocumentServices::OpenDocument(strModulePath,ipDoc);
	CATIProduct_var piRootProduct = GetRootProduct(ipDoc);

	CATIProduct_var spDMUOriginalPrd;
	CATIProduct_var spDMUChangePrd;
	CATListValCATBaseUnknown_var *pChildList=NULL;
	pChildList = piRootProduct->GetAllChildren();
	for (int i=1;i<=pChildList->Size();i++)
	{
		CATIProduct_var spTempProduct = (*pChildList)[i];
		CATUnicodeString partname = spTempProduct->GetPartNumber();
		if (partname=="original point A")
		{
			spDMUOriginalPrd = spTempProduct->GetReferenceProduct();
			break;
		}
	}

	for (int j=1;j<=pChildList->Size();j++)
	{
		CATIProduct_var spTempProduct = (*pChildList)[j];
		CATUnicodeString partname = spTempProduct->GetPartNumber();
		if (partname=="Part1")
		{
			spDMUChangePrd = spTempProduct;
			break;
		}
	}

	//iLISTProdOfSwepTPart.RemoveAll();
	CATLISTP(CATIProduct) iLISTProdOfSwepTPart;
	iLISTProdOfSwepTPart.Append(spDMUChangePrd);
	//1、获得Replay
	//ReplayFactory
	CATIReplayFactory * piReplayFactory = NULL;
	HRESULT rc = ipDoc->QueryInterface(IID_CATIReplayFactory, (void**)&piReplayFactory);
	if(FAILED(rc) || piReplayFactory==NULL)
	{
		cout<<"Failed QI piReplayFactory"<<endl;
		return rc;
	}
	else
		cout<<"Succeed QI piReplayFactory"<<endl;

	//Replay List
	CATIReplayList* piListOfReplays = new CATIReplayList();
	rc = piReplayFactory->ListReplays (piListOfReplays);
	if(FAILED(rc))
	{
		cout<<"Failed ListReplays"<<endl;
		return rc;
	}

	//first Replay
	CATIReplay * piReplay = NULL;
	if( piListOfReplays->Size() > 0 ) 
	{
		piReplay = (*piListOfReplays)[1];
		if(piReplay==NULL)
		{
			cout<<"piReplay == NULL"<<endl;
			return rc;
		}
	}else
	{
		piReplayFactory->CreateInstance(&piReplay);
	}
	delete piListOfReplays;
	piListOfReplays = NULL;



	CATIAReplay * piCATIAReplay = NULL;
	rc = piReplay->QueryInterface(IID_CATIAReplay, (void **)&piCATIAReplay);
	if(FAILED(rc) || piCATIAReplay==NULL)
	{
		cout<<"Failed QI piCATIAReplay"<<endl;
		return rc;
	}
	else
		cout<<"Succeed QI piCATIAReplay"<<endl;

	//2、获得需要创建包络的product	
	//CATIProduct_var spRootPrd = spRootProduct;//获得Root Product
	//CATListValCATBaseUnknown_var * pListPrd = spRootPrd->GetAllChildren();

	//CATIProduct_var spPrdSweptRef;
	////spPrdSweptRef = ispFixedProduct;
	//if (NULL_var==spPrdSweptRef)
	//{
	//	cout<<"NULL_var==spPrdSweptRef"<<endl;
	//}

	CATIAProduct * iProductReference=NULL;
	rc = spDMUOriginalPrd->QueryInterface(IID_CATIAProduct, (void **)&iProductReference);
	if(FAILED(rc) || iProductReference==NULL)
	{
		cout<<"Failed QI iProductReference"<<endl;
		return rc;
	}
	else
		cout<<"Succeed QI iProductReference"<<endl;


	//3、获得创建包络的接口
	//SweptVolumeFactory
	CATISweptVolumeFactory * piSweptVolumeFactory = NULL;
	rc = ipDoc->QueryInterface(IID_CATISweptVolumeFactory, (void **)&piSweptVolumeFactory);
	if(FAILED(rc) || piSweptVolumeFactory==NULL)
	{
		cout<<"Failed QI piSweptVolumeFactory"<<endl;
		return rc;
	}
	else
		cout<<"Succeed QI piSweptVolumeFactory"<<endl;

	//4、创建包络

	//输入列表
	//将需要创建包络的product转为basedispatch格式

	int NumOfSwepTPart=iLISTProdOfSwepTPart.Size();
	cout<<"需要计算的包络体个数："<<NumOfSwepTPart<<endl;
	CATBaseDispatch ** iObjectArray = new CATBaseDispatch *[NumOfSwepTPart];

	for (int i=0;i<NumOfSwepTPart;i++)
	{

		CATIProduct_var spPrdSwept1;
		//CATIProduct_var spPrdSwept2;
		//CATIProduct_var spPrdSwept3;

		spPrdSwept1 = iLISTProdOfSwepTPart[i+1];
		if (NULL_var==spPrdSwept1)
		{
			cout<<"NULL_var==spPrdSwept1"<<endl;
		}

		CATBaseDispatch * iBaseDispatch1 = NULL;
		rc = spPrdSwept1->QueryInterface(IID_CATBaseDispatch, (void**)&iBaseDispatch1);
		if(FAILED(rc) || iBaseDispatch1==NULL)
		{
			cout<<"Failed QI iBaseDispatch1"<<endl;
			return rc;
		}
		else
			cout<<"Succeed QI iBaseDispatch1"<<endl;


		if (iBaseDispatch1==NULL)
		{
			cout<<"Failed QI iBaseDispatch1"<<endl;

		}

		iObjectArray[i] = iBaseDispatch1;



	}

	CATSafeArrayVariant * pArrayVariant = BuildSafeArrayVariant((const CATBaseDispatch **)iObjectArray, NumOfSwepTPart);

	cout<<"1"<<endl;

	//输出列表
	CATBaseDispatch ** iObjectArrayOut = new CATBaseDispatch *[NumOfSwepTPart];
	for (int i=0;i<NumOfSwepTPart;i++)
	{
		iObjectArrayOut[i] = NULL;


	}
	//iObjectArrayOut[1] = NULL;
	//iObjectArrayOut[2] = NULL;
	CATSafeArrayVariant * oSweptVolumeDocuments=
		::BuildSafeArrayVariant((const CATBaseDispatch **)iObjectArrayOut,NumOfSwepTPart);

	cout<<"2"<<endl;

	//创建包络
	//CATSafeArrayVariant oSweptVolumeDocuments;
	if (NULL==piCATIAReplay)
	{
		cout<<"NULL==piCATIAReplay"<<endl;
	}
	if (NULL==iProductReference)
	{
		cout<<"NULL==iProductReference"<<endl;
	}
	cout<<"ComputeSweptVolumesFromReplay之前"<<endl;
	rc = piSweptVolumeFactory->ComputeSweptVolumesFromReplay(piCATIAReplay, 
		*pArrayVariant,iProductReference, 0, 0.200000, 0, 0, -1.000000, -1.000000, -1.000000, *oSweptVolumeDocuments);
	cout<<"ComputeSweptVolumesFromReplay之后"<<endl;

	cout<<"3"<<endl;
	if(FAILED(rc))
	{
		cout<<"Failed ComputeSweptVolumesFromReplay"<<endl;
		//RDCDMUBFErrorMsgBox("生成包络体失败");
		return rc;
	}
	else
		cout<<"Succeed ComputeSweptVolumesFromReplay"<<endl;

	//输出列表长度
	long arraySize = GetVariantArraySize(oSweptVolumeDocuments);
	cout<<"arraySize: "<<arraySize<<endl;

	//获得输出的包络列表
	CATBaseDispatch ** ioObjectArrayOut = new CATBaseDispatch *[arraySize];
	//long ret = ConvertSafeArrayVariant(pArrayVariant, ioObjectArrayOut, 3);
	long ret = ConvertSafeArrayVariant(oSweptVolumeDocuments,ioObjectArrayOut,1);
	cout<<"ret: "<<ret<<endl;

	//cout<<ioObjectArrayOut[0]<<endl;
	//cout<<ioObjectArrayOut[1]<<endl;
	//cout<<ioObjectArrayOut[2]<<endl;

	for (int i=0;i<arraySize;i++)
	{
		CATIADocument_var spADoc = NULL_var; 
		if ( ret > 0 ) 
		{ 
			spADoc = ioObjectArrayOut[i]; 
		} 
		if ( !!spADoc ) 
		{ 
			rc = spADoc->Activate();
			rc = spADoc->Save();

			CATUnicodeString ioPath = "E:\\tmp\\envelope\\Rod.1_.cgr";

			//int index=ioPath.SearchSubString(".cgr",0,CATUnicodeString::CATSearchModeBackward);

			////获取时间
			//time_t rawtime;

			//time ( &rawtime );
			////printf("%ld\n", &rawtime);
			////printf ( "The current local time is: %s", ctime (&rawtime) );

			//char * time = ctime(&rawtime);
			////ctime(&rawtime) : time_t/timestampe -> "Www Mmm dd hh:mm:ss yyyy" format
			//cout<< time << endl;


			//struct tm * ptm;
			//ptm = gmtime(&rawtime);

			//cout<<(ptm->tm_year + 1900)<<"year "<<(ptm->tm_mon + 1)<<"month "<<(ptm->tm_mday)<<"day "<<(ptm
			//	->tm_hour)<<":"<<(ptm->tm_min)<<":"<<(ptm->tm_sec)<<endl;
			//CATUnicodeString timeyear;
			//CATUnicodeString timemonth;
			//CATUnicodeString timeday;
			//CATUnicodeString timehour;
			//CATUnicodeString timemin;
			//CATUnicodeString timesec;

			//timeyear.BuildFromNum(ptm->tm_year + 1900);
			//timemonth.BuildFromNum(ptm->tm_mon + 1);
			//timeday.BuildFromNum(ptm->tm_mday);
			//timehour.BuildFromNum(ptm->tm_hour+8);
			//timemin.BuildFromNum(ptm->tm_min);
			//timesec.BuildFromNum(ptm->tm_sec);


			//CATUnicodeString timestamp;
			////timestamp.BuildFromNum(i);
			//timestamp=timeyear+timemonth+timeday+timehour+timemin+timesec;

			//cout<<"timestamp="<<timestamp<<endl;
			//ioPath.Insert(index,timestamp);

			//cout<<"1"<<endl;
			CATBSTR bstrFullPath;
			ioPath.ConvertToBSTR(&bstrFullPath);//strFullPath
			//cout<<"12"<<endl;

			rc = spADoc->SaveAs(bstrFullPath);
			//cout<<"rc="<<rc<<endl;
			//cout<<"122"<<endl;
			//if (FAILED(rc))
			//{
			//	cout<<"保存cgr失败！！！！"<<endl;
			//	return rc;
			//}
			cout<<"123"<<endl;

		} 
		else
			cout<<"spADoc = NULL"<<endl;

	}

	return TRUE;
}

HRESULT TestEnvelopeCore::CreateSweptVolume(CATIProduct_var ispDMUprd,CATListValCATISpecObject_var iLISTProdOfSwepTPart,CATUnicodeString &ioPath)
{
	//CATIProduct_var spDMUOriginalPrd;
	//CATListValCATBaseUnknown_var *pChildList=NULL;
	//pChildList = ispDMUprd->GetAllChildren();
	//for (int i=1;i<=pChildList->Size();i++)
	//{
	//	CATIProduct_var spTempProduct = (*pChildList)[i];
	//	CATUnicodeString partname = spTempProduct->GetPartNumber();
	//	if (partname=="original point A")
	//	{
	//		spDMUOriginalPrd = spTempProduct;
	//		break;
	//	}
	//}

	CATIProduct_var spPrdSkeletonRef=ispDMUprd->GetReferenceProduct();
	CATILinkableObject_var spPrdLink=spPrdSkeletonRef;
	CATDocument *ipDoc=spPrdLink->GetDocument();

	CATIKinMechanism* piMechanism2 = NULL;
	CATIKinMechanismFactory* piMechanism2FactoryOnDocument = NULL;
	HRESULT rc = ipDoc->QueryInterface(IID_CATIKinMechanismFactory,(void**)&piMechanism2FactoryOnDocument);
	if (SUCCEEDED(rc))
	{
		CATLISTP(CATBaseUnknown) ListOfMechanisms;
		rc = piMechanism2FactoryOnDocument->ListInstances (ListOfMechanisms);
		if (SUCCEEDED(rc))
		{
			// Read all the mechanisms of the document
			int nbMechanisms = ListOfMechanisms.Size();
			CATBaseUnknown * pMechanism_bu = NULL;

			pMechanism_bu = ListOfMechanisms[nbMechanisms];//最初用的是pMechanism_bu = ListOfMechanisms[1];
			CATUnicodeString fixedprd;
			double UpperLimit1=0;
			if (pMechanism_bu &&
				SUCCEEDED(pMechanism_bu->QueryInterface(IID_CATIKinMechanism,(void**)&piMechanism2)))
			{

				
				CATLISTP(CATBaseUnknown)* cmdList = NULL;
				CATBaseUnknown * pCmd_bu = NULL;
				rc = piMechanism2->GetCmdList(&cmdList);
				if (SUCCEEDED(rc) && cmdList)
				{
					cout << "   Command" <<endl << flush;

					int nbCmds = cmdList->Size();
					for (int l = 1;l<=nbCmds;l++)
					{
						cout << "      " << l << " : ";
						CATIKinCmd* piCmd = NULL;
						pCmd_bu = (*cmdList)[l];

						if (pCmd_bu)
						{
							if (SUCCEEDED(pCmd_bu->QueryInterface(IID_CATIKinCmd,(void**)&piCmd)))
							{

								// Get the command type
								const char* cmdType = NULL;
								rc =piCmd->GetType(&cmdType);
								if (SUCCEEDED(rc)) 
								{
									cout << cmdType << "; ";
								}

								// Get the joint associated to the command
								CATIKinJoint* papiAssociatedJoint = NULL; 
								rc =piCmd->GetJoint(&papiAssociatedJoint);
								if (SUCCEEDED(rc))
								{

									cout<< "joint Ok;";
									const char* jointType = NULL;
									CATLISTP(CATBaseUnknown)* oConnectors =NULL;
									//papiAssociatedJoint->GetType(&jointType);
									//cout<<jointType<<endl;
									papiAssociatedJoint->GetConnectors(&oConnectors);
									cout<<"joint connectors:"<<oConnectors->Size();

									papiAssociatedJoint->Release();
									papiAssociatedJoint = NULL;
								}
								cout << endl << flush;
								piCmd->Release();
								piCmd = NULL;
							}
							pCmd_bu->Release();
							pCmd_bu = NULL;
						}
					}
					cout << "   EndCommand" << endl << flush;

					if (cmdList)
					{
						delete cmdList;
						cmdList = NULL;
					}
				}
				piMechanism2->UpdateAllJoints();
			}
		}
	}
	//CATDocument *ipDoc = NULL;
	CATUnicodeString strModulePath = "E:\\tmp\\envelope\\DMU.CATProduct";
	rc = CATDocumentServices::SaveAs(*ipDoc,strModulePath,"",TRUE);

	//HRESULT rc = CATDocumentServices::OpenDocument(strModulePath,ipDoc);
	CATIProduct_var piRootProduct = GetRootProduct(ipDoc);

	CATIProduct_var spDMUOriginalPrd;
	CATIProduct_var spDMUChangePrd;
	CATListValCATBaseUnknown_var *pChildList=NULL;
	pChildList = piRootProduct->GetAllChildren();
	for (int i=1;i<=pChildList->Size();i++)
	{
		CATIProduct_var spTempProduct = (*pChildList)[i];
		CATUnicodeString partname = spTempProduct->GetPartNumber();
		if (partname=="original point A")
		{
			spDMUOriginalPrd = spTempProduct->GetReferenceProduct();
			break;
		}
	}

	for (int j=1;j<=pChildList->Size();j++)
	{
		CATIProduct_var spTempProduct = (*pChildList)[j];
		CATUnicodeString partname = spTempProduct->GetPartNumber();
		if (partname=="Part1")
		{
			spDMUChangePrd = spTempProduct;
			break;
		}
	}

	iLISTProdOfSwepTPart.RemoveAll();
	iLISTProdOfSwepTPart.Append(spDMUChangePrd);
	//1、获得Replay
	//ReplayFactory
	CATIReplayFactory * piReplayFactory = NULL;
	rc = ipDoc->QueryInterface(IID_CATIReplayFactory, (void**)&piReplayFactory);
	if(FAILED(rc) || piReplayFactory==NULL)
	{
		cout<<"Failed QI piReplayFactory"<<endl;
		return rc;
	}
	else
		cout<<"Succeed QI piReplayFactory"<<endl;

	//Replay List
	CATIReplayList* piListOfReplays = new CATIReplayList();
	rc = piReplayFactory->ListReplays (piListOfReplays);
	if(FAILED(rc))
	{
		cout<<"Failed ListReplays"<<endl;
		return rc;
	}

	//first Replay
	CATIReplay * piReplay = NULL;
	if( piListOfReplays->Size() > 0 ) 
	{
		piReplay = (*piListOfReplays)[1];
		if(piReplay==NULL)
		{
			cout<<"piReplay == NULL"<<endl;
			return rc;
		}
	}else
	{
		piReplayFactory->CreateInstance(&piReplay);
	}
	delete piListOfReplays;
	piListOfReplays = NULL;



	CATIAReplay * piCATIAReplay = NULL;
	rc = piReplay->QueryInterface(IID_CATIAReplay, (void **)&piCATIAReplay);
	if(FAILED(rc) || piCATIAReplay==NULL)
	{
		cout<<"Failed QI piCATIAReplay"<<endl;
		return rc;
	}
	else
		cout<<"Succeed QI piCATIAReplay"<<endl;

	//2、获得需要创建包络的product	
	//CATIProduct_var spRootPrd = spRootProduct;//获得Root Product
	//CATListValCATBaseUnknown_var * pListPrd = spRootPrd->GetAllChildren();

	//CATIProduct_var spPrdSweptRef;
	////spPrdSweptRef = ispFixedProduct;
	//if (NULL_var==spPrdSweptRef)
	//{
	//	cout<<"NULL_var==spPrdSweptRef"<<endl;
	//}

	CATIAProduct * iProductReference=NULL;
	rc = spDMUOriginalPrd->QueryInterface(IID_CATIAProduct, (void **)&iProductReference);
	if(FAILED(rc) || iProductReference==NULL)
	{
		cout<<"Failed QI iProductReference"<<endl;
		return rc;
	}
	else
		cout<<"Succeed QI iProductReference"<<endl;


	//3、获得创建包络的接口
	//SweptVolumeFactory
	CATISweptVolumeFactory * piSweptVolumeFactory = NULL;
	rc = ipDoc->QueryInterface(IID_CATISweptVolumeFactory, (void **)&piSweptVolumeFactory);
	if(FAILED(rc) || piSweptVolumeFactory==NULL)
	{
		cout<<"Failed QI piSweptVolumeFactory"<<endl;
		return rc;
	}
	else
		cout<<"Succeed QI piSweptVolumeFactory"<<endl;

	//4、创建包络

	//输入列表
	//将需要创建包络的product转为basedispatch格式
	
	int NumOfSwepTPart=iLISTProdOfSwepTPart.Size();
	cout<<"需要计算的包络体个数："<<NumOfSwepTPart<<endl;
	CATBaseDispatch ** iObjectArray = new CATBaseDispatch *[NumOfSwepTPart];

	for (int i=0;i<NumOfSwepTPart;i++)
	{

		CATIProduct_var spPrdSwept1;
		//CATIProduct_var spPrdSwept2;
		//CATIProduct_var spPrdSwept3;

		spPrdSwept1 = iLISTProdOfSwepTPart[i+1];
		if (NULL_var==spPrdSwept1)
		{
			cout<<"NULL_var==spPrdSwept1"<<endl;
		}

		CATBaseDispatch * iBaseDispatch1 = NULL;
		rc = spPrdSwept1->QueryInterface(IID_CATBaseDispatch, (void**)&iBaseDispatch1);
		if(FAILED(rc) || iBaseDispatch1==NULL)
		{
			cout<<"Failed QI iBaseDispatch1"<<endl;
			return rc;
		}
		else
			cout<<"Succeed QI iBaseDispatch1"<<endl;


		if (iBaseDispatch1==NULL)
		{
			cout<<"Failed QI iBaseDispatch1"<<endl;

		}

		iObjectArray[i] = iBaseDispatch1;



	}

	CATSafeArrayVariant * pArrayVariant = BuildSafeArrayVariant((const CATBaseDispatch **)iObjectArray, NumOfSwepTPart);

	cout<<"1"<<endl;

	//输出列表
	CATBaseDispatch ** iObjectArrayOut = new CATBaseDispatch *[NumOfSwepTPart];
	for (int i=0;i<NumOfSwepTPart;i++)
	{
		iObjectArrayOut[i] = NULL;


	}
	//iObjectArrayOut[1] = NULL;
	//iObjectArrayOut[2] = NULL;
	CATSafeArrayVariant * oSweptVolumeDocuments=
		::BuildSafeArrayVariant((const CATBaseDispatch **)iObjectArrayOut,NumOfSwepTPart);

	cout<<"2"<<endl;

	//创建包络
	//CATSafeArrayVariant oSweptVolumeDocuments;
	//if (NULL==piCATIAReplay)
	//{
	//	cout<<"NULL==piCATIAReplay"<<endl;
	//}
	if (NULL==iProductReference)
	{
		cout<<"NULL==iProductReference"<<endl;
	}
	cout<<"ComputeSweptVolumesFromReplay之前"<<endl;
	rc = piSweptVolumeFactory->ComputeSweptVolumesFromReplay(piCATIAReplay, 
		*pArrayVariant,iProductReference, 0, 0.200000, 0, 0, -1.000000, -1.000000, -1.000000, *oSweptVolumeDocuments);
	cout<<"ComputeSweptVolumesFromReplay之后"<<endl;

	cout<<"3"<<endl;
	if(FAILED(rc))
	{
		cout<<"Failed ComputeSweptVolumesFromReplay"<<endl;
		//RDCDMUBFErrorMsgBox("生成包络体失败");
		return rc;
	}
	else
		cout<<"Succeed ComputeSweptVolumesFromReplay"<<endl;

	//输出列表长度
	long arraySize = GetVariantArraySize(oSweptVolumeDocuments);
	cout<<"arraySize: "<<arraySize<<endl;

	//获得输出的包络列表
	CATBaseDispatch ** ioObjectArrayOut = new CATBaseDispatch *[arraySize];
	//long ret = ConvertSafeArrayVariant(pArrayVariant, ioObjectArrayOut, 3);
	long ret = ConvertSafeArrayVariant(oSweptVolumeDocuments,ioObjectArrayOut,1);
	cout<<"ret: "<<ret<<endl;

	//cout<<ioObjectArrayOut[0]<<endl;
	//cout<<ioObjectArrayOut[1]<<endl;
	//cout<<ioObjectArrayOut[2]<<endl;

	for (int i=0;i<arraySize;i++)
	{
		CATIADocument_var spADoc = NULL_var; 
		if ( ret > 0 ) 
		{ 
			spADoc = ioObjectArrayOut[i]; 
		} 
		if ( !!spADoc ) 
		{ 
			rc = spADoc->Activate();
			rc = spADoc->Save();

			//CATUnicodeString strFullPath = "E:\\项目\\上汽商用车\\滑移门\\afterdlgFailed\\Test\\Rod.1_.cgr";

			int index=ioPath.SearchSubString(".cgr",0,CATUnicodeString::CATSearchModeBackward);

			//获取时间
			time_t rawtime;

			time ( &rawtime );
			//printf("%ld\n", &rawtime);
			//printf ( "The current local time is: %s", ctime (&rawtime) );

			char * time = ctime(&rawtime);
			//ctime(&rawtime) : time_t/timestampe -> "Www Mmm dd hh:mm:ss yyyy" format
			cout<< time << endl;


			struct tm * ptm;
			ptm = gmtime(&rawtime);

			cout<<(ptm->tm_year + 1900)<<"year "<<(ptm->tm_mon + 1)<<"month "<<(ptm->tm_mday)<<"day "<<(ptm
				->tm_hour)<<":"<<(ptm->tm_min)<<":"<<(ptm->tm_sec)<<endl;
			CATUnicodeString timeyear;
			CATUnicodeString timemonth;
			CATUnicodeString timeday;
			CATUnicodeString timehour;
			CATUnicodeString timemin;
			CATUnicodeString timesec;

			timeyear.BuildFromNum(ptm->tm_year + 1900);
			timemonth.BuildFromNum(ptm->tm_mon + 1);
			timeday.BuildFromNum(ptm->tm_mday);
			timehour.BuildFromNum(ptm->tm_hour+8);
			timemin.BuildFromNum(ptm->tm_min);
			timesec.BuildFromNum(ptm->tm_sec);


			CATUnicodeString timestamp;
			//timestamp.BuildFromNum(i);
			timestamp=timeyear+timemonth+timeday+timehour+timemin+timesec;

			cout<<"timestamp="<<timestamp<<endl;
			ioPath.Insert(index,timestamp);

			cout<<"1"<<endl;
			CATBSTR bstrFullPath;
			ioPath.ConvertToBSTR(&bstrFullPath);//strFullPath
			cout<<"12"<<endl;

			rc = spADoc->SaveAs(bstrFullPath);
			cout<<"rc="<<rc<<endl;
			cout<<"122"<<endl;
			if (FAILED(rc))
			{
				cout<<"保存cgr失败！！！！"<<endl;
				return rc;
			}
			cout<<"123"<<endl;

		} 
		else
			cout<<"spADoc = NULL"<<endl;

	}

	return TRUE;
}

HRESULT TestEnvelopeCore::InsertTemplateToModel(CATIProduct_var ispProduct,CATUnicodeString iPath,CATIProduct_var &ioProductNew)
{
	HRESULT hr=E_FAIL;
	CATDocument *pCataDoc = NULL;
	hr = CATDocumentServices::OpenDocument(iPath,pCataDoc);
	CATIProduct_var ispInsertPrd = GetRootProduct(pCataDoc);
	if ( NULL_var == ispInsertPrd ) return E_FAIL;
	else
	{
		cout<<"insert"<<endl;
		CATIProduct_var spRootPrdModel = ispProduct;
		ioProductNew = spRootPrdModel->AddProduct(ispInsertPrd);
	}

	return S_OK;
}

//检查干涉
HRESULT TestEnvelopeCore::CheckClash(CATIProduct_var iRootProduct,CATDocument *pDoc,CATUnicodeString iPath)
{
	HRESULT hr=E_FAIL;

	if(NULL==pDoc) return E_FAIL;

	CATIClashFactory* piClashFact = NULL;//干涉factory
	CATIClashResult *piClashResult = NULL;//干涉结果
	CATIClash		*_piClash = NULL;//碰撞
	CATListValCATBaseUnknown_var
		listPrd1,//产品集1
		listPrd2;//产品集2
	CATComputationCase modeComputation=CATComputationCaseClashContact;//计算间隙参数
	CATGroupMode modeGroup=CATGroupModeInsideOne;//分组类型
	hr=pDoc->QueryInterface(IID_CATIClashFactory,(void**)&piClashFact);//干涉factory赋值
	if (FAILED(hr) || NULL==piClashFact)
	{
		cout << "SJDIIBasic::GetClashFactory ==> QI CATIClashFactory Failed!" << endl;
		return E_FAIL;
	}

	hr=piClashFact->Create(_piClash);//创建干涉
	if (FAILED(hr) || NULL==_piClash)
	{
		cout << "SJDIIClash::ComputeAndAddToList ==> _piClashFact->Create Failed!" << endl;
		return E_FAIL;
	}

	//干涉设定
	listPrd1.Append(iRootProduct);
	hr=_piClash->SetGroup(1, listPrd1);//第一组产品赋值
	hr=_piClash->SetGroup(2, listPrd2);//第二组产品赋值
	hr=_piClash->SetComputationCase(modeComputation);//设定计算间隙参数
	hr=_piClash->SetClearance(0);//设定容差
	hr=_piClash->SetGroupMode(modeGroup);//设定分组模式
	hr=_piClash->Compute();//执行计算

	_piClash->GetResult(piClashResult);//获取干涉结果
	if (FAILED(hr) || NULL==piClashResult)
	{
		cout << "SJDIIClash::ComputeAndAddToList ==> piClash->GetResult Failed!" << endl;
		return E_FAIL;
	}

	int iNumOfConflicts=0;//冲突个数
	piClashResult->CountConflicts(iNumOfConflicts);//获取干涉冲突的个数
	cout<<"num:"<<iNumOfConflicts<<endl;
	for (int i=0;i<iNumOfConflicts;i++)//循环获取冲突内信息
	{
		CATIConflict *piConflict = NULL;
		piClashResult->GetConflict(i,piConflict);//获取指定的冲突
		structConflictInfo infoTmp;//信息结构
		GetConflictInfo(piConflict,infoTmp);//获取干涉信息

		if (infoTmp.m_Value!=0)
		{
			_vectorClashResult.push_back(infoTmp);//信息列表
		}
		piConflict->Release();piConflict=NULL;
	}
	piClashResult->Export(CATExportFormat::CATTextFormat,iPath,CATExportType::CATFullExport);

	return S_OK;
}

//获取干涉信息
HRESULT TestEnvelopeCore::GetConflictInfo(CATIConflict* ipiConflict,structConflictInfo &oInfo)
{
	HRESULT hr=E_FAIL;//初始化

	if(NULL==ipiConflict) return E_FAIL;//是否为空
	oInfo.m_IsSolved=FALSE;//结构信息初始化
	oInfo.m_IsPrdValid=TRUE;//结构信息初始化
	// Get conflict value
	oInfo.m_Value=0;//结构信息初始化
	// Get conflict type
	ipiConflict->GetResultType(oInfo.m_Type);
	cout<<"type:"<<oInfo.m_Type<<endl;
	if(oInfo.m_Type==CATTypeClash)//判断是否为干涉
	{
		// Get conflict products
		CATIProduct *piFirstPrd=NULL,*piSecondPrd=NULL;
		CATUnicodeString strFirstShapeName,strSecondShapeName;
		hr=ipiConflict->GetFirstProduct(piFirstPrd,strFirstShapeName);//获取第一个product及名字
		hr=ipiConflict->GetSecondProduct(piSecondPrd,strSecondShapeName);//获取第二个product及名字

		//set info
		oInfo.m_FirstPrd=piFirstPrd;//结构信息第一个产品赋值
		oInfo.m_SecondPrd=piSecondPrd;//结构信息第二个产品赋值
		oInfo.m_FirstName=piFirstPrd->GetPartNumber();//结构信息第一个产品名
		oInfo.m_SecondName=piSecondPrd->GetPartNumber();//结构信息第二个产品名
		piFirstPrd->Release();piFirstPrd=NULL;//释放
		piSecondPrd->Release();piSecondPrd=NULL;//释放

		hr=ipiConflict->GetValue(oInfo.m_Value);//获取干涉值
	}

	return hr;
}

CATDocument* TestEnvelopeCore::GetCurrentDocument()
{
	HRESULT rc=E_FAIL;
	CATDocument *pDocument = NULL;

	// Get current editor
	CATFrmEditor * pEditor =CATFrmEditor::GetCurrentEditor();
	// Get active object.
	CATPathElement spPath = pEditor->GetUIActiveObject();
	// Get current selected element.
	CATBaseUnknown* pCurrbase = spPath.CurrentElement();

	CATILinkableObject *piLinkableObject = NULL;
	if( !!pCurrbase )
		rc = pCurrbase->QueryInterface(IID_CATILinkableObject,(void**)&piLinkableObject);

	if( SUCCEEDED(rc) && !!piLinkableObject ) {
		// Get current document associate with the selected element.
		pDocument = piLinkableObject->GetDocument();
		piLinkableObject->Release();     piLinkableObject = NULL ;
	}

	return pDocument;
}