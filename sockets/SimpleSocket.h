#pragma once
#include<WinSock2.h>
#include<stdio.h>
#include<iostream>

using namespace std;

class SimpleSocket {
public:
	// Constructor
	SimpleSocket(int domain, int service, int protocol, int port, u_long interface_s); 
	// domain: internetwork: UDP, TCP, etc.
	// service: socket types: stream, datagram, etc.
	// protocol: TCP, UDP, etc.
	// port
	// interface: access range
	
	
	
	// Virtual function to connect
	virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
	//Function to test if connected
	void test_if_connect(int test_item);
	// getter functions
	struct sockaddr_in get_address();
	int get_sock();
	int get_connection();
	// setter functions
	void set_connection(int cons);
private:
	int sock;						// socket
	int connection;					// connection for connectivity test
	struct sockaddr_in address;		// socket address
};