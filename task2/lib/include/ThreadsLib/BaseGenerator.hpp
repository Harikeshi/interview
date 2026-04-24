#pragma once

class BaseGenerator
{
public:
    virtual int Next() = 0;
    virtual void SetLimit(int limit) = 0;
    virtual ~BaseGenerator() = default;
};
