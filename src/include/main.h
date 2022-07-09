#pragma once

#include <fstream>
#include <sstream>

#include "./server.h"

class MainServer : public Server
{
public:
	MainServer(int portName);
	void launch();

	const char* filePath;
private:
	void acceptRequest();
	void handleResponse();
	void respondData();

	const char* readFile();

	char buffer[32768] = { 0 };
	int newSocket;
};
