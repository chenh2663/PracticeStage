 ///
 /// @file    Point.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-01-09 10:05:41
 ///
 
#include <math.h>

#include <iostream>
using std::cout;
using std::endl;

//using namespace std;



class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	}

	void print() const 
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" ;
	}

	//不能这样写, 输出流运算符不能作为成员函数重载
	//左左操作数必须是流对象;如果以成员函数形式重载，
	//左操作数就是对象本身了, 所以是矛盾的
	//operator<<(std::ostream & os)


	friend std::ostream operator<<(std::ostream os, const Point & rhs);
private:
	//禁止复制操作
	Point(const Point & rhs);
	Point & operator=(const Point & rhs);

private:
	int _ix;
	int _iy;
};

//所有的流对象是不能进行复制的
std::ostream operator<<(std::ostream os, const Point & rhs)
{
	os << "(" << rhs._ix 
	   << "," << rhs._iy
	   << ")";
	return os;
}

int main(void)
{
	Point pt1(1, 2), pt2(3, 4);
	cout << "pt1 = " << pt1 << endl
		 << "pt2 = " << pt2 << endl;
	
	pt1 = pt2;//error

	Point pt3 = pt1;//error
	//pt1 << cout;

	return 0;
}
