#ifndef PROJECT_1_VERTEX_H
#define PROJECT_1_VERTEX_H
#include <string>
#include "list.h"
#include "vector.h"

using namespace std;
extern myVector<int> idfVoc;

class vertex {
public:
    int printed,trained;
    string spec, itemSpecs;
    double *tfidf, value;
    myVector<int> *jsonWords;
    list *specList;
    vertex(string, string);
    int copyList(list*);
    void printList();
    ~vertex();
};


#endif
