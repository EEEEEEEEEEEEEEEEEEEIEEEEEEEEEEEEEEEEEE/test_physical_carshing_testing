#ifndef DIY_WEAPON_H
#define DIY_WEAPON_H
#include "baseclass.h"
#include "motion.h"
#include "CrashLive.h"
#define LASER 1
#define MISSILE 2
#define EGG  3
#define MISSLE_FLYING 4
#define MISSLE_BROKE 5
/*enum MissleStyle
{
    M_FLY,
    M_BROKE
};
enum EggStyle
{
    E_FLY,
    E_BROKE
};
union WeaponStation
{
    MissleStyle MS;
    EggStyle MS;
};*/
class Weapon;
class SingleShip;
class PreWeaponSeed
{
    public:
        bool Exist;
        int Using;
        virtual void Show(Weapon*){};
        virtual bool Preanalyze(Weapon*){};
        PreWeaponSeed():Exist(true),Using(0){}
};
template <class T>
class WeaponSeed:public PreWeaponSeed
{
    public:
        T* Point;
        virtual void Analyze(Weapon*){};
        bool Preanalyze(Weapon* W)
        {
            if(!Exist&&Using==0)
            {
                if(Point!=NULL)   delete Point;
                return true;
            }else{
                Analyze(W);
            }
            return false;
        }
        WeaponSeed(T* P):Point(P){}
};
class Weapon:public Plugin_Base
{
    public:
        //Crash* Cra;
        std::list< PreWeaponSeed* > AllWeapon;
        Weapon(std::string S):Plugin_Base(S){}
        long LastTime;
        //Coordinate MissileMove(SingleWeapon*);
        void Show(ControlCenter* CC);
        void Analyze(ControlCenter* CC);
};

#include "weapon.cpp"
#endif
