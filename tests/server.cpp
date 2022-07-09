#include <signal.h>
#include "../src/include/main.h"

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        exit(EXIT_FAILURE);
    }

	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = [](int signalCode)
	{
		std::cout << "========== Stopped ==========" << std::endl;
		exit(signalCode);
	};

	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);

	MainServer server(atoi(argv[1]));
	server.filePath = "./tests/index.html";
	server.launch();
}
