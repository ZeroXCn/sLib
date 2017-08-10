#include "../../sCore/SStringBuilder.h"
int main()
{
	SStringBuilder *str = new SStringBuilder();//测试SStringBuilder();
	printf(TEXT("%s\n"), str->a);

	SStringBuilder *str1 = new SStringBuilder(TEXT("the first string!"));//测试SStringBuilder(const char *strbuf);
	//printf(TEXT("this is the first string %c \n"),str);//不能显示一个对象,可以显示该对象的属性或方法
	printf(TEXT("this is the first string %s \n"), str1->a);//a 是类的一个属性,必须由对象来调用,而str是一个指针,注意其表示方式

	SStringBuilder *str2 = new SStringBuilder(TEXT("hahaha the second string"), 3, 6);//测试SStringBuilder(const char *bytes, int offset, int length);
	printf(TEXT("this is the second string :%s \n"), str2->a);//注意字符数组的长度.

	SStringBuilder *str3 = new SStringBuilder(TEXT("1234567890"));//测试SStringBuilder(const SStringBuilder& str);
	printf(TEXT("this is the third string :%s \n"), str3->a);
	printf(TEXT("the a's new length is : %d\n"), str3->length());

	/*
	str3->append(TEXT("append()"));//测试void append(const char* strbuf),//void append(const char ch);;
	printf(TEXT("after appending : %s \n"),str3->a);
	printf(TEXT("the a's new length is : %d\n"),str3->length());

	str3->insert(5,"here ")); //测试void insert(int index, const char *strbuf);
	printf(TEXT("after inserting : %s \n"	,str3->a);
	printf(TEXT("the a's new length is : %d\n"),str3->length());

	str3->insert(5,'a');//测试void insert(int index, const char ch);
	printf(TEXT("after inserting : %s \n"	,str3->a);

	int eq=str3->equals(TEXT("hoho the third string :"));//测试equals(const char* strbuf)
	if(eq==0)
	printf(TEXT("equals \n"));
	else
	printf(TEXT("not equals \n"));

	int eq2=str3->equals(TEXT("aa"));//??在这里我是想调用equals(const SStringBuilder& str),可结果也可以认为是调用了equals(const char* strbuf),还是不太明白
	if(eq2==0)
	printf(TEXT("equals \n"));
	else
	printf(TEXT("not equals \n"));

	int isN = str3->isNull();//测试int isNull()
	if(isN==0)
	printf(TEXT("isNull \n"));
	else
	printf(TEXT("is not Null \n"));

	int isEm = str3->isEmpty();//测试int isEmpty()
	if(isEm==0)
	printf(TEXT("isEmpty  \n"));
	else
	printf(TEXT("is not empty \n"));

	char c=str3->charAt(18);//测试char charAt()
	if(c==' ')
	printf(TEXT("this is the empty char"));
	else
	printf(TEXT("%c"),c);

	int index=str3->indexOf('t');//测试int indexOf(char ch)
	printf(TEXT("%d\n"),index);

	int index2=str3->indexOf('t',14);//测试int indexOf(char ch, int fromIndex)
	printf(TEXT("%d"),index2);

	//测试SStringBuilder copy(const char* str)
	//char *strA=new char[str3->length()];
	//strA=str3->copy(TEXT(" test the copy"));// wrong :cannot convert `SStringBuilder' to `char*' in assignment

	//SStringBuilder *strA=new SStringBuilder();
	//strA=str3->copy(TEXT(" test the copy"));//wrong:cannot convert `SStringBuilder' to `SStringBuilder*' in assignment
	//printf(TEXT("%s\n"),str3->copy(TEXT(" test the copy")));//wrong:内存读写错误

	str3->copy(TEXT(" test the copy"));
	printf(TEXT("%s\n"),str3->a);

	str3->substring(3);//测试SStringBuilder substring(int beginIndex);
	printf(TEXT("%s\n"),str3->a);

	str3->substring(5,6);//测试SStringBuilder substring(int beginIndex, int endIndex);
	printf(TEXT("%s\n"),str3->a);

	str3->toLowerCase();//测试 SStringBuilder toLowerCase();

	str3->toUpperCase();//测试 SStringBuilder toUpperCase();

	//str3->trim();//?测试void trim()

	str3->trimLeft();
	printf(TEXT("the a's new length is : %d\n"),str3->strlength);

	str3->trimRight();
	printf(TEXT("the a's new length is : %d\n"),str3->strlength);

	str3->mergeSpace();

	int isStart=str3->startsWith(TEXT("  the"));//测试int startsWith(SStringBuilder &prefix);
	if(isStart==0)
	printf(TEXT("is start with \n"));
	else
	printf(TEXT("is not start with \n"));

	int isEnd=str3->endsWith(TEXT("string"));//测试int endsWith(SStringBuilder &prefix);
	if(isEnd==0)
	printf(TEXT("is end with \n"));
	else
	printf(TEXT("is not end with \n"));

	str3->replaceAll('t','T');//测试void replaceAll(char oldChar, char newChar);
	printf(TEXT("%s"),str3->a);

	str3->remove(TEXT("st"));

	str3->replaceFirst(TEXT("stri"),"aa"));
	str3->replaceFirst(TEXT("st"),"aaaa"));
	str3->replaceFirst(TEXT("aa"),"bb"));
	printf(TEXT("%s\n"),str3->a);

	str3->replaceAll(TEXT("th"),"aabbccddee"));//测试void replaceAll(SStringBuilder oldsubSStringBuilder, SStringBuilder newsubSStringBuilder);
	printf(TEXT("%s"),str3->a);

	str3->operator=(TEXT("hahahoho"));

	str3->operator+(TEXT("hahahoho"));
	printf(TEXT("%s"),str3->a);

	int r=str3->operator==(TEXT("432"));
	printf(TEXT("r = %d\n"), r);

	int r = str3->parseInt(10);//为什么结果会少1?
	printf(TEXT("r = %d\n"), r);
	*/
	delete str;//delete只针对new产生的对象,与new配对
	delete str1;
	delete str2;
	delete str3;
	SStringBuilder sa = TEXT("a");
	SStringBuilder sb = TEXT("b");
	SStringBuilder sc = sa + sb;
}
