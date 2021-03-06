// COPYRIGHT Dassault Systemes 2021
//===================================================================
//
// TJMWheelHouseDraftCls.h
// Header definition of TJMWheelHouseDraftCls
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  Feb 2021  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TJMWheelHouseDraftCls_H
#define TJMWheelHouseDraftCls_H

#include "CATBaseUnknown.h"

#include "TJMWheelHouseDraftGeneralClass.h"

#include "CATIMeasurablePlane.h"
#include "CATIGSMProject.h"

struct FeaturesInfo{

	vector<CATISpecObject_var>		lstSpecCurves;

	vector<CATISpecObject_var>		lstSpecPrtTools;

	CATISpecObject_var				spiSpecBaseSurface;

	int								iSplitSideBaseSurface;

	CATISpecObject_var				spiSpecOffsetSurface;

	int								iSplitSideOffsetSurface;

	CATISpecObject_var				spiSpecOffsetSurfaceInner;

	int								iSplitSideOffsetSurfaceInner;

	CATISpecObject_var				spiSpecOffsetSurfaceMid;

	int								iSplitSideOffsetSurfaceMid;

	CATISpecObject_var				spiSpecOffsetSurfaceMidOuterOffset;			//中分面往外offset的面

	int								iSplitSideOffsetSurfaceMidOuterOffset;

	CATISpecObject_var				spiSpecOffsetSurfaceOuter;

	int								iSplitSideOffsetSurfaceOuter;

};

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* Do not use the @href TJMWheelHouseDraftCls constructor to
* do such and such but instead...
*
* @example
*  // example is optional
*  pObject = new TJMWheelHouseDraftCls;
*  pObject->SetXXX(...);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class TJMWheelHouseDraftCls: public CATBaseUnknown
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
     TJMWheelHouseDraftCls ();
     virtual ~TJMWheelHouseDraftCls ();

  // Copy constructor and equal operator
  // -----------------------------------
  TJMWheelHouseDraftCls (TJMWheelHouseDraftCls &);
  TJMWheelHouseDraftCls& operator=(TJMWheelHouseDraftCls&);
  HRESULT SetDatas(CATIProduct_var *iRootProduct,CATISpecObject_var *iSurface,CATBaseUnknown_var *iSketch,CATBaseUnknown_var *iToolingDir,double iDraftAngle);
  HRESULT ComputeResults();
  HRESULT GetSeperatedCurvesFromSketch(vector<CATISpecObject_var> &olstSpecCurves);
  HRESULT GetSeperatedCurvesFromSketch(CATISpecObject_var ispiSpecSketch,vector<CATISpecObject_var> &olstSpecCurves);
  HRESULT JudgeSurfacePositiveOrNegative(CATGeoFactory *ipGeoFact, CATTopData *ipTopData, CATBaseUnknown_var ispBUSurface, CATMathVector iToolingDir, int &oiSplitSide);
  HRESULT GetCenterOfSurface( CATBody_var ispBodySurface,CATMathPoint &omathOriginalPoint );
  HRESULT GetNormalOfSurface(CATGeoFactory *ipGeoFact,CATTopData *ipTopData,CATBody_var ispBodySolid,CATCell_var ispCellSurface,CATMathVector &oNormalDir);
  HRESULT ComputeResults2();
  HRESULT GetMinDistanceByMeasure(CATISpecObject_var ispiSpec1,CATIProduct_var ispiProd1,CATISpecObject_var ispiSpec2,CATIProduct_var ispiProd2,CATMathPoint &omathPt1,CATMathPoint &omathPt2,double &oDistance);
private:

	CATBaseUnknown_var				_spBUSurface;

	CATISpecObject_var				_spiSpecSurface;

	CATBaseUnknown_var				_spBUSketch;

	CATBaseUnknown_var				_spBUToolingDir;

	CATIProduct_var					_spiRootProduct;

	FeaturesInfo					_structFeaturesInfo;

	double							_dDraftAngle;


};

//-----------------------------------------------------------------------

#endif
