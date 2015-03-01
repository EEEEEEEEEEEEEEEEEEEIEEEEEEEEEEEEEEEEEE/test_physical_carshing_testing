#ifndef DIY_WEAPON_CPP
#define DIY_WEAPON_CPP
#include "weapon.h"
void Weapon::Show(ControlCenter* CC)
{
    if(!AllWeapon.empty())
    {
        //error<<"sadasdasdasd"<<endl;
        std::list<PreWeaponSeed*>::iterator P;
        for(P=AllWeapon.begin();P!=AllWeapon.end();++P)
        {
            (*P)->Show(this);
        }
    }
}
void Weapon::Analyze(ControlCenter* CC)
{
    while(!Library.empty())
    {
        Information Te(GetInformation());
        if(Te.Category1==456677)
        {
            /*error<<"jajaja"<<endl; 
            SingleWeapon* SW=new SingleWeapon;
            SW->Style=&Missile;
            SW->Resource=static_cast<Coordinate*>(Te.Data1.v);
            SW->Target=static_cast<Coordinate*>(Te.Data2.v);
            SW->Location=SW->Resource->Location;
            error<<(int)(Te.Data1.v);
            error<<"  pp"<<static_cast<Coordinate*>(Te.Data1.v)->Location.X<<"  "<<static_cast<Coordinate*>(Te.Data1.v)->Location.Y<<"  "<<static_cast<Coordinate*>(Te.Data1.v)->Location.Z <<endl;
            error<<"  tt"<<SW->Resource->Location.X<<"  "<<SW->Resource->Location.Y<<"  "<<SW->Resource->Location.Z <<endl;
            error<<"  tt2   "<<SW->Target->Location.X<<"  "<<SW->Target->Location.Y<<"  "<<SW->Target->Location.Z <<endl;
            SW->Up=SW->Resource->Up;
            SW->Front=SW->Resource->Front;
            SW->Left=SW->Resource->Left;
            SW->LastTime=SDL_GetTicks();
            AllWeapon.push_back(SW);*/
        }
    }
    LastTime=SDL_GetTicks();
    //error<<AllWeapon.size()<<endl;
    for(std::list<PreWeaponSeed*>::iterator P=AllWeapon.begin();P!=AllWeapon.end();++P)
    {
        //error<<"спак~~~"<<endl;
        if((*P)->Preanalyze(this))
        {
            AllWeapon.erase(P--);
        }   
    }
}

/*Coordinate Weapon::MissileMove(SingleWeapon* SW)
{
    Coordinate Tem=*SW;
    //error<<" ghfdgfdg "<<Tem.Location.X<<"  "<<Tem.Location.Y<<"  "<<Tem.Location.Z <<endl;
    XYZF T1=SW->Target->Location-Tem.Location;
    if(T1*Tem.Front>=0)
    {
        Missile.Mo.Move[0]=true;
        Missile.Mo.Move[1]=false;
    }else{
        Missile.Mo.Move[0]=false;
        Missile.Mo.Move[1]=true;
    }
    if(T1*Tem.Left>0)
    {
        Missile.Mo.AngleT[2]=true;
        Missile.Mo.AngleT[3]=false;
    }else if(T1*Tem.Left<0)
    {
        Missile.Mo.AngleT[2]=false;
        Missile.Mo.AngleT[3]=true;
    }else{
        Missile.Mo.AngleT[2]=false;
        Missile.Mo.AngleT[3]=false;
    }
    if(T1*Tem.Up<0)
    {
        Missile.Mo.AngleT[4]=true;
        Missile.Mo.AngleT[5]=false;
    }else if(T1*Tem.Up>0)
    {
        Missile.Mo.AngleT[4]=false;
        Missile.Mo.AngleT[5]=true;
    }else{
        Missile.Mo.AngleT[4]=false;
        Missile.Mo.AngleT[5]=false;
    }
    Missile.Mo.Change(10,SW,&Tem);
    //error<<""<<endl;
    return Tem;
}*/
#endif
