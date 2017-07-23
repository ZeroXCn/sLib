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
			//1.�������ܵ�
			ifstream in(path.c_str(), ios::in);
			if (!in)throw in;

			//2.����������
			char buffer[1024];
			int readCount = -1;

			//3.�Է��ص�readCount���ַ�����ƴ��
			while (!in.eof())
			{
				in.read(buffer, 1024);
				readCount = in.gcount();
				result += string(buffer, readCount);
			}
			//4.�ر����ܵ�
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
			//1.�������ܵ�
			ofstream out(path.c_str(), ios::ate);     //ios::appΪ׷��
			if (!out)throw out;

			//2.����������
			const char *buffer = text.c_str();
			out.write(buffer, text.size());
			//����out<<buffer;

			//3.�ر����ܵ�
			out.close();
		}
		catch (...){
			cout << "Can't Open File" << endl;
			return;
		}

	}
};
#endif