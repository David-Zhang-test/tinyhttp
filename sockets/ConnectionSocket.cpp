#include "ConnectionSocket.h"

ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port,
	u_long interface_s) :SimpleSocket(domain, service, protocol, port, interface_s) {
	
	set_connection(connect_to_network(get_sock(), get_address()));
	test_if_connect(get_connection());
}
int ConnectingSocket::connect_to_network(int sock, struct sockaddr_in address) {
	return connect(sock, (struct sockaddr*)&address, sizeof(address));
}