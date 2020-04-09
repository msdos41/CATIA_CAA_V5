// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TstIFactory.h
// Define the TstIFactory interface
//
//===================================================================
//
// Usage notes:
//   New interface: describe its use here
//
//===================================================================
//
//  Apr 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TstIFactory_H
#define TstIFactory_H

#include "TestExtendPtItfCPP.h"
#include "CATBaseUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByTestExtendPtItfCPP IID IID_TstIFactory;
#else
extern "C" const IID IID_TstIFactory ;
#endif

#include "TstIPoint.h"
//------------------------------------------------------------------

/**
* Interface representing xxx.
*
* <br><b>Role</b>: Components that implement
* TstIFactory are ...
* <p>
* Do not use the TstIFactory interface for such and such

*
* @example
*  // example is optional
*  TstIFactory* currentDisplay = NULL;
*  rc = window-&gt;QueryInterface(IID_TstIFactory,
*                                     (void**) &amp;currentDisplay);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class ExportedByTestExtendPtItfCPP TstIFactory: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

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
	  virtual HRESULT CreateTstPoint(double iX,double iY,double iZ,TstIPoint **oPT)	= 0;
};

//------------------------------------------------------------------
CATDeclareHandler(TstIFactory,CATBaseUnknown);
#endif
