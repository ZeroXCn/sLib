/**
* SIni类
* 读取ini配置文件
* @author ZeroX
* @version v1.0 04/08/2017(27/01/2016)
*/
#include "../sCore/SObject.h"
#include "extern/inifile2/inifile.h"
using namespace inifile;
#ifndef _SINI_H_
#define _SINI_H_
class SIni:
	public SObject,
	public IniFile
{

};

#endif