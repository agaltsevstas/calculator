#include "calculator.h"

int main(int argc, const char * argv[])
{
    std::string str;
    Calculator calculator;
    while (true)
    {
        try
        {
            std::cout << "Входное выражение: ";
            getline(std::cin, str);
            std::cout << "Результат:​ " << calculator.calculation(str) << std::endl;
        }
        catch (const std::exception &exception)
        {
            std::cout << "некорректный​​ ввод,​​ строка​​ содержит​​ недопустимое​​ выражение​​ "
                      << exception.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "некорректный ввод" << std::endl;
        }
    }
    return 0;
}
