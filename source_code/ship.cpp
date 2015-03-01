void SingleShip::Show(Coordinate* Co)
{
    for(std::list<PreExpand*>::const_iterator Po=Ex.begin();Po!=Ex.end();++Po)
    {
        if((*Po)->Sho) (*Po)->Show(this,NULL);
    }
}
void SingleShip::Analyze(void)
{
    for(std::list<PreExpand*>::const_iterator Po=Ex.begin();Po!=Ex.end();++Po)
    {
        (*Po)->Preanalyze(this);
    }
    Brain::Analyze(this);
    Time=SDL_GetTicks()-LastTime;
    LastTime+=Time;
    Up=Next.Up;
    Front=Next.Front;
    Left=Next.Left;
    Location=Next.Location;
    LastTime=SDL_GetTicks();
}
