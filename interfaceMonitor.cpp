/**
* Name: Weslie, Pavan, Jon 
* Date: 2020-03-28 
* Course: DPS912NSA 
* Documentation for Assignment #1
**/ 

#include <iostream>
#include <stdio.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <sys/un.h> 
#include <stdlib.h> 
using namespace std; 

char socket_path[] = "/tmp"

int main(int argc, char *argv[]) {
	
	// variable declaration 
	struct sockaddr_un addr; 
	char buf[100]; 
	int fd, cl, rc, len, ret; 
	bool isRunning = true; 
	
	// Create a socket 
	if ((fd = socket ( AF_UNIX, SOCK_STREAM, 0)) < 0 ) {
		cout << "Error with creation of socket" << endl; 
		cout << "server: " << strerror(errno) << endl; 
		exit(-1); 
	}
	
	// Set the socket path to a local socket file 
	memset(&addr, 0, sizeof(addr)); 
	addr.sun_family = AF_UNIX; 
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1); 
	unlink(socket_path); 
	
	// Bind the socket to this local socket file 
	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		cout << "Error with binding the socket" << endl; 
		cout << "server: " << strerror(errno) << endl; 
		close(fd); 
		exit(-1); 
	}
	
	// Listen for a connection to this local socket file 
	if (listen(fd, 5) < 0) {
		cout << "server: " << strerror(errno) << endl; 
		unlink(socket_path); 
		close(fd); 
		exit(-1); 
	}	
}
