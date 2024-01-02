#include "header.h"
#include<iostream>


Header::Header(int client, string fileName, string pagestate) :client(client), fileName(fileName), pagestate(pagestate) {
	get_HeadType(fileName);
}
Header::Header(int client) :client(client) {
	ReadHeader();
}

const void Header::get_HeadType(string fileName) {
	// decide the head type
	if (fileName != "") {
		string fileType = fileName.substr(fileName.find_last_of('.') + 1);
		if (fileType == "html") { HeadType = "text/html"; }
		else if (fileType == "css") { HeadType = "text/css"; }
		else if (fileType == "jpg") { HeadType = "image/jpg"; }
		else if (fileType == "png") { HeadType = "image/png"; }
		else if (fileType == "js") { HeadType = "application/x-javascript"; }
	}
}

void Header::SendHeader() {
	// 1.not supported/404/200
	// 2.what filetype is it
	// 3.send

	// 1.send pagestate
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

	// 2.send server name
	strcpy_s(buff, "Server: tinyhttp/0.1\r\n");
	send(client, buff, strlen(buff), 0);
	
	// 3.send content type
	sprintf_s(buff, "Content-Type:%s\r\n",HeadType.c_str());
	send(client, buff, strlen(buff), 0);

	// 4.send end
	strcpy_s(buff, "\r\n");
	send(client, buff, strlen(buff), 0);


}

void Header::ReadHeader() {
	buff_r.resize((const size_t)1024);		// read the first row
	int number_char = read_line();							


	int pos = buff_r.find_first_of(" ");	// method, GET or POST
	method = buff_r.substr(0,pos);			
	

	buff_r = buff_r.substr(pos + 1);		// request url
	pos = buff_r.find_first_of(" ");
	url = buff_r.substr(0,pos);


	path = "htm" + url;						// file path
	if (path.back() == '/') {
		path += "index.html";
	}
	struct stat status;						// check the accessibility
	if(stat(path.c_str(),&status) == -1){
		while (number_char > 0 && buff_r == "\n") {
			read_line();
		}
		// not_found();
	}
	else {
		if ((status.st_mode & S_IFMT) == S_IFDIR) {
			path += "/index.html";
		}
	}


}


int Header::read_line() {
	int i = 0;
	char c = '0';
	while (i < buff_r.length() && c != '\n') {
		int n = recv(client, &c, 1, 0);
		if (n > 0) {
			if (c == '\r') {
				n = recv(client, &c, 1, MSG_PEEK);
				if (n > 0 && c == '\n') { recv(client, &c, 1, 0); }
				else { c = '\n'; }
			}
			buff_r[i++] = c;
		}
		else { c = '\n'; }
	}
	return i;
}