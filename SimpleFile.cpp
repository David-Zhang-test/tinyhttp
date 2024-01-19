#include "SimpleFile.h"
#include <iostream>
using namespace std;

SimpleFile::SimpleFile(int client, string fileName) :client(client) {
	int ret = fopen_s(&resource, fileName.c_str(), "rb");
	if (ret < 0) {	// if file not found, send a not-found page to browser
		NotFound();
	}
	else {			// if found, send the file to browser
		SendFile();
	}
}

/*
SimpleFile::~SimpleFile() {
	fclose(resource);
}*/

void SimpleFile::SendFile() {
	char buff[4096];		// a temp data package
	int count = 0;			// length of sent data
	while (1) {	// a cycle until all the resource is sent to buff and sent to the browser
		// read data from resource to buff
		int ret = fread(buff, sizeof(char), sizeof(buff), resource);	
		if (ret <= 0) {
			break;
		}
		count += ret;

		// send buff
		int sent = send(client, buff, ret, 0);
		if (sent == -1) {
			perror("send");
		}
		else {
			printf("sent %d bytes \n", sent);
		}
	}

	printf("一共发送%d字节\n", count);
	fclose(resource);
}
// a todo function
void SimpleFile::NotFound() {
	cout << "to do" << endl;
}