// ExcelFont.h: interface for the CExcelFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELFONT_H__71F5D570_62CD_4759_AED1_1510FA24200F__INCLUDED_)
#define AFX_EXCELFONT_H__71F5D570_62CD_4759_AED1_1510FA24200F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CExcelFont : public COleDispatchDriver
{
public:
	CExcelFont() {}		// Calls COleDispatchDriver default constructor
	CExcelFont(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CExcelFont(const CExcelFont& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	virtual ~CExcelFont(){}
	
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
	
	VARIANT GetBackground()
	{
		VARIANT result;
		InvokeHelper(0xb4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetBackground(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0xb4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetBold()
	{
		VARIANT result;
		InvokeHelper(0x60, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetBold(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x60, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
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
	
	VARIANT GetFontStyle()
	{
		VARIANT result;
		InvokeHelper(0xb1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetFontStyle(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0xb1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetItalic()
	{
		VARIANT result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetItalic(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x65, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetName()
	{
		VARIANT result;
		InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetName(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x6e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetOutlineFont()
	{
		VARIANT result;
		InvokeHelper(0xdd, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetOutlineFont(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0xdd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetShadow()
	{
		VARIANT result;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetShadow(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetSize()
	{
		VARIANT result;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetSize(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetStrikethrough()
	{
		VARIANT result;
		InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetStrikethrough(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetSubscript()
	{
		VARIANT result;
		InvokeHelper(0xb3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetSubscript(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0xb3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetSuperscript()
	{
		VARIANT result;
		InvokeHelper(0xb2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetSuperscript(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0xb2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
	
	VARIANT GetUnderline()
	{
		VARIANT result;
		InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	
	void SetUnderline(const VARIANT& newValue)
	{
		static BYTE parms[] =
			VTS_VARIANT;
		InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
			&newValue);
	}
};

#endif // !defined(AFX_EXCELFONT_H__71F5D570_62CD_4759_AED1_1510FA24200F__INCLUDED_)
