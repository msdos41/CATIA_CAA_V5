// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CWorkbooks wrapper class

class CWorkbooks : public COleDispatchDriver
{
public:
	CWorkbooks(){} // Calls COleDispatchDriver default constructor
	CWorkbooks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWorkbooks(const CWorkbooks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
     virtual ~CWorkbooks(){} 
	// Attributes
public:

	// Operations
public:


	// Workbooks methods
public:
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Creator()
	{
		long result;
		InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH Add(VARIANT Template)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xb5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Template);
		return result;
	}
	void Close()
	{
		InvokeHelper(0x115, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Item(VARIANT Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH Open(LPCTSTR Filename, VARIANT UpdateLinks, VARIANT ReadOnly, VARIANT Format, VARIANT Password, VARIANT WriteResPassword, VARIANT IgnoreReadOnlyRecommended, VARIANT Origin, VARIANT Delimiter, VARIANT Editable, VARIANT Notify, VARIANT Converter, VARIANT AddToMru)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x2aa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Filename, &UpdateLinks, &ReadOnly, &Format, &Password, &WriteResPassword, &IgnoreReadOnlyRecommended, &Origin, &Delimiter, &Editable, &Notify, &Converter, &AddToMru);
		return result;
	}
	void _OpenText(LPCTSTR Filename, VARIANT Origin, VARIANT StartRow, VARIANT DataType, long TextQualifier, VARIANT ConsecutiveDelimiter, VARIANT Tab, VARIANT Semicolon, VARIANT Comma, VARIANT Space, VARIANT Other, VARIANT OtherChar, VARIANT FieldInfo, VARIANT TextVisualLayout)
	{
		static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x2ab, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Filename, &Origin, &StartRow, &DataType, TextQualifier, &ConsecutiveDelimiter, &Tab, &Semicolon, &Comma, &Space, &Other, &OtherChar, &FieldInfo, &TextVisualLayout);
	}
	LPDISPATCH get__Default(VARIANT Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	void OpenText(LPCTSTR Filename, VARIANT Origin, VARIANT StartRow, VARIANT DataType, long TextQualifier, VARIANT ConsecutiveDelimiter, VARIANT Tab, VARIANT Semicolon, VARIANT Comma, VARIANT Space, VARIANT Other, VARIANT OtherChar, VARIANT FieldInfo, VARIANT TextVisualLayout, VARIANT DecimalSeparator, VARIANT ThousandsSeparator)
	{
		static BYTE parms[] = VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x6ed, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Filename, &Origin, &StartRow, &DataType, TextQualifier, &ConsecutiveDelimiter, &Tab, &Semicolon, &Comma, &Space, &Other, &OtherChar, &FieldInfo, &TextVisualLayout, &DecimalSeparator, &ThousandsSeparator);
	}

	// Workbooks properties
public:

};
