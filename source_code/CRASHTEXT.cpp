#include "Plugin_Base.h"
#include "CrashDead.h"
#include "ShowCrash.cpp"
#include "sgprint.h"
#include "motion.h"
#include "game/numberOut.h"
#include "Flat.h"
#include "shipView.h"
#include "Ship.h"
#include "Brain.h"
extern Weapon WE;
class CrashLive;
class CrashText:public Plugin_Base,public Flat,public ShipView
{
    SingleShip CD;
    SingleShip CD2;
    CrashFaceData FD;
    std::map<unsigned char , bool > Key;
    Sentence3D SC;
    Movement M;
    bool Right;
    NumberOut NO;
    Speed Sp;
    long LastTime;
    public:
        void Init(ControlCenter* CC)
        {
            Cppp=&CD;
            float Face1[]={ 1.0,1.0,1.0,
                            -1.0,1.0,1.0,
                            -1.0,-1.0,1.0,
                            1.0,-1.0,1.0};
            float Face2[]={ -1.0,1.0,1.0,
                            -1.0,1.0,-1.0,
                            -1.0,-1.0,-1.0,
                            -1.0,-1.0,1.0};
            float Face3[]={ -1.0,1.0,-1.0,
                            1.0,1.0,-1.0,
                            1.0,-1.0,-1.0,
                            -1.0,-1.0,-1.0};
            float Face4[]={ 1.0,1.0,-1.0,
                            1.0,1.0,1.0,
                            1.0,-1.0,1.0,
                            1.0,-1.0,-1.0};
            float Aera[]={  1.2,-1.2,
                            -1.2,-1.2,
                            -1.2,1.2,
                            1.2,1.2};
            float Speedt[8]={1.0,2.0,0.5,0.5,1.0,0.02,0.1,0.02};
            float Anglee[6]={0.0,0.1,0.0,0.1,0.0,0.1};
            M.SetTranslation(M_All,Speedt);
            M.SetAngle(Anglee);
            //error<<"tryuuyds     "<<M.TranslationData[0]<<endl;
            //M.Target(&CD2);
            Set(&CD2);
            FD.JustOnce=false;
            FD.FaceAdd(Face1,4);
            FD.FaceAdd(Face2,4);
            FD.FaceAdd(Face3,4);
            FD.FaceAdd(Face4,4);
            //CD.Set(Aera,4);     
            CD.Set(&FD);
            CD2.Set(&FD);
            CD2.WE=&WE;
            MissileTarget* Tc=new MissileTarget;
            ExMissile* Tr=new ExMissile;
            ExEGG* Ty=new ExEGG;
            CD2.SW.push_back(&MC);
            CD2.SW.push_back(Tc);
            CD2.Ex.push_back(Tr);
            CD2.Ex.push_back(Ty);
            //CD2.Set(Aera,4);
            CD2.Location.Set(0.1,0.0,-5.0);
            CD.Location.Set(0.0,0.0,0.0);
            //CD2.SW.push_back(static_cast<Software*>(&MC));
            Key.insert(std::make_pair('w',false));
            Key.insert(std::make_pair('s',false));
            Key.insert(std::make_pair('a',false));
            Key.insert(std::make_pair('d',false));
            Key.insert(std::make_pair('p',false));
            SC.Add("碰撞了");
            NO.Set((void*)(&CD2.Location.Z),NUM_FLOAT);
            NO.Set("I'm here");
            LastTime=SDL_GetTicks();
        }
        void Show(ControlCenter* CC)
        {
            //Useless();
            //SDL_WarpMouse(0,0);
            //View();
            float T=(SDL_GetTicks()-LastTime)/1000.0;
            //CD.Location.Set(-4.0*sin(T*3.141592653/5.0),0.0,-4.0*cos(T*3.141592653/5.0));
            //CD2.Location.Set(14.0,2.0,1.0);
            //CD2.Location.Set(2.0*sin(T*3.141592653/2.0)+4.0,0.0,2.0*cos(T*3.141592653/4.0)-10.0);
            ShowCrash(&CD);
            ShowCrash(&CD2);
            if(Right)SC.Show(XYZF(0.0,0.0,0.0),XYZF(0.0,-1.0,0.0),XYZF(0.0,0.0,1.0),1.0,1.0,1.0,1.0);
            glPushMatrix();
            glLoadIdentity();
            NO.Reflesh();
            glPopMatrix();
            Start2D(0);
            NO.Show(0.0,0.0,CC,0.1);
            glBegin(GL_LINE_LOOP);
            glVertex2f(-1.0,1.0);
            glVertex2f(1.0,1.0);
            glVertex2f(1.0,-1.0);
            glVertex2f(-1.0,-1.0);
            glEnd();
            Back();
            //M.Change(30);
            //ShowCrash(&CD2);
            
        }
        void Analyze(ControlCenter* CC)
        {
            static float Ter=0.0;
            static float Tec=0.0;
            Ter+=0.1;
            Tec+=0.003;
            CD2.Up.Set(0.0,cos(Tec),sin(Tec));
            CD2.Left.Set(cos(Tec),sin(Tec),0.0);
            CD2.Reflash();
            //error<<"just a try~"<<endl;
            while(!Library.empty())
            {
                Information Ter=GetInformation();
                for(int i=2;i<6;++i)
                {
                    M.AngleT[i]=false;
                }
                if(Ter.Category1==INFEVENT)
                {
                    if(Ter.Category2==INFKEY)
                    {
                            if(Ter.Category3==INFKEYDOWN)
                            {
                                if(Key.count(Ter.Data1)>0)
                                {
                                    Key[Ter.Data1]=true;
                                }
                                //error<<"jiushizheyanglamiao~   "<<Ter.Data1.uc<<endl;
                                if(Ter.Data1.uc=='z') LockMouse();
                                if(Ter.Data1.uc=='x') UnlockMouse();
                            }else if(Ter.Category3==INFKEYUP)
                            {
                                if(Key.count(Ter.Data1)>0)
                                {
                                    Key[Ter.Data1]=false;
                                }
                            }
                    }else if(Ter.Category2==INFMOUSE)
                    {
                        if(Ter.Category3==MOUSEMOTION)
                        {
                            /*if(Ter.Data1.f<0)
                            {
                                CD2.Mo.AngleT[2]=true;
                                CD2.Mo.AngleT[3]=false;
                            }else if(Ter.Data1.f>0)
                            {
                                CD2.Mo.AngleT[2]=false;
                                CD2.Mo.AngleT[3]=true;
                            }else{
                                CD2.Mo.AngleT[2]=false;
                                CD2.Mo.AngleT[3]=false;
                            }
                            if(Ter.Data2.f<0)
                            {
                                CD2.Mo.AngleT[4]=false;
                                CD2.Mo.AngleT[5]=true;
                            }else if(Ter.Data2.f>0)
                            {
                                CD2.Mo.AngleT[4]=true;
                                CD2.Mo.AngleT[5]=false;
                            }else{
                                CD2.Mo.AngleT[4]=false;
                                CD2.Mo.AngleT[5]=false;
                            }*/
                        }else if(Ter.Category3==MOUSEBUTTONDOWN)
                        {
                            /*error<<"就是这样秒~"<<endl;
                            Information Tec=NewInformation(Call("WEAPON"),456677);
                            error<<" xxx"<<CD2.Location.X<<"  "<<CD2.Location.Y<<"  "<<CD2.Location.Z <<endl;
                            //Tec.Data1=static_cast<void*>(static_cast<Coordinate*>(static_cast<CrashLive*>(&CD2)));
                            Tec.Data1=TransPoint<Coordinate,SingleShip>(&CD2);
                            error<<(int)(Tec.Data1.v);
                            error<<"  xx   "<<static_cast<Coordinate*>(Tec.Data1.v)->Location.X<<"  "<<static_cast<Coordinate*>(Tec.Data1.v)->Location.Y<<"  "<<static_cast<Coordinate*>(Tec.Data1.v)->Location.Z <<endl;
                            
                            Tec.Data2=TransPoint<Coordinate,SingleShip>(&CD);
                            error<<"  xx2  "<<static_cast<Coordinate*>(Tec.Data2.v)->Location.X<<"  "<<static_cast<Coordinate*>(Tec.Data2.v)->Location.Y<<"  "<<static_cast<Coordinate*>(Tec.Data2.v)->Location.Z <<endl;
                            Out(Tec);*/
                            CD2.Target=true;
                        }else if(Ter.Category3==MOUSEBUTTONUP) CD2.Target=false;
                    }
                }
            }
            /*if(Key['w']){CD2.Mo.Move[0]=true;}else CD2.Mo.Move[0]=false;
            if(Key['s']){CD2.Mo.Move[1]=true;}else CD2.Mo.Move[1]=false;
            if(Key['a']){CD2.Mo.Move[2]=true;}else CD2.Mo.Move[2]=false;
            if(Key['d']){CD2.Mo.Move[3]=true;}else CD2.Mo.Move[3]=false;
            if(Key['q']){M.AngleT[0]=true;}else M.AngleT[0]=false;
            if(Key['e']){M.AngleT[1]=true;}else M.AngleT[1]=false;
            if(Key['p']){ViewStyle();Key['p']=false;}*/
            if(Key['i']){CD2.Location=CD2.Location+XYZF(0.0,0.0,0.01);}
            if(Key['k']){CD2.Location=CD2.Location-XYZF(0.0,0.0,0.01);}
            if(Key['j']){CD2.Location=CD2.Location-XYZF(0.01,0.0,0.0);}
            if(Key['l']){CD2.Location=CD2.Location+XYZF(0.01,0.0,0.0);}
            CrashLocation Tr=CD;
            //if(CD.Check(&CD2,Tr)) 
            //error<<"一次检测开始"<<endl;
            Right=CD.CheckFace(&CD2,Tr);
            //error<<"二次检测结束"<<endl;
            //else Right=false;
            //M.Change(SDL_GetTicks()-LastTime,&Sp,&CD2);
            //CD2.Analyze();
        }
    CrashText(std::string Name,ControlCenter* CC):Plugin_Base(Name),Flat(CC){}
};
