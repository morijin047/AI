//
// Created by Administrator on 8/31/2021.
//

#include "Perceptron.h"
Perceptron::Perceptron(int nbInputs) {
    for (int i = 0; i < nbInputs; i++) {
        double temp = 1 - 2 * rand() % 1;
        W.push_back(temp);
    }
    teta = 1 - 2 * rand() % 1;
}
double Perceptron::computeSum(std::vector<double > X) {
    double sum = 0;
    for (int i = 0; i < W.size(); i++) {
        sum += X[i] * W[i];
    }
    sum += teta;
    return sum;
}
double Perceptron::activationFunction(double x) {
    return x >= 0 ? 1 : -1;
}
double Perceptron::getOutPut(std::vector<double > X) {
    return activationFunction(computeSum(X));
}
bool Perceptron::learn(std::vector<double > X, double expected) {
    double output = getOutPut(X);

    if (output != expected) {
        for (int i = 0; i < W.size(); i++) {
            W[i] += (expected - output) * X[i];
        }
        teta += (expected - output);
    }
    return output == expected;
}
double Perceptron::getWx() const {
    return W[0];
}
double Perceptron::getWy() const {
    return W[1];
}
double Perceptron::getTeta() const {
    return teta;
}
