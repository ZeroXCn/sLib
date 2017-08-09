#include "../../sParser/SInf.h"
#include <iostream>

int main()
{
	SInfDocument inf;
	inf.Load("D:\\data.txt");
	////////读
	for (int i = 0; i < inf.GetSize(); i++)
	{
		std::cout << inf[i]["Name"].ToStrString() << std::endl;
	}

	///////读
	std::cout << inf.GetValue("Section1", "Age",15).ToInt()<<std::endl;		//第三个参数为默认值

	////////简单写
	inf[0]["Name"] = "gggg";
	inf.Save("D:\\data.txt");


	///////简单写
	SInfSection section;
	section.SetName("NewSection");
	section.SetValue("key1", "value1");
	inf.Insert(section);
	inf.Save("D:\\data.txt");

	//////////////


	return 0;
}