#ifndef DIY_WEAPON_MISSILE_H
#define DIY_WEAPON_MISSILE_H
#include "Weapon.h"
class Missile:public Speed,public Coordinate,public WeaponSeed<Missile>
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
        int Situation;
        TargetSeed Target;
        TargetSeed Resource;
        Coordinate Move(long);
        void Show(Weapon*);
        void Analyze(Weapon*);
        void Init(void);
        Missile::Missile(TargetTree* T1,TargetTree* T2):Resource(T1),Target(T2),WeaponSeed<Missile>(this)
        {
            Location=Resource->Location;
            Up=Resource->Up;
            Front=Resource->Front;
            Left=Resource->Left;
        }
        //Missile():WeaponSeed<Missile>(this){}
};
float Mis[8]={4.0,4.0,0.5,-1.0,0.0,0.0,0.0,0.0};
float MisA[6]={0.0,0.1,0.0,0.1,0.0,0.1};
Movement Missile::Mo(M_Front,Mis,MisA);
long Missile::Time(30000);
int Missile::Damage(10);
int Missile::EnergyCost(10);
int Missile::ID(0);
int Missile::Model(-1);
Coordinate Missile::Move(long Time)
{
    Coordinate Tem=*this;
    //error<<" ghfdgfdg "<<Tem.Location.X<<"  "<<Tem.Location.Y<<"  "<<Tem.Location.Z <<endl;
    XYZF T1=Target->Location-Tem.Location;
    if(T1*Tem.Front>=0)
    {
        Mo.Move[0]=true;
        Mo.Move[1]=false;
    }else{
        Mo.Move[0]=false;
        Mo.Move[1]=true;
    }
    if(T1*Tem.Left>0)
    {
        Mo.AngleT[2]=true;
        Mo.AngleT[3]=false;
    }else if(T1*Tem.Left<0)
    {
        Mo.AngleT[2]=false;
        Mo.AngleT[3]=true;
    }else{
        Mo.AngleT[2]=false;
        Mo.AngleT[3]=false;
    }
    if(T1*Tem.Up<0)
    {
        Mo.AngleT[4]=true;
        Mo.AngleT[5]=false;
    }else if(T1*Tem.Up>0)
    {
        Mo.AngleT[4]=false;
        Mo.AngleT[5]=true;
    }else{
        Mo.AngleT[4]=false;
        Mo.AngleT[5]=false;
    }
    Mo.Change(10,this,&Tem);
    return Tem;
}
void Missile::Show(Weapon* W)
{
    if(Exist)
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
}
void Missile::Analyze(Weapon* W)
{
    if(Exist)
    {
        if(W->LastTime-LastTime>=Time)
        {
            Exist=false;
        }else{
            Coordinate Tr=Move(W->LastTime-LastTime);
            if((Location-Target->Location).Long()<=0.5)
            {
                Exist=false;
                    //error<<"sadasf"<<endl;
            }else{
                Location=Tr.Location;
                Up=Tr.Up;
                Front=Tr.Front;
                Left=Tr.Left;
            }
        }
    }
}
#endif
