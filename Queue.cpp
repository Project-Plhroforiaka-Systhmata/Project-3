//
// Created by dennis on 1/18/21.
//

#include "Queue.h"

Queue::Queue():size(0), front(nullptr), rear(nullptr) {

}

void Queue::insert(Job *newJob) {
    qNode *newNode = new qNode;
    newNode->myJob = newJob;
    if(!size){
        front = newNode;
        rear = newNode;
    }
    else {
        newNode->next = rear;
        rear->prev = newNode;
        rear = newNode;
    }
    size++;
}

Job *Queue::pop() {
    Job *temp;
    if(!size) return nullptr;
    else if(size) {
        temp = front->myJob;
        front = nullptr;
        rear = nullptr;
    }
    else{
        temp = front->myJob;
        front = front->prev;
        front->next = nullptr;
    }
    return temp;
}

Queue::~Queue() {
    qNode *temp = rear;
    while(temp != nullptr){
        qNode *temp2;
        temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
}
