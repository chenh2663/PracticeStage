 ///
 /// @file    Complex.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-01-09 11:06:51
 ///
 
#include <iostream>
using std::cout;
using std::endl;


//内置类型的运算符无法重载
#if 0
int operator+(int v1, int v2)
{
	return v1 - v2;
}
#endif

void test()
{
	int a = 100;
	//短路求值特性
	if(0 && a++ )
	{
		
	}
	cout << "a = " << a << endl;

	if( 0 || a++ )
	{
		
	}
	cout << "a = " << a << endl;
}
 
int main(void)
{
	Complex c1(1, 2), c2(3, 4);
	//Complex c3 = c1 + c2;//error
	
	test();


	return 0;
}
