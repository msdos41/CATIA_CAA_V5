// COPYRIGHT Dassault Systemes 2013
//===================================================================
//
// DumITempArrow.h
// Define the DumITempArrow interface
//
//===================================================================
//
// Usage notes:
//   New interface: describe its use here
//
//===================================================================
//
//  Mar 2013  Creation: Code generated by the CAA wizard  
//===================================================================
#ifndef DumITempArrow_H
#define DumITempArrow_H

#include "YFDatumTempM.h"
#include "CATBaseUnknown.h"

#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATRep.h"
#include "CAT3DRep.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYFDatumTempM IID IID_DumITempArrow;
#else
extern "C" const IID IID_DumITempArrow ;
#endif


//------------------------------------------------------------------

/**
* Interface representing xxx.
*
* <br><b>Role</b>: Components that implement
* DumITempArrow are ...
* <p>
* Do not use the DumITempArrow interface for such and such

*
* @example
*  // example is optional
*  DumITempArrow* currentDisplay = NULL;
*  rc = window-&gt;QueryInterface(IID_DumITempArrow,
*                                     (void**) &amp;currentDisplay);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class ExportedByYFDatumTempM DumITempArrow: public CATBaseUnknown
{
  CATDeclareInterface;

  public:
	  virtual HRESULT SetDatas(CATMathPoint *iOrigin,CATMathDirection * iDir) = 0;
	  virtual HRESULT SetGraphicRepresentation (CATRep *  iRep ) = 0;
	  virtual HRESULT GetGraphicRepresentation (CATRep **  oRep ) = 0;
	  virtual HRESULT GetPosition(CATMathPoint * oOrigin,CATMathDirection * oDir ) = 0;

    /**
     * Remember that interfaces define only virtual pure methods.
     * Dont forget to document your methods.
     * <dl>
     * <dt><b>Example:</b>
     * <pre>
     *       
           *   MyFunction does this and that
           *   @param Arg1
           *      The first argument of MyFunction.
           *   @return
           *      Error code of function.
           * 
     * virtual int MyFunction (int Arg1) = 0;
     * </pre>
     * </dl>
     */

  // No constructors or destructors on this pure virtual base class
  // --------------------------------------------------------------
};

CATDeclareHandler(DumITempArrow,CATBaseUnknown);

//------------------------------------------------------------------

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYFDatumTempM

//ListPtr
#include "CATLISTP_Clean.h"
#include "CATLISTP_AllFunct.h"
#include "CATLISTP_Declare.h"

CATLISTP_DECLARE(DumITempArrow)

#include "CATLISTHand_Clean.h"
#include "CATLISTHand_AllFunct.h"
#include "CATLISTHand_Declare.h"

CATLISTHand_DECLARE(DumITempArrow_var)

#undef	CATCOLLEC_ExportedBy

#endif