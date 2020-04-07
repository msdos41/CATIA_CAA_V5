// COPYRIGHT Dassault Systemes 2019
//===================================================================
//
// GeneralClass.h
// Header definition of GeneralClass
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Jan 2019  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef GeneralClass_H
#define GeneralClass_H

#include "GeneralClassMod.h"
#include "CATBaseUnknown.h"
#include "YFExcelClass.h"
#include "YFAirventXMLClass.h"

#include "CAACommonModule.h"

//System
#include "CATInstantiateComponent.h"
//#include "CATIUnknownList.h"
#include "CATIUnknownListImpl.h"
#include "CATSettingRepository.h"
#include "CATLib.h"
#include "CATGetEnvValue.h"
#include "CATAutoConversions.h"
#include "CATISysLicenseSettingAtt.h"
#include "CATISysDynLicenseSettingAtt.h"
#include "CATError.h"

//ObjectSpecsModeler 
#include "CATIDescendants.h"
#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATLISTV_CATISpecAttrKey.h"
#include "CATISpecAttribute.h"
#include "CATICatalog.h"
#include "CATCatalogFactoryServices.h"

//InteractiveInterfaces 
#include "CATIBuildPath.h"
#include "CATIIniInteractiveSession.h"

//KnowledgeInterfaces 
#include "CATICkeFunctionFactory.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeParameterSet.h"
#include "CATICkeParm.h"
#include "CATIInstance.h"

//Visualization 
#include "CATHSO.h"
#include "CATISO.h"
#include "CATIVisProperties.h"
#include "CATIModelEvents.h"
#include "CATModifyVisProperties.h"
#include "CATI3DGeoVisu.h"
#include "CATViewer.h"

//VisualizationBase
#include "CAT3DBagRep.h"
#include "CAT3DManipulator.h"
#include "CAT3DCustomRep.h"
#include "CAT3DFaceGP.h"

//MecModInterfaces
#include "CATIPrtContainer.h"
#include "CATIMfBRep.h"
#include "CATIGeometricalElement.h"
#include "CATIBodyRequest.h"
#include "CATIIsolate.h"
#include "CATIGSMTool.h"
#include "CATMfErrUpdate.h"
#include "CATIPartRequest.h"
#include "CATIContainerOfDocument.h"
#include "CATIMf3DAxisSystem.h"
#include "CATIPrtPart.h"
#include "CATIBRepAccess.h"
#include "CATMecModAutoServices.h"
#include "CATIMfGeometryAccess.h"
#include "CATIPersistentSubElement.h"
#include "CATIMechanicalRootFactory.h"
#include "CATIDatumFactory.h"
#include "CATI3DGeometricalElement.h"

//ObjectModelerBase 
#include "CATInit.h"
#include "CATIDocRoots.h"
#include "CATDocument.h"
#include "CATIDocId.h"
#include "CATDocumentServices.h"
#include "CATIContainer.h"
#include "CATSession.h"
#include "CATIEditor.h"

//NewTopologicalObjects 
#include "CATBody.h"
#include "CATCell.h"
#include "CATFace.h"
#include "CATSurface.h"
#include "CATTopData.h"
#include "CATVertex.h"
#include "ListPOfCATBody.h"
#include "CATWire.h"

//ProductStructure 
#include "CATIMovable.h"
#include "CATIProduct.h"
#include "CATListPtrCATIProduct.h"

//GeometricObjects 
#include "CATCurve.h"
#include "CATPoint.h"
#include "CATCrvParam.h"
#include "CATSurParam.h"
#include "CATCircle.h"
#include "CATLine.h"
#include "CATEdgeCurve.h"
#include "CATEdge.h"
#include "CATGeoFactory.h"
#include "CATPlane.h"
#include "CATSurface.h"
#include "CATSurLimits.h"
#include "CATTransfoManager.h"
#include "CATCrvLimits.h"
#include "CATListOfCATSurfaces.h"

//DraftingInterfaces
#include "CATIGenerSpec.h"
#include "CATIDftElementWithLeader.h"
#include "CATIDftGenView.h"
#include "CATIDftGenGeomAccess.h"
#include "CATIDftGenGeom.h"
#include "CATIDrwGenDrawShape.h"
#include "CATDimDefinition.h"
#include "CATIADrawingView.h"
#include "CATIADrawingPictures.h"
#include "CATIADrawingPicture.h"
#include "CATIDrwDressUp.h"
#include "CATIDftText.h"
#include "CATIDrwText.h"
#include "CATIDrwGenDrawShape.h"
#include "CATIDftTextRange.h"
#include "CATIDrwDimValue.h"
#include "CATIDrwDimValueComponent.h"
#include "CATIDrwDimDimensionLine.h"
#include "CATIDftElementWithLeader.h"
#include "CATIADrawingTables.h"
#include "CATIADrawingTable.h"
#include "CATIADrawingView.h"
#include "CATIDftSheet.h"
#include "CATIDftDocumentServices.h"
#include "CATIDftDrawing.h"
#include "CATISheet.h"
#include "CATIDftView.h"
#include "CATIDftSheetFormat.h"
#include "CATIDftFormat.h"
#include "CATIDrwFactory.h"
#include "CATIADrawingComponent.h"
#include "CATIAGenerativeViewBehavior.h"
#include "CATIAGenerativeViewLinks.h"
#include "CATIDrwTextProperties.h"
#include "CATIADrawingComponents.h"
#include "CATIDrwAnnotationFactory.h"

//SketerInterface
#include "IDMCurve2D.h"
#include "CATI2DCurve.h"
#include "CATI2DWFGeometry.h"
#include "CATI2DWFFactory.h"
#include "CATI2DDetail.h"
#include "CATIMove2D.h"
#include "CATI2DDitto.h"

//MechanicalModeler 
#include "CATMmrLinearBodyServices.h"
#include "CATMfBRepDecode.h"

//SpaceAnalysisInterfaces 
//#include "CATIMeasurableInContext.h"
#include "CATIMeasurable.h"

//MeasureGeometryInterfaces 
#include "CATIMeasurableCircle.h"

//ApplicationFrame
#include "CATAfrCommandHeaderServices.h"
#include "CATFrmEditor.h"
#include "CATApplicationFrame.h"
#include "CATI3DCamera.h"
#include "CATFrmLayout.h"
#include "CATFrmWindow.h"

//Mathematics
#include "CATSoftwareConfiguration.h"
#include "CATMathBox2D.h"
#include "CATMathPoint2D.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATMathDef.h"
#include "CATMathTransformation2D.h"
#include "CATMathLine2D.h"

//BasicTopologicalOpe 
#include "CATTopPointOperator.h"
#include "CATTopLineOperator.h"

//MechanicalModelerUI 
#include "CATFeatureImportAgent.h"

//DialogEngine
#include "CATOtherDocumentAgent.h"
#include "CATPathElementAgent.h"

//TopologicalOperators
#include "CATTopBodyExtremum.h"
#include "CreateDistanceMinTopo.h"
#include "CATDistanceMinBodyBody.h"
#include "CATHybIntersect.h"
#include "CATTopSkin.h"
#include "CATHybAssemble.h"
#include "CATCreateTopAssemble.h"
#include "CATCreateTopProject.h"
#include "CATHybProject.h"
#include "CATDynMassProperties3D.h"
#include "CATTopReflectLine.h"
#include "CATCreateTopReflectLine.h"
#include "CATTopWire.h"

//InfInterfaces
#include "CATIADocument.h"
#include "CATIASelection.h"
#include "CATIAReference.h"

//SpaceAnalysisInterfaces 
#include "CATIInertia.h"

//GeometricOperators
#include "CATCreateLocalAnalysisD.h"
#include "CATLocalAnalysis2D.h"
#include "CATCreateReflectCurve.h"
#include "CATReflectCurve.h"

//VPMInterfaces
#include "CATIVpmAFLAffectedObject.h"

//ObjectModelerSystem
#include "CORBAAnyDef.h"

//GSMInterfaces 
#include "CATIGSMProceduralView.h"
#include "CATIGSMPlane.h"

//
#include <map>
#include <vector>
#include "float.h"
#include "iostream.h"
#include "string.h"
#include "fstream.h"
#include "sstream.h"


using namespace std;



void  ExportedByGeneralClassMod CAAMessageBox(CATUnicodeString message,CATUnicodeString title = "Notice");
CATUnicodeString ExportedByGeneralClassMod CAAUStringBuildFromChar(char * strchar);
void ExportedByGeneralClassMod CAAUStringConvertToChar(CATUnicodeString strUnicode,char* strchar );
void ExportedByGeneralClassMod CAAUStringConvertToWChar(CATUnicodeString strUnicode, wchar_t* strwcANSI);
HRESULT ExportedByGeneralClassMod GetIPAddrFromResourceFile(const char* ichVarName,CATUnicodeString istrFileName,char **ocharIPAddr);
HRESULT ExportedByGeneralClassMod GetIPAddrFromTxt(char **ocharIPAddr);
HRESULT ExportedByGeneralClassMod YFGetLicServerIP(char **ocharIPAddr);
HRESULT ExportedByGeneralClassMod YFGetLicServerIP(char **ocharIPAddr, int &oiPort);

ExportedByGeneralClassMod int GetResourcePath(CATUnicodeString istrFileName,CATUnicodeString istrFilePath,CATUnicodeString &oPath);
ExportedByGeneralClassMod int CreateResourcePath(CATUnicodeString istrFileName,CATUnicodeString istrFilePath,CATUnicodeString &oPath);
struct POINT2D{

	double Coord[2];

};

#define TOLTANGENCY 0.005	//0.005rad 约等于 0.3度不到 作为两线相切的判断公差

#define TOLSURFACEGAP 0.004	//曲面G0连续的间隙公差值

#define TOLCURVEGAP	0.004	//曲线G0连续的间隙公差值


//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* Do not use the @href GeneralClass constructor to
* do such and such but instead...
*
* @example
*  // example is optional
*  pObject = new GeneralClass;
*  pObject->SetXXX(...);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class ExportedByGeneralClassMod GeneralClass: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
     GeneralClass ();
     virtual ~GeneralClass ();

  // Copy constructor and equal operator
  // -----------------------------------
  GeneralClass (GeneralClass &);
  GeneralClass& operator=(GeneralClass&);

  //获取当前打开的根节点----只适用于CATProduct
  HRESULT GetRootProduct(CATIProduct_var &ospiRootProd);

  //HRESULT GetRootProductFromResourceFile(CATUnicodeString istrFilePath,CATIProduct_var &ospiRootProd);
  HRESULT GetRootProductFromResourceFile(CATUnicodeString istrFilePath,CATBoolean ibDocReadOnly,CATIProduct_var &ospiRootProd);

  //获取当前打开的根节点------同时适用于CATPart和CATProduct
  HRESULT GetRootProductUpdate(CATIProduct_var &ospiRootProduct);

  //获取当前打开CATPart的PrtPart
  HRESULT GetRootPrtPart(CATIPrtPart_var &ospiRootPrtPart);

  //判断是CATProduct还是CATPart
  CATBoolean IsProduct(CATIProduct_var ispiPrd);

  ////从Product获取PrtPart以及对应的PrtContainer
  HRESULT GetPartFromProduct(CATIProduct_var ispProduct,CATISpecObject_var &ospPartFromProduct,CATIPrtContainer_var &ospiPrtCont);

  //从所有打开的窗口中获取所有的RootProduct
  HRESULT GetAllRootPrdFromWindows(CATLISTP(CATIProduct) &olstRootProducts);

  //获取某对象下的double参数-------可以指定参数集或者不指定
  CATBoolean GetParameterOfObject(CATISpecObject_var ispiSpecObject, CATUnicodeString istrParameterSetName, CATUnicodeString istrParameterName, double &oValue);

  //获取所选择的面的数学平面
  HRESULT GetMathPlane(CATBaseUnknown_var ispiSpecObject,CATMathPlane &MathPlane);

  //从所选的BU转换到CATBody
  CATBody_var GetBodyFromFeature( CATBaseUnknown_var ispFeature );
  //从指定目录下获得CATPart文件的根节点
  HRESULT GetRootPartFromResourceFile(CATUnicodeString istrFilePath,CATBoolean ibDocReadOnly,CATIPrtPart_var &ospiRootPrtPart);

  //从输入的Curve中获取所有的不共点的端点列表--------兼容多段且不连续的Curve
  HRESULT GetAllStartEndPoints(CATBody_var ispBodyOnCurve, CATLISTV(CATMathPoint) &olstMathPointsStartEnd);

  //从Curve的Body转到CATCurve 
  HRESULT GetCurvesFromBody(CATBody_var spCurveBody,CATLISTP(CATCurve) &olstCurves);

  //获取所选Curve的两个端点-------适用于选择输入，单段Curve
  void GetPointFromCurve(CATBaseUnknown_var ispBUCurve,CATMathPoint &omathPt1,CATMathPoint &omathPt2);

  //从CATSurface获得对应的Body
  HRESULT GetBodyFromSurface(CATSurface *ipSurface,CATIProduct_var ispiProduct,CATBody *&opBodyOnSurface);

  //选择元素，转换成BaseUnknown，并同时返回所属Product(Instance)
  void TransferSelectToBU(CATFeatureImportAgent *pFeatAgent,CATBaseUnknown *&opBUSelection, CATIProduct_var &ospProductSeletion);

  //选择元素，转换成BaseUnknown，并同时返回所属Product(Instance)--------兼容跨文档选择
  void TransferSelectToBU(CATOtherDocumentAgent *pOtherDocAgent,CATBaseUnknown *&opBUSelection, CATIProduct_var &ospProductSeletion);

  ////设置高亮
  void SetHighlight(CATFeatureImportAgent *ipFeatImpAgt, CATHSO *ipHSO);
  void SetHighlight(CATBaseUnknown *ipBUSelect, CATFrmEditor *ipEditor, CATHSO *ipHSO);
  void SetGroupHighlight(CATBaseUnknown *ipBUSelect, CATFrmEditor *ipEditor, CATHSO *ipHSO);
  void SetHighlight(CATBaseUnknown *pBUSelect);	//VB方法，同时可以适用于跨窗口以及2D
  void SetHighlightCells(CATBody_var ispBody, CATLISTP(CATCell) ilstCell, int iDimension);
  void SetHighlightCells(CATBody_var ispBody, vector<CATCell_var> ivecCell, int iDimension);
  void SetGroupHighlightFromSpecObj(CATISpecObject_var ispSpecObj, CATFrmEditor *ipEditor, CATHSO *ipHSO);
  //从选择Agent返回对应的路径字符串
  void PathElementString(CATFeatureImportAgent *ipFeatImpAgt,CATUnicodeString &strPathName);

  //从PathElement返回对应路径字符串
  void PathElementString(CATPathElement *ipPathElem, CATUnicodeString &ostrPath);

  ////根据选择对象的路径，找到所属的最高一级的实体body
  CATISpecObject_var GetMechanicalToolFromPath(CATPathElement *ipPath);
  //获得输入节点下的所有存储信息
  HRESULT YFGetSpecAttrInfo(CATISpecObject_var ispiSpecOnObject);

  //根据属性类型返回类型的字符串
  CATUnicodeString YFGetSpecAttType(CATAttrKind iAttrType);

  //属性值转为字符串
  CATUnicodeString YFGetSpecAttrValue(CATISpecAttrAccess_var spiSpecAttrAccess,CATUnicodeString iStrAttrName,int iIndex,CATAttrKind iAttrType,CATBoolean &oIsBRepFeature);

  //获取整个装配体的包围盒
  HRESULT Get3DBoundingBoxFromProduct(CATIProduct_var ispiProduct, CATMathBox &omathBox);

  //获取单一对象的包围盒
  //CATMathBox Get3DBoundingBoxUpdate(CATISpecObject_var ispiSpecProd);
  CATMathBox Get3DBoundingBoxOfSinglePart(CATISpecObject_var ispiSpecProd);
  HRESULT Get3DBoundingBoxOfSinglePart(CATISpecObject_var ispiSpecProd, CATMathVector imathVecX, CATMathVector imathVecY, CATMathVector imathVecZ, vector<CATMathPoint> &olstBoundingPts);
  //从CATBody转到CATCell再获取每个Cell的包围盒-------转到2维面获取每个2维面的包围盒，再叠加
  HRESULT GetBodyBox(CATBody_var spBody, CATIProduct_var ispiProduct, CATMathBox& oMathBox);

  //获得整车绝对坐标系下的变换矩阵
  HRESULT GetAbsMathBox(CATISpecObject_var ispiSpecObj, CATMathBox iBox, CATMathBox &oAbsBox);

  //求出Body的6个方向的极值，以此推导出包络体----------该方式求出的包络体较精确
  HRESULT GetBodyBoxFromExtremePt(CATBody_var spBody, CATIProduct_var ispiProduct, CATMathVector VAxeX, CATMathVector VAxeY, CATMathVector VAxeZ, CATMathBox& oMathBox);
  HRESULT GetBodyBoxFromExtremePt(CATBody_var spBody, CATIProduct_var ispiProduct, CATMathVector VAxeX, CATMathVector VAxeY, CATMathVector VAxeZ, vector<CATMathPoint> &olstEtremePts);
  //获取PartContainer
  CATIPrtContainer_var GetPrtContainer(CATIProduct_var ispiObject);

  //查看特征的显示类型
  CATBoolean CheckShowState(CATISpecObject_var spSpec);

  //计算整车绝对坐标系下的transformation
  CATMathTransformation GetAbsTransformation(CATIProduct_var ispCurrentProduct);

  //从Product获取对应的CATGeoFactory和PrtContainer
  CATGeoFactory* GetProductGeoFactoryAndPrtCont(CATIProduct_var ispProduct,CATIPrtContainer_var &ospiCont);

  ////从Product获取对应的PrtContainer
  void GetPrtContFromPrd(CATIProduct_var ispiPrd, CATIPrtContainer_var & ospiCont);

  ////从Product获取对应的Document
  HRESULT GetReferencePrdDocument(CATIProduct_var ispiInstanceProduct,CATDocument *&opDocument);

  //从Document获取PrtContainer
  HRESULT GetContOfPartDocument(CATDocument *ipDocument,CATIPrtContainer_var &opiCont);

  //从Document获取CATGeoFactory
  CATGeoFactory*GetCATGeoFactory(CATDocument * ipDoc);

  ////从Cell转到Body------2维曲面
  HRESULT CreateBodyFromCell(CATCell *ipCell,CATIProduct_var ispiProduct,CATBody *&opBodyOnCell);
  CATBody* CreateBodyFromCell(CATGeoFactory *ipGeoFactory, CATCell_var ispCell, int iDimension);
  ////从body获得MathPoint
  HRESULT GetMathPoint(CATBody_var ispPointBody,CATMathPoint& oMathPoint);

  //Body根据3个方向获得6个极值点的Body
  void CreateExtremePoint(CATBody_var ispBody,CATGeoFactory_var ispGeoFac , CATMathVector iFirstVT,CATMathVector iSecondVT, CATMathVector iThirdVT,int iMaxOrMin,CATBody_var &ospPointBody);

  //
  void GetMathPtFromBody(CATBody*ipBody,CATLISTV(CATMathPoint) &oMathPtList);

  //设置属性-------3D和2D同时适用
  HRESULT YFSetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATLISTV(CATUnicodeString) iLstStrings);
  HRESULT YFSetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATListOfDouble  iValueList);
  HRESULT YFSetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATListOfInt  iValueList);
  HRESULT YFSetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, int  iValue);
  HRESULT YFSetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, double  iValue);
  HRESULT YFSetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATUnicodeString istrValue);
  HRESULT YFSetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATBoolean ibBool);
  HRESULT YFSetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATISpecObject_var ispiSpecSetObj);

  //获取属性-------3D和2D同时适用
  HRESULT YFGetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATLISTV(CATUnicodeString) &oLstStrings);
  HRESULT YFGetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATListOfDouble &oLstDouble);
  HRESULT YFGetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATListOfInt &oLstInteger);
  HRESULT YFGetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, int &oValue);
  HRESULT YFGetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, double &oValue);
  HRESULT YFGetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATUnicodeString &ostrValue);
  HRESULT YFGetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATBoolean obBool);
  HRESULT YFGetSpecObjectAttrEx(CATISpecObject_var ispiSpecObject, CATUnicodeString istrKey, CATISpecObject_var &ospiSpecGetObj);

  //???获得曲面的中点-------CATCell和CATFace的两个直接计算中点的方法结果一样，都有缺陷，月牙形的一半环形平面所获得的计算中点仍然在曲面外
  CATBoolean GetMidPtOfSurface(CATBody_var ispObjectBody, CATMathPoint &omathPoint, CATMathVector &omathVector);

  //获取当前屏幕所称平面
  void GetPlaneFromScreen();
  void GetPlaneFromScreen(CATMathPlane &omathPlaneScreen);

  //获得图纸的所有Sheet
  HRESULT GetAllSheets(CATDocument * pDftDoc, vector<CATIDftSheet*> &olstSheets);

  //获得图纸的所有View
  HRESULT GetAllViews(CATUnicodeString istrPath, CATLISTV(CATISpecObject_var) &oListOfViews);
  HRESULT GetAllViews(CATDocument *ipDoc, CATLISTV(CATISpecObject_var) &oListOfViews);

  //获取图纸大小和具体的长宽
  HRESULT GetSheetFormatAndSize(CATIDftSheet *ipiDftSheet, CATUnicodeString &ostrSheetFormat, double &odblWidth, double &odblHeight);
  HRESULT GetSheetFormatAndSize(CATDocument *ipDoc, CATUnicodeString &ostrSheetFormat, double &odblWidth, double &odblHeight);

  //获取当前SHEET的背景图纸
  CATBoolean GetBackgroundViewOfActiveSheet(CATDocument * pDoc,CATIView_var &ospView);
  //描述：获取指定SHEET的背景图纸
  CATBoolean GetBackgroundViewOfSheet(CATIDftSheet* ipDftSheet,CATIView_var &ospView);

  //获取Detail Sheet页
  CATIDftSheet * GetDetailSheet(CATDocument * pDftDoc);

  //新建Detail Sheet页
  //HRESULT CreateDetailSheet(CATDocument *ipDoc, CATIDftSheet *&opiDetailSheet);
  HRESULT CreateDetailSheet(CATDocument *ipDoc, CATUnicodeString istrSheetName, CATIDftSheet *&opiDetailSheet);

  //在指定Sheet页中创建视图
  CATIView_var CreateView(CATIDftSheet *ipiDftSheet);

  //在指定Sheet页中根据输入的母视图，创建DetailView
  CATIView_var CreateDetailView(CATIDftSheet *ipiDftSheet, CATIView_var ispiMotherView, double *idCirclePos, double idblRadius, double idblScale, double *idViewPos, CATUnicodeString istrViewPrefix, CATUnicodeString istrViewID, CATUnicodeString istrViewSuffix);

  //在指定页中插入ISO视图
  CATIView_var CreateISOView(CATIDftSheet *ipiDftSheet, CATIProduct_var ispiProduct);
  CATIView_var CreateISOView(CATIDftSheet *ipiDftSheet, CATIProduct_var ispiProduct, CATMathPlane imathPlaneProject);
  CATIView_var CreateISOView(CATIDftSheet *ipiDftSheet, CATLISTP(CATIProduct) ilstProd, CATMathPlane imathPlaneProject);
  //在指定Detail Sheet中创建DetailView
  CATIView_var CreateViewInDetailSheet(CATIDftSheet *ipiDftSheet);

  //删除Detail Sheet中的指定名称的View
  CATBoolean RemoveDetailView(CATIDftSheet * piDetailSheet,CATUnicodeString strViewName);

  //在指定视图中插入符号(实例化部件)
  HRESULT InsertSymbol(CATIView_var ispiView, CATUnicodeString strSymbolName, CATMathPoint2D iPickingPt, CATBaseUnknown* oExternalObject, double iScale);

  //在指定视图中插入KCDS符号-----含有可编辑的text框
  HRESULT InsertKCDSSymbol(CATIView_var ispiView, CATMathPoint2D iPickingPt, CATBaseUnknown* oExternalObject, CATListOfCATUnicodeString iListOfText, CATUnicodeString strSymbolName, double iScale);

  //将3D点转为2D点
  CATBoolean Coord3DTransformTo2D(CATIView_var spiView, CATMathPoint i3DPositin, double* op2DPt);

  //获取字符串中的英文字符
  void SeparateEnZhString(CATUnicodeString istrString,CATListOfCATUnicodeString &oListOfENString,CATListOfCATUnicodeString &oListOfZhString);

  // wchar_t to string
  void Wchar_tToString(string& szDst, wchar_t *wchar);

  //在Excel文件中根据表头具体列名，获取对应列的内容
  void GetStringOfInputSheet(CATUnicodeString strInputSheetPath, long ilRow, CATUnicodeString istrColName, CATListOfCATUnicodeString &oListOfCellsData);

  //在Excel文件中获取指定cell的内容值，并返回该cell对应的合并单元格的信息
  void GetCellValueAndMergeInfo(CATUnicodeString strInputSheetPath, long ilRow, long ilCol, CATUnicodeString &ostrCellValue, long &oMergeRowCount, long &oMergeColumnCount, long &oMergeStartRow, long &oMergeStartColumn);

  //读取Excel文件中的指定行的所有内容---------主要用于读取所有表头
  void GetRowContents(CATUnicodeString strInputSheetPath, long ilRow, CATListOfCATUnicodeString &oListOfRowContents);

  //读取Excel文件中的指定列的所有内容
  void GetColumnContents(CATUnicodeString strInputSheetPath, long ilCol, CATListOfCATUnicodeString &oListOfColContents);

  //图纸中创建零件信息表格
  CATBoolean CreatePartInfoTable(CATIView_var ispiCurrentView, double iPositionX, double iPositionY, int iRow, int iCol, CATUnicodeString istrTableName, vector<CATListOfCATUnicodeString> iListOfCellString, CATIADrawingTable *&opiaDrwTable);
  void ChangeFontType(CATIADrawingText *ipText ,CATUnicodeString istrText);

  //根据Inertia的方向计算3D包围盒
  HRESULT GetBoundingPtsFromInertia(CATIProduct_var ispiProd,vector<CATMathPoint> &olstBoundingPts);

  //从xml中读取
  int YFGetResourcePath(CATUnicodeString istrFileName,CATUnicodeString &oPath);
  HRESULT GetFeatureNamesFromXML(CATUnicodeString istrFileName, CATListOfCATUnicodeString &olstFeatureNames);
  HRESULT GetParmNamesAndTolFromXML(CATUnicodeString istrFileName, CATListOfCATUnicodeString &olstFeatureNames);
  //从xml中获取比例
  HRESULT GetScaleFromXML(CATUnicodeString istrFileName, vector<CATListOfDouble> &ovecScale);

  //判断是否是大众零件号
  CATBoolean IsVWPartNumber(CATIProduct_var ispiProd);

  //从PartName中获取大众零件号
  CATUnicodeString GetVWPartNum(CATUnicodeString istrFullName);

  //从PartName中获取非大众零件号
  CATUnicodeString GetNonVWPartNum(CATUnicodeString istrFullName);

  //从PartName中获取大众零件名
  CATUnicodeString GetVWPartName(CATUnicodeString istrFullName);

  //从PartName中获取非大众零件名
  CATUnicodeString GetNonVWPartName(CATUnicodeString istrFullName);

  //根据YFAI的规则从Product中获取PartNumber和 PartName
  HRESULT GetPartNumAndNameFromProduct(CATIProduct_var ispiProd, CATUnicodeString &ostrPartNum, CATUnicodeString &ostrPartName);

  //获取UnicodeString下第一个出现的字母的序号
  int IsAlpha(CATUnicodeString istrValue);

  //从三个输入的向量中过滤出夹角最接近90度的两个向量
  void GetTwoVerticalVectors(double iarrX[3],double iarrY[3],double iarrZ[3],double oarrFirst[3], double oarrSecond[3]);


  CATIDftSheet* GetSheetFromComponentName(CATDocument *ipDoc, CATUnicodeString istrAlias);
  HRESULT GetSheetFromDittoName(CATDocument *ipDoc, CATUnicodeString istrAlias, CATIDftSheet *&opiDftSheet, CATI2DDitto *&opiDitto);
  HRESULT GetSheetFromDittoName(CATDocument *ipDoc, CATUnicodeString istrAlias, CATIDftSheet *&opiDftSheet, CATI2DDitto *&opiDitto,double oarrPos[2]);
  HRESULT GetTablePosInView(CATI2DDitto *ipiDittoTable, double oarrPos[2]);

  //根据输入的4点和相对锚点位置，把这4个点转到相应的图纸全局位置上，并排序，输出列表第一个是包围盒最左上角的点，第二个点是顺时针的下一个点
  void TransferPoint2DToAbsPos(vector<CATMathPoint2D> ivecPt2D, double iarrAnchorpos[2],CATMathPoint2D oPt2Dnew[4]);

  //根据输入的4点进行排序，输出列表第一个是包围盒最左上角的点，第二个点是顺时针的下一个点
  void SortPt2DClockwise(vector<double*> ivecPt2D,vector<double*> &ovecPt2Dnew);
  void SortPt2DClockwise(vector<double*> &iovecPt2D);
  void SortPt2DClockwise(vector<POINT2D> &iovecPt2D);

  //根据锚点和比例，把输入的点集移动到该位置，并返回新坐标的点集
  void TransferPt2DToAbsPos(vector<double*> ivecPt2D, double iarrAnchorPos[2],double iScale,vector<double*> &ovecPt2DAbs);

  //根据输入的三个向量，投影到输入平面后，根据向量的长度，取前2个较长的作为输出方向
  void GetTwoLongerDirections(double iarrDir1[3],double iarrDir2[3],double iarrDir3[3],double iarrPlane[3],double oarrDir1[3],double oarrDir2[3]);

  //根据输入的斜向包围盒的4个点，算出竖直方向的偏移量，然后获得新的参考锚点
  void CalculateVerticalMovePoint(vector<double*> ivecPt2D,double ipt1[2],double ipt2[2],double iTol,int iType,double opt[2]);

  //根据锚点和比例，把输入的点集移动到该位置，并返回新坐标的点集，以及对应的长方形包围盒的对角线的两个点
  void MovePt2DToAbsPos(vector<POINT2D> ivecPt2D, double iarrAnchorPos[2],double iScale,int iType, vector<POINT2D> &ovecPt2DAbs,double oPtCorner1[2],double oPtCorner2[2]);

  //根据输入的4点按顺序创建数学线
  void CreateLinesFromPoints(vector<POINT2D> ivecPt2D, vector<CATMathLine2D> &ovecLine);

  //检查输入线与box的4根线的交点
  void CheckLineIntersect(CATMathLine2D iLine, vector<CATMathLine2D> ivecLine, vector<CATMathPoint2D> &ovecPt);

  //判断输入点是否在box内部，包括box边线上
  CATBoolean IsPointInsideBox(POINT2D iPt2D, vector<POINT2D> vecBox);

  //检查输入的4点与已经存在的点集是否有相交(包括接触)，并求出y向的最大干涉值（即需要移动摆脱干涉的距离）
  CATBoolean CheckBoxIntersect(int iType, vector<POINT2D> ivecPt2D, vector<vector<POINT2D>> ivecLstBox, double &oCollisionY);

  //计算点在box内的y向最大干涉量
  double CalculateCollisionDistanceMax(int iType,POINT2D iPt,vector<POINT2D> ivecBox);

  //根据分割关键字分割字符串，输出字符串列表
  CATBoolean SplitString(CATUnicodeString iStrString, CATUnicodeString iStrSplit, CATListOfCATUnicodeString &oStrList);

  //检查License
  HRESULT CheckStaticLicense(CATUnicodeString istrLicName);
  HRESULT CheckDynamicLicense(CATUnicodeString istrLicName);

  //删除数字型字符串末尾无用的0和小数点
  void RemoveLastZeroesFromString(CATUnicodeString &ioString);

  //获取BaseUnknown的名称
  CATUnicodeString GetNameFromBaseUnknownFunc(CATBaseUnknown_var ispiBaseUnknown);

  //创建2D尺寸标注
  CATBoolean Create2DDrwDimension(CATIDrwAnnotationFactory_var spAnnFact, CATISpecObject_var spSpecOn2DElem1, CATISpecObject_var spSpecOn2DElem2, CATDrwDimType dimType, CATDrwDimRepresentation dimRep, CATMathPoint2D iMathAnchorPt1, CATMathPoint2D iMathAnchorPt2, CATIDrwDimDimension_var &spiDim);

  //求出曲面中点的曲率半径最大和最小值
  HRESULT GetCrvRadiusOnSurface(CATFace_var ispFace,double &odblCrvRadiusMin,double &odblCrvRadiusMax);

  //CATBaseUnknown特征化到CATSpecObject
  CATISpecObject_var GetSpecFromBaseUnknownFunc(CATBaseUnknown* ipBUOfObject);

  //获取RGB颜色值
  HRESULT GetColorOnBRepObject(CATIBRepAccess_var ispiSubElement,unsigned int &oRed,unsigned int &oGreen,unsigned int &oBlue);
  HRESULT GetColorOnObject(CATISpecObject_var ispiSpecOnObject,unsigned int &oRed,unsigned int &oGreen,unsigned int &oBlue);

  //根据输入的曲面获取所有的边界，相切的cell算作一根边界
  HRESULT GetBordersFromSurface(CATBaseUnknown_var ispBUSurface, CATIProduct_var ispiProduct, CATBaseUnknown_var ispBUCurve, vector<vector<CATCell_var>> &olstCellEdge);
  HRESULT GetBordersFromSurface(CATGeoFactory *ipGeoFactory, CATTopData *ipTopData, vector<CATCell_var> ivecCellSurface, vector<CATCell_var> ivecCellCurve, vector<vector<CATCell_var>> &olstCellEdge);

  //从curve的cell中获取两个端点
  HRESULT GetPointsFromCurveCell(CATCell_var ispCellOfCurve, CATMathPoint &omathPt1, CATMathPoint &omathPt2);

  ////检查1个点是否和参考的2个点中的其中一个点相同，如果相同，把相同的那个参考点放在ref1的位置
  CATBoolean CheckPointsEqual(CATMathPoint imathPt1, CATMathPoint &iomathPtRef1, CATMathPoint &iomathPtRef2);

  //检查两根曲线是否相切
  int CheckTwoCurvesTangency(CATCell_var ispCellCurve1,CATCell_var ispCellCurve2);
  int CheckTwoCurvesTangency(CATCell_var ispCellCurve1,CATMathPoint iptCurve1,CATCell_var ispCellCurve2,CATMathPoint iptCurve2);
  int CheckTwoCurvesTangency(CATGeoFactory *ipGeoFactory,CATTopData *ipTopData,CATCell_var ispCellCurve1,CATMathPoint iptCurve1,CATCell_var ispCellCurve2,CATMathPoint iptCurve2);

  //从CATCell转到CATCurve
  CATCurve_var GetCurveFromCell(CATCell_var ispCellCurve);

  //根据2维surfacecell和对应的1维curvecell在实体body上找到相邻的cell，并且同时判断是否相切
  int GetNeighborCellList(CATGeoFactory *ipGeoFactory, CATTopData *ipTopData, CATBody_var ispBodySolid,vector<CATCell_var> ivecCellSurface,vector<CATCell_var> ivecCellCurve,vector<CATCell_var> &ovecCellSurfaceNeighbor);

  //检查两个body是否G0连续
  CATBoolean CheckG0Connection(CATGeoFactory *ipGeoFactory,CATTopData *ipTopData,CATBody_var ispBody1,CATBody_var ispBody2);
  CATBoolean CheckG0Connection(CATGeoFactory *ipGeoFactory,CATTopData *ipTopData,CATLISTP(CATBody) ilstBody);
  //检查两个曲面在共线上的任意一点的法线的方向是否相同或者相反
  int CheckTwoSurfaceTangencyInOnePoint(CATGeoFactory *ipGeoFactory, CATTopData *ipTopData, CATCell_var ispCellSurface1,CATCell_var ispCellSurface2,CATCell_var ispCellCurveMutual);
  HRESULT CreateNewPrtTool(CATIProduct_var ispiProd,CATUnicodeString istrName,CATISpecObject_var &ospiSpecPrtTool);
  HRESULT CreateNewGeoSet(CATIProduct_var ispiProd,CATUnicodeString istrName,CATISpecObject_var &ospiSpecGeoSet);
  HRESULT InsertObjOnTree(CATIProduct_var ispProd,CATISpecObject_var ispiSpecGeoSet,CATUnicodeString istrObjName,CATBody *ipBody, CATISpecObject_var &ospiSpecObj);
  HRESULT GetSurfaceFromBody(CATBody_var ispBody, CATLISTP(CATSurface) &olstSurface);
  HRESULT GetBodyFromCurve(CATCurve *ipCurve, CATGeoFactory *ipGeoFactory,CATTopData *ipTopData,CATBody *&opBody);
  void MessageOutputWarning (CATUnicodeString iString,CATUnicodeString iTopString);
  void MessageOutputError (CATUnicodeString iString,CATUnicodeString iTopString);
  void MessageOutputInfo (CATUnicodeString iString,CATUnicodeString iTopString);
  CATBoolean CreateMsgBoxOptOKCancel(CATUnicodeString usMsg);
  
};

//-----------------------------------------------------------------------

#endif
