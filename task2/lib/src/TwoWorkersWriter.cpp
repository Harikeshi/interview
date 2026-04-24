#include <ThreadsLib/TwoWorkersWriter.hpp>

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

inline std::string getHomePath()
{
    std::string result;
#ifdef _WIN32
    result = std::string(std::getenv("USERPROFILE"));
#else
    result = std::string(getenv("HOME"));
#endif
    return result;
}

TwoWorkersWriter::TwoWorkersWriter(int limit)
    : activeThreads{2}
{
    generator = std::make_unique<PrimeNumberGenerator>(limit);
}

void TwoWorkersWriter::SetLimit(int number)
{
    std::lock_guard lk(generatorMutex);
    generator = std::make_unique<PrimeNumberGenerator>(number);
}

void TwoWorkersWriter::start()
{
    resultFile.open(getHomePath() + "\\Result.txt");
    {
        std::lock_guard lk(threadMutex);
        activeThreads = 2;
    }

    thread1 = std::thread(&TwoWorkersWriter::worker, this, getHomePath() + "\\Result1.txt");
    thread2 = std::thread(&TwoWorkersWriter::worker, this, getHomePath() + "\\Result2.txt");
}

void TwoWorkersWriter::wait()
{
    std::unique_lock lk(threadMutex);
    cv.wait(lk, [&] { return activeThreads == 0; });

    if (thread1.joinable())
        thread1.join();
    if (thread2.joinable())
        thread2.join();
}

TwoWorkersWriter::~TwoWorkersWriter()
{
    wait();
#ifdef _DEBUG
    std::cout << "Done!" << std::endl;
#endif
}

void TwoWorkersWriter::worker(const std::string& fileName)
{
    std::ofstream file(fileName);

    while (true)
    {
        int prime;
        {
            std::lock_guard lk(generatorMutex);
            prime = generator->Next();

            if (prime == -1)
                break;

            resultFile << prime << " ";
            resultFile.flush();
        }
        file << prime << " ";
    }
    {
        std::lock_guard lk(threadMutex);
        --activeThreads;
    }
    cv.notify_one();
}