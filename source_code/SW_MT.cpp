#ifndef DIY_MT_H
#define DIY_MT_H
#include "Weapon_Missile.h"
class SingleShip;
SingleShip* Cppp;
class MissileTarget:public Software
{
    long Time;
    bool Ready;
    public:
        MissileTarget():Ready(false){}
        void Analyze(SingleShip* SS,void* V)
        {
            if(SS->Target)
            {
                if(!Ready)
                {
                    Time=SS->LastTime;
                    Ready=true;
                }else{
                    if(SS->Target)
                    {   
                        if(SS->LastTime-Time>=1000)
                        {
                            for(std::list<PreExpand*>::iterator Po=SS->Ex.begin();Po!=SS->Ex.end();++Po)
                            {
                                if((*Po)->Style==MissileLancer)
                                {
                                    Information Tr;
                                    Tr.Category1=123;
                                    Tr.Data1.v=TransPoint<TargetTree,SingleShip>(Cppp);
                                    (*Po)->In.push_back(Tr);
                                }
                            }
                            SS->Target=false;
                        }
                    }else{
                        Ready=false;
                    }
                }
            }else{
                Ready=false;
            }
        }
};
#endif
