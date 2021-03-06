// COPYRIGHT Dassault Systemes 2020
//===================================================================
//
// TstEPointIcon.cpp
// Provide implementation to interface
//    CATIIcon
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Apr 2020  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "TstEPointIcon.h"
 
CATImplementClass(TstEPointIcon,
                  DataExtension,
                  CATBaseUnknown,
                  TestExtendPT );	//最后一个参数需要给的是catalog里面的startuptype
 

//-----------------------------------------------------------------------------
// TstEPointIcon : constructor
//-----------------------------------------------------------------------------
TstEPointIcon::TstEPointIcon():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// TstEPointIcon : destructor
//-----------------------------------------------------------------------------
TstEPointIcon::~TstEPointIcon()
{
}
 
// Link the implementation to its interface
// ---------------------------------------



//TIE or TIEchain definitions
#include "TIE_CATIIcon.h"
TIE_CATIIcon( TstEPointIcon);


//Methods implementation

//-----------------------------------------------------------------------------
// Implements CATIIcon::GetIconName
//-----------------------------------------------------------------------------
HRESULT TstEPointIcon::GetIconName (CATUnicodeString&  oName)
{
	oName = CATUnicodeString("TestExtendPt");
   return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CATIIcon::SetIconName
//-----------------------------------------------------------------------------
HRESULT TstEPointIcon::SetIconName (const CATUnicodeString&  iName)
{

   return S_OK;
}

