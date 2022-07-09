#include "./include/main.h"

MainServer::MainServer(int portName) : Server(AF_INET, SOCK_STREAM, 0, portName, INADDR_ANY, 10) {}

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
	std::cout << "Starting on \033[1;4mlocalhost:" << ntohs(getSocketAddress()->getServerAddress().sin_port) << "\033[0m... Press Ctrl+C to stop." << std::endl;

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
