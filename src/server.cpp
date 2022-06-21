#include "./include/server.h"

Server::Server(int domain, int type, int protocol, int port, u_long ip, int backlog)
{
	socket = new SocketListener(domain, type, protocol, port, ip, backlog);
}

SocketListener* Server::getSocketAddress()
{
	return socket;
}
