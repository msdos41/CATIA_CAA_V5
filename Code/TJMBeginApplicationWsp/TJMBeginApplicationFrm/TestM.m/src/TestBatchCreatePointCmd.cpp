//#include "CAAGsiUserTools.h"
#include <iostream.h>
//#include "CATIGSMTool.h"
//#include "CATISysLicenseSettingAtt.h"
//#include "CATInstantiateComponent.h"

//HRESULT CheckStaticLicense(CATUnicodeString istrLicName);


int main(int argc, char* argv[])
{
	//// Checks arguments
	//cout << " argc = "<< argc << endl;
	//for (int i=0;i<argc;i++) cout << "argv =[ "<<i<<" ]= "<< argv[i] << endl;
	//if ( 5 <  argc) return 1;

	//char*  pPartName = NULL;
	//pPartName=  argv[1];

	//CATUnicodeString istrX,istrY,istrZ;

	//int length = strlen(argv[2]);
	//istrX.BuildFromUTF8(argv[2],length);

	//length = strlen(argv[3]);
	//istrY.BuildFromUTF8(argv[3],length);

	//length = strlen(argv[4]);
	//istrZ.BuildFromUTF8(argv[4],length);

	//// Create Tool Object 
	//CAAGsiUserTools CAAGsiObjTool;

	//HRESULT rc = S_OK;

	//cout << "====================================================================" << endl;
	//cout << "=========        Batch : Start Create A Point              =========" << endl;
	//cout << "====================================================================" << endl;
	//cout << "(TestBatchCreatePointCmd) Start"  << endl;
	//cout << endl;

	//cout<<"  Starting Checking License  "<<endl;	//在建立sesstion前需要先设置license，不能放后面
	//CATUnicodeString strLicName = "_MD2.slt+";
	//rc = CheckStaticLicense(strLicName);
	//if (FAILED(rc))
	//{
	//	system("pause");
	//	return 99;
	//}

	//cout << "(TestBatchCreatePointCmd) Init session " << endl;
	//cout << " Init Session  " << endl;
	//char* pSessionName = "TestBatchCreatePointSession";
	//rc = CAAGsiObjTool.Init( pSessionName);
	//if (FAILED(rc)) return 2; 


	//CATIGSMTool_var spTool  = CAAGsiObjTool.CreateGSMTool("TestBatchCreatPoint",1,0,0);

	//cout << "(TestBatchCreatePointCmd) Creating Points" << endl; 

	//CATLISTV(CATISpecObject_var) lstSpecParameters;
	//CATISpecObject_var spiParmCurrent = NULL_var;

	//double dblCoordX,dblCoordY,dblCoordZ;
	//int iTransferX = istrX.ConvertToNum(&dblCoordX);
	//int iTransferY = istrY.ConvertToNum(&dblCoordY);
	//int iTransferZ = istrZ.ConvertToNum(&dblCoordZ);
	//if (iTransferX==0 || iTransferY==0 || iTransferZ==0)
	//{
	//	return 3;
	//}

	//CAAGsiObjTool.CreateLength("Coord_X",dblCoordX,spiParmCurrent);	lstSpecParameters.Append(spiParmCurrent);
	//CAAGsiObjTool.CreateLength("Coord_Y",dblCoordY,spiParmCurrent);	lstSpecParameters.Append(spiParmCurrent);
	//CAAGsiObjTool.CreateLength("Coord_Z",dblCoordZ,spiParmCurrent);	lstSpecParameters.Append(spiParmCurrent);

	//CATISpecObject_var spiSpecPoint = CAAGsiObjTool.CreatePointCoord(lstSpecParameters);

	//// ----------------------------------------------------------------------------
	//// 4- Exit 
	//// ----------------------------------------------------------------------------

	//// Save Part 
	//// ------------------------------------
	//// Saves the modified pad in the second input path

	//if ( NULL != pPartName ) {
	//	cout << "(TestBatchCreatePointCmd) Save : "<< pPartName  << endl;
	//	rc = CAAGsiObjTool.Save(pPartName);
	//	if (FAILED(rc)) return 4 ;        
	//}

	//// Close Session
	//// ------------------------------------
	//cout << "(TestBatchCreatePointCmd) Close session " << endl;
	//rc = CAAGsiObjTool.Close(pSessionName);
	//if (FAILED(rc)) return 5;        

	cout << "(TestBatchCreatePointCmd) End "  <<endl;
	cout << "====================================================================" << endl;
	cout << "=========        Batch : End TestBatchCreatePointCmd       =========" << endl;
	cout << "====================================================================" << endl;
	cout << endl;

	system("pause");

	return 0;
}

////检查License是否勾选，如果没有则勾选上
//HRESULT CheckStaticLicense(CATUnicodeString istrLicName)
//{
//	CATISysLicenseSettingAtt* piSysLicenseSettingAtt = NULL;
//
//	HRESULT rc = CATInstantiateComponent("CATSysLicenseSettingCtrl",
//		IID_CATISysLicenseSettingAtt, (void **)&piSysLicenseSettingAtt);	//第一个输入的字符串不是随意输入
//
//	if(piSysLicenseSettingAtt == NULL||FAILED(rc))
//	{
//		cout<<"Error in piSysLicenseSettingAtt"<<endl;
//		return E_FAIL;
//	}
//	else
//	{
//		cout<<"Successful in piSysLicenseSettingAtt"<<endl;
//	}
//
//	//CATUnicodeString iLicenseName = "FMS.prd";
//
//	CATUnicodeString oValue ;
//
//	rc = piSysLicenseSettingAtt->GetLicense(&istrLicName, &oValue);
//
//	if (FAILED(rc))
//	{
//		cout<<"Get License Failed! "<<endl;
//		return E_FAIL;
//	}
//
//	if(oValue == "NotRequested")//如果license不存在,则勾选该License
//
//	{
//		cout<<"License not Selected"<<endl;
//		cout<<"Starting to Select the License"<<endl;
//		oValue = istrLicName;
//		rc = piSysLicenseSettingAtt->SetLicense(&istrLicName,&oValue);
//		if (FAILED(rc))
//		{
//			cout<<"Set License Failed!"<<endl;
//			return E_FAIL;
//		}
//		else
//		{
//			cout<<"Set License Succeeded! "<<endl;
//		}
//
//	}
//
//	else 
//	{
//		cout<<"License Already Selected"<<endl;
//	}
//
//	return S_OK;
//}
