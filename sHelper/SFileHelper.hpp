/**
* SFileHelper��
* �򵥵��ļ���д������
* @author ZeroX
* @version v1.0 03/08/2017(25/04/2016)
*/

#ifndef SFILEHELPER_H
#define SFILEHELPER_H
#include <iostream>
#include <string>
#include <fstream>

namespace SFileHelper
{
	static std::string ReadText(std::string path)
	{
		std::string result = "";
		try
		{
			//1.�������ܵ�
			std::ifstream in(path.c_str(), std::ios::in);
			if (!in)throw in;

			//2.����������
			char buffer[1024];
			int readCount = -1;

			//3.�Է��ص�readCount���ַ�����ƴ��
			while (!in.eof())
			{
				in.read(buffer, 1024);
				readCount = in.gcount();
				result += std::string(buffer, readCount);
			}
			//4.�ر����ܵ�
			in.close();

		}
		catch (...){
			return "";
		}
		return result;
	}

	static bool WriteText(std::string path, std::string text)
	{
		try
		{
			//1.�������ܵ�
			std::ofstream out(path.c_str(), std::ios::ate);     //ios::appΪ׷��
			if (!out)throw out;

			//2.����������
			const char *buffer = text.c_str();
			out.write(buffer, text.size());
			//����out<<buffer;

			//3.�ر����ܵ�
			out.close();
		}
		catch (...){
			std::cout << "Can't Open File" << std::endl;
			return;
		}

	}
};
#endif