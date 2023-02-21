#pragma once

#include <fstream>
#include <sstream>

#include "./server.h"

class MainServer : public Server
{
public:
	MainServer(int portName) : Server(AF_INET, SOCK_STREAM, 0, portName, INADDR_ANY, 10) {}
	~MainServer();

	void launch();

	const char* filePath;
	int getSocket();
private:
	void acceptRequest();
	void handleResponse();
	void respondData();

	const char* readFile();

	char buffer[32768] = { 0 };
	int newSocket;
};
