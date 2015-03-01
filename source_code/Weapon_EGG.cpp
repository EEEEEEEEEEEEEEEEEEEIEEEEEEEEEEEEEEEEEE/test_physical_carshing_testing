#ifndef DIY_WEAPON_EGG_H
#define DIY_WEAPON_EGG_H
#include "Weapon.h"
class Egg:public Speed,public Coordinate,public WeaponSeed<Egg>
{
    public:
        static Movement Mo;
        static long Time;
        static int Damage;
        static int EnergyCost;
        static int ID;
        static int Model;
        
        long LastTime;
        float Stage;
        Coordinate Move(long);
        void Show(Weapon*);
        void Analyze(Weapon*);
        void Init(void);
        Egg(Coordinate* Resource,long T):WeaponSeed<Egg>(this),LastTime(T)
        {
            Location=Resource->Location;
            Up=Resource->Up;
            Front=Resource->Front;
            Left=Resource->Left;
        }
};
float Eggc[8]={4.0,2.0,0.5,-1.0,0.0,0.0,0.0,0.0};
float EggA[6]={0.0,0.5,0.0,0.5,0.0,0.5};
Movement Egg::Mo(M_Null,Eggc,EggA);
long Egg::Time(10000);
int Egg::Damage(10);
int Egg::EnergyCost(10);
int Egg::ID(0);
int Egg::Model(-1);
Coordinate Egg::Move(long Time)
{
    Coordinate Tem=*this;
    //error<<" ghfdgfdg "<<Tem.Location.X<<"  "<<Tem.Location.Y<<"  "<<Tem.Location.Z <<endl;
    Mo.Move[0]=true;
    Mo.Move[1]=false;
    Mo.Change(10,this,&Tem);
    return Tem;
}
void Egg::Analyze(Weapon* W)
{
    if(W->LastTime-LastTime>=Time)
    {
        Exist=false;
    }else{
        Coordinate Tr=Move(W->LastTime-LastTime);
        Location=Tr.Location;
        Up=Tr.Up;
        Front=Tr.Front;
        Left=Tr.Left;
        //LastTime=W->LastTime;
    }
}
void Egg::Show(Weapon* W)
{
        if(Model==-1)
        {
            //error<<"³õÊ¼»¯"<<endl;
            const float c=0.3;
            const float k=0.1;
            const float g=0.1;
            Model=glGenLists(1);
    
            glNewList(Model,GL_COMPILE);
            glBegin(GL_QUAD_STRIP);
            glVertex3f(-k,g,-c);
            glVertex3f(-k,g,c);
    
            glVertex3f(k,g,-c);
            glVertex3f(k,g,c);
    
            glVertex3f(k,-g,-c);
            glVertex3f(k,-g,c);
    
            glVertex3f(-k,-g,-c);
            glVertex3f(-k,-g,c);
    
            glVertex3f(-k,g,-c);
            glVertex3f(-k,g,c);
            glEnd();
            glBegin(GL_QUADS);
            glVertex3f(k,g,c);
            glVertex3f(-k,g,c);
            glVertex3f(-k,-g,c);
            glVertex3f(-k,-g,c);
            glEnd();
            glBegin(GL_QUADS);
            glVertex3f(-k,g,-c);
            glVertex3f(k,g,-c);
            glVertex3f(k,-g,-c);
            glVertex3f(-k,-g,-c);
            glEnd();
            glEndList();
        }
        float Tr[16];
        glPushMatrix();
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    //glTranslatef((*P)->Location.X,(*P)->Location.Y,(*P)->Location.Z);
        ToGlMatrix(this,Tr);
        glMultMatrixf(Tr);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_POINTS);
        glVertex3f(0.0,0.0,0.0);
        glEnd();
        glCallList(Model);
        glPopMatrix();
}
#endif
