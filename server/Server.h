#pragma once

#include "SimpleServer.h"
#include "../libc-headers.h"
#include"../SimpleFile.h"

using namespace std;


class Server : public SimpleServer {
public:
	// server constructor
	Server(int domain, int service, int protocol, int port, u_long interface_s, int bklg);
	// start the server
	void launch();	
private:
	// accept request
	void accepter();
	// handle request: read headers
	void handler();
	// send header and send file
	void responder();
	int client_sock;	// client socket
	int server_port;	// server port
	string path;		// file path
};