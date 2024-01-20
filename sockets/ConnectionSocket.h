#pragma once
#include<stdio.h>
#include "SimpleSocket.h"

using namespace std;

class ConnectingSocket : public SimpleSocket {
public:
	// constructor
	ConnectingSocket(int domain, int service, int protocol, int port, u_long interface_s);
	// virtual function from parent
	int connect_to_network(int sock, struct sockaddr_in address);
};