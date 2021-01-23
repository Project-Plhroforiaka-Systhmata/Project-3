#include "functions.h"

void train(hashTable *hash, JobScheduler *sch){
    //TRAIN
    double h = 0.01;
    string *batchArray;
    int batch = 0, maxBatch = 5;
    batchArray = new string[maxBatch];

    for (int i = 0; i < hash->numBuckets; i++) {//TRAIN

        bucket *temp = hash->table[i];
        while(temp != NULL) {
            for(int j = 0; j < temp->currentRecords; j++){
                node *temp1;
                temp1 = temp->records[j].spec->specList->head;
                while(temp1 != NULL){

                    if (temp1->spec->spec != temp->records[j].spec->spec && !temp1->spec->trained) {
                        vertex *vert1, *vert2;
                        vert1 = temp1->spec;
                        vert2 = temp->records[j].spec;

                        if (vert1 != nullptr && vert2 != nullptr) {
                            string pair;
                            pair = vert1->spec + "," + vert2->spec + ",1";
                            batchArray[batch++] = pair;
                            if(batch == maxBatch){
                                arguments *args = new arguments;
                                args->batch = batchArray;
                                args->h = h;
                                args->hash = hash;
                                args->batchSize = batch;
                                Job *newJob = new Job("batchTrain", args);
                                sch->submit_job(newJob);
                                batchArray = new string[maxBatch];
                                batch = 0;
                            }
                        }

                    }
                    temp1 = temp1->next;
                }
                temp->records[j].spec->trained = 1;
            }
            temp = temp->next;
        }
    }

    for (int i = 0; i < hash->numBuckets; i++) { //TRAIN
        bucket *temp = hash->table[i];
        while(temp != NULL) {
            for(int j = 0; j < temp->currentRecords; j++){
                if(temp->records[j].spec->specList->trained) continue;
                node *temp1 = temp->records[j].spec->specList->head;
                while(temp1 != NULL) {
                    lnode *temp2 = temp->records[j].spec->specList->negList->head;
                    while (temp2 != NULL){
                        //if(temp2->spec == this || temp2->spec->printed){
                        if(temp2->spec->trained){
                            temp2 = temp2->next;
                            continue;
                        }
                        node *temp3 = temp2->spec->head;
                        while(temp3 != NULL){
                            vertex *vert1, *vert2;
                            vert1 = temp1->spec;
                            vert2 = temp3->spec;

                            if (vert1 != nullptr && vert2 != nullptr) {
                                string pair;
                                pair = vert1->spec + "," + vert2->spec + ",0";
                                batchArray[batch++] = pair;
                                if(batch == maxBatch){
                                    arguments *args = new arguments;
                                    args->batch = batchArray;
                                    args->h = h;
                                    args->hash = hash;
                                    args->batchSize = batch;
                                    Job *newJob = new Job("batchTrain", args);
                                    sch->submit_job(newJob);
                                    batchArray = new string[maxBatch];
                                    batch = 0;
                                }
                            }
                            temp3 = temp3->next;
                        }
                        temp2 = temp2->next;
                    }
                    temp1 = temp1->next;
                }
                temp->records[j].spec->specList->trained = 1;
            }
            temp = temp->next;
        }
    }

    if(batch != 0){
        arguments *args = new arguments;
        args->batch = batchArray;
        args->h = h;
        args->hash = hash;
        args->batchSize = batch;
        Job *newJob = new Job("batchTrain", args);
        sch->submit_job(newJob);
    }
}