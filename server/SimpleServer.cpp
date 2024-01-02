#include "SimpleServer.h"

SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface_s, int bklg) {
	socket = new ListeningSocket(domain, service, protocol, port, interface_s, bklg);

}
ListeningSocket* SimpleServer::get_socket() {
	return socket;
}