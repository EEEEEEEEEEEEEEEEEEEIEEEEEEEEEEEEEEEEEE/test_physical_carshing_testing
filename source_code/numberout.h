#ifndef DIY_NUMBEROUT_H
#define DIY_NUMBEROUT_H
#include <stdio.h>
#include <string>
#include <list>
#include <map>
#include "sgprint.h"
#include "stdio.h"
#include "picture.h"
#define NUM_FLOAT 1
#define NUM_INT 2
class NumberOut
{
    int Mode;
    void* Point;
    Sentence3D Perfix;
    std::string St;
    static std::map<char,unsigned int> NumberModel;
    static unsigned int ModelPoint[12];
    static int PointNumber;
    public:
        bool Inable;
        void Set(void* Poi,const int Mode2);
        void Set(const std::string rr);
        void Off(void);
        void In(void);
        XYZF Show(const float X,const float Y,ControlCenter* CC,const float Size2);
        void Reflesh();
        NumberOut();
        ~NumberOut()
        {
            PointNumber-=1;
            if(PointNumber==0)
            {
                NumberModel.clear();
                for(int i=0;i<12;++i)
                {
                    glDeleteTextures(1,&(ModelPoint[i]));
                    ModelPoint[i]=0;
                }
            }
        }
};
std::map<char,unsigned int> NumberOut::NumberModel;
unsigned int NumberOut::ModelPoint[12];
int NumberOut::PointNumber=0;

class Number
{
    std::list<NumberOut> Data;
    std::map<int , std::list<NumberOut>::iterator > List;
    int NowUsing;
    ControlCenter* CC;
    public:
        Number();
        int Set(void* P,int Mode,std::string Perfix);
        XYZF Show(int Number, float X,float Y);
        void Init(ControlCenter* re);
        void Reflesh(int Number);
        void Reflesh(const int* ty,int Number);
        void In(int Number);
        void In(const int* ty,int Number);
        void Off(int Number);
        void Off(const int* ty,int Number);
};



void NumberOut::Set(void* Poi,const int Mode2)
{
    switch(Mode2)
    {
        case NUM_FLOAT:
            Point=Poi;
            Mode=Mode2;
            break;
        case NUM_INT:
            Point=Poi;
            Mode=Mode2;
    }
    Reflesh();
}
void NumberOut::Set(const std::string rr)
{
    Perfix.Delete();
    Perfix.Add(rr);
}
void NumberOut::Off(void)
{
    Inable=false;
}
void NumberOut::In(void)
{
    Inable=true;
}
XYZF NumberOut::Show(const float X,const float Y,ControlCenter* CC,const float Size2=0.1)
{
    if(NumberModel.empty())
    {
        //error<<"初始化~"<<endl;
        char Txt[]={'0','1','2','3','4','5','6','7','8','9','-','.'};
        for(int i=0;i<12;++i)
        {
            SDL_Surface *Texture;
            SDL_Surface *Back;
            int w;
            int h;
            float W;
            float H;
            unsigned int Point;
            std::string Tu;
            Tu=Tu+Txt[i];
            Texture = TTF_RenderUTF8_Blended( Perfix.Font() , Tu.c_str() , (SDL_Color){255,255,255} );
            w = static_cast<int>(pow(2,ceil(log(Texture->w)/log(2)))+0.5 );
            h = static_cast<int>(pow(2,ceil(log(Texture->h)/log(2)))+0.5 );
            W=static_cast<float>(Texture->w)/w;
            H=static_cast<float>(Texture->h)/h;
            Back=SDL_CreateRGBSurface(0,w,h,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
            SDL_BlitSurface(Texture,0,Back,0);
            void* PointForTexture= operator new[](sizeof(unsigned long*) * w*h*4);
            unsigned char* Poi= static_cast<unsigned char*> (PointForTexture);
            unsigned char* Poi2=static_cast<unsigned char*> (Back->pixels);
            for(int hh=0;hh< static_cast<int>(H*h*4);++hh)
            {
                for(int ww=0;ww< static_cast<int>(W*w);++ww)
                {
                    Poi[hh*w+ww*4]=Poi2[hh*w+ww*4];
                    Poi[hh*w+ww*4+1]=Poi2[hh*w+ww*4+1];
                    Poi[hh*w+ww*4+2]=Poi2[hh*w+ww*4+2];
                    if(Poi[hh*w+ww*4]!=0&&Poi[hh*w+ww*4+1]!=0&&Poi[hh*w+ww*4+2]!=0)
                    {
                        Poi[hh*w+ww*4+3]=255;
                    }else{
                        Poi[hh*w+ww*4+3]=0;
                    }
                }
            } 
            glGenTextures(1,&Point);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,Point);
            glTexImage2D(GL_TEXTURE_2D,0,4,w,h,0,GL_BGRA,GL_UNSIGNED_BYTE,PointForTexture);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glDisable(GL_TEXTURE_2D);
            SDL_FreeSurface(Texture);
            SDL_FreeSurface(Back);
            operator delete[] (PointForTexture);
            
            ModelPoint[i]=glGenLists(1);
            glNewList(ModelPoint[i],GL_COMPILE);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,Point);
            glColor4f(1.0,1.0,1.0,1.0);
            glBegin(GL_QUADS);
                glTexCoord2f(W,H);        glVertex2f(0.04,-0.1);  
                glTexCoord2f(W,0.0);      glVertex2f(0.04,0.0);                  
                glTexCoord2f(0.0,0.0);     glVertex2f(0.0,0.0);
                glTexCoord2f(0.0,H);       glVertex2f(0.0,-0.1);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glEndList();
            NumberModel.insert(std::make_pair(Txt[i],ModelPoint[i]));
        }
    }
    if(Inable)
    {
        //error<<"我来对了~"<<endl;
        int I=0;
        XYZF T=Perfix.Show(XYZF(X,Y,0.0),XYZF(0.0,-1.0,0.0),XYZF(0.0,0.0,1.0),1.0f,1.0f,1.0f,Size2);
        glPushMatrix();
        glTranslatef(T.X,T.Y,0.0);
        glColor4f(1.0,1.0,1.0,1.0);
        bool Shendu=glIsEnabled(GL_ALPHA_TEST);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GEQUAL, 0.9f);
        for(std::string::iterator Po=St.begin();Po!=St.end();++Po)
        {
            if(NumberModel.count(*Po)>0)
            {
                //error<<"12123"<<endl;
                glCallList(NumberModel[*Po]);
                glTranslatef(Size2*0.5,0.0,0.0);
            }
            ++I;
        }
        if(!Shendu) glDisable(GL_ALPHA_TEST);
        glPopMatrix();
        return T+XYZF(I*Size2,0.0,0.0);
                                                                                                                                                      
    }
    return XYZF(0.0,0.0,0.0);
}
void NumberOut::Reflesh()
{
    if(Inable)
    {
        float* F=static_cast<float*>(Point);
        int* I=static_cast<int*>(Point);
        char Tem[20];
        switch(Mode)
        {
            case NUM_FLOAT:
                sprintf(Tem, "%.4f",*F);
                St=Tem;
                break;
            case NUM_INT:
                sprintf(Tem, "%d",*I);
                St=Tem;
                break;
        }
    }
}
NumberOut::NumberOut()
{
    Inable=true;
    Mode=0;
    PointNumber+=1;
}










Number::Number()
{
    NowUsing=0;
}
int Number::Set(void* P,int Mode,std::string Perfix="")
{
    NumberOut Tr;
    Tr.Set(P,Mode);
    Tr.Set(Perfix);
    Tr.Off();
    Data.push_back(Tr);
    std::list<NumberOut>::iterator Tty=Data.end();
    Tty--;
    ++NowUsing;
    List.insert(make_pair(NowUsing,Tty));
    return NowUsing;
}
XYZF Number::Show(int Number, float X,float Y)
{
    if(List.count(Number)>0)
    {
        if(List[Number]->Inable)
        {
            return (List[Number])->Show(X,Y,CC);
        }else{
            return XYZF(0.0,0.0,0.0);
        }
    }else{
        return XYZF(0.0,0.0,0.0);
    }
}
void Number::Init(ControlCenter* re)
{
    CC=re;
}
void Number::Reflesh(int Number)
{
    if(List.count(Number)>0)
    {
        List[Number]->Reflesh();
    }
}
void Number::Reflesh(const int* ty,int Number)
{
    for(int i=0;i<Number;++i)
    {
        Reflesh(ty[i]);
    }
}


void Number::In(int Number)
{
    if(List.count(Number)>0)
    {
        List[Number]->In();
    }
}
void Number::In(const int* ty,int Number)
{
    for(int i=0;i<Number;++i)
    {
        In(ty[i]);
    }
}
void Number::Off(int Number)
{
    if(List.count(Number)>0)
    {
        List[Number]->Off();
    }
}
void Number::Off(const int* ty,int Number)
{
    for(int i=0;i<Number;++i)
    {
        Off(ty[i]);
    }
}

#endif
