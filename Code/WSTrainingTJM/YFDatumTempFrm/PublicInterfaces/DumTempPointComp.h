// COPYRIGHT Dassault Systemes 2012
//===================================================================
//
// DumTempPointComp.h
// Provide implementation to interface
//    DumITempPoint

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//IMPLEMENTATION
//    TIE: DumITempPoint

//End CAA2 Wizard Generation Report
//
//  Dec 2012  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef DumTempPointComp_H
#define DumTempPointComp_H

#include "YFDatumTempM.h"
#include "CATBaseUnknown.h"

#include "CATModelForRep3D.h"
#include "CAT3DCustomRep.h"
#include "CAT3DFixedArrowGP.h"
#include "CAT3DFixedPlanGP.h"
#include "CAT3DPlanarFaceGP.h"
#include "CATRep.h"
#include "CATMathPoint.h"
#include "CATMathPlane.h"
#include "CAT3DBoundingSphere.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href DumITempPoint
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class ExportedByYFDatumTempM DumTempPointComp: public CATModelForRep3D

{
	CATDeclareClass;

public:

	// Standard constructors and destructors for an implementation class
	// -----------------------------------------------------------------
	DumTempPointComp ();
	virtual ~DumTempPointComp ();

	HRESULT SetDatas (CATMathPoint * iOrigin,CATMathPlane * iPlane);
	HRESULT SetDatas (CATMathPoint * iOrigin);
	HRESULT SetGraphicRepresentation (CATRep *  iRep);
	HRESULT GetGraphicRepresentation (CATRep **  oRep);
	HRESULT GetPosition(CATMathPoint * oOrigin,CATMathPlane * oPlane );

private:
	// The copy constructor and the equal operator must not be implemented
	// -------------------------------------------------------------------
	DumTempPointComp (DumTempPointComp &);
	DumTempPointComp& operator=(DumTempPointComp&);

	HRESULT UpdatePoint();

private:
	CATMathPoint _mathPt;
	CATMathPlane _mathPlane;

};

//-----------------------------------------------------------------------

#endif