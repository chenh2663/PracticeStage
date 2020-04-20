 ///
 /// @file    Threadpool.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-02-09 15:59:46
 ///
 
#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__

#include "TaskQueue.h"
#include <vector>
#include <memory>
#include <functional>
using namespace std;

namespace wd
{

using Task = function<void()>;
class Thread;
class Threadpool
{
public:
	Threadpool(size_t threadNum, size_t queSize);
	~Threadpool();

	void addTask(Task && task);
	void start();//开启线程池
	void stop();//停止线程池
private:
	void threadFunc();//每一个线程要执行的任务
	Task getTask();

private:
	size_t _threadNum;
	vector<unique_ptr<Thread>> _threads;
	size_t _queSize;
	TaskQueue _taskque;
	bool _isExit;
};

}//end of namespace wd

#endif
