#ifndef DIY_LIGHT_H
#define DIY_LIGHT_H
#include "baseclass.h"
#include "plugin_base.h"
#include "glsimplify.h"
class Light:public Plugin_Base
{
    bool Reflesh;
    float LightPosition[3];
    float LightAmbient[4];
    float LightDiffuse[4];
    float LightFace[3];
    float LightSpecular[4];
    public:
        void Init(ControlCenter* Data)
        {
            /*glLightModelfv(GL_LIGHT_MODEL_AMBIENT,LightDiffuse);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, LightSpecular);
            glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40.0f);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightFace);*/
            
            glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
            glLightfv(GL_LIGHT1, GL_POSITION,LightPosition); // 设置光源位置
            /*glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5f);
            glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5f);
            glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2f);
            glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0f);*/
            glEnable(GL_LIGHT1);
            
            /*glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 40.0f);
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightFace);
            glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
            glLightfv(GL_LIGHT0, GL_POSITION,LightPosition); // 设置光源位置
            glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5f);
            glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5f);
            glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2f);
            glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);
            glEnable(GL_LIGHT0);*/
            
            
            glEnable(GL_LIGHTING);
            glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT);
            glEnable(GL_COLOR_MATERIAL);
        }
        void Show(ControlCenter* Data)
        {
            //glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, LightFace);
            glBlendFunc(GL_SRC_ALPHA,GL_ONE);
            glEnable(GL_ALPHA_TEST); 
            glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
        }
        void Analyze(ControlCenter* Data)
        {
            Information Tem=GetInformation();
        }
        Light():Plugin_Base("Light")
        {
            *LightDiffuse=1.0f;
            *(LightDiffuse+1)=1.0f;
            *(LightDiffuse+2)=1.0f;
            *(LightDiffuse+3)=0.5f;
            *(LightAmbient+0)=0.5f;
            *(LightAmbient+1)=0.5f;
            *(LightAmbient+2)=0.5f;
            *(LightAmbient+3)=0.5f;
            *(LightFace)=0.0;
            *(LightFace+1)=0.0;
            *(LightFace+2)=-1.0;
            *(LightSpecular+0)=1.0f;
            *(LightSpecular+1)=1.0f;
            *(LightSpecular+2)=1.0f;
            *(LightSpecular+3)=1.0f;
            *(LightPosition+0)=0.0f;
            *(LightPosition+1)=0.0f;
            *(LightPosition+2)=0.0f;
            
        }
};




#endif
