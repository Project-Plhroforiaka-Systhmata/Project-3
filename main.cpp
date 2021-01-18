#include <iostream>
#include <cstdlib>
#include <thread>

using namespace std;


void foo()
{
    while (true) {
        cout << "yo" << endl;
    }
}

void bar()
{
    while (true) {
        cout << "men" << endl;
    }
}

int main()
{
    std::thread first (foo);     // spawn new thread that calls foo()
    std::thread second (bar);  // spawn new thread that calls bar(0)



    // synchronize threads:
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes

    std::cout << "foo and bar completed.\n";

    return 0;
}