#ifndef DIY_2DFLAT_H
#define DIY_2DFLAT_H
#include "ControlCenter.h"
class Flat
{
    public:
        ControlCenter* CC;
        void Start2D(unsigned int);
        void Back(void);
        Flat(ControlCenter* C):CC(C){}
};
void Flat::Start2D(unsigned int i)
{
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0,0.0,-CC->NearSize-0.0107-0.00001*i);
    glScalef(CC->NX,CC->NY,0.0);
}
void Flat::Back(void)
{
    glPopMatrix();
}
#endif
