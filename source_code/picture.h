#ifndef DIY_PICTURE_H
#define DIY_PICTURE_H
#include <SDL/SDL_image.h>
#define IMG_NOKEY 0
#define IMG_KEY 1
#define WUCHA 20
#define UPDOWN 125
#define LEFTRIGHT 78
#include "baseclass.h"
bool PictureReady=false;
class Picture
{
    protected:
    float W;
    float H;
    float Big;
    float AXS;
    float AYS;
    float AXE;
    float AYE;
    bool UpsideDown;
    bool Perverted;
    std::vector<float> Cut;
    bool NormalCut;
    bool KillColor;
    std::string Name;
    public:
        unsigned int Point;
    void Bigger(float Bigg)
    {
        Big=Bigg;
    }
    void Cutting(float XS , float YS , float XE , float YE)
    {
        NormalCut=true;
        AXE=XE;
        AYS=YS;
        AXS=XS;
        AYE=YE;
    }
    void Cutting(float* DataPoint,int size)
    {
        NormalCut=false;
        Cut.clear();
        std::vector<float> Tem(DataPoint,DataPoint+size);
        Cut=Tem;
    }
    void Cutting(std::vector<float>& Tem)
    {
        NormalCut=false;
        Cut.clear();
        Cut=Tem;
    }
    void Turn(int Mode)
    {
        if(Mode==UPDOWN)
        {
            UpsideDown=(!UpsideDown);
        }else if(Mode==LEFTRIGHT)
        {
            Perverted=(!Perverted);
        }
    }
    void Load(std::string File , float TM=1.0)
    {
        KillColor=false;
        Name=File;
        AXS=0.0;
        AYS=1.0;
        AXE=1.0;
        AYE=0.0;
        NormalCut=true;
        UpsideDown=false;
        Perverted=false;
        if(PictureReady)
        {
            if(Point!=0)
            {
                glDeleteTextures(1,&Point);
            }
            SDL_Surface* Picture = IMG_Load(Name.c_str());
            SDL_Surface* TT=SDL_DisplayFormat(Picture);
            SDL_FreeSurface(Picture);
            int w;
            int h;
            w = static_cast<int>(pow(2,ceil(log(Picture->w)/log(2)))+0.5 );
            h = static_cast<int>(pow(2,ceil(log(Picture->h)/log(2)))+0.5 );
            W=static_cast<float>(Picture->w)/w;
            H=static_cast<float>(Picture->h)/h;
            SDL_Surface* Back = SDL_CreateRGBSurface (0,w,h,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
            SDL_BlitSurface(TT,0,Back,0);
            glGenTextures(1,&Point);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,Point);
            glTexImage2D(GL_TEXTURE_2D,0,4,w,h,0,GL_BGRA,GL_UNSIGNED_BYTE,Back->pixels);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            SDL_FreeSurface(TT);
            SDL_FreeSurface(Back);
        }
    }
    void Load(std::string File ,unsigned char R, unsigned char G,unsigned char B,float TM=1.0)
    {
        KillColor=true;
        Name=File;
        AXS=0.0;
        AYS=1.0;
        AXE=1.0;
        AYE=0.0;
        NormalCut=true;
        UpsideDown=false;
        Perverted=false;
        if(PictureReady)
        {
            if(Point!=0)
            {
                glDeleteTextures(1,&Point);
            }
            SDL_Surface* Picture = IMG_Load(Name.c_str());
            int w;
            int h;
            w = static_cast<int>(pow(2,ceil(log(Picture->w)/log(2)))+0.5 );
            h = static_cast<int>(pow(2,ceil(log(Picture->h)/log(2)))+0.5 );
            W=static_cast<float>(Picture->w)/w;
            H=static_cast<float>(Picture->h)/h;
            SDL_Surface* Back = SDL_CreateRGBSurface (0,w,h,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
            SDL_Surface* TT=SDL_DisplayFormat(Picture);
            SDL_FreeSurface(Picture);
            SDL_BlitSurface(TT,0,Back,0);
            void* PointForTexture= operator new[](sizeof(unsigned long*) * w*h*4);
            unsigned char* Poi= static_cast<unsigned char*> (PointForTexture);
            unsigned char* Poi2=static_cast<unsigned char*> (Back->pixels);
            for(int hh=0;hh< static_cast<int>((H*h+1)*4);++hh)
            {
                for(int ww=0;ww< static_cast<int>(W*w+1);++ww)
                {
                    Poi[hh*w+ww*4]=Poi2[hh*w+ww*4];
                    Poi[hh*w+ww*4+1]=Poi2[hh*w+ww*4+1];
                    Poi[hh*w+ww*4+2]=Poi2[hh*w+ww*4+2];
                    if(Poi[hh*w+ww*4]>B-WUCHA&&Poi[hh*w+ww*4+1]>G-WUCHA&&Poi[hh*w+ww*4+2]>R-WUCHA&&Poi[hh*w+ww*4]<B+WUCHA&&Poi[hh*w+ww*4+1]<G+WUCHA&&Poi[hh*w+ww*4+2]<R+WUCHA)
                    {
                        Poi[hh*w+ww*4+3]=0;
                    }else{
                        Poi[hh*w+ww*4+3]=255;
                    }
                }
            } 
            glGenTextures(1,&Point);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,Point);
            glTexImage2D(GL_TEXTURE_2D,0,4,w,h,0,GL_BGRA,GL_UNSIGNED_BYTE,PointForTexture);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            SDL_FreeSurface(TT);
            SDL_FreeSurface(Back);
            operator delete[] (PointForTexture);
        }
    }
    void Show(float XS,float YS,float XE,float YE,float TM=1.0)
    {
        if(Point!=0&&NormalCut)
        {
            float SX=AXS;
            float EX=AXE;
            float SY=AYS;
            float EY=AYE;
            if(UpsideDown)
            {
                SY=AYE;
                EY=AYS;
            }
            if(Perverted)
            {
                SX=AXE;
                EX=AXS;
            }
            bool Alpha=false;
            bool Kill=false;
                if(KillColor)
                {
                    Alpha=glIsEnabled(GL_ALPHA_TEST);
                    glAlphaFunc(GL_GEQUAL, 0.5f); 
                    glEnable(GL_ALPHA_TEST);
                }
                Kill=glIsEnabled(GL_CULL_FACE);
                glDisable(GL_CULL_FACE);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,Point);
                glColor4f(1.0,1.0,1.0,TM);
                glBegin(GL_QUADS);
                    glTexCoord2f(SX*W,EY*H);     glVertex2f(XS,YS);
                    glTexCoord2f(SX*W,SY*H);       glVertex2f(XS,YE);
                    glTexCoord2f(EX*W,SY*H);         glVertex2f(XE,YE);
                    glTexCoord2f(EX*W,EY*H);       glVertex2f(XE,YS);
                glEnd();
                glDisable(GL_TEXTURE_2D);
                if(KillColor&&(!Alpha))
                {
                    glDisable(GL_ALPHA_TEST);
                }
                if(Kill)
                {
                    glEnable(GL_CULL_FACE);
                }
        }
        
    }
    void Show(std::vector<XYF> Tem ,float TM)
    {
    }
    void Delete()
    {
        if(Point!=0)
        {
            glDeleteTextures(1,&Point);
            Point=0;
        }
    }
    Picture():Point(0),AXS(0.0),AYS(1.0),AXE(1.0),AYE(0.0),Big(1.0),NormalCut(true),KillColor(false),UpsideDown(false),Perverted(false)
    {
        if(!PictureReady)
        {
            IMG_Init(IMG_INIT_JPG||IMG_INIT_PNG||IMG_INIT_TIF);
            atexit(IMG_Quit);
            PictureReady=true;
        }
    }
    ~Picture()
    {
        if(Point!=0)
        {
            glDeleteTextures(1,&Point);
        }
    }
};
class Picture3D:public Picture//起始坐标，竖直方向，水平方向 
{
    public:
    void Show(XYZF Te,XYZF Tr,XYZF yy)//Te是空间起点坐标，Tr是水平平移量，yy是竖直 
    {
        if(Point!=0&&NormalCut)
        {
            float SX=AXS;
            float EX=AXE;
            float SY=AYS;
            float EY=AYE;
            
            if(UpsideDown)
            {
                SY=AYE;
                EY=AYS;
            }
            if(Perverted)
            {
                SX=AXE;
                EX=AXS;
            }
                        bool Alpha=false;
                        bool Kill=false;
                if(KillColor)
                {
                    Alpha=glIsEnabled(GL_ALPHA_TEST);
                    glAlphaFunc(GL_GEQUAL, 0.5f); 
                    glEnable(GL_ALPHA_TEST);
                }
                Kill=glIsEnabled(GL_CULL_FACE);
                glDisable(GL_CULL_FACE);
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,Point);
                glColor4f(1.0,1.0,1.0,1.0);
                glBegin(GL_QUADS);
                    glNormal(yy&Tr);
                    glTexCoord2f(SX*W,EY*H);     glVertex(Te);
                    glTexCoord2f(SX*W,SY*H);     glVertex(Te+Tr);
                    glTexCoord2f(EX*W,SY*H);     glVertex(Te+Tr+yy);
                    glTexCoord2f(EX*W,EY*H);     glVertex(Te+yy);
                glEnd();
                glDisable(GL_TEXTURE_2D);
                if(KillColor&&(!Alpha))
                {
                    glDisable(GL_ALPHA_TEST);
                }
                                if(Kill)
                {
                    glEnable(GL_CULL_FACE);
                }
        }
    }
};
#endif
