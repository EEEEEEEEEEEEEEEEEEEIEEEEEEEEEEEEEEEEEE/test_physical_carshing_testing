#ifndef DIY_CRASHMAP_H
#define DIY_CRASHMAP_H
#include "CrashData.h"
class CrashMap:public CrashData
{
    unsigned int X;
    unsigned int Z;
    float MaxX;
    float MinX;
    float MaxZ;
    float MinZ;
    std::list<XYF> Data;
    public:
        void SetMapSize(unsigned int x,unsigned int z);
        void Set(const float* ,int);
        bool Check(const CrashData*);
        Information Regedit(){}
        CrashMap():X(1),Z(1),CrashData(Map){}
        CrashMap(unsigned int x,unsigned int z):X(x),Z(z),CrashData(Map){}
};
#include "CrashMap.cpp"
#endif
