 ///
 /// @file    Condition.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-02-02 16:39:30
 ///
 
#include "Condition.h"
#include "MutexLock.h"

#include <stdio.h>
#include <errno.h>
 

namespace wd
{
Condition::Condition(MutexLock & mutex)
: _mutex(mutex)
{
	if(pthread_cond_init(&_cond, NULL)) {
		perror("pthread_cond_init");
	}
}

void Condition::wait()
{
	if(pthread_cond_wait(&_cond, _mutex.getMutexLockPtr()))	{
		perror("pthread_cond_wait");
	}
}

void Condition::notify()
{
	if(pthread_cond_signal(&_cond)) {
		perror("pthread_cond_signal");
	}
}

void Condition::notifyall()
{
	if(pthread_cond_broadcast(&_cond)) {
		perror("pthread_cond_broadcast");
	}
}

Condition::~Condition()
{
	if(pthread_cond_destroy(&_cond)) {
		perror("pthread_cond_destroy");
	}
}

}//end of namespace wd
