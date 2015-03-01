#ifndef DIY_STOREHOUSE_H
#define DIY_STOREHOUSE_H
class SingleShip;
enum GoodsStyle
{
    GMissile,
    GNormalGoods
};
class SGNS //GOODS NAME SIZE
{
    public:
        std::string Name;
        int Size;
        SGNS(std::string C="´íÎó",int S=0):Name(C),Size(S){}
};
class CGNS
{
    public:
        std::map<GoodsStyle,SGNS> Data;
        SGNS operator[] (GoodsStyle G)
        {
            SGNS Tem=Data[G];
            return Tem;
        }
        CGNS()
        {
            SGNS C("µ¼µ¯",0);
            Data.insert(make_pair(GMissile,C));
        }
}GNS;
class Goods
{
    public:
        GoodsStyle GS;
        operator GoodsStyle(){return GS;} 
        Goods(GoodsStyle G):GS(G){}
};
class Storehouse
{
    public:
        int MaxSpace;
        int LeftSpace;
        std::list< std::list<Goods> > Store;
        int Fund(GoodsStyle G)
        {
            for(std::list< std::list<Goods> >::iterator P=Store.begin();P!=Store.end();++P)
            {
                if(P->empty())
                {
                    Store.erase(P--);
                }else if(P->begin()->GS==G)
                {
                    return P->size();
                }
            }
            return 0;
        }
        void Insert(GoodsStyle G)
        {
            for(std::list< std::list<Goods> >::iterator P=Store.begin();P!=Store.end();++P)
            {
                if(P->begin()->GS==G)
                {
                    P->push_back(Goods(G));
                }
            }std::list<Goods> Tem;
            Store.push_back(Tem);
            (--Store.end())->push_back(Goods(G));
        }
        int Insert(GoodsStyle G,int n)
        {
            int N=GNS[G].Size*n;
            if(LeftSpace>=N)
            {
                for(int i=0;i<n;++i)
                {
                    Goods* Gd=new Goods(G);
                    Insert(G);
                }
                return n;
            }else   return 0;
        }
        int Destory(GoodsStyle G,int n)
        {
            for(std::list< std::list<Goods> >::iterator P=Store.begin();P!=Store.end();++P)
            {
                if(P->empty())
                {
                    Store.erase(P--);
                }else if(P->begin()->GS==G)
                {
                    if(P->size()>=n)
                    {
                        for(int i=0;i<n;++i)
                        {
                            P->pop_back();
                        }
                        if(P->empty())
                        {
                            Store.erase(P--);
                        }
                        return n;
                    }
                }
            }
            return 0;
        }
};
#endif
