#include <iostream>
#include <thread>
#include "JobScheduler.h"

using namespace std;

queue<Job*> myqueue;
pthread_mutex_t lock1; //first mutex
thread **threads;

Job *getJobInFIFO() {
    if (myqueue.size() == 0){
        return nullptr;
    }
    pthread_mutex_lock(&lock1);
    Job *torun = myqueue.front();
    myqueue.pop();
    pthread_mutex_unlock(&lock1);

    return torun;


}


void thread_execute(){
    while (true){
        Job *toexecute = getJobInFIFO();
        if (toexecute != nullptr){
            //toexecute call functon reference
            toexecute->executeJob();
        }
    }
}

void createThreads(int num,thread::id *tids){
    threads = new thread*[num];
    for (int i  = 0 ; i < num; i++){
        threads[i] = new thread(thread_execute);
        tids[i] = threads[i]->get_id();
    }
    // synchronize threads:
    cout << "Main Thread: Waiting Threads to finish" << endl;
    for (int i  = 0 ; i < num; i++){
        threads[i]->join();
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
    myqueue = queue;
    createThreads(execution_threads,tids);
    return nullptr;

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


JobScheduler::~JobScheduler() {
    pthread_mutex_destroy(&lock1);
}

