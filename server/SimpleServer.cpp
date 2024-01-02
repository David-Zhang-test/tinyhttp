#include "SimpleServer.h"

SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface_s, int bklg) {
	socket = new ListeningSocket(domain, service, protocol, port, interface_s, bklg);
	/*
	if (port == 0) {
		random_port();
		
	}
	
	else if (port > 65535) {
		perror("port out of range");
	}
	*/

}
ListeningSocket* SimpleServer::get_socket() {
	return socket;
}
/*
void SimpleServer::random_port() {
	struct sockaddr_in server_address = socket->get_address();
	int namelen = sizeof(server_address);
	getsockname((SOCKET)socket, (struct sockaddr*)&server_address, &namelen);
	printf("%d", server_address.sin_port);

}
*/