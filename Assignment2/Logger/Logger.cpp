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

// Variable Declaration 
char logLevel;
const int BUF_LEN=4096; 
const int PORT = 1153; 
const char IP_ADDR[] = "192.168.205.134";
int fd; 
bool is_running; 
struct sockaddr_in servaddr; 
pthread_mutex_t mutex_lock; 

//function declaration 
void *recv_func(void *arg); 

// This initializes the log. 
int InitializeLog() {
int ret, len;  
socklen_t addrlen = sizeof(servaddr); 
char buff[BUF_LEN]; 

  if ((fd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0))<0){
	cout << "Cannot create the socket: " << strerror(errno) << endl; 
	return(-1); 
  }
  
  memset((char *)&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  
  if ((ret = inet_pton(AF_INET, IP_ADDR, &servaddr.sin_addr))==0){
	cout << "No such address: " << strerror(errno) << endl; 
	close(fd); 
	exit(-1); 
  }
  servaddr.sin_port = htons(PORT); 
  pthread_mutex_init(&mutex_lock, NULL); 
  is_running = true; 
  pthread_t thread_1; 
  ret = pthread_create(&thread_1, NULL, recv_func, &fd); 
  if(ret!=0) {
	cout << "The thread cannot start: " << strerror(errno)<<endl; 
	close(fd); 
	return(-1); 
  }
}

// receive thread function that is waiting for a command from the server. 
void *recv_func(void *arg) 
{
	// Variable Declaration 
	int fd = *(int *)arg; 
	socklen_t addrlen = sizeof(servaddr); 
	char buf[BUF_LEN]; 

	cout << "Server reading:" << endl; 
	while(is_running) {
		memset(buf, 0, 110); 
		pthread_mutex_lock(&mutex_lock); 
		int len = recvfrom(fd, buf, BUF_LEN, 0, (struct sockaddr *)&servaddr, &addrlen)-1; 
		pthread_mutex_unlock(&mutex_lock); 
		if(len<0) {
			sleep(1); 
		}
		else {
			char lgLevel[] = "Set Log Level="; 
			len=strlen(lgLevel); 
			if(strncmp(lgLevel, buf, len)==0) {
				logLevel = atoi(&buf[len]); 
				cout << logLevel << endl; 
			}
			else {
				cout << lgLevel << endl; 
			}
		}


	}	
// closing and exiting the pthread. 
cout << "exit pthread" << endl; 
pthread_exit(NULL); 

}

// This sets the Log Level 
void SetLogLevel(LOG_LEVEL level)
{

    logLevel = level; 
}

// This log function creates the log that will be sent to the server. 
// It compares the severity of the log and filter log. 
// // creates the log and then sends it to the server.  
void Log(LOG_LEVEL level, const char *prog, const char *func, int line, const char *message){
	// Variable Declaration 
	int ret, len; 
	time_t now = time(0);
	char *dt = ctime(&now);
	len = strlen(dt); 
	dt[len-1]='\0'; 
        char buf[BUF_LEN]; 

	// Compare the severity of the log. The log is thrown away if the serverity is 
	// lower than the filter log severity 
	if(level<logLevel){
		return; 
	}
	
	memset(buf, 0, BUF_LEN);
        char levelStr[][16]={"DEBUG", "WARNING", "ERROR", "CRITICAL"};
        len = sprintf(buf, "%s %s %s:%s:%d %s\n", dt, levelStr[level], prog, func, line, message)+1;
        buf[len-1]='\0';
	
	// message is sent to the server via sendto(). 
	ret = sendto(fd, buf, len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr)); 
}

// This exits the log. 
void ExitLog(){
	cout << "Exiting Log" << endl; 
	is_running = false;
        close(fd); 	
}
