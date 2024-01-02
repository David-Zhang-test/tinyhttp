#pragma once

#include "../sockets/libc-sockets.h"

using namespace std;

class SimpleServer {
public:
	SimpleServer(int domain, int service, int protocol, int port, u_long interface_s, int bklg);
	virtual void launch() = 0;
	ListeningSocket* get_socket();
private:
	ListeningSocket* socket;
	virtual void accepter() = 0;
	virtual void handler() = 0;
	virtual void responder() = 0;
};