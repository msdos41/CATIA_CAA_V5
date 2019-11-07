// CInterior.h: interface for the CInterior class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CINTERIOR_H__62F4AF43_2D4A_4FFC_928E_BA937DFAAB0C__INCLUDED_)
#define AFX_CINTERIOR_H__62F4AF43_2D4A_4FFC_928E_BA937DFAAB0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInterior : public COleDispatchDriver
{
public:
	CInterior() {}		// Calls COleDispatchDriver default constructor
	CInterior(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CInterior(const CInterior& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	 virtual ~CInterior() {}	
	LPDISPATCH GetApplication()
	{
		LPDISPATCH result;
		InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	
	long GetCreator()
	{
		long result;
		InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	
	LPDISPATCH GetParent()
	{
		LPDISPATCH result;
		InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	
	VARIANT GetColor()
	{
		VARIANT result;
		InvokeHelper(0x63, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetColor(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x63, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetColorIndex()
	{
		VARIANT result;
		InvokeHelper(0x61, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetColorIndex(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x61, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetInvertIfNegative()
	{
		VARIANT result;
		InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetInvertIfNegative(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x84, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetPattern()
	{
		VARIANT result;
		InvokeHelper(0x5f, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetPattern(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x5f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetPatternColor()
	{
		VARIANT result;
		InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetPatternColor(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetPatternColorIndex()
	{
		VARIANT result;
		InvokeHelper(0x62, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetPatternColorIndex(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x62, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
};

#endif // !defined(AFX_CINTERIOR_H__62F4AF43_2D4A_4FFC_928E_BA937DFAAB0C__INCLUDED_)
