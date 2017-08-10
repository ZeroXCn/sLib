
int main()
{
	/*Date d1(2016,8,18);
	//d1.Display();

	//d1 = d1++;
	cout << d1 << endl;*/

	//Date d1(2015, 12, 3);
	//(d1++).Display();  //d1.operator++(&d1, 0);
	//(++d1).Display(); //d1.operator++(&d1);

	Date d1(2015, 12, 3);
	Date d2(2015, 11, 1);
	cout << (d1 - d2) << endl;

	//Date d1(2015, 12, 3);
	//Date ret = d1 + 40; //operator+
	//ret.Display();


	/*Date d1(2015, 12, 3);
	Date ret = d1 + 40;
	d1 = ret;
	ret = d1 - 40;
	ret.Display();*/

	/*Date ret;
	Date d2(2015, 1, 1);
	ret = d2 - 1;
	ret.Display();*/
	return 0;
}