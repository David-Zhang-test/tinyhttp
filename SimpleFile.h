#pragma once

#include<stdio.h>
#include<string>
#include<WinSock2.h>
using namespace std;


class SimpleFile {
public:
	// default constructor, main function is to assign the parameters
	SimpleFile(int client, string fileName);
	//~SimpleFile();
	
	// send a not found page, todo
	void NotFound();

	// send file function
	void SendFile();


private:
	string fileName;	// file name
	int client;			// client socket
	FILE* resource;		// file temp storage
};