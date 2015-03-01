#ifndef DIY_CRASHDATA_H
#define DIY_CRASHDATA_H
#include <list>
#include <vector>
#include "information.h"
#include "baseclass.h"
#include "crashbase.h"

class CrashData;
class CrashFeekback
{
    friend class CrashData;
    CrashData* Poi;
    XYZF Vector;
    XYZF SpeedVector;
    bool Mode;//TRUE means Initiative;
    operator CrashData*(){return Poi;}
    CrashFeekback(CrashData* P,XYZF& V,XYZF& V2,bool S):Poi(P),Vector(V),SpeedVector(V2),Mode(S){}
    void Set(CrashData* P,XYZF& V,XYZF& V2,bool S){Poi=P;Vector=V;SpeedVector=V2;Mode=S;}
};
class CrashFaceData
{
    public:
        float Distance;
        std::list<CrashFace> FaceData;
        bool JustOnce;
        void Set(const float* Point,int number,std::vector<CrashSingleData>& ValueData,std::list<CrashSingleData>& ValueDataE);
        bool Check(const XYF& Location,std::vector<CrashSingleData>& ValueData,std::list<CrashSingleData>& ValueDataE);
        void FaceAdd(const float* Data,int number);
        CrashFaceData():JustOnce(false){}
        CrashFaceData(bool T):JustOnce(T){}
};
class CrashData:virtual public CrashLocation
{
    protected:
        CrashData(){}
    public:
        unsigned int ID;
        CrashMode Mode;
        CrashStyle Style;
        std::list<CrashData*> CrashList;
        CrashFaceData* CFD;
        bool Crash;
        std::list<CrashFeekback> FeekbackData;
        
        bool (*Function)(const XYZF& Location, float Distance);
        bool (*RegeditFunction)(const XYZF& Location);
        //inline void Set(const float* Poi,int number){Set(Poi,number,ValueData,ValueDataE);}
        inline bool CheckLine(const XYZF&,const XYZF&,CrashFace*);
        bool Check(CrashData*);
        bool CheckLine(CrashData*,const CrashLocation*);
        //inline bool Check(const XYF& Loc){return Check(Loc,ValueData,ValueDataE);}
        bool CheckFace(CrashData* Tem,const CrashLocation& Tec);
        Information Regedit();
        CrashData(const CrashStyle& Tem):Style(Tem)
        {
            CFD=new CrashFaceData(true);
        }
        void Set(CrashFaceData* CF)
        {
            if(CFD!=NULL)
            {
                if(CFD->JustOnce)  delete (CFD);
            }
            if(CF->JustOnce)
            {
                CFD=new CrashFaceData(true);
                *CFD=*CF;
            }else   CFD=CF;
        }
        ~CrashData()
        {
            if(CFD!=NULL)
            {
                if(CFD->JustOnce)  delete (CFD);
            }
        }
        void operator= (const CrashData& C)
        {
            ID=C.ID;
            Style=C.Style;
            Up=C.Up;
            Front=C.Front;
            Left=C.Left;
            Location=C.Location;
            Set(NULL);
            if((C.CFD)->JustOnce)
            {
                CFD=new CrashFaceData(true);
                *CFD=*(C.CFD);
            }
        }
        bool FeekAction(void);
        virtual int InsideAction(void){};
        int (*Action)(CrashData*);
        virtual bool CrashAction(XYZF&){};
        inline void SetFunction(int (*action)(CrashData*)){Action=action;}
        void Feekback(CrashData* P,XYZF& V,XYZF& V2,bool S);
        bool Check(CrashData* Tem,const XYZF& Vector);
        operator CrashLocation(){CrashLocation Tem;Tem.Location=Location;Tem.Up=Up;Tem.Left=Left;Tem.Front=Front;return Tem;}
        /*void CheckTT()
        {
            glColor3f(0.0,1.0,0.0);
            glBegin(GL_LINE_LOOP);
			for(std::vector<CrashSingleData>::iterator Poi=ValueData.begin();Poi!=ValueData.end();++Poi)
			{
				error<<"("<<Poi->Data.X<<","<<Poi->Data.Y<<")"<<" ";
				if(Poi->PE!=NULL) error<<"*";
				glVertex2f(Poi->Data.Y/4.0,Poi->Data.X/4.0);
			}
			error<<"End"<<endl;
			glEnd();
			glColor3f(0.0,1.0,0.0);
            glBegin(GL_POINTS);
			for(std::list<CrashSingleData>::iterator Poi=ValueDataE.begin();Poi!=ValueDataE.end();++Poi)
			{
				error<<"("<<Poi->Data.X<<","<<Poi->Data.Y<<")"<<" ";
				glVertex2f(Poi->Data.Y/4.0,Poi->Data.X/4.0);
			}
			error<<"End"<<endl;
			glEnd();
        }*/
        /*void CheckFace()
        {
            int i=FaceData.size();
            error<<"��ǰ����"<<FaceData.size()<<endl;
            std::list<CrashFace>::iterator Poi=FaceData.begin();
            for(int k=0;k<i;++k)
            {
                error<<"Face:"<<k+1<<endl;
                error<<"Location :("<<Poi->Location.X<<","<<Poi->Location.Y<<","<<Poi->Location.Z<<")"<<endl;
                error<<"��  ("<<Poi->Vector.X<<","<<Poi->Vector.Y<<","<<Poi->Vector.Z<<")"<<endl;
                error<<"��2  ("<<Poi->AuxiliaryVector.X<<","<<Poi->AuxiliaryVector.Y<<","<<Poi->AuxiliaryVector.Z<<")"<<endl;
                
            }
        } */
};
#include "Crashdata.cpp"
#endif
