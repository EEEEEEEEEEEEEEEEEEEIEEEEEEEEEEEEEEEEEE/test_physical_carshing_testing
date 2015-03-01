#ifndef DIY_GLSIMPLIFY_H
#define DIY_GLSIMPLIFY_H
#include "baseclass.h"
inline float Abs(float r)
{
    if(r>=0)
    return r;
    else
    return -r;
}
inline void glVertex(const float* tte,int Tem=1)
{
    glVertex3f(*(tte+(Tem-1)*3),*(tte+(Tem-1)*3+1),*(tte+(Tem-1)*3+2));
}
inline void glVertex(XYZF Tem)
{
    glVertex3f(Tem.X,Tem.Y,Tem.Z);
}
inline void glVertex(XYF Tem)
{
    glVertex2f(Tem.X,Tem.Y);
}
inline void PT(XYZF Tem)
{
    float Temm=Abs(Tem.X)+Abs(Tem.Y)+Abs(Tem.Z);
    glColor3f(Abs(Tem.X/Temm)*2,Abs(Tem.Y/Temm)*2,Abs(Tem.Z/Temm)*2);
    glVertex3f(Tem.X,Tem.Y,Tem.Z);
}
inline void glNormal(XYZF Tem)
{
    glNormal3f(Tem.X,Tem.Y,Tem.Z);
}
inline void glColor(XYZF Tem)
{
    glColor3f(Tem.X,Tem.Y,Tem.Z);
}
inline void gluLookAt(XYZF V1,XYZF V2,XYZF V3)
{
    gluLookAt(V1.X,V1.Y,V1.Z,V2.X,V2.Y,V2.Z,V3.X,V3.Y,V3.Z);
}
#endif
