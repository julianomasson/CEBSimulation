#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <semaphore>

class Fog {
private:
    unsigned int id;
    double sendingFreq;
    std::string currentMessage = "";
    //void (*externalFunction)();
    std::counting_semaphore<1> semaphore;
    bool killConnection = false;

public:
    Fog(unsigned int id, double sendingFreq)
        : id(id), sendingFreq(sendingFreq), semaphore(1) {}

    void getConnection()
    {
        killConnection = !semaphore.try_acquire();
    }

    bool getKillConnection()
    {
        return killConnection;
    }

    void releaseConnection()
    {
        semaphore.release();
    }

    void addData(const std::string& data)
    {
        //std::cout << "[Fog] " << id << ": " << data << "\n";
        currentMessage += data;
    }

    void run()
    {
        std::chrono::milliseconds sendingInterval(static_cast<int>((1 / sendingFreq) * 1000));

        auto sendingTimer = std::chrono::steady_clock::now();

        while (true) {
            auto currentTimer = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTimer - sendingTimer) >= sendingInterval) {
                //sendData();
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