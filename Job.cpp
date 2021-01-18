#include "Job.h"
#include <iostream>

using namespace std;

Job::Job(string myJob, arguments funArgs): jobExe(myJob), args(funArgs) {
}


void Job::executeJob() {
    if (jobExe == "test"){
        cout << add(args.a,args.b) << endl;
    }
}

int Job::add(int a,int b) {
    return a+b;
}
