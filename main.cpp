#include <iostream>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include "JobScheduler.h"


using namespace std;




void test(){
    cout << 1 << endl;
}

int main()
{
    //thread first (test);     // spawn new thread that calls foo()
    //std::thread second (bar);  // spawn new thread that calls bar(0)
    /// << first.get_id() << endl;
    JobScheduler *scheduler = new JobScheduler(5);

    // synchronize threads:
    //first.join();                // pauses until first finishes
    //second.join();               // pauses until second finishes

    //pthread_mutex_lock(&lock);
    //pthread_mutex_unlock(&lock);
    //pthread_mutex_destroy(&lock);

    return 0;
}