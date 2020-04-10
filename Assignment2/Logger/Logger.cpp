#include "Logger.h"
#include <arpa/inet.h>
#include <iostream>
#include <net/if.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>


LOG_LEVEL logLevel;
const int PORT = 1153; 
const char IP_ADDR[] = "192.168.205.134"; 

Logger::InitializeLog() {
  int fd, ret, len; 
  struct sockaddr_in servaddr; 

  if ((fd = socket(AF_INET, SOCK_DGRAM, 0))<0){
	cout << "Cannot create the socket: " << strerror(errno) << endl; 
	exit(-1); 
  }
  
  memset((char *)&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  
  if ((ret = inet_pton(AF_INET, IP_ADDR, &servaddr.sin_addr))==0){
	cout << "No such address: " << strerror(errno) << endl; 
	close(fd); 
	exit(-1); 
  }
  servaddr.sin_port = htons(PORT); 

 // INCOMPLETE  
}

Logger::SetLogLevel(LOG_LEVEL level){
    logLevel = level; 
}

Logger::Log(LOG_LEVEL level, const char *prog, const char *func, int line, const char *message){
  
  
}

Logger::ExitLog(){
  
  
}
