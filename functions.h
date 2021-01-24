#ifndef PROJECT_3_FUNCTIONS_H
#define PROJECT_3_FUNCTIONS_H
#include "hashTable.h"
#include "JobScheduler.h"
#include "BF.h"


void train(hashTable*, JobScheduler*);
void preprocess(string[], string[]);
int jsonRead(char*, hashTable*);
int csvRead(hashTable*, char*);
void printMatches(hashTable*);
void makeVectors(hashTable*, char*, BF*, string[], string[], myVector<string>&);
void idfInitialize(hashTable*);
void jsonInitialize(hashTable*);
void testing(hashTable*, int, char*, JobScheduler&, double&);
void validation(int, double, hashTable*, char*);

#endif
