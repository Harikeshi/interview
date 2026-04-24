#pragma once

#include <ThreadsLib/BaseGenerator.hpp>

class PrimeNumberGenerator final : public BaseGenerator
{
public:
    explicit PrimeNumberGenerator(int limits);

    void SetLimit(int number) override;
    int Next() override;

    static bool isPrime(int n);

private:
    int current;
    int limit;
};