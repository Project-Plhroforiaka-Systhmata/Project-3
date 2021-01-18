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
    scheduler->submit_job(new Job("test",tmp));
    tmp.a++;
    scheduler->submit_job(new Job("test",tmp));
    tmp.a++;
    scheduler->submit_job(new Job("test",tmp));
    tmp.a++;
    scheduler->submit_job(new Job("test",tmp));
    tmp.a++;
    scheduler->submit_job(new Job("test",tmp));
    tmp.a++;
    scheduler->submit_job(new Job("test",tmp));
    tmp.a++;
    scheduler->submit_job(new Job("test",tmp));
    tmp.a++;

    scheduler->wait_all_tasks_finish();

    delete scheduler;

    sleep(2);


    return 0;
}