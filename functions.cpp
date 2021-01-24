#include "functions.h"
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <regex>
#include <cstdlib>
#include <cmath>

void train(hashTable *hash, JobScheduler *sch){
    //TRAIN
    double h = 0.01;
    string *batchArray;
    int batch = 0, maxBatch = 100;
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

void preprocess(string stopwords[], string specialChars[]){
    fstream fin;
    //string str;
    fin.open("stopwords", ios::in);

    string line;
    int ind = 0;
    while (getline(fin, line)){
        stopwords[ind++] = line;
    }
    fin.close();

    fin.open("specialChars", ios::in);
    ind = 0;
    while (getline(fin, line)){
        specialChars[ind++] = line;
    }
    fin.close();
}

int jsonRead(char *arg, hashTable *hash){
    int worlds=0;
    FILE *fp;
    DIR *dirp2,*dirp3;
    struct dirent * entry2;
    struct dirent * entry3;
    string specs;
    char path[200],path2[200], path3[200], realPath[200], fline[100];
    if (arg == nullptr){
        cout << "Please insert json files path!" << endl;
        exit(-1);
    }
    strcpy(path,arg);
    strcat(path,"/");
    dirp2 = opendir(arg);
    if (dirp2 == nullptr){
        cout << "Camera Specs Folder Not Found" << endl;
        return -1;
    }

    while ((entry2 = readdir(dirp2)) != NULL) {
        strcpy(path,arg);

        if(entry2->d_name[0]=='.') continue;

        strcpy(path3, entry2->d_name);
        strcat(path3,"/");
        strcat(entry2->d_name,"/");
        strcat(path,entry2->d_name);

        dirp3 = opendir(path);
        while ((entry3 = readdir(dirp3)) != NULL) {
            specs="";
            strcpy(path2,path);
            strcpy(realPath,path3);

            if(entry3->d_name[0]=='.') continue;
            strcat(path2,entry3->d_name);
            strcat(realPath,entry3->d_name);

            fp = fopen(path2, "r");
            while (fgets(fline, sizeof(fline), fp))
            {
                specs+=fline;

            }
            fclose(fp);
            char* pch;
            char specs_string[specs.length()+1];
            strcpy(specs_string,specs.c_str());
            pch = strtok (specs_string," ");
            while (pch != NULL)
            {
                string str;
                str+=pch;
                worlds++;

                pch = strtok (NULL, " ");
            }


            string name;
            name += realPath;
            name = regex_replace(name, regex("/"), "//");
            name = regex_replace(name, regex(".json"), "");
            hash->insert(name, new vertex(name, specs));
        }
        closedir(dirp3);
    }
    closedir(dirp2);
    return worlds;
}

int csvRead(hashTable* hash, char *arg){
    fstream fin;
    string word, leftSpecId, rightSpecId, label, line;
    int lines_counter=0, sigmod_lines = 0;
    int count;
    fin.open(arg, ios::in);
    while (getline(fin, line)){
        if(lines_counter==178592) break;
        sigmod_lines++;
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
                    label = word;
            }
        }

        if (label == "1") {
            vertex *vert1, *vert2;
            vert1 = hash->search(leftSpecId);
            vert2 = hash->search(rightSpecId);
            //if leftSpecId and rightSpecId exist and are not already in the same list
            if (vert1 != nullptr && vert2 != nullptr && vert1->specList != vert2->specList) {
                //copy leftSpecId's list to rightSpecId's list
                vert1->copyList(vert2->specList);
            }
        }
        lines_counter++;
    }
    fin.close();

    lines_counter=0;
    fin.open(arg, ios::in);
    while (getline(fin, line)){
        if(lines_counter==178592) break;
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
                    label = word;
            }
        }

        if(label == "0") {

            vertex *vert1, *vert2;
            vert1 = hash->search(leftSpecId);
            vert2 = hash->search(rightSpecId);

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
        lines_counter++;
    }
    fin.close();
    return sigmod_lines;
}

void printMatches(hashTable* hash){
    //print every vertex's list in the hashable
    cout << "All positive matches\n" << endl;
    for (int i = 0; i < hash->numBuckets; i++) {
        bucket *temp = hash->table[i];
        while(temp != NULL) {
            for(int j = 0; j < temp->currentRecords; j++){
                temp->records[j].spec->printList();
            }
            temp = temp->next;
        }
    }

    cout << "\n\nAll negative matches\n" << endl;
    for (int i = 0; i < hash->numBuckets; i++) {
        bucket *temp = hash->table[i];
        while(temp != NULL) {
            for(int j = 0; j < temp->currentRecords; j++){
                temp->records[j].spec->specList->printNegList();
            }
            temp = temp->next;
        }
    }
}

void makeVectors(hashTable* hash, char* arg, BF *bf, string stopwords[], string specialChars[], myVector<string> &voc){
    FILE *fp;
    DIR *dirp2,*dirp3;
    struct dirent * entry2;
    struct dirent * entry3;
    string specs;
    char path[200],path2[200], path3[200], realPath[200], fline[100];

    dirp2 = opendir(arg);
    while ((entry2 = readdir(dirp2)) != NULL) {

        strcpy(path,arg);
        if(entry2->d_name[0]=='.') continue;

        strcpy(path3, entry2->d_name);
        strcat(path3,"/");
        strcat(entry2->d_name,"/");
        strcat(path,entry2->d_name);
        cout<<entry2->d_name<<endl;

        dirp3 = opendir(path);
        vertex* tmpvertex;
        while ((entry3 = readdir(dirp3)) != NULL) {
            specs="";
            strcpy(path2,path);
            strcpy(realPath,path3);
            if(entry3->d_name[0]=='.') continue;

            strcat(path2,entry3->d_name);
            strcat(realPath,entry3->d_name);

            string searchPath;
            searchPath+=realPath;
            searchPath = regex_replace(searchPath, regex("/"), "//");
            searchPath = regex_replace(searchPath, regex(".json"), "");
            tmpvertex=hash->search(searchPath);

            fp = fopen(path2, "r");
            while (fgets(fline, sizeof(fline), fp))
            {
                int flineindex=-1;
                for(int i=0;i<strlen(fline);i++)
                {
                    if(fline[i]=='"' && fline[i+1]==':')
                    {
                        flineindex=i+1;

                        break;
                    }
                }
                strcpy(fline,&fline[flineindex+1]);
                specs+=fline;

            }
            fclose(fp);
            int index=0;
            int vocIndex=-1;
            int flag=0, flag1 = 0;
            char* pch;
            char specs_string[specs.length()+1];
            strcpy(specs_string,specs.c_str());
            pch = strtok (specs_string," ");
            while (pch != NULL)
            {
                flag=0;
                flag1 = 0;
                string str;
                str+=pch;
                string chars;


                for_each(str.begin(), str.end(), [](char & c){
                    c = ::tolower(c);
                });

                for(int i = 0; i < 34; i++) {
                    chars += specialChars[i];
                }

                str.erase(remove_if(str.begin(), str.end(), [&chars](const char& c) {
                    return chars.find(c) != string::npos;
                }), str.end());


                for(int i = 0; i < 194; i++) {
                    if(str == stopwords[i]){
                        flag1 = 1;
                        break;
                    }
                }

                str = regex_replace(str, regex("\n"), "");

                if(flag1 || str == "\n" || str.empty()) {
                    pch = strtok(NULL, " ");
                    continue;
                }

                //insert words in vocabulary
                strcpy(pch, str.c_str());


                if(!bf->find(pch))  //check in bf
                {
                    index=voc.pushBack(str);
                    tmpvertex->jsonWords->pushBack(1,index);
                    bf->insert(pch);
                }
                else
                {
                    for(int i=0;i<voc.size;i++)
                    {
                        if(voc.buffer[i]==str)
                        {
                            flag=1;
                            vocIndex=i;
                            break;
                        }
                    }
                    if(flag==0) // word doesn't exists
                    {
                        bf->insert(pch);
                        index=voc.pushBack(str);
                        tmpvertex->jsonWords->pushBack(1,index);
                    }
                    else    //word exists in voc but you should insert it in json's "voc"
                    {
                        int flagjson=0;
                        for(int j=0;j<tmpvertex->jsonWords->size;j++)
                        {
                            if(tmpvertex->jsonWords->sBuffer[j][0]==vocIndex)
                            {
                                flagjson=1;
                                (tmpvertex->jsonWords->sBuffer[j][1])++;
                            }

                        }
                        if(flagjson==0)
                        {
                            tmpvertex->jsonWords->pushBack(1,vocIndex);
                        }
                    }

                }

                pch = strtok (NULL, " ");
            }
        }
        closedir(dirp3);
    }
    closedir(dirp2);
}

void idfInitialize(hashTable *hash){
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
}

void jsonInitialize(hashTable* hash){
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
                for(int k = 0; k < temp->records[j].spec->jsonWords->size; k++){
                    if (k == 1000) break;
                    if (temp->records[j].spec->tfidf[k] == -1) break;
                    temp->records[j].spec->value += temp->records[j].spec->tfidf[k];
                }
            }
            temp = temp->next;
        }
    }
}

void testing(hashTable *hash, int sigmod_lines, char *arg, JobScheduler &sch, double &threshold){
    double b = 0.5, e = 2.71828;
    int sigmod_array[297652-sigmod_lines];
    for (int i=0;i<(297652-sigmod_lines);i++)
    {
        sigmod_array[i]=-1;
    }

    int count, lines_counter;
    fstream fin;
    string line, word, leftSpecId, rightSpecId;
    while(threshold<0.5)
    {
        lines_counter=0;
        int y;
        int success=0;
        fin.open(arg, ios::in);
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
    }
}

void validation(int sigmod_lines, double threshold, hashTable* hash, char* arg){
    int y;
    int lines_counter = 0;
    int templines=0, testlines = 0;
    int success=0, count;
    double b = 0.5, e = 2.71828;
    fstream fin;
    string line, word, leftSpecId, rightSpecId;
    fin.open(arg, ios::in);
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
        testlines++;
        if (vert1 != nullptr && vert2 != nullptr) {
            templines++;
            double x1, x2;
            x1 = vert1->value;
            x2 = vert2->value;
            double p = -(b + minw1 * x1 + minw2 * x2);
            double pred = 1 / (1 + pow(e,p));
            if(pred>=threshold) pred=1;
            else pred=0;
            if(pred==y) success++;
            cout<<vert1->spec<<","<<vert2->spec<<", pred: " << pred << " y: " << y <<endl;
        }
    }
    fin.close();
    cout<<"success rate: "<<(double(success)/59530)*100<<"%"<<endl;
}