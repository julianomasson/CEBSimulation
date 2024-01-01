#pragma once
#include <chrono>
#include "Sensor.h"

#include "Error.h"

class SensorTemperatura : public Sensor {
private:
    double value = 25.5;
    Error* error;

public:
    SensorTemperatura(unsigned int sensorId, Error* error = nullptr) : Sensor(sensorId), error(error){}

    std::string read() override 
    {
        //auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
        std::string message;
        //message += std::format("%d_", id);
        //message += std::format("{:%Y-%m-%d_%X}", time);
        message += "_";
        message += id;
        message += "_";
        if (error)
        {
            message += std::to_string(error->compute(value));
        }
        else
        {
            message += std::to_string(value);
        }
        return message;
    }
};