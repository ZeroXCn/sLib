#ifndef SFILEHELPER_H
#define SFILEHELPER_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace SFileHelper
{
	static string ReadText(string path)
	{
		string result = "";
		try
		{
			//1.创建流管道
			ifstream in(path.c_str(), ios::in);
			if (!in)throw in;

			//2.创建缓冲区
			char buffer[1024];
			int readCount = -1;

			//3.对返回的readCount个字符进行拼接
			while (!in.eof())
			{
				in.read(buffer, 1024);
				readCount = in.gcount();
				result += string(buffer, readCount);
			}
			//4.关闭流管道
			in.close();

		}
		catch (...){
			return "";
		}
		return result;
	}

	static bool WriteText(string path, string text)
	{
		try
		{
			//1.创建流管道
			ofstream out(path.c_str(), ios::ate);     //ios::app为追加
			if (!out)throw out;

			//2.创建缓冲区
			const char *buffer = text.c_str();
			out.write(buffer, text.size());
			//或者out<<buffer;

			//3.关闭流管道
			out.close();
		}
		catch (...){
			cout << "Can't Open File" << endl;
			return;
		}

	}
};
#endif