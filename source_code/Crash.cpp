#ifndef DIY_CRASH_CPP
#define DIY_CRASH_CPP
#include "Crash.h"
void Crash::ChangeMap(CrashMap* Poi)//传入的应该是类型为OccypuMap类型的指针 
{
    if(Poi->X>=1&&Poi->Z>=1&&Poi->MaxX>Poi->MinX&&Poi->MaxZ>Poi->MinZ)
    {
        BlockData.clear();
        LiveData.clear();
        float X1=Poi->MaxX;
        float X2=Poi->MinX;
        float Z1=Poi->MaxZ;
        float Z2=Poi->MinZ;
        unsigned int x=Poi->X;
        unsigned int z=Poi->Z;
        float EachX=(X1-X2)/x;
        float EachZ=(Z1-Z2)/z;
        std::list<XYF> DX;
        std::list<XYF> DY;
        float TX=X1;
        for(int k=0;k<x;++k)
        {
            XYF Tr(TX,TX-EachX);
            DX.push_back(Tr);
            TX=TX-EachX;
        }
        DX.push_back(XYF(TX,X2));
        float TZ=Z1;
        for(int k=0;k<z;++k)
        {
            XYF Tr(TZ,TZ-EachZ);
            DZ.push_back(Tr);
            TZ=TZ-EachZ;
        }
        DZ.push_back(XYF(TZ,Z2));
        for(std::list<XYF>::iterator Poi=DX.begin();Poi!=DX.end();++Poi)
        {
            for(std::list<XYF>::iterator Poi2=DZ.begin();Poi!=DZ.end();++Poi)
            {
                CrashBlock Tc(Poi->Y,Poi2->Y,Poi->X,Poi2->X);
                BlockData.push_back(Tc);
            }
        }
        MapPoi=Poi;
    }
}
void CrashBlock::Check(CrashData* Poi)
{
    float& DI=Poi->Distance;
    float& LX=Poi->Location.X;
    float& LY=Poi->Location.Z;
    float XB=Size.X>Size2.X ? Size.X:Size2.X;
    float XS=Size.X<Size2.X ? Size.X:Size2.X;
    float XD=XB-XS+2*DI;
    float YB=Size.Y>Size2.Y ? Size.Y:Size2.Y;
    float YS=Size.Y<Size2.Y ? Size.Y:Size2.Y;
    float YD=YB-YS+2*DI;
    if((abs(LX-DI-XB)<XD||abs(LX+DI-XS)<XD)||(abs(LY-DI-YB)<YD||abs(LY+DI-YS)<YD)) return true;
    else return false;
}
void CrashBlock::Text(CrashData* Poi)
{
    if(Check(Poi))
    {
        Point.push_back(Poi);
        break;
    }
}
void CrashBlock::Delete(CrashData* Poi)
{
    if(!Point.empty())
    {
        std::list<CrashData*>::iterator Ty=Point.begin();
        for(;Ty!=Point.end();++Ty)
        {
            if(*Ty==Poi)
            {
                Point.earse(Ty);
                break;
            }
        }
    }
}
void Crash::Regedit(CrashData* Poi)
{
    switch(Style)
    {
        case Limited:
        case Dead:
            std::list<BlockData>::iterator Poi=BlockData.begin();
            for(;Poi!=Block.end();++Poi)    Poi->Text(*Poi);
            break;
        case Live:
            LiveData.push_back(Poi);
            break;
    }
}
Information Crash::Check(CrashData* Tem,const CrashLocation* Ter,CarshData* Tcc=NULL)
{
    if(MapPoi!=NULL)
    {
        Tem->CrashList.clear();
        bool OutPut=false;
        if(!MapPoi->Data.empty())
        {
            if(!Check(Tem))
            {
                Information Ter;
                Tre.Category1=CRASHOUMAP;
                Tre.Category2=(*Ty)->Style;
                Tre.Data1=static_cast<void*>(*Ty);
                return Tre;
            }
            for(std::list<CrashData*>::iterator Ty=LiveData.begin();Ty!=LiveData.end();++Ty)//判断自由物体 
            {
                if(*Ty!=Tcc&&*Ty!=Tem)
                {
                    if(Tem->Check(*Ty))
                    {
                        if(Tem->CheckFace(*Ty,Ter))
                        {
                            Tem->CrashList.push_back(*Ty);
                            OutPut=true;
                        }//输出，面碰撞了 
                    }
                }
            }
            for(std::list<CrashData*>::iterator Ty=TemDeadData.begin();Ty!=TemDeadData.end();++Ty)//判断临时自由物体 
            {
                if(*Ty!=Tcc&&*Ty!=Tem)
                {
                    if(Tem->Check(*Ty))
                    {
                        if(Tem->CheckFace(*Ty,Vector))
                        {
                            Tem->CrashList.push_back(*Ty);
                            OutPut=true;
                        }//输出，面碰撞了 
                    }
                }
            }
            for(std::list<CrashBlock>::iterator Tr=BlockData.begin();Tr!=BlockData.end();++Tr)//判断限制物体 
            {
                for(int i=1;i<=4;++i)
                {
                    if(Tr->Check(Tem))
                    {
                        for(std::list<CrashData*>::iterator Ui=Tr->Point.begin();Ui!=Tr->Point.end();++Ui)
                        {
                            if(Tem-Check(*Ui))
                            {
                                if(Tem->CheckFace(*Ui,Vector))
                                {
                                    Tem->CrashList.push_back(*Ty);
                                    OutPut=true;
                                }//输出，碰撞了 
                            }
                        }
                    }
                }
            }
            if(OutPut)
            {
                Information Ter;
                Tre.Category1=CRASHFACE;
                Tre.Category2=(*Ty)->Style;
                Tre.Data1=static_cast<void*>(*Ty);
                return Tre;
            }
            Information Fr;
            Fr.Category1=CRASHNOCRASH;
            return Fr;
        }
    }
    Information Fr;
    Fr.Category1=CRASHNODATA;
    return Fr;
}
#endif
