 ///
 /// @file    shared_ptr.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-01-16 17:53:27
 ///
 
#include <iostream>
#include <memory>
using std::cout;
using std::endl;

using std::shared_ptr;

class Point
{
public:
	Point(int x = 0, int y = 0)
	: _x(x)
	, _y(y)
	{
		cout << "Point(int,int)" << endl;
	}

	void print() const 
	{
		cout << "(" << _x
			 << "," << _y
			 << ")" << endl;
	}

	void setX(int x)
	{	_x = x;	}

	void setY(int y)
	{	_y = y;	}

	~Point() {	cout << "~Point()" << endl;}

private:
	int _x;
	int _y;
};

shared_ptr<Point> getValue()
{
	shared_ptr<Point> tmp(new Point(11, 12));
	return tmp;
}

void test0()
{
	Point * pt1 = new Point(1, 2);
	//默认情况下，当shared_ptr被销毁时，会执行delete表达式
	shared_ptr<Point> sp(pt1);
	cout << "pt1: " << pt1 << endl
		 << "sp.get():" << sp.get() << endl;//获取资源的地址
	sp->print();//操作sp跟操作pt1是一样的
	(*sp).print();

	//执行复制操作时，引用计数加1，资源本身并没有进行复制
	shared_ptr<Point> sp2(sp);//ok 表达值语义  
	//shared_ptr<Point> sp2(std::move(sp));//ok
	cout << "sp2.use_count(): " << sp2.use_count() << endl;
	cout << "sp.use_count(): " << sp.use_count() << endl;

	cout << "sp.get():" << sp.get() << endl;//获取资源的地址
	cout << "sp2.get():" << sp2.get() << endl;//获取资源的地址

	sp->setX(11);
	sp->setY(12);
	sp->print();//操作sp跟操作pt1是一样的
	(*sp).print();
	sp2->print();//操作sp2跟操作pt1是一样的
	(*sp2).print();
	
	//shared_ptr内部定义了具有移动语义的函数
	shared_ptr<Point> sp3 = getValue();
	sp3->print();
}

int main(void)
{
	test0();

	return 0;
}
