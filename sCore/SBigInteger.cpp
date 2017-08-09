#include "SBigInteger.h"
using namespace std;

const SBigInteger SBigInteger::ZERO = SBigInteger(0);
const SBigInteger SBigInteger::ONE = SBigInteger(1);
const SBigInteger SBigInteger::TEN = SBigInteger(10);


SBigInteger::SBigInteger()
{
	sign = true;
}


SBigInteger::SBigInteger(int val){// construct with a int integer
	if (val >= 0)
		sign = true;
	else{
		sign = false;
		val *= (-1);
	}
	do{
		digits.push_back((char)(val % 10));
		val /= 10;
	} while (val != 0);
}


SBigInteger::SBigInteger(string def)
{
	sign = true;
	for (string::reverse_iterator iter = def.rbegin(); iter < def.rend(); iter++){
		char ch = (*iter);
		if (iter == def.rend() - 1){
			if (ch == '+')
				break;
			if (ch == '-'){
				sign = false;
				break;
			}
		}
		digits.push_back((char)((*iter) - '0'));
	}
	trim();
}
void SBigInteger::trim(){
	vector<char>::reverse_iterator iter = digits.rbegin();
	while (!digits.empty() && (*iter) == 0){
		digits.pop_back();
		iter = digits.rbegin();
	}
	if (digits.size() == 0){
		sign = true;
		digits.push_back(0);
	}
}


SBigInteger::SBigInteger(const SBigInteger& op2){
	sign = op2.sign;
	digits = op2.digits;
}


SBigInteger SBigInteger::operator=(const SBigInteger& op2){
	digits = op2.digits;
	sign = op2.sign;
	return (*this);
}
SBigInteger SBigInteger::operator=(string num)
{
	return SBigInteger(num);
}

SBigInteger SBigInteger::abs() const {
	if (sign)  return *this;
	else      return -(*this);
}

SBigInteger SBigInteger::pow(int a)
{
	SBigInteger res(1);
	for (int i = 0; i<a; i++)
		res *= (*this);
	return res;
}

string SBigInteger::toString() const
{
	string result;
	for (vector<char>::const_reverse_iterator iter = digits.rbegin(); iter != digits.rend(); iter++)
		result+=(char)((*iter) + '0');
	return result;
}

//binary operators
SBigInteger operator+=(SBigInteger& op1, const SBigInteger& op2){
	if (op1.sign == op2.sign){     //只处理相同的符号的情况，异号的情况给-处理
		vector<char>::iterator iter1;
		vector<char>::const_iterator iter2;
		iter1 = op1.digits.begin();
		iter2 = op2.digits.begin();
		char to_add = 0;        //进位
		while (iter1 != op1.digits.end() && iter2 != op2.digits.end()){
			(*iter1) = (*iter1) + (*iter2) + to_add;
			to_add = ((*iter1) > 9);    // 大于9进一位
			(*iter1) = (*iter1) % 10;
			iter1++; iter2++;
		}
		while (iter1 != op1.digits.end()){   // 
			(*iter1) = (*iter1) + to_add;
			to_add = ((*iter1) > 9);
			(*iter1) %= 10;
			iter1++;
		}
		while (iter2 != op2.digits.end()){
			char val = (*iter2) + to_add;
			to_add = (val > 9);
			val %= 10;
			op1.digits.push_back(val);
			iter2++;
		}
		if (to_add != 0)
			op1.digits.push_back(to_add);
		return op1;
	}
	else{
		if (op1.sign)
			return op1 -= (-op2);
		else
			return op1 = op2 - (-op1);
	}

}

SBigInteger operator-=(SBigInteger& op1, const SBigInteger& op2){
	if (op1.sign == op2.sign){     //只处理相同的符号的情况，异号的情况给+处理
		if (op1.sign) {
			if (op1 < op2)  // 2 - 3
				return  op1 = -(op2 - op1);
		}
		else {
			if (-op1 > -op2)  // (-3)-(-2) = -(3 - 2)
				return op1 = -((-op1) - (-op2));
			else             // (-2)-(-3) = 3 - 2 
				return op1 = (-op2) - (-op1);
		}
		vector<char>::iterator iter1;
		vector<char>::const_iterator iter2;
		iter1 = op1.digits.begin();
		iter2 = op2.digits.begin();

		char to_substract = 0;  //借位

		while (iter1 != op1.digits.end() && iter2 != op2.digits.end()){
			(*iter1) = (*iter1) - (*iter2) - to_substract;
			to_substract = 0;
			if ((*iter1) < 0){
				to_substract = 1;
				(*iter1) += 10;
			}
			iter1++;
			iter2++;
		}
		while (iter1 != op1.digits.end()){
			(*iter1) = (*iter1) - to_substract;
			to_substract = 0;
			if ((*iter1) < 0){
				to_substract = 1;
				(*iter1) += 10;
			}
			else break;
			iter1++;
		}
		op1.trim();
		return op1;
	}
	else{
		if (op1 > SBigInteger::ZERO)
			return op1 += (-op2);
		else
			return op1 = -(op2 + (-op1));
	}
}
SBigInteger operator*=(SBigInteger& op1, const SBigInteger& op2){
	SBigInteger result(0);
	if (op1 == SBigInteger::ZERO || op2 == SBigInteger::ZERO)
		result = SBigInteger::ZERO;
	else{
		vector<char>::const_iterator iter2 = op2.digits.begin();
		while (iter2 != op2.digits.end()){
			if (*iter2 != 0){
				deque<char> temp(op1.digits.begin(), op1.digits.end());
				char to_add = 0;
				deque<char>::iterator iter1 = temp.begin();
				while (iter1 != temp.end()){
					(*iter1) *= (*iter2);
					(*iter1) += to_add;
					to_add = (*iter1) / 10;
					(*iter1) %= 10;
					iter1++;
				}
				if (to_add != 0)
					temp.push_back(to_add);
				int num_of_zeros = iter2 - op2.digits.begin();
				while (num_of_zeros--)
					temp.push_front(0);
				SBigInteger temp2;
				temp2.digits.insert(temp2.digits.end(), temp.begin(), temp.end());
				temp2.trim();
				result = result + temp2;
			}
			iter2++;
		}
		result.sign = ((op1.sign && op2.sign) || (!op1.sign && !op2.sign));
	}
	op1 = result;
	return op1;
}

SBigInteger operator/=(SBigInteger& op1, const SBigInteger& op2) throw(DividedByZeroException) {
	if (op2 == SBigInteger::ZERO)
		throw DividedByZeroException();
	SBigInteger t1 = op1.abs(), t2 = op2.abs();
	if (t1 < t2){
		op1 = SBigInteger::ZERO;
		return op1;
	}
	//现在 t1 > t2 > 0
	//只需将 t1/t2的结果交给result就可以了
	deque<char> temp;
	vector<char>::reverse_iterator iter = t1.digits.rbegin();

	SBigInteger temp2(0);
	while (iter != t1.digits.rend()){
		temp2 = temp2 * SBigInteger::TEN + SBigInteger((int)(*iter));
		char s = 0;
		while (temp2 >= t2){
			temp2 = temp2 - t2;
			s = s + 1;
		}
		temp.push_front(s);
		iter++;
	}
	op1.digits.clear();
	op1.digits.insert(op1.digits.end(), temp.begin(), temp.end());
	op1.trim();
	op1.sign = ((op1.sign && op2.sign) || (!op1.sign && !op2.sign));
	return op1;
}

SBigInteger operator%=(SBigInteger& op1, const SBigInteger& op2) throw(DividedByZeroException) {
	return op1 -= ((op1 / op2)*op2);
}

SBigInteger operator+(const SBigInteger& op1, const SBigInteger& op2){
	SBigInteger temp(op1);
	temp += op2;
	return temp;
}
SBigInteger operator-(const SBigInteger& op1, const SBigInteger& op2){
	SBigInteger temp(op1);
	temp -= op2;
	return temp;
}

SBigInteger operator*(const SBigInteger& op1, const SBigInteger& op2){
	SBigInteger temp(op1);
	temp *= op2;
	return temp;

}

SBigInteger operator/(const SBigInteger& op1, const SBigInteger& op2) throw(DividedByZeroException) {
	SBigInteger temp(op1);
	temp /= op2;
	return temp;
}

SBigInteger operator%(const SBigInteger& op1, const SBigInteger& op2) throw(DividedByZeroException) {
	SBigInteger temp(op1);
	temp %= op2;
	return temp;
}

//uniary operators
SBigInteger operator-(const SBigInteger& op){   //negative
	SBigInteger temp = SBigInteger(op);
	temp.sign = !temp.sign;
	return temp;
}

SBigInteger operator++(SBigInteger& op){    //++v
	op += SBigInteger::ONE;
	return op;
}

SBigInteger operator++(SBigInteger& op, int x){  //v++
	SBigInteger temp(op);
	++op;
	return temp;
}

SBigInteger operator--(SBigInteger& op){    //--v
	op -= SBigInteger::ONE;
	return op;
}

SBigInteger operator--(SBigInteger& op, int x){  //v--
	SBigInteger temp(op);
	--op;
	return temp;
}

bool operator<(const SBigInteger& op1, const SBigInteger& op2){
	if (op1.sign != op2.sign)
		return !op1.sign;
	else{
		if (op1.digits.size() != op2.digits.size())
			return (op1.sign && op1.digits.size()<op2.digits.size())
			|| (!op1.sign && op1.digits.size()>op2.digits.size());
		vector<char>::const_reverse_iterator iter1, iter2;
		iter1 = op1.digits.rbegin(); iter2 = op2.digits.rbegin();
		while (iter1 != op1.digits.rend()){
			if (op1.sign &&  *iter1 < *iter2) return true;
			if (op1.sign &&  *iter1 > *iter2) return false;
			if (!op1.sign &&  *iter1 > *iter2) return true;
			if (!op1.sign &&  *iter1 < *iter2) return false;
			iter1++;
			iter2++;
		}
		return false;
	}
}
bool operator==(const SBigInteger& op1, const SBigInteger& op2){
	if (op1.sign != op2.sign || op1.digits.size() != op2.digits.size())
		return false;
	vector<char>::const_iterator iter1, iter2;
	iter1 = op1.digits.begin();
	iter2 = op2.digits.begin();
	while (iter1 != op1.digits.end()){
		if (*iter1 != *iter2)  return false;
		iter1++;
		iter2++;
	}
	return true;
}

bool operator!=(const SBigInteger& op1, const SBigInteger& op2){
	return !(op1 == op2);
}

bool operator>=(const SBigInteger& op1, const SBigInteger& op2){
	return (op1>op2) || (op1 == op2);
}

bool operator<=(const SBigInteger& op1, const SBigInteger& op2){
	return (op1<op2) || (op1 == op2);
}

bool operator>(const SBigInteger& op1, const SBigInteger& op2){
	return !(op1 <= op2);
}

ostream& operator<<(ostream& stream, const SBigInteger& val){    //print the SBigInteger
	if (!val.sign)
		stream << "-";
	for (vector<char>::const_reverse_iterator iter = val.digits.rbegin(); iter != val.digits.rend(); iter++)
		stream << (char)((*iter) + '0');
	return stream;
}

istream& operator>>(istream& stream, SBigInteger& val){    //Input the SBigInteger
	string str;
	stream >> str;
	val = SBigInteger(str);
	return stream;
}

////////////////////////////////////////////////////////////
