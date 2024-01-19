#include "Server.h"
#include <iostream>

using namespace std;

// default constructor
Server::Server(int domain, int service, int protocol,
	int port, u_long interface_s, int bklg) : SimpleServer(domain, service, protocol, port, interface_s, bklg) { // user SimpleServer to construct
	server_port = port; // storage port seperately
}

// accept function
void Server::accepter() {
	printf("the server has started, the port is: %d\n", server_port);
	struct sockaddr_in address = get_socket()->get_address();	// get address
	int address_len = sizeof(address);							// get address len
	client_sock = accept(get_socket()->get_sock(), (struct sockaddr*)&address, &address_len);	//get client socket

	
	// error test
	if (client_sock < 0) {
		perror("client_sock");
	}
}

// handle function
void Server::handler() {
	ReadHeader header1(client_sock);		// call read_header constructor
	string method = header1.get_method();	// read method: GET, POST, etc.
	path = header1.get_path();				// get file path
	if (method == "GET") {
		cout << "function is get" << endl;
	}
	else {
		cout << "not support" << endl;		// next version
	}
	
}

// respond function
void Server::responder() {
	SendHeader header_send(client_sock, path, "OK");	// call send_header constructor
	header_send.sendheader();							// send headers
	SimpleFile file1(client_sock, path);				// call File constructor, and send the file
	shutdown(client_sock, SD_SEND);						// shut down
	closesocket(client_sock);							// close socket
	
}

// launch server
void Server::launch() {
	while (TRUE) {
		accepter();
		handler();
		responder();
	}

}