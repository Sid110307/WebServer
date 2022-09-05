CC=clang++
EXECUTABLE_DIR=bin

CPPFLAGS=-std=c++20 -Wall -Wextra
LIBS=

OBJECTS=tests/server.cpp src/socket.cpp src/server.cpp src/main.cpp

webServer:
	mkdir -p $(EXECUTABLE_DIR)
	$(CC) $(CPPFLAGS) -o $(EXECUTABLE_DIR)/$@ $(OBJECTS) $(LIBS)
	sudo ./$(EXECUTABLE_DIR)/$@

clean:
	rm -rf $(EXECUTABLE_DIR)

