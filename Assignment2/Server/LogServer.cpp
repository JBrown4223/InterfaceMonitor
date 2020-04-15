#include <iostream>
#include <queue>
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
struct sockaddr_in remaddr;

void* recv_func(void* arg);
pthread_mutex_t lock_x;


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

	int masterSocket, fd, ret, c, len, * new_sock;
	struct sockaddr_in addr, clientAddr;
	char buf[BUF_LEN];

	//Set up a signal handler to terminate the program gracefully
	struct sigaction terminate;
	terminate.sa_handler = signalHandler;
	sigemptyset(&terminate.sa_mask);
	terminate.sa_flags = 0;
	sigaction(SIGINT, &terminate, NULL);

	
  memset(&addr, 0, sizeof(addr));
   //creating and binding a socket to a temp socket file
  if ((masterSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
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
  
  if ((ret = bind(masterSocket, (struct sockaddr *)&addr, sizeof(addr))) < 0) {
      cout << "Cannot bind the socket to the local address: " << strerror(errno) << endl; 
      exit(-1); 
  }
  //creation of recieve thread
  memset((char*)&clientAddr, 0, sizeof(clientAddr));
  clientAddr.sin_family = AF_INET;
  ret = inet_pton(AF_INET, IP_ADDR, &clientAddr.sin_addr);
  if (ret == 0) {
	  cout << " No such address" << endl;
	  cout << strerror(errno) << endl;
	  close(fd);
	  return -1;
  }
  clientAddr.sin_port = htons(encoder.ip_port);

  //Mutex thread creation
  pthread_t tid;
  ret = pthread_create(&tid, NULL, recv_func, &fd);
  if (ret != 0) {
	  cout  << ": Cannot create receive thread" << endl;
	  cout << strerror(errno) << endl;
	  close(fd);
	  return -1;
  }
 pthread_mutex_init(&lock_x, NULL);

 pthread_mutex_lock(&lock_x);
  bool isOnline = true;
  int select = -1;
  char x;
  do {



	  //User Selection
	  cout << "Make a Selection..." << endl;
	  cout << "2: Dump the log file here" << endl;
	  cout << "1: Set the log level" << endl;
	  cout << "0: Shutdown" << endl;
	  cin >> select;


	  if (select == 1) {
		  //Set Log Level
		  memset(buf, 0, BUF_LEN);
		  len = sprintf(buf, "Set Log Level=%d", level) + 1;
		  sendto(fd, buf, len, 0, (struct sockaddr*) & remaddr, addrlen);
		  

	  }
	  else if (select == 2) {
		  //Dump the log file here
		  c = open('./LogFile.txt', O_RDONLY);
		  if (c == -1)
			  cout << strerror(errno) << endl;

		  int r = read(c, buf, BUF_LEN);
		  if (r == -1)
			  cout << strerror(errno) << endl;
		  cout << buf << endl;
		  cout << "Press any key to continue: ";
		  cin >> x >> endl;


	  }
	  else if (select == 0) {

		  is_running = false
			  online = false


	  }
	  else
		  cout << "Invalid Selection....Try Again" << endl;
	
  
  } while (isOnline);
  pthread_join(tid, NULL);
  close(fd);
  pthread_close(NULL);



  //Recieve Function for thread mutex
  void* recv_func(void* arg)
  {
	  int fd1 = *(int*)arg;
	  int writeFD, openFD;
	  socklen_t addrlen = sizeof(remaddr);
	  char buf[100];

	  cout << "Recieve Thread: " << endl;
	  while (is_running) {
		  memset(buf, 0, 100);
		  int len = recvfrom(fd1, buf, BUF_LEN, 0, (struct sockaddr*) & remaddr, &addrlen);
		  cout << "received " << len << " bytes from " << inet_ntoa(remaddr.sin_addr) << endl;
		  openFD = open('./LogFile.txt', O_WRONLY, O_CREAT, O_TRUNC);
		  if (writeFD == -1)
			  cout << strerror(errno) << endl;
		  pthread_mutex_lock(&lock_x);
		  writeFD = write(openFD, buf, sizeof(buf));
		  pthread_mutex_unlock(&lock_x);
	  }
  }
 

  return 0;
 
}

