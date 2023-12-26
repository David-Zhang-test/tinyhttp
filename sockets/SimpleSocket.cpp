#include "SimpleSocket.h"


//default constructor
SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface_s) {
	
	//define address
	address.sin_addr.s_addr = htonl(interface_s);
	address.sin_family = domain;
	address.sin_port = htons(port);

	//establish connection
	sock = socket(domain, service, protocol);
	test_if_connect(sock);
	

}

//connection test
void SimpleSocket::test_if_connect(int test_item) {
	if (test_item < 0) {
		perror("Failed to connect...");
		exit(EXIT_FAILURE);
	}
}

//get value functions
struct sockaddr_in SimpleSocket::get_address() {
	return address;
}
int SimpleSocket::get_sock() {
	return sock;
}
int SimpleSocket::get_connection() {
	return connection;
}
void SimpleSocket::set_connection(int cons) {
	connection = cons;
}