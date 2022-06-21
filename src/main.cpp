#include "./include/main.h"

MainServer::MainServer() : Server(AF_INET, SOCK_STREAM, 0, 420, INADDR_ANY, 10) {}

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

// TODO: Convert newlines and tabs into respective escape sequences
const char* readFile(const char* fileName)
{
	std::ifstream file(fileName);
	static std::string contents = "";

	while (getline(file, contents)) continue;
	return contents.c_str();
}

void MainServer::respondData()
{
	char* response = (char*)readFile(filePath);

	write(newSocket, response, strlen(response));
	close(newSocket);
}

void MainServer::launch()
{
	std::cout << "Starting on port " << (int)getSocketAddress()->getServerAddress().sin_port << "... Press Ctrl+C to stop." << std::endl;

	while (true)
	{
		std::cout << "========== Waiting ==========\n" << std::endl;
		acceptRequest();
		handleResponse();
		respondData();
		close(newSocket);
		std::cout << "========== Done ==========" << std::endl;
	}
}
