#include "./include/main.h"

MainServer::~MainServer()
{
	close(newSocket);
	std::cout << "========== Stopped ==========" << std::endl;
}

void MainServer::acceptRequest()
{
	struct sockaddr_in address = getSocketAddress()->getServerAddress();
	int addressLength = sizeof(address);

	newSocket = accept(getSocketAddress()->getSocket(), (struct sockaddr*)&address, (socklen_t*)&addressLength);
	read(newSocket, buffer, sizeof(buffer));
}

void MainServer::handleResponse()
{
	std::cout << buffer << std::endl;
}

const char* MainServer::readFile()
{
	if (strcmp(filePath, "") == 0)
	{
		std::cerr << "No file path specified!" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::ifstream file(filePath);
	std::stringstream buffer;
	buffer << file.rdbuf();

	const std::string& temp = buffer.str();
	buffer.seekp(0);
	buffer << "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" << temp;

	static std::string contents = buffer.str();
	return contents.c_str();
}

void MainServer::respondData()
{
	const char* response = readFile();
	write(newSocket, response, strlen(response));
}

void MainServer::launch()
{
	int port = ntohs(getSocketAddress()->getServerAddress().sin_port);
	std::cout << "Starting on \033]8;;http://localhost:" << port << "\033\\localhost:" << port << "\033]8;;\033\\" << std::endl;

	while (true)
	{
		std::cout << "========== Waiting ==========\n" << std::endl;
		acceptRequest();
		handleResponse();
		respondData();
		close(newSocket);
		std::cout << "========== Done =============" << std::endl;
	}
}

inline int MainServer::getSocket()
{
	return newSocket;
}
