#ifndef PROJECT_3_JOBSCHEDULER_H
#define PROJECT_3_JOBSCHEDULER_H


#include <thread>
#include <queue>
#include "Queue.h"

using namespace std;


class JobScheduler {
public:
    int execution_threads;
    Queue *queue;
    thread::id* tids;
    JobScheduler();
    JobScheduler(int numThreads);
    ~JobScheduler();
    JobScheduler* initialize_scheduler(int execution_threads); //called by constructor
    int submit_job(Job* j);
    int execute_all_jobs();
    int wait_all_tasks_finish();
    int destroy_scheduler();
};


#endif //PROJECT_3_JOBSCHEDULER_H
