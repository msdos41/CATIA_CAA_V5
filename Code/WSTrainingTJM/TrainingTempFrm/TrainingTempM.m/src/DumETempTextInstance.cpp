// COPYRIGHT Dassault Systemes 2013
//===================================================================
//
// DumETempTextInstance.cpp
// Provide implementation to interface
//    CATICreateInstance
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Jul 2013  Creation: Code generated by the CAA wizard  
//===================================================================
#include "DumETempTextInstance.h"
#include "DumTempTextComp.h"
 
CATImplementClass(DumETempTextInstance,
                  DataExtension,
                  CATBaseUnknown,
                  DumTempTextComp );
 

//-----------------------------------------------------------------------------
// DumETempTextInstance : constructor
//-----------------------------------------------------------------------------
DumETempTextInstance::DumETempTextInstance():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// DumETempTextInstance : destructor
//-----------------------------------------------------------------------------
DumETempTextInstance::~DumETempTextInstance()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance( DumETempTextInstance);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATICreateInstance::CreateInstance
//-----------------------------------------------------------------------------
HRESULT __stdcall DumETempTextInstance::CreateInstance (void ** oPPV)
{
	DumTempTextComp *pVisPointModel = new DumTempTextComp();

	if( NULL == pVisPointModel ) return (E_OUTOFMEMORY);

	*oPPV = (void *)pVisPointModel;

   return S_OK;
}
