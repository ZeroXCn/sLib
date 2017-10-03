/**
* SCalculator��
* ���ʽ������
* @author ���ִ�ѧ �������ѧ�뼼��ѧԺ 2006 ������
* @version v1.0 2008/01
*/
#include "../sCore/SObject.h"

#ifndef SCALCULATOR_H
#define SCALCULATOR_H

#include <cmath>
#include <string>

class SCalculator : public SObject
{

private:
	static const double Ee;				//��Ȼ����
	static const double Pi;				//Բ����(������Ⱦ)
	static const char NUM[];			//���ַ��ż�
	static const char  OPERATION[];		//�������ż�
private:
	class Fun //����ϵͳ��ѧ��������
	{
	public:
		Fun(std::string o, int t, double l = 0.0, double r = 0.0) :op(o), type(t), lvalue(l), rvalue(r){}
		static std::string FUN[];
		double calc();
	private:
		int type; //666 0   1 sin90    2 3!   3  3C2 
		std::string op; //��������
		double lvalue; //������ߵ�ֵ
		double rvalue; //�����ұߵ�ֵ
		static int FunNum;
	};

	class Unit //˫�����������㵥Ԫ
	{
	public:
		Unit(int p, char o, std::string c, double v, int t, Unit * pr = NULL, Unit * n = NULL);

		static void Release(Unit *head);

		int PRI; //���ȼ�
		char Operation; //������
		std::string Code; //ԭʼ����
		double value; //����

		int Type; //���� ������0  ����1  ����2
		Unit * Pre; //����˫������
		Unit * Next;
	};

	class Node //���ʽ��״�ṹ�Ľڵ�
	{
	public:
		Node(char o, int p, int e = 1, double v = 0, Node * ph = NULL, Node * pl = NULL, Node * pr = NULL);
		
		static void Release(Node * head);

		Node * Head; //�ڵ�ĸ�,����֦,����֦
		Node * Left;
		Node * Right;
		double GetValue();
		char GetOperation() const { return Operation; }
		int GetPri() const { return PRI; }
		int IsExp() const { return Expression; }
	private:
		char Operation; //������
		int PRI; //���ȼ�
		int Expression; //��¼�ýڵ��Ƿ��Ǳ��ʽ0 1
		double value; //�ýڵ��ֵ
	};

private:
	/*
	����˵��:
	1:log����10Ϊ�׵Ĺ��̶���
	2:ln ����eΪ�׵���Ȼ����
	3:C ��������� ������� ����� 3ȡ2�����   ������ʽ 3C2
	4:A ���������� ������� ����� 3ȡ2������   ������ʽ 3A2
	5:! ����׳�
	6:^ x��y�η� ���� x^y
	*/
	static int factorial(int n); //�׳˺���
	static int C(int a, int b);
	static int A(int a, int b);

	static bool Isnum(char c);
	static bool Isoperation(char c);

	static Unit * Analyse(std::string exp); //�������ʽ����������
	
	static Unit * Calc(Unit * head); //����˫�����������Ԫ��ֵ
	static Node * Tree(Unit * head); //���ɱ��ʽ��
public:
	static double Calculate(std::string exp);
	
};

#endif