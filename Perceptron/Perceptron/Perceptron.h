//
// Created by Administrator on 8/31/2021.
//

#ifndef DEMOFIRSTSDL_PERCEPTRON_H
#define DEMOFIRSTSDL_PERCEPTRON_H
#include <vector>
#include <stdlib.h>
class Perceptron {
    std::vector<double> W;
    double teta;
public:
    Perceptron(int nbInputs);
    double computeSum(std::vector<double > X);
    double activationFunction(double x);
    double getOutPut(std::vector<double > X);
    bool learn(std::vector<double > X, double expected);
    double getWx() const;
    double getWy() const;
    double getTeta() const;
};
#endif //DEMOFIRSTSDL_PERCEPTRON_H
