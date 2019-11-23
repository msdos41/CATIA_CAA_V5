// COPYRIGHT Dassault Systemes 2012
//===================================================================
//
// DumTempPointComp.cpp
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
#include "DumTempPointComp.h"
#include "CATFrmEditor.h"
#include "CAT3DPointRep.h"
#include "CATGraphicAttributeSet.h"
#include "CATISO.h"
 
CATImplementClass(DumTempPointComp,
                  Implementation,
                  CATModelForRep3D,
                  CATnull );
 

//-----------------------------------------------------------------------------
// DumTempPointComp : constructor
//-----------------------------------------------------------------------------
DumTempPointComp::DumTempPointComp():
    CATModelForRep3D()
{
}

//-----------------------------------------------------------------------------
// DumTempPointComp : destructor
//-----------------------------------------------------------------------------
DumTempPointComp::~DumTempPointComp()
{
}
 
// Link the implementation to its interface
// ---------------------------------------

//TIE or TIEchain definitions
#include "TIE_DumITempPoint.h"
TIE_DumITempPoint(DumTempPointComp);


//Methods implementation
HRESULT DumTempPointComp::SetDatas (CATMathPoint * iOrigin,CATMathPlane * iPlane)
{
	HRESULT rc = S_OK;

	_mathPt = (*iOrigin);
	_mathPlane = (*iPlane);

	UpdatePoint();

	return rc;
}

HRESULT DumTempPointComp::SetDatas (CATMathPoint * iOrigin)
{
	HRESULT rc = S_OK;

	_mathPt = (*iOrigin);
	//_mathPlane = (*iPlane);

	UpdatePoint();

	return rc;
}

HRESULT DumTempPointComp::SetGraphicRepresentation(CATRep * iRep)
{
	SetRep(iRep);

	return S_OK;
}

HRESULT DumTempPointComp::GetGraphicRepresentation(CATRep ** oRep)
{
	(*oRep) = GiveRep();

	return S_OK;
}

HRESULT DumTempPointComp::GetPosition(CATMathPoint * oOrigin,CATMathPlane * oPlane )
{
	(*oOrigin) = _mathPt;
	(*oPlane) = _mathPlane;

	return S_OK;
}

HRESULT DumTempPointComp::UpdatePoint()
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

	//Center Point
	float xyz[3];
	xyz[0] = (float)_mathPt.GetX();
	xyz[1] = (float)_mathPt.GetY();
	xyz[2] = (float)_mathPt.GetZ();
	CAT3DMarkerGP * marker = new CAT3DMarkerGP ( xyz, 1 , STAR );

	//set color
	CATGraphicAttributeSet attGP;
	attGP.SetColor(GREEN);

	//add graphic primitive
	pRepForCenter->AddGP(marker,attGP);

	SetGraphicRepresentation(pRepForCenter);

	pISO->AddElement(this);

	return S_OK;
}

