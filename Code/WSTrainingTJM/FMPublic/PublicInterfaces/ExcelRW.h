// ExcelRW.h: interface for the CExcelRW class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCELRW_H__5924BB3B_3F3E_4273_AF1B_15E31FC929AC__INCLUDED_)
#define AFX_EXCELRW_H__5924BB3B_3F3E_4273_AF1B_15E31FC929AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxdisp.h>
//#include <uf_cfi.h>
#include "CApplication.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CRange.h"
#include "CWorksheets.h"
#include "CPicture.h"
#include "CPictures.h"
#include "CBorder.h"
#include "CBorders.h"
#include "CExcelFont.h"
#include "CInterior.h"

//#include "iostream.h"
#include <iostream>
using namespace std;

#include "CATBaseUnknown.h"
#include "ModPubExcel.h"

//下滑线的种类
#define xlUnderlineStyleDouble -4119
#define xlUnderlineStyleDoubleAccounting 5
#define xlUnderlineStyleNone -4142
#define xlUnderlineStyleSingle 2
#define xlUnderlineStyleSingleAccounting 4
//边框方位
#define xlDiagonalDown 5
#define xlDiagonalUp 6
#define xlEdgeBottom 9
#define xlEdgeLeft 7
#define xlEdgeRight 10
#define xlEdgeTop 8
#define xlInsideHorizontal 12
#define xlInsideVertical 11
//边框划线类型
#define xlContinuous 1
#define xlDash -4115
#define xlDashDot 4
#define xlDashDotDot 5
#define xlDot -4118
#define xlDouble -4119
#define xlLineStyleNone -4142
#define xlNone -4142
#define xlSlantDashDot 13
//字体水平对齐方式
#define xlGeneral 1
#define xlCenter -4108
#define xlLeft -4131
#define xlRight -4152
#define xlFill 5
#define xlJustify -4130
//字体垂直对齐方式
#define xlTop -4160
#define xlBottom -4107
//边框划线的粗细
#define xlHairline 1
#define xlMedium -4138
#define xlThick 4
#define xlThin 2
//背景图案的类型
#define xlSolid 1
#define xlGray8 18
#define xlGray75 -4126
#define xlGray50 -4125
#define xlGray25 -4124
#define xlGray16 17
#define xlHorizontal -4128
#define xlVertical -4166
#define xlDown -4121
#define xlUp -4162
#define xlChecker 9
#define xlSemiGray75 10
#define xlLightHorizontal 11
#define xlLightVertical 12
#define xlLightDown 13
#define xlLightUp 14
#define xlGrid 15
#define xlCrissCross 16
//边框设置参数类
class MyBorder
{
public:
	//线条形状
	short LineStyle;
	//粗线
    short Weight;
	//颜色
    long Color;
	//构造函数
	MyBorder();
};

//背景设置参数类
class MyBackStyle
{
public:
	//背景颜色
	long Color;
	//背景图案
    short Pattern;
	//背景图案颜色
    long PatternColor;
	//透明不透明
	BOOL transparent;
	//构造函数
	MyBackStyle();
};
//字体设置参数类
class MyFont
{
public:
	//名字
    CString Name;
	//大小
	long size;
	//前景
	long ForeColor;
	//粗体
	BOOL Bold;
	//斜体
	BOOL Italic;
	//中间线
	BOOL Strikethrough;
	//阴影
	BOOL Shadow;
	//下标
	BOOL Subscript;
	//上标
	BOOL Superscricp;
	//下划线
	short Underline;
	//构造函数
	MyFont();
};
//文字对齐方式设置参数类
class MyAlignment
{
public:
	//水平对齐
	short HorizontalAlignment;
	//垂直对齐
	short VerticalAlignment;
	//构造函数
	MyAlignment();
};
//列数据类型的设置参数类
class MyNumberFormat
{
public:
	MyNumberFormat();
	//设置参数
	CString strValue;
	//返回文本类型的设置
	CString GetText();
	//返回数字格式的设置
	//blnBox: 使用分隔符 RightSum: 小数位数 
	CString GetNumber(BOOL blnBox,int RightSum);
	//返回货币格式的设置
	//blnChinese: TURE:"￥",FALSE:"$"
	//RightSum: 小数位数 
	CString GetMoney(BOOL blnChinese,int RightSum);
	//返回日期格式的设置
	//blnChinese: TURE:"年月日",FALSE:"-"
	CString GetDate(BOOL blnChinese);
	//返回时间格式的设置
	//blnChinese: TURE:"时分秒",FALSE:":"
	CString GetTime(BOOL blnChinese);
	//返回常规设置
	CString GetGeneral();
	//返回特殊数字的设置
	//blnChinese: TURE:大写,FALSE:小写
	CString GetDBNumber(BOOL blnChinese);
	//返回百分数的设置
	//RightSum: 小数位数 
	CString GetPercentNumBer(int RightSum);
	//返回分数的设置
	//DownSum:分母位数 DownNum(0): 固定分母数(0)
	CString GetFractionNumBer(int DownSum,int DownNum);
	//返回科学计数的设置
	//RightSum: 小数位数 
	CString GetTechNumBer(int RightSum);
	//返回6位邮政编码格式
	//Sum: 固定邮政编码的位数
	CString GetPost(int Sum);
	//返回日期加时间的设置
	//blnChinese: TURE:"年月日时分秒",FALSE:"-:"
	CString GetDateTime(BOOL blnChinese);
};

class ExportedByModPubExcel CExcelRW: public CATBaseUnknown
{
  CATDeclareClass;

public:
	bool SetCurrentSheetName(CString sheetname);
	bool GetSheetsCount(int& sheetcount);
	CString GetCurrentSheetName();
	bool OpenSheet(int i = 1);
	bool Add_Column(int column);
	bool Delete_Column(int column);
	bool Add_Row(int row);
	bool Add_Row_Items(int row, CStringArray &row_values);
	bool Delete_Row(int row);
	bool Get_Rows_Columns(int& nrow, int& ncolumn);
	bool MergeUnits(const CString range1, const CString range2);
	bool Write_Picture(const CString range1, const CString range2, const CString PicPath, bool clamp = false);
public:
	CExcelRW();
	~CExcelRW();
	CExcelRW (CExcelRW &);
    CExcelRW& operator=(CExcelRW&);



	BOOL Open();                                 //打开新的Excel文件
	
	BOOL Open(CString strFile);                  //打开strFile文件
	
	BOOL OpenSheet(CString strSheet);            //打开名为strSheet的表
	
	BOOL SetItemText(long Row,long Col,CString strText);//设置(ROW,COL)的字符strText
	
	CString GetItemText(long Row,long Col);             //取得(ROW,COL)的字符
	
	void Exit();                                        //退出excel
	
	void SetVisible(BOOL blnVisible);                  //显示excel
	
	BOOL IsFileExist(CString strFn, BOOL bDir);         //查找此文件是否存在
	
	void Save();                                        //自动保存(针对打开已经存在的文件)
	
	BOOL SaveAs(CString strPath);                        //保存为strPath
	
	void AddSheet(CString strSheet);                     //添加新的表
	
	void GetRange(CString strBegin,CString strEnd);         //得到新的选择区域
	void GetCharacters( int  strBegin,int strEnd);
	
	void AutoColFit();                                      //列自动展开

	void AutoRowFit();                               	//行自动展开
	
	void SetWrapText(BOOL blnTrue);                    //设置自动换行
	
	void GetFont(MyFont &font);                       //得到当前字体
	
	void SetFont(MyFont font);                        //设置字体

	void GetAllRange();	                              //得到整个区域
	
	void SetMergeCells(BOOL blnTrue);                  //合并单元格
	
	void SetBackStyle(MyBackStyle BackStyle);                  //设置背景
	
	//void SetBorderLine(short Xposition,MyBorder XBorder);       //设置边框
	
	void SetBorderLine(long Row,long Col,short Xposition,MyBorder XBorder);
	void GetAlignment(MyAlignment &XMyAlignment);           //得到对齐方式
	
	void SetAlignment(MyAlignment XMyAlignment);           //设置对齐方式
	
	long GetRowS();                                       //得到列数
	
	long GetColS();                                        //得到行数
	
	void SetNumberFormat(MyNumberFormat XNumberFormat);   //设置数据的类型
	
	void SetColumnWidth(int intWidth);                    //设置列宽
	
	double GetRowHeight();                     //得到当前行高
	
	void SetRowHeight(int intHeight);            //设置行高
	
	void PrintOut(short CopySum);                //打印//CopySum:打印的份数
	
	void PrePrintOut(BOOL blnEnable);                //打印预览//blnEnable:TRUE-允许修改 FALSE-不允许
	
	void InsertPicture(CString strFilePath);           	//插入图片//strFilePath:文件名路径
	
	void SetBackPicture(CString strFilePath);             	//设置背景图片//strFilePath:文件名路径
	
	CString GetAppPath();                                  //返回当前程序所在路径

	void SetColorForBackByZR(int Row,int Column,MyBackStyle BackStyle);  //设置表格背景颜色

	void SetMergeCellsByZR(int iStartRow,int iStartColumn,int iEndRow,int iEndColumn,CString strContent);

protected:
public:
	//Excel的应用
	CApplication	MyApp;  
	CWorkbook		MyBook;
	CWorksheet		MySheet;   
	CWorkbooks		MyBooks;   
	CWorksheets		MySheets;   
	CRange			MyRange;  
	CString strFilePath;
};

#endif // !defined(AFX_EXCELRW_H__5924BB3B_3F3E_4273_AF1B_15E31FC929AC__INCLUDED_)
