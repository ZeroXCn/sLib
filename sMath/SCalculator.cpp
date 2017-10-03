#include "SCalculator.h"

const char SCalculator::NUM[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };
const char SCalculator::OPERATION[] = { '+', '-', '*', '/' };
const double SCalculator::Pi = 3.14159265358979;
const double SCalculator::Ee = 2.71828182818281;

//

int SCalculator::Fun::FunNum = 10;
std::string SCalculator::Fun::FUN[] = { "!", "sin", "cos", "tan", "log", "ln", "C", "A", "^", "-" };

double SCalculator::Fun::calc() //计算系统函数的值
{
	if (type == 0)
		return lvalue;
	else
	{
		if (op == "!")
			return factorial((int)lvalue);
		if (op == "sin")
			return sin(rvalue / 180 * Pi);
		if (op == "cos")
			return cos(rvalue / 180 * Pi);
		if (op == "tan")
			return tan(rvalue / 180 * Pi);
		if (op == "log")
			return log10(rvalue);
		if (op == "ln")
			return log10(rvalue) / log10(Ee);
		if (op == "C")
			return C((int)lvalue, (int)rvalue);
		if (op == "A")
			return A((int)lvalue, (int)rvalue);
		if (op == "^")
			return pow(lvalue, rvalue);
		if (op == "-")
			return -rvalue;
		else
		{
			//std::string err = "暂时没有函数" + op;
			//MessageBox(NULL, err.c_str(), "错误", MB_OK);
			return 0;
		}
	}
}

SCalculator::Unit::Unit(int p, char o, std::string c, double v, int t, Unit * pr , Unit * n )
:PRI(p), Operation(o), Code(c), value(v), Type(t), Pre(pr), Next(n)
{

}
void SCalculator::Unit::Release(Unit *head)
{
	if (!head)return;
	Unit * p = head;
	while (p != NULL)
	{
		Unit *temp = p->Next;
		delete p;
		p = temp;
	}
}


SCalculator::Node::Node(char o, int p, int e , double v, Node * ph , Node * pl, Node * pr)
:Operation(o), PRI(p), Expression(e), value(v), Head(ph), Left(pl), Right(pr)
{

}
void SCalculator::Node::Release(Node *root)
{
	if (root){
		if (root->Left)Release(root->Left);
		if (root->Right)Release(root->Right);
		delete root;
	}
}

double SCalculator::Node::GetValue() //运算该节点的值
{
	if (IsExp()) //该节点的值还未算出来
	{
		double lvalue, rvalue;
		lvalue = Left->GetValue();
		rvalue = Right->GetValue();
		Expression = 0;
		char op = GetOperation();
		switch (op)
		{
		case '+':
			return lvalue + rvalue;
		case '-':
			return lvalue - rvalue;
		case '*':
			return lvalue*rvalue;
		case '/':
			return lvalue / rvalue;
		default:
			return 0;
		}
	}
	else
		return value;
}


////////////////////////////////////////////////////////////
/*
函数说明:
1:log是以10为底的工程对数
2:ln 是以e为底的自然对数
3:C 计算组合数 输入规则 如计算 3取2的组合   输入表达式 3C2
4:A 计算排列数 输入规则 如计算 3取2的排列   输入表达式 3A2
5:! 计算阶乘
6:^ x的y次方 输入 x^y
*/

int SCalculator::factorial(int n) //阶乘函数
{
	int i, s = 1;
	for (i = 1; i <= n; i++)
		s *= i;
	return s;
}

int SCalculator::C(int a, int b)
{
	return factorial(a) / (factorial(b)*factorial(a - b));
}

int SCalculator::A(int a, int b)
{
	return factorial(a) / factorial(b);
}





bool SCalculator::Isnum(char c)
{
	for (int i = 0; i<sizeof(NUM); i++)
	{
		if (c == NUM[i])
			return true;
	}
	return false;
}

bool SCalculator::Isoperation(char c)
{
	for (int i = 0; i<sizeof(OPERATION); i++)
	{
		if (c == OPERATION[i])
			return true;
	}
	return false;
}

SCalculator::Unit * SCalculator::Analyse(std::string exp) //分析表达式并生成链表
{
	int pri = 0; //当前优先级
	int stat = 1; //当前的读入状态 括号 0  运算符 1  其他 2
	Unit * head = NULL, *p = NULL;
	int i = 0, explen;
	explen = exp.size();
	for (i = 0; i<explen; i++)
	{
		char c = exp.at(i);
		if (c == '(')
		{
			pri += 3;
			stat = 0;
		}
		else if (c == ')')
		{
			pri -= 3;
			stat = 0;
		}
		else if (Isoperation(c) && stat != 1) //操作符后的当正负号处理
		{
			stat = 1;
			Unit * temp = p;
			int add_pri; //自身增加的优先级
			if (c == '+' || c == '-')
				add_pri = 1;
			else
				add_pri = 2;
			p->Next = new Unit(pri + add_pri, c, " ", 0, 0);
			p = p->Next;
			p->Pre = temp;
		}
		else //其他的当做函数处理
		{
			stat = 2;
			std::string function = "";
			while (i<explen && (c = exp.at(i), !Isoperation(c)) && c != ')')
			{
				function += c;
				i++;
			}
			i--;

			if (head == NULL)
			{
				p = new Unit(pri, ' ', function, 0, 2);
				head = p;
			}
			else
			{
				Unit * temp = p;
				p->Next = new Unit(pri, ' ', function, 0, 2);
				p = p->Next;
				p->Pre = temp;
			}
		}
	}
	return head;
}

SCalculator::Unit * SCalculator::Calc(Unit * head) //计算双向链表基本单元的值
{
	Unit * p = head;
	while (p != NULL)
	{
		if (p->Type != 0) //非操作符
		{
			std::string temp = p->Code;
			std::string op;
			double lvalue = 0, rvalue = 0;
			int l_point = 0, r_point = 0;
			int type = 0;
			unsigned int i = 0;
			char ch;
			while (i<temp.size() && (ch = temp.at(i), Isnum(ch)))
			{
				if (ch == '.')
				{
					l_point++;
					i++;
					continue;
				}
				if (!l_point)
					lvalue *= 10;
				lvalue += (ch - '0')*pow(10, -l_point);
				i++;
				if (l_point)
					l_point++;
			}
			while (i<temp.size() && (ch = temp.at(i), !Isnum(ch)))
			{
				op += ch;
				type = 1;
				i++;
			}
			while (i<temp.size() && (ch = temp.at(i), Isnum(ch)))
			{
				if (ch == '.')
				{
					r_point++;
					i++;
					continue;
				}
				if (!r_point)
					rvalue *= 10;
				rvalue += (ch - '0')*pow(10, -r_point);
				i++;
				if (r_point)
					r_point++;
			}
			Fun * f = new Fun(op, type, lvalue, rvalue);
			p->value = f->calc();
		}
		p = p->Next;
	}
	return head;
}

SCalculator::Node * SCalculator::Tree(Unit * head) //生成表达式树
{
	Node * root = NULL, *proot = NULL, *pbranch = NULL;
	Unit * p = head;
	int now_pri; //当前优先级
	bool hadop = false;
	while (p != NULL)
	{
		if (p->Type == 0) //如果是一个操作符
		{
			hadop = true;
			if (root == NULL)
			{
				proot = new Node(p->Operation, p->PRI, 1);
				root = proot;
				pbranch = root;
				now_pri = p->PRI;
				proot->Left = new Node(' ', 0, 0, p->Pre->value);
				proot->Right = new Node(' ', 0, 0, p->Next->value);
			}
			else
			{
				if (p->PRI<now_pri) //优先级低于当前优先级,树根方向
				{
					proot = new Node(p->Operation, p->PRI, 1); //新的树根
					proot->Left = root; //根的变换
					proot->Left->Head = proot;
					proot->Right = new Node(' ', 0, 0, p->Next->value);
					proot->Right->Head = proot;
					root = proot;

					pbranch = proot; //右树枝的变换
					//pbranch->Right=new Node(' ',0,0,p->Pre->value); //树枝右边取值
				}
				else if (p->PRI == now_pri) //优先级相同,先算左边的
				{
					Node * temp;
					temp = new Node(p->Operation, p->PRI, 1);

					temp->Left = pbranch;
					if (pbranch->Head == NULL)
					{
						proot = temp;
						root = proot;
						pbranch->Head = proot;
					}
					else
					{
						Node * temp0;
						temp0 = pbranch->Head;
						temp0->Right = temp;
						temp->Head = temp0;
						pbranch->Head = temp;
					}
					pbranch = temp;
					pbranch->Right = new Node(' ', 0, 0, p->Next->value);
					pbranch->Right->Head = pbranch;
				}
				else
				{
					Node * temp;
					temp = new Node(p->Operation, p->PRI, 1);

					pbranch->Right = temp;
					temp->Head = pbranch;

					pbranch = pbranch->Right;
					pbranch->Left = new Node(' ', 0, 0, p->Pre->value);
					pbranch->Left->Head = pbranch;
					pbranch->Right = new Node(' ', 0, 0, p->Next->value);
					pbranch->Right->Head = pbranch;
				}
				now_pri = p->PRI;
			}
		}
		p = p->Next;
	}
	if (!hadop)
		root = new Node(' ', 0, 0, head->value);
	return root;
}

///////////////////

double SCalculator::Calculate(std::string exp)
{
	double ret;
	Unit *h = Analyse(exp);
	h = Calc(h);
	Node * root = Tree(h);
	ret=root->GetValue();
	Unit::Release(h);
	Node::Release(root);
	return ret;

}