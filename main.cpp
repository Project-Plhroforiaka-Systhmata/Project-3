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
//#include "BF.h"
#include "cmath"
#include "JobScheduler.h"
#include "functions.h"


using namespace std;

double minErr, w1, w2, minw1, minw2;
myVector<int> idfVoc(20, false);

int main(int argc, char **argv){
    minErr = 10; w1 = 0; w2 = 0;
    int numThreads = 1;
    JobScheduler sch(numThreads);

    string stopwords[194], specialChars[34];
    preprocess(stopwords,specialChars);

    int worlds=0,sigmod_lines=0;
    myVector<string> voc(91000, false);
    auto *hash = new hashTable(10000);

    worlds = jsonRead(argv[1], hash);
    sigmod_lines = csvRead(hash, argv[2]);

    fstream fin;
    string word, leftSpecId, rightSpecId, label, line;
    int lines_counter=0, count;

    printMatches(hash);

    int numOfUpdates=5;
    BF* bf = new BF(worlds,numOfUpdates);

    makeVectors(hash, argv[1], bf, stopwords, specialChars, voc);

    //idf voc initialization
    idfVoc.resize(voc.size);
    for(int i = 0; i < idfVoc.maxCapacity; i++){
        idfVoc.buffer[i] = 0;
    }

    for (int i = 0; i < hash->numBuckets; i++) {
        bucket *temp = hash->table[i];
        while(temp != NULL) {
            for(int j = 0; j < temp->currentRecords; j++) {
                for (int k = 0; k < temp->records[j].spec->jsonWords->size; k++) {
                    (idfVoc.buffer[temp->records[j].spec->jsonWords->sBuffer[k][0]])++;
                }
            }
            temp = temp->next;
        }
    }

    for (int i = 0; i < hash->numBuckets; i++) {
        bucket *temp = hash->table[i];
        while(temp != NULL) {
            for(int j = 0; j < temp->currentRecords; j++){
                temp->records[j].spec->tfidf=(double*)malloc(sizeof(double)*temp->records[j].spec->jsonWords->size);
                for(int k=0;k<temp->records[j].spec->jsonWords->size;k++) temp->records[j].spec->tfidf[k]=-1;
            }
            temp = temp->next;
        }
    }

    for (int i = 0; i < hash->numBuckets; i++) {
        bucket *temp = hash->table[i];
        while(temp != NULL) {
            for(int j = 0; j < temp->currentRecords; j++){
                for(int i = 0; i < temp->records[j].spec->jsonWords->size; i++){
                    double temp_tfidf;
                    temp_tfidf=((double)temp->records[j].spec->jsonWords->sBuffer[i][1]/temp->records[j].spec->jsonWords->size) * log(hash->size / idfVoc.buffer[temp->records[j].spec->jsonWords->sBuffer[i][0]]);
                    int n=0;
                    while(temp->records[j].spec->tfidf[n]!=-1 && temp->records[j].spec->jsonWords->size != n) n++;
                    temp->records[j].spec->tfidf[n]=temp_tfidf;
                }
                sort(temp->records[j].spec->tfidf,(temp->records[j].spec->tfidf)+temp->records[j].spec->jsonWords->size, greater<double>());
                for(int k = 0; k < 1000; k++){
                    if (temp->records[j].spec->tfidf[k] == -1) break;
                    temp->records[j].spec->value += temp->records[j].spec->tfidf[k];
                }
            }
            temp = temp->next;
        }
    }


    double b = 0.5, e = 2.71828;
    fin.open(argv[2], ios::in);
    int train_lines=0.6*sigmod_lines;
    int templines=0;


    //TRAIN
    train(hash, &sch);
    sch.wait_all_tasks_finish();


    //TEST

    int sigmod_array[297652-sigmod_lines];
    for (int i=0;i<(297652-sigmod_lines);i++)
    {
        sigmod_array[i]=-1;
    }

    double threshold=0.1;
    while(threshold<0.5)
    {
        lines_counter=0;
        int y;
        templines=0;
        int success=0;
        fin.open(argv[2], ios::in);
        while (getline(fin, line)){

            if(lines_counter<sigmod_lines)
            {
                lines_counter++;
                continue;
            }

            if(sigmod_array[lines_counter-sigmod_lines]==1)
            {
                lines_counter++;
                continue;
            }
            if(lines_counter==sigmod_lines+(59531)) break;
            //cout<<line<<endl;

            stringstream s(line);
            count = 0;
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
            vertex *vert1, *vert2;
            vert1 = hash->search(leftSpecId);
            vert2 = hash->search(rightSpecId);

            if (vert1 != nullptr && vert2 != nullptr) {
                templines++;
                double x1, x2;
                x1 = vert1->value;
                x2 = vert2->value;
                double p = -(b + minw1 * x1 + minw2 * x2);
                double pred = 1 / (1 + pow(e,p));


                if(double(pred)<threshold || double(pred)>1-threshold)
                {
                    sigmod_array[lines_counter-sigmod_lines]=1;
                    if (pred<0.5 && vert1 != nullptr && vert2 != nullptr && vert1->specList != vert2->specList) {
                        //copy leftSpecId's list to rightSpecId's list
                        vert1->copyList(vert2->specList);
                    }
                    else
                    {

                        if (vert1 != nullptr && vert2 != nullptr) {
                            list *list1, *list2;
                            list1 = vert1->specList;
                            list2 = vert2->specList;
                            if(list1->negList != list2->negList) {
                                //list1->copyNegList(list2->negList);
                                list1->negList->insert(list2);
                                list2->negList->insert(list1);
                            }
                        }
                    }
                }

            }

            lines_counter++;
        }
        fin.close();
        threshold+=0.1;
        train(hash, &sch);
        sch.wait_all_tasks_finish();
    }
    fin.open(argv[2], ios::in);


    //VALIDATION
    int y;
    templines=0;
    int success=0;
    while (getline(fin, line)){
        if(lines_counter<sigmod_lines+(59531))
        {
            lines_counter++;
            continue;
        }

        stringstream s(line);
        count = 0;
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
        vertex *vert1, *vert2;
        vert1 = hash->search(leftSpecId);
        vert2 = hash->search(rightSpecId);

        if (vert1 != nullptr && vert2 != nullptr) {
            templines++;
            double x1, x2;
            x1 = vert1->value;
            x2 = vert2->value;
            double p = -(b + minw1 * x1 + minw2 * x2);
            double pred = 1 / (1 + pow(e,p));
            cout<<vert1->spec<<","<<vert2->spec<<": "<<pred << " " << y <<endl;
            if(pred>=threshold) pred=1;
            else pred=0;
            if(pred==y) success++;
        }
    }
    fin.close();
    cout << success << " " << templines<< endl;
    cout<<"success rate: "<<(double(success)/59530)*100<<"%"<<endl;

    cout<<minw1<<'\t'<<minw2 << "\t" << minErr <<endl;

    sch.destroy_scheduler();

    delete hash;
    delete bf;
    return 0;
}