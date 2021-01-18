#ifndef PROJECT_3_JOBSCHEDULER_H
#define PROJECT_3_JOBSCHEDULER_H


#include <thread>
#include <queue>

using namespace std;

struct Job{};

class JobScheduler {
public:
    int execution_threads;
    //Job *queue;
    std::queue<Job*> queue;
    thread::id* tids;
    pthread_mutex_t lock1; //first mutex
    pthread_mutex_t lock2; //second mutex
    JobScheduler();
    JobScheduler(int numThreads);
    ~JobScheduler();
    Job *thread_execute();
    JobScheduler* initialize_scheduler(int execution_threads); //called by constructor
    Job* getJobInFIFO();
    int submit_job(JobScheduler *sch/*,Job* j*/);
    int execute_all_jobs(JobScheduler *sch);
    int wait_all_tasks_finish(JobScheduler *sch);
    int destroy_scheduler(JobScheduler *sch);
};


#endif //PROJECT_3_JOBSCHEDULER_H