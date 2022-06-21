#pragma once

#include <iostream>
#include <cstring>
#include <unistd.h>
#include "./socket.h"

class Server
{
public:
	Server(int domain, int type, int protocol, int port, u_long ip, int backlog);

	virtual void launch() = 0;
	SocketListener* getSocketAddress();
private:
	SocketListener* socket;

	virtual void acceptRequest() = 0;
	virtual void handleResponse() = 0;
	virtual void respondData() = 0;
};
