#pragma once
#include "header.h"
using namespace std;


class ReadHeader : public Header {
public:
	ReadHeader(int client);
	
	string get_method();
	string get_path();
private:
	void read();
	int read_line();
	string buff_r;	// read header buff
	string method;	// GET, POST, UNSUPPORTED
	string url;		// request url
	string path;	// file path

};