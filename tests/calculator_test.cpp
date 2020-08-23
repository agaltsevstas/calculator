#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE CalculatorTest

#include <iostream>
#include <fstream>

#include <boost/test/unit_test.hpp>

#include "calculator.h"

#define Impl(Class) Class##Impl

#define DerivedClass(Name) \
class Impl(Name) :  public Name \
{   \
    public: \
        Impl(Name)() : \
            Name() {} \
        ~Impl(Name)() {} \
    using Name::addition; \
    using Name::subtraction; \
    using Name::multiplication; \
    using Name::division; \
    using Name::operations; \
    using Name::readBuffer; \
}

#define WRAP(s) (std::string(boost::core::demangle(typeid(*this).name())) + "::" + std::string(__FUNCTION__) + "(): " + (s))
#define PRINT(s) std::cout << (s) << std::endl

using namespace boost;
using namespace boost::unit_test;

DerivedClass(Calculator);

struct CalculatorFixture
{
    CalculatorFixture()
    {
        std::cout << "-----------------------" << std::endl;
        std::cout << "START" << std::endl;
        calculator = new (Impl(Calculator))();
    }

    ~CalculatorFixture()
    {
        delete calculator;
    }

    Impl(Calculator) *calculator = nullptr;
    std::string buffer;
};

struct LogToFile
{
    LogToFile()
    {
        logFile.open(logFileName.c_str(), std::ios_base::out);
        unit_test_log.set_stream(logFile);
        unit_test_log.set_threshold_level(log_all_errors);
//        unit_test_log.set_format(OF_CLF);
    }

    ~LogToFile()
    {
        unit_test_log.test_finish();
        logFile.close();
        logFile.open(logFileName, std::ios_base::in);
        std::stringstream strStream;
        strStream << logFile.rdbuf();
        std::cout << strStream.str() << std::endl;
    }

    std::string logFileName = "errors.txt";
    std::fstream logFile;
};

BOOST_GLOBAL_FIXTURE(LogToFile);

BOOST_AUTO_TEST_SUITE(CalculatorTest)

BOOST_FIXTURE_TEST_CASE(isNumberOne, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->isNumber("0.001"), 0);
}

BOOST_FIXTURE_TEST_CASE(isNumberTwo, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->isNumber("0.004"), 0.0);
}

BOOST_FIXTURE_TEST_CASE(isNumberThree, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->isNumber("0.005"), 0.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(isNumberFour, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->isNumber("0.01"), 0.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(isNumberFive, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->isNumber("-0.001"), 0.0);
}

BOOST_FIXTURE_TEST_CASE(isNumberSix, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->isNumber("-0.004"), 0.0);
}

BOOST_FIXTURE_TEST_CASE(isNumberSeven, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->isNumber("-0.005"), -0.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(isNumberEight, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->isNumber("-0.01"), -0.01, 0.001);
}


BOOST_FIXTURE_TEST_CASE(additionOne, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->addition({1, 2}), 3);
}

BOOST_FIXTURE_TEST_CASE(additionTwo, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->addition({-1, 2}), 1);
}

BOOST_FIXTURE_TEST_CASE(additionThree, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->addition({1, -2}), -1);
}

BOOST_FIXTURE_TEST_CASE(additionFour, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->addition({-1, -2}), -3);
}

BOOST_FIXTURE_TEST_CASE(additionFive, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->addition({1, 0.01}), 1.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(additionSix, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->addition({-1, 0.01}), -0.99, 0.001);
}

BOOST_FIXTURE_TEST_CASE(additionSeven, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->addition({1, -0.01}), 0.99, 0.001);
}

BOOST_FIXTURE_TEST_CASE(additionEight, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->addition({-1, -0.01}), -1.01, 0.001);
}


BOOST_FIXTURE_TEST_CASE(subtractionOne, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->subtraction({1, 2}), -1);
}

BOOST_FIXTURE_TEST_CASE(subtractionTwo, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->subtraction({2, 1}), 1);
}

BOOST_FIXTURE_TEST_CASE(subtractionThree, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->subtraction({-1, 2}), -3);
}

BOOST_FIXTURE_TEST_CASE(subtractionFour, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->subtraction({2, -1}), 3);
}

BOOST_FIXTURE_TEST_CASE(subtractionFive, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->subtraction({1, -2}), 3);
}

BOOST_FIXTURE_TEST_CASE(subtractionSix, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->subtraction({-2, 1}), -3);
}

BOOST_FIXTURE_TEST_CASE(subtractionSeven, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->subtraction({-1, -2}), 1);
}

BOOST_FIXTURE_TEST_CASE(subtractionEight, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->subtraction({-2, -1}), -1);
}

BOOST_FIXTURE_TEST_CASE(subtractionNine, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->subtraction({1, 0.01}), 0.99, 0.001);
}

BOOST_FIXTURE_TEST_CASE(subtractionTen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->subtraction({-1, 0.01}), -1.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(subtractionEleven, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->subtraction({-0.01, 1}), -1.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(subtractionTwelve, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->subtraction({1, -0.01}), 1.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(subtractionThirteen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->subtraction({0.01, -1}), 1.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(subtractionFourteen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->subtraction({-1, -0.01}), -0.99, 0.001);
}


BOOST_FIXTURE_TEST_CASE(multiplicationOne, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->multiplication({1, 2}), 2);
}

BOOST_FIXTURE_TEST_CASE(multiplicationTwo, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->multiplication({-1, 2}), -2);
}

BOOST_FIXTURE_TEST_CASE(multiplicationThree, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->multiplication({1, -2}), -2);
}

BOOST_FIXTURE_TEST_CASE(multiplicationFour, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->multiplication({-1, -2}), 2);
}

BOOST_FIXTURE_TEST_CASE(multiplicationFive, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->multiplication({1, 0.01}), 0.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(multiplicationSix, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->multiplication({-1, 0.01}), -0.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(multiplicationSeven, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->multiplication({1, -0.01}), -0.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(multiplicationEight, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->multiplication({-1, -0.01}), 0.01, 0.001);
}


BOOST_FIXTURE_TEST_CASE(divisionOne, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({1, 2}), 0.5);
}

BOOST_FIXTURE_TEST_CASE(divisionTwo, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({2, 1}), 2);
}

BOOST_FIXTURE_TEST_CASE(divisionThree, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({-1, 2}), -0.5);
}

BOOST_FIXTURE_TEST_CASE(divisionFour, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({2, -1}), -2);
}

BOOST_FIXTURE_TEST_CASE(divisionFive, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({1, -2}), -0.5);
}

BOOST_FIXTURE_TEST_CASE(divisionSix, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({-2, 1}), -2);
}

BOOST_FIXTURE_TEST_CASE(divisionSeven, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({-1, -2}), 0.5);
}

BOOST_FIXTURE_TEST_CASE(divisionEight, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({-2, -1}), 2);
}

BOOST_FIXTURE_TEST_CASE(divisionNine, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({1, 0.01}), 100);
}

BOOST_FIXTURE_TEST_CASE(divisionTen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({-1, 0.01}), -100);
}

BOOST_FIXTURE_TEST_CASE(divisionEleven, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->division({-0.01, 1}), -0.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(divisionTwelve, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({1, -0.01}), -100);
}

BOOST_FIXTURE_TEST_CASE(divisionThirteen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_CLOSE_FRACTION(calculator->division({0.01, -1}), -0.01, 0.001);
}

BOOST_FIXTURE_TEST_CASE(divisionFourteen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    BOOST_CHECK_EQUAL(calculator->division({-1, -0.01}), 100);
}


BOOST_FIXTURE_TEST_CASE(calculationOne, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "1";
    BOOST_CHECK_EQUAL(calculator->calculation(buffer), 1);
}

BOOST_FIXTURE_TEST_CASE(calculationTwo, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "+1";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationThree, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "-1";
    BOOST_CHECK_EQUAL(calculator->calculation(buffer), -1);
}

BOOST_FIXTURE_TEST_CASE(calculationFour, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "1/";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationFive, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "/1";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationSix, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "1//";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationSeven, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "1+-1";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationEight, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "(1)";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationNine, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "(-1)";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationTen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "(+1)";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationEleven, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "+(1)";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationTwelve, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "-(1)";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationThirteen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "(1+2)";
    BOOST_CHECK_EQUAL(calculator->calculation(buffer), 3);
}

BOOST_FIXTURE_TEST_CASE(calculationFourteen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "(1+2";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationFifteen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "1+2)";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationSixteen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "(2+1)+1";
    BOOST_CHECK_EQUAL(calculator->calculation(buffer), 4);
}

BOOST_FIXTURE_TEST_CASE(calculationSeventeen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "((2+1)+1";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationEighteen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "((2+1)+1)";
    BOOST_CHECK_EQUAL(calculator->calculation(buffer), 4);
}

BOOST_FIXTURE_TEST_CASE(calculationNineteen, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "+((1-2)+2)";
    BOOST_CHECK_THROW(calculator->calculation(buffer), std::exception);
}

BOOST_FIXTURE_TEST_CASE(calculationTwenty, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "-((1-2)+2)";
    BOOST_CHECK_EQUAL(calculator->calculation(buffer), -1);
}

BOOST_FIXTURE_TEST_CASE(calculationTwentyOne, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "-1 + 5 - 3";
    BOOST_CHECK_EQUAL(calculator->calculation(buffer), 1);
}

BOOST_FIXTURE_TEST_CASE(calculationTwentyTwo, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "-10 + (8 * 2.5) - (3 / 1,5)";
    BOOST_CHECK_EQUAL(calculator->calculation(buffer), 8);
}

BOOST_FIXTURE_TEST_CASE(calculationTwentyThree, CalculatorFixture)
{
    PRINT(WRAP("..."));

    buffer = "1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)";
    BOOST_CHECK_EQUAL(calculator->calculation(buffer), 11);
}

BOOST_AUTO_TEST_SUITE_END()
