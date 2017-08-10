/*
* test.cpp
*
*  Created on: 2016��10��9��
*      Author: havesnag
*/

#include <iostream>
using namespace std;

#include "../../sCore/SDuration.h"
#include "../../sCore/SDate.h"
#include "../../sCore/STime.h"


int main(int argc, char *argv[])
{
	SDate d(2000, 1, 1);
	cout << "d = " << d.format() << endl;

	STime t = d.toTime().addHour(1);
	cout << "t = " << t.toDate().format() << endl;

	return 0;
}


