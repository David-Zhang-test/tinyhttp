#pragma once

#include "BindingSocket.h"

using namespace std;

class ListeningSocket : public BindingSocket {
public:
	ListeningSocket(int domain, int service, int protocol,
		int port, u_long interface_s, int bklg);
	void start_listening();
private:
	//the maximum number can be listened
	int backlog;
	int listening;
};