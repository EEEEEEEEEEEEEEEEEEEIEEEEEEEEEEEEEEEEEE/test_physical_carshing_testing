#ifndef DIY_CRASHBASE_H
#define DIY_CRASHBASE_H
#include <list>
#include <vector>
#include "information.h"
#include "baseclass.h"
#define CRASHBEGIN 10
#define CRASHMIDDLE 2
#define CRASHEND 30

#define CRASH 45
#define UNCRASH 78

#define CRASHTEXT 73

#define CRASHOUTMAP 74
#define CRASHFACE 12
#define CRASHNODATA 46
#define CRASHNOCRASH 95
#define CrashLocation Coordinate

enum CrashMode
{
    Function,
    Value
};
enum CrashStyle
{
    Dead,
    DeadTem,
    Live,
    Limited,
    Map,
    Mark
};
bool ConcaveCheck(XYF X1,XYF X2,XYF X3);
class CrashSingleData
{
    public:
        int Mode;
        XYF Data;
        bool AnotherPoint;
        std::list<CrashSingleData>::iterator PE;
        CrashSingleData():AnotherPoint(false){}
        operator XYF()
        {
            return Data;
        }
};
class CrashFace:public CrashLocation
{
    public:
        int Mode;
        float Distance;
        std::vector<CrashSingleData> Data;
        std::list<CrashSingleData> DataE;
        /*XYZF Translate(XYF& Tr)
        {
            XYZF Tcc(Tr.X*AuxiliaryVector2+Tr.Y*AuxiliaryVector);
            return Tcc+Location;
        }
        XYF Translate(XYZF& Tr)
        {
            XYZF Tb=Tr-Location;
            Tb=Tb.ToCoordinate(AuxiliaryVector2,Vector,AuxiliaryVector);
            XYF Tii(Tb.X,Tb.Z);
            return Tii;
        }*/
};
class CrashSingleForXYZF
{
    public:
        XYZF Data;
        std::list<CrashSingleData>::iterator PE;
        operator XYZF()
        {
            return Data;
        }
};
#include "Crashbase.cpp"
#endif
