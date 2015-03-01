class MoveControl:public Software
{
    public:
        void Analyze(SingleShip*,void*);
}MC;
void MoveControl::Analyze(SingleShip* SS,void* D)
{
    float M=SS->Quality;
    float P=SS->Push;
    SS->Mo.TranslationData[0]=P/M/0.1;
    SS->Mo.Change(SS->Time,SS,&SS->Next);
}
