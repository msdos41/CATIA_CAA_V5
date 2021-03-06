// COPYRIGHT Dassault Systemes 2012
//===================================================================
//
// DumTempPlaneComp.h
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
#ifndef DumTempPlaneComp_H
#define DumTempPlaneComp_H

#include "TrainingTempM.h"
#include "CATBaseUnknown.h"

#include "CATModelForRep3D.h"
#include "CAT3DCustomRep.h"
#include "CAT3DFixedPlanGP.h"
#include "CATRep.h"
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CAT3DBoundingSphere.h"

#include "CAT3DBagRep.h"

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
class ExportedByTrainingTempM DumTempPlaneComp: public CATModelForRep3D

{
	CATDeclareClass;

public:

	// Standard constructors and destructors for an implementation class
	// -----------------------------------------------------------------
	DumTempPlaneComp ();
	virtual ~DumTempPlaneComp ();

	HRESULT SetDatas(CATMathPoint *iOrigin,	CATMathDirection * iDirX, CATMathDirection * iDirY);
	HRESULT GetPosition(CATMathPoint * oOrigin, CATMathDirection * oDirX, CATMathDirection * oDirY);

	HRESULT SetGraphicRepresentation (CATRep *  iRep );
	HRESULT GetGraphicRepresentation (CATRep **  oRep );

private:
	// The copy constructor and the equal operator must not be implemented
	// -------------------------------------------------------------------
	DumTempPlaneComp (DumTempPlaneComp &);
	DumTempPlaneComp& operator=(DumTempPlaneComp&);

	HRESULT UpdatePlane();


private:
	CATMathPoint		_mathPt;
	CATMathDirection	_mathDirX;
	CATMathDirection	_mathDirY;

};

//-----------------------------------------------------------------------

#endif
