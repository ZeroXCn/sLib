#include "SStringBuilder.h"


const SStringBuilder& SStringBuilder::operator=(const SStringBuilder& str)
{
	int len = str.length();
	memcpy(a, str.a, len + 1);
	return *this;
}

const SStringBuilder& SStringBuilder::operator=(const TCHAR *strbuf)
{
	int len = _tcslen(strbuf);
	memcpy(a, strbuf, len);
	a[len] = '\0';
	return *this;
}

SStringBuilder SStringBuilder::operator+(const SStringBuilder& str)
{
	int lenS = str.length(),
		len = strlength + lenS + 1;
	TCHAR *p = new TCHAR[len];
	memcpy(p, a, strlength + 1);
	delete a;
	a = p;
	_tcscat_s(a, len, str.a);
	a[len - 1] = '\0';
	return p;
}

SStringBuilder SStringBuilder::operator+(const TCHAR *strbuf)
{
	int len = _tcslen(a) + _tcslen(strbuf) + 1;
	TCHAR *p = new TCHAR[len];
	memcpy(p, a, strlength + 1);
	delete a;
	a = p;
	
	_tcscat_s(a, len, strbuf);
	a[len - 1] = '\0';
	return p;
}

const SStringBuilder& SStringBuilder::operator+=(const SStringBuilder& str)
{
	int len = _tcslen(a) + str.length() + 1;
	TCHAR *p = new TCHAR[len];
	memcpy(p, a, len);
	delete a;
	a = p;

	_tcscat_s(a, len,str.a);
	a[len] = '\0';
	return *this;
}

const SStringBuilder& SStringBuilder::operator+=(const TCHAR *strbuf)
{
	int len = _tcslen(a) + _tcslen(strbuf) + 1;
	TCHAR *p = new TCHAR[len];
	memcpy(p, a, strlength + 1);
	delete a;
	a = p;

	_tcscat_s(a, len,strbuf);
	a[len] = '\0';
	return *this;
}

int SStringBuilder::operator==(const SStringBuilder& str)
{
	int lenA = _tcslen(a), lenStr = str.length();
	if (lenA != lenStr)
		return -1;
	else
	{
		TCHAR *p = new TCHAR[lenStr + 1];
		memcpy(p, str.a, lenStr + 1);
		int figure = memcmp(a, p, lenA);
		delete p;
		return figure;
	}
}

int SStringBuilder::operator==(const TCHAR *strbuf)
{
	int lenA = _tcslen(a), lenStr = _tcslen(strbuf);
	if (lenA != lenStr)
		return -1;
	else
	{
		int figure = memcmp(a, strbuf, lenA);
		return figure;
	}
}

int SStringBuilder::operator!=(const SStringBuilder& str)
{
	int lenA = _tcslen(a), lenStr = str.length();
	if (lenA != lenStr)
		return 0;
	else
	{
		TCHAR *p = new TCHAR[lenStr + 1];
		memcpy(p, str.a, lenStr + 1);
		int figure = memcmp(a, p, lenA);
		delete p;
		if (figure == 0)
			return -1;
		else
			return 0;
	}
}

int SStringBuilder::operator!=(const TCHAR *strbuf)
{
	int lenA = _tcslen(a), lenStr = _tcslen(strbuf);
	if (lenA != lenStr)
		return 0;
	else
	{
		int figure = memcmp(a, strbuf, lenA);
		if (figure == 0)
			return -1;
		else
			return 0;
	}
}


SStringBuilder operator+(const SStringBuilder& str1, const SStringBuilder& str2)//?
{
	int len = str1.length() + str2.length() + 1;
	TCHAR *p = new TCHAR[len];
	memcpy(p, str1.a, str1.length());
	memcpy(p + str1.length(), str2.a, str1.length() + 1);

	SStringBuilder str = p;
	return str;
}

/*
SStringBuilder SStringBuilder::operator+(const SStringBuilder& str, const TCHAR *strbuf)//?
{
int len=str.length()+_tcslen(strbuf)+1;
TCHAR *p=new TCHAR[len+1];
memcpy(p,str.a,str.length());
delete a;
a=p;

_tcscat(a,strbuf);
a[len]='\0';
return *this;
}

SStringBuilder SStringBuilder::operator+(const TCHAR *strbuf, const SStringBuilder& str)//?
{
int len=_tcslen(strbuf)+str.length()+1;
TCHAR *p=new TCHAR[len+1];
memcpy(p,strbuf,_tcslen(strbuf));
delete a;
a=p;

_tcscat(a,str.a);
a[len]='\0';
return *this;
}
*/
SStringBuilder::SStringBuilder()
{
	a = NULL;
	strlength = 0;
}

SStringBuilder::SStringBuilder(const TCHAR *strbuf)
{
	strlength = 0;
	int i;
	for (i = 0; strbuf[i] != '\0'; i++)
		strlength++;
	a = new TCHAR[strlength + 1];
	for (i = 0; i<strlength; i++)
	{
		a[i] = strbuf[i];
		//{}//printf("%c",a[i]);
	}
	a[strlength] = '\0';
	//{}//printf("this is the first string :%s \n",a);//字符数组a组成的是一个字符串,整体表示时用"%s"表示
}

SStringBuilder::SStringBuilder(const TCHAR *bytes, int offset, int length)
{
	//strcpy(a,bytes); //如果在这里进行了拷贝,则不能显示出要显示的内容
	if (offset<0)
	{
		a = NULL;
		strlength = 0;
		{}//printf("offset is the wrong number");
	}
	int lenO = length + offset,
		strB = _tcslen(bytes);
	if (lenO>strB)
	{
		length = (_tcslen(bytes) - offset);
	}

	a = new TCHAR[length + 1];
	int i;
	for (i = 0; i<length; i++)
	{
		a[i] = bytes[i + offset];
	}
	memcpy(a, bytes + offset, length + 1);
	a[length] = '\0';
	//{}//printf("%s\n",a);
	strlength = length;
}

SStringBuilder::SStringBuilder(const SStringBuilder& str)//把str的长度和内容拷贝到a中,定义为const,表示不能改变类中的其它非const属性
{
	int len = str.length();
	a = new TCHAR(len + 1);
	//strcpy(a,str.a);//还需要计算串有多长,比memcpy()慢
	memcpy(a, str.a, str.length() + 1);//直接在内存中操作拷贝,速度快
	strlength = str.length();
}

SStringBuilder::~SStringBuilder()
{
	delete a;
}

void SStringBuilder::append(const TCHAR* strbuf)
{
	int len = _tcslen(strbuf) + _tcslen(a) + 1;
	TCHAR *p = new TCHAR[len];
	memcpy(p, a, _tcslen(a));
	delete a;
	a = p;

	_tcscat_s(a,len, strbuf);
	a[len] = '\0';
}

void SStringBuilder::append(const TCHAR ch)
{
	int len = _tcslen(a) + 2;
	TCHAR *p = new TCHAR[len];
	memcpy(p, a, _tcslen(a));
	delete a;
	a = p;

	a[len] = ch;
	a[len + 1] = '\0';
}

void SStringBuilder::insert(int index, const TCHAR* strbuf)
{
	int len = _tcslen(strbuf);
	//对a重新分配空间
	TCHAR *pt = new TCHAR[len + strlength + 1];
	memcpy(pt, a, strlength + 1);
	delete a;
	a = pt;

	//{}//printf("%d\n",len);
	/*
	memmove(a+index+len, a+index, strlength-index+1);
	memcpy(a+index, strbuf, len);
	strlength+=len;
	*/
	//	strlength+=len;

	for (int i = strlength; i >= index; i--) {
		a[i + len] = a[i];
	}
	for (int i = index; i<index + len; i++) {
		a[i] = strbuf[i - index];
	}

	strlength += len;
}

void SStringBuilder::insert(int index, const TCHAR ch)
{
	strlength += 1;
	for (int i = strlength - 1; i>index; i--)
	{
		a[i] = a[i - 1];
	}
	a[index] = ch;
	a[strlength] = '\0';
}

int SStringBuilder::equals(const TCHAR* strbuf)
{
	int lenA = _tcslen(a), lenBuf = _tcslen(strbuf);
	if (lenA != lenBuf)
		return -1;
	else
	{
		int figure = memcmp(a, strbuf, lenA);
		return figure;
	}
}

int SStringBuilder::equals(const SStringBuilder& str)
{
	int lenA = _tcslen(a), lenStr = str.length();
	{}//printf("%d", lenStr);
	if (lenA != lenStr)
		return -1;
	else
	{
		TCHAR *b = new TCHAR[lenStr + 1];
		//strcpy(a,str.a);//还需要计算串有多长,比memcpy()慢
		memcpy(b, str.a, str.length() + 1);
		{}//printf("%s", b);
		int figure = memcmp(a, b, lenA);
		delete b;
		return figure;
	}
}

int SStringBuilder::isNull()//与isEmpty()还有点混淆
{
	if (_tcslen(a) == 0)
		return 0;
	else
		return -1;
}

int SStringBuilder::isEmpty()
{
	if (_tcslen(a) != 0)
		return -1;
	else
		return 0;
}

TCHAR SStringBuilder::charAt(int index)
{
	int len = _tcslen(a);
	if (len == 0)
	{
		{}//printf("the string is NULL");
		return -1;
	}
	if (index>len || index<0)
	{
		{}//printf("the index is out of the bound");
		return -1;
	}
	else
		return a[index - 1];
}

int SStringBuilder::indexOf(TCHAR ch)
{
	//int pos=strchr(a,ch);
	//return pos;
	int len = _tcslen(a);
	for (int i = 0; i<len; i++)
	{
		if (a[i] == ch)
			return i;
	}
	{}//printf("%c is not exit in the string\n", ch);
	return -1;
}

int SStringBuilder::indexOf(TCHAR ch, int fromIndex)
{
	int len = _tcslen(a);
	for (int i = fromIndex - 1; i<len; i++)
	{
		if (a[i] == ch)
			return i;
	}
	{}//printf("%c is not exit in the string form the fromIndex %d\n", ch, fromIndex);
	return -1;
}

int SStringBuilder::lastIndexOf(TCHAR ch)
{
	int len = _tcslen(a);
	for (int i = len - 1; i>0; i--)
	{
		if (a[i] == ch)
			return i;
	}
	{}//printf("%c is not exit in the string\n", ch);
	return -1;
}

int SStringBuilder::lastIndexOf(int ch, int fromIndex)
{
	int len = _tcslen(a);
	for (int i = len - 1; i>fromIndex - 1; i--)
	{
		if (a[i] == ch)
			return i;
	}
	{}//printf("%c is not exit in the string form the fromIndex %d\n", ch, fromIndex);
	return -1;
}

int SStringBuilder::length() const
{
	return strlength;
}

SStringBuilder SStringBuilder::copy(const TCHAR* str)
{
	memcpy(a, str, _tcslen(a));
	//{}//printf("%s",a);
	return a;
}

SStringBuilder SStringBuilder::substring(int beginIndex)
{
	int len = _tcslen(a) - beginIndex;
	for (int i = 0; i<len; i++)
	{
		a[i] = a[i + beginIndex - 1];
	}
	a[len] = '\0';
	return a;
}

SStringBuilder SStringBuilder::substring(int beginIndex, int endIndex)
{
	int len = endIndex - beginIndex;
	for (int i = 0; i <= len; i++)
	{
		a[i] = a[i + beginIndex - 1];
	}
	a[len + 1] = '\0';
	return a;
}

SStringBuilder SStringBuilder::toLowerCase()
{
	int len = _tcslen(a);
	for (int i = 0; i<len; i++)
	{
		int strA = (int)a[i];
		if (strA>65 && strA<90)
			strA += 32;
		a[i] = (char)strA;
	}
	{}//printf("%s\n", a);
	return a;
}

SStringBuilder SStringBuilder::toUpperCase()
{
	int len = _tcslen(a);
	for (int i = 0; i<len; i++)
	{
		int strA = (int)a[i];
		if (strA>97 && strA<122)
			strA -= 32;
		a[i] = (char)strA;
	}
	{}//printf("%s\n", a);
	return a;
}

void SStringBuilder::trim()
{

	int len = _tcslen(a);
	for (int i = 0; i<len; i++)
	{
		if (a[i] == ' ')
		for (int j = i; i<len; j++)
			a[j] = a[j + 1];
		{}//printf("%s\n", a);
	}
	/*
	TCHAR *ch="' '";//用strtok没有调试出来
	a=strtok(a,ch);
	while(a!=NULL)
	{
	a=strtok(NULL,ch);
	}
	*/
	{}//printf("%s", a);

}

void SStringBuilder::trimLeft()
{
	int len = _tcslen(a);
	if (len == 0)
		{}//printf(" the string is null");

	if (a[0] != ' ' || a[0] == '\n')
		{}//printf("not in the string ");
	else
	{
		TCHAR *p1 = a;
		for (int i = 0; i<len; i++)
		{
			if (a[i] == ' ' || a[i] == '\n')
				p1 += 1;
			else
				break;
		}
		a = p1;
		{}//printf("%s\n", a);
	}
	strlength = _tcslen(a);
}

void SStringBuilder::trimRight()
{
	int len = _tcslen(a);
	if (len == 0)
		{}//printf(" the string is null");
	else
	{
		TCHAR *p1 = a + len;
		for (int i = len - 1; i >= 0; i--)
		{
			if (a[i] == ' ')
				p1 = p1 - 1;
			else
				break;
		}
		int pos = p1 - a;
		{}//printf("%d\n", pos);
		a[pos] = '\0';
		{}//printf("%s\n", a);
	}
	strlength = _tcslen(a);
}

void SStringBuilder::mergeSpace()
{
	int len = _tcslen(a);
	if (len == 0)
		{}//printf("the string is null");
	else
	{
		for (int i = 0; i<len; i++)
		{
			if (a[i] == ' ')
			{
				for (int j = i + 1; j<len; j++)//把a后面的空格往前移
				{
					if (a[j] == ' ')
					if (a[j + 1] == ' ')//如果a后的空格的下一位也是空格则把其下一位前移,否则把a后的空格往前移
						memmove(a + i, a + j + 1, len - j + 2);
					else
						memmove(a + i, a + j, len - j + 2);
					else break;
				}
				{}//printf("%s\n", a);
			}
		}
		//{}//printf("%s\n",a);
		strlength = _tcslen(a);
		{}//printf("haha\n");


	}
}

int SStringBuilder::startsWith(const SStringBuilder& prefix)
{
	int len = prefix.length();
	//TCHAR *b = new TCHAR(len+1);
	//memcpy(b,prefix.a,len);		
	int figure = memcmp(a, prefix.a, len);
	//delete b;
	if (figure == 0)
		return 0;
	else
		return -1;
}

int SStringBuilder::endsWith(const SStringBuilder& suffix)
{
	int len = suffix.length(), lenA = _tcslen(a);
	TCHAR *b = new TCHAR(len + 1);
	memcpy(b, suffix.a, len);

	for (int i = 0; i<len; i++)
	{
		if (a[i + lenA - len] != b[i])
			return -1;;
	}
	return 0;
}

void SStringBuilder::remove(TCHAR *str)
{
	TCHAR *pos = _tcsstr(a, str);
	if (pos != NULL)
	{
		int result = pos - a + 1, lenStr = _tcslen(str), lenA = _tcslen(a);
		for (int i = result - 1; i<lenA - 1; i++)
			a[i] = a[i + lenStr];
		{}//printf("%s", a);
	}
	else
		{}//printf("there is not the string");
}

void SStringBuilder::replaceAll(char oldChar, char newChar)
{
	int len = _tcslen(a);
	for (int i = 0; i<len; i++)
	{
		if (a[i] == oldChar)
			a[i] = newChar;
	}
}

void SStringBuilder::replaceFirst(SStringBuilder oldsubString, SStringBuilder newsubString)
{
	//可用memmove(),和memcpy()实现;
	int len = _tcslen(a),
		lenOld = oldsubString.length(),
		lenNew = newsubString.length();

	TCHAR *b = new TCHAR[lenOld];
	TCHAR *c = new TCHAR[lenNew];
	memcpy(b, oldsubString.a, lenOld + 1);
	//{}//printf("%s\n",b);
	memcpy(c, newsubString.a, lenNew + 1);
	//{}//printf("%s\n",c);
	TCHAR *pos = _tcsstr(a, b);
	//TCHAR *pos=_tcsstr(a+result+lenNew,oldsubString.a);//指向下一个相同的字符串的指针地址
	if (pos != NULL)
	{
		int result = pos - a + 1;
		{}//printf("%d\n", result);
		if (lenOld >= lenNew)
		{
			for (int i = result - 1; i<len - 1; i++)
			{
				if (i<result + lenNew - 1)
					a[i] = c[i - result + 1];
				else
					a[i] = a[i + lenOld - lenNew];
			}
		}
		else
		{
			//变长后需要重新分配空间,可用new(),realloc(),melloc()
			int lenAdd = lenNew - lenOld, len = _tcslen(a);
			len += lenAdd;
			for (int i = len - 1; i >= result - 1; i--)
			{
				if (i >= result + lenNew - 1)
					a[i] = a[i - lenAdd];
				else
					a[i] = c[i - result + 1];
			}
			a[len] = '\0';
			{}//printf("%d\n", len);
		}
		{}//printf("%s", a);
	}
	else
	{
		{}//printf("%s is not in the string\n", newsubString.a);
	}
	/*

	int len=strlength,
	lenOld=oldsubString.length();
	int	lenNew=newsubString.length();
	int lenAdd=lenNew-lenOld;
	if(lenAdd>0)//空间不够大时,重新分配空间
	{
	TCHAR *pt=new TCHAR[strlength+lenAdd];
	memcpy(pt,a,strlength);
	delete a;
	a=pt;
	}
	if(newsubString.a==NULL)
	{
	{}//printf("the newsubString is null");
	}
	else if(newsubString.length()==0)
	{
	remove(oldsubString.a);
	}
	else if(newsubString.length()>0)
	{
	TCHAR *b;
	b=_tcsstr(a,oldsubString.a);
	if(b!=NULL)
	{
	int pos=b-a;
	memmove(b,b+lenOld,len-pos-lenOld);
	b[len-pos-lenOld]='\0';
	{}//printf("%s\n",b);
	//memmove(b,newsubString.a,lenNew);
	insert(pos,newsubString.a);//因为b动态的指针,这时b有可能已经指向其它的地方了,所以不太安全
	//{}//printf("%s\n",b);
	b=_tcsstr(a,oldsubString.a);
	}
	//else
	//	{}//printf("the newsubString is not exit in the string\n");
	}
	{}//printf("%s\n",a);

	*/
}

void SStringBuilder::replaceAll(SStringBuilder oldsubString, SStringBuilder newsubString)
{
	int strEquals = _tcscmp(oldsubString.a, newsubString.a);
	if (strEquals == 0)
	{
		{}//printf("the strings are same");
	}
	else
	{
		int len = strlength,
			lenOld = oldsubString.length();
		int	lenNew = newsubString.length();

		int lenAdd = lenNew - lenOld;
		if (lenAdd>0)//空间不够大时,重新分配空间
		{
			TCHAR *pt = new TCHAR[strlength + lenAdd];
			memcpy(pt, a, strlength);
			delete a;
			a = pt;
		}
		if (newsubString.a == NULL)
		{
			{}//printf("the newsubString is null");
		}
		else if (newsubString.length() == 0)
		{
			remove(oldsubString.a);
		}
		else if (newsubString.length()>0)
		{
			TCHAR *b;
			b = _tcsstr(a, oldsubString.a);
			if (b != NULL)
			{
				while (b != NULL)
				{
					len += lenAdd;
					int pos = b - a;
					memmove(b + lenNew, b + lenOld, len - pos - lenOld);//把需要插入的地方空出来
					memcpy(b, newsubString.a, lenNew);//把新串拷贝进去
					b = _tcsstr(a, oldsubString.a);//继续往下找
				}
				a[len] = '\0';
			}
			else
				{}//printf("the newsubString is not exit in the string\n");
		}
		{}//printf("%s\n", a);
	}

}


int SStringBuilder::parseInt(int base)//为什么会少1?
{
	int len = _tcslen(a);
	int *b = new int[len];
	for (int i = 0; i<len; i++)
	{
		if (isdigit(a[i]))
			b[i] = (int)(a[i] - '0');
		if (isalpha(a[i]))
		{
			a[i] = toupper(a[i]);
			if (a[i] >= 'A'&&a[i] <= 'F')
				b[i] = (int)(a[i] - 'A' + 10);
			else
				break;
		}
		{}//printf("%d\n", b[i]);
	}
	int sum = 0;

	for (int i = 0; i<len; i++)
	{
		//b[i]=b[i]*pow(10,(len-i-1));
		sum += b[i] * (int)(pow(10.0f, (len - i - 1)) + 0.5);
		{}//printf("i= %d ,sum = %d\n", i, sum);
	}
	//{}//printf("%s",a);
	{}//printf("sum = %d\n", sum);
	delete b;
	return sum;
}

double SStringBuilder::parseFloat()
{
	return _tstof(a);
}
