#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <dirent.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include "hashTable.h"
#include "cmath"
#include "JobScheduler.h"
#include "functions.h"


using namespace std;

double w1, w2, minw1, minw2, minErr;
myVector<int> idfVoc(20, false);

int main(int argc, char **argv){
    minErr = 10; w1 = 0; w2 = 0;
    int numThreads = 4;
    JobScheduler sch(numThreads);

    string stopwords[194], specialChars[34];
    preprocess(stopwords,specialChars);

    int worlds,sigmod_lines;
    myVector<string> voc(91000, false);
    auto *hash = new hashTable(10000);

    worlds = jsonRead(argv[1], hash);
    sigmod_lines = csvRead(hash, argv[2]);

    fstream fin;
    string word, leftSpecId, rightSpecId, label, line;

    printMatches(hash);

    int numOfUpdates=5;
    BF* bf = new BF(worlds,numOfUpdates);

    makeVectors(hash, argv[1], bf, stopwords, specialChars, voc);

    //idf voc initialization
    idfVoc.resize(voc.size);
    idfInitialize(hash);

    jsonInitialize(hash);


    //TRAIN
    train(hash, &sch);
    cout<<minw1<<'\t'<<minw2 << "\t" << minErr <<endl;
    sch.wait_all_tasks_finish();
    cout<<minw1<<'\t'<<minw2 << "\t" << minErr <<endl;

    //TEST
    double threshold = 0.1;
    testing(hash,sigmod_lines,argv[2], sch, threshold);
    sch.wait_all_tasks_finish();

    //VALIDATION
    validation(sigmod_lines,threshold, hash, argv[2]);

    sch.destroy_scheduler();

    delete hash;
    delete bf;
    return 0;
}