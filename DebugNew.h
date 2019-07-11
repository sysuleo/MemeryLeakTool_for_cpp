#ifndef DEBUG_NEW_H_
#define DEBUG_NEW_H_
#include"TracerNew.h"
void* operator new (size_t size,char*file,long line){
    void *p=malloc(size);//begin to record
    NewTracer.Add();
};

//using global varance to record the operation of new and delete
//the rest of the records indicate  memery leak

#define new new(__FILE__,__LINE__)



#endif//!DEBUG_NEW_H_
