#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <fcntl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std; 

const int PORT=1153; 
const char IP_ADDR[] = "127.0.0.1";
const int BUF_LEN = 4096;
bool isOnline;
struct sockaddr_in remaddr;

queue<string>messages;

void* recv_func(void* arg);
pthread_mutex_t lock_x;


int masterSocket, ret, len;
struct sockaddr_in clientAddr;
socklen_t addrlen = sizeof(remaddr);
char buf[BUF_LEN];


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

	

	//Set up a signal handler to terminate the program gracefully
	struct sigaction terminate;
	terminate.sa_handler = signalHandler;
	sigemptyset(&terminate.sa_mask);
	terminate.sa_flags = 0;
	sigaction(SIGINT, &terminate, NULL);

	
  memset(&clientAddr, 0, sizeof(clientAddr));
   //creating and binding a socket to a temp socket file
  masterSocket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
  if(masterSocket == -1){
	cout << "Cannot bind socket for master file descriptor: " << strerror(errno) << endl;
	exit(-1);
  }
  
  memset((char*)&clientAddr, 0, sizeof(clientAddr));
  clientAddr.sin_family = AF_INET;

  ret = inet_pton(AF_INET, IP_ADDR, &clientAddr.sin_addr);
  
  ret = bind(masterSocket, (struct sockaddr*) & clientAddr, sizeof(clientAddr));
  if(ret < 0){
      cout << "Cannot bind the socket to the local address: " << strerror(errno) << endl; 
      exit(-1); 
  }


  //Mutex thread creation
  pthread_mutex_init(&lock_x, NULL);
  pthread_t tid;
  ret = pthread_create(&tid, NULL, recv_func, &masterSocket);
  if (ret != 0) {
	  cout  << ": Cannot create receive thread" << endl;
	  cout << strerror(errno) << endl;
	  close(masterSocket);
	  return -1;
  }


  isOnline = true;
  int select = -1;
  char x;
  do {



	  //User Selection
	  cout << "Make a Selection..." << endl;
	  cout << "2: Dump the log file here" << endl;
	  cout << "1: Set the log level" << endl;
	  cout << "0: Shutdown" << endl;
	  cin >> select;


	  switch (select) {
	  case 1:
		  int level = -1;

		  cout << "Choose a level of severity[(1) DEBUG, (2) WARNING, (3) ERROR, (4) CRITICAL]:  " << endl;
		  cin >> level;



		  //Set Log Level
		  memset(buf, 0, BUF_LEN);
		  len = sprintf(buf, "Set Log Level=%d", level - 1) + 1;
		  sendto(masterSocket, buf, len, 0, (struct sockaddr*) & remaddr, addrlen);

		  break;

	  case 2:
		  //Dump the log file here
		  FILE * fp;
		  fp = fopen("LogFile.txt", "r");
		  if (fp == NULL) {
			  cout << "Cannot open syslog file" << endl;
			  cout << strerror(errno) << endl;
		  }
		  else {
			  memset(buf, 0, BUF_LEN);

			  while (!feof(fp)) {
				  fgets(buf, BUF_LEN, fp);
				  puts(buf);
			  }
			  fclose(fp);
		  }


		  break;

	  case 0:

		  cout << "Shutting down" << endl;
		  isOnline = false;
		  break;

	  }
	  if (select != 0) {
		  char key;
		  cout << "Press any key to continues: ";
		  cin >> key;
		  system("clear");
	  }
  
  } while (isOnline);
 
  
  pthread_join(tid, NULL);
  close(masterSocket);
  



  return 0;
 
}

//Recieve Function for thread mutex
void* recv_func(void* arg) {
	FILE* fp;
	fp = fopen("LogFile.txt", "w");
	if (fp == NULL) {
		cout << "Can't open file" << endl;
		cout << strerror(errno) << endl;
	}
	int fd1 = *(int*)arg;
	int len;
	socklen_t addrlen = sizeof(remaddr);
	char buf[BUF_LEN];


	memset(buf, 0, BUF_LEN);
	cout << "Recieve Thread: " << endl;
	while (isOnline) {
		pthread_mutex_lock(&lock_x);
		len = recvfrom(fd1, buf, BUF_LEN, 0, (struct sockaddr*) & remaddr, &addrlen) - 1;
		pthread_mutex_unlock(&lock_x);

		if (len < 0) {
			sleep(1);
		}
		else {
			fprintf(fp, "%s\n", buf);
		}

	}
	fclose(fp);

	pthread_exit(NULL);
}

