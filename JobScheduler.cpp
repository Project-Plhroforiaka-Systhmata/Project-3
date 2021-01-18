#include <iostream>
#include <thread>
#include "JobScheduler.h"

using namespace std;



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

    for (int i  = 0 ; i < execution_threads; i++){
        thread newthread;
        tids[i] = newthread.get_id();
    }


}

int JobScheduler::submit_job(JobScheduler *sch/*, Job *j*/) {
    return 0;
}

int JobScheduler::execute_all_jobs(JobScheduler *sch) {
    return 0;
}

int JobScheduler::wait_all_tasks_finish(JobScheduler *sch) {
    return 0;
}

int JobScheduler::destroy_scheduler(JobScheduler *sch) {
    return 0;
}

Job *JobScheduler::getJobInFIFO() {
    pthread_mutex_lock(&lock1);

        Job *torun = queue.front();
        queue.pop();

    pthread_mutex_unlock(&lock1);
    return torun;
}

JobScheduler::~JobScheduler() {
    pthread_mutex_destroy(&lock1);
}

Job * JobScheduler::thread_execute(){
    while (true){
        Job *toexecute = getJobInFIFO();
        if (toexecute != nullptr){
            //toexecute call functon reference
        }
    }
}