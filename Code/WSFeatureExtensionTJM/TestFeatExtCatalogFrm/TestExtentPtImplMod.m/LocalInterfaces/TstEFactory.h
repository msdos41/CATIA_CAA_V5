// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TstEFactory.h
// Provide implementation to interface
//    TstIFactory

//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//EXTENSION:	CATFeatCont
//EXTENSIONTYPE:	DataExtension

//    BOA: TstIFactory

//End CAA2 Wizard Generation Report
//
//  Apr 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#ifndef TstEFactory_H
#define TstEFactory_H

#include "TstIFactory.h"

#include "CATIContainer.h"

#include "CATICatalog.h"                
#include "CATISpecObject.h"
#include "CATCatalogFactoryServices.h"

//-----------------------------------------------------------------------

/**
* Class representing xxx.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* It implements the interfaces :
*  <ol>
*  <li>@href TstIFactory
*  </ol>
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/
class TstEFactory: public TstIFactory

{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
     TstEFactory ();
     virtual ~TstEFactory ();

    /**
     * Implements a function from an interface.
     * @href TstIFactory#CreateTstPoint
     */
     HRESULT CreateTstPoint (double  iX  , double  iY  , double  iZ  , TstIPoint ** oPT ) ;


  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  TstEFactory (TstEFactory &);
  TstEFactory& operator=(TstEFactory&);

};

//-----------------------------------------------------------------------

#endif
