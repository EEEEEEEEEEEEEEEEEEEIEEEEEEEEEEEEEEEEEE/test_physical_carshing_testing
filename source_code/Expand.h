#ifndef DIY_EXPAND_H
#define DIY_EXPAND_H
enum ExStyle
{
    Brain,
    MissileLancer,
    LaserLancer,
    EggLancer,
    SuperEngine,
};
class PreExpand
{
    public:
        bool Exist;
        int Using; 
        ExStyle Style;
        bool Switch;
        bool Sho;
        std::list<Information> In;
        std::list<Information> Out;
        virtual void Equip(SingleShip*,void* Data){};
        virtual bool Preanalyze(SingleShip*){};
        virtual void Show(SingleShip*,void* Data){Sho=false;};
        virtual void Unequip(SingleShip*,void* Data){};
        PreExpand():Exist(true){}
};
template <class T>
class Expand:public PreExpand
{
    public:
        T* Point;
        virtual void Analyze(SingleShip*){};
        bool Preanalyze(SingleShip* W)
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
        Expand(T* P):Point(P){}
};
#endif
