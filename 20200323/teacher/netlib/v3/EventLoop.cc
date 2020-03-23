 ///
 /// @file    EventLoop.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-02-19 11:24:22
 ///
 
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/eventfd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

EventLoop::EventLoop(Acceptor & acceptor)
: _efd(createEpollFd())
, _eventfd(createEventfd())
, _acceptor(acceptor)
, _eventsList(1024)
, _isLooping(false)
{
	addEpollReadFd(_acceptor.fd());
	addEpollReadFd(_eventfd);
}

EventLoop::~EventLoop()
{
	::close(_efd);
}

void EventLoop::loop()
{
	_isLooping = true;
	while(_isLooping) {
		waitEpollFds();
	}
}
	
void EventLoop::unloop()
{
	if(_isLooping) 
		_isLooping = false;
}

void EventLoop::runInLoop(Functor && cb)
{
	//成为临界资源
	{
		MutexLockGuard autolock(_mutex);
		_pendingFunctors.push_back(std::move(cb));
	}
	wakeup();//通知IO线程
}


//IO线程中执行的就是该方法
void EventLoop::waitEpollFds()
{
	int nready;
	do {
		nready = ::epoll_wait(_efd, &*_eventsList.begin(), _eventsList.size(), 5000);
	}while(nready == -1 && errno == EINTR);

	if(nready == 0) {
		printf(">> epoll_wait timeout!\n");
	} else if(nready == -1){
		::perror(">> epoll_wait");
		return;
	} else {
		if(nready == _eventsList.size()) {
			_eventsList.resize(2 * _eventsList.size());
		}
		
		for(int idx = 0; idx < nready; ++idx) {
			if(_eventsList[idx].data.fd == _acceptor.fd() &&
			   _eventsList[idx].events & EPOLLIN) {
				handleNewConnection();
			} else if(_eventsList[idx].data.fd == _eventfd){
				handleRead();
				doPeningFunctors();
			} else {
				handleMessage(_eventsList[idx].data.fd);	
			}
		}
	}
}

void EventLoop::handleNewConnection()
{
	int peerfd = _acceptor.accept();
	addEpollReadFd(peerfd);

	shared_ptr<TcpConnection> conn(new TcpConnection(peerfd, *this));
	_conns.insert(std::make_pair(peerfd, conn));
	conn->setConnectionCallback(_onConnectionCallback);
	conn->setMessageCallback(_onMessageCallback);
	conn->setCloseCallback(_onCloseCallback);

	//do something
	conn->handleConnectionCallback();//相当于挖空, 再填上
}

void EventLoop::handleMessage(int peerfd)
{
	auto iter = _conns.find(peerfd);
	if(iter != _conns.end()) {
		//先判断连接是否断开
		auto conn = iter->second;
		bool closed = conn->isClosed();
		if(!closed) {//收到数据的情况
			//do something 
			conn->handleMessageCallback();
		} else {// 连接断开的情况
			//do something
			conn->handleCloseCallback();
			delEpollReadFd(peerfd);
			_conns.erase(peerfd);
		}
	}
}

int EventLoop::createEpollFd()
{
	int fd = ::epoll_create1(0);
	if(fd == -1) {
		::perror(">> epoll_create1");
	}
	return fd;
}

int EventLoop::createEventfd()
{
	int fd = ::eventfd(0, 0);
	if(fd == -1) {
		::perror(">> eventfd");
	}
	return fd;
}
void EventLoop::addEpollReadFd(int fd)
{
	struct epoll_event value;
	value.data.fd = fd;
	value.events = EPOLLIN;
	int ret = ::epoll_ctl(_efd, EPOLL_CTL_ADD, fd, &value);
	if(ret == -1) {
		perror(">> epoll_ctl");
	}
}

void EventLoop::delEpollReadFd(int fd)
{
	struct epoll_event value;
	value.data.fd = fd;
	value.events = EPOLLIN;
	int ret = ::epoll_ctl(_efd, EPOLL_CTL_DEL, fd, &value);
	if(ret == -1) {
		perror(">> epoll_ctl");
	}
}

void EventLoop::handleRead()
{
	uint64_t howmany = 0;
	int ret = ::read(_eventfd, &howmany, sizeof(howmany));
	if(ret != sizeof(howmany)) {
		::perror(">> read");
	}
}

void EventLoop::wakeup()
{
	uint64_t one = 1;
	int ret = ::write(_eventfd, &one, sizeof(one));
	if(ret != sizeof(one)) {
		::perror(">> write");
	}
}

void EventLoop::doPeningFunctors()
{
	vector<Functor> tmp;
	{
		MutexLockGuard autolock(_mutex);
		tmp.swap(_pendingFunctors);
	}

	for(auto & functor : tmp)
		functor();
}

}//end of namespace wd


 
