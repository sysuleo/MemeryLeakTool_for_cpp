#define new new(__FILE__,__LINE__)
#include "DebugNew.h"

int main(){
    int *p=new int;
    return 0;
}
