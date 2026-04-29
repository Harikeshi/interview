#pragma once

#include <ThreadsLib/PrimeNumberGenerator.hpp>

#include <fstream>
#include <mutex>
#include <memory>
#include <thread>
#include <condition_variable>
#include <atomic>

class TwoWorkersWriter
{
    constexpr static int workers = 2;

public:
    explicit TwoWorkersWriter(int limit);
    void SetLimit(int number);
    void start();
    ~TwoWorkersWriter();

private:
    void worker(const std::string& fileName);
    void wait();

    std::unique_ptr<PrimeNumberGenerator> generator;
    std::thread thread1;
    std::thread thread2;

    std::mutex generatorMutex;
    std::ofstream resultFile;

    std::mutex threadMutex;
    std::condition_variable cv;
    std::atomic<int> activeThreads; // количество активных потоков
};
