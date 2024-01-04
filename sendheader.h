#pragma once
#include "header.h"
using namespace std;

class SendHeader : public Header {
public:
	SendHeader(int client, string fileName, string pagestate);
	void sendheader();
private:
	
	string HeadType;
	string fileName;
	string pagestate;								//"OK","NOTFOUND","UNSUPPORTED"
	const void get_HeadType(string fileName);
};