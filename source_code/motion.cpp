#ifndef DIY_MOTION_CPP
#define DIY_MOTION_CPP
/*void Motion::Crash(Motion* Tem)
{
    float& M1=Quality;
    float& M2=Tem->Quality;
    float& K1=Parameter;
    float& K2=Tem->Parameter;
    float VT1[3];
    float VT2[3];
    float VT12[3];
    float VT22[3];
    VToF(Direction,VT1);
    VToF(Tem->Direction,VT2);
    for(int i=0;i<3;++i)
    {
        float V1=Speed*VT1[i];
        float V2=Tem->Speed*VT2[i];
        XYZF A=0.5/M1*(pow(M1,2.0),pow(M2,2.0));
        float B=-M2/M1*(M1*V1+M2*V2);
        float C=M2*(V1,V2)-0.5*M2*(K2-M2/M1)*pow(V2,2.0)-(K1-1.0)*0.5*M1*pow(V1,2.0);
        float V21=(-B+sqrt(pow(B,2.0)-4.0*A*C))/2.0/A;
        float V22=(-B+sqrt(pow(B,2.0)-4.0*A*C))/2.0/A;
        float V11=M1*V1+M2*(V2-V21);
        float V12=M1*V2+M2*(V2-V22);
        if(V21>V11)
        {
            VT12[i]=V11;
            VT22[i]=V21;
        }else{
            VT12[i]=V12;
            VT22[i]=V22;
        }
    }
    FToV(Direction,VT12);
    FToV(Tem->Direction,VT22);
    Speed=Direction.Long();
    Tem->Speed=Tem->Direction.Long();
    Direction=Direction.Uint();
    Tem->Direction=Tem->Direction.Uint();
}
inline XYZF Motion::pow(const XYZF& T1,float T2);
{
    XYZF Ter(pow(T1.X,T2),pow(T1.Y,T2),pow(T1.Z,T2));
    return Ter;
}
inline XYZF Motion::Multiplication(const XYZF& V1, const XYZF& V2)
{
    XYZF Ter(V1.X*V2.X,V1.Y*V2.Y,V1.Z*V2.Z);
    return Ter;
}
inline void Motion::VToF(const XYZF& T,const flaot* P)
{
    P[0]=T.X;
    P[1]=T.Y;
    P[2]=T.Z;
}
inline void Motion::FToV(XYZF& T, const float* P)
{
    T.Set(P[0],P[1],P[2]);
}*/
/*void Translation::operator=(const Translation& Ter)
{
    Style=Ter.Style;
    for(int i=0;i<9;++i)
    {
        TranslationData[i]=Ter.TranslationData[i];
    }
}*/
void Translation::Change(long Time,Speed* Sp,Coordinate* Target)
{
    float T=(float)Time/1000.0;
    XYZF Ta(0.0,0.0,0.0);
    float* D=TranslationData;
    float& X=Sp->F;
    float& L=Sp->L;
    float& U=Sp->U;
    if(Target!=NULL)
    {
        if(Style%2>=1)
        {
            //error<<"Yes"<<endl;
            //error<<T<<endl;
            if(Move[0])
            {
                //error<<"jiushishuoa"<<endl;
                //error<<"("<<Target->Front.Z<<endl;
                float LV=D[0]*T+X;
                if(X>=D[1])
                {
                    Ta=Ta+X*T*Target->Front;
                    //X=D[1];
                }else if(LV>D[1])
                {
                    float T1=(D[1]-X)/D[0];
                    Ta=Ta+(0.5*D[0]*T1*T1+D[1]*(T-T1))*Target->Front;
                    X=D[1];
                }else{
                    Ta=Ta+(0.5*D[0]*T*T+X*T)*Target->Front;
                    X=LV;
                }
            }
            if(Move[1])
            {
                float LV=X-D[2]*T;
                if(X<=-D[3])
                {
                    Ta=Ta+X*T*Target->Front;
                    //X=-D[3];
                }else if(LV<D[3])
                {
                    float T1=(D[3]-X)/D[2];
                    Ta=Ta+(-0.5*D[2]*T1*T1-D[3]*(T-T1))*Target->Front;
                    X=-D[3];
                }else{
                    Ta=Ta+(-0.5*D[2]*T*T+X*T)*Target->Front;
                    X=LV;
                }
            }
            if(!Move[0]&&!Move[1]) Ta=Ta+X*T*Target->Front;
        }else{
            if(Move[0]) Ta=Ta+D[1]*T*Target->Front;
            if(Move[1]) Ta=Ta-D[3]*T*Target->Front;
        }
        
        if(Style%4>=2)
        {
            if(Move[2])
            {
                float LV=L+D[4]*T;
                if(L>=D[5])
                {
                    Ta=Ta+D[5]*T*Target->Left;
                    L=D[5];
                }else if(LV>D[5])
                {
                    float T1=(D[5]-L)/D[4];
                    Ta=Ta+(0.5*D[4]*T1*T1+D[5]*(T-T1))*Target->Left;
                    L=D[5];
                }else{
                    Ta=Ta+(0.5*D[4]*T*T+L*T)*Target->Left;
                    L=LV;
                }
            }else Ta=Ta+D[5]*Target->Left;
            if(Move[3])
            {
                float LV=L-D[4]*T;
                if(L<=-D[5])
                {
                    Ta=Ta-D[5]*T*Target->Left;
                    L=-D[5];
                }else if(LV<D[5])
                {
                    float T1=fabs((-D[5]-L))/D[4];
                    Ta=Ta+(-0.5*D[4]*T1*T1-D[5]*(T-T1))*Target->Left;
                    L=-D[5];
                }else{
                    Ta=Ta+(-0.5*D[4]*T*T+L*T)*Target->Left;
                    L=LV;
                }
            }else Ta=Ta-D[5]*Target->Left;
        }else{
            if(Move[2]) Ta=Ta+D[5]*Target->Left;
            if(Move[3]) Ta=Ta-D[5]*Target->Left;
        }
        
        if(Style%8>=4)
        {
            if(Move[4])
            {
                float LV=U+D[7]*T;
                if(U>=D[7])
                {
                    Ta=Ta+D[7]*T*Target->Up;
                    U=D[7];
                }else if(LV>D[7])
                {
                    float T1=fabs((D[7]-U))/D[6];
                    Ta=Ta+(0.5*D[6]*T1+D[7]*(T-T1))*Target->Up;
                    D[6]=D[7];
                }else{
                    Ta=Ta+(0.5*D[6]*T*T+U*T)*Target->Up;
                    U=LV;
                }
            }else Ta=Ta+D[7]*Target->Up;
            if(Move[5])
            {
                float LV=U-D[7]*T;
                if(U<=-D[7])
                {
                    Ta=Ta+D[7]*T*Target->Up;
                    U=-D[7];
                }else if(LV>D[7])
                {
                    float T1=fabs((D[7]-U))/D[6];
                    Ta=Ta+(-0.5*D[6]*T1-D[7]*(T-T1))*Target->Up;
                    D[6]=-D[7];
                }else{
                    Ta=Ta+(-0.5*D[6]*T*T+U*T)*Target->Up;
                    U=LV;
                }
            }else Ta=Ta-D[7]*Target->Up;
        }else{
            if(Move[4]) Ta=Ta+D[7]*Target->Up;
            if(Move[5]) Ta=Ta-D[7]*Target->Up;
        }
        //error<<"("<<Ta.X<<"  ,  "<<Ta.Y<<"  ,  "<<Ta.Z<<"  )  "<<endl;
        Target->Location=Target->Location+Ta;//XYZF(0.001,0.0,0.001);
    }
}
void FaceAngle::Change(long Tc,Angle* A, Coordinate* Target)
{
    float* T=AngleData;
    if(AngleT[0])
    {
        Target->Up=(Target->Left*sin(T[1]/180*3.141592)+Target->Up*cos(T[1]/180*3.141592653)).Uint();
        Target->Left=(Target->Up&Target->Front).Uint();
    }
    if(AngleT[1])
    {
        Target->Up=(Target->Left*sin(-T[1]/180*3.141592)+Target->Up*cos(-T[1]/180*3.141592653)).Uint();
        Target->Left=(Target->Up&Target->Front).Uint();
    }
    if(AngleT[2])
    {
        Target->Front=(Target->Left*sin(T[3]/180*3.141592)+Target->Front*cos(T[3]/180*3.141592653)).Uint();
        Target->Left=(Target->Up&Target->Front).Uint();
    }
    if(AngleT[3])
    {
        Target->Front=(Target->Left*sin(-T[3]/180*3.141592)+Target->Front*cos(-T[3]/180*3.141592653)).Uint();
        Target->Left=(Target->Up&Target->Front).Uint();
    }
    if(AngleT[4])
    {
        Target->Front=(Target->Up*sin(T[5]/180*3.141592)+Target->Front*cos(T[5]/180*3.141592653)).Uint();
        Target->Up=(Target->Front&Target->Left).Uint();
    }
    if(AngleT[5])
    {
        Target->Front=(Target->Up*sin(-T[5]/180*3.141592)+Target->Front*cos(-T[5]/180*3.141592653)).Uint();
        Target->Up=(Target->Front&Target->Left).Uint();
    }
}
void Translation::SetTranslation(MoveStyle St,float* Ter)
{
    Style=St;
    for(int i=0;i<8;++i)
    {
        TranslationData[i]=Ter[i];
    }
}
void FaceAngle::SetAngle(float* Ter)
{
    for(int i=0;i<6;++i)
    {
        AngleData[i]=Ter[i];
    }
}
#endif
