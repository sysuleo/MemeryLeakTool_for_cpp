#ifndef TRACER_NEW_H_
#define TRACER_NEW_H_
#include<map>

void * operator new(size_t size,const char*file,long line);

class TracerNew{
//inner classr
    class TraceNewInfo{
    public:
	TracerNewInfo(const char*file=nullptr,long line =0);
 	const char*File()const;
	long Line()const;
    private:
	const char*file_;
	long line_;
    }
public:
    TracerNew();
    ~TracerNew();
    void Add(void*p,const char*file,long line);
    void Remove();
    void Dump();
private:
    std::map<void*,TraceNewInfo> tracer_infos_;
    private:
	const char*file_;
	long line_;
};


extern TracerNew NewTracer;
#endif//!TRACER_NEW_H_
