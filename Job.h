#ifndef PROJECT_3_JOB_H
#define PROJECT_3_JOB_H
#include <string>
#include "hashTable.h"
#include "vector.h"

extern double minErr, w1, w2, minw1, minw2;
extern myVector<int> idfVoc;

using namespace std;

struct arguments{
    int a,b;
    int batchSize;
    hashTable *hash;
    double h;
    string *batch;
};


class Job {
public:
    arguments *args;
    string jobExe;
    Job(string, arguments*);
    void executeJob();
    int add(int,int);
    void batchTrain(int, hashTable*, double, string*);
    ~Job();
};


#endif
