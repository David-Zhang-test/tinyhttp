#include "readheader.h"
using namespace std;


ReadHeader::ReadHeader(int client) :Header(client) {
	readheader();
}

// read header function
void ReadHeader::readheader() {
	buff_r.resize((const size_t)1024);		// read the first row
	int number_char = read_line();


	int pos = buff_r.find_first_of(" ");	// method, GET or POST
	method = buff_r.substr(0, pos);


	buff_r = buff_r.substr(pos + 1);		// request url
	pos = buff_r.find_first_of(" ");
	url = buff_r.substr(0, pos);


	path = "htm" + url;						// file path
	if (path.back() == '/') {
		path += "index.html";
	}
	struct stat status;						// check the accessibility
	if (stat(path.c_str(), &status) == -1) {
		while (number_char > 0 && buff_r == "\n") {
			read_line();
		}
		// not_found();
	}
	else {
		if ((status.st_mode & S_IFMT) == S_IFDIR) {
			path += "/index.html";
		}
		while (number_char > 0 && buff_r == "\n") {
			read_line();
		}
	}
}

// read line function
int ReadHeader::read_line() {
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

// getter function
string ReadHeader::get_method() {
	return method;
}
string ReadHeader::get_path() {
	return path;
}