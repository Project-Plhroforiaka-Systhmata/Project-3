#include "Job.h"
#include <iostream>

using namespace std;

Job::Job(string myJob, arguments funArgs): jobExe(myJob), args(funArgs) {
}


void Job::executeJob() {
}

void Job::jobFunction(int function) {
    function;
}
