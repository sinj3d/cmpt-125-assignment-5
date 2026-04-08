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

#pragma once
#include <vector>
#include <string>

class NeuralNet {
private:
    // Sizes
    const int INPUT_SIZE = 44;
    const int HIDDEN1_SIZE = 64;
    const int HIDDEN2_SIZE = 64;
    const int OUTPUT_SIZE = 14;

    // Weights and biases
    std::vector<float> fc1_weight; // size: 64 * 44
    std::vector<float> fc1_bias;   // size: 64
    std::vector<float> fc2_weight; // size: 64 * 64
    std::vector<float> fc2_bias;   // size: 64
    std::vector<float> fc3_weight; // size: 14 * 64
    std::vector<float> fc3_bias;   // size: 14
    
    bool isLoaded = false;
    
    float relu(float x);

public:
    NeuralNet();
    
    // Loads the model weights exported from PyTorch
    bool loadWeights(const std::string& filename);
    
    // Given the 44 input features, returns 14 probabilities (raw scores)
    std::vector<float> predict(const std::vector<float>& input);
    
    bool getIsLoaded() const { return isLoaded; }
};
