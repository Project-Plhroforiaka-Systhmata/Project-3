#ifndef PROJECT_3_JOB_H
#define PROJECT_3_JOB_H
#include <string>

using namespace std;

struct arguments{

};


class Job {
public:
    arguments args;
    string jobExe;
    Job(string, arguments);
    void executeJob();
    void jobFunction(int);
};


#endif
