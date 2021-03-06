// COPYRIGHT Dassault Systemes 2012
//===================================================================
//
// DumTempTextComp.cpp
// Provide implementation to interface
//    DumITempPoint
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Dec 2012  Creation: Code generated by the CAA wizard  Administrator
//===================================================================
#include "DumTempTextComp.h"
#include "CATFrmEditor.h"
#include "CAT3DAnnotationTextGP.h"
#include "CATGraphicAttributeSet.h"
#include "CATISO.h"
 
CATImplementClass(DumTempTextComp,
                  Implementation,
                  CATModelForRep3D,
                  CATnull );
 

//-----------------------------------------------------------------------------
// DumTempTextComp : constructor
//-----------------------------------------------------------------------------
DumTempTextComp::DumTempTextComp():
    CATModelForRep3D()
{
}

//-----------------------------------------------------------------------------
// DumTempTextComp : destructor
//-----------------------------------------------------------------------------
DumTempTextComp::~DumTempTextComp()
{
}
 
// Link the implementation to its interface
// ---------------------------------------

//TIE or TIEchain definitions
#include "TIE_DumITempText.h"
TIE_DumITempText(DumTempTextComp);


//Methods implementation
HRESULT DumTempTextComp::SetDatas (CATMathPoint * iOrigin, CATUnicodeString * strText)
{
	HRESULT rc = S_OK;

	_mathPt = (*iOrigin);
	_strText = (*strText);

	UpdateText();

	return rc;
}

HRESULT DumTempTextComp::SetGraphicRepresentation(CATRep * iRep)
{
	SetRep(iRep);

	return S_OK;
}

HRESULT DumTempTextComp::GetGraphicRepresentation(CATRep ** oRep)
{
	(*oRep) = GiveRep();

	return S_OK;
}

HRESULT DumTempTextComp::UpdateText()
{
	HRESULT rc=E_FAIL;

	CAT3DCustomRep * pRepForCenter = new CAT3DCustomRep();

	//Get the CATISO
	CATFrmEditor *pEditor=CATFrmEditor::GetCurrentEditor();
	CATISO * pISO = pEditor->GetISO();

	//Check the old CATRep is exist ?
	CATRep *pRep  =NULL;
	rc = GetGraphicRepresentation(&pRep);
	if( !!pRep ) 
	{  //The old one is exist.
		pISO->RemoveElement(this);
	}

	CATMathPointf mathPoint(_mathPt); 
	CAT3DAnnotationTextGP * text = new CAT3DAnnotationTextGP(mathPoint, _strText, BOTTOM_LEFT);

	//set color
	CATGraphicAttributeSet attGP;
	attGP.SetColor(GREEN);
	attGP.SetThickness(20);

	//add graphic primitive
	pRepForCenter->AddGP(text,attGP);

	SetGraphicRepresentation(pRepForCenter);

	pISO->AddElement(this);

	return S_OK;
}

HRESULT DumTempTextComp::GetInformation(CATMathPoint * oOrigin, CATUnicodeString * strText )
{
	(*oOrigin) = _mathPt;
	(*strText) = _strText;

	return S_OK;
}