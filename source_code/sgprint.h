#ifndef  DIY_SGPRINT_H 
#define  DIY_SGPRINT_H 
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include "language.h"
#include "baseclass.h"
#include "information.h"
#include "SDL/SDL_ttf.h"
//#include "SDL/SDL_image.h"
//#include "picture.h"
bool PReadyToUse=false;
void SGTTF_Init ( )
{
    TTF_Init() ;
    atexit( TTF_Quit );
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    PReadyToUse=true;
}
class Sentence
{
    protected:
        unsigned int Point;
        std::string Data;
        static TTF_Font *font;
        float W;
        float H;
    public:
        void Add(std::string, TTF_Font*);
        XYF Show( float X ,float Y , float R,float G,float B,float Size,TTF_Font* Font);
        XYF Show( XYF Tem,float R,float G,float B,float Size,TTF_Font* Font);
        TTF_Font* Font(){return font;}
        void Delete();
        Sentence(const Sentence& Tem);
        Sentence();
        ~Sentence();
};
class Sentence3D:public Sentence
{
    public:
        XYZF Show( const XYZF Local , 
                 const XYZF Target2 ,
                   const  XYZF Face ,
                         float R,
                         float G,
                         float B,
                    float Size ,
                  TTF_Font* Font);//Target是指向下 ;
};
TTF_Font* Sentence::font=NULL;















        void Sentence::Add(std::string data , TTF_Font* Font=font )
        {
            Data=data;
            if(Point!=0)
            {
                Delete();
            }
            if(PReadyToUse)
            {
                SDL_Surface *Texture;
                SDL_Surface *Back;
                int w;
                int h;
                Texture = TTF_RenderUTF8_Blended( Font , GbToUTF(Data).c_str() , (SDL_Color){255,255,255} );
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
            }
        }
        
        XYF Sentence::Show( float X ,float Y , float R,float G,float B,float Size=0.2,TTF_Font* Font=font)
        {
            if(PReadyToUse)
            {
                //er<<"是的！"<<endl;
                bool Shendu=glIsEnabled(GL_ALPHA_TEST);
                glEnable(GL_ALPHA_TEST);  
                glAlphaFunc(GL_GEQUAL, 0.2f); 
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,Point);
                glColor4f(R,G,B,1.0);
                glBegin(GL_QUADS);
                    glTexCoord2f(W,H);        glVertex2f(X+Data.size()*Size*0.4,Y-Size);  
                    glTexCoord2f(W,0.0);      glVertex2f(X+Data.size()*Size*0.4,Y);                  
                    glTexCoord2f(0.0,0.0);     glVertex2f(X,Y);
                    glTexCoord2f(0.0,H);       glVertex2f(X,Y-Size);
                glEnd();
                glDisable(GL_TEXTURE_2D);
                if(!Shendu)glDisable(GL_ALPHA_TEST);
                return XYF(X+Data.size()*Size*0.4,Y);
            }
            return XYF(0.0,0.0);
        }
        
        XYF Sentence::Show( XYF Tem,float R,float G,float B,float Size=0.2,TTF_Font* Font=font)
        {
            return Show(Tem.X,Tem.Y,R,G,B,Size,Font);
        }
        void Sentence::Delete()
        {
            if(Point!=0)
            {
                glDeleteTextures(1,&Point);
                Point=0;
            }
        }
        Sentence::Sentence(const Sentence& Tem)
        {
            Add(Tem.Data);
        }
        
        Sentence::Sentence():Point(0)
        {
            if(!PReadyToUse)
            {
                SGTTF_Init();
                font=TTF_OpenFont("simhei.ttf",50);
                if(!font)
                {
                    font=TTF_OpenFont("c:\\WINDOWS\\Fonts\\SIMKAI.TTF",50);
                    if(!font)
                    {
                        font=TTF_OpenFont("d:\\WINDOWS\\Fonts\\SIMKAI.TTF",50);
                    }
                }
            }
        }
        Sentence::~Sentence()
        {
            if(Point!=0)
            {
                glDeleteTextures(1,&Point);
            }
        }
        XYZF Sentence3D::Show( const XYZF Local , const XYZF Target2 ,const  XYZF Face ,float R=1.0,float G=1.0,float B=1.0,float Size=0.02 ,TTF_Font* Font=font)//Target是指向下 
        {
            if(PReadyToUse)//&&Point!=0)
            {
                bool Shendu=glIsEnabled(GL_ALPHA_TEST);
                XYZF Target=Target2;
                XYZF Crosswise=Face&Target;
                Crosswise=Crosswise.Uint(Size*0.4);
                Target=Target.Uint(Size);
                glEnable(GL_ALPHA_TEST);
                glAlphaFunc(GL_GEQUAL, 0.9f); 
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D,Point);
                glColor4f(R,G,B,1.0);
                glBegin(GL_QUADS);
                    glNormal(Face);
                    glTexCoord2f(W,H);        glVertex(Local+Crosswise*Data.size()+Target);  
                    glTexCoord2f(W,0.0);      glVertex(Local+Crosswise*Data.size());                   
                    glTexCoord2f(0.0,0.0);    glVertex(Local);
                    glTexCoord2f(0.0,H);      glVertex(Local+Target);
                glEnd();
                glDisable(GL_TEXTURE_2D);
                if(!Shendu) glDisable(GL_ALPHA_TEST);
                return XYZF(Local+Crosswise*Data.size());
            }
            return XYZF(0.0,0.0,0.0);
        }
#endif
