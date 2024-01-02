#include "Server.h"

Server::Server(int domain, int service, int protocol,
	int port, u_long interface_s, int bklg) : SimpleServer(domain, service, protocol, port, interface_s, bklg) {
	server_port = get_socket()->get_address().sin_port;
	launch();
}

void Server::accepter() {
	struct sockaddr_in address = get_socket()->get_address();
	int address_len = sizeof(address);

	printf("the server has started, the port is: %d\n", server_port);
	client_sock = accept(get_socket()->get_sock(), (struct sockaddr*)&address, &address_len);
	if (client_sock < 0) {
		perror("client_sock");
	}
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