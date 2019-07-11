#include "tracerNew.h"
#include<cstdio>
#include<iostream>
TracerNew NewTracer;
bool TracerNew::Ready=false;

void*operator new(size_t size,const char*file,long line){
    void*p=malloc(size);
    //begin to record
    NewTracer.Add(p,file,line);
    return p;
}

void*operator new(size_t size){
    void*p=malloc(size);
    if(TracerNew::Ready)  //Ready=false first
	NewTracer.Add(p,"Unknow",-1);
    return p;
}

void operator delete(void*){
    if(TracerNew::Ready)//prevent delete p after cancling of NewTracer
        NewTracer.Remove(p);
    free(p);
}

TracerNew::TracerNewInfo::TracerNewInfo(const char *file,long line):file_(file),line_(line){

}

const char*TracerNew::TracerNewInfo::File()const
{
    return file_;
}

TracerNew::TracerNew(){
    TracerNew::Ready=true;//can be done by lock.it is unsafe now;
}

TracerNew::~TracerNew(){
    NewTracer::Ready=false;
    Dump();
}

long TracerNew::TracerNewInfo::Line()const{
    return line_;
}

void TracerNew::Add(void*p,const char*file,long line){
    if(lock_count_>0) return;
    lock_count_++; //add lock
    tracer_infos_[p]=TracerNewInfo(file,line);  //in order to wuxiandigui
    lock_count_--; //
}

void TracerNew::Remove(void*p){
    if(lock_count_>0) return;
    lock_count_++; //add lock
    auto it = tracer_infos_.find(p);
    if(it!=tracer_infos_.end()){
	tracer_infos_.erase(it); //delete, maybe fanfu buting delete
    }
    lock_count_--;
}

void TracerNew:Dump(){
    for (auto tracer_info:tracer_infos_){
	std::cout<<"0x"<<tracer_info.first<<":\t"<<tracer_info.second.File()<<"\tIn_line:"<<tracer_info.Line()<<endl;
    }
}

    
