// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// TestUserDefinedMathBoxCmd.cpp
// The state chart based command: TestUserDefinedMathBoxCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Aug 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TestUserDefinedMathBoxCmd.h"
#include "CATIndicationAgent.h"
#include "CATMathPlane.h"

#include "CATCreateExternalObject.h"
CATCreateClass( TestUserDefinedMathBoxCmd);


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
TestUserDefinedMathBoxCmd::TestUserDefinedMathBoxCmd() :
  CATStateCommand ("TestUserDefinedMathBoxCmd", CATDlgEngOneShot, CATCommandModeExclusive) 
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
  ,_Indication(NULL)
{
	/* 读取txt获取ip地址和port的测试代码
	cout<<"Test Starting........."<<endl;

	char *pIPAddr = NULL;
	int iPort = 8090;
	YFGetLicServerIP(&pIPAddr,iPort);
	cout<<pIPAddr<<": "<<iPort<<endl;
	*/
	
	_pGeneralCls = new GeneralClass();

	//测试自动高亮以及高亮面的中点处的曲率半径
	CATIProduct_var spiProdRoot = NULL_var;
	_pGeneralCls->GetRootProductUpdate(spiProdRoot);
	if (spiProdRoot == NULL_var)
	{
		RequestDelayedDestruction();
		return;
	}
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
	for (int i=1; i<= lstCell.Size(); i++)
	{
		CATFace_var spFace = lstCell[i];
		if (spFace == NULL_var)
		{
			continue;
		}
		CATIBRepAccess_var spiBrepAcess  =NULL_var;
		spiBrepAcess = CATBRepDecodeCellInBody(spFace,spBody);
		if (spiBrepAcess == NULL_var)
		{
			continue;
		}
		CATIFeaturize_var  spToFeaturize  =  spiBrepAcess;
		if  (NULL_var  ==  spToFeaturize)
		{
			continue;
		}
		//CATISpecObject_var spiSpecOnCell  =  spToFeaturize->FeaturizeR(MfPermanentBody|MfLastFeatureSupport|MfRelimitedFeaturization|MfDuplicateFeature);    //(MfNoDuplicateFeature  |  MfTemporaryBody  |  MfSelectingFeatureSupport  |  MfFunctionalFeaturization);
		//CATISpecObject_var spiSpecOnCell  =  spToFeaturize->FeaturizeF();
		CATISpecObject_var spiSpecOnCell  =  spToFeaturize->FeaturizeR(MfNoDuplicateFeature | MfPermanentBody | MfSelectingFeatureSupport | MfFunctionalFeaturization);
		CATBaseUnknown *pBU = NULL;
		rc = spiSpecOnCell->QueryInterface(IID_CATBaseUnknown,(void**)&pBU);
		if (SUCCEEDED(rc)&&pBU != NULL)
		{
			_pGeneralCls->SetHighlight(pBU);	//目前只能用vb方法高亮成功，caa方法暂时都无法高亮
		}
		//AddHSO(spiSpecOnCell);
		//
		double dblCrvRadiusMin,dblCrvRadiusMax;
		rc = _pGeneralCls->GetCrvRadiusOnSurface(spFace,dblCrvRadiusMin,dblCrvRadiusMax);
		if (SUCCEEDED(rc))
		{
			cout<<"Rmin: "<<dblCrvRadiusMin<<"   Rmax: "<<dblCrvRadiusMax<<endl;
		}
		
	}

	/*
	double num1 = 0.00005;
	double num2 = 0.00006;
	cout<<abs(num2-num1)<<"  "<<fabs(num2-num1)<<endl;
	cout<<"----------------"<<endl;

	POINT2D pt1 = {{0,100}};
	POINT2D pt2 = {{100,100}};
	POINT2D pt3 = {{100,0}};
	POINT2D pt4 = {{0,0}};
	vector<POINT2D> vecPt;
	vecPt.push_back(pt1);
	vecPt.push_back(pt2);
	vecPt.push_back(pt3);
	vecPt.push_back(pt4);
	vector<vector<POINT2D>> vecLstPt;
	vecLstPt.push_back(vecPt);

	POINT2D PT1 = {{50,50}};
	POINT2D PT2 = {{150,60}};
	POINT2D PT3 = {{150,-40}};
	POINT2D PT4 = {{50,-50}};
	vector<POINT2D> vecPT;
	vecPT.push_back(PT1);
	vecPT.push_back(PT2);
	vecPT.push_back(PT3);
	vecPT.push_back(PT4);


	double collision;
	CATBoolean bIntersect = _pGeneralCls->CheckBoxIntersect(1,vecPT,vecLstPt,collision);
	cout<<"------------------"<<endl;

	*/

	/* 二维直线相交测试代码

	CATMathPoint2D pt1(0,-500);
	CATMathPoint2D pt2(500,-500);
	CATMathPoint2D pt3(100,0);
	CATMathVector2D dir(0,-1);
	CATMathLine2D line1(pt2,pt1);
	CATMathLine2D line2(pt3,dir);
	CATMathPoint2D ptOrigin = line2.GetOrigin();
	double parm,parmOther;
	int iIntersect = line2.Intersect(line1,parmOther,parm);
	cout<<"--------------"<<endl;

	*/
	
	/* vector相关方法代码测试
	vector<int> vec;
	for (int i=0;i<10;i++)
	{
		vec.push_back(i);
	}
	for (int i=0; i<vec.size(); i++)
	{
		cout<<vec[i];
	}
	cout<<"\n"<<endl;
	vec.erase(vec.begin(),vec.begin()+3);//删掉从第一个起的3个元素
	for (int i=0; i<vec.size(); i++)
	{
		cout<<vec[i];
	}
	cout<<"\n"<<endl;
	*/
	
	/* 二维点顺时针排序并计算移动量的测试代码
	double pt1[2]={50,200};
	double pt4[2]={50,0};
	double pt3[2]={-50,-200};
	double pt2[2]={-50,0};
	vector<double*> vecPt;
	vecPt.push_back(pt1);
	vecPt.push_back(pt2);
	vecPt.push_back(pt3);
	vecPt.push_back(pt4);
	vector<double*> ptResult;
	_pGeneralCls->SortPt2DClockwise(vecPt,ptResult);
	double ipt1[2] = {-500,200};
	double ipt2[2] = {500,-200};
	double ptMove[2];
	_pGeneralCls->CalculateVerticalMovePoint(ptResult,ipt1,ipt2,10,1,ptMove);
	cout<<ptMove[0]<<" , "<<ptMove[1]<<endl;
	cout<<"-------------------------------"<<endl;
	*/

	/*
	POINT2D pt1 = {{0,200}};
	POINT2D pt4 = {{500,0}};
	//pt4.Coord={500,0};
	POINT2D pt3 = {{0,-200}};
	//pt3.Coord={0,-200};
	POINT2D pt2 = {{-500,0}};
	//pt2.Coord={-500,0};
	vector<POINT2D> vecPt;
	vecPt.push_back(pt1);
	vecPt.push_back(pt2);
	vecPt.push_back(pt3);
	vecPt.push_back(pt4);
	double arrPos[2] = {0,0};
	//vector<double*> ptResult;
	_pGeneralCls->SortPt2DClockwise(vecPt);
	for (int i=0; i<vecPt.size(); i++)
	{
		cout<<vecPt[i].Coord[0]<<","<<vecPt[i].Coord[1]<<endl;
	}
	cout<<"-------------------------"<<endl;

	vector<POINT2D> ptTransfer;
	double ptCorner1[2];
	double ptcorner2[2];
	//_pGeneralCls->TransferPt2DToAbsPos(vecPt,arrPos,0.5,ptTransfer);
	_pGeneralCls->MovePt2DToAbsPos(vecPt,arrPos,0.5,1,ptTransfer,ptCorner1,ptcorner2);
	for (int i=0; i<ptTransfer.size(); i++)
	{
		cout<<ptTransfer[i].Coord[0]<<","<<ptTransfer[i].Coord[1]<<endl;
	}
	cout<<"-------------------------"<<endl;

	*/
	
	/* 二维点顺逆时针排序相关测试代码
	//vector<double[2]> vec;
	
	double pt1[2]={0,200};
	double pt4[2]={500,0};
	double pt3[2]={0,-200};
	double pt2[2]={-500,0};
	vector<double*> vecPt;
	vecPt.push_back(pt1);
	vecPt.push_back(pt2);
	vecPt.push_back(pt3);
	vecPt.push_back(pt4);
	double arrPos[2] = {0,0};
	vector<double*> ptResult;
	_pGeneralCls->SortPt2DClockwise(vecPt);
	for (int i=0; i<vecPt.size(); i++)
	{
		cout<<vecPt[i][0]<<","<<vecPt[i][1]<<endl;
	}
	cout<<"-------------------------"<<endl;

	vector<double*> ptTransfer;
	_pGeneralCls->TransferPt2DToAbsPos(vecPt,arrPos,0.5,ptTransfer);
	for (int i=0; i<ptTransfer.size(); i++)
	{
		cout<<ptTransfer[i][0]<<","<<ptTransfer[i][1]<<endl;
	}
	cout<<"-------------------------"<<endl;
	*/

	/*根据名称获取Drawing内Instance Component的测试代码
	CATFrmEditor *pEditor = CATFrmEditor::GetCurrentEditor();
	CATDocument *pDoc = pEditor->GetDocument();
	//CATIDftSheet *pDftSheet = _pGeneralCls->GetSheetFromComponentName(pDoc,"Circle");
	CATIDftSheet *piDftSheet = NULL;
	CATI2DDitto *piDitto = NULL;
	double arrPosDitto[2], arrPosTable[2];
	//HRESULT rc = _pGeneralCls->GetSheetFromDittoName(pDoc,"Circle",piDftSheet,piDitto);
	//if (piDftSheet != NULL)
	//{
	//	CATISheet *piSheet = NULL;
	//	rc = piDftSheet->QueryInterface(IID_CATISheet,(void**)&piSheet);
	//	if (SUCCEEDED(rc) && piSheet != NULL)
	//	{
	//		cout<<"Ditto in Sheet: "<<CATIAlias_var(piSheet)->GetAlias()<<endl;
	//	}
	//	double arrPos[6];
	//	piDitto->Get2DAxisMatrix(arrPos);
	//	for (int i=0; i <6; i++)
	//	{
	//		cout<<arrPos[i]<<endl;	//最后两位就是坐标系原点位置
	//	}
	//	IUnknown *piUnknown = NULL;
	//	rc = piDitto->GetDetail(IID_CATIView,&piUnknown);	//获得Ditto的参考视图
	//	if (SUCCEEDED(rc) && piUnknown != NULL)
	//	{
	//		CATIView_var spiView = NULL_var;
	//		rc = piUnknown->QueryInterface(IID_CATIView,(void**)&spiView);
	//		if (SUCCEEDED(rc) && spiView != NULL_var)
	//		{
	//			cout<<"Ditto's reference view is  "<<CATIAlias_var(spiView)->GetAlias()<<endl;
	//		}
	//	}
	//}
	HRESULT rc = _pGeneralCls->GetSheetFromDittoName(pDoc,"Table",piDftSheet,piDitto,arrPosDitto);
	if (piDftSheet != NULL)
	{
		cout<<"Ditto Pos: "<<arrPosDitto[0]<<" , "<<arrPosDitto[1]<<endl;
		_pGeneralCls->GetTablePosInView(piDitto,arrPosTable);
		cout<<"Table Pos: "<<arrPosTable[0]<<" , "<<arrPosTable[1]<<endl;
	}
	
	*/

	/* 测试yfai逻辑读取零件号和零件名的代码
	//
	CATIProduct_var spiRootProd = NULL_var;
	_pGeneralCls->GetRootProductUpdate(spiRootProd);
	//CATBoolean bIsVWPartNum = _pGeneralCls->IsVWPartNumber(spiRootProd);
	//if (bIsVWPartNum == TRUE)
	//{
	//	CATUnicodeString strFullName = spiRootProd->GetPartNumber();
	//	CATUnicodeString strVWPartNum = _pGeneralCls->GetVWPartNum(strFullName);
	//	CATUnicodeString strVWPartName = _pGeneralCls->GetVWPartName(strFullName);
	//}
	//else
	//{
	//	CATUnicodeString strFullName = spiRootProd->GetPartNumber();
	//	CATUnicodeString strVWNonPartNum = _pGeneralCls->GetNonVWPartNum(strFullName);
	//	CATUnicodeString strVWNonPartName = _pGeneralCls->GetNonVWPartName(strFullName);
	//}
	CATUnicodeString strPartNum = "";
	CATUnicodeString strPartName = "";
	HRESULT rc = _pGeneralCls->GetPartNumAndNameFromProduct(spiRootProd,strPartNum,strPartName);
	cout<<strPartNum<<"  "<<strPartName<<endl;

	*/

	/*  读取xml相关测试代码

	CATListOfCATUnicodeString lstHVaneFeatureName = NULL;
	_pGeneralCls->GetFeatureNamesFromXML("H-Vane.xml", lstHVaneFeatureName);
	for (int i=1 ; i <= lstHVaneFeatureName.Size(); i++)
	{
		cout<<lstHVaneFeatureName[i]<<endl;
	}

	CATListOfCATUnicodeString lstHVaneParmName = NULL;
	_pGeneralCls->GetParmNamesAndTolFromXML("H-Vane.xml",lstHVaneParmName);
	for (int j=1 ; j <= lstHVaneParmName.Size(); j++)
	{
		cout<<lstHVaneParmName[j]<<endl;
	}

	*/

	//CAACommonModule *pCommonMod = new CAACommonModule();



	/* 斜向包围盒的测试代码
	
	//
	CATIProduct_var spiRootProduct = NULL_var;
	_pGeneralCls->GetRootProductUpdate(spiRootProduct);

	CATListValCATBaseUnknown_var *lstAllChildren = spiRootProduct->GetAllChildren();
	if (lstAllChildren == NULL)
	{
		return;
	}
	//过滤出Part
	CATIProduct_var spChild = NULL_var;
	CATLISTP(CATIProduct) lstCATPart = NULL;
	for (int i = 1; i <= lstAllChildren->Size(); i++)
	{
		spChild = (*lstAllChildren)[i];
		lstCATPart.Append(spChild);
	}

	CATMathPlane mathPlaneScreen;
	_pGeneralCls->GetPlaneFromScreen(mathPlaneScreen);

	///*
	//定义斜向坐标系
	CATMathVector mathVecX, mathVecY, mathVecScreen;
	CATMathPoint mathPointOrg;
	mathPlaneScreen.GetFirstDirection(mathVecX);
	mathPlaneScreen.GetSecondDirection(mathVecY);
	mathPlaneScreen.GetNormal(mathVecScreen);
	mathPlaneScreen.GetOrigin(mathPointOrg);
	double arrayX[3], arrayScreen[3], arrayOrg[3];
	mathVecX.GetCoord(arrayX);
	mathVecScreen.GetCoord(arrayScreen);
	mathPointOrg.GetCoord(arrayOrg);



	//从测量Inertia获得斜向方向
	CATIInertia* piInertiaOnProduct = NULL;
	HRESULT rc = lstCATPart[1]->QueryInterface(IID_CATIInertia,(void**)&piInertiaOnProduct);
	if (FAILED(rc) || piInertiaOnProduct == NULL)
	{
		return;
	}
	double arrdAxis[9];
	rc = piInertiaOnProduct->GetPrincipalAxes(arrdAxis);
	double arrayTemp[3] = {arrdAxis[6],arrdAxis[7],arrdAxis[8]};
	//
	double arrayXnew[3], arrayYnew[3];
	CATMathVector mathVecXnew = mathVecScreen ^ CATMathVector(arrayTemp);
	mathVecXnew = mathVecXnew ^ mathVecScreen;
	mathVecXnew.Normalize();
	mathVecXnew.GetCoord(arrayXnew);
	
	//D3PointProjectOnPlane(arrayTemp,arrayOrg,arrayScreen,arrayXnew);
	//D3ArrayCopy(arrayTemp,arrayXnew);
	//D3VectorRotate(arrayX,arrayScreen,CATPI/6,arrayXnew);
	D3CrossProduct(arrayScreen,arrayXnew,arrayYnew);

	//获取当前打开零件的包围盒------绝对坐标系下
	//CATMathBox mathBoxAbs = _pGeneralCls->Get3DBoundingBoxOfSinglePart(spiRootProduct);

	//double   ioXMin,ioXMax, ioYMin,  ioYMax,  ioZMin,  ioZMax;
	//mathBoxAbs.GetExtremities (ioXMin,ioXMax, ioYMin,  ioYMax,  ioZMin,  ioZMax);
	//CATMathPoint  iLow1(ioXMin,ioYMin,ioZMin);
	//CATMathPoint  iLow2(ioXMin,ioYMax,ioZMin);
	//CATMathPoint  iLow3(ioXMax,ioYMax,ioZMin);
	//CATMathPoint  iLow4(ioXMax,ioYMin,ioZMin);
	//CATMathPoint  iHigh1(ioXMin,ioYMin,ioZMax);
	//CATMathPoint  iHigh2(ioXMin,ioYMax,ioZMax);
	//CATMathPoint  iHigh3(ioXMax,ioYMax,ioZMax);
	//CATMathPoint  iHigh4(ioXMax,ioYMin,ioZMax);
	////
	//vector<CATMathPoint> lstPointsAbs;
	//lstPointsAbs.push_back(iLow1);
	//lstPointsAbs.push_back(iLow2);
	//lstPointsAbs.push_back(iLow3);
	//lstPointsAbs.push_back(iLow4);
	//lstPointsAbs.push_back(iHigh1);
	//lstPointsAbs.push_back(iHigh2);
	//lstPointsAbs.push_back(iHigh3);
	//lstPointsAbs.push_back(iHigh4);

	//根据Inertia测量计算出的轴系，计算包围盒
	double arrX[3] = {arrdAxis[0],arrdAxis[3],arrdAxis[6]};
	double arrY[3] = {arrdAxis[1],arrdAxis[4],arrdAxis[7]};
	double arrZ[3] = {arrdAxis[2],arrdAxis[5],arrdAxis[8]};
	vector<CATMathPoint> lstAllPartsBoundary;
	for (int i=1; i <= lstCATPart.Size(); i++)
	{
		vector<CATMathPoint> lstBoundaryPts;
		rc = _pGeneralCls->Get3DBoundingBoxOfSinglePart(lstCATPart[i],CATMathVector(arrX),CATMathVector(arrY),CATMathVector(arrZ),lstBoundaryPts);
		for (int j=0; j < lstBoundaryPts.size(); j++)
		{
			lstAllPartsBoundary.push_back(lstBoundaryPts[j]);
		}
	}
	CATMathPoint*  pBoundingBox3D = new CATMathPoint[8];
	Create3DBoxWithAxis(lstAllPartsBoundary,mathPlaneScreen.GetOrigin(),CATMathVector(arrX),CATMathVector(arrY),CATMathVector(arrZ),pBoundingBox3D);

	double arrPt1[3],arrPt2[3],arrPt4[3],arrPt5[3];
	pBoundingBox3D[0].GetCoord(arrPt1);
	pBoundingBox3D[1].GetCoord(arrPt2);
	pBoundingBox3D[3].GetCoord(arrPt4);
	pBoundingBox3D[4].GetCoord(arrPt5);
	double vectorX[3],vectorY[3],vectorZ[3];
	D3VectorSetFromTwoPoint(arrPt1,arrPt4,vectorX);
	D3VectorSetFromTwoPoint(arrPt1,arrPt5,vectorY);
	D3VectorSetFromTwoPoint(arrPt1,arrPt2,vectorZ);
	double vector1[3],vector2[3];
	_pGeneralCls->GetTwoLongerDirections(vectorX,vectorY,vectorZ,arrayScreen,vector1,vector2);


	////把inertia测出的x和y轴投影到当前屏幕
	//double arrXproj[3], arrYproj[3], arrZproj[3];
	//double arrT[3];
	//D3CrossProduct(arrayScreen,arrX,arrT);
	//D3CrossProduct(arrT,arrayScreen,arrXproj);

	//D3CrossProduct(arrayScreen,arrY,arrT);
	//D3CrossProduct(arrT,arrayScreen,arrYproj);

	//D3CrossProduct(arrayScreen,arrZ,arrT);
	//D3CrossProduct(arrT,arrayScreen,arrZproj);

	////算出夹角最接近90度的两个方向
	//double arrFirst[3],arrSecond[3];
	//_pGeneralCls->GetTwoVerticalVectors(arrXproj,arrYproj,arrZproj,arrFirst,arrSecond);


	CATMathPoint*  BoundingBox3Dnew = new CATMathPoint[8] ;
	CATMathPoint*  BoundingBox2Dnew = new CATMathPoint[4] ;
	vector<CATMathPoint> lstPointsNewSys;
	//Create3DBoxWithAxis(lstBoundingPts,mathPlaneScreen.GetOrigin(),CATMathVector(arrayXnew),CATMathVector(arrayYnew),mathVecScreen,BoundingBox3Dnew);
	Create3DBoxWithAxis(lstAllPartsBoundary,mathPlaneScreen.GetOrigin(),CATMathVector(vector1),CATMathVector(vector2),mathVecScreen,BoundingBox3Dnew);
	for (int i=0; i<=7; i++)
	{
		lstPointsNewSys.push_back(BoundingBox3Dnew[i]);
	}
	//
	//lstPointsNewSys.clear();
	//rc = _pGeneralCls->GetBoundingPtsFromInertia(spiRootProduct,lstPointsNewSys);
	PointsProjectingInTo2DBoxOnViewAlongDirection(lstPointsNewSys,mathPlaneScreen.GetOrigin(),CATMathVector(vector1),CATMathVector(vector2),mathVecScreen,BoundingBox2Dnew);

	


	//CATListValCATBaseUnknown_var *lstAllChildren = spiRootProduct->GetAllChildren();
	//if (lstAllChildren == NULL)
	//{
	//	return;
	//}
	////过滤出Part
	//CATIProduct_var spChild = NULL_var;
	//CATLISTP(CATIProduct) lstCATPart = NULL;
	//for (int i = 1; i <= lstAllChildren->Size(); i++)
	//{
	//	spChild = (*lstAllChildren)[i];
	//	lstCATPart.Append(spChild);
	//}

	//打开图纸
	CATUnicodeString strDwgPath = "C:\\Users\\Administrator\\Desktop\\Drawing1.CATDrawing";
	//CATDocument * pDoc = NULL;
	//HRESULT rc=CATDocumentServices::OpenDocument(strDwgPath,pDoc);//打开二维图文档
	//if (NULL == pDoc)
	//{
	//	return;
	//}
	CATSession * pSession = CATSession::GetPtrSession();
	if (pSession==NULL)
	{
		cout<<"GetPtrSession Failed"<<endl;
		return;
	}

	CATIIniInteractiveSession* pInteractiveSession = NULL;
	rc=pSession->QueryInterface(IID_CATIIniInteractiveSession, (void **) &pInteractiveSession);
	if (FAILED(rc)||pInteractiveSession==NULL)
	{
		cout<<"Get CATIIniInteractiveSession Failed"<<endl;
		return;
	}

	CATIEditor* pEditor = NULL;
	pInteractiveSession->Open( strDwgPath, FALSE,&pEditor);
	if (pEditor == NULL)
	{
		cout<<"NewFrom Failed"<<endl;
		return;
	}

	CATDocument* pDoc = NULL;
	pDoc = pEditor->GetEditor()->GetDocument();
	if (pDoc==NULL)
	{
		cout<<"GetDocument Failed"<<endl;
		return;
	}
	//ISO投图
	vector<CATIDftSheet*> lstSheets;
	_pGeneralCls->GetAllSheets(pDoc,lstSheets);
	CATLISTP(CATIProduct) lstProducts = NULL;
	_pGeneralCls->GetAllRootPrdFromWindows(lstProducts);
	//CATIView_var spiViewISO = _pGeneralCls->CreateISOView(lstSheets[0],lstProducts[1],mathPlaneScreen);
	CATIView_var spiViewISO = _pGeneralCls->CreateISOView(lstSheets[0],lstCATPart,mathPlaneScreen);

	//画点
	CATI2DWFFactory_var spi2DWFFactory = spiViewISO;
	for (int i=0; i <=3; i++)
	{
		double arrd[2];
		_pGeneralCls->Coord3DTransformTo2D(spiViewISO,BoundingBox2Dnew[i],arrd);
		cout<<i+1<<" : "<<arrd[0]<<" , "<<arrd[1]<<endl;
		CATISpecObject_var spiSpecCircle = spi2DWFFactory->CreatePoint(arrd);
		spiSpecCircle->Update();
	}

	RequestDelayedDestruction();

	*/


}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
TestUserDefinedMathBoxCmd::~TestUserDefinedMathBoxCmd()
{
   cout<<"Test Ending............."<<endl;

	if (_Indication != NULL) 
      _Indication->RequestDelayedDestruction();

	if (_pGeneralCls != NULL)
	{
		delete _pGeneralCls;
		_pGeneralCls = NULL;
	}
}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void TestUserDefinedMathBoxCmd::BuildGraph()
{


  // TODO: Define the StateChart 
  // ---------------------------
  _Indication = new CATIndicationAgent ("Indication");
  CATMathPlane PlaneXY;
  _Indication -> SetMathPlane (PlaneXY);
  CATDialogState * initialState = GetInitialState("initialState");
  initialState -> AddDialogAgent (_Indication);
  
  AddTransition( initialState, NULL, 
                 IsOutputSetCondition (_Indication),
                 Action ((ActionMethod) &TestUserDefinedMathBoxCmd::ActionOne));
}


//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean TestUserDefinedMathBoxCmd::ActionOne( void *data )
{
  // TODO: Define the action associated with the transition 
  // ------------------------------------------------------

  return TRUE;
}


//描述：高亮某对象
//输入：CATISpecObject对象
//输出：CATBoolean
//返回：CATBoolean
CATBoolean TestUserDefinedMathBoxCmd::AddHSO(CATBaseUnknown_var ispSpecSelect)
{
	HRESULT rc=S_OK;

	CATFrmEditor * pEditor=NULL;
	pEditor = CATFrmEditor::GetCurrentEditor();
	if(pEditor==NULL)
		return FALSE;

	CATHSO * pHSO = pEditor->GetHSO();
	if(pHSO==NULL)
		return FALSE;

	//if (pHSO != NULL)
	//	pHSO->Empty();

	if ((ispSpecSelect != NULL_var) && (pEditor != NULL) && (pHSO != NULL))
	{
		CATIBuildPath *piBuildPath = NULL;
		HRESULT rc = ispSpecSelect->QueryInterface(IID_CATIBuildPath,(void**) &piBuildPath);
		if (SUCCEEDED(rc))
		{
			CATPathElement context = pEditor->GetUIActiveObject();
			CATPathElement *pPathElement = NULL;

			rc = piBuildPath->ExtractPathElement(&context,&pPathElement);
			if (pPathElement != NULL)
			{
				CATUnicodeString strPath = "";
				_pGeneralCls->PathElementString(pPathElement,strPath);
				cout<<strPath<<endl;
				pHSO->AddElement(pPathElement);
				pPathElement->Release();
				pPathElement = NULL;
			}
			piBuildPath->Release();
			piBuildPath = NULL;
		}
	}

	return TRUE;
}