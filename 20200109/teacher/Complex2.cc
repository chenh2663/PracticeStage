 ///
 /// @file    Complex.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-01-09 11:06:51
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Complex
{
	//复数
	//负数  -1 
public:
	Complex(double dreal, double dimage)
	: _dreal(dreal)
	, _dimage(dimage)
	{
		cout << "Complex(double,double)" << endl;
	}

	void print() const
	{
		cout << _dreal << " + " << _dimage << "i" << endl;
	}

	double real() const {	return _dreal;	}
	double image() const {	return _dimage;	}

private:
	double _dreal;
	double _dimage;
};

//重载运算符时，不能有默认参数，否则会改变运算符的操作数的数量
//Complex operator+(const Complex & lhs, const Complex & rhs = Complex(1, 2))


//普通函数形式重载
Complex operator+(const Complex & lhs, const Complex & rhs)
{
	cout << "Complex operator+(lhs,rhs)" << endl;
	return Complex(lhs.real() + rhs.real(),
				   lhs.image() + rhs.image());
}
 
int main(void)
{
	Complex c1(1, 2), c2(3, 4);
	cout << "c1 = ";
	c1.print();
	cout << "c2 = ";
	c2.print();
	Complex c3 = c1 + c2;
	cout << "c3 = ";
	c3.print();
	


	return 0;
}
