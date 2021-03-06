 ///
 /// @file    TestThreadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-02-09 16:35:31
 ///
 
#include "Threadpool.h"

#include <unistd.h>
#include <stdlib.h>

#include <iostream>
#include <memory>
using namespace wd;
using namespace std;

class MyTask
: public wd::Task
{
public:
	//process的调用是在其中一个子线程里完成的
	void process()
	{
		::srand(::time(NULL));
		int number = ::rand() % 100;
		cout << "pthid " << pthread_self() << ", number = " << number << endl;
		//::sleep(2);//代表的是该任务执行的时间为2秒
	}
};

//test方法运行在主线程
void test()
{
	unique_ptr<Task> up(new MyTask());
	unique_ptr<Threadpool> threadpoolPtr(new Threadpool(4, 10));
	threadpoolPtr->start();
	int cnt = 20;
	while(cnt--) {
		threadpoolPtr->addTask(up.get());
	}

	cout << ">> test(): exit while(cnt--)  " << endl; 
	threadpoolPtr->stop();
}
 
int main(void)
{
	test();
	return 0;
}
