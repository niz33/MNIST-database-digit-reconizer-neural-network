#pragma once
#include<iostream>
#include<vector>
#include<time.h>
using namespace std;

struct neuron {
	double activation_value;
	vector <double> weight;
};
class layer {
public:
	int neuron_count = -1, last_layer_neuron_count = -1, index;
	double bias;
	vector <neuron> neurons;
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
		neuron temp;
		for (int i = 1; i <= neuron_count; i++) {
			for (int i = 1; i <= last_layer_neuron_count; i++) {
				temp.weight.push_back((double)rand() / RAND_MAX);
			}
			neurons.push_back(temp);
		}
	}
};

class activation_functions {

public:
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

	}
};