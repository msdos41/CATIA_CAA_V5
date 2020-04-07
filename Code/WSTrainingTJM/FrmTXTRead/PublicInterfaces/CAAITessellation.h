// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// CAAITessellation.h
// Define the CAAITessellation interface
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
#ifndef CAAITessellation_H
#define CAAITessellation_H

#include "TestInterfaceMod.h"
#include "CATBaseUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByTestInterfaceMod IID IID_CAAITessellation;
#else
extern "C" const IID IID_CAAITessellation ;
#endif

//------------------------------------------------------------------

/**
* Interface representing xxx.
*
* <br><b>Role</b>: Components that implement
* CAAITessellation are ...
* <p>
* Do not use the CAAITessellation interface for such and such

*
* @example
*  // example is optional
*  CAAITessellation* currentDisplay = NULL;
*  rc = window-&gt;QueryInterface(IID_CAAITessellation,
*                                     (void**) &amp;currentDisplay);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class ExportedByTestInterfaceMod CAAITessellation: public CATBaseUnknown
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
};

//------------------------------------------------------------------

#endif
