#include "AdoConn.h"

int main(int argc, char* argv[])
{
	AdoConn m_adoConn;
	if (FAILED(m_adoConn.InitAdoConn()))
	{
		m_adoConn.CloseAdoConn();
		return 1;
	}

	string sql = "select * from bands";
	vector<string> results;
	m_adoConn.SelectData(sql,results);
	
	m_adoConn.CloseAdoConn();
	
	return 0;
}