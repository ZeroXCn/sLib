#include "../../sParser/SInf.h"
#include <iostream>

int main()
{
	SInfDocument inf;
	inf.Load("D:\\data.txt");
	////////��
	for (int i = 0; i < inf.GetSize(); i++)
	{
		std::cout << inf[i]["Name"].ToStrString() << std::endl;
	}

	///////��
	std::cout << inf.GetValue("Section1", "Age",15).ToInt()<<std::endl;		//����������ΪĬ��ֵ

	////////��д
	inf[0]["Name"] = "gggg";
	inf.Save("D:\\data.txt");


	///////��д
	SInfSection section;
	section.SetName("NewSection");
	section.SetValue("key1", "value1");
	inf.Insert(section);
	inf.Save("D:\\data.txt");

	//////////////


	return 0;
}