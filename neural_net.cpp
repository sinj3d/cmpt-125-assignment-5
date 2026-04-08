/*
 * Names: Shenghua Jin, Luke Choi
 * SFU IDs: 301659564, 301658198
 * Emails: sja204@sfu.ca, esc9@sfu.ca
 *
 * Statement of Originality:
 * All the code and comments below are my (our) own original work. For any non-
 * original work, I (we) have provided citations above and in the comments with
 * enough detail so that someone can see the exact source and extent of the
 * borrowed work.
 *
 * In addition, I (we) have not shared this work with anyone else, and I (we) have
 * not seen solutions from other students, tutors, websites, books, etc.
 */

#include "neural_net.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

NeuralNet::NeuralNet() {}

float NeuralNet::relu(float x) {
    return x > 0 ? x : 0;
}

bool NeuralNet::loadWeights(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    string currentLayer = "";
    while (getline(file, line)) {
        if (line.substr(0, 3) == "---") {
            // Find the layer name inside --- name ---
            int start = line.find(" ") + 1;
            int end = line.rfind(" ") - 1;
            currentLayer = line.substr(start, end - start + 1);
        } else {
            stringstream ss(line);
            string valStr;
            vector<float>* targetVec = nullptr;

            if (currentLayer == "fc1.weight") targetVec = &fc1_weight;
            else if (currentLayer == "fc1.bias") targetVec = &fc1_bias;
            else if (currentLayer == "fc2.weight") targetVec = &fc2_weight;
            else if (currentLayer == "fc2.bias") targetVec = &fc2_bias;
            else if (currentLayer == "fc3.weight") targetVec = &fc3_weight;
            else if (currentLayer == "fc3.bias") targetVec = &fc3_bias;

            if (targetVec != nullptr) {
                while (getline(ss, valStr, ' ')) {
                    if (!valStr.empty()) {
                        targetVec->push_back(stof(valStr));
                    }
                }
            }
        }
    }
    
    // Verify sizes
    if (fc1_weight.size() != HIDDEN1_SIZE * INPUT_SIZE ||
        fc1_bias.size() != HIDDEN1_SIZE ||
        fc2_weight.size() != HIDDEN2_SIZE * HIDDEN1_SIZE ||
        fc2_bias.size() != HIDDEN2_SIZE ||
        fc3_weight.size() != OUTPUT_SIZE * HIDDEN2_SIZE ||
        fc3_bias.size() != OUTPUT_SIZE) {
        cerr << "Error: Loaded model dimensions do not match expected architecture." << endl;
        isLoaded = false;
        return false;
    }

    isLoaded = true;
    return true;
}

vector<float> NeuralNet::predict(const vector<float>& input) {
    if (!isLoaded || input.size() != INPUT_SIZE) {
        return vector<float>(OUTPUT_SIZE, 0.0f);
    }

    // Layer 1
    vector<float> h1(HIDDEN1_SIZE, 0.0f);
    for (int i = 0; i < HIDDEN1_SIZE; i++) {
        float sum = fc1_bias[i];
        for (int j = 0; j < INPUT_SIZE; j++) {
            sum += fc1_weight[i * INPUT_SIZE + j] * input[j];
        }
        h1[i] = relu(sum);
    }

    // Layer 2
    vector<float> h2(HIDDEN2_SIZE, 0.0f);
    for (int i = 0; i < HIDDEN2_SIZE; i++) {
        float sum = fc2_bias[i];
        for (int j = 0; j < HIDDEN1_SIZE; j++) {
            sum += fc2_weight[i * HIDDEN1_SIZE + j] * h1[j];
        }
        h2[i] = relu(sum);
    }

    // Layer 3 (Output - no ReLU)
    vector<float> output(OUTPUT_SIZE, 0.0f);
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        float sum = fc3_bias[i];
        for (int j = 0; j < HIDDEN2_SIZE; j++) {
            sum += fc3_weight[i * HIDDEN2_SIZE + j] * h2[j];
        }
        output[i] = sum;
    }

    return output;
}
