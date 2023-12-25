#pragma once
#include<stdio.h>
#include "SimpleSocket.h"

using namespace std;

class BindingSocket : public SimpleSocket {
public:
	//Constructor
	BindingSocket(int domain, int service, int protocol, int port, u_long interface_s);
	//virutal function from parent
	int connect_to_network(int sock, struct sockaddr_in address);



};