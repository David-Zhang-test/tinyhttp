#include "header.h"
#include<iostream>


Header::Header(int client, string fileName, string pagestate) :client(client), fileName(fileName), pagestate(pagestate) {
	get_HeadType(fileName);
}

const void Header::get_HeadType(string fileName) {
	//decide the head type
	//to do
	string fileType = fileName.substr(fileName.find_last_of('.')+1);
	if (fileType == "html") { HeadType = "text/html"; }
	else if (fileType == "css") { HeadType = "text/css"; }
	else if (fileType == "jpg") { HeadType = "image/jpg"; }
	else if (fileType == "png") { HeadType = "image/png"; }
	else if (fileType == "js") { HeadType = "application/x-javascript"; }

}
void Header::SendHeader() {
	//1. not supported/404/200
	//2. what filetype is it
	//3. send

	//1.send pagestate
	char buff[1024];
	if (pagestate == "OK") {
		strcpy_s(buff, "HTTP/1.1 200 OK\r\n");
	}
	else if (pagestate == "NOTFOUND") {
		strcpy_s(buff, "HTTP/1.1 404 NOT FOUND\r\n");
	}
	else if (pagestate == "UNSUPPORTED") {
		strcpy_s(buff, "HTTP/1.1 501 Method Not Implemented\r\n");
	}
	send(client, buff, strlen(buff), 0);

	//2.send server name
	strcpy_s(buff, "Server: tinyhttp/0.1\r\n");
	send(client, buff, strlen(buff), 0);
	
	//3.send content type
	sprintf_s(buff, "Content-Type:%s\r\n",HeadType.c_str());
	send(client, buff, strlen(buff), 0);

	//4.send end
	strcpy_s(buff, "\r\n");
	send(client, buff, strlen(buff), 0);


}