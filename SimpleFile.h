#pragma once

#include<stdio.h>
#include<string>
#include<WinSock2.h>
using namespace std;


class SimpleFile {
public:
	SimpleFile(int client, string fileName);
	//~SimpleFile();
	void NotFound();
	void SendFile();


private:
	string fileName;
	int client;
	FILE* resource;
};