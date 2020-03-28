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
const int BUF_LEN = 100; 
bool isRunning = false; 


int main(int argc, char *argv[]) {
	// variable declaration 
	struct sockaddr_un addr; 
	char buf[BUF_LEN]; 
	int fd; 
	
	// Make sure user provides interface name 
	if (argc < 2) {
		cout << "Error: No interface name provided" << endl; 
		exit(-1); 
	}
	
	// Create a socket 
	if ((fd = socket (AF_UNIX, SOCK_STREAM, 0)) < 0 ) {
		cout << "Error with creation of socket" << endl; 
		cout << "client: " << strerror(errno) << endl; 
		exit(-1); 
	}
	
	// Set the socket path to a local socket file 
	memset(&addr, 0, sizeof(addr)); 
	addr.sun_family = AF_UNIX; 
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1); 
	
	// connecting to the local socket 
	if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		cout << "Error with connecting the socket" << endl; 
		cout << "client: " << strerror(errno) << endl; 
		close(fd); 
		exit(-1); 	
	}
	
	isRunning = true; 
}
