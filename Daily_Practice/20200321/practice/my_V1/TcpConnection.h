#pragma once

#include "InetAddress.h"
#include "Socket.h"
#include "Acceptor.h"
#include "SocketIO.h"


namespace  wd{


class TcpConnection
{
public:
    TcpConnection(int);
    ~TcpConnection();
    void send(const string & );
    string receive();
    //void shutdown();
private:
    InetAddress localInetAddr();
    InetAddress peerInetAddr();


private:
    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;
    SocketIO _socketIO;
    bool _isShutDownWrite;

};





}//end of namespace wd
