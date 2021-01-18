#include <iostream>
#include <thread>
#include <csignal>
#include <unistd.h>
#include "JobScheduler.h"
#include "Queue.h"



using namespace std;

Queue* myqueue;
pthread_mutex_t lock1; //first mutex
thread **threads;
bool destroyThreads = false;

Job *getJobInFIFO() {

    pthread_mutex_lock(&lock1);

    Job *torun = myqueue->pop();

    pthread_mutex_unlock(&lock1);

    return torun;


}


void thread_execute(){
    while (true && !destroyThreads){
        Job *toexecute = getJobInFIFO();
        if (toexecute != nullptr){
            //toexecute call functon reference
            toexecute->executeJob();
            delete toexecute;
        }
    }
    if (destroyThreads)
        cout << "Thread Terminated" << endl;
    else
        cout << "Thread Exited" << endl;

}

void createThreads(int num,thread::id *tids){
    threads = new thread*[num];
    for (int i  = 0 ; i < num; i++){
        threads[i] = new thread(thread_execute);
        tids[i] = threads[i]->get_id();
    }


}

JobScheduler::JobScheduler() {
    execution_threads = 1;
    cout << "WARNING: Scheduler Initialized with no arguments!!\nOnly 1 Thread will be created!!" << endl;
    initialize_scheduler(1);
    return;
}

JobScheduler::JobScheduler(int numThreads) {
    initialize_scheduler(numThreads);
}


JobScheduler *JobScheduler::initialize_scheduler(int numThreads) {
    execution_threads = numThreads;
    tids = new thread::id[5];
    queue = new Queue();
    myqueue = queue;
    createThreads(execution_threads,tids);
    return nullptr;

}

int JobScheduler::submit_job( Job *j) {
    queue->insert(j);
    return 0;
}

int JobScheduler::execute_all_jobs() {
    return 0;
}

int JobScheduler::wait_all_tasks_finish() {
    // synchronize threads:
    cout << "Main Thread: Waiting Threads to finish" << endl;
    for (int i  = 0 ; i < execution_threads; i++){
        threads[i]->join();
    }
    return 0;
}

int JobScheduler::destroy_scheduler() {
    destroyThreads = true;

    return 0;
}


JobScheduler::~JobScheduler() {
    pthread_mutex_destroy(&lock1);
    for (int i = 0 ; i < execution_threads; i++){
        threads[i]->detach();
        delete threads[i];
    }
    usleep(500);
    delete[] threads;
    delete myqueue;
    delete[] tids;
}

