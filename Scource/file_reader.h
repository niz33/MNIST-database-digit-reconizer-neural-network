#pragma once
#include<iostream>
#include<fstream>
using namespace std;
struct image {
	int label;
	char p[30][30];
};
class traning_data {
public:
	unsigned int magic_number, image_width, image_height, image_count;
	image i[60000];
	void import_data() {
		ifstream image_file ("Resource Files\train-images.data", ios::binary | ios::in);
		char temp[4]={0,0,0,0};
		image_file.read(temp, 4);
		cout << (int)temp[0] << " " << (int)temp[1] << " " << (int)temp[2] << " " << (int)temp[3] << endl;
		magic_number = temp[3] | (temp[2] << 8) | (temp[1] << 16) | (temp[0] << 24);
	}
};