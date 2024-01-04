// 
// This is the 0.1 version using C++ to create a server.
// Though still only support GET method without cgi, I have used OOP features to rewrite it.
// 
// 24.1.4
// David John
// 



#include "sockets/libc-sockets.h"
#include "server/Server.h"

int main() {
	Server servertest1(PF_INET, SOCK_STREAM, IPPROTO_TCP, 80, INADDR_ANY, 10); // start server

	return 0;
}