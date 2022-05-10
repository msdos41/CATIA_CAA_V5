//===================================================================
// COPYRIGHT tang 2022/05/05
//===================================================================
// AdoConn.cpp
// Header definition of class AdoConn
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2022/05/05 Creation: Code generated by the 3DS wizard
//===================================================================

#include "AdoConn.h"

//-----------------------------------------------------------------------------
// AdoConn : constructor
//-----------------------------------------------------------------------------
AdoConn::AdoConn():CATBaseUnknown()
{
//
//TODO: Add the constructor code here
//
}

//-----------------------------------------------------------------------------
// AdoConn : destructor
//-----------------------------------------------------------------------------

AdoConn::~AdoConn()
{
//
// TODO: Place code here.
//
}

HRESULT AdoConn::InitAdoConn()
{
	HRESULT hr = ::CoInitialize(NULL); 

	if (SUCCEEDED(hr))
	{
		if(!Connect())
		{
			return E_FAIL;
		}
	}
	else
	{
		cout<<"COM CoInitialize NOT succeeded"<<endl;
		return E_FAIL;
	}

	return hr;
}

void AdoConn::CloseAdoConn()
{
	if (m_pRecordset != NULL)
	{
		m_pRecordset->Close();
	}
	if (m_pConnection != NULL)
	{
		m_pConnection->Close();
	}
	CoUninitialize();
}

bool AdoConn::Connect()
{
	if (m_pConnection==NULL || adStateClosed == m_pConnection->State)
	{
		try
		{
			if (!FAILED(m_pConnection.CreateInstance(_uuidof(Connection))))
			{
				m_pConnection->CommandTimeout = 30;			//unit s
				//_bstr_t strConnect = "driver={SQL Server};Server=(localdb)\Projects;Database=record_company;UID=;PWD=";
				//_bstr_t strConnect = "Data Source=(localdb)\\v11.0;Initial Catalog=record_company;Integrated Security=True;Connect Timeout=15;Encrypt=False;TrustServerCertificate=False";
				_bstr_t strConnect("Provider=SQLNCLI11.1;Integrated Security=SSPI;Persist Security Info=False;User ID="";Initial Catalog=record_company;Data Source=(LocalDB)\\v11.0;Initial File Name="";Server SPN=""");
				m_pConnection->Open(strConnect,"","",adModeUnknown);
				return true;
			}
		}
		catch (_com_error e)
		{
			cout<<e.Description()<<endl;
		}
	}
	return false;
}

bool AdoConn::ReConnect()
{
	long ReConnectTimes = 0;
	while (true)
	{
		++ReConnectTimes;
		cout<<"Reconnect times: "<<ReConnectTimes<<endl;
		Sleep(2000);
		if (Connect())
		{
			return true;
		}
	}
	return false;
}

//执行SQL语句
int AdoConn::ExecuteSQL(_bstr_t bstrSQL)
{    
	int ret = -1;

	try		
	{			
		if(m_pConnection == NULL || adStateClosed == m_pConnection->State)		// 是否已经连接数据库		
		{
			if (!Connect())
			{
				return -1;
			}
		}

		_variant_t RecordsAffected;
		m_pConnection->Execute(bstrSQL,&RecordsAffected,adCmdText); // 执行SQL语句

		// Connection对象的Execute方法:(_bstr_t CommandText,		
		// VARIANT * RecordsAffected, long Options )		
		// 其中CommandText是命令字串，通常是SQL命令。		
		// 参数RecordsAffected是操作完成后所影响的行数,		
		// 参数Options表示CommandText的类型：adCmdText-文本命令；adCmdTable-表名		
		// adCmdProc-存储过程；adCmdUnknown-未知

		//return true; //没异常就返回true
		//ret = RecordsAffected.lVal;	//更新行数
		ret = 0;

	}
	catch(_com_error e)	 // 捕捉异常		
	{	
		cout<<"Execute sql error,retry,"<<e.Description()<<" sql:" << bstrSQL<<endl;
		//AfxMessageBox(e.Description());	

		//LLogWarn("Execute sql error,retry,"<< (char*)(e.Description())<<" sql:" << sql);
		//偶发连接错误处理
		//报:[DBNETLIB][ConnectionRead (recv()).]一般性网络错误。请检查网络文档
		//处理 lsl-20200828
		//网上说的是Data Source=10.237.103.28,1433，后面要加上端口号
		string errorInfo(e.Description());
		if (errorInfo.find("DBNETLIB") != string::npos)
		{
			if (ReConnect())
			{
				ret = ExecuteSQL(bstrSQL);//再次执行
			}
			if (ret != 0)
			{
				//LLogError("retry Execute error,error:" << (char*)(e.Description()) << " sql:" << sql);
				cout<<"retry Execute error,error:"<<e.Description()<<" sql:" << bstrSQL<<endl;
			}
		}
	}	

	return ret;
}

int AdoConn::SelectData(const string& sql, std::vector<string>& results)
{
	int ret = -1;

	if (sql.size() > 0)
	{
		if (NULL == m_pConnection || adStateClosed == m_pConnection->State)
		{
			if (!ReConnect())
			{
				return -1;
			}
		}

		try
		{
			_variant_t RecordsAffected;
			//改进，直接用Execute，返回_RecordsetPtr就很快，很棒！
			_RecordsetPtr pRecordset = m_pConnection->Execute(_bstr_t(sql.c_str()), &RecordsAffected, adCmdText);
			long line = 0;
			while (NULL != pRecordset && !pRecordset->adoEOF && adStateClosed != pRecordset->State)
			{
				long count = pRecordset->Fields->Count;
				++line;
				stringstream ss;
				ss << line;
				for (long i = 0; i < count; ++i)
				{
					//按列序号，从0开始
					_variant_t rusultGet = pRecordset->Fields->GetItem(long(i))->Value;

					char midData[MAXCHAR] = { 0 };
					rusultGet.ChangeType(VT_BSTR);//统一转成字符串，否则下面有可能出错
					WideCharToMultiByte(CP_ACP, 0, rusultGet.bstrVal, -1, midData, MAXCHAR, NULL, NULL);
					ss << "," << midData;
				}
				results.emplace_back(ss.str());
				pRecordset->MoveNext();
			}
			pRecordset = NULL;
			ret = 0;
		}
		catch (_com_error e)
		{
			cout<<"Execute sql error,retry,"<<e.Description()<<" sql:" << sql<<endl;
			//LLogWarn("Execute sql error,retry," << (char*)(e.Description()) << " sql:" << sql);
			//偶发连接错误处理
			//报:[DBNETLIB][ConnectionRead (recv()).]一般性网络错误。请检查网络文档
			//处理 lsl-20200828
			//网上说的是Data Source=10.237.103.28,1433，后面要加上端口号
			string errorInfo(e.Description());
			if (errorInfo.find("DBNETLIB") != string::npos)
			{
				if (ReConnect())
				{
					ret = SelectData(sql, results);//再次执行
				}
				if (ret != 0)
				{
					//LLogError("retry Execute error,error:" << (char*)(e.Description()) << " sql:" << sql);
					cout<<"retry Execute error,error:"<<e.Description()<<" sql:" << sql<<endl;
				}
			}
		}
	}
	return ret;
}
