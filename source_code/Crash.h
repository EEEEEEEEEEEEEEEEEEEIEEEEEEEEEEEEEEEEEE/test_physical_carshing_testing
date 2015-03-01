#ifndef DIY_CRASH_H
#define DIY_CRASH_H
#include "CrashBase.h"
#include "CrashData.h"
#include "CrashMap.h"
class CrashBlock
{
    public:
        XYF Size;
        XYF Size2;
        std::list<CrashData*> Point;
        XYF Get(int Mode)
        {
            XYF Te;
            switch(Mode)
            {
                case 1:
                    Te.Set(Size.X,Size.Y);
                    break;
                case 4:
                    Te.Set(Size2.X,Size2.Y);
                    break;
                case 2:
                    Te.Set(Size2.X,Size.Y);
                    break;
                case 3:
                    Te.Set(Size.X,Size2.Y);
                    break;
            }
            return Te;
        }
        void Text(CrashData* Tr);
        void Delete(CrashData* Tr);
        void Check(CrashData*);
        CrashBlock(){}
        CrashBlock(float X1,float Y1,float X2,float Y2):Size(X1,Y1),Size2(X2,Y2){}
};
class CrashRelationship
{
    public:
        CrashData* Frist;
        CrashData* Second;
};
class Crash
{
    std::list<CrashBlock> BlockData;
    std::list<CrashData*> LiveData;
    std::list<CrashData*> TemDeadData;
    std::list<CrashData*> WaitingList;
    CrashMap* MapPoi;
    public:
        void ChangeMap(CrashMap* Poi);
        void Regedit(CrashData* Poi);
        Information Check(CrashData* Tem,const CrashLocation*,CrashData* Tcc);
};
#endif
