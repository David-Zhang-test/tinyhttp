#pragma once

#include "BindingSocket.h"

using namespace std;

// every listening socket is a binding socket
class ListeningSocket : public BindingSocket {
public:
	// constructor
	ListeningSocket(int domain, int service, int protocol,
		int port, u_long interface_s, int bklg);
	// start function
	void start_listening();
private:
	int backlog;		// the maximum number can be listened
	int listening;		// test variable
};