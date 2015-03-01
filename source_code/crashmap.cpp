#ifndef DIY_CRASHMAP_CPP
#define DIY_CRASHMAP_CPP
#include "crashmap.h"
void CrashMap::Set(const float* Poi,int number)
{
    float Max=0.0,Mix=0.0,Maz=0.0,Miz=0.0;
    for(int i=0;i<number;++i)
    {
        if(Poi[i]>Max) Max=Poi[i];
        else if(Poi[i]<Mix) Mix=Poi[i];
        if(Poi[i+1]>Maz) Maz=Poi[i+1];
        else if(Poi[i+1]<Miz) Miz=Poi[i+1];
    }
    MaxX=Max;
    MinX=Mix;
    MaxZ=Maz;
    MinZ=Miz;
    for(int i=0;i<number;++i)
    {
        XYF Tem(Poi[i*2],Poi[i*2+1]);
        Data.push_back(Tem);
    }
}
void CrashMap::SetMapSize(unsigned int x,unsigned int z)
{
    if(x>0&&z>0)
    {
        X=x;
        Z=z;
    }
}
bool CrashMap::Check(const CrashData* Poi)
{
    std::list<CrashSingleData>::iterator P2=Data.begin();
    std::list<CrashSingleData>::iterator P1=Data.begin();
    ++P2;
    XYF Lo(Poi->Location.X,Poi->Location.Z);
    float& Di=Poi->Distance;
    for(;P2!=Data.end();++P1,++P2)
    {
        if(Lo.Distance(*P1,*P2)<Di)
        {
            if(Lo.Distance(*P1)<Di||Lo.Distance(*P2)<Di)
            {
                return true;
            }else{
                XYF Pp1=Lo-*P1;
                XYF Pp2=Lo-*P2;
                if(Pp1*Pp2<=0.0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
#endif
