#include "./include/socket.h"

Socket::Socket(int domain, int type, int protocol, int port, u_long ip)
{
	serverAddress.sin_family = domain;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = htonl(ip);

	sockfd = socket(domain, type, protocol);
	testConnection(sockfd);
}

void Socket::testConnection(int testItem)
{
	if (testItem < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

inline struct sockaddr_in Socket::getServerAddress()
{
	return serverAddress;
}

inline int Socket::getSocket()
{
	return sockfd;
}

SocketBinder::SocketBinder(int domain, int type, int protocol, int port, u_long ip) : Socket(domain, type, protocol, port, ip)
{
	int connection = connect(getSocket(), getServerAddress());
	testConnection(connection);
}

int SocketBinder::connect(int sockfd, struct sockaddr_in serverAddress)
{
	return bind(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
}

SocketConnector::SocketConnector(int domain, int type, int protocol, int port, u_long ip) : Socket(domain, type, protocol, port, ip)
{
	int connection = connectSocket(getSocket(), getServerAddress());
	testConnection(connection);
}

int SocketConnector::connectSocket(int sockfd, struct sockaddr_in serverAddress)
{
	return ::connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
}

SocketListener::SocketListener(int domain, int type, int protocol, int port, u_long ip, int backlog) : SocketBinder(domain, type, protocol, port, ip)
{
	this->backlog = backlog;
	listenSocket();
	testConnection(listener);
}

void SocketListener::listenSocket()
{
	listener = listen(getSocket(), backlog);
}
