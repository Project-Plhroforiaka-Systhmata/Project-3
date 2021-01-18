#include <iostream>
#include <cstdlib>
#include <thread>
#include "Job.h"

using namespace std;


void foo()
{
    while (true) {
        cout << "yo" << endl;
    }
}

int bar(int a, int b)
{
    cout << "men" << endl;
    return a + b;
}

int main()
{
    //std::thread first (foo);     // spawn new thread that calls foo()
    //std::thread second (bar);  // spawn new thread that calls bar(0)
    Job a;
    a.jobFunction(bar(1,2));

    // synchronize threads:
    //first.join();                // pauses until first finishes
    //second.join();               // pauses until second finishes

    //std::cout << "foo and bar completed.\n";

    return 0;
}