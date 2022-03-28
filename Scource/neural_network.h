#pragma once
#include<iostream>
#include<vector>
#include<time.h>
#include<cmath>
#include"file_reader.h"
using namespace std;

class layer {
public:
	int neuron_count = -1, last_layer_neuron_count = -1, index;
	long double weight[1001][1001], bias[1001], a[1001], z[1001];
	long double d_weight[1001][1001], d_bias[1001], d_a[1001], d_z[1001];
	void initialize() {
		srand(time(0) * index);
		if (!neuron_count) {
			cout << "invalid neuron_count value" << endl;
			return;
		}
		if (!last_layer_neuron_count) {
			cout << "invalid last_layer_neuron_count value" << endl;
			return;
		}
		for (int i = 0; i < last_layer_neuron_count; i++) {
			for (int j = 0; j < neuron_count; j++) {
				weight[i][j] = (long double)rand() / RAND_MAX * 2 - 1;
			}
			bias[i] = (long double)rand() / RAND_MAX * 2 - 1;
		}
		return;
	}
};

long double ReLU(long double x) {
	return max((long double)0.0, x);
}
long double ReLU_derivative(long double x) {
	if (x < 0) {
		return 0;
	}
	return 1;
}
long double sigmoid(long double x) {
	return (1.0 / (1.0 + pow(exp(1), 0 - x)));
}
long double sigmoid_derivative(long double x) {
	return sigmoid(x) * (1.0 - sigmoid(x));
}
long double activate(long double x, int type) {
	return 0;
}

class neural_network {
public:
	int layer_count = -1, hidden_layer_count = -1;
	bool initialized = false, initialized_layers = false;
	long double accuracy = 0, cost = 0;
	vector <layer> layers;
	void initialize() {
		if (!layer_count) {
			cout << "invalid layer_count value" << endl;
			return;
		}
		if (hidden_layer_count != layer_count - 2) {
			hidden_layer_count = layer_count - 2;
			cout << "hidden_layer_count set set to " << hidden_layer_count << endl;
		}
		layer temp;
		for (int i = 1; i <= layer_count; i++) {
			layers.push_back(temp);
		}
		initialized = true;
		return;
	}
	void initialize_layers() {
		for (int i = 1; i < layer_count; i++) {
			layers[i].index = i;
			layers[i].last_layer_neuron_count = layers[i - 1].neuron_count;
			layers[i].initialize();
		}
		initialized_layers = true;
		return;
	}
	void cal(image &im) {
		if (!initialized) {
			cout << "Network uninitialized." << endl;
			return;
		}
		if (!initialized_layers) {
			cout << "Network layers uninitialized." << endl;
			return;
		}
		for (int i = 0; i < 28; i++) {
			for (int j = 0; j < 28; j++) {
				layers[0].a[i * 28 + j] = (long double)im.p[i][j];
			}
		}
		for (int i = 1; i < layer_count; i++) {
			for (int j = 0; j < layers[i].neuron_count; j++) {
				layers[i].a[j] = 0;
				layers[i].z[j] = 0;
				for (int k = 0; k < layers[i].last_layer_neuron_count; k++) {
					layers[i].z[j] += layers[i - 1].a[k] * layers[i].weight[k][j];
				}
				layers[i].z[j] += layers[i].bias[j];
				layers[i].a[j] = sigmoid(layers[i].z[j]);
			}
		}
		cost = 0;
		for (int i = 0; i < layers[layer_count - 1].neuron_count; i++) {
			if (i == im.label) {
				cost += pow(1 - layers[layer_count - 1].a[i], 2);
			}
			else {
				cost += pow(layers[layer_count - 1].a[i], 2);
			}
			//cout << layers[layer_count - 1].a[i] << " ";	
		}
		//cout << endl << cost << endl << im.label << endl;
		//for (int i = 0; i < layer_count; i++) {
		//	cout << layers[i].a[0] << " ";
		//}cout << endl;
		return;
	}
	void update_accuracy(image_dataset &test_data) {
		if (!initialized) {
			cout << "Network uninitialized." << endl;
			return;
		}
		if (!initialized_layers) {
			cout << "Network layers uninitialized." << endl;
			return;
		}
		long double max_v;
		int max_n = 0, accurate_count = 0;
		for (int i = 0; i < test_data.image_count; i++) {
			cal(test_data.images[i]);
			max_v = -1;
			for (int j = 0; j < layers[layer_count - 1].neuron_count; j++) {
				if (layers[layer_count - 1].a[j] > max_v) {
					max_v = layers[layer_count - 1].a[j];
					max_n = j;
				}
			}
			if (max_n == test_data.images[i].label) {
				accurate_count++;
			}
		}
		accuracy = (long double)accurate_count / (long double)test_data.image_count;
		

	}
	void back_prop(image_dataset train_data, long double descent_rate) {
		if (!initialized) {
			cout << "Network uninitialized." << endl;
			return;
		}
		if (!initialized_layers) {
			cout << "Network layers uninitialized." << endl;
			return;
		}
		for (int i = 1; i < layer_count; i++) {
			for (int j = 0; j < layers[i].neuron_count; j++) {
				layers[i].d_a[j] = 0;
				layers[i].d_z[j] = 0;
				layers[i].d_bias[j] = 0;
				for (int k = 0; k < layers[i].last_layer_neuron_count; k++) {
					layers[i].d_weight[k][j] = 0;
				}
			}
		}
		for (int i = 0; i < train_data.image_count; i++) {
			cal(train_data.images[i]);
			for (int j = 0; j < layer_count; j++) {
				for (int k = 0; k < layers[j].neuron_count; k++) {
					layers[j].d_a[k] = 0;
				}
			}
			for (int j = 0; j < layers[layer_count - 1].neuron_count; j++) {
				if (j == train_data.images[i].label) {
					layers[layer_count - 1].d_a[j] = 2.0 * (layers[layer_count - 1].a[j] - 1);
				}
				else {
					layers[layer_count - 1].d_a[j] = 2.0 * layers[layer_count - 1].a[j];
				}
			}
			for (int j = layer_count - 1; j >= 1; j--) {
				for (int k = 0; k < layers[j].neuron_count; k++) {
					layers[j].d_z[k] = sigmoid_derivative(layers[j].z[k]) * layers[j].d_a[k];
					layers[j].d_bias[k] += layers[j].d_z[k];
					for (int l = 0; l < layers[j].last_layer_neuron_count; l++) {
						layers[j].d_weight[l][k] += layers[j].d_z[k] * layers[j - 1].a[l];
						layers[j - 1].d_a[l] += layers[j].d_z[k] * layers[j].weight[l][k];
						
					}
				}
			}
		}
		for (int i = 1; i < layer_count; i++) {
			for (int j = 0; j < layers[i].neuron_count; j++) {
				layers[i].bias[j] -= layers[i].d_bias[j] * descent_rate / train_data.image_count;
				for (int k = 0; k < layers[i].last_layer_neuron_count; k++) {
					layers[i].weight[k][j] -= layers[i].d_weight[k][j] * descent_rate / train_data.image_count;
				}
			}
		}
		return;
	}
	void display_network() {
		if (!initialized) {
			cout << "Network uninitialized." << endl;
			return;
		}
		if (!initialized_layers) {
			cout << "Network layers uninitialized." << endl;
			return;
		}
		for (int i = 2; i < layer_count; i++) {
			cout << "layer " << i << ":" << endl;
			cout << "neuron_count: " << layers[i].neuron_count << endl;
			for (int j = 0; j < layers[i].neuron_count; j++) {
				cout << "neuron " << j << ":" << layers[i].z[j] << " " << layers[i].a[j] << endl;
				cout << "bias :" << layers[i].bias[j] << endl;
				cout << "weights :";
				for (int k = 0; k < layers[i].last_layer_neuron_count; k++) {
					cout << layers[i].weight[k][j] << " ";
				}
				cout << endl;
			}
		}
		return;
	}
};