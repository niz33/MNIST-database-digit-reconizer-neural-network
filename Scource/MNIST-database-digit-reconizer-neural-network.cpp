// MNIST database digit reconizer neural network.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "neural_network.h"

int main()
{
   // std::cout << "Hello World!\n";
    neural_network n, best;
    //cout << exp(1) << endl;
    //why is this not updating???
    image_dataset train_data;
    train_data.import_data("F:\\Administrator\\source\\repos\\MNIST-database-digit-reconizer-neural-network\\Scource\\Resource Files\\train-images.data", 
        "F:\\Administrator\\source\\repos\\MNIST-database-digit-reconizer-neural-network\\Scource\\Resource Files\\train-labels.data");
    image_dataset test_data;
    test_data.import_data("F:\\Administrator\\source\\repos\\MNIST-database-digit-reconizer-neural-network\\Scource\\Resource Files\\test-images.data",
        "F:\\Administrator\\source\\repos\\MNIST-database-digit-reconizer-neural-network\\Scource\\Resource Files\\test-labels.data");
    //test_data.display_image(100);
    n.layer_count = 4;
    n.initialize();
    n.layers[0].neuron_count = 28 * 28;
    n.layers[1].neuron_count = 16;
    n.layers[2].neuron_count = 16;
    n.layers[3].neuron_count = 10;
    n.initialize_layers();
    n.display_network();
    //cout << sigmoid_derivative(-1) << endl;
    n.cal(train_data.images[1]);
    image_dataset temp_test_data = test_data;
    temp_test_data.image_count = 100;
    n.update_accuracy(temp_test_data);
    image_dataset mini_batch[600];
    for (int i = 0; i < 60000; i++) {
        mini_batch[i % 600].images.push_back(train_data.images[i]);
    }
    long double best_accuracy=0;
    best = n;
    for (int epoch = 0; epoch < 10; epoch++) {
        for (int i = 0; i < 600; i++) {
            mini_batch[i].image_count = 100;
            n.back_prop(mini_batch[i], 3);
            n.update_accuracy(temp_test_data);
            if (n.accuracy > best_accuracy) {
                best = n;
                best_accuracy = n.accuracy;
                cout << i << ": Accuracy updated to " << n.accuracy << " while best accuracy is " << best_accuracy << endl;
                continue;
            }
            if (i % 10 == 0) {
                cout << i << ": Accuracy updated to " << n.accuracy << " while best accuracy is " << best_accuracy << endl;
            }
            //n.display_network();
        }
        n.update_accuracy(test_data);
        cout << "Accuracy updated to " << n.accuracy << endl;
    }
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file