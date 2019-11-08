// ExcelRW.cpp: implementation of the CExcelRW class.
//
//////////////////////////////////////////////////////////////////////

#include "ExcelRW.h"
#include <comdef.h>
#include <io.h>
#include <afx.h>
//#include "iostream.h"
#include <iostream>
using namespace std;



CATImplementClass( CExcelRW,
                   Implementation, 
                   CATBaseUnknown,
                   CATNull );
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//extern int delete_exist;	//汇佳Excel删除图片标记

CExcelRW::CExcelRW(): CATBaseUnknown()
{
	OleInitialize(NULL);
	strFilePath=_T("");
}

CExcelRW::~CExcelRW()
{
	COleVariant covFalse((short)FALSE);
	COleVariant	covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR); 
	MyRange.ReleaseDispatch();
	MySheet.ReleaseDispatch();
	MySheets.ReleaseDispatch();
	MyBook.Close(covFalse,_variant_t(strFilePath),covOptional);
	MyBook.ReleaseDispatch();
	MyBooks.Close();
	MyBooks.ReleaseDispatch();
	MyApp.Quit();
	MyApp.ReleaseDispatch();
 	OleUninitialize();
}
CExcelRW::CExcelRW(CExcelRW& original):
   CATBaseUnknown(original)
{
}
 
//-----------------------------------------------------------------------------
// ExcelRW : equal operator
//-----------------------------------------------------------------------------
CExcelRW& CExcelRW::operator=(CExcelRW& original)
{
   CATBaseUnknown::operator=(original);
   return *this;
}
CString CExcelRW::GetAppPath()
{
	TCHAR lpFileName[MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(),lpFileName,MAX_PATH);
	
	CString strFileName = lpFileName;
	int nIndex = strFileName.ReverseFind ('\\');
	
	CString strPath;
	
	if (nIndex > 0)
		strPath = strFileName.Left (nIndex);
	else
		strPath = "";
	return strPath;
}


BOOL CExcelRW::Open()
{
	LPDISPATCH lpDisp=NULL;
	try
	{
		COleVariant covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);
		if (!MyApp.CreateDispatch(_T("Excel.Application"),NULL))	//打开Excel
		{
			//AfxMessageBox(_T("EXCEL初始化时出错!"),MB_OK|MB_ICONERROR);
			return FALSE;
		}
		lpDisp=MyApp.get_Workbooks();	//得到workbooks
		MyBooks.AttachDispatch(lpDisp,TRUE);
		lpDisp = MyBooks.Add(covOptional);	//得到workbook
		MyBook.AttachDispatch(lpDisp,TRUE);
		lpDisp=MyBook.get_Worksheets();		//得到worksheets
		MySheets.AttachDispatch(lpDisp,TRUE);
	}
	catch (...)
	{
		return false;
	}
	
	//MySheets.get_Worksheet();
	return TRUE;
}

BOOL CExcelRW::Open(CString strFile)
{
	LPDISPATCH   lpDisp=NULL;
	//OleInitialize(NULL);
	if (!MyApp.CreateDispatch(_T("Excel.Application"),NULL))
	{
		//AfxMessageBox(_T("EXCEL初始化时出错!"),MB_OK|MB_ICONERROR);
		return FALSE;
	}
	lpDisp=MyApp.get_Workbooks();
	MyBooks.AttachDispatch(lpDisp,TRUE);
	lpDisp = MyBooks.Open(strFile, vtMissing, vtMissing, vtMissing, 
		vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, vtMissing,vtMissing);
	MyBook.AttachDispatch(lpDisp,TRUE);
	lpDisp=MyBook.get_Worksheets(); 
	MySheets.AttachDispatch(lpDisp,TRUE);
	strFilePath=strFile;
	return TRUE;
}

BOOL CExcelRW::OpenSheet(CString strSheet)
{
	LPDISPATCH  lpDisp=NULL;
	long len;
	len=MySheets.get_Count();
	for(long i=1;i<=len;i++)
	{
		lpDisp=MySheets.get_Item((_variant_t)(long)i);
		MySheet.AttachDispatch(lpDisp,TRUE);
		CString str=MySheet.get_Name();
		if(MySheet.get_Name()==strSheet)
		{
			lpDisp=MySheet.get_Cells();
			MyRange.AttachDispatch(lpDisp,TRUE);
			return TRUE;
		}
	}
	return FALSE;
}

bool CExcelRW::OpenSheet(int i)
{
	LPDISPATCH  lpDisp=NULL;
	long len;
	len=MySheets.get_Count();
	lpDisp=MySheets.get_Item((_variant_t)(long)i);
	MySheet.AttachDispatch(lpDisp,TRUE);
	lpDisp=MySheet.get_Cells();
	MyRange.AttachDispatch(lpDisp,TRUE);
	return true;
}

CString CExcelRW::GetCurrentSheetName()
{
	return MySheet.get_Name();
}

bool CExcelRW::GetSheetsCount(int& sheetcount)
{
	sheetcount = MySheets.get_Count();
	return true;
}

bool CExcelRW::SetCurrentSheetName(CString sheetname)
{
	MySheet.put_Name(sheetname);
	return true;
}

BOOL CExcelRW::SetItemText(long Row,long Col,CString strText)
{
	long lRow=0,lCol=0;
	lRow=GetRowS();
	lCol=GetColS();
	if(Row>lRow ||Col>lCol)
	{
		CString strText;
		strText.Format(_T("由于(%d,%d)已经超过了(%d,%d)的范围,所以在(%d,%d)设置失败!")
			,Row,Col,lRow,lCol,Row,Col);
		//AfxMessageBox(strText,MB_OK|MB_ICONERROR);
		return FALSE;
	}
	MyRange.put_Item(_variant_t(Row), _variant_t(Col), _variant_t(strText));
	return TRUE;
}

CString CExcelRW::GetItemText(long Row,long Col)
{
	CString strValue=_T("");
	long lRow=0,lCol=0;
	lRow=GetRowS();
	lCol=GetColS();
	if(Row>lRow || Col>lCol)
	{
		CString strText;
		strText.Format(_T("由于(%d,%d)已经超过了(%d,%d)的范围,所以返回空值")
			,Row,Col,lRow,lCol,Row,Col);
		//AfxMessageBox(strText,MB_OK|MB_ICONERROR);
		return strValue;
	}
	VARIANT lpDisp;
	try
	{
		lpDisp=MyRange.get_Item(_variant_t(Row), _variant_t(Col));
	}
	catch(...)
	{
		return strValue;
	}
	CRange rgRgeValue;
	rgRgeValue.AttachDispatch(lpDisp.pdispVal, TRUE);
	_variant_t vtVal = rgRgeValue.get_Value();
	if (vtVal.vt == VT_EMPTY)
	{
		rgRgeValue.ReleaseDispatch();
		strValue = _T("");
		rgRgeValue.ReleaseDispatch();
		return strValue;
	}

	vtVal.ChangeType(VT_BSTR);
	strValue= vtVal.bstrVal;
	rgRgeValue.ReleaseDispatch();
	return strValue;
}

BOOL CExcelRW::SaveAs(CString strPath)
{
	try
	{
		if(IsFileExist(strPath,FALSE)==TRUE)
		DeleteFile(strPath);
		MyBook.SaveAs(_variant_t(strPath),vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,
						0,vtMissing,vtMissing,vtMissing,vtMissing);
		strFilePath=strPath;
		//AfxMessageBox(_T("Excel保存成功"),MB_OK|MB_ICONINFORMATION);
	}
	catch (...)
	{
		return false;
	}
	return true;	
}

void CExcelRW::Save()
{
	MyBook.Save();
//	AfxMessageBox(_T("Excel保存成功"),MB_OK|MB_ICONINFORMATION);
}

void CExcelRW::AddSheet(CString strSheet)
{
	LPDISPATCH  lpDisp=NULL;
	lpDisp=MySheets.Add(vtMissing,vtMissing,vtMissing,vtMissing);
	MySheet.AttachDispatch(lpDisp,TRUE);
	MySheet.put_Name(strSheet);
	lpDisp=MySheet.get_Cells();
	MyRange.AttachDispatch(lpDisp,TRUE);
}

void CExcelRW::GetRange(CString strBegin,CString strEnd)
{
	MyRange=MySheet.get_Range(_variant_t(strBegin),_variant_t(strEnd));
}
void CExcelRW::GetCharacters( int start,int length )
{
	MyRange = MyRange.get_Characters(_variant_t( start),_variant_t( length) );
}

void CExcelRW::AutoColFit()
{
	CRange rg=MyRange.get_EntireColumn();
	rg.AutoFit();
	rg.ReleaseDispatch();
}

void CExcelRW::AutoRowFit()
{
	CRange rg=MyRange.get_EntireRow();
	rg.AutoFit();	
	rg.ReleaseDispatch();
}

void CExcelRW::SetWrapText(BOOL blnTrue)
{
	MyRange.put_WrapText((_variant_t)(short)blnTrue);
}

void CExcelRW::SetVisible(BOOL blnVisible)
{
	if(blnVisible==TRUE)
		if(strFilePath!="")
		{
			if(IsFileExist(strFilePath,FALSE))
			{
				Exit();
				ShellExecute(NULL,_T("open"),strFilePath,NULL,NULL,SW_SHOW);
			}
			else
			{
				CString strName;
				strName="路径"+strFilePath+"错误,不能打开显示!";
				//AfxMessageBox(strFilePath,MB_OK|MB_ICONINFORMATION);
			}
		}
		else
		{
			//AfxMessageBox(_T("请先存文件后,方可打开!"),MB_OK|MB_ICONINFORMATION);
		}
}

void CExcelRW::GetFont(MyFont &font)
{
	CExcelFont f=MyRange.get_Font();
	font.Name = (CString)(_variant_t)(f.GetName());
	font.Shadow = (BOOL)(_variant_t)(f.GetShadow());
	font.size = (long)(_variant_t)(f.GetSize());
	font.Underline = (short)(_variant_t)(f.GetUnderline());
	font.Bold = (BOOL)(_variant_t)(f.GetBold());
	font.ForeColor = (long)(_variant_t)(f.GetColor());
	font.Italic = (BOOL)(_variant_t)(f.GetItalic());
	font.Strikethrough = (BOOL)(_variant_t)(f.GetStrikethrough());
	font.Subscript = (BOOL)(_variant_t)(f.GetSubscript());
	font.Subscript = (BOOL)(_variant_t)(f.GetSuperscript());
	f.ReleaseDispatch();
}

void CExcelRW::SetFont(MyFont font)
{
	CExcelFont f=MyRange.get_Font();
	f.SetName(_variant_t(font.Name));
	f.SetShadow((_variant_t)(short)font.Shadow);
	f.SetSize((_variant_t)(short)font.size);
	f.SetUnderline((_variant_t)(short)font.Underline);
	f.SetBold((_variant_t)(short)font.Bold);
	f.SetColor((_variant_t)(long)font.ForeColor);
	f.SetItalic((_variant_t)(short)font.Italic);
	f.SetStrikethrough((_variant_t)(short)font.Strikethrough);
	f.SetSubscript((_variant_t)(short)font.Subscript);
	f.SetSuperscript((_variant_t)(short)font.Subscript);
	f.ReleaseDispatch();
}

void CExcelRW::GetAlignment(MyAlignment &XMyAlignment)
{
	XMyAlignment.HorizontalAlignment = (short)(_variant_t)(MyRange.get_HorizontalAlignment());
	XMyAlignment.VerticalAlignment = (short)(_variant_t)(MyRange.get_VerticalAlignment());
}

void CExcelRW::SetAlignment(MyAlignment XMyAlignment)
{
	MyRange.put_HorizontalAlignment((_variant_t)(short)XMyAlignment.HorizontalAlignment);
	MyRange.put_VerticalAlignment((_variant_t)(short)XMyAlignment.VerticalAlignment);
}

void CExcelRW::GetAllRange()
{
	LPDISPATCH  lpDisp=NULL;
	lpDisp=MySheet.get_Cells();
	MyRange.AttachDispatch(lpDisp,TRUE);
}

void CExcelRW::SetMergeCells(BOOL blnTrue)
{
	if(blnTrue==TRUE)
	{
		int i,j;
		long Row=GetRowS();
		long Col=GetColS();
		for(j=2;j<=Col;j++) SetItemText(1,j,"");
		for(i=2;i<=Row;i++)
			for(j=1;j<=Col;j++)
				SetItemText(i,j,"");
	}
	MyRange.put_MergeCells((_variant_t)(short)blnTrue);
}

void CExcelRW::SetBackStyle(MyBackStyle BackStyle)
{
	LPDISPATCH  lpDisp=NULL;
	CInterior Itor;
	lpDisp=MyRange.get_Interior();
	Itor.AttachDispatch(lpDisp,TRUE);
	if(BackStyle.transparent==TRUE)
		Itor.SetColorIndex((_variant_t)(short)xlNone);
	else
	{
		Itor.SetColor((_variant_t)(long)BackStyle.Color);
		Itor.SetPattern((_variant_t)(short)BackStyle.Pattern);
		Itor.SetPatternColor((_variant_t)(long)BackStyle.PatternColor);
	}
	Itor.ReleaseDispatch();

}

void CExcelRW::SetBorderLine(long Row,long Col,short Xposition,MyBorder XBorder)
{
	//long Row,Col;
	Row=GetRowS();
	Col=GetColS();
	if(Row==1)
		if(Xposition==xlInsideHorizontal) return;
	if(Col==1)
		if(Xposition==xlInsideVertical) return;
	LPDISPATCH  lpDisp=NULL;
	lpDisp=MyRange.get_Borders();   
	CBorders   bds;   
	bds.AttachDispatch(lpDisp);   
	CBorder   bd;   
	lpDisp=bds.get_Item((long)Xposition);
	bd.AttachDispatch(lpDisp);   
	bd.put_LineStyle((_variant_t)(short)XBorder.LineStyle);
	bd.put_Color((_variant_t)(long)XBorder.Color);
	bd.put_Weight((_variant_t)(short)XBorder.Weight);
	bd.ReleaseDispatch();
	bds.ReleaseDispatch();
}

long CExcelRW::GetRowS()
{
	long len=0;
	CRange rg=MyRange.get_EntireRow();	
	len=rg.get_Count();
	rg.ReleaseDispatch();
	return len;
}

long CExcelRW::GetColS()
{
	long len=0;
	CRange rg=MyRange.get_EntireColumn();
	len=rg.get_Count();
	rg.ReleaseDispatch();
	return len;
}

void CExcelRW::SetNumberFormat(MyNumberFormat XNumberFormat)
{
	CString strText=XNumberFormat.strValue;
	MyRange.put_NumberFormat(_variant_t(strText));
}

void CExcelRW::SetColumnWidth(int intWidth)
{
	double f=intWidth/8.08;
	MyRange.put_ColumnWidth((_variant_t)(double)f);
}

double CExcelRW::GetRowHeight()
{
	return (double)(_variant_t)MyRange.get_RowHeight();
}

void CExcelRW::SetRowHeight(int intHeight)
{
	double f=intHeight/8.08;
	MyRange.put_RowHeight((_variant_t)(double)f);
}

void CExcelRW::InsertPicture(CString strFilePath)
{
	LPDISPATCH  lpDisp=NULL;
	if(IsFileExist(strFilePath,FALSE))
	{
	//	lpDisp=MySheet.get
	}
}

void CExcelRW::SetBackPicture(CString strFilePath)
{
	if(IsFileExist(strFilePath,FALSE)==TRUE)
		MySheet.SetBackgroundPicture(strFilePath);
}

void CExcelRW::PrintOut(short CopySum)
{
	if(CopySum<=0) CopySum=1;
	COleVariant covTrue((short)TRUE); 
	COleVariant covFalse((short)FALSE); 
	COleVariant	covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR); 
	MySheet.PrintOut(vtMissing,vtMissing,(_variant_t)(short)CopySum,vtMissing
		,vtMissing,vtMissing,covTrue,vtMissing);
}

void CExcelRW::PrePrintOut(BOOL blnEnable)
{
	COleVariant covOptional((short)blnEnable);
	MySheet.PrintPreview(covOptional);
}

BOOL CExcelRW::IsFileExist(CString strFn, BOOL bDir)
{
    HANDLE h;
	LPWIN32_FIND_DATA pFD=new WIN32_FIND_DATA;
	BOOL bFound=FALSE;
	if(pFD)
	{
		h=FindFirstFile(strFn,pFD);
		bFound=(h!=INVALID_HANDLE_VALUE);
		if(bFound)
		{
			if(bDir)
				bFound= (pFD->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)!=NULL;
			FindClose(h);
		}
		delete pFD;
	}
	return bFound;
}

void CExcelRW::Exit()
{
	COleVariant covFalse((short)FALSE);
	COleVariant	covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR); 
	MyRange.ReleaseDispatch();
	MySheet.ReleaseDispatch();
	MySheets.ReleaseDispatch();
	MyBook.Close(covFalse,_variant_t(strFilePath),covOptional);
	MyBook.ReleaseDispatch();
	MyBooks.Close();
	MyBooks.ReleaseDispatch();
	MyApp.Quit();
	MyApp.ReleaseDispatch();
// 	CoUninitialize();
	OleUninitialize();
}

MyFont::MyFont()
{
	//名字
    Name="Microsoft Sans Serif";
	//大小
	size=12;
	//前景
	ForeColor=RGB(0,0,0);
	//粗体
	Bold=FALSE;
	//斜体
	Italic=FALSE;
	//中间线
	Strikethrough=FALSE;
	//阴影
	Shadow=FALSE;
	//下标
	Subscript=FALSE;
	//上标
	Superscricp=FALSE;
	//下划线
	Underline=xlUnderlineStyleNone;	
}

MyBorder::MyBorder()
{
	//线条形状
	LineStyle=xlContinuous;
	//粗线
    Weight=xlThin;
	//颜色
    Color=RGB(0,0,0);
}

MyBackStyle::MyBackStyle()
{
	//背景颜色
	Color=RGB(255,255,255);
	//背景图案
    Pattern=xlSolid;
	//背景图案颜色
    PatternColor=RGB(255,0,0);
	//默认为不透明
	transparent=FALSE;
}

MyAlignment::MyAlignment()
{
	//普通
	HorizontalAlignment=xlGeneral;
	//居中对齐
	VerticalAlignment=xlCenter;
}

MyNumberFormat::MyNumberFormat()
{
	strValue="G/通用格式";
}

CString MyNumberFormat::GetText()
{
	strValue="@";
	return strValue;
}

CString MyNumberFormat::GetGeneral()
{
	strValue="G/通用格式";
	return strValue;
}

CString MyNumberFormat::GetNumber(BOOL blnBox,int RightSum)
{
	CString str="0";
	int i;
	if(RightSum<0) RightSum=0;
	if(blnBox==TRUE)
	{
		if(RightSum==0)
		{
			str="#,##0_ ";
			strValue=str;
			return strValue;
		}
		else
		{
			str="#,##0.";
			for(i=0;i<RightSum;i++) str=str+"0";
			str=str+"_ ";
			strValue=str;
			return strValue;	
		}
	}
	else
	{
		if(RightSum==0)
		{
			str="0_ ";
			strValue=str;
			return strValue;
		}
		else
		{
			str="0.";
			for(i=0;i<RightSum;i++) str=str+"0";
			str=str+"_ ";
			strValue=str;
			return strValue;	
		}
	}
}

CString MyNumberFormat::GetDate(BOOL blnChinese)
{
	if(blnChinese==TRUE)
		strValue="yyyy\"年\"m\"月\"d\"日\";@";
	else
		strValue="yyyy-m-d;@";
	return strValue;
}

CString MyNumberFormat::GetDateTime(BOOL blnChinese)
{
	if(blnChinese==TRUE)
		strValue="yyyy\"年\"m\"月\"d\"日\" h\"时\"mm\"分\"ss\"秒\";@";
	else
		strValue="yyyy-m-d h:mm:ss;@";
	return strValue;
}

CString MyNumberFormat::GetDBNumber(BOOL blnChinese)
{
	if(blnChinese==TRUE)
		strValue="[DBNum1][$-804]G/通用格式";
	else
		strValue="[DBNum2][$-804]G/通用格式";
	return strValue;
}

CString MyNumberFormat::GetFractionNumBer(int DownSum,int DownNum)
{	
	CString str;
	int i;
	if(DownNum>0 && DownSum>0)
	{
		//AfxMessageBox(_T("分母位数和固定数只能设置一个,默认返回分母位数的设置!")
			//,MB_ICONINFORMATION|MB_OK);
	}
	if(DownSum<=0)
	{
		if(DownNum<=0)
		{
			str=_T("# ?/1");
			strValue=str;
			return strValue;
		}
		else
		{
			str.Format(_T("# ?/%d"),DownNum);
			strValue=str;
			return strValue;
		}
	}
	else
	{
		str=_T("# ?/");
		for(i=0;i<DownSum;i++) str=str+"?";
		strValue=str;
		return strValue;
	}
}

CString MyNumberFormat::GetMoney(BOOL blnChinese,int RightSum)
{
	CString str;
	int i;
	if(RightSum<=0) RightSum=0;
	if(blnChinese==TRUE)
	{
		if(RightSum==0)
		{
			str="#,##0";
			strValue="￥"+str+";"+"￥-"+str;
			return strValue;
		}
		else
		{
			str="#,##0.";
			for(i=0;i<RightSum;i++) str=str+"0";
			strValue="￥"+str+";"+"￥-"+str;
			return strValue;
		}

	}
	else
	{
		if(RightSum==0)
		{
			str="#,##0";
			strValue="$"+str+";"+"$-"+str;
			return strValue;
		}
		else
		{
			str="#,##0.";
			for(i=0;i<RightSum;i++) str=str+"0";
			strValue="$"+str+";"+"$-"+str;
			return strValue;
		}
	}
}

CString MyNumberFormat::GetPercentNumBer(int RightSum)
{
	CString str;
	int i;
	if(RightSum<=0) RightSum=0;
	if(RightSum==0)
	{
		str="0%";
		strValue=str;
		return strValue;
	}
	else
	{
		str="0.";
		for(i=0;i<RightSum;i++) str=str+"0";
		strValue=str+"%";
		return strValue;
	}
}

CString MyNumberFormat::GetTechNumBer(int RightSum)
{
	CString str;
	int i;
	if(RightSum<=0) RightSum=0;
	str="0.";
	for(i=0;i<RightSum;i++) str=str+"0";
	strValue=str+"E+00";
	return strValue;
}

CString MyNumberFormat::GetTime(BOOL blnChinese)
{
	if(blnChinese==TRUE)
	{
		strValue="h\"时\"mm\"分\"ss\"秒\";@";
		return strValue;
	}
	else
	{
		strValue="h:mm:ss;@";
		return strValue;
	}
}

CString MyNumberFormat::GetPost(int Sum)
{
	int i;
	CString str="";
	if(Sum<=0) Sum=1;
	for(i=0;i<Sum;i++)
		str=str+"0";
	strValue=str;
	return strValue;
}

bool CExcelRW::Add_Column(int column)
{
	LPDISPATCH lpDisp;
	char index = 'A' + column - 1 ;
	CString columC ;
	columC.Format(_T("%c"), index) ;
	columC += "1" ;
	lpDisp = MySheet.get_Range(COleVariant(columC),COleVariant(columC));
	ASSERT(lpDisp);
	MyRange.AttachDispatch(lpDisp);
	lpDisp = MyRange.get_EntireColumn() ;
	MyRange.AttachDispatch(lpDisp);
	MyRange.Insert(COleVariant((long)1));
	return true;
}
bool CExcelRW::Delete_Column(int column)
{
	LPDISPATCH lpDisp;
	char index = 'A' + column - 1 ;
	CString columC ;
	columC.Format(_T("%c"), index) ;
	columC += "1" ;
	lpDisp = MySheet.get_Range(COleVariant(columC),COleVariant(columC));
	ASSERT(lpDisp);
	MyRange.AttachDispatch(lpDisp);
	lpDisp = MyRange.get_EntireColumn() ;
	MyRange.AttachDispatch(lpDisp);
	MyRange.Delete(COleVariant((long)1));
	return true;
}
bool CExcelRW::Add_Row(int row)
{
	LPDISPATCH lpDisp;
	CString rowC ;
	rowC.Format(_T("%d"), row) ;
	rowC = "A" + rowC ;
	lpDisp = MySheet.get_Range(COleVariant(rowC),COleVariant(rowC));
	ASSERT(lpDisp);
	MyRange.AttachDispatch(lpDisp);
	lpDisp = MyRange.get_EntireRow() ;
	MyRange.AttachDispatch(lpDisp);
	MyRange.Insert(COleVariant((long)1));
	return true;
}
bool CExcelRW::Add_Row_Items(int row, CStringArray &row_values)
{
	int i = 0, exist = 1;
	char str[8] = "";
	CString cell_value;

	for (i = 0; i < row_values.GetSize(); i++)
	{
		cell_value = row_values.GetAt(i);
		if (i == 5)
		{
			sprintf(str, "F%d", row);
			//exist = _access( cell_value.GetBuffer(cell_value.GetLength()+1), 00); //UF_CFI_ask_file_exist(cell_value, &exist);
			exist = 0 ;
			if (exist == 0)
			{
				CExcelRW::Write_Picture(str, str, cell_value, true);
				CExcelRW::GetAllRange();
			}
		}
		else
		{
			CExcelRW::SetItemText(row, i + 1, cell_value);
		}
	}

	return true;
}
bool CExcelRW::Delete_Row(int row)
{
	LPDISPATCH lpDisp;
	CString rowC ;
	rowC.Format(_T("%d"), row);
	rowC = "A" + rowC ;
	lpDisp = MySheet.get_Range(COleVariant(rowC),COleVariant(rowC));
	ASSERT(lpDisp);
	MyRange.AttachDispatch(lpDisp);
	lpDisp = MyRange.get_EntireRow() ;
	MyRange.AttachDispatch(lpDisp);
	MyRange.Delete(COleVariant((long)1));
	return true;
}

bool CExcelRW::Get_Rows_Columns(int& nrow, int& ncolumn)
{
	nrow = GetRowS();
	ncolumn = GetColS();
	return true;
}

bool CExcelRW::MergeUnits(const CString range1, const CString range2)
{
	return true;
}

bool CExcelRW::Write_Picture(const CString range1, const CString range2, const CString PicPath, bool clamp)
{
	int delete_exist = 0;	//弥补本文件开头的注释（否则链接出错）
	COleVariant m_covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR); 
	CPicture pic;
	CPictures pics;
	CBorder border;
	
	pics = MySheet.Pictures(m_covOptional);
	MyRange = MySheet.get_Range(COleVariant(range1), COleVariant(range2));
	MyRange.Select ();
	if (delete_exist == 0)
	{
		pics.Delete();	//一次性删除已经存在于excel中的所有图片（如果有的话）
		delete_exist = 1;
	}
	pic = pics.Insert (PicPath, m_covOptional);

	if (clamp)
	{
		double width = pic.get_Width() ;
		double height = pic.get_Height() ;
		double scale = width / height ;
		
		double width_range = MyRange.get_Width().dblVal ;
		double height_range = MyRange.get_Height().dblVal ;
		
		double height_res = width_range / scale ;
		double width_res ;
		if (height_res > height_range)
		{
			height_res = height_range ;
			width_res = height_range * scale ;
		}
		else
			width_res = width_range ;
		
		pic.put_Height(0.8 * height_res) ;
		pic.put_Width(0.8 * width_res) ;
	}
	MyRange.Show ();
	MyRange = MySheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("A1")));
	MyRange.Select();
	pic.ReleaseDispatch();
	pics.ReleaseDispatch();
	return true;
}

void CExcelRW::SetColorForBackByZR(int Row,int Column,MyBackStyle BackStyle)
{
	long lRow=0,lCol=0;
	lRow=GetRowS();
	lCol=GetColS();
	if(Row>lRow || Column>lCol)
	{
		CString strText;
		strText.Format(_T("由于(%d,%d)已经超过了(%d,%d)的范围,所以返回空值"),Row,Column,lRow,lCol,Row,Column);
		//AfxMessageBox(strText,MB_OK|MB_ICONERROR);
		return;
	}
	VARIANT lpDisp=MyRange.get_Item(_variant_t(Row), _variant_t(Column));
	CRange rgRgeValue;
	rgRgeValue.AttachDispatch(lpDisp.pdispVal, TRUE);

	LPDISPATCH  LpDisp=NULL;
	CInterior Itor;
	LpDisp=rgRgeValue.get_Interior();
	Itor.AttachDispatch(LpDisp,TRUE);
	if(BackStyle.transparent==TRUE)
		Itor.SetColorIndex((_variant_t)(short)xlNone);
	else
	{
		Itor.SetColor((_variant_t)(long)BackStyle.Color);
		Itor.SetPattern((_variant_t)(short)BackStyle.Pattern);
		Itor.SetPatternColor((_variant_t)(long)BackStyle.PatternColor);
	}
	Itor.ReleaseDispatch();

	return;
}

void CExcelRW::SetMergeCellsByZR(int iStartRow,int iStartColumn,int iEndRow,int iEndColumn,CString strContent)
{
	VARIANT lpDispStart = MyRange.get_Item(_variant_t(iStartRow), _variant_t(iStartColumn));
	VARIANT lpDispEnd = MyRange.get_Item(_variant_t(iEndRow), _variant_t(iEndColumn));
	
	CRange rgRgeValue;
	rgRgeValue.AttachDispatch(MySheet.get_Range(_variant_t(lpDispStart),_variant_t(lpDispEnd)),TRUE);

	rgRgeValue.put_MergeCells((_variant_t)(short)TRUE);

	for(int i=iStartRow;i<=iEndRow;i++) 
	{
		for(int j=iStartColumn;j<=iEndColumn;j++)
		{
			SetItemText(i,j,strContent);
		}
	}

	//rgRgeValue.put_Item(_variant_t(lpDispStart),_variant_t(lpDispEnd), _variant_t(strContent));

	rgRgeValue.ReleaseDispatch();
}