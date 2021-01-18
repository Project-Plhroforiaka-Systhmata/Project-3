#ifndef PROJECT_3_JOB_H
#define PROJECT_3_JOB_H
#include <string>

using namespace std;

typedef struct arguments{
    int a,b;
}arguemnts;


class Job {
public:
    arguments args;
    string jobExe;
    Job(string, arguments);
    void executeJob();
    int add(int,int);
};


#endif
