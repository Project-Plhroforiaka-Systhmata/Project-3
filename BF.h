#ifndef PROJECT_2_BF_H
#define PROJECT_2_BF_H

#include <cstring>

static const unsigned char bit_mask[8] = {
        0x80,  //10000000
        0x40,  //01000000
        0x20,  //00100000
        0x10,  //00010000
        0x08,  //00001000
        0x04,  //00000100
        0x02,  //00000010
        0x01   //00000001

};


class BF {
public:
    int size;
    int numberOfRecords;
    char* array;
    int numberOfUpdates;
    int nextUpdate;
    BF(int,int);
    bool insert(const char*);
    void updateBit(int);
    bool checkBit(int);
    bool find(const char*);
    bool search(const char*);
    void resetNextUpdate();
    ~BF();
};


#endif
