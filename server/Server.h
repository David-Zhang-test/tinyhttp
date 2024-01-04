#pragma once

#include "SimpleServer.h"
#include "../libc-headers.h"

using namespace std;

class Server : public SimpleServer {
public:
	Server(int domain, int service, int protocol, int port, u_long interface_s, int bklg);
	void launch();
private:
	void accepter();
	void handler();
	void responder();
	int client_sock;
	int server_port;
};