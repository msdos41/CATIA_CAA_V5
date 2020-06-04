// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TestEnvelopeCmd.h
// The state chart based command: TestEnvelopeCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//   STATECOMMAND
//End CAA2 Wizard Generation Report
//
//  May 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TestEnvelopeCmd_H
#define TestEnvelopeCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

#include "TestEnvelopeDlg.h"
#include "GeneralClass.h"

#include "CATDynTransformation.h"
#include "CATDynBoolean.h"

#include "CATVisManager.h"
#include "CATIMeasurableInContext.h"

#include "DumITempPoint.h"
#include "DumITempArrow.h"
#include "DumITempPlane.h"
#include "DumITempFace.h"
#include "DumITempLine.h"

#include "CATTessPointIter.h"
#include "CATTessStripeIter.h"
#include "CATTessFanIter.h"
#include "CATTessPolyIter.h"
#include "CATTessTrianIter.h"
#include "CATCellTessellator.h"

class CATIndicationAgent;

//----------------------------------------------------------------------

/**
 * Describe your command here.
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 * <p>
 * refer to programming resources of Dialog engine framework.
 * (consult base class description).
 */
class TestEnvelopeCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( TestEnvelopeCmd, CATStateCommand )

  public:

  TestEnvelopeCmd();
  virtual ~TestEnvelopeCmd();

    /**
     * Defines the command automata.
     * <br>
     * <i>(states, transitions and agents)</i>
     */
  virtual void     BuildGraph();

    /**
     * Action associated to state transitions.
     */
  virtual CATBoolean  ActionOne(void * data);
  CATBoolean ActionExit(void * data);
  CATBoolean ActionOK(void * data);
  void selectObjAFunc(void * data);
  void selectObjBFunc(void * data);
  void TransToSelectA(void * data);
  void TransToSelectB(void * data);
  HRESULT CreateEnvelope(CATBaseUnknown_var ispBUObj,CATBaseUnknown_var ispBUCurve);
  HRESULT GetRepFromBU(CATBaseUnknown_var ispBU,CATRep **opRep);
  HRESULT GetRepFromBU(CATBaseUnknown *ipBU, CATFrmEditor *ipEditor,CATRep ** oRep,CATRepPath &oRepPath);
  HRESULT TestCgr();
  HRESULT Get3DRep(CATPathElement *iObject, CAT3DRep ** oRep,CATRepPath &oRepPath);
  HRESULT GetPathElemFromBU(CATBaseUnknown_var ispBU,CATFrmEditor *ipEditor,CATPathElement *&opPathElem);
  HRESULT CreateTessellation(CATBaseUnknown_var ispBUElement,vector<CATMathPoint> &olstVertices);
  HRESULT CreateRotationTransformation(vector<CATMathPoint> ilstVertices,double iDeg,CATMathLine iAxis,double iStep,vector<CATMathPoint> &olstVerticesAll);
  void GetExtremePointsInEachArea(vector<CATMathPoint> &iolstPt,double iFirstDirMin,double iFirstDirMax,double iSecondDirMin,double iSecondDirMax, CATUnicodeString istrThirdDir,CATMathPoint &oPtMin,CATMathPoint &oPtMax);
  void GetExtremePointsInEachArea(vector<CATMathPoint> &iolstPt,double iFirstDirMin,double iFirstDirMax,double iSecondDirMin,double iSecondDirMax, CATUnicodeString istrThirdDir,CATMathPoint &oPtMin,CATMathPoint &oPtMax,CATBoolean &obFindMin,CATBoolean &obFindMax);
  void GetExtremePointsInEachArea(vector<CATMathPoint> &iolstPt,double iFirstDirMin,double iFirstDirMax,double iSecondDirMin,double iSecondDirMax, CATUnicodeString istrThirdDir,CATMathPoint &oPtMin,CATMathPoint &oPtMax,CATBoolean &obFindMin,CATBoolean &obFindMax, vector<CATMathPoint> &iolstPtFilter);
  HRESULT CalculateOuterPoints(vector<CATMathPoint> &iolstVerticesAll,double iStep);
  CATBoolean IsOccur(CATMathPoint iPt,vector<CATMathPoint> ilstPt);
  CATBoolean ActionOK2(void * data);
  CATBoolean ActionOK3(void * data);
  HRESULT CreateRotationTransformationUpdate(vector<CATMathPoint> ilstVertices,double iDeg,CATMathLine iAxis,double iStep,vector<CATMathPoint> &olstVerticesAll);
  HRESULT CreateTranslateTransformation(vector<CATMathPoint> ilstVertices,double iDistance,CATMathVector iDir,double iStep,vector<CATMathPoint> &olstVerticesAll);
  HRESULT CreateTranslateTransformation(CATBody_var ispBody,CATIProduct_var ispiProd,double iDistance,CATMathVector iDir,double iStep,CATBody *&opBodyAssy);
  HRESULT CreateTranslateTransformation(double iDistance,CATMathVector iDir,double iStep, map<int,map<int,vector<CATMathPoint>>> &iomap, int iIndexDir);
  CATBoolean ActionOK4(void * data);
  HRESULT CreateEdgeTessellation(CATBody *ipBodyCurve,vector<CATMathPoint> &olstVertices);
  HRESULT CalculateOuterHull(vector<CATMathPoint> ilstPtAll, double idR,CATUnicodeString istrDir,vector<CATMathPoint> &olstPtConcaveHull);
  CATBoolean IsFindNextHullPoint(vector<CATMathPoint2D> &iolstPtRest,CATMathPoint2D iPtCurrent,CATMathVector2D iDirRef,double idR,CATMathPoint2D &oPtNext);
  CATBoolean IsFindNextHullPoint(vector<CATMathPoint2D> &iolstPtRest,CATMathPoint2D iPtCurrent,CATMathVector2D iDirRef,double idR,CATMathPoint2D &oPtNext,CATMathPoint2D &oCenter);
  void SortAdjListByAngle(vector<CATMathPoint2D> ilstPt, CATMathPoint2D iPtCurrent,CATMathVector2D iDirRef,double idR,vector<int> &olstIndexSorted);
  CATBoolean CompareAngle(CATMathPoint2D iPtA,CATMathPoint2D iPtB,CATMathPoint2D iPtCurrent,CATMathVector2D idirRef);
  double GetCross(CATMathVector2D a, CATMathVector2D b);
  double GetDot(CATMathVector2D a,CATMathVector2D b);
  CATBoolean GetCircleCenter(CATMathPoint2D iPtA, CATMathPoint2D iPtB, double idR,CATMathPoint2D &oCenter);
  CATBoolean HasPointsInCircle(vector<CATMathPoint2D> ilstPt,vector<int> ilstIndex,CATMathPoint2D iptCenter,double idR,int adjIndex);
  HRESULT GetTransformationBody(CATBody_var ispBody,CATMathTransformation itrans,CATBody_var& ospResultBody);
  CATBoolean ActionOK5(void * data);
  CATBody*CreateTopAssembly(CATGeoFactory* ipGeoFactory,CATTopData* itopdata,CATLISTP(CATBody) ListOfBodyLst);
  CATBody* CreateTopIntersect( CATGeoFactory* ipGeoFactory, CATTopData* itopdata,CATBody*iBody1,CATBody*iBody2 );
  CATBoolean CreatePlaneBody( CATGeoFactory_var spGeoFactory,CATTopData * topdata, CATMathPlane iMathPlane,CATBody_var &ospPlaneBody );
  HRESULT GetBodyFromBodyCells(CATBody_var ispBody,CATGeoFactory *ipGeoFact,int iDimension,CATBody *&opBody);
  HRESULT CreateCircle( CATGeoFactory_var spGeoFactory,CATTopData * topdata,CATMathPlane iMathPlane,double Radius,CATBody_var &ospBody );
  CATBoolean ActionOK6(void * data);
  CATBody* CreateBodyFromDomain(CATGeoFactory *ipGeoFactory, CATDomain *ipDomain, int iDimension);
  HRESULT CreateTranslateTransformationUpdate(CATBody_var ispBody,CATIProduct_var ispiProd,double iDistance,CATMathVector iDir,double iStep,CATBody *&opBodyAssy);
  HRESULT CreateSurfaceTessellation(CATBaseUnknown_var ispBUElement, map<int,map<int,vector<CATMathPoint>>> &omapXY, map<int,map<int,vector<CATMathPoint>>> &omapXZ, map<int,map<int,vector<CATMathPoint>>> &omapYZ);
  CATBoolean IsMaxOrMinPoint(CATMathPoint iPt,vector<CATMathPoint> &iolstPt,int iDir);
  CATBoolean ActionOK7(void * data);
  void DrawTempPoints(map<int,map<int,vector<CATMathPoint>>> imapPt);
private:

	  TestEnvelopeDlg		*_pDlg;

	  CATFrmEditor			*_pEditor;

	  CATHSO				*_pHSO;

	  CATISO				*_pISO;

	  GeneralClass			*_pGeneralCls;

	  CATFeatureImportAgent * _pSelAAgent;

	  //CATFeatureImportAgent * _pSelBAgent;
	  CATPathElementAgent	*_pSelBAgent;

	  CATDialogAgent		* _pSelAFieldAgent;

	  CATDialogAgent		* _pSelBFieldAgent;

	  CATBaseUnknown_var	_spBUSelectA;

	  CATBaseUnknown_var	_spBUSelectB;

	  CATIProduct_var		_spiProdSelA;

	  CATIProduct_var		_spiProdSelB;

	  double				_dMotionStep;

	  double				_dTessellateStep;

	  double				_dRadiusRolling;

	  map<int,map<int,vector<CATMathPoint>>>	_mapXY;

	  map<int,map<int,vector<CATMathPoint>>>	_mapXZ;

	  map<int,map<int,vector<CATMathPoint>>>	_mapYZ;

};

//----------------------------------------------------------------------

#endif
