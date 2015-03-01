#ifndef DIY_CRASHBASE_CPP
#define DIY_CRASHBASE_CPP
#include "CrashBase.h"
bool ConcaveCheck(XYF X1,XYF X2,XYF X3) 
{
    XYF Tem1=X2-X1;
    XYF Tem2=X3-X2;
    XYF Tem3=XYF(Tem1.Y,-Tem1.X);
    if(Tem3*Tem2<0) return true;
    else return false;
}
#endif
