#ifndef DIY_EX_MISSILE_H
#define DIY_EX_MISSILE_H
#include "expand.h"
#include "Weapon_Missile.h"
class ExMissile:public Expand<ExMissile>
{
    bool Activing;
    long LastTime;
    long RecharedTime;
    TargetTree* Target;
    public:
        void Analyze(SingleShip* SS)
        {
            while(!In.empty())
            {
                //error<<"ÊÇµÄ"<<endl;
                std::list<Information>::iterator Inf=In.begin();
                if(Inf->Category1==123)
                {
                    Activing=true;
                    Target=static_cast<TargetTree*>(Inf->Data1.v);
                }
                In.pop_front();
            }
            if(Activing)
            {
                if(SS->LastTime-LastTime>=RecharedTime)
                {
                    Missile* Ty=new Missile(SS,Target);
                    //Ty->Target=Target;
                    SS->WE->AllWeapon.push_back(Ty);
                    LastTime=SS->LastTime;
                }
                Activing=false;
            }
        }
        ExMissile():Expand<ExMissile>(this),RecharedTime(0),LastTime(0)
        {
            Style=MissileLancer; 
        }
};
#endif
