#ifndef DIY_MOTION_H
#define DIY_MOTION_H
//#include <match>
#include "baseclass.h"
/*class Motion
{
    XYZF Direction;
    float Speed;
    float Quality;
    float Parameter;
    inline void VToF(const XYZF& , const float*);
    inline void FToV(XYZF& , const float*);
    XYZF pow(const XYZF&,float);
    XYZF Multiplication(const XYZF&, const XYZF&);
    public:
        Motion():Quality(1.0),Parameter(1.0){}
        //void Crash(Motion*);
};*/
enum MoveStyle
{
    M_Null=0,
    M_Front=1, //FV,FA,FL,DA,DL,HV,VV
    M_Horizontal=2, //FV,DV,HV,HA,HL,VV
    M_Vertical=4, //FV,DV,HV,VV,VA,VL
    M_All=7//FV,FA,FL,DA,DL,HV,HA,HL,VV,VA,VL
};
enum AngleStyle
{
    F_Null=0,
    F_Horizontal=1, //FV,DV,HV,HA,HL,VV
    F_Vertical=2, //FV,DV,HV,VV,VA,VL
    F_Oclock=4,
    F_All=7
};
class Speed
{
    public:
        float F;
        float L;
        float U;
};
class Translation
{
    public:
        bool Move[6];//f,d,l,r,u,d 
        float TranslationData[8];
        MoveStyle Style;
        void SetTranslation(MoveStyle,float*);
        Translation()
        {
            for(int i=0;i<6;++i)
            {
                Move[i]=false;
            }
        };
        void Change(long,Speed*,Coordinate*);
        Translation operator+ (const Translation& TT)
        {
            Translation Tr=*this;
            for(int i=0;i<8;++i)
            {
                Tr.TranslationData[i]=TranslationData[i]+TT.TranslationData[i];
            }
            return Tr;
        }
};
class Angle
{
    public:
        float C;
        float R;
        float F;
};
class FaceAngle
{
    public:
        AngleStyle Style;
        bool AngleT[6];
        float AngleData[6];
        void SetAngle(float*);
        void Change(long,Angle*,Coordinate*);
        FaceAngle()
        {
            for(int i=0;i<6;++i)
            {
                AngleT[i]=false;
            }
        }
        FaceAngle operator+(const FaceAngle& Tc)
        {
            FaceAngle Te=*this;
            for(int i=0;i<6;++i)
            {
                Te.AngleData[i]=AngleData[i]+Tc.AngleData[i];
            }
        }
};
class Movement:public Translation,public FaceAngle
{
    public:
        void Change(long Tf,Speed* S,Coordinate* C)
        {
            Angle Te;
            Translation::Change(Tf,S,C);
            FaceAngle::Change(Tf,&Te,C);
        }
        Movement operator+(const Movement& Mv)
        {
            Movement Mo=*this;
            for(int i=0;i<8;++i)
            {
                Mo.TranslationData[i]=TranslationData[i]+Mv.TranslationData[i];
            }
            for(int i=0;i<6;++i)
            {
                Mo.AngleData[i]=AngleData[i]+Mv.AngleData[i];
            }
            return Mo;
        }
        Movement operator-(const Movement& Mv)
        {
            Movement Mo=*this;
            for(int i=0;i<8;++i)
            {
                Mo.TranslationData[i]=TranslationData[i]-Mv.TranslationData[i];
            }
            for(int i=0;i<6;++i)
            {
                Mo.AngleData[i]=AngleData[i]-Mv.AngleData[i];
            }
            return Mo;
        }
        Movement(){}
        Movement(MoveStyle MS,float* T,float* Y)
        {
            SetTranslation(MS,T);
            SetAngle(Y);
        }
        //Movement(MoveStyle W,float* E,float* R):Tarnslation(W,E){FaceAngle::Set(R);}
};
#include "motion.cpp"
#endif
