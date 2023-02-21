#include "../src/include/main.h"

int main(int argc, const char** argv)
{
	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " <file> <port>" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::ifstream file(argv[1]);
	if (!file.is_open())
	{
		perror("File not found");
		exit(EXIT_FAILURE);
	}

	file.close();
	MainServer server(atoi(argv[2]));

	server.filePath = argv[1];
	server.launch();
}
