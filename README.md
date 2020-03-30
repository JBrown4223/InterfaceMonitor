# Assignment #1

## Questions

### 1.	In a few sentences, describe the general architecture of your interface monitor. [1 mark]

The interface monitor follows a client-based architecture. It creates a socket and connects to the network monitor. Once the interface monitor is connected with the network monitor, it sends a message to the network monitor to let it know that its ready to monitor. The interface monnitor and network monitor send messages back and forth to obtain/display the required data.  When the network monitor sends a message, "Shut Down" or a SIGINT, the interface monitor will safely quit and shut down. 

### 3.	Could the interface monitor and network monitor all be contained within one process, if so how? [1 mark]
A interface monitor and network monitor can be contained in one process with the use of multithreads. The network monitor needs to continuously listen to the socket it is connected to. The interface monitor would run on its own thread so sending data won't block the execution of the main application.   

(MAYBE? I am not sure) 



### 4.	Could the interface monitor and network monitor all be contained within one process, assuming 128 network interfaces running at several Giga-bits per second, which require a polling interval of one millisecond per interface. [1 mark]
No, I dont believe it can. Even if we were to use threads, threads are competing for a finite virtual address space of the host process. Threads local storage consumes a part of the process virtual address space. Even though the available virtual address space is large, there is significant limitations for processes employing large number of threads or threads that require large amounts of memory. 128 network interfaces running at several Giga-bits per second, which require a polling interval of one millisecond per interface would be considered to require large amounts of memory. 


### 5.	What is a software defined network? In doing so, describe the applications layer, the control layer, and the forwarding layer. [2 marks]

Software Defined Network = SDN refers to the network architecture model that allows programmatic management, control and optimization of network resources. SND separates network configuration and traffic engineering from the underlying hardware infrastructure to ensure holistic and consistent control of the network using open APIs. 

Application Layer = The plane where applications and services that define network behavior reside. Applications that directly (or primarily) support the operation of the forwarding plane (such as routing processes within the control plane) are not considered part of the application plane.

Control Layer = Responsible for making decisions on how packets should be forwarded by one or more network devices and pushing such decisions down to the network devices for execution. The control plane main job is to fine-tune the forwarding tables that reside in the forwarding plane, based on the network topology or external service requests.

Forwarding Layer = Responsible for handling data packets based on the instructions received from the control plane. Actions of the forwarding plane include, but are not limited to, forwarding, dropping, and changing packets. Examples of forwarding resources are classifiers, meters, etc. The forwarding plane is also widely referred to as the "data plane" or the "data path".

https://sdn.ieee.org/newsletter/september-2017/overview-of-rfc7426-sdn-layers-and-architecture-terminology
