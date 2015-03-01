#ifndef DIY_SPECIALPOINT_H
#define DIY_SPECIALPOINT_H
#include "list.h"
class PrePoint
{
    friend class SpecialPoint;
    bool Exist;
    std::list<PrePoint*> Point;
    std::list<PrePoint*> BePointed;
    PrePoint(PrePoint* PP)
    {
        PP->BePointed.push_back(this);
        Point.push_back(PP);
    }
    virtual void Delete()=0;
    virtual void PointAt(PrePoint* PP)
    {
        bool In=true;
        std::list<PrePoint>::iterator Po;
        for(Po=Point.begin();Po!=Point.end();++Po)
        {
            if(*Po==PP)
            {
                In=false;
                break;
            }
        }
        if(In)  Point.push_back(PP);
        In=true;
        for(Po=BePointed.begin();Po!=BePointed.end();++Po)
        {
            if(*Po==this)
            {
                In=false;
                break;
            }
        }
        if(In)  BePointed.push_back(PP);
    }
    ~PrePoint()
    {
        bool In=true;
        std::list<PrePoint>::iterator Po;
        std::list<PrePoint>::iterator Po2;
        for(Po=Point.begin();Po!=Point.end();++Po)
        {
            for(Po=Point.begin();Po!=Point.end();++Po)
            {
                if(*Po==PP)
                {
                    In=false;
                    break;
                }
            }
        }
        if(In)  Point.push_back(PP);
        In=true;
        for(Po=BePointed.begin();Po!=BePointed.end();++Po)
        {
            if(*Po==this)
            {
                In=false;
                break;
            }
        }
        if(In)  BePointed.push_back(PP);
    }
};
#endif;
