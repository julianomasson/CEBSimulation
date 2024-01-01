#pragma once
#include <iostream>
#include <chrono>
#include <vector>

#include "Sensor.h"
#include "Communication.h"
#include "Error.h"

class Edge {
private:
    unsigned int id;
    double samplingFreq;
    double sendingFreq;
    std::vector<Sensor*> sensors;
    std::string currentMessage = "";
    Communication* communication;
    std::vector<Error*> errors;

public:
    Edge(unsigned int id, double samplingFreq, double sendingFreq, Communication* communication)
        : id(id), samplingFreq(samplingFreq), sendingFreq(sendingFreq), communication(communication) {}

    ~Edge() {}

    void addSensor(Sensor* sensor)
    {
        sensors.emplace_back(sensor);
    }

    void addError(Error* error)
    {
        errors.emplace_back(error);
    }

    void readSensors() {
        // Verificar se ocorreu erro com base na taxa de erro
        for (const auto error : errors)
        {
            if (error->check())
            {
                return;
            }
        }
        for (const auto& sensor : sensors) {
            currentMessage += sensor->read() + ";";
        }
        std::cout << "[Edge] " << id << ": " << currentMessage << "\n";
    }

    void sendData() {
        // Call the communication
        communication->sendData(currentMessage);
        currentMessage = "";
    }

    void run() {
        std::chrono::milliseconds samplingInterval(static_cast<int>((1 / samplingFreq) * 1000));
        std::chrono::milliseconds sendingInterval(static_cast<int>((1 / sendingFreq) * 1000));
        
        auto samplingTimer = std::chrono::steady_clock::now();
        auto sendingTimer = std::chrono::steady_clock::now();

        while (true) {
            auto currentTimer = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTimer - samplingTimer) >= samplingInterval)
            {
                readSensors();
                samplingTimer = currentTimer;
            }

            if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTimer - sendingTimer) >= sendingInterval) {
                sendData();
                sendingTimer = currentTimer;
            }
            // Count 1 ms
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    std::thread startThread()
    {
        return std::thread([=] { run(); });
    }
};