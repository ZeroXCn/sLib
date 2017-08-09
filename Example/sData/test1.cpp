//#include <mysql.h>		//库的头文件
#include <sqlite3.h>		//库的头文件
#include <iostream>
#include "../../sData/SSql.h"
//

int main()
{
	//SSqlConnection con = SSqlDriverManager::GetConnection<SMysql>("127.0.0.1","root","root",3306);
	SSqlConnection con = SSqlDriverManager::GetConnection<SSqlite>("D://test1.db");
	SSqlStatement stmt = con.CreateStatement();
	SSqlResultSet ret;
	stmt.Excute("SET NAMES GBK");
	ret = stmt.ExcuteQuery("select * from table");

	while (ret.Next()){

		std::cout << ret.GetValue(1) << std::endl;
	}
	
	con.Close();
	return 0;
}