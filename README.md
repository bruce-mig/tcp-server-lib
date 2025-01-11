# tcp-server-lib

Implementation of TCP Server Library in C/C++

C++ Library which provides TCP-Connection Management functionality to applications.

Functionality includes:
 - Creating Multithreaded Clients
 - Notify about client connection/disconnection/msg recvd
 - Maintaining stats per client
 - Client Migration ( from threaded to Multiplexed and Vice-Versa)
 - Detecting connection termination based on Keep-Alive Msgs
 - TCP Message Demarcation.