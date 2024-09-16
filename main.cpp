#include <iostream>
#include <cmath>
#include <memory>
#include "functions.h"

class Integral{
public:

    float integral_solution(std::unique_ptr<Function> function_pointer,
                            float lower_bound, float upper_bound){

    int steps = 1000;
    float stepsize = 1.0f*(upper_bound-lower_bound) / steps;
    float solution = 0.0;

    for(int i = 0; i < steps; i++){
        solution += (stepsize * (function_pointer->function(lower_bound + stepsize*i)));
    }
    return solution;
    }
};

int main(int argc,char** argv){
    std::unique_ptr<Function> function_pointer = std::make_unique<quadratic_function>();
    std::unique_ptr<Function> exponential_ptr = std::make_unique<exponential_function>();
    std::unique_ptr<Function> gaussian_ptr = std::make_unique<gaussian_function>();
    std::unique_ptr<Integral> integral_ptr = std::make_unique<Integral>();

    float y = integral_ptr->integral_solution(std::move(function_pointer),-2.43,3.0);
    std::cout << "Ergebnis des quadratischen Integrals ist  " << y << "\n";
    float y2 = integral_ptr->integral_solution(std::move(exponential_ptr),-0,2);
    std::cout << "Ergebnis des exponentiellen Integrals ist  " << y2 << "\n";
    float y3 = integral_ptr->integral_solution(std::move(gaussian_ptr),0,1);
    std::cout << "Ergebniss des gaussian Integrals ist " << y3 << "\n"; 
    return 0;
    }