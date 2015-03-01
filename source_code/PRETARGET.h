#ifndef DIY_PRETARGET_H
#define DIY_PRETARGET_H
#include "baseclass.h"
class TargetSeed;
class TargetTree
{
    friend class TargetSeed;
    std::list<TargetSeed*> Land;
    Coordinate* C;
    public:
        TargetTree(Coordinate* Cp):C(Cp){}
        Coordinate* operator->() const{return C;}
        ~TargetTree();
};
class TargetSeed
{
    friend class TargetTree;
    bool Switch;
    TargetTree* TT;
    Coordinate* Point;
    public:
        TargetSeed(TargetTree* T):Point(T->C),Switch(false),TT(T)
        {
            T->Land.push_back(this);
        }
        Coordinate* operator->() const{return Point;}
        ~TargetSeed()
        {
            if(Switch)
            {
                delete Point;
            }else{
                for(std::list<TargetSeed*>::iterator Po=TT->Land.begin();Po!=TT->Land.end();++Po)
                {
                    if((*Po)==this)
                    {
                        TT->Land.erase(Po);
                        break;
                    }
                }
            }
        }
};


TargetTree::~TargetTree()
{
    for(std::list<TargetSeed*>::iterator Po=Land.begin();Po!=Land.end();++Po)
    {
        (*Po)->Point=new Coordinate(*C);
        (*Po)->Switch=true;
    }
}
#endif
