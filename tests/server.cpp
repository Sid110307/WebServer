#include <signal.h>
#include "../src/include/main.h"

MainServer server;

static void signalHandler(int signalCode)
{
	close(server.getSocket());
	std::cout << "========== Stopped ==========" << std::endl;

	exit(signalCode);
};

int main(int argc, const char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
		exit(EXIT_FAILURE);
	}

	server = MainServer(atoi(argv[1]));

	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = signalHandler;

	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	server.filePath = "./tests/index.html";
	server.launch();
}
