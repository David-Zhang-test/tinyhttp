#pragma once

#include<string>
#include<WinSock2.h>
#include<string.h>
using namespace std;


class Header {
public:
	Header(int client, string fileName, string pagestate);
	//~Header();
	void SendHeader();
private:
	string pagestate; //"OK","NOTFOUND","UNSUPPORTED"
	int client;
	string fileName;
	string HeadType;
	const void get_HeadType(string fileName);
};