/*作者：温林达 
  完成于：2012年4月20日 
*/


#ifndef DIY_PLUGIN_BASE_H
#define DIY_PLUGIN_BASE_H
#include <string>
#include <list>
#include <map>
#include <vector>
#include <set>
#include "Information.h"
#include <GL/gl.h>
#include <SDL/SDL.H>
#include <SDL/SDL_opengl.h>
#include <GL/GLU.h>
#include "glsimplify.h"
class Plugin_Base;
class ControlCenter;
std::map<std::string , int > NaTarSI;
std::map<int , Plugin_Base* > NaTarIP;
std::map<int , std::string > NaTarIS;
inline int Call(std::string Tem)
{
    if(NaTarSI.count(Tem))
        return NaTarSI[Tem];
    else
        return INFNOTAR;
}
inline Plugin_Base* Call(int Tem)
{
    if(NaTarIP.count(Tem))
        return NaTarIP[Tem];
    else
        return NULL;
}
int Thread_1_Function(void* Data);
class Plugin_Base //插件基类 
{
    protected:
    friend class ControlCenter;
    friend int Thread_1_Function(void* Data);
    friend int Oclock(void *param);
    int RegeditID;
    const std::string Name;
    std::list< Information > OutLibrary;
    std::list< Information > Library;
    bool FunSho;
    void virtual Destory(ControlCenter* Data);
    void virtual Show(ControlCenter* Data);
    bool FunAna;
    void virtual Analyze(ControlCenter* Data);
    void virtual Init(ControlCenter* Data);
    bool FunTim;
    void virtual Time(ControlCenter* Data); 
    bool RefuseINFALL;
    bool FunDel;
    public: 
        bool ShootLib(Information& Temp);
        Information Deliver(Information& Tem);
        Plugin_Base(std::string name);
        Plugin_Base(std::string name,bool choice);
        void Useless(void);
        void GetLib(Information& Temp);
        void ToAspect(unsigned int Te);
        void Orthogonality(void);
        void Perspective(void);
        void UnableExit(void);
        void Kill(void);
        void Out(Information& Tem);
        void Exit(void);
        void LockMouse(void);
        void UnlockMouse(void);
        Information NewInformation(int Target,int Category1,int Category2,int Category3,int Category4);
        Information GetInformation(void);
        ~Plugin_Base();
}; 


#include "Plugin_base.cpp"
#endif
