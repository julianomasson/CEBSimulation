#include <thread>

#include "Fog.h"
#include "Edge.h"
#include "TemperatureSensor.h"
#include "SimpleError.h"
#include "GaussianNoise.h"

int main(int argc, char** argv)
{
    auto gaussianNoiseError = new GaussianNoise(8184945894894, 0.5, 100000, 50);
    auto tempSensor = new SensorTemperatura(44848, gaussianNoiseError);
    auto simpleError = new SimpleError(8184945894894, 0.005);
    

    auto edgeId = 518898483;
    auto fogId = 518898484;

    auto fog = new Fog(fogId, 2);
    
    auto numberOfEdges = 10;// std::atoi(argv[1]);
    for (unsigned int i = 0; i < numberOfEdges; i++)
    {
        edgeId += i;
        auto communication = new Communication(edgeId, fogId, 100000000, simpleError, fog, gaussianNoiseError);
        auto edge = new Edge(edgeId, 1, .005, communication);
        edge->addSensor(tempSensor);
        edge->startThread().detach();
    }
    auto threadFog = fog->startThread();
    threadFog.join();
}