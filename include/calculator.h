#ifndef calculator_hpp
#define calculator_hpp

#include <iostream>
#include <sstream>
#include <map>
#include <cmath>
#include <stdexcept>

class Calculator
{
public:
    Calculator() {}
    float isNumber(const std::string &number);
    float calculation(std::string &buffer);
    
protected:
    float addition(const std::pair<float, float> &numbers);
    float subtraction(const std::pair<float, float> &numbers);
    float multiplication(const std::pair<float, float> &numbers);
    float division(const std::pair<float, float> &numbers);
    float operations(const std::pair<std::string, std::string> &numbers, const char operation);
    float readBuffer(std::string &buffer);
    
private:
    int recursionCounter_ = 0;
    float result_ = 0.0;
    std::string buffer_;
};

#endif /* calculator_h */
