#include "ListeningSocket.h"

// constructor
ListeningSocket::ListeningSocket(int domain, int service, int protocol,
	int port, u_long interface_s, int bklg) :BindingSocket(domain, service, protocol, port, interface_s) {
	backlog = bklg;
	start_listening();				// start function
	test_if_connect(listening);		// test function, inherited from BindingSocket
}
void ListeningSocket::start_listening() {
	listening = listen(get_sock(), backlog);		// call listen function
}