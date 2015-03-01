#ifndef DIY_BRAIN_H
#define DIY_BRAIN_H
#include "software.h"
#define BCRASH 12
#define BWEAPON 45
#define BINFORMATION 78

class Brain
{
    //Crash* Cr;
    public:
    std::list<Software*> SW;
    std::list<Information> Inf;
    bool Ready;
    public:
        void SetBrain();
        //Information* Inf;
        void Init(SingleShip*,void*);
        void Run(SingleShip*);
        Brain():Ready(false)
        {
            //Software* S=&MC;
            //SW.push_back(S);
            //SW.push_back();
        }
        //void Show(SingleShip*,void*);
        void Analyze(SingleShip*);
};
void Brain::Analyze(SingleShip* SS)
{
        for(std::list<Software*>::iterator Po=SW.begin();Po!=SW.end();++Po)
        {
            if((*Po)->Switch) (*Po)->Analyze(SS,NULL);
        } 
}
void Brain::Init(SingleShip* SS,void* er=0)
{
    for(std::list<Software*>::iterator Po=SW.begin();Po!=SW.end();++Po)
    {
        (*Po)->Init(SS,er);
    }  
}
void Brain::SetBrain()
{
    //Cr=C;
    //In=I;
    Ready=true;
}
#endif
