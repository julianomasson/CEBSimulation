#pragma once
#include <cstdlib>

class Error {
protected:
    unsigned int id;
    float rate;

public:
    Error(unsigned int errorId, float rate) : id(errorId), rate(rate) {}

    virtual bool check()
    {
        return (std::rand() / static_cast<double>(RAND_MAX) <= rate);
    }

    virtual float compute(float value) = 0;

};