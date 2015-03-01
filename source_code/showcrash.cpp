void ShowCrash(CrashData* Tem)
{
        glColor3f(1.0,1.0,0.0);
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<=30;++i)
        {
            XYZF Tree(Tem->CFD->Distance*sin(i/15.0*3.141592653),0.0,Tem->CFD->Distance*cos(i/15.0*3.141592653));
            Tree=Tree+Tem->Location;
            Tree.Y=0.0;
            glVertex(Tree);
        }
        glEnd();
    if(!Tem->CFD->FaceData.empty())
    {
        glColor3f(1.0,0.0,1.0);
        for(std::list<CrashFace>::iterator Pc=Tem->CFD->FaceData.begin();Pc!=Tem->CFD->FaceData.end();++Pc)
        {
            glBegin(GL_LINE_LOOP);
            for(std::vector<CrashSingleData>::iterator Pi=Pc->Data.begin();Pi!=Pc->Data.end();++Pi)
            {
                XYF Ter=*Pi;
                XYZF Tree(Ter.X,0.0,Ter.Y);
                Tree=Pc->FromCoordinate(Tree);
                Tree=Tem->FromCoordinate(Tree);
                glVertex(Tree);
            }
            glEnd();
        }
    }
}
