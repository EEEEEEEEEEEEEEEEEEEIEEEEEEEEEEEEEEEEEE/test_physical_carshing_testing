
class ControlForGame:public Plugin_Base
{
    XYZF Location;
    XYZF* LocPoint;
    float* AUP;
    float AngleUp;
    float* ARP;
    float AngleRight;
    XYZF Face;
    XYZF Face2;
    XYZF Up;
    std::map<unsigned char , bool > Key;
    ChState State;
    public:
        ControlForGame(View Tem,Aspect Tem2):Plugin_Base("CG")
        {
            Key.insert(make_pair('w',false));
            Key.insert(make_pair('s',false));
            Key.insert(make_pair('a',false));
            Key.insert(make_pair('d',false));
            Key.insert(make_pair(27,false));
            Key.insert(make_pair(32,false));
        }
        void Init(ControlCenter* CC)
        {
            
        }
        void Time(ControlCenter* CC)
        {
            bool Set=false;
            if(Key['w'])
            {
                Location=Location+Face*SPEED;
                Set=true;
            }
            if(Key['s'])
            {
                Location=Location-Face*SPEED;
                Set=true;
            }
            if(Key['a'])
            {
                Location=Location-XYZF(-Face.Z,0.0,Face.X)*SPEED;
                Set=true;
            }
            if(Key['d'])
            {
                Location=Location+XYZF(-Face.Z,0.0,Face.X)*SPEED;
                Set=true;
            }
            if(Set)
            {
                Information Tem=NewInformation(Call("View"),VIEWLOCATION);
                XYZF TemXYZ;
                Tem.Resource=Call("Aspect");
                TemXYZ=Location-Face2*4;
                Tem.Data1.f=TemXYZ.X;
                Tem.Data2.f=TemXYZ.Y;
                Tem.Data3.f=TemXYZ.Z;
                Out(Tem);
                Tem=NewInformation(Call("Aspect"),ASPLOCATION);
                Tem.Data1.f=Location.X;
                Tem.Data2.f=Location.Y;
                Tem.Data3.f=Location.Z;
                Out(Tem);
            }
        }
        void Analyze(ControlCenter* CC)
        {
            while(!Library.empty())
            {
                //error<<"dfjashdlkjahfasdf"<<endl;
                Information Tem=GetInformation();
                if(Tem.Category1==INFEVENT&&Tem.Category2==INFKEY)
                {
                    if(Tem.Category3==INFKEYDOWN)
                    {
                        if(Key.count(Tem.Data1)>0)
                        {
                            Key[Tem.Data1]=true;
                        }
                    }else if(Tem.Category3==INFKEYUP)
                    {
                        if(Key.count(Tem.Data1)>0)
                        {
                            Key[Tem.Data1]=false;
                        }
                    }
                }else if(Tem.Category1==INFEVENT&&Tem.Category2==INFMOUSE)
                {
                    if(Tem.Category3==MOUSEMOTION)
                    {
                        AngleRight-=Tem.Data3.i*0.005;
                        AngleUp+=Tem.Data4.i*0.005;
                        Face.Set(sin(AngleRight),0.0,-cos(AngleRight));
                        Face2.Set(cos(AngleUp)*sin(AngleRight),sin(AngleUp),-cos(AngleUp)*cos(AngleRight));
                        Up.Set(-sin(AngleUp)*sin(AngleRight),cos(AngleUp),sin(AngleUp)*cos(AngleRight));
                        Information Tem=NewInformation(Call("View"),VIEWANGLE);
                        Tem.Data1.f=AngleUp;
                        Tem.Data2.f=AngleRight;
                        Out(Tem);
                        Tem=NewInformation(Call("View"),VIEWLOCATION);
                        XYZF TemXYZ;
                        TemXYZ=Location-Face2*4;
                        Tem.Data1.f=TemXYZ.X;
                        Tem.Data2.f=TemXYZ.Y;
                        Tem.Data3.f=TemXYZ.Z;
                        Out(Tem);
                        Tem=NewInformation(Call("Aspect"),ASPANGLE);
                        Tem.Data1.f=AngleUp;
                        Tem.Data2.f=AngleRight;
                        Out(Tem);
                    }
                }
            }
            if(Key[27])    Exit();
        }
};
