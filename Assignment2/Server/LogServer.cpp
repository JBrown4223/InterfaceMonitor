#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std; 

const int PORT=1153; 
const char IP_ADDR[]="192.168.205.134"; 
const int BUF_LEN = 256;
bool isOnline;

//implementation of signal handler to exit program gracefully
static void signalHandler(int signum) {
	switch (signum) {
        case SIGINT:
            cout << "Program has been closed" << endl;
            isOnline = false;
            break;
        default:
            cout << "Program has been closed" << endl;
	}
} 

int main(void)
{
  int fd, ret, len; 
  struct sockaddr_in addr; 
  char buf[BUF_LEN]; 
  
  //Set up a signal handler to terminate the program gracefully
  struct sigaction terminate;
  terminate.sa_handler = signalHandler;
  sigemptyset(&terminate.sa_mask);
  terminate.sa_flags = 0;
  sigaction(SIGINT, &terminate, NULL);
  
  memset(&addr, 0, sizeof(addr));
   //creating and binding a socket to a temp socket file
  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
	cout << "Cannot bind socket for master file descriptor: " << strerror(errno) << endl;
	exit(-1);
  }
  
  addr.sin_family = AF_INET; 
  if ((ret = inet_pton(AF_INET, IP_ADDR, &addr.sin_addr)) < 1) {
      cout << "No such address: " << strerror(errno) << endl; 
      close(fd); 
      exit(-1); 
  }
  addr.sin_port = htons(PORT); 
  
  if ((ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr))) < 0) {
      cout << "Cannot bind the socket to the local address: " << strerror(errno) << endl; 
      exit(-1); 
  }
 
}

