#include <iostream>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include "JobScheduler.h"
#include "Job.h"

using namespace std;



int main()
{
    arguments tmp;
    tmp.a = 2;
    tmp.b = 3;
    auto *scheduler = new JobScheduler(5);
    tmp.a++;
    Job *tmpjob = new Job("test",tmp);
    scheduler->submit_job(tmpjob);
    
    tmp.a++;
    tmpjob = new Job("test",tmp);
    scheduler->submit_job(tmpjob);
    
    tmp.a++;
    tmpjob = new Job("test",tmp);
    scheduler->submit_job(tmpjob);
    
    tmp.a++;
    tmpjob = new Job("test",tmp);
    scheduler->submit_job(tmpjob);
    
    tmp.a++;
    tmpjob = new Job("test",tmp);
    scheduler->submit_job(tmpjob);
    
    tmp.a++;
    tmpjob = new Job("test",tmp);
    scheduler->submit_job(tmpjob);
    
    tmp.a++;
    tmpjob = new Job("test",tmp);
    scheduler->submit_job(tmpjob);
    


    //scheduler->wait_all_tasks_finish();
    sleep(2);
    scheduler->destroy_scheduler();

    delete scheduler;

    sleep(2);


    return 0;
}