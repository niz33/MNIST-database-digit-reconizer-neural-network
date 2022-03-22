#pragma once
#include<iostream>
#include<fstream>
using namespace std;
struct image {
	int label;
	unsigned char p[30][30];
};
class image_dataset {
public:
	unsigned int magic_number, image_width, image_height, image_count, expected_image_magic_number = 2051, expected_label_magic_number = 2049;
	bool data_loaded = false;
	image images[60000];
	void import_data(string image_location, string label_location) {
		fstream image_file;
		image_file.open(image_location, ios::in | ios::binary);
		if (image_file.fail())
		{
			cout << "Unable to load " << image_location << " " << endl;
			return;
		}
		char temp[50000000];
		image_file.read(temp, 4);
		magic_number = (unsigned char)temp[3] | ((unsigned char)temp[2] << 8) | ((unsigned char)temp[1] << 16) | ((unsigned char)temp[0] << 24);
		//cout << magic_number << endl;
		if (magic_number != expected_image_magic_number) {
			cout << "Magic number should be " << expected_image_magic_number << ", while read " << magic_number << "." << endl;
			cout << "Please check if the imput file is correct." << endl;
		}
		image_file.read(temp, 4);
		image_count = (unsigned char)temp[3] | ((unsigned char)temp[2] << 8) | ((unsigned char)temp[1] << 16) | ((unsigned char)temp[0] << 24);
		//cout << image_count << endl;
		image_file.read(temp, 4);
		image_height = (unsigned char)temp[3] | ((unsigned char)temp[2] << 8) | ((unsigned char)temp[1] << 16) | ((unsigned char)temp[0] << 24);
		//cout << image_height << endl;
		image_file.read(temp, 4);
		image_width = (unsigned char)temp[3] | ((unsigned char)temp[2] << 8) | ((unsigned char)temp[1] << 16) | ((unsigned char)temp[0] << 24);
		//cout << image_width << endl;
		image_file.read(temp, image_count*image_height*image_width);
		int tempi = 0;
		for (int i = 0; i < image_count; i++) {
			for (int j = 0; j < image_height; j++) {
				for (int k = 0; k < image_width; k++) {
					images[i].p[j][k] = temp[tempi];
					tempi++;
				}
			}
		}
		cout << "Completed loading images." << endl;
		fstream label_file;
		label_file.open(label_location, ios::in | ios::binary);
		if (label_file.fail())
		{
			cout << "Unable to load " << label_location << " " << endl;
			return;
		}
		label_file.read(temp, 4);
		magic_number = (unsigned char)temp[3] | ((unsigned char)temp[2] << 8) | ((unsigned char)temp[1] << 16) | ((unsigned char)temp[0] << 24);
		//cout << magic_number << endl;
		if (magic_number != expected_label_magic_number) {
			cout << "Magic number should be " << expected_label_magic_number << ", while read " << magic_number << "." << endl;
			cout << "Please check if the imput file is correct." << endl;
		}
		label_file.read(temp, 4);
		label_file.read(temp, image_count);
		for (int i = 0; i < image_count; i++) {
			images[i].label = temp[i];
		}
		cout << "Completed loading labels." << endl;
		data_loaded = true;
		return;
	}
	void display_image(int index) {
		if (!data_loaded) {
			cout << "Image data not loaded." << endl;
			return;
		}
		cout << "Label:" << endl << images[index].label << endl;
		for (int i = 0; i < image_height; i++) {
			for (int j = 0; j < image_width; j++) {
				printf("%4d ", (int)images[index].p[i][j]);
			}
			cout << endl;
		}
		return;
	}
};