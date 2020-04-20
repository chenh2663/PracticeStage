 ///
 /// @file    MutexLock.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-02-02 16:27:24
 ///
 
#include "MutexLock.h"

#include <stdio.h>
#include <errno.h>

namespace wd
{

MutexLock::MutexLock()
{
	if(pthread_mutex_init(&_mutex, NULL))
	{
		perror("pthread_mutex_init");
	}
}

void MutexLock::lock()
{
	if(pthread_mutex_lock(&_mutex))
	{
		perror("pthread_mutex_lock");
	}
}

void MutexLock::unlock()
{
	if(pthread_mutex_unlock(&_mutex))
	{
		perror("pthread_mutex_unlock");
	}
}

MutexLock::~MutexLock()
{
	if(pthread_mutex_destroy(&_mutex))
	{
		perror("pthread_mutex_destroy");
	}
}
}//end of namespace wd
