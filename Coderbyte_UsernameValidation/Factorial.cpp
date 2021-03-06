#include "Factorial.h"

// Have the function FirstFactorial(num) take the num parameter being passed and 
// return the factorial of it. For example: if num = 4, then your program should 
// return (4 * 3 * 2 * 1) = 24. For the test cases, the range will be between 1 
// and 18 and the input will always be an integer.

long long Factorial::FirstFactorial(int num)
{
    long long result = 0UL;

    if (num == 0)
    {
        result = 1;
    }

    else
    {
        auto value = FirstFactorial(num - 1);
        result = (long long)num * value;
    }

    return result;
}
