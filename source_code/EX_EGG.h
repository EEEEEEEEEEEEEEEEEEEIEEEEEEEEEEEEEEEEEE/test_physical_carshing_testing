#ifndef DIY_EX_EGG_H
#define DIY_EX_EGG_H
#include "expand.h"
#include "Weapon_EGG.cpp"
class ExEGG:public Expand<ExEGG>
{
    bool Activing;
    long LastTime;
    long RecharedTime;
    public:
        void Analyze(SingleShip* SS)
        {
            if(SS->LastTime-LastTime>=RecharedTime)
            {
                if(SS->Target)
                {
                    Egg* Ty=new Egg(SS,SS->LastTime);
                    //Ty->Target=Target;
                    SS->WE->AllWeapon.push_back(Ty);
                    LastTime=SS->LastTime;
                }
            }
        }
        ExEGG():Expand<ExEGG>(this),RecharedTime(500),LastTime(0)
        {
            Style=EggLancer; 
        }
};
#endif
