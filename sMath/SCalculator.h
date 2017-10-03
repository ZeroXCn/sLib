/**
* SCalculator类
* 表达式计算器
* @author 吉林大学 计算机科学与技术学院 2006 罗泗勇
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
	static const double Ee;				//自然对数
	static const double Pi;				//圆周率(名字污染)
	static const char NUM[];			//数字符号集
	static const char  OPERATION[];		//操作符号集
private:
	class Fun //处理系统数学函数的类
	{
	public:
		Fun(std::string o, int t, double l = 0.0, double r = 0.0) :op(o), type(t), lvalue(l), rvalue(r){}
		static std::string FUN[];
		double calc();
	private:
		int type; //666 0   1 sin90    2 3!   3  3C2 
		std::string op; //函数类型
		double lvalue; //函数左边的值
		double rvalue; //函数右边的值
		static int FunNum;
	};

	class Unit //双向链表保存运算单元
	{
	public:
		Unit(int p, char o, std::string c, double v, int t, Unit * pr = NULL, Unit * n = NULL);

		static void Release(Unit *head);

		int PRI; //优先级
		char Operation; //操作符
		std::string Code; //原始代码
		double value; //数据

		int Type; //类型 操作符0  数据1  函数2
		Unit * Pre; //构成双向链表
		Unit * Next;
	};

	class Node //表达式树状结构的节点
	{
	public:
		Node(char o, int p, int e = 1, double v = 0, Node * ph = NULL, Node * pl = NULL, Node * pr = NULL);
		
		static void Release(Node * head);

		Node * Head; //节点的根,左树枝,右树枝
		Node * Left;
		Node * Right;
		double GetValue();
		char GetOperation() const { return Operation; }
		int GetPri() const { return PRI; }
		int IsExp() const { return Expression; }
	private:
		char Operation; //操作符
		int PRI; //优先级
		int Expression; //记录该节点是否是表达式0 1
		double value; //该节点的值
	};

private:
	/*
	函数说明:
	1:log是以10为底的工程对数
	2:ln 是以e为底的自然对数
	3:C 计算组合数 输入规则 如计算 3取2的组合   输入表达式 3C2
	4:A 计算排列数 输入规则 如计算 3取2的排列   输入表达式 3A2
	5:! 计算阶乘
	6:^ x的y次方 输入 x^y
	*/
	static int factorial(int n); //阶乘函数
	static int C(int a, int b);
	static int A(int a, int b);

	static bool Isnum(char c);
	static bool Isoperation(char c);

	static Unit * Analyse(std::string exp); //分析表达式并生成链表
	
	static Unit * Calc(Unit * head); //计算双向链表基本单元的值
	static Node * Tree(Unit * head); //生成表达式树
public:
	static double Calculate(std::string exp);
	
};

#endif