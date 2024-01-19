#pragma once
#include "header.h"
using namespace std;


class SendHeader : public Header {
public:
	// send header constructor
	SendHeader(int client, string fileName, string pagestate);

	void sendheader();
private:
	
	string HeadType;								// head type: GET, POST, etc.
	string fileName;								// file name
	string pagestate;								// page state: "OK","NOTFOUND","UNSUPPORTED"
	const void get_HeadType(string fileName);		// read headers and get head type
};