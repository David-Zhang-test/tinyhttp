#pragma once

#include<string>
#include<WinSock2.h>
#include<string.h>
using namespace std;


// the design of this father class is unsuccessful, since send header and read header have nothing overlaped
class Header {
public:
	Header(int client);  //constructor for read header

protected:
	int client;

};