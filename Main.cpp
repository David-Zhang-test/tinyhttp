#include "sockets/libc-sockets.h"
#include "server/Server.h"

int main() {
	Server servertest1(PF_INET, SOCK_STREAM, IPPROTO_TCP, 80, INADDR_ANY, 10);

	return 0;
}