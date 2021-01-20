#ifndef PROJECT_3_JOB_H
#define PROJECT_3_JOB_H
#include <string>

using namespace std;

struct arguments{
    int a,b;
};


class Job {
public:
    arguments args;
    string jobExe;
    Job(string, arguments);
    void executeJob();
    int add(int,int);
};


#endif
