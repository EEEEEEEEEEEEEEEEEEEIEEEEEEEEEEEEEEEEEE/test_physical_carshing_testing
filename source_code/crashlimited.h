#ifndef DIY_CRASHLIMITED_H
#define DIY_CRASHLIMITED_H
#include "Crashbase.h"

class CrashLimited:public CrashData
{
    std::vector<CrashSingleData> Data;
    std::list<CrashSingleData> DataE;
};
#include "Crash.cpp"
#endif
