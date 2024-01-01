#pragma once
#include <chrono>
#include <thread>
#include <semaphore>

#include "Fog.h"
#include "Error.h"

class Communication {
private:
    unsigned int sourceId;
    // Bytes/s
    double transmissionSpeedOriginal;
    double transmissionSpeed;
    Error* error;
    Error* transmissionSpeedError;
    Fog* fog;

public:
    Communication(int sourceId, int destinationId, double transmissionSpeed, Error* error, Fog* fog, Error* transmissionSpeedError = nullptr)
        : sourceId(sourceId), transmissionSpeedOriginal(transmissionSpeed), error(error), fog(fog), transmissionSpeedError(transmissionSpeedError){}



    void sendData(const std::string& dados) {
        fog->getConnection();
        if (transmissionSpeedError)
        {
            transmissionSpeed = transmissionSpeedError->compute(transmissionSpeedOriginal);
        }
        else
        {
            transmissionSpeed = transmissionSpeedOriginal;
        }
        // Loose the subsequent threads data
        if (fog->getKillConnection())
        {
            //std::cout << "[Communication] dropping message from " << sourceId << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dados.size() / transmissionSpeed) * 1000));
            return;
        }
        // Wait for data to be transfered
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(dados.size() / transmissionSpeed) * 1000));
        // Loose the first thread data
        if (fog->getKillConnection())
        {
            //std::cout << "[Communication] dropping message from " << sourceId << "\n";
            fog->releaseConnection();
            return;
        }
        // Verifica se ocorreu um erro de transmissão com base na taxa de erro
        if (error && error->check()) 
        {
            std::cout << "[Communication] error dropping message from " << sourceId << "\n";
            fog->releaseConnection(); // Libera o semáforo para indicar erro
            return;
        }
        std::cout << "[Communication] sending message from " << sourceId << "\n";
        // Send the data for real
        fog->addData(dados);
        // Dados transmitidos com sucesso
        fog->releaseConnection(); // Libera o semáforo para indicar sucesso
    }
};