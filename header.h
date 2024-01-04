#pragma once

#include<string>
#include<WinSock2.h>
#include<string.h>
using namespace std;


class Header {
public:
	Header(int client);  //constructor for read header

protected:
	int client;

};