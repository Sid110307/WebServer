#include <signal.h>
#include "../src/include/main.h"

int main()
{
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = [](int signalCode)
	{
		std::cout << "\rStopping..." << std::endl;
		exit(signalCode);
	};

	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

	MainServer server;
	server.filePath = "./tests/index.html";
	server.launch();
}
