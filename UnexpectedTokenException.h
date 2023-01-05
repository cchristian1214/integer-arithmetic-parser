/*
    The following class definition
    defines a User-Defined exception
    for handling unexpected input tokens
    in the calculator.
*/
#include <iostream>

class UnexpectedTokenException
{
public:
    UnexpectedTokenException()
    {
        std::runtime_error("ERROR: Unexpected Token Encountered!");
    }
};