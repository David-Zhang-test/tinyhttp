#include "Server.h"
#include <iostream>

using namespace std;

Server::Server(int domain, int service, int protocol,
	int port, u_long interface_s, int bklg) : SimpleServer(domain, service, protocol, port, interface_s, bklg) {
	server_port = port;
	launch();
}

void Server::accepter() {
	printf("the server has started, the port is: %d\n", server_port);
	struct sockaddr_in address = get_socket()->get_address();
	int address_len = sizeof(address);
	client_sock = accept(get_socket()->get_sock(), (struct sockaddr*)&address, &address_len);

	
	
	if (client_sock < 0) {
		perror("client_sock");
	}
}

void Server::handler() {
	ReadHeader header1(client_sock);		// call read_header constructor
	string method = header1.get_method();
	path = header1.get_path();
	if (method == "GET") {
		cout << "function is get" << endl;
	}
	else {
		cout << "not support" << endl;
	}
	
}

void Server::responder() {
	SendHeader header_send(client_sock, path, "OK");
	header_send.sendheader();
	SimpleFile file1(client_sock, path);
	shutdown(client_sock, SD_SEND);
	closesocket(client_sock);
	
}

void Server::launch() {
	while (TRUE) {		
		accepter();
		handler();
		responder();
	}

}