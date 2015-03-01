#ifndef DIY_CRASHLIVE_H
#define DIY_CRASHLIVE_H
#include "CrashData.h"
class CrashLive:public CrashData
{
    public:
        CrashLive():CrashData(Live){}
};
#endif
