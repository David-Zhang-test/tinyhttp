#include "BindingSocket.h"

// Consturctor
BindingSocket::BindingSocket(int domain, int service, int protocol,
	int port, u_long interface_s) :SimpleSocket(domain, service, protocol, port, interface_s) {
	set_connection(connect_to_network(get_sock(), get_address()));
	test_if_connect(get_connection());
}

// Definition of the virtual function
int BindingSocket::connect_to_network(int sock, struct sockaddr_in address) {
	return bind(sock, (struct sockaddr*)&address, sizeof(address));
}