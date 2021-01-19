#include <iostream>
#include <thread>
#include <csignal>
#include <unistd.h>
#include "JobScheduler.h"
#include "Queue.h"
#include "ctime"



using namespace std;

Queue *myqueue;
//queue<Job*> myqueue;
pthread_mutex_t lock1; //first mutex
thread **threads;
bool destroyThreads = false;
int threadsTerminated = 0;


Job *getJobInFIFO() {
    if (myqueue->size == 0)
        return nullptr;

    Job *tmp; //= myqueue->getFront();
    tmp = myqueue->pop();
    return tmp;
    //Job *torun = myqueue->pop();
    //return torun;
}


void thread_execute(){
    while (!destroyThreads){
        if (pthread_mutex_lock(&lock1) != 0){
            cout << "An error occurred while locking semaphore" << endl;
        }
        Job *toexecute = getJobInFIFO();

        if (toexecute != nullptr){
            //toexecute call function reference
            toexecute->executeJob();
            delete toexecute;
        }
        if (pthread_mutex_unlock(&lock1) != 0){
            cout << "An error occurred while unlocking semaphore" << endl;
        }
    }
    if (destroyThreads){
        threadsTerminated++;
        cout << "Thread Terminated" << endl;
    }

    //else
        //cout << "Thread Exited" << endl;

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
    pthread_mutex_init(&lock1, NULL);
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
    if (pthread_mutex_lock(&lock1) != 0){
        cout << "An error occurred while locking semaphore" << endl;
    }
    myqueue->push(j);
    if (pthread_mutex_unlock(&lock1) != 0){
        cout << "An error occurred while locking semaphore" << endl;
    }
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
    if (pthread_mutex_lock(&lock1) != 0){
        cout << "An error occurred while locking semaphore" << endl;
    }
    destroyThreads = true;
    if (pthread_mutex_unlock(&lock1) != 0){
        cout << "An error occurred while unlocking semaphore" << endl;
    }
    while (threadsTerminated < execution_threads) {}

    return 0;
}


JobScheduler::~JobScheduler() {
    if (pthread_mutex_lock(&lock1) != 0) {
        cout << "An error occurred while locking semaphore" << endl;
    }
    if (pthread_mutex_unlock(&lock1) != 0){
        cout << "An error occurred while unlocking semaphore" << endl;
    }
    pthread_mutex_destroy(&lock1);
    for (int i = 0 ; i < execution_threads; i++){
        if (threads[i]->joinable())
            threads[i]->detach();
        delete threads[i];
    }
    delete[] threads;
    //
    delete queue;
    delete[] tids;
}

