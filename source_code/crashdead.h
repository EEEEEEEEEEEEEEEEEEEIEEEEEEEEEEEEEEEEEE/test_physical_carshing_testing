#ifndef DIY_CRASHDEAD_H
#define DIY_CRASHDEAD_H
#include "Crashdata.h"

class CrashDead:public CrashData
{
    public:
        CrashDead():CrashData(Dead){}
        //int InsideAction(void);
};
#include "CrashDead.cpp"
#endif
