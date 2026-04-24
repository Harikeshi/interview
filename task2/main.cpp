#include <ThreadsLib/TwoWorkersWriter.hpp>

int main()
{
    TwoWorkersWriter writer(1000);
    writer.start();

    return 0;
}