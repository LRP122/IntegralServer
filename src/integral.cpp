#pragma once
#include <iostream>
#include <cmath>
#include <memory>
#include "functions.h"

class Integral{
public:

    float integral_solution(std::unique_ptr<Function> function_pointer,
                            float lower_bound, float upper_bound){

    int steps = 100000;
    float stepsize = 1.0f*(upper_bound-lower_bound) / steps;
    float solution = 0.0;

    for(int i = 0; i < steps; i++){
        solution += (stepsize * (function_pointer->function(lower_bound + stepsize*i)));
    }
    return solution;
    }
};

float integral_calculations(float lower_bound, float upper_bound, int choosen_number){

    std::unique_ptr<Function> function_pointer = std::make_unique<quadratic_function>();
    std::unique_ptr<Function> exponential_ptr = std::make_unique<exponential_function>();
    std::unique_ptr<Function> gaussian_ptr = std::make_unique<gaussian_function>();
    std::unique_ptr<Integral> integral_ptr = std::make_unique<Integral>();

    switch(choosen_number){
        case 1:
            {
            float integral_result = integral_ptr->integral_solution(std::move(function_pointer),lower_bound,upper_bound);
            //std::cout << "Solution of quadratic integral is " << integral_result << "\n";
            return integral_result;
            break;
            }
        case 2:
            {
            float integral_result = integral_ptr->integral_solution(std::move(exponential_ptr),lower_bound,upper_bound);
            //std::cout << "Solution of exponential integral is  " << integral_result << "\n";
            return integral_result;
            break;
            }
        case 3:
            {
            float integral_result = integral_ptr->integral_solution(std::move(gaussian_ptr),lower_bound,upper_bound);
            //std::cout << "Solution of gaussian integral is " << integral_result << "\n";
            return integral_result;
            break;
            } 
    }

    return 0.0;

    }