// COPYRIGHT Dassault Systemes 2015
//===================================================================
//
// DumETempFaceInstance.h
// Provide implementation to interface
//    CATICreateInstance

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//EXTENSION:	PipTempFaceComp
//EXTENSIONTYPE:	DataExtension

//    TIE: CATICreateInstance

//End CAA2 Wizard Generation Report
//
//  Jul 2015  Creation: Code generated by the CAA wizard  likj
//===================================================================
#ifndef DumETempFaceInstance_H
#define DumETempFaceInstance_H

#include "YFDatumTempM.h"
#include "CATBaseUnknown.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href CATICreateInstance
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class ExportedByYFDatumTempM DumETempFaceInstance: public CATBaseUnknown

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     DumETempFaceInstance ();
     virtual ~DumETempFaceInstance ();

    /**
     * Implements a function from an interface.
     * @href CATICreateInstance#CreateInstance
     */
     HRESULT __stdcall CreateInstance (void ** oPPV ) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  DumETempFaceInstance (DumETempFaceInstance &);
  DumETempFaceInstance& operator=(DumETempFaceInstance&);

};

//-----------------------------------------------------------------------

#endif
