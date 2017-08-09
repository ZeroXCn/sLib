/**
* SSql接口类
* 封装SQL一些通用操作-具体由对应数据库实现
* @author ZeroX
* @version v1.0 08/08/2017
*/
/* 所有操作必须有具体数据库继承重写实现 */
/* 如需自定义,请继承Impl接口类,并重写其函数 */
#ifndef _SSQL_H_
#define _SSQL_H_

#include "extern\SSqlite.hpp"
#include "extern\SMysql.hpp"


//////
#include "SSqlDriverManager.h"
#include "SSqlDriverManager.cpp"

#include "SSqlConnection.h"
#include "SSqlException.h"
#include "SSqlResultSet.h"
#include "SSqlStatement.h"

#endif