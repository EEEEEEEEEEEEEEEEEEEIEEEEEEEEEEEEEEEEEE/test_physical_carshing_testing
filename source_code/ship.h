#ifndef DIY_SHIP_H
#define DIY_SHIP_H
#include <set>
#include "motion.h"
#include "CrashLive.h"
#include "Brain.h"
#include "Storehouse.h"
#include "Expand.h"
#include "Pretarget.h"
class Ship
{
    public:
        int ID;
        int Shield;
        int Armor;
        std::set<PreExpand*> PossibleExpand;
        std::list<Coordinate> EachPosition;
        std::map<ExStyle, std::list<Coordinate>::iterator> ExpandPosition;
        int NumberOfExpand;
        float Quality;
        Movement Mo;
        //virtual void Show();
};
class SingleShip:public Speed,public Angle,public CrashLive,public Brain,public Storehouse,public TargetTree
{
    public:
        Ship* Style;
        bool Locking;
        Weapon* WE;
        int Owner;
        int Station;
        int ShieldLimited;
        int ShieldRechart;
        int Shield;
        int ArmorLimited;
        int Armor;
        float Quality;
        float Push;
        long LastTime;
        long Time;
        bool Target;
        Coordinate Next;
        Movement Mo;
        std::list<PreExpand*> Ex;
        void Show(Coordinate*);
        void Analyze(void);
        SingleShip():TargetTree(this)
        {
            ShieldLimited=1000;
            ShieldLimited=1000;
            ShieldRechart=1000;
            Shield=1000;
            ArmorLimited=1000;
            Armor=1000;
            Quality=1.0;
            Push=0.1;
            float Speedt[8]={1.0,2.0,0.5,0.5,1.0,0.02,0.1,0.02};
            float Anglee[6]={0.0,0.1,0.0,0.1,0.0,0.1};
            Mo.SetTranslation(M_Front,Speedt);
            Mo.SetAngle(Anglee);
            LastTime=SDL_GetTicks();
            Locking=false;
        }
};

#include "ship.cpp"
#include "SW_MC.h"
#include "SW_MT.cpp"
#include "Ex_MISSILE.h"
#include "Ex_EGG.h"
#endif
