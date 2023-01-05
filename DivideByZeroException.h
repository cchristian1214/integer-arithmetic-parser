/*
    The following class definition
    defines a User-Defined exception
    for handling division by zero
    in the calculator.
*/
#include <iostream>

class DivideByZeroException
{
public:
    DivideByZeroException()
    {
        std::runtime_error("ERROR: Division by zero!");
    }
};