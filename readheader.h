#pragma once
#include "header.h"
using namespace std;


class ReadHeader : public Header {
public:
	// constructor
	ReadHeader(int client);
	
	// getter function
	string get_method();
	string get_path();
private:
	void readheader();
	int read_line();
	string buff_r;	// read header buff
	string method;	// GET, POST, UNSUPPORTED
	string url;		// request url
	string path;	// file path

};