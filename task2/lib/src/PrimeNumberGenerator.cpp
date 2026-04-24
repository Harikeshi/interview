#include <ThreadsLib/PrimeNumberGenerator.hpp>

#include <cmath>

PrimeNumberGenerator::PrimeNumberGenerator(const int limits) : current(0), limit(limits)
{
}

void PrimeNumberGenerator::SetLimit(const int number)
{
    limit = number;
}

int PrimeNumberGenerator::Next()
{
    while (true)
    {
        current++;
        if (current > limit)
            return -1;

        if (isPrime(current))
            return current;
    }
}

bool PrimeNumberGenerator::isPrime(const int n)
{
    if (n == 1)
        return false;

    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}