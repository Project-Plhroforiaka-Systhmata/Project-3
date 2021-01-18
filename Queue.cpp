//
// Created by dennis on 1/18/21.
//

#include "Queue.h"

Queue::Queue():size(0), front(nullptr), rear(nullptr) {

}

void Queue::insert(Job *newJob) {
    auto *newNode = new qNode;
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
    else if(size == 1) {
        temp = front->myJob;
        delete front;
        front = nullptr;
        rear = nullptr;
    }
    else{
        temp = front->myJob;
        qNode *temp2 = front;
        front = front->prev;
        delete temp2;
        front->next = nullptr;
    }
    size--;
    return temp;
}

Queue::~Queue() {
    qNode *temp = rear;
    while(temp != nullptr){
        qNode *temp2;
        temp2 = temp;
        temp = temp->next;
        delete temp2->myJob;
        delete temp2;
    }
}
