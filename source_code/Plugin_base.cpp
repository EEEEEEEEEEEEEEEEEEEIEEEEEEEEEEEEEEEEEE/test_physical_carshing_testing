#ifndef DIY_PLUGIN_BASE_APP_CPP
#define DIY_PLUGIN_BASE_APP_CPP
#include "plugin_base.h"
void Plugin_Base::Destory(ControlCenter* Data)
{
}
void Plugin_Base::Show(ControlCenter* Data)
{
    FunSho=false;
}

void Plugin_Base::Analyze(ControlCenter* Data)
{
    FunAna=false;
}
void Plugin_Base::Time(ControlCenter* Data)
{
    FunTim=false;
}
bool Plugin_Base::ShootLib(Information& Temp)
{
    if(NaTarIP.count(Temp.Target))
    {
        if((NaTarIP[Temp.Target])->FunSho||(NaTarIP[Temp.Target])->FunAna)
            (NaTarIP[Temp.Target])->Library.push_back(Temp);
        return true;
    }
    return false;
}

Information Plugin_Base::Deliver(Information& Tem)
{
    if((!FunAna)&&(!FunSho)&&(!FunTim))
    {
        FunDel=false;
        Library.clear();
        OutLibrary.clear();
    }else{
        Information Temp;
            //er<<Name<<" "<<"OutLibrary:"<<OutLibrary.size()<<endl; 
            //er<<"Library:"<<Library.size()<<endl; 
        while(!OutLibrary.empty())
        {
            Temp=*OutLibrary.begin();
        //check("ÎÒ³¬",Temp);
            OutLibrary.pop_front();
            if(Temp.Target!=INFALL&&Temp.Target!=INFNOTAR)
            {
            //er<<"sdsergggggg"<<endl;
                if(!ShootLib(Temp))
                {
                //er<<"Yes!!"<<endl;
                    return Temp;
                }
            }else if(Temp.Target==INFALL)
            {
            //er<<"sdsddfsdfgthyhytj"<<endl;
                return Temp;
            }else if(Temp.Target==INFNOTAR)
            {
            //er<<"Some thing wrong"<<endl;
                Temp.Target=INFRETURN;
                Temp.Category1=INFNEXT;
                return Temp;
            }
        }
        if(Tem.Resource!=RegeditID&&(Tem.Target==RegeditID||(Tem.Target==INFALL&&(!RefuseINFALL))))
        {
            Library.push_back(Tem);
            if(Tem.Target==RegeditID)
            {
                Temp.Resource=RegeditID;
                Temp.Target=INFRETURN;
                Temp.Category1=INFDELETE;
                return Temp;
            }
        }
        Temp.Resource=RegeditID;
        Temp.Target=INFRETURN;
        Temp.Category1=INFNEXT;
        return Temp;
    }
}
Plugin_Base::~Plugin_Base()
{
    Kill();
    Library.clear();
    OutLibrary.clear(); 
}
Plugin_Base::Plugin_Base(std::string name):Name(name),RefuseINFALL(false)
{
    RegeditID=INFNOID;
    FunSho=true;
    FunAna=true;
    FunDel=true;
    FunTim=true;
}

Plugin_Base::Plugin_Base(std::string name,bool choice):Name(name),RefuseINFALL(choice)
{
    RegeditID=INFNOID;
    FunSho=true;
    FunAna=true;
    FunDel=true;
    FunTim=true;
}

void Plugin_Base::GetLib(Information& Temp)
{
    if(Temp.Target==RegeditID||Temp.Target==INFALL)
    {
        Library.push_back(Temp);
    }
}

void Plugin_Base::ToAspect(unsigned int Te)
{
    Information Tem;
    Tem.Resource=RegeditID;
    Tem.Target=INFCONID;
    Tem.Category1=INFASPECT;
    Tem.Data1.ui=Te;
    OutLibrary.push_back(Tem);
}

void Plugin_Base::Orthogonality(void)
{
    Information Tem;
    Tem.Resource=RegeditID;
    Tem.Target=INFCONID;
    Tem.Category1=INFCONZJ;
    OutLibrary.push_back(Tem);
}

void Plugin_Base::UnableExit(void)
{
    Information Tem;
    Tem.Resource=RegeditID;
    Tem.Target=INFCONID;
    Tem.Category1=INFUNABLEEXITIMI;
    OutLibrary.push_back(Tem);
}

void Plugin_Base::Perspective(void)
{
    Information Tem;
    Tem.Resource=RegeditID;
    Tem.Target=INFCONID;
    Tem.Category1=INFCONTS;
    OutLibrary.push_back(Tem);
}

void Plugin_Base::Out(Information& Tem)
{
    OutLibrary.push_back(Tem);
}

void Plugin_Base::Kill(void)
{
    Information Tem;
    Tem.Target=INFCONID;
    Tem.Resource=RegeditID;
    Tem.Category1=INFDESTORY;
    Out(Tem);
}
void Plugin_Base::Init(ControlCenter* Data)
{
}
Information Plugin_Base::NewInformation(int Target,int Category1=INFNULL,int Category2=INFNULL,int Category3=INFNULL,int Category4=INFNULL)
{
    Information Tem;
    Tem.Resource=RegeditID;
    Tem.Target=Target;
    Tem.Category1=Category1;
    Tem.Category2=Category2;
    Tem.Category3=Category3;
    Tem.Category4=Category4;
    return Tem;
}
            
Information Plugin_Base::GetInformation(void)
{
    if(Library.empty())
    {
        return EMPTY;
    }else{
        Information Tem=*Library.begin();
        Library.pop_front();
        return Tem;
    }
}
void Plugin_Base::Useless(void)
{
    Library.clear();
}
void Plugin_Base::Exit(void)
{
    Information Tem=NewInformation(INFCONID,INFEVENT,INFEXIT);
    Out(Tem);
}
void Plugin_Base::LockMouse(void)
{
    Information Tem=NewInformation(INFCONID,INFMOUSELOCK);
    Out(Tem);
}
void Plugin_Base::UnlockMouse(void)
{
    Information Tem=NewInformation(INFCONID,INFMOUSEUNLOCK);
    Out(Tem);
}
#endif

