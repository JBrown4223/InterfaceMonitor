# Assignment #1

## Questions

### 1.	In a few sentences, describe the general architecture of your interface monitor. [1 mark]

The interface monitor follows a client-based architecture. It creates a socket and connects to the network monitor. Once the interface monitor is connected with the network monitor, it sends a message to the network monitor to let it know that its ready to monitor. The interface monnitor and network monitor send messages back and forth to obtain/display the required data.  When the network monitor sends a message, "Shut Down" or a SIGINT, the interface monitor will safely quit and shut down. 

### 2.	In a few sentences, describe the general architecture of your network monitor. [1 mark]
The network monitor acts like a server. First, many things such as the signal handler to terminate the program, the opening of the directory, and creating child PIDs are done first. After the ground work’s complete, sockets are created and binded to a temporary file, including the master file. Network information is read into the buffer, once all the required information is read, interfaceMonitor(s) are executed with the information in the buffer as an argument. The program then begins to listen and accepts all connects based on file descriptors, accepting new connections to the master socket and adding them to the socket set, after that, each interfaceMonitor’s input is read and a corresponding reply will be sent. A boolean variable called ‘isOnline’ keeps track of when the program has been given the termination command, the main loops all run depending if the program ‘isOnline’, and would operation if ‘isOnline’ is false. If 'isOnline' is false, 'Shut Down' messages are sent to each of the interfaceClients to terminate them.

### 3.	Could the interface monitor and network monitor all be contained within one process, if so how? [1 mark]
A interface monitor and network monitor can be contained in one process with the use of multithreads. The network monitor needs to continuously listen to the socket it is connected to. The interface monitor would run on its own thread so sending data won't block the execution of the main application. This way, sharing data between the interface monitor and network monitor would be easy.   

### 4.	Could the interface monitor and network monitor all be contained within one process, assuming 128 network interfaces running at several Giga-bits per second, which require a polling interval of one millisecond per interface. [1 mark]
No, I dont believe it can. Even if we were to use threads, threads are competing for a finite virtual address space of the host process. Threads local storage consumes a part of the process virtual address space. Even though the available virtual address space is large, there is significant limitations for processes employing large number of threads or threads that require large amounts of memory. 128 network interfaces running at several Giga-bits per second, which require a polling interval of one millisecond per interface would be considered to require large amounts of memory. 


### 5.	What is a software defined network? In doing so, describe the applications layer, the control layer, and the forwarding layer. [2 marks]

Software Defined Network: SDN is a network architecture model that allows programmatic management. It has the capability to initialize, control, change, and manage network resources dynamically through open interfaces. 

Application Layer: This layer is where applications and services that define network behaviour are kept. The application layer communicates the behaviours and needed resources with the controller layer through APIs. 

Control Layer: The control layer receives instructions and requirements from the application layer and relays them to the networking components. It extracts information about the network from the hardware devices and communicates back to the applications with information about the network, statistics, and events about what is happening. 

Forwarding Layer: Responsible for handling data packets based on the instructions received from the control layer. Actions of the forwarding plane include, but are not limited to, forwarding, dropping, and changing packets.
