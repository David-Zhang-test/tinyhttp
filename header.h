#pragma once

#include<string>
#include<WinSock2.h>
#include<string.h>
using namespace std;


class Header {
public:
	Header(int client, string fileName, string pagestate); // constructor for send header
	Header(int client);  //constructor for read header
	//~Header();
	void SendHeader();
	void ReadHeader();
	
private:
	int read_line();
	string pagestate; //"OK","NOTFOUND","UNSUPPORTED"
	int client;
	string fileName;
	string HeadType;
	const void get_HeadType(string fileName);
	
	string buff_r;	// read header buff
	string method;	// GET, POST, UNSUPPORTED
	string url;		// request url
	string path;	// file path

};