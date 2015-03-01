#ifndef DIY_CONTROLCENTER_CPP
#define DIY_CONTROLCENTER_CPP
#include "ControlCenter.h"
bool ControlCenter::SetView(int Mode)
{
    switch(Mode)
    {
        case 1:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(-1.0,1.0,-1.0,1.0);
            return true;
            break;
        case 2:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1,1,-1,1,1,-1);
            glMatrixMode(GL_MODELVIEW);
            return true;
            break;
        case 3:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(Angle,static_cast<float>(WindowW)/WindowH,NearSize,FarSize);
            glMatrixMode(GL_MODELVIEW);
            return true;
            break;
    }
    return false;
}
unsigned int ControlCenter::Asp(void)
{
    return Aspect;
}

bool ControlCenter::Init(int Mode=1,int W=640,int H=480)
{
    if(RegeditReady)
    {
        WindowW=W;
        WindowH=H;
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );//设定GL的初始属性，想使用GL的话必须用这个，其中参数自己百度
        Screen = SDL_SetVideoMode( WindowW, WindowH, 32, SDL_OPENGL); // 同上，设定属性的另一函数，必要。其参数自己百度
        
        Far=FarSize;
        Near=NearSize;
        NX=Near*tan(Angle*0.03490);
        FX=Far*tan(Angle*0.03490);
        NY=NX*WindowY()/WindowX();
        FY=FX*WindowY()/WindowX();
        
        if(!FunctionLibrary.empty())
        {
            for(std::list<Plugin_Base*>::iterator Poi=FunctionLibrary.begin();Poi!=FunctionLibrary.end();++Poi)
            {
                (*Poi)->Init(this);
            }
        }
        Thread1=SDL_CreateThread(Thread_1_Function,(void*) this);
        Thread2=SDL_CreateThread(Oclock,(void*) this);
        //TimeID=SDL_AddTimer(5,Oclock,(void*)this);
        StarTime=SDL_GetTicks();
        if(!SetView(Mode))    SetView(1);
        
    }
}



void ControlCenter::GetReady(void (*Temporary)(ControlCenter& This))
{
    (*Temporary)(*this);
}

int ControlCenter::CheckInf(Information& Temp)
{
    std::vector< Information >::const_iterator Poi;
    if(!FastShoot.empty())
    {
        for(Poi=FastShoot.begin();Poi!=FastShoot.end();++Poi)
        {
            if( Poi->Target==Temp.Target && Call(Temp.Target)!=NULL)
            {
                if( (Poi->Category1==Temp.Category1||Poi->Category1==-999)
                  &&(Poi->Category2==Temp.Category2||Poi->Category2==-999)
                  &&(Poi->Category3==Temp.Category3||Poi->Category3==-999))
                {
                    if(NaTarIP.count(Temp.Target)!=0)
                    {
                        Call(Temp.Target)->Library.push_back(Temp);
                        return 1;
                    }
                }
            }
        }
    }
    DeliverLibrary.push_back(Temp);
    return 2;
}

void ControlCenter::Finish(void)
{
    SDL_Delay( DelayForShow );//暂停~~~~
    Calculate+=1;
    if(Calculate>=2000001)
        Calculate=0;
    int Time=SDL_GetTicks()-TimeForShow;
    if(Time>=22&&DelayForShow>=1)
    {
        DelayForShow-=1;
    }else if(Time<18&&DelayForShow>=0)
    {
        DelayForShow+=1;
    }
}
        
void ControlCenter::Run(int number=0)
{
    if(Running)
    {
        TimeForShow=SDL_GetTicks();
        while(!MainLibrary.empty())
        {
                    //er<<"Win!!!"<<endl;
            Information Tempp=*MainLibrary.begin();
                    //check("sss",Tempp);
            MainLibrary.pop_front();
                if(Tempp.Category1==INFCONZJ)
                {
                    SetView(2);
                }else if(Tempp.Category1==INFCONTS)
                {
                    SetView(3);
                }else if(Tempp.Category1==INFUNABLEEXITIMI)
                {
                    ExitImi=false;
                }
                    
            if(Tempp.Category2==INFEXIT&&Tempp.Category1==INFEVENT)
            {
                Running=false;
                while((!TimeReadyToExit)||(!AnalyzeReadyToExit)){SDL_Delay(1);}
                SDL_KillThread(Thread1);
                SDL_KillThread(Thread2);
                //SDL_RemoveTimer(TimeID);
                //exit(0);
            }
        }
        while( SDL_PollEvent( &Event) ) 
        {
            Information Temporary;
            Temporary.Resource=INFCONID;
            Temporary.Target=INFALL;
            Temporary.Category1=INFEVENT;
            float Temporary2[1];
            switch(Event.type)
            {
                case SDL_QUIT:
                    //Running = false;
                    Temporary.Category2=INFEXIT;
                    break;
                case SDL_KEYDOWN:
                    Temporary.Category2=INFKEY;
                    Temporary.Category3=INFKEYDOWN;
                    Temporary.Data1.uc=Event.key.keysym.sym;
                    //er<<Event.key.keysym.sym<<endl;
                    break;
                case SDL_KEYUP:
                    Temporary.Category2=INFKEY;
                    Temporary.Category3=INFKEYUP;
                    Temporary.Data1.uc=Event.key.keysym.sym;
                    break;
                case SDL_MOUSEMOTION:
                    Temporary.Category2=INFMOUSE;
                    Temporary.Category3=MOUSEMOTION;
                    Temporary.Data1.f=(float)(2*Event.motion.x-(WindowW))/(float)(WindowW);
                    Temporary.Data2.f=-(float)(2*Event.motion.y-(WindowH))/(float)(WindowH);
                    //glReadPixels(Event.motion.x,WindowH-Event.motion.y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,Temporary2);
                    //Temporary.Data3.f=Temporary2[0];
                    //Temporary.Data3.i=Event.motion.x;
                    //Temporary.Data4.i=Event.motion.y;
                    Temporary.Data3.i=Event.motion.xrel;
                    Temporary.Data4.i=Event.motion.yrel;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    Temporary.Category2=INFMOUSE;
                    Temporary.Category3=MOUSEBUTTONDOWN;
                    Temporary.Data1.f=(float)(2*Event.button.x-(WindowW))/(float)(WindowW);
                    Temporary.Data2.f=-(float)(2*Event.button.y-(WindowH))/(float)(WindowH);
                    //glReadPixels(Event.button.x,WindowH-Event.button.y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,Temporary2);
                    //Temporary.Data3.f=Temporary2[0];
                    //Temporary.Data4.i=Event.button.x;
                    //Temporary.Data5.i=Event.button.y;
                    //kk<<"试试"<<Temporary.Data3.f<<endl;
                    //kk<<"鼠标"<<Event.button.x<<" "<<Event.button.y<<endl; 
                    break;
                case SDL_MOUSEBUTTONUP:
                    Temporary.Category2=INFMOUSE;
                    Temporary.Category3=MOUSEBUTTONUP;
                    Temporary.Data1.f=(float)(2*Event.button.x-(WindowW))/(float)(WindowW);
                    Temporary.Data2.f=-(float)(2*Event.button.y-(WindowH))/(float)(WindowH);
                    //glReadPixels(Event.button.x,WindowH-Event.button.y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,Temporary2);
                    //Temporary.Data3.f=Temporary2[0];
                    //Temporary.Data4.i=Event.button.x;
                    //Temporary.Data5.i=Event.button.y;
                    break;
            }
            CheckInf(Temporary);
            //check("  主函数事件",Temporary);
                    
        }
        std::list<Plugin_Base*>::iterator Poi;
        while(HaveToChange){SDL_Delay(1);}
        FunctionInUse=true;
        SDL_GL_SwapBuffers();//强制输出，刷屏。
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        if(MouseLock)
        {
            SDL_WarpMouse(WindowW/2,WindowH/2);
        }
        if(!FunctionLibrary.empty())
        {
            for(Poi=FunctionLibrary.begin();Poi!=FunctionLibrary.end();++Poi)
            {
                if((*Poi)->FunSho)
                {
                    (*Poi)->Show(this);
                }
            }
        }
        FunctionInUse=false;
        //error<<"Show"<<endl;
                //check("  主函数分析",Tem);
    }
}

void ControlCenter::Regedit(Plugin_Base* Temporary)
{
    if(!RegeditReady)
    {
        if(NaTarSI.count(Temporary->Name)==0)
        {
            RegeditID+=1;
            Temporary->RegeditID=RegeditID;
            NaTarIP.insert(std::make_pair(RegeditID , Temporary));
            NaTarSI.insert(std::make_pair(Temporary->Name , RegeditID));
            NaTarIS.insert(std::make_pair(RegeditID,Temporary->Name  ));
            FunctionLibrary.push_back(Temporary);
            Information Tem;
            Tem.Resource=INFCONID;
            Tem.Target=RegeditID;
            Tem.Category1=INFCONREG;
            DeliverLibrary.push_back(Tem);
        }
    }
}

ControlCenter::ControlCenter():ThreadReady(false),Running(true),RegeditReady(false),ExitImi(true),HaveToChange(false),FunctionInUse(false)
{
    RegeditID=INFCONID;
    Aspect=1;
    DelayForShow=5;
    DelayForAnalyze=5;
    Calculate=0;
    WindowW=1200;
    WindowH=800;
    Angle=40;
    FarSize=50;
    NearSize=0.001;
    TimeReadyToExit=false;
    AnalyzeReadyToExit=false;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) //SDL初始化失败
    {
        exit(0);
    }
    atexit(SDL_Quit);//注册退出函数 
}

void ControlCenter::Ready()
{
    RegeditReady=true;
}

void ControlCenter::AimAt(std::string Name , int Category1=-999  , int Category2=-999 , int Category3=-999 )
{
    Information Temp;
    Temp.Resource = INFCONID;
    if( NaTarSI.count(Name) )
    {
        Temp.Target = NaTarSI[Name];
        Temp.Category1=Category1;
        Temp.Category2=Category2;
        Temp.Category3=Category3;
        FastShoot.push_back(Temp);
    }
}

int ControlCenter::Time(int Number)
{
    return SDL_GetTicks()-StarTime-Number;
}
bool ControlCenter::Time(int X1,int X2)
{
    int Time=SDL_GetTicks()-StarTime;
    if((Time>=X1&&Time<=X2)||(Time>=X2&&Time<=X1))    return true;
    else    return false;
}
int Thread_1_Function(void* Data) //对数据的分析 
{
    ControlCenter* CC = static_cast< ControlCenter* > (Data);
    std::list<Plugin_Base*>::iterator FunPoi;
    Information Tem;
    if(CC->RegeditReady)
    {
        while(CC->Running)
        {
            //error<<"dsafdsafaggdfs"<<endl;
            CC->TimeForAnalyze=SDL_GetTicks();
            do
            {
                Information Temp;
                //er<<"Library数量"<<CC->DeliverLibrary.size()<<endl;
                if(!CC->DeliverLibrary.empty())
                {
                    Tem = *(CC->DeliverLibrary.begin());
                    CC->DeliverLibrary.pop_front();
                }else
                    Tem = NEXT;
                //check("  复函数分析2",Tem);
                while(Tem.Resource!=INFCONID&&(Tem.Target==INFALL||Tem.Target==INFCONID))
                {
                    //check("  复函数分析",Tem);
                    if(Tem.Target==INFALL)
                    {
                        
                    }else if(Tem.Target == INFCONID)
                    {
                        Plugin_Base* Point;
                        switch(Tem.Category1)
                        {
                            case INFEVENT:
                                if(Tem.Category2==INFEXIT)
                                    CC->MainLibrary.push_back(Tem);
                                break;
                            case INFCONTS:
                            case INFCONZJ:
                                CC->MainLibrary.push_back(Tem);
                                break;
                            case INFASPECT:
                                CC->Aspect=Tem.Data1.ui;
                                break;
                            case INFDESTORY:
                                CC->HaveToChange=true;
                                while(CC->FunctionInUse||CC->FunctionInUse2){SDL_Delay(1);}
                                Point=Call(Tem.Resource);
                                for(std::map<std::string , int >::iterator Poi=NaTarSI.begin();Poi!=NaTarSI.end();++Poi)
                                {
                                    if(Poi->first==Point->Name)
                                    {
                                        NaTarSI.erase(Poi);
                                        break;
                                    }
                                }
                                for(std::map<int , Plugin_Base* >::iterator Poi=NaTarIP.begin();Poi!=NaTarIP.end();++Poi)
                                {
                                    if(Poi->first==Point->RegeditID)
                                    {
                                        NaTarIP.erase(Poi);
                                        break;
                                    }
                                }
                                for(std::map<int , std::string >::iterator Poi=NaTarIS.begin();Poi!=NaTarIS.end();++Poi)
                                {
                                    if(Poi->first==Point->RegeditID)
                                    {
                                        NaTarIS.erase(Poi);
                                        break;
                                    }
                                }
                                for(std::list<Plugin_Base*>::iterator Poi=CC->FunctionLibrary.begin();Poi!=CC->FunctionLibrary.end();++Poi)
                                {
                                    if((*Poi)==Point)
                                    {
                                        (*Poi)->Destory(CC);
                                        CC->FunctionLibrary.erase(Poi);
                                        break;
                                    }
                                }
                                CC->HaveToChange=false;
                                break;
                            case INFCREATE:
                                CC->HaveToChange=true;
                                while(CC->FunctionInUse||CC->FunctionInUse){SDL_Delay(1);}
                                if(NaTarSI.count(static_cast<Plugin_Base*>(Tem.Data1.v)->Name)==0)
                                {
                                    CC->FunctionLibrary.push_back(static_cast<Plugin_Base*>(Tem.Data1.v));
                                    CC->RegeditID+=1;
                                    static_cast<Plugin_Base*>(Tem.Data1.v)->RegeditID=CC->RegeditID;
                                    NaTarIP.insert(std::make_pair(static_cast<Plugin_Base*>(Tem.Data1.v)->RegeditID , static_cast<Plugin_Base*>(Tem.Data1.v)));
                                    NaTarSI.insert(std::make_pair(static_cast<Plugin_Base*>(Tem.Data1.v)->Name , static_cast<Plugin_Base*>(Tem.Data1.v)->RegeditID));
                                    NaTarIS.insert(std::make_pair(static_cast<Plugin_Base*>(Tem.Data1.v)->RegeditID ,static_cast<Plugin_Base*>(Tem.Data1.v)->Name));
                                    static_cast<Plugin_Base*>(Tem.Data1.v)->Init(CC);
                                }
                                CC->HaveToChange=false;
                                break;
                            case INFRESETTIME:
                                CC->StarTime=SDL_GetTicks();
                                break;
                            case INFMOUSELOCK:
                                CC->MouseLock=true;
                                break;
                            case INFMOUSEUNLOCK:
                                CC->MouseLock=false;
                                break;
                        }
                        if(!CC->DeliverLibrary.empty())
                        {
                            Tem=*(CC->DeliverLibrary.begin());
                            CC->DeliverLibrary.pop_front();
                        }else{
                            Tem=EMPTY;
                            break;
                        }
                    }
                }
                if(!CC->FunctionLibrary.empty())
                {
                    //er<<"OK"<<endl;
                    for(FunPoi=CC->FunctionLibrary.begin();FunPoi!=CC->FunctionLibrary.end();++FunPoi)
                    {
                        if(*FunPoi!=NULL)
                        {
                            if((*FunPoi)->FunDel)
                            {
                                do
                                {
                                //er<<"too"<<endl;
                                    Temp=(*FunPoi)->Deliver(Tem);
                                    if(Temp.Target!=INFRETURN)
                                    {
                                    //er<<"OK~"<<endl;
                                        CC->DeliverLibrary.push_back(Temp);
                                    }
                                }while(Temp.Target!=INFRETURN);
                                if(Temp.Target==INFRETURN&&Temp.Category1==INFDELETE)
                                {
                                    break;
                                }
                            }
                        }
                    }
                    if(CC->ExitImi)
                    {
                        if(Tem.Resource==INFCONID&&Tem.Target==INFALL&&Tem.Category1==INFEVENT&&Tem.Category2==INFEXIT)
                        {
                            CC->MainLibrary.push_back(Tem);
                        }
                    }
                }else if(Tem.Resource==INFCONID&&Tem.Target==INFALL&&Tem.Category1==INFEVENT&&Tem.Category2==INFEXIT)
                {
                    CC->MainLibrary.push_back(Tem);
                }
            }while(!CC->DeliverLibrary.empty());
            if(!CC->FunctionLibrary.empty())
            {
                FunPoi=CC->FunctionLibrary.begin();
                for(;FunPoi!=CC->FunctionLibrary.end();++FunPoi)
                {
                    if(*FunPoi!=NULL)
                    {
                        if((*FunPoi)->FunAna)
                        {
                            (*FunPoi)->Analyze(CC);
                        }
                    }
                }
            }
            SDL_Delay( CC->DelayForAnalyze );
            int Time=SDL_GetTicks()-CC->TimeForAnalyze;
            if(Time>=5&&CC->DelayForAnalyze>=1)
            {
                CC->DelayForAnalyze-=1;
            }else if(Time<=3&&CC->DelayForAnalyze>=0)
            {
                CC->DelayForAnalyze+=1;
            }
            //error<<"Analyze"<<endl;
        }
        
    }
    CC->AnalyzeReadyToExit=true;
}
int Oclock(void *param)
{
    static int Tem=SDL_GetTicks();
    ControlCenter* CC=static_cast<ControlCenter*>(param);
    //error<<"我试试看行不行"<<endl;
    if(CC->RegeditReady)
    {
        Tem=SDL_GetTicks();
        while(CC->Running)
        {
            while(CC->HaveToChange){SDL_Delay(1);};
            CC->FunctionInUse2=true;
            if(!CC->FunctionLibrary.empty())
            {
                for(std::list<Plugin_Base*>::iterator Poi=CC->FunctionLibrary.begin();Poi!=CC->FunctionLibrary.end();++Poi)
                {
                    if((*Poi)->FunTim)
                    {
                        (*Poi)->Time(CC);
                    }
                }
            }
            CC->FunctionInUse2=false;
            //error<<SDL_GetTicks()-Tem<<endl;
            while(SDL_GetTicks()-Tem<5)
            {
                SDL_Delay(1);
            }
            Tem=SDL_GetTicks();
            //error<<"Time"<<endl;
        }
    }
    CC->TimeReadyToExit=true;
}
#endif
