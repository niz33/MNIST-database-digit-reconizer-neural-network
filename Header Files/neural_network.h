#pragma once
#include<iostream>
#include<vector>
#include<time.h>
using namespace std;

class layer {
public:
	int neuron_count = -1, last_layer_neuron_count = -1, index;
	double weight[101][101],bias,a[101];
	void initialize() {
		srand(time(0));
		if (!neuron_count) {
			cout << "invalid neuron_count value" << endl;
			return;
		}
		if (!last_layer_neuron_count) {
			cout << "invalid last_layer_neuron_count value" << endl;
			return;
		}
		bias = (double)rand() / RAND_MAX;
		for (int i = 1; i <= last_layer_neuron_count; i++) {
			for (int j = 1; j <= neuron_count; j++) {
				weight[i][j] = (double)rand() / RAND_MAX;
			}
		}
	}
};

double ReLU(double x) {

}
double sigmoid(double x) {

}
double sigmoid_differential(double x) {

}
double activate(double x, int type) {

}

};

class neural_network {
public:
	int layer_count = -1, hidden_layer_count = -1;
	vector <layer> layers;
	void initialize() {
		if (!layer_count) {
			cout << "invalid layer_count value" << endl;
			return;
		}
		if (hidden_layer_count != layer_count - 2) {
			hidden_layer_count -= 2;
			cout << "hidden_layer_count set changed to " << hidden_layer_count << endl;
		}
		layer temp;
		for (int i = 1; i <= layer_count; i++) {
			layers.push_back(temp);
		}
	}
	void initialize_layers() {
		for (int i = 0; i < layer_count; i++) {
			layers[i].index = i;
			layers[i].initialize();
		}
	}
	void cal() {
		for (int i = 1; i < layer_count; i++) {
			for (int j = 1; j <= layers[i].neuron_count; j++) {
				layers[i].a[j] = 0;
				for (int k = 1; k <= layers[i].last_layer_neuron_count; k++) {
					layers[i].a[j] += layers[i - 1].a[k] * layers[i].weight[k][j];
				}
				layers[i].a[j] = sigmoid(layers[i].a[j] + layers[i].bias);
			}
		}
	}
};