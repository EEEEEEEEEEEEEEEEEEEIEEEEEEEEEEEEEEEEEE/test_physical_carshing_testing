#include "Plugin_Base.h"
#include "CrashDead.h"
#include "ShowCrash.cpp"
#include "sgprint.h"
#include "motion.h"
#include "numberOut.h"
#include "Flat.h"
#include "shipView.h"
#include "Ship.h"
#include "Brain.h"
class CrashText:public Plugin_Base,public Flat,public ShipView
{
    SingleShip CD;
    SingleShip CD2;
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
            CD.FaceAdd(Face1,4);
            CD.FaceAdd(Face2,4);
            CD.FaceAdd(Face3,4);
            CD.FaceAdd(Face4,4);
            //CD.Set(Aera,4);     
            CD2.FaceAdd(Face1,4);
            CD2.FaceAdd(Face2,4);
            CD2.FaceAdd(Face3,4);
            CD2.FaceAdd(Face4,4);
            //CD2.Set(Aera,4);
            CD2.Location.Set(4.0,0.0,8.0);
            Key.insert(std::make_pair('w',false));
            Key.insert(std::make_pair('s',false));
            Key.insert(std::make_pair('a',false));
            Key.insert(std::make_pair('d',false));
            Key.insert(std::make_pair('p',false));
            SC.Add("碰撞了");
            NO.Set((void*)(&CD2.Location.Z),NUM_FLOAT);
            LastTime=SDL_GetTicks();
        }
        void Show(ControlCenter* CC)
        {
            //Useless();
            //SDL_WarpMouse(0,0);
            View();
            float T=(SDL_GetTicks()-LastTime)/1000.0;
            CD.Location.Set(4.0*sin(T*3.141592653/5.0),0.0,4.0*cos(T*3.141592653/5.0));
            CD2.Location.Set(2.0*sin(T*3.141592653/2.0)+4.0,0.0,2.0*cos(T*3.141592653/4.0)-10.0);
            ShowCrash(&CD);
            ShowCrash(&CD2);
            if(Right)SC.Show(XYZF(0.0,0.0,0.0),XYZF(0.0,-1.0,0.0),XYZF(0.0,0.0,1.0),1.0,1.0,1.0,1.0);
            glPushMatrix();
            glLoadIdentity();
            NO.Reflesh();
            NO.Show(-1.0,1.0,CC,0.1);
            glPopMatrix();
            Start2D(0);
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
            //CD2.Up.Set(0.0,cos(Ter),sin(Ter));
            //CD2.Left.Set(cos(Tec),sin(Tec),0.0);
            //CD2.Reflash();
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
                                error<<"jiushizheyanglamiao~   "<<Ter.Data1.uc<<endl;
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
                            if(Ter.Data1.f<0)
                            {
                                M.AngleT[2]=true;
                                M.AngleT[3]=false;
                            }else if(Ter.Data1.f>0)
                            {
                                M.AngleT[2]=false;
                                M.AngleT[3]=true;
                            }
                            if(Ter.Data2.f<0)
                            {
                                M.AngleT[4]=false;
                                M.AngleT[5]=true;
                            }else if(Ter.Data2.f>0)
                            {
                                M.AngleT[4]=true;
                                M.AngleT[5]=false;
                            }
                        }else if(Ter.Category3==MOUSEBUTTONDOWN)
                        {
                            error<<"就是这样秒~"<<endl;
                            Information Tec=NewInformation(Call("WEAPON"),4566);
                            error<<"  "<<CD2.Location.X<<"  "<<CD2.Location.Y<<"  "<<CD2.Location.Z <<endl;
                            
                            Tec.Data1=TransPoint<Coordinate*,SingleShip*>(&CD2);
                            error<<"  "<<static_cast<CrashDead*>(Tec.Data1.v)->Location.X<<"  "<<static_cast<CrashDead*>(Tec.Data1.v)->Location.Y<<"  "<<static_cast<CrashDead*>(Tec.Data1.v)->Location.Z <<endl;
                            Tec.Data2.v=static_cast<void*>(static_cast<Coordinate*>(&CD));
                            Out(Tec);
                        }
                    }
                }
            }
            //if(Key['w']){M.Move[0]=true;}else M.Move[0]=false;
            //if(Key['s']){M.Move[1]=true;}else M.Move[1]=false;
            //if(Key['a']){M.Move[2]=true;}else M.Move[2]=false;
            //if(Key['d']){M.Move[3]=true;}else M.Move[3]=false;
            //if(Key['q']){M.AngleT[0]=true;}else M.AngleT[0]=false;
            //if(Key['e']){M.AngleT[1]=true;}else M.AngleT[1]=false;
            if(Key['p']){ViewStyle();Key['p']=false;}
            /*if(Key['i']){CD2.Location=CD2.Location+XYZF(0.0,0.0,0.01);}
            if(Key['k']){CD2.Location=CD2.Location-XYZF(0.0,0.0,0.01);}
            if(Key['j']){CD2.Location=CD2.Location-XYZF(0.01,0.0,0.0);}
            if(Key['l']){CD2.Location=CD2.Location+XYZF(0.01,0.0,0.0);}*/
            CrashLocation Tr=CD;
            //if(CD.Check(&CD2,Tr)) 
            Right=CD.CheckFace(&CD2,Tr);
            //else Right=false;
            //M.Change(SDL_GetTicks()-LastTime,&Sp,&CD2);
        }
    CrashText(std::string Name,ControlCenter* CC):Plugin_Base(Name),Flat(CC){}
};
