#include "muduo/net/EventLoop.h"
#include "muduo/net/TcpServer.h"


using namespace muduo;
using namespace muduo::net;


int main()
{
    EventLoop loop;
    TcpServer server(&loop, InetAddress(8888), "Finger");
    server.start();
    loop.loop();
}