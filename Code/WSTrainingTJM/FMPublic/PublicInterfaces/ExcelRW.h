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

//�»��ߵ�����
#define xlUnderlineStyleDouble -4119
#define xlUnderlineStyleDoubleAccounting 5
#define xlUnderlineStyleNone -4142
#define xlUnderlineStyleSingle 2
#define xlUnderlineStyleSingleAccounting 4
//�߿�λ
#define xlDiagonalDown 5
#define xlDiagonalUp 6
#define xlEdgeBottom 9
#define xlEdgeLeft 7
#define xlEdgeRight 10
#define xlEdgeTop 8
#define xlInsideHorizontal 12
#define xlInsideVertical 11
//�߿�������
#define xlContinuous 1
#define xlDash -4115
#define xlDashDot 4
#define xlDashDotDot 5
#define xlDot -4118
#define xlDouble -4119
#define xlLineStyleNone -4142
#define xlNone -4142
#define xlSlantDashDot 13
//����ˮƽ���뷽ʽ
#define xlGeneral 1
#define xlCenter -4108
#define xlLeft -4131
#define xlRight -4152
#define xlFill 5
#define xlJustify -4130
//���崹ֱ���뷽ʽ
#define xlTop -4160
#define xlBottom -4107
//�߿��ߵĴ�ϸ
#define xlHairline 1
#define xlMedium -4138
#define xlThick 4
#define xlThin 2
//����ͼ��������
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
//�߿����ò�����
class MyBorder
{
public:
	//������״
	short LineStyle;
	//����
    short Weight;
	//��ɫ
    long Color;
	//���캯��
	MyBorder();
};

//�������ò�����
class MyBackStyle
{
public:
	//������ɫ
	long Color;
	//����ͼ��
    short Pattern;
	//����ͼ����ɫ
    long PatternColor;
	//͸����͸��
	BOOL transparent;
	//���캯��
	MyBackStyle();
};
//�������ò�����
class MyFont
{
public:
	//����
    CString Name;
	//��С
	long size;
	//ǰ��
	long ForeColor;
	//����
	BOOL Bold;
	//б��
	BOOL Italic;
	//�м���
	BOOL Strikethrough;
	//��Ӱ
	BOOL Shadow;
	//�±�
	BOOL Subscript;
	//�ϱ�
	BOOL Superscricp;
	//�»���
	short Underline;
	//���캯��
	MyFont();
};
//���ֶ��뷽ʽ���ò�����
class MyAlignment
{
public:
	//ˮƽ����
	short HorizontalAlignment;
	//��ֱ����
	short VerticalAlignment;
	//���캯��
	MyAlignment();
};
//���������͵����ò�����
class MyNumberFormat
{
public:
	MyNumberFormat();
	//���ò���
	CString strValue;
	//�����ı����͵�����
	CString GetText();
	//�������ָ�ʽ������
	//blnBox: ʹ�÷ָ��� RightSum: С��λ�� 
	CString GetNumber(BOOL blnBox,int RightSum);
	//���ػ��Ҹ�ʽ������
	//blnChinese: TURE:"��",FALSE:"$"
	//RightSum: С��λ�� 
	CString GetMoney(BOOL blnChinese,int RightSum);
	//�������ڸ�ʽ������
	//blnChinese: TURE:"������",FALSE:"-"
	CString GetDate(BOOL blnChinese);
	//����ʱ���ʽ������
	//blnChinese: TURE:"ʱ����",FALSE:":"
	CString GetTime(BOOL blnChinese);
	//���س�������
	CString GetGeneral();
	//�����������ֵ�����
	//blnChinese: TURE:��д,FALSE:Сд
	CString GetDBNumber(BOOL blnChinese);
	//���ذٷ���������
	//RightSum: С��λ�� 
	CString GetPercentNumBer(int RightSum);
	//���ط���������
	//DownSum:��ĸλ�� DownNum(0): �̶���ĸ��(0)
	CString GetFractionNumBer(int DownSum,int DownNum);
	//���ؿ�ѧ����������
	//RightSum: С��λ�� 
	CString GetTechNumBer(int RightSum);
	//����6λ���������ʽ
	//Sum: �̶����������λ��
	CString GetPost(int Sum);
	//�������ڼ�ʱ�������
	//blnChinese: TURE:"������ʱ����",FALSE:"-:"
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



	BOOL Open();                                 //���µ�Excel�ļ�
	
	BOOL Open(CString strFile);                  //��strFile�ļ�
	
	BOOL OpenSheet(CString strSheet);            //����ΪstrSheet�ı�
	
	BOOL SetItemText(long Row,long Col,CString strText);//����(ROW,COL)���ַ�strText
	
	CString GetItemText(long Row,long Col);             //ȡ��(ROW,COL)���ַ�
	
	void Exit();                                        //�˳�excel
	
	void SetVisible(BOOL blnVisible);                  //��ʾexcel
	
	BOOL IsFileExist(CString strFn, BOOL bDir);         //���Ҵ��ļ��Ƿ����
	
	void Save();                                        //�Զ�����(��Դ��Ѿ����ڵ��ļ�)
	
	BOOL SaveAs(CString strPath);                        //����ΪstrPath
	
	void AddSheet(CString strSheet);                     //����µı�
	
	void GetRange(CString strBegin,CString strEnd);         //�õ��µ�ѡ������
	void GetCharacters( int  strBegin,int strEnd);
	
	void AutoColFit();                                      //���Զ�չ��

	void AutoRowFit();                               	//���Զ�չ��
	
	void SetWrapText(BOOL blnTrue);                    //�����Զ�����
	
	void GetFont(MyFont &font);                       //�õ���ǰ����
	
	void SetFont(MyFont font);                        //��������

	void GetAllRange();	                              //�õ���������
	
	void SetMergeCells(BOOL blnTrue);                  //�ϲ���Ԫ��
	
	void SetBackStyle(MyBackStyle BackStyle);                  //���ñ���
	
	//void SetBorderLine(short Xposition,MyBorder XBorder);       //���ñ߿�
	
	void SetBorderLine(long Row,long Col,short Xposition,MyBorder XBorder);
	void GetAlignment(MyAlignment &XMyAlignment);           //�õ����뷽ʽ
	
	void SetAlignment(MyAlignment XMyAlignment);           //���ö��뷽ʽ
	
	long GetRowS();                                       //�õ�����
	
	long GetColS();                                        //�õ�����
	
	void SetNumberFormat(MyNumberFormat XNumberFormat);   //�������ݵ�����
	
	void SetColumnWidth(int intWidth);                    //�����п�
	
	double GetRowHeight();                     //�õ���ǰ�и�
	
	void SetRowHeight(int intHeight);            //�����и�
	
	void PrintOut(short CopySum);                //��ӡ//CopySum:��ӡ�ķ���
	
	void PrePrintOut(BOOL blnEnable);                //��ӡԤ��//blnEnable:TRUE-�����޸� FALSE-������
	
	void InsertPicture(CString strFilePath);           	//����ͼƬ//strFilePath:�ļ���·��
	
	void SetBackPicture(CString strFilePath);             	//���ñ���ͼƬ//strFilePath:�ļ���·��
	
	CString GetAppPath();                                  //���ص�ǰ��������·��

	void SetColorForBackByZR(int Row,int Column,MyBackStyle BackStyle);  //���ñ�񱳾���ɫ

	void SetMergeCellsByZR(int iStartRow,int iStartColumn,int iEndRow,int iEndColumn,CString strContent);

protected:
public:
	//Excel��Ӧ��
	CApplication	MyApp;  
	CWorkbook		MyBook;
	CWorksheet		MySheet;   
	CWorkbooks		MyBooks;   
	CWorksheets		MySheets;   
	CRange			MyRange;  
	CString strFilePath;
};

#endif // !defined(AFX_EXCELRW_H__5924BB3B_3F3E_4273_AF1B_15E31FC929AC__INCLUDED_)
