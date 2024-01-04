#include "SimpleFile.h"
#include <iostream>
using namespace std;

SimpleFile::SimpleFile(int client, string fileName) :client(client) {
	int ret = fopen_s(&resource, fileName.c_str(), "rb");
	if (ret < 0) {
		NotFound();
	}
	else {
		SendFile();
	}
}

/*
SimpleFile::~SimpleFile() {
	fclose(resource);
}*/

void SimpleFile::SendFile() {
	char buff[4096];
	int count = 0;
	while (1) {
		int ret = fread(buff, sizeof(char), sizeof(buff), resource);
		if (ret <= 0) {
			break;
		}
		count += ret;

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

void SimpleFile::NotFound() {
	cout << "to do" << endl;
}