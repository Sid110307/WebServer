#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

class Socket
{
public:
	Socket(int domain, int type, int protocol, int port, u_long ip);
	int connect(int sockfd, struct sockaddr_in serverAddress);
	void testConnection(int testItem);

	struct sockaddr_in getServerAddress();
	int getSocket();
private:
	struct sockaddr_in serverAddress;
	int sockfd;
};

class SocketBinder : public Socket
{
public:
	SocketBinder(int domain, int type, int protocol, int port, u_long ip);
private:
	int connect(int sockfd, struct sockaddr_in serverAddress);
};

class SocketConnector : public Socket
{
public:
	SocketConnector(int domain, int type, int protocol, int port, u_long ip);
	int connectSocket(int sockfd, struct sockaddr_in serverAddress);
};

class SocketListener : public SocketBinder
{
public:
	SocketListener(int domain, int type, int protocol, int port, u_long ip, int backlog);
	void listenSocket();
private:
	int backlog;
	int listener;
};
