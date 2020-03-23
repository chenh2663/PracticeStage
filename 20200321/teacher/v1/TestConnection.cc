 ///
 /// @file    TestConnection.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-02-18 18:22:17
 ///
 
#include "Acceptor.h"
#include "TcpConnection.h"

#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

void test0(void)
{
	wd::Acceptor acceptor("192.168.30.128", 8888);
	acceptor.ready();

	int peerfd = acceptor.accept();
	
	wd::TcpConnection conn(peerfd);
	string msg = conn.receive();
	cout << ">> server receive: " << msg << endl;
	conn.send(msg);
	::sleep(2);
}
 
int main(void)
{
	test0();
	return 0;
}
