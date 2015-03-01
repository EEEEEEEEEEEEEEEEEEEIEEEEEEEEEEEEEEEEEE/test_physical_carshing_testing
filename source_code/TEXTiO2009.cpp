#include <fstream>
using namespace std;
//fstream error("erroewwww.txt",ios::out);
#include "Plugin_Base.h"
#include "ControlCenter.h"
#include "View.cpp"
//#include "Crash.h"
#include "numberout.h"
#include "Weapon.h"
#include "Crashtext.cpp"
ControlCenter CC;
View V(true);
CrashText CT("CT",&CC);
Weapon WE("WEAPON");
int main(int argc, _TCHAR* argv[])
{
    CC.Regedit(&V);
    CC.Regedit(&CT);
    CC.Regedit(&WE);
    CC.Ready();
    CC.Init(3);
    while(CC.Running)
    {
        CC.Run();
        glBegin(GL_POINTS);
        glVertex3f(0.0,0.0,0.0);
        glEnd();
        CC.Finish();
    }
}
