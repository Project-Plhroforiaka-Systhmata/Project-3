#include "Job.h"
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

pthread_mutex_t lock;

Job::Job(string myJob, arguments *funArgs): jobExe(myJob) {
    args = funArgs;
    pthread_mutex_init(&lock, NULL);
}


void Job::executeJob() {
    if (jobExe == "test"){
        cout << add(args->a,args->b) << endl;
    } else if(jobExe == "batchTrain"){
        batchTrain(args->batchSize, args->hash, args->h, args->batch);
    }
}

int Job::add(int a,int b) {
    return a+b;
}

void Job::batchTrain(int batchSize, hashTable *hash, double h, string *batch) {
    double wb1 = 0, wb2 = 0, cost = 0, err, e = 2.71828, b = 0.5;
    int y;
    for(int i = 0; i < batchSize; i++) {
        string line, word, leftSpecId, rightSpecId, label;
        line = batch[i];
        stringstream s(line);
        int count = 0;
        while (getline(s, word, ',')) {
            count++;

            //split line by ',' and recognise leftSpecId, rightpecId and label
            switch (count) {
                case 1:
                    leftSpecId = word;
                    break;
                case 2:
                    rightSpecId = word;
                    break;
                default:
                    stringstream num(word);
                    num >> y;
            }
        }

        //POTENTIALLY LOCK THREAD
        vertex *vert1, *vert2;
        vert1 = hash->search(leftSpecId);
        vert2 = hash->search(rightSpecId);


        double x1, x2;
        x1 = vert1->value;
        x2 = vert2->value;

        double p = -(b + w1 * x1 + w2 * x2);
        double pred = 1 / (1 + pow(e,p));

        err = - y * log(pred) - (1 - y) * log(1 - pred);

        wb1 += (pred - y) * x1;
        wb2 += (pred - y) * x2;
        cost += err;
    }
    //calculate error and change w
    double batchErr;
    batchErr = cost / batchSize;

    //LOCK THREAD
    if (pthread_mutex_lock(&lock) != 0){
        cout << "An error occurred while locking semaphore" << endl;
    }
    w1 = w1 - h * wb1;
    w2 = w2 - h * wb2;
    if(batchErr < minErr){
        minErr = err;
        minw1 = w1;
        minw2 = w2;
    }
    //UNLOCK THREAD
    if (pthread_mutex_unlock(&lock) != 0){
        cout << "An error occurred while locking semaphore" << endl;
    }
}

Job::~Job() {
    if (jobExe == "batchTrain") {
        delete[]args->batch;
    }
    delete args;
}
