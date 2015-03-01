//ÐÐÁÐÊ½ 
#ifndef DIY_DETAMINATE_H
#define DIY_DETAMINATE_H
#include <math.h>
#define DNULL 0

class Detaminate
{
    unsigned int J;
    void* Data;
    double NN;
    double GetValue(Detaminate& Te)
    {
        if(Te.J==2)
        {
            double* Tem=Te.Point();
            //tt<<Tem[0]*Tem[3]-Tem[1]*Tem[2]<<endl;
            return Tem[0]*Tem[3]-Tem[1]*Tem[2];
        }else{
            double All=0.0f;
            for(int i=0;i<Te.J;++i)
            {
                void* Daa=operator new[](sizeof(double)*(Te.J-1)*(Te.J-1));
                double* tt=static_cast<double*>(Daa);
                double* ii=Te.Point();
                for(int c=0,t=0;c<Te.J;++c)
                {
                    for(int k=0;k<Te.J;++k)
                    {
                        if(c!=0&&k!=i)
                        {
                            tt[t]=ii[c*Te.J+k];
                            ++t;
                        }
                    }
                }
                Detaminate Ty(Te.J-1,tt);
                operator delete[](Daa);
                if(ii[i]!=0.0)    All+=pow(-1,i)*GetValue(Ty)*ii[i];
            }
            return All;
        }
    }
    public:
        double* Point(void)
        {
            double* Te=static_cast<double*>(Data);
            return Te;
        }
        double Value(void)
        {
            if(J<=0)
            {
                return 0;
            }else if(J==1)
            {
                return *(Point());
            }else{
                return GetValue(*this);
            }
        }
        Detaminate(unsigned int K,const double* Te)
        {
            J=K;
            NN=-1.0f;
            Data=operator new[](sizeof(double)*J*J);
            double* Tr=Point();
            for(int i=0;i<J*J;++i)
            {
                Tr[i]=Te[i];
            }
           /* for(int i=0;i<J;++i)
            {
                tt<<"|   ";
                for(int k=0;k<J;++k)
                {
                    tt<<Tr[i*J+k]<<"  ";
                }
                tt<<"|   "<<endl;
            }
            tt<<endl;*/
        }
        ~Detaminate()
        {
            if(Data!=DNULL)
            {
                operator delete[](Data);
                Data=DNULL;
            }
        }
        inline unsigned Call(unsigned int H,unsigned int L)
        {
            return H*J+L;
        }
};
#endif
