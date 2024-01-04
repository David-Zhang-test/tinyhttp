#pragma once

#include<stdio.h>
#include<string>
#include<WinSock2.h>
using namespace std;


class SimpleFile {
public:
	SimpleFile(int client, string fileName);
	~SimpleFile();
	void NotFound(int client);
	void SendFile(int client, FILE* resource);


private:
	string fileName;
	int client;
	FILE* resource;
};