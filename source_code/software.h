#ifndef DIY_SOFTWARE_H
#define DIY_SOFTWARE_H
class SingleShip;
class Software
{
    public:
        int DataMode;
        bool Switch;
        std::list<Software*> Income;
        virtual void Init(SingleShip* S,void* V){}
        virtual void Analyze(SingleShip* S,void* V){}
        Software():Switch(true){}
};
#endif
