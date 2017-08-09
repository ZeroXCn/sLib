/**
* SFileHelper类
* 简单的文件读写辅助类
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
			//1.创建流管道
			std::ifstream in(path.c_str(), std::ios::in);
			if (!in)throw in;

			//2.创建缓冲区
			char buffer[1024];
			int readCount = -1;

			//3.对返回的readCount个字符进行拼接
			while (!in.eof())
			{
				in.read(buffer, 1024);
				readCount = in.gcount();
				result += std::string(buffer, readCount);
			}
			//4.关闭流管道
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
			//1.创建流管道
			std::ofstream out(path.c_str(), std::ios::ate);     //ios::app为追加
			if (!out)throw out;

			//2.创建缓冲区
			const char *buffer = text.c_str();
			out.write(buffer, text.size());
			//或者out<<buffer;

			//3.关闭流管道
			out.close();
		}
		catch (...){
			std::cout << "Can't Open File" << std::endl;
			return;
		}

	}
};
#endif