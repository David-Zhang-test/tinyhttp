#pragma once

#include "../sockets/libc-sockets.h"

using namespace std;

class SimpleServer {
public:
	// default constructor, from ListeningSocket class
	SimpleServer(int domain, int service, int protocol, int port, u_long interface_s, int bklg);
	// logical class function launch
	virtual void launch() = 0;
	// get listening socket function
	ListeningSocket* get_socket();
private:
	ListeningSocket* socket;		// listening socket
	virtual void accepter() = 0;	// logical function, which emphasize the main function of server
	virtual void handler() = 0;
	virtual void responder() = 0;
	// void random_port();			//unfortunately, the random port function has not been done yet
};