CPPFLAGS=-std=c++17 -Wall -Wextra
LIBS=

OBJECTS=tests/server.cpp src/socket.cpp src/server.cpp src/main.cpp

webServer:
	mkdir -p bin
	clang++ $(CPPFLAGS) -o bin/$@ $(OBJECTS) $(LIBS)
	sudo ./bin/$@

clean:
	rm -rf bin/*
