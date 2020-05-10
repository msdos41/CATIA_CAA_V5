// COPYRIGHT Dassault Systemes 2018
//===================================================================
//
// MyAddinMain.cpp
// Provide implementation to interface
//    CATIAfrGeneralWksAddin
//    CATIWorkbenchAddin
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Nov 2018  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "MyAddinMain.h"
 
CATImplementClass(MyAddinMain,
                  Implementation,
                  CATBaseUnknown,
                  CATnull );
MacDeclareHeader(MyAddinHdr)

//-----------------------------------------------------------------------------
// MyAddinMain : constructor
//-----------------------------------------------------------------------------
MyAddinMain::MyAddinMain():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// MyAddinMain : destructor
//-----------------------------------------------------------------------------
MyAddinMain::~MyAddinMain()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATIAfrGeneralWksAddin.h"
TIE_CATIAfrGeneralWksAddin(MyAddinMain);
//#include "TIE_CATIWorkbenchAddin.h"
//TIE_CATIWorkbenchAddin(MyAddinMain);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATIWorkbenchAddin::CreateCommands
//-----------------------------------------------------------------------------
void MyAddinMain::CreateCommands ()
{
	new MyAddinHdr("TXTRead","TXTReadMod","TXTReadCmd",(void*)NULL);
	new MyAddinHdr("CreateLine","StateCommandMod","CreateLineCmd",(void*)NULL);
	new MyAddinHdr("CopyPasteNew","CopyPasteNewMod","CopyPasteNewCmd", (void*)NULL);
	new MyAddinHdr("WriteExcel","WriteExcelMod","WriteExcelCmd", (void*)NULL);
	new MyAddinHdr("RPSCreation","RPSCreationMod","RPSCreationCmd", (void*)NULL);
	new MyAddinHdr("CreatePad", "CreatePadMod", "CreatePadCmd", (void*)NULL);
	new MyAddinHdr("CreateCubeFillet","CreateCubeFilletMod","CreateCubeFilletCmd", (void*)NULL);
	new MyAddinHdr("ReadXml","ReadXmlMod","ReadXmlCmd", (void*)NULL);
	new MyAddinHdr("DrwSetColor","DrwSetColorMod","DrwSetColorCmd", (void*)NULL);
	new MyAddinHdr("CreateConstraints","ProductConstraintsMod","ProductConstraintsCmd", (void*)NULL);
	new MyAddinHdr("GridView2D","GridView2DMod","GridView2DCmd", (void*)NULL);
	new MyAddinHdr("Test","TestMod","TestCmd", (void*)NULL);
	new MyAddinHdr("DrwAnnotation","DrwAnnotationMod","DrwAnnotationCmd", (void*)NULL);
	new MyAddinHdr("TestProj","TestProjectionMod","TestProjectionCmd", (void*)NULL);
	new MyAddinHdr("TestTempArrow","TestTempArrowMod","TestTempArrowCmd", (void*)NULL);
	new MyAddinHdr("TestCrossDoc","TestCrossDocMod","TestCrossDocCmd", (void*)NULL);
	new MyAddinHdr("TestUserDefinedMathBox","TestUserDefinedMathBox","TestUserDefinedMathBoxCmd", (void*)NULL);
	new MyAddinHdr("TestDrwDimension","TestDrwDimensionMod","TestDrwDimensionCmd", (void*)NULL);
	new MyAddinHdr("TestCrvRadius","TestCrvRadiusMod","TestCrvRadiusCmd", (void*)NULL);
	new MyAddinHdr("TestTempPoint","TestTempPointMod","TestTempPointCmd", (void*)NULL);
	new MyAddinHdr("TestMultiList","TestMultiListMod","TestMultiListCmd", (void*)NULL);
	new MyAddinHdr("TestUIChange","TestUIChangeMod","TestUIChangeCmd", (void*)NULL);
	new MyAddinHdr("TestProgressBar","TestProgressBarMod","TestProgressBarCmd", (void*)NULL);
	new MyAddinHdr("TestTooling","TestToolingMod","TestToolingCmd", (void*)NULL);
	new MyAddinHdr("TestCATIAReference","TestCATIAReferenceMod","TestCATIAReferenceCmd", (void*)NULL);
	new MyAddinHdr("TestTessellation","TestTessellationMod","TestTessellationCmd", (void*)NULL);
	new MyAddinHdr("TestFeatureExtension","TestFeatureExtensionMod","TestFeatureExtensionCmd", (void*)NULL);
	new MyAddinHdr("TestSection","TestSectionMod","TestSectionCmd", (void*)NULL);
	new MyAddinHdr("TestMeasurement","TestMeasurementMod","TestMeasurementCmd", (void*)NULL);
}

//-----------------------------------------------------------------------------
// Implements CATIWorkbenchAddin::CreateToolbars
//-----------------------------------------------------------------------------
CATCmdContainer * MyAddinMain::CreateToolbars ()
{
	NewAccess(CATCmdContainer,pMyTlb,MyTlb);
	NewAccess(CATCmdStarter,pTXTRead,TXTRead);
	SetAccessCommand(pTXTRead,"TXTRead");
	SetAccessChild(pMyTlb,pTXTRead);

	NewAccess(CATCmdStarter,pCreateLine,CreateLine);
	SetAccessCommand(pCreateLine,"CreateLine");
	SetAccessNext(pTXTRead,pCreateLine);

	NewAccess(CATCmdStarter,pCopyPaste,CopyPaste);
	SetAccessCommand(pCopyPaste,"CopyPasteNew");
	SetAccessNext(pCreateLine,pCopyPaste);

	NewAccess(CATCmdStarter,pWriteExcel,WriteExcel);
	SetAccessCommand(pWriteExcel,"WriteExcel");
	SetAccessNext(pCopyPaste,pWriteExcel);

	NewAccess(CATCmdStarter,pRPSCreation,RPSCreation);
	SetAccessCommand(pRPSCreation,"RPSCreation");
	SetAccessNext(pWriteExcel,pRPSCreation);

	NewAccess(CATCmdStarter,pCreatePad,CreatePad);
	SetAccessCommand(pCreatePad,"CreatePad");
	SetAccessNext(pRPSCreation,pCreatePad);

	NewAccess(CATCmdStarter,pCreateCubeFillet,CreateCubeFillet);
	SetAccessCommand(pCreateCubeFillet,"CreateCubeFillet");
	SetAccessNext(pCreatePad,pCreateCubeFillet);

	NewAccess(CATCmdStarter,pReadXml,ReadXml);
	SetAccessCommand(pReadXml,"ReadXml");
	SetAccessNext(pCreateCubeFillet,pReadXml);

	NewAccess(CATCmdStarter,pDrwSetColor,DrwSetColor);
	SetAccessCommand(pDrwSetColor,"DrwSetColor");
	SetAccessNext(pReadXml,pDrwSetColor);

	NewAccess(CATCmdStarter,pCreateConstraints,CreateConstraints);
	SetAccessCommand(pCreateConstraints,"CreateConstraints");
	SetAccessNext(pDrwSetColor,pCreateConstraints);

	NewAccess(CATCmdStarter,pGridView2D,GridView2D);
	SetAccessCommand(pGridView2D,"GridView2D");
	SetAccessNext(pCreateConstraints,pGridView2D);

	NewAccess(CATCmdStarter,pTest,Test);
	SetAccessCommand(pTest,"Test");
	SetAccessNext(pGridView2D,pTest);

	NewAccess(CATCmdStarter,pDrwAnnotation,DrwAnnotation);
	SetAccessCommand(pDrwAnnotation,"DrwAnnotation");
	SetAccessNext(pTest,pDrwAnnotation);

	NewAccess(CATCmdStarter,pTestProjection,TestProj);
	SetAccessCommand(pTestProjection,"TestProj");
	SetAccessNext(pDrwAnnotation,pTestProjection);

	NewAccess(CATCmdStarter,pTestTempArrow,TestTempArrow);
	SetAccessCommand(pTestTempArrow,"TestTempArrow");
	SetAccessNext(pTestProjection,pTestTempArrow);

	NewAccess(CATCmdStarter,pTestCrossDoc,TestCrossDoc);
	SetAccessCommand(pTestCrossDoc,"TestCrossDoc");
	SetAccessNext(pTestTempArrow,pTestCrossDoc);

	NewAccess(CATCmdStarter,pTestUDMathBox,TestUserDefinedMathBox);
	SetAccessCommand(pTestUDMathBox,"TestUserDefinedMathBox");
	SetAccessNext(pTestCrossDoc,pTestUDMathBox);

	NewAccess(CATCmdStarter,pTestDrwDim,TestDrwDimension);
	SetAccessCommand(pTestDrwDim,"TestDrwDimension");
	SetAccessNext(pTestUDMathBox,pTestDrwDim);

	NewAccess(CATCmdStarter,pTestCrvRadius,TestCrvRadius);
	SetAccessCommand(pTestCrvRadius,"TestCrvRadius");
	SetAccessNext(pTestDrwDim,pTestCrvRadius);

	NewAccess(CATCmdStarter,pTestTempPoint,TestTempPoint);
	SetAccessCommand(pTestTempPoint,"TestTempPoint");
	SetAccessNext(pTestCrvRadius,pTestTempPoint);

	NewAccess(CATCmdStarter,pTestMultiList,TestMultiList);
	SetAccessCommand(pTestMultiList,"TestMultiList");
	SetAccessNext(pTestTempPoint,pTestMultiList);

	NewAccess(CATCmdStarter,pTestUIChange,TestUIChange);
	SetAccessCommand(pTestUIChange,"TestUIChange");
	SetAccessNext(pTestMultiList,pTestUIChange);

	NewAccess(CATCmdStarter,pTestProgressBar,TestProgressBar);
	SetAccessCommand(pTestProgressBar,"TestProgressBar");
	SetAccessNext(pTestUIChange,pTestProgressBar);

	NewAccess(CATCmdStarter,pTestTooling,TestTooling);
	SetAccessCommand(pTestTooling,"TestTooling");
	SetAccessNext(pTestProgressBar,pTestTooling);

	NewAccess(CATCmdStarter,pTestCATIARef,TestCATIAReference);
	SetAccessCommand(pTestCATIARef,"TestCATIAReference");
	SetAccessNext(pTestTooling,pTestCATIARef);

	NewAccess(CATCmdStarter,pTestTessellation,TestTessellation);
	SetAccessCommand(pTestTessellation,"TestTessellation");
	SetAccessNext(pTestCATIARef,pTestTessellation);

	NewAccess(CATCmdStarter,pTestFeatureExtension,TestFeatureExtension);
	SetAccessCommand(pTestFeatureExtension,"TestFeatureExtension");
	SetAccessNext(pTestTessellation,pTestFeatureExtension);

	NewAccess(CATCmdStarter,pTestSection,TestSection);
	SetAccessCommand(pTestSection,"TestSection");
	SetAccessNext(pTestFeatureExtension,pTestSection);

	NewAccess(CATCmdStarter,pTestMeasurement,TestMeasurement);
	SetAccessCommand(pTestMeasurement,"TestMeasurement");
	SetAccessNext(pTestSection,pTestMeasurement);

	AddToolbarView(pMyTlb,1,Left);
    return pMyTlb;
}
