//
// Created by dennis on 1/18/21.
//

#ifndef PROJECT_3_QUEUE_H
#define PROJECT_3_QUEUE_H
#include "Job.h"

struct qNode{
    Job *myJob;
    qNode *next = nullptr;
    qNode *prev = nullptr;
};


class Queue {
public:
    int size;
    qNode *front, *rear;
    Queue();
    void push(Job*);
    Job *pop();
    ~Queue();
};


#endif //PROJECT_3_QUEUE_H
