#pragma once

#include <fstream>
#include "./server.h"

class MainServer : public Server
{
public:
	MainServer();
	void launch();

	const char* filePath;
private:
	void acceptRequest();
	void handleResponse();
	void respondData();

	char buffer[32768] = { 0 };
	int newSocket;
};