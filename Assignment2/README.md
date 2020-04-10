# Assignment #2 Questions: 

## Questions

### 1.	Generally, what are syslog and rsyslog? Specifically, name three features of syslog/rsyslog and compare them to your embedded debug logging. Will there be any overlap of information?

syslog - is a way for network devices to send event messages to a logging server – usually known as a Syslog server. This is a standard for messaging logging. It allows separation of the software that generate messages, the system that stores them, and the software that reports and analyzes them. 

rsyslog - RSYSLOG is the rocket-fast system for log processing. It offers high-performance, great security features and a modular design. While it started as a regular syslogd, rsyslog has evolved into a kind of swiss army knife of logging, being able to accept inputs from a wide variety of sources, transform them, and output to the results to diverse destinations.

3 features of syslog/rsyslog: 
  1. 


#INCOMPLETE 










### 2.	Name five features of syslog-ng.

1. Receive and send JSON formatted messages
2. Work with any type of unstructured data 
3. Normalize, crunch, and process logs as they flow through the system
4. Hand over logs for further processing using files, message queues, or databases
5. Forward logs to big data tools (like Elasticsearch, Apache Kafka, or Apache Hadoop)
6. Receive and send RFC3164 and RFC5424 style syslog messages

#COMPLETED 

### 3.	Name five ways syslog-ng is an improvement over syslog/rsyslog.

1. syslog-ng has the ability to classify, tag, and correlate log messages in real-time
2. 

#INCOMPLETE 





### 4.	Consider a Log Server that has to manage embedded logs for a massive amount of processes on a massive amount of machines. Name three ways the server could manage the connections to each process.








### 5.	Consider a Log Server that has to manage embedded logs for a massive amount of processes on a massive amount of machines. With such a large amount of data in the logs, name three ways a user could extract useful information from them (be general).








### 6.	Explain how gdb could be used on a Linux machine to attach to a process and get thread information. Is this also useful in debugging?

