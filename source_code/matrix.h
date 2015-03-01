//矩阵 
#ifndef DIY_MATRIX_H
#define DIY_MATRIX_H
#define MNULL 0
#include "detaminate.h"
//因为误差的缘故，如果求逆矩阵用“XX.Adj()/XX.Det()”比“!XX”效果好 
class Matrix
{
    unsigned int H;
    unsigned int L;
    void* Data;
    bool Right;
    public:
        Matrix(int H,int L);
        Matrix(int H,int L,const double* Data);
        Matrix(const Matrix&);
        
        void Reset(int H,int L);
        void Reset(int H,int L,const double* Tem);
        inline void Reset(const Matrix& Tem);
        
        ~Matrix();
        
        Matrix operator+ (const Matrix&) const;
        Matrix operator* (const Matrix&) const;
        Matrix operator~ (void) const;//转置矩阵 
        Matrix& operator= (const Matrix&);
        Matrix operator* (double Numb) const;
        Matrix operator/ (double Numb) const;
        double& operator[](const int H) const;
        Matrix operator! (void);//逆矩阵 未完成 
        
        
        double& Call(unsigned int H,unsigned int L);
        
        void HAdd(double Number,unsigned int H1,unsigned int H2);//将H2乘以NUMBER加到H上 //未测试 
        void LAdd(double Number,unsigned int L1,unsigned int L2);                        //未测试 
        
        Matrix Cof(unsigned int H2,unsigned int L2) const; //代数余子式 
        Matrix Adj(void);//伴随矩阵 
        double Det();//行列式的值 
        
        double* Point(void) const;//返回指向矩阵数据的指针，按行至列的排列。 
        void Check()
        {
            double* ty=Point();
            for(int i=0;i<H;++i)
            {
                tt<<" | ";
                for(int k=0;k<L;++k)
                {
                    tt<<ty[i*L+k]<<" ";
                }
                tt<<" | "<<endl;
            }
            tt<<endl;
        }
};



Matrix Matrix::operator!(void)
{
    Matrix Tem(*this);
    if(Right&&L==H)
    {
        double D=Det();
        if(D!=0)
        {
            Tem.Reset(Adj());
            //tt<<"逆矩阵"<<endl; 
            (Tem/D).Check();
            return Tem/D;
        }
    }
    Tem.Right=false;
    return Tem;
}
void Matrix::HAdd(double Number,unsigned int H1,unsigned int H2)
{
    double* PH=Point();
    for(int i=0;i<L;++i)
    {
        PH[(H1-1)*L+i]=PH[(H1-1)*L+i]+PH[(H2-1)*L+i]*Number;
    }
}
void Matrix::LAdd(double Number,unsigned int L1,unsigned int L2)
{
    double* PH=Point();
    for(int i=0;i<H;++i)
    {
        PH[(L1-1)+i*H]=PH[(L1-1)+i*H]+PH[(L2-1)+i*H]*Number;
    }
}
double& Matrix::Call(unsigned int H2,unsigned int L2)
{
    return *(Point()+(L2-1)+(H2-1)*H);
}
Matrix::Matrix(int C2=0,int K2=0)
{
    H=C2;
    L=K2;
    Data=operator new [](sizeof(double)*L*H);
    Right=true;
}
Matrix::Matrix(int C2,int K2,const double* Tem)
{
    Right=true;
    H=C2;
    L=K2;
    Data=operator new[](sizeof(double)*L*H);
    double* Num=static_cast<double*>(Data);
    for(int i=0;i<H;++i)
    {
        for(int k=0;k<L;++k)
        {
            Num[i*L+k]=Tem[i*L+k];
        }
    }
}
Matrix::Matrix(const Matrix& Tem)
{
    L=Tem.L;
    H=Tem.H;
    Right=Tem.Right;
    Data=operator new[](sizeof(double)*L*H);
    double* Num=static_cast<double*>(Data);
    double* Num2=Tem.Point();
    for(int i=0;i<H;++i)
    {
        for(int k=0;k<L;++k)
        {
            Num[i*L+k]=Num2[i*L+k];
        }
    }
}
void Matrix::Reset(int C2,int K2)
{
    Right=true;
    H=C2;
    L=K2;
    if(Data!=MNULL)
    {
        operator delete[](Data);
        Data=MNULL;
    }
}
void Matrix::Reset(int C2,int K2,const double* Tem)
{
    Right=true;
    H=C2;
    L=K2;
    if(Data!=MNULL)
    {
        operator  delete[](Data);
        Data=MNULL;
    }
    Data=operator new[](sizeof(double)*L*H);
    double* Num=static_cast<double*>(Data);
    for(int i=0;i<H;++i)
    {
        for(int k=0;k<L;++k)
        {
            Num[i*L+k]=Tem[i*L+k];
        }
    }
}
void Matrix::Reset(const Matrix& Tem)
{
    Reset(Tem.H,Tem.L,Tem.Point());
}
Matrix::~Matrix()
{
    if(Data!=MNULL)    operator delete[](Data);
}
Matrix Matrix::operator+ (const Matrix& Te) const
{
    Matrix Ty(H,L);
    if(L==Te.L&&H==Te.H&&Right&&Te.Right)
    {
        double* Num=static_cast<double*>(Data);
        double* Num2=Te.Point();
        double* Num3=Ty.Point();
        for(int i=0;i<L*H;++i)
        {
            Num3[i]=Num[i]+Num2[i];
        }
    }else{
        Ty.Right=false;
    }
    return Ty;
}
Matrix Matrix::operator* (const Matrix& Te) const
{
    Matrix Ty(H,Te.L);
    if(L==Te.H&&Right&&Te.Right)
    {
        double* Num=static_cast<double*>(Data);
        double* Num2=Te.Point();
        double* Num3=Ty.Point();
        for(int i=0;i<H;++i)//还需要修改。 
        {
            for(int k=0;k<Te.L;++k)
            {
                double Temporary2=0.0;
                for(int j=0;j<L;++j)
                {
                    Temporary2+=Num[i*L+j]*Num2[k+j*Te.L];
                }
                Num3[i*L+k]=Temporary2;
            }
        }
    }else{
        Ty.Right=false;
    }
    return Ty;
}
double* Matrix::Point(void) const
{
    return static_cast<double*>(Data);
}
Matrix Matrix::operator~ (void) const//转置矩阵 
{
    Matrix Ty(L,H);
    double* Num=Point();
    double* Num2=Ty.Point();
    for(int i=0;i<H;++i)
    {
        for(int k=0;k<L;++k)
        {
            Num2[i+k*H]=Num[i*L+k];
        }
    }
    return Ty;
}
double Matrix::Det()
{
    if(H==L&&Right)
    {
        Detaminate Tc(H,Point());
        return Tc.Value();
    }else{
        return 0.0;
    }
}
Matrix Matrix::Cof(unsigned int H2,unsigned int L2) const //余子式 
{
    if(H>=2&&L>=2&&H2>=1&&H2<=H&&L2>=1&&L2<=L)
    {
        Matrix Tr(H-1,L-1);
        double* Ty=Tr.Point();
        double* Num=Point();
        for(int i=0,t=0;i<H;++i)
        {
            for(int k=0;k<L;++k)
            {
                if(i!=H2-1&&k!=L2-1)
                {
                    Ty[t]=Num[i*L+k];
                    ++t;
                }
            }
        }
        return Tr;
    }else if(H==1&&L==1)
    {
        double Tu=1.0f;
        Matrix Tr(1,1,&Tu);
        return Tr;
    }else{
        return *this;
    }
}
Matrix Matrix::Adj(void)//伴随矩阵 
{
    Matrix Tr(H,L);
    if(H==L&&H>=2&&L>=2)
    {
        const double te=Det();
        if(te!=0)
        {
            double* Rt=Tr.Point();
            double* Num=Point();
            for(int i=0;i<H;++i)
            {
                for(int k=0;k<L;++k)
                {
                    if((i+k)%2==1)
                        Rt[i*L+k]=(Cof(i+1,k+1)).Det()*(-1);
                    else
                        Rt[i*L+k]=(Cof(i+1,k+1)).Det();
                }
            }
            //tt<<"伴随矩阵"<<endl;
            (~Tr).Check();
            return ~Tr;
        }
    }
    Tr.Right=false;
    return Tr;
}
Matrix& Matrix::operator= (const Matrix& Ty)
{
    Reset(Ty.H,Ty.L,Ty.Point());
    return *this;
}
Matrix Matrix::operator* (double Numb) const
{
    Matrix Tr(*this);
    double* Trr=Tr.Point();
    for(int i=0;i<H*L;++i)
    {
        (Trr[i])*=Numb;
    }
    return Tr;
}
Matrix Matrix::operator/ (double Numb) const
{
    Matrix Tr(*this);
    double* Trr=Tr.Point();
    for(int i=0;i<H*L;++i)
    {
        (Trr[i])/=Numb;
    }
    return Tr;
}
double& Matrix::operator[](const int Size) const
{
    return *(Point()+Size);
}
#endif
