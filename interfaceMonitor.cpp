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
#include <signal.h> 
using namespace std; 

char socket_path[] = "/tmp"
const int BUF_LEN = 100; 
bool isRunning = false; 
static volatile sig_atomic_t gotSigint = 0; 

static void signalHandler(int signum) 
{
	switch(signum) {
		case SIGINT: 
			gotSigint = 1;  
		default: 
			cout << "signalHandler("<<signum<<"): unknown" << endl; 
	}
	
}


int main(int argc, char *argv[]) {
	// variable declaration 
	struct sockaddr_un addr; 
	char buf[BUF_LEN]; 
	int fd, len, ret; 
	
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
		while (isRunning) {
		//Step 1: Send Message(Ping) to network monitor
		string ping = "Ready to monitor";
		rxBuff = write(fd, ping.c_str(), sizeof(ping.c_str() + 1));
		if (rxBuff == -1)
			cout << "Failed to send " << strerror(errno) << endl;
			
		//Step 2: Recieve message to Monitor
		rc = read(fd, buf, sizeof(buf));
		signal(SIGINT, signalHandler); 
		if (rc > 0) {
			if (strncmp("Monitor", buf, 5) == 0) {
				string ping = "Monitoring";
				rxBuff = write(fd, ping.c_str(), sizeof(ping.c_str() + 1));
				if (rxBuff == -1)
					cout << "Failed to send " << strerror(errno) << endl;
			}
			// if the Monitor sends "Shut Down" or there is a SIGINT 
			else if (strncmp("Shut Down", buf, 9) == 0 || gotSigint == 1){ 
				len = sprintf(buf, "Done") + 1; 
				ret = write(fd, buf, len);
				close(fd); 
				exit(-1); 
			}				
		}
		else
			cout << "Failed to recieve message from buffer..." << endl;

		
		//Step 4: Recieve and Open Interface
		interFace+argv[2];
		/*
			The following blocks of code do the same thing:
			1 - open the specified file for reading
			2 - read the line
			3 -send the contents over the socket to the network monitor
		*/
		//Operstate
		string fileName = interFace + "/operstate";
		char fileBuff[10];
		size_t r;
		if(readFd = open(fileName.c_str(), O_RDONLY) == -1)
			cout << "Error opening file " << strerror(errno) << endl;
		else
		 r = read(readFd, fileBuff,10);
		 if (r == -1) 
			cout << "Error reading file " << strerror(errno) << endl;
		 else {
			 rxBuff = write(fd, fileBuff, sizeof(fileBuff));
			 if (rxBuff == -1)
				 cout << "Failed to send " << strerror(errno) << endl;
			 else 
				 close(readFd); 
			 
		 }

		
		//carrier_up_count
		 string fileName = interFace + "/carrier_up_count";
		 char fileBuff[10];
		 size_t r;
		 if (readFd = open(fileName.c_str(), O_RDONLY) == -1)
			 cout << "Error opening file " << strerror(errno) << endl;
		 else
			 r = read(readFd, fileBuff, 2);
		 if (r == -1)
			 cout << "Error reading file " << strerror(errno) << endl;
		 else {
			 rxBuff = write(fd, fileBuff, sizeof(fileBuff));
			 if (rxBuff == -1)
				 cout << "Failed to send " << strerror(errno) << endl;
			 else
				 close(readFd);
		 }

		 //carrier_down_count
		 string fileName = interFace + "/carrier_down_count";
		 char fileBuff[10];
		 size_t r;
		 if (readFd = open(fileName.c_str(), O_RDONLY) == -1)
			 cout << "Error opening file " << strerror(errno) << endl;
		 else
			 r = read(readFd, fileBuff, 2);
		 if (r == -1)
			 cout << "Error reading file " << strerror(errno) << endl;
		 else {
			 rxBuff = write(fd, fileBuff, sizeof(fileBuff));
			 if (rxBuff == -1)
				 cout << "Failed to send " << strerror(errno) << endl;
			 else
				 close(readFd);

		 }

		 //rx_bytes
		 string fileName = interFace + "/statistics/rx_bytes";
		 char fileBuff[10];
		 size_t r;
		 if (readFd = open(fileName.c_str(), O_RDONLY) == -1)
			 cout << "Error opening file " << strerror(errno) << endl;
		 else
			 r = read(readFd, fileBuff, 10);
		 if (r == -1)
			 cout << "Error reading file " << strerror(errno) << endl;
		 else {
			 rxBuff = write(fd, fileBuff, sizeof(fileBuff));
			 if (rxBuff == -1)
				 cout << "Failed to send " << strerror(errno) << endl;
			 else
				 close(readFd);

		 }

		 //rx_dropped
		 string fileName = interFace + "/statistics/rx_dropped";
		 char fileBuff[10];
		 size_t r;
		 if (readFd = open(fileName.c_str(), O_RDONLY) == -1)
			 cout << "Error opening file " << strerror(errno) << endl;
		 else
			 r = read(readFd, fileBuff, 10);
		 if (r == -1)
			 cout << "Error reading file " << strerror(errno) << endl;
		 else {
			 rxBuff = write(fd, fileBuff, sizeof(fileBuff));
			 if (rxBuff == -1)
				 cout << "Failed to send " << strerror(errno) << endl;
			 else
				 close(readFd);

		 }

		 //rx_errors
		 string fileName = interFace + "/statistics/rx_errors";
		 char fileBuff[10];
		 size_t r;
		 if (readFd = open(fileName.c_str(), O_RDONLY) == -1)
			 cout << "Error opening file " << strerror(errno) << endl;
		 else
			 r = read(readFd, fileBuff, 10);
		 if (r == -1)
			 cout << "Error reading file " << strerror(errno) << endl;
		 else {
			 rxBuff = write(fd, fileBuff, sizeof(fileBuff));
			 if (rxBuff == -1)
				 cout << "Failed to send " << strerror(errno) << endl;
			 else
				 close(readFd);

		 }

		 //rx_packets
		 string fileName = interFace + "/statistics/rx_packets";
		 char fileBuff[10];
		 size_t r;
		 if (readFd = open(fileName.c_str(), O_RDONLY) == -1)
			 cout << "Error opening file " << strerror(errno) << endl;
		 else
			 r = read(readFd, fileBuff, 10);
		 if (r == -1)
			 cout << "Error reading file " << strerror(errno) << endl;
		 else {
			 rxBuff = write(fd, fileBuff, sizeof(fileBuff));
			 if (rxBuff == -1)
				 cout << "Failed to send " << strerror(errno) << endl;
			 else
				 close(readFd);

		 }

		 //tx_bytes
		 string fileName = interFace + "/statistics/tx_bytes";
		 char fileBuff[10];
		 size_t r;
		 if (readFd = open(fileName.c_str(), O_RDONLY) == -1)
			 cout << "Error opening file " << strerror(errno) << endl;
		 else
			 r = read(readFd, fileBuff, 10);
		 if (r == -1)
			 cout << "Error reading file " << strerror(errno) << endl;
		 else {
			 rxBuff = write(fd, fileBuff, sizeof(fileBuff));
			 if (rxBuff == -1)
				 cout << "Failed to send " << strerror(errno) << endl;
			 else
				 close(readFd);

		 }

		 //tx_errors
		 string fileName = interFace + "/statistics/tx_errors";
		 char fileBuff[10];
		 size_t r;
		 if (readFd = open(fileName.c_str(), O_RDONLY) == -1)
			 cout << "Error opening file " << strerror(errno) << endl;
		 else
			 r = read(readFd, fileBuff, 10);
		 if (r == -1)
			 cout << "Error reading file " << strerror(errno) << endl;
		 else {
			 rxBuff = write(fd, fileBuff, sizeof(fileBuff));
			 if (rxBuff == -1)
				 cout << "Failed to send " << strerror(errno) << endl;
			 else
				 close(readFd);

		 }

		 //tx_packets
		 string fileName = interFace + "/statistics/tx_packets";
		 char fileBuff[10];
		 size_t r;
		 if (readFd = open(fileName.c_str(), O_RDONLY) == -1)
			 cout << "Error opening file " << strerror(errno) << endl;
		 else
			 r = read(readFd, fileBuff, 10);
		 if (r == -1)
			 cout << "Error reading file " << strerror(errno) << endl;
		 else {
			 rxBuff = write(fd, fileBuff, sizeof(fileBuff));
			 if (rxBuff == -1)
				 cout << "Failed to send " << strerror(errno) << endl;
			 else
				 close(readFd);

		 }
}
