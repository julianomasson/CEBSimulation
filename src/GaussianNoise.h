#pragma once
#include <random>

#include "Error.h"

class GaussianNoise : public Error{
protected:
    float mean;
    float stdDev;
    std::default_random_engine generator;

public:
    GaussianNoise(unsigned int id, float rate, float mean, float stdDev) : Error(id, rate), mean(mean), stdDev(stdDev) {};

    float compute(float value) override
    {
        if (!check())
        {
            return value;
        }
        std::normal_distribution<float> dist(mean, stdDev);
        return value + dist(generator);
    }
};