#pragma once
#include "Error.h"

class SimpleError : public Error {
public:
    SimpleError(unsigned int id, float rate) : Error(id, rate) {};

    float compute(float value) override
    {
        return value;
    }
};