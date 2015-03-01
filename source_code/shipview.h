#ifndef DIY_SHIPVIEW_H
#define DIY_SHIPVIEW_H
#include "baseclass.h"
class ShipView
{
    public:
    Coordinate* Coor;
    int Mode;
    void Set(Coordinate* C){Coor=C;}
    ShipView():Mode(0){}
    void ViewStyle(){Mode+=1;if(Mode==3)Mode=0;}
    void View(void)
    {
        glLoadIdentity();
        if(Mode==0)    gluLookAt(Coor->Location,Coor->Front+Coor->Location,Coor->Up);
        else if(Mode==1)   gluLookAt(Coor->Location+Coor->Up*2.0-Coor->Front*4.0,Coor->Location+2.0*Coor->Up,Coor->Up);
        else if(Mode==2)   gluLookAt(Coor->Location+2.0*Coor->Up+Coor->Front*4.0,Coor->Location+2.0*Coor->Up,Coor->Up);
    }
};
#endif
