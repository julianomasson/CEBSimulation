#pragma once
#include <string>

class Sensor {
protected:
    unsigned int id;

public:
    Sensor(unsigned int sensorId) : id(sensorId) {}

    virtual std::string read() = 0;
};