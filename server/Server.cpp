#include "Server.h"

Server::Server(int domain, int service, int protocol,
	int port, u_long interface_s, int bklg) : SimpleServer(domain, service, protocol, default_port, interface_s, bklg) {
	
	launch();
}

void Server::accepter() {
	struct sockaddr_in address = get_socket()->get_address();
	int address_len = sizeof(address);
	client_sock = accept(get_socket()->get_sock(), (struct sockaddr*)&address, &address_len);
	
}

void Server::handler() {

}

void Server::responder() {
	closesocket(client_sock);
}

void Server::launch() {
	while (TRUE) {
		accepter();
		handler();
		responder();
	}
	

}