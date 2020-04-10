#include <iostream>
#include <fstream>
#include <signal.h>
#include <string.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

using namespace std; 

const int PORT=1153; 
const char IP_ADDR[]="192.168.205.133"; 
const int BUF_LEN = 256;

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
  
   //creating and binding a socket to a temp socket file
  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
	cout << "Cannot bind socket for master file descriptor: " << strerror(errno) << endl;
	exit(-1);
  }
  
  memset(&addr, 0, sizeof(addr));
  myaddr.sin_family = AF_INET; 
  if ((ret = inet_pton(AF_INET, IP_ADDR, &addr.sin_addr)) < 1) {
      cout << "No such address: " << strerror(errno) << endl; 
      close(fd); 
      exit(-1); 
  }
  addr.sin_port = htons(PORT); 
  
  if ((ret = bind(fd, (struct sockaddr *)&addr, sizeof(myaddr)) < 0) {
      cout << "Cannot bind the socket to the local address: " << strerror(errno) << endl; 
      exit(-1); 
  }
 
}

