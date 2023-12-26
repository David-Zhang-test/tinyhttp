#include<stdint.h>
#include<stdio.h>

#include<sys/types.h>
#include<sys/stat.h>

#pragma comment(lib, "WS2_32.lib")
#include "header.h"
#include "log.h"
#include "sockets/libc-sockets.h"

#define PRINTF(str) printf("[%s - %d]"#str": %s\n",__func__, __LINE__, str);

void error_die(const char* str) {
	perror(str);
	exit(1);
}

int startup(int* port) {
	//startup
	WSADATA data;
	INT32 ret = WSAStartup(MAKEWORD(1, 1), &data);
	if (ret != 0) { error_die("WSAStartup"); }

	// create socket
	INT32 server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == -1) { error_die("socket"); }

	// set socket option
	INT32 opt = 1;
	ret = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
	if (ret == -1) { error_die("setsocketopt"); }

	//config server network
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(*port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind socket
	if (bind(server_socket, (const sockaddr*)&server_addr, sizeof(server_addr)) < 0) { error_die("bind"); }

	//dynamic port
	INT32 nameLen = sizeof(server_addr);
	if (*port == 0) {
		if (getsockname(server_socket, (struct sockaddr*)&server_addr, &nameLen) < 0) { error_die("getsockname"); }
		*port = server_addr.sin_port;
	}
	
	//listen port
	if (listen(server_socket, 5) < 0) { error_die("listen"); }
	
	return server_socket;

}


int read_line(int sock, char* buff, int size) {
	char c = 0;
	int i = 0;
	while (i < size - 1 && c != '\n') {
		int n = recv(sock, &c, 1, 0);
		if (n > 0) {
			if (c == '\r') {
				n = recv(sock, &c, 1, MSG_PEEK);
				if (n > 0 && c == '\n') { recv(sock, &c, 1, 0); }
				else { c = '\n'; }
			}
			buff[i++] = c;
		}
		else {
			c = '\n';
		}
	}
	buff[i] = 0;

	return i;
}
void unsupported_method(int client) {
	//to do
	char buf[1024];
	Header headerus(client,"", "UNSUPPORTED");
	headerus.SendHeader();
	/*
	strcpy_s(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy_s(buf, "Server: tinyhttp / 0.1\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy_s(buf, "Content-Type: text/html\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy_s(buf, "\r\n");
	send(client, buf, strlen(buf), 0);
	*/
	strcpy_s(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy_s(buf, "</TITLE></HEAD>\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy_s(buf, "<BODY><P>HTTP request method not supported.\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy_s(buf, "</BODY></HTML>\r\n");
	send(client, buf, strlen(buf), 0);
}
void not_found(int client) {
	//to do
	Header headernf(client, "", "NOTFOUND");
	headernf.SendHeader();
	char buff[1024];
	/*
	
	strcpy_s(buff, "HTTP/1.1 404 NOT FOUND\r\n");
	send(client, buff, strlen(buff), 0);
	strcpy_s(buff, "Server: tinyhttp/0.1\r\n");
	send(client, buff, strlen(buff), 0);
	strcpy_s(buff, "Content-Type:text/html\r\n");
	send(client, buff, strlen(buff), 0);
	strcpy_s(buff, "\r\n");
	
	
	send(client, buff, strlen(buff), 0);
	*/
	strcpy_s(buff,
		"<HTML>							\
		<TITLE>NOT FOUND </TITLE>		\
		<BODY><H2> The resource is unavailable </H2></BODY> \
		</HTML>"
		);
	send(client, buff, strlen(buff), 0);

}
const char* gethead_type(const char* fileName) {
	const char* ret = "text/html";
	const char* p = strrchr(fileName, '.');
	if (!p) return ret;
	p++;
	if (!strcmp(p, "css")) ret = "text/css";
	else if (!strcmp(p, "jpg")) ret = "image/jpg";
	else if (!strcmp(p, "png")) ret = "image/png";
	else if (!strcmp(p, "js")) ret = "application/x-javascript";
	return ret;
	


}

void cat(int client, FILE* resource) {
	//send file
	char buff[4096];

	int count = 0;

	
	while (1) {
		int ret = fread(buff, sizeof(char), sizeof(buff), resource);
		if (ret <= 0) {
			break;
		}
		count += ret;
		
		int sent = send(client, buff, ret, 0);
		if (sent == -1) {
			error_die("send");
		}
		else {
			printf("sent %d bytes \n", sent);
		}
	}
	
	printf("一共发送%d字节\n", count);
	
	

}
void server_file(int client, const char* fileName) {
	//read headers and clean up
	char buff[1024];
	int number_char = 1;
	while (number_char > 0 && strcmp(buff, "\n")) {
		read_line(client, buff, sizeof(buff));
	}
	
	//read and send file
	FILE* resource;
	if (fopen_s(&resource, fileName, "rb") != 0) {
		
		
		not_found(client);
	}
	else {
		string str(fileName);
		//headers(client,gethead_type(fileName));
		Header headers(client, str , "OK");
		headers.SendHeader();
		cat(client, resource);
		printf("资源发送完毕！\n");
	}

	fclose(resource);


}
//thread 
DWORD WINAPI accept_request(LPVOID arg) {
	char buff[1024]; //all request data
	int client = (SOCKET)arg;
	int number_char = read_line(client, buff, sizeof(buff));
	PRINTF(buff);

	//resolve data method
	char method[255];
	int i = 0, j = 0;
	while (!isspace(buff[j])) {
		method[i++] = buff[j++];
	}
	method[i] = 0;
	PRINTF(method);
	if (_stricmp(method, "GET") && _stricmp(method, "POST")) {
		// return wrong
		unsupported_method(client);
		return 0;

	}

	//resolve data url
	char url[255];
	i = 0;
	while (isspace(buff[j]) && j < sizeof(buff)) { //jump ' '
		j++;
	}
	while (!isspace(buff[j]) && i < sizeof(url) - 1 && j < sizeof(buff)) {
		url[i++] = buff[j++];
	}
	url[i] = 0;
	PRINTF(url);


	//connect path and url
	char path[512] = "";
	sprintf_s(path, "htm%s", url);
	if (path[strlen(path) - 1] == '/') {
		strcat_s(path, "index.html");
	}
	struct stat status;
	if(stat(path,&status) == -1){ //if not found, clear up the memory and print out not found
		while (number_char>0 && strcmp(buff,"\n")) {
			read_line(client, buff, sizeof(buff));
		}
		
		not_found(client);
	}
	else { //if found, connect index.html
		if ((status.st_mode & S_IFMT) == S_IFDIR) {
			strcat_s(path, "/index.html");
		}
		server_file(client, path);
	}
	
	closesocket(client);


	return 0;
}

int main() {
	//starting http server
	int port = 80;
	int server_sock = startup(&port);
	printf("http服务已经启动，正在监听%d端口", port);

	//
	struct sockaddr_in client_addr;
	int client_addr_len = sizeof(client_addr);
	while (1) {
		int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len);
		if (client_sock == -1) { error_die("accpet"); }

		DWORD threadId = 0;
		CreateThread(0, 0, accept_request, (void*)client_sock, 0, &threadId);
	}
	closesocket(server_sock);




	return 0;

	
}