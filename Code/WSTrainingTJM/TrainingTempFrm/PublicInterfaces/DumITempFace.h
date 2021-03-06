// COPYRIGHT Dassault Systemes 2015
//===================================================================
//
// DumITempFace.h
// Define the DumITempFace interface
//
//===================================================================
//
// Usage notes:
//   New interface: describe its use here
//
//===================================================================
//
//  Jul 2015  Creation: Code generated by the CAA wizard  likj
//===================================================================
#ifndef DumITempFace_H
#define DumITempFace_H

#include "TrainingTempM.h"
#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATModelForRep3D.h"
#include "CATMathVector.h"
#include "CATRep.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByTrainingTempM IID IID_DumITempFace;
#else
extern "C" const IID IID_DumITempFace ;
#endif

//------------------------------------------------------------------

/**
* Interface representing xxx.
*
* <br><b>Role</b>: Components that implement
* DumITempFace are ...
* <p>
* Do not use the DumITempFace interface for such and such

*
* @example
*  // example is optional
*  DumITempFace* currentDisplay = NULL;
*  rc = window-&gt;QueryInterface(IID_DumITempFace,
*                                     (void**) &amp;currentDisplay);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class ExportedByTrainingTempM DumITempFace: public CATBaseUnknown
{
  CATDeclareInterface;

  public:
	 virtual HRESULT SetDatas(CATLISTV(CATMathPoint) lstMathVertices,
							  CATMathVector iMathNormal,
							  int iTransparent,
							  int iRed = 0,
							  int iGreen = 255,
							  int iBlue = 0) = 0;
	 virtual HRESULT SetGraphicRepresentation (CATRep *  iRep ) = 0;
	 virtual HRESULT GetGraphicRepresentation (CATRep **  oRep ) = 0;
	 virtual HRESULT GetNormalDir(CATMathVector& ioMathNormal) = 0;
	 virtual HRESULT GetCenterPoint(CATMathPoint& iCenterPoint)=0;
	 virtual HRESULT GetCornerPoints(CATLISTV(CATMathPoint) &olstCornerPoints)=0;
};
CATDeclareHandler(DumITempFace,CATBaseUnknown);
//------------------------------------------------------------------

#endif
