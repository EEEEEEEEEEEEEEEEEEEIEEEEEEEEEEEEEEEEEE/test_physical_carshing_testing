#ifndef DIY_CRASHDATA_CPP
#define DIY_CRASHDATA_CPP
#include "Crashdata.h"
void CrashFaceData::Set(const float* Point,int number,std::vector<CrashSingleData>& ValueData,std::list<CrashSingleData>& ValueDataE)
{
    if(number>3)
    {
        bool Cricle2=false;
        ValueData.clear();
        ValueDataE.clear();
        if(Point[0]==Point[2*(number-1)]&&Point[1]==Point[2*(number-1)+1])    Cricle2=true;
        void* Memory=NULL;
        float* Temp;
        int k=number;
        if(Cricle2) k-=1;
        float X=0.0;
        float Z=0.0;
        for(int i=0;i<k;++i)
        {
            X+=Point[i*2];
            Z+=Point[i*2+1];
        }
        X/=k;
        Z/=k;
        float TemDistance=0.0;
        int Num;
        for(int i=0;i<k;++i)
        {
            float Tem=XYF(X,Z).Distance(XYF(Point[i*2],Point[i*2+1]));
            if(Tem>TemDistance)
            {
                Num=i;
                TemDistance=Tem;
            }
        }
        Memory=operator new[](sizeof(float)*(k+1)*2);
        Temp=static_cast<float*>(Memory);
        for(int p=0,i=Num;p<k;++i,++p)
        {
            if(i>=k) i=0;
            Temp[p*2]=Point[i*2];
            Temp[p*2+1]=Point[i*2+1];
        }
            Temp[k*2]=Point[Num*2];
            Temp[k*2+1]=Point[Num*2+1];
        std::vector<CrashSingleData> TemData;
        for(int i=0;i<=k;++i)
        {
            CrashSingleData Tem;
            Tem.Data.Set(Temp[i*2],Temp[i*2+1]);
            TemData.push_back(Tem);
        }
        std::vector<CrashSingleData>::iterator P1,P2,P3;
        P1=TemData.begin();
        P2=P1+1;
        P3=P2+1;
        bool Contiunation=false; 
        for(;P3!=TemData.end();)
        {
            if((*ConcaveCheck)(*P1,*P2,*P3))
            {
                CrashSingleData Temcc;
                if(!Contiunation)
                {
                    Temcc=*P1;
                    ValueDataE.push_back(Temcc);
                    P1->AnotherPoint=true;
                    P1->PE=ValueDataE.end();
                    --P1->PE;
                }
                Temcc=*P2;
                ValueDataE.push_back(Temcc);
                P3->PE=ValueDataE.end();
                --P3->PE;
                Contiunation=true;
                P2=P3;
                ++P3;
            }else{
                CrashSingleData Temcc;
                if(Contiunation)
                {
                    Temcc=*P2;
                    ValueDataE.push_back(Temcc);
                    P2->AnotherPoint=true;
                    P2->PE=ValueDataE.end();
                    --P2->PE;
                }
                Contiunation=false;
                if(P1==TemData.begin())  P1->Mode=CRASHBEGIN;
                else P1->Mode=CRASHMIDDLE;
                ValueData.push_back(*P1);
                P1=P2;
                P2=P3;
                ++P3;
            }
        }
        if(P3==TemData.end())
        {
            P1->Mode=CRASHMIDDLE;
            P2->Mode=CRASHEND;
            ValueData.push_back(*P1);
            ValueData.push_back(*P2);
        }
        //CheckTT();
        operator delete[](Memory);
    }else if(number==3)
    {
        for(int i=0;i<3;++i)
        {
            CrashSingleData tr;
            tr.Data.Set(Point[i*2],Point[i*2+1]);
            ValueData.push_back(tr);
        }
    }
}
bool CrashFaceData::Check(const XYF& Point,std::vector<CrashSingleData>& ValueData,std::list<CrashSingleData>& ValueDataE)
{
    /*glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2f(Point.Y/4.0,Point.X/4.0);
    glEnd();*/
    std::vector<CrashSingleData>::iterator P1;
    std::vector<CrashSingleData>::iterator P2;
    if(!ValueData.empty())
    {
        bool Inside=true;
        float Dis=0.0;
        for(P1=ValueData.begin(),P2=ValueData.begin()+1;P2!=ValueData.end();P1=P2,++P2)
        {
            XYF PP1=*P2-*P1;
            XYF PP2=Point-*P1;
            XYF PP3(PP1.Y,-PP1.X);
            //error<<PP3.X<<" "<<PP3.Y<<"     X     "<<PP2.X<<" "<<PP2.Y<<" "<<endl;
            if(PP3*PP2<0)   Inside=false;
            else{
                //error<<"ï¿½Ú¶ï¿½ï¿½ï¿½ï¿½Ğ¶Ï°ï¿½"<<endl;
                if(P1->AnotherPoint&&P2->AnotherPoint)
                {
                    bool OutSide=true;
                    std::list<CrashSingleData>::iterator I=P2->PE;
                    //if(!Inside) error<<"zheli jiu meiyou le"<<endl;
                    //if(!OutSide) error<<"woshiegSB"<<endl;
                    //error<<"sdfsdf"<<endl;
                    while(I!=P1->PE)
                    {
                        if(!OutSide) break;
                        //error<<"12213212"<<endl;
                        XYF T1=*I;
                        I--;
                        XYF P2=*I-T1;
                        XYF P3=Point-T1;
                        XYF P4(P2.Y,-P2.X);
                        if(P4*P3<0) OutSide=false;
                    }
                    if(OutSide) Inside=false;
                }
                //if(Inside) error<<"jiushuoyige"<<endl;
                //else error<<"zhenshiwa"<<endl;
            }
            if(!Inside) break;    
        }
        //if(!Inside) error<<"dasfdfhfghghghjfgesfa"<<endl;
        return Inside;
    }
    return false;
}
//ï¿½Ñ²ï¿½ï¿½ï¿½ 
bool CrashData::CheckFace(CrashData* Tem,const CrashLocation& Tec)//Î´ï¿½ê£¬Î´ï¿½ï¿½ï¿½ï¿½ 
{
    //error<<"Point~"<<endl;
    if(CFD->Distance<=0||Tem->CFD->Distance<=0)  return false;
    std::list<CrashFace>::iterator P1 =CFD->FaceData.begin();
    std::list<CrashFace>::iterator P2 = Tem->CFD->FaceData.begin();
    //error<<"Point~"<<endl;
    std::list< std::list<CrashFace>::iterator  > Face1;
    std::list< std::list<CrashFace>::iterator  > Face2;
    XYZF Vector=Tem->Location-Tec.Location;
    for(;P1!=CFD->FaceData.end();++P1)
    {
        XYZF V1=Tec.VectorFromCoordinate(P1->Up); 
        if(V1*Vector>0)
        {
            Face1.push_back(P1);
        }
    }
    for(;P2!=Tem->CFD->FaceData.end(); ++P2)
    {
        XYZF V2=Tem->VectorFromCoordinate(P2->Up);
        if(V2*Vector<0)
        {
            Face2.push_back(P2);                   
        }                                                                                         
    }
    //error<<Face1.size()<<endl;
    //error<<Face2.size()<<endl;
    std::list< std::list<CrashFace>::iterator  >::iterator Face11=Face1.begin();
    std::list< std::list<CrashFace>::iterator  >::iterator Face22;
    for(;Face11!=Face1.end();++Face11)//this way!!!!!!!!!!
    {
        std::list< CrashFace >::iterator Tem1=*Face11;
        for(Face22=Face2.begin();Face22!=Face2.end();++Face22)
        {
            std::list< CrashFace >::iterator Tem2=*Face22;
            std::vector<CrashSingleData>::iterator P1=Tem1->Data.begin();
            std::vector<CrashSingleData>::iterator P2=Tem2->Data.begin();
            std::list<XYZF> Num;
            bool temright=true;
            //error<<"size of Face"<<(*Tem2).Data.size()<<endl;
            for(;P1!=Tem1->Data.end();++P1)
            {
                XYZF Tes=P1->Data.X*Tem1->Left+P1->Data.Y*Tem1->Front+Tem1->Location;
                Tes=Tec.FromCoordinate(Tes);
                XYZF er=Tem->ToCoordinate(Tes);
                er=Tem2->ToCoordinate(er);
                //error<<"<"<<er.X<<","<<er.Y<<","<<er.Z<<")"<<endl;
                Num.push_back(er);
                XYF Te2(er.X,er.Z);
                //error<<"×îĞÂĞŞ¸Ä"<<endl; 
                if(Te2.Long()<=Tem2->Distance)
                {
                    //error<<"¾ÍÊä³öÊÔÊÔ"<<endl; 
                    if(CFD->Check(Te2,Tem2->Data,Tem2->DataE))
                    {
                        //error<<"ÊÇÕâÀïµÄÎÊÌâÃ´"<<endl;
                        temright=false;
                    //error<<"sdhkfksdf"<<er.Z<<endl;
                    //if((er.Z)*(pr.Z)<=0)
                        if(er.Y<=0)//||pr.Z<=0)//for text
                        {
                        //Feekback(Tem,V2,Vector,true);
                        //Tem->Feekback(this,V,Vector,true);
                            return true;//ï¿½ï¿½ï¿½Ê±ï¿½ï¿½ï¿½Ê¾ï¿½ï¿½×²ï¿½Ë£ï¿½Òªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½×²ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 
                        }
                    }
                    //error<<"pia pia pua~"<<endl;
                } 
            }
            //error<<"jie shu "<<endl;
            std::list<XYZF>::iterator Poi1=Num.begin();
            std::list<XYZF>::iterator Poi2=Poi1;
            ++Poi2;
            //error<<"ÊÇÕâÀïµÄÎÊÌâÃ´122"<<endl;
            for(;Poi2!=Num.end()&&Poi1!=Num.end();++Poi1,++Poi2)
            {
                //error<<"bushi !!!??"<<endl; 
                if(Tem->CheckLine(*Poi1,*Poi2,&(*Tem2))) return true;
            }
            //error<<"Point~"<<endl;
            Num.clear();
            //error<<"bushi !!!?233213411243?"<<endl; 
            if(temright)
            {
                //error<<"lalala"<<endl ;
                for(;P2!=Tem2->Data.end();++P2)
                {
                    XYZF Tes=P2->Data.X*Tem2->Left+P2->Data.Y*Tem2->Front+Tem2->Location;
                    XYZF Tee=Tem->FromCoordinate(Tes);
                    XYZF er=Tec.ToCoordinate(Tee);
                    er=Tem1->ToCoordinate(er);
                    Num.push_back(er);
                    //XYZF ui=C2.ToCoordinate(Tee);
                    XYF Te2(er.X,er.Z);
                    if(Te2.Long()<=Tem1->Distance)
                    {
                        if(CFD->Check(Te2,Tem1->Data,Tem1->DataE))
                        {
                            if(er.Y<=0)//||ui.Z<=0)
                            {
                            //Feekback(Tem,V2,Vector,true);
                            //Tem->Feekback(this,V,Vector,true);
                                return true;//ï¿½ï¿½ï¿½Ê±ï¿½ï¿½ï¿½Ê¾ï¿½ï¿½×²ï¿½Ë£ï¿½Òªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½×²ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 
                            }
                        }
                    }
                }
                std::list<XYZF>::iterator Poi1=Num.begin();
                std::list<XYZF>::iterator Poi2=Poi1;
                ++Poi2;
                //error<<"µ½µ×ÊÇÄÄÀïÓĞ´íÎó°¡£¡£¡"<<endl;
                for(;Poi2!=Num.end();++Poi1,++Poi2)
                {
                    if(Tem->CheckLine(*Poi1,*Poi2,&(*Tem1))) return true;
                }
            }
            //error<<"**NoCrash"<<endl;
        }
        //ï¿½ï¿½İ¿ï¿½È± 
    }
    return false;
    //ï¿½ï¿½İ¿ï¿½È±                                                                      
}
void CrashFaceData::FaceAdd(const float* Data,int number)
{
    if(number>=3)
    {
        CrashFace Tem;
        std::list<XYZF> Te;
        for(int i=0;i<number;++i)
        {
            XYZF De(Data[i*3],Data[i*3+1],Data[i*3+2]);
            Te.push_back(De);
            float Tc=sqrt(De*De);
            if(Tc>Distance) Distance=Tc;
        }
        
        
        
        std::list<XYZF>::iterator Tp=Te.begin();
        std::list<XYZF>::iterator Tmax;
        std::list<XYZF>::iterator Tnext;
        XYZF Dis(0.0,0.0,0.0);
        for(;Tp!=Te.end();++Tp)
        {
            Dis=Dis+*Tp;
        }
        Dis=Dis*(1.0/number);
        //error<<"<"<<Dis.X<<" "<<Dis.Y<<"  "<<Dis.Z<<">"<<endl;
        float LostDis=0.0;
        float TemDis=0.0;
        for(Tp=Te.begin();Tp!=Te.end();++Tp)
        {
            TemDis=Dis.Distance(*Tp);
            if(TemDis>LostDis)
            {
                LostDis=TemDis;
                Tmax=Tp;
                Tnext=Tmax;
                ++Tnext;
                if(Tnext==Te.begin())
                {
                    Tnext=Tmax;
                    --Tmax;
                }
            }
        }
        Tem.Distance=LostDis;
        Tem.Location=Dis;
        XYZF AV=(*Tmax-Dis).Uint();
        
        
        //error<<"sajhdkjfhakshfkjsadhf"<<"<"<<AV.X<<" "<<AV.Y<<"  "<<AV.Z<<">"<<endl;
        
        Tem.Left=AV;
        XYZF AV2=(*Tnext-*Tmax).Uint();
        Tem.Up=(AV&AV2).Uint();
        //error<<"sajhdkjfhakshfkjsadhf"<<"<"<<Tem.Up.X<<" "<<Tem.Up.Y<<"  "<<Tem.Up.Z<<">"<<endl;
        Tem.Front=(Tem.Left&Tem.Up).Uint();
        
        
        
        
        
        //error<<"  ¾ÍÊÇÕâÑùµÄËµ  "<<endl;
        //Tem.AuxiliaryVector2=AV2;
        void* Data=operator new[](sizeof(float)*3*number);
        float* Point=static_cast<float*>(Data);
        Tp=Te.begin();
        for(int i=0;Tp!=Te.end()&&i<number;++Tp,++i)
        {
            XYZF Trr=Tem.ToCoordinate(*Tp);
            Point[i*2]=Trr.X;
            Point[i*2+1]=Trr.Z;
            //error<<"<"<<Point[i*2]<<","<<Point[i*2+1]<<">"<<endl;
        }
        Set(Point,number,Tem.Data,Tem.DataE);
        FaceData.push_back(Tem);
        operator delete[](Data);
    }
}
void CrashData::Feekback(CrashData* P,XYZF& V,XYZF& V2,bool S)
{
    Crash=true;
    CrashFeekback Feekback(P,V,V2,S);
    FeekbackData.push_front(Feekback);
}
bool CrashData::FeekAction(void)
{
    switch(this->Style)
    {
        case Dead:
        case DeadTem:
            /*if(Action!=NULL)
            {
                
            }else{
                return false;
            }*/
            break;
        case Live:
            break;
        case Limited:
            break;
        case Map:
            break;
    }
}
bool CrashData::Check(CrashData* Tem)//ï¿½Ğ¶ï¿½}ï¿½ï¿½DATAï¿½Ç·ï¿½ï¿½ï¿½ï¿½ï¿½ 
{
    XYZF De=Tem->Location-Location;
    float Tr=sqrt(De*De);
    if(Tr<Tem->CFD->Distance+CFD->Distance) return true;
    else return false;
}
bool CrashData::CheckLine(const XYZF& L1,const XYZF& L2,CrashFace* CF)
{
    if(L1.Y*L2.Y<=0)
    {
        XYZF P1=L2-L1;
        float K=-L1.Y/(L2.Y-L1.Y);
        P1=K*P1+L1;
        XYF Ter(P1.X,P1.Z);
        if(Ter.Long()<=CF->Distance) return CFD->Check(Ter,CF->Data,CF->DataE);
    }
    return false;
}
bool CrashData::CheckLine(CrashData* Tem,const CrashLocation* Tec)
{
    const XYZF& L1=Location;
    const XYZF& L2=Tec->Location;
    const XYZF& L3=Tem->Location;
    float D=CFD->Distance+Tem->CFD->Distance;
    if(Tem->Location.Distance(Tec->Location,Location)<=D)
    {
        if(L3.Distance(L1)<=D||L3.Distance(L2)<=D||(L3-L1)*(L3-L2)<0)
        {
            std::list<CrashFace>::iterator P1 =CFD->FaceData.begin();
            std::list<CrashFace>::iterator P2 = Tem->CFD->FaceData.begin();
            std::list< std::list<CrashFace>::iterator  > Face1;
            std::list< std::list<CrashFace>::iterator  > Face2;
            XYZF Vector=Tem->Location-Tec->Location;
            for(;P1!=CFD->FaceData.end();++P1)
            {
                XYZF V1=Tec->VectorFromCoordinate(P1->Up); 
                if(V1*Vector>0)
                {
                    Face1.push_back(P1);
                }
            }
            for(;P2!=Tem->CFD->FaceData.end(); ++P2)
            {
                XYZF V2=Tem->VectorFromCoordinate(P2->Up);
                if(V2*Vector<0)
                {
                    Face2.push_back(P2);                   
                }                                                                                         
            }
            std::list< std::list<CrashFace>::iterator  >::iterator Face11;
            std::list< std::list<CrashFace>::iterator  >::iterator Face22;
            for(Face11=Face1.begin();Face11!=Face1.end();++Face11)
            {
                std::list<CrashFace>::iterator A1=*Face11;
                std::list<XYZF> P1;
                std::list<XYZF> P2;
                for(std::vector<CrashSingleData>::iterator B1=A1->Data.begin();B1!=A1->Data.end();++B1)
                {
                    XYZF T(B1->Data.X,0.0,B1->Data.Y);
                    T=A1->FromCoordinate(T);
                    XYZF T1=FromCoordinate(T);
                    XYZF T2=FromCoordinate(T);
                    P1.push_back(T1);
                    P2.push_back(T2);
                }
                for(Face22=Face2.begin();Face22!=Face2.end();++Face22)
                {
                    std::list<CrashFace>::iterator A2=*Face22;
                    std::list<XYZF>::iterator PP1;
                    std::list<XYZF>::iterator PP2;
                    for(PP1=P1.begin(),PP2=P2.begin();PP1!=P1.end()&&PP2!=P2.end();++PP1,++PP2)
                    {
                        XYZF T1=Tem->ToCoordinate(*PP1);
                        T1=A2->ToCoordinate(T1);
                        XYZF T2=Tem->ToCoordinate(*PP2);
                        T2=A2->ToCoordinate(T2);
                        if(Tem->CheckLine(T1,T2,&(*A2))) return true;
                    }
                }
            }
        }
    }
    return false;
}
//å…³äºåæ ‡çš„è½¬æ¢å·¥ä½œç°å·²é‡æ–°æ›´æ–°ï¼Œä¸ºäº†ä¿æŒç•Œé¢ç®€æ´ï¼Œè¦é‡å†™Checkå‡½æ•°
#endif
