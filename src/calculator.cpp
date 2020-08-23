#include "calculator.h"

float Calculator::calculation(std::string &buffer)
{
    result_ = readBuffer(buffer);
    result_ == 0 ? result_ = 0 : result_;
    return  round(result_ * 100) / 100;
}

float Calculator::addition(const std::pair<float, float> &numbers)
{
    return numbers.first + numbers.second;
}

float Calculator::subtraction(const std::pair<float, float> &numbers)
{
    return numbers.first - numbers.second;
}

float Calculator::multiplication(const std::pair<float, float> &numbers)
{
    return numbers.first * numbers.second;
}

float Calculator::division(const std::pair<float, float> &numbers)
{
    const float divisor = numbers.second;
    if (divisor == 0)
        throw std::invalid_argument("некорректный ввод, делитель не может быть 0");
    return numbers.first / numbers.second;
}

float Calculator::isNumber(const std::string &number)
{
    return round(std::stof(number) * 100) / 100;
}

float Calculator::operations(const std::pair<std::string, std::string> &numbersString, const char operation)
{
    float fisrtNumber = isNumber(numbersString.first);
    float secondNumber = isNumber(numbersString.second);
    switch (operation)
    {
        case '+':
            return addition({fisrtNumber, secondNumber});
            
        case '-':
            return subtraction({fisrtNumber, secondNumber});
            
        case '*':
            return multiplication({fisrtNumber, secondNumber});
            
        case '/':
            return division({fisrtNumber, secondNumber});
            
        default:
            throw operation;
    }
    return 0;
}

float Calculator::readBuffer(std::string &buffer)
{
    std::string first, second;
    std::string input;
    char operation = '\0';
    float result = 0.0;
    int size = static_cast<int>(buffer.size()) - 1;
    for (int i = 0; i <= size; ++i)
    {
        char c = buffer[i];
        if (c == ' ')
        {
            continue;
        }
        else if (c == '-' && i == 0)
        {
            input += c;
        }
        else if (isdigit(c))
        {
            input += c;
        }
        else if (c == '.' || c == ',')
        {
            input += '.';
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (operation == '\0')
            {
                first = input;
                input.clear();
            }
            else
            {
                if (input.empty())
                {
                    throw std::invalid_argument(std::to_string(c));
                }
                second = input;
                result = operations({first, second}, operation);
                first = std::to_string(result);
                second.clear();
                input.clear();
            }
            operation = c;
        }
        else if (c == '(')
        {
            ++recursionCounter_;
            buffer = buffer.substr(i + 1);
            input += std::to_string(readBuffer(buffer));
            --recursionCounter_;
            i = -1;
            size = static_cast<int>(buffer.size());
        }
        else if (c == ')')
        {
            if (recursionCounter_ == 0)
            {
                throw std::invalid_argument(")");
            }
            second = input;
            buffer = buffer.substr(i + 1);
            return operations({first, second}, operation);
        }
        else if (c != '\0')
        {
            throw std::invalid_argument(std::to_string(c));
        }
        if (i == size)
        {
            second = input;
            if (first.empty() || second.empty())
            {
                if (operation != '\0')
                {
                    throw std::invalid_argument(std::to_string(operation));
                }
                result = std::stof(input);
            }
            else
            {
                result = operations({first, second}, operation);
            }
        }
    }
    if (recursionCounter_ != 0)
    {
        throw std::invalid_argument("(");
    }
    return result;
}


