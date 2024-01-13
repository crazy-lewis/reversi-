#include "ai.h"

ai::ai() {}

#include <stdio.h>

bool ai::inside(int x,int y)
{
    return x>=0&&y>=0&&x<8&&y<8;
}
int ai::check_bj(int sz[8][8],int x,int y,int z)
{
    if(sz[x][y])return false;
    int rt=0;
    for(int a=-1;a<=1;a++)
    {
        for(int b=-1;b<=1;b++)
        {
            if(a==0&&b==0)continue;
            int i=x+a,j=y+b;
            while(inside(i,j)&&sz[i][j]==(z^3))i+=a,j+=b;
            if(inside(i,j)&&sz[i][j]==z&&(x+a!=i||y+b!=j))
            {
                i-=a;j-=b;
                while(i!=x||j!=y)
                {
                    bj[i][j]=1;
                    i-=a,j-=b;rt+=1;
                }
            }
        }
    }
    return rt;
}
bool ai::check(int sz[8][8],int x,int y,int z)
{
    if(sz[x][y])return false;
    for(int a=-1;a<=1;a++)
    {
        for(int b=-1;b<=1;b++)
        {
            if(a==0&&b==0)continue;
            int i=x+a,j=y+b;
            while(inside(i,j)&&sz[i][j]==(z^3))i+=a,j+=b;
            if(inside(i,j)&&sz[i][j]==z&&(x+a!=i||y+b!=j))
                return true;
        }
    }
    return false;
}
void ai::mark(int sz[8][8],int x,int y,int z,bool tr)
{
    sz[x][y]=z;
    for(int a=-1;a<=1;a++)
    {
        for(int b=-1;b<=1;b++)
        {
            if(a==0&&b==0)continue;
            int i=x+a,j=y+b;
            while(inside(i,j)&&sz[i][j]==(z^3))i+=a,j+=b;
            if(inside(i,j)&&sz[i][j]==z)
            {
                i-=a;j-=b;
                while(i!=x||j!=y)
                {
                    sz[i][j]=z;
                    if(tr)st[tp++]=(i<<3)|j;
                    i-=a,j-=b;
                }
            }
        }
    }
}
void ai::makee1()
{
    for(int i=0;i<8;i++)
        e1[i]=0;
    for(int i=0,e;i<8;i++)
    {
        e=e0[i];e1[i]|=(e<<1)|(e>>1);
        if(i)e1[i-1]|=e|(e<<1)|(e>>1);
        if(i<7)e1[i+1]|=e|(e<<1)|(e>>1);
    }
}
bool ai::isstable(int sz[8][8],int x,int y)
{
    int c=sz[x][y];
    bool all=1;
    for(int s=0;s<8;s++)
    {
        int a=ne[s][0],b=ne[s][1],i=x,j=y;
        bool f1=0;
        while(inside(i,j)&&sz[i][j]!=0)
        {
            if(sz[i][j]==(c^3))f1=1;
            i+=a,j+=b;
        }
        if(inside(i,j)&&sz[i][j]==0&&!f1)
            return false;
        if(inside(i,j)&&sz[i][j]==0)all=0;
    }
    if(all)(c==1?st1:st2)+=1;
    return true;
}
int ai::calpts(int sz[8][8],int cc,bool ed)
{
    int jg=0,c1=0,c2=0;
    for(int i=0;i<8;i++)e0[i]=bi3[i]=bj3[i]=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(sz[i][j]==1)jg+=pts[i][j],c1+=1;
            else if(sz[i][j]==2)jg-=pts[i][j],c2+=1;
            if(sz[i][j])e0[i]|=(1<<j);
            else bi3[i]=bj3[j]=1;
        }
    if(ED||ed||c1+c2==64||c1==0||c2==0)
        return 1e6*(c1-c2);
    bool fd=0;makee1();
    double t=(c1+c2)/10.0;int xd=2*t*t*t+5*(t+1);
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)bj[i][j]=0;
    int x1=0,x2=0,j1=0,j2=0;
    for(int i=0,h,s;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(((e1[i]>>j)&1)==0||sz[i][j])continue;
            h=0;
            if(s=check_bj(sz,i,j,1))
            {
                x1+=1;fd=1;
                if((i==0||i==7)&&(j==0||j==7))
                {
                    h+=1;x1+=1;
                    jg+=s*s*50;
                }
            }
            if(s=check_bj(sz,i,j,2))
            {
                x2+=1;fd=1;
                if((i==0||i==7)&&(j==0||j==7))
                {
                    h-=1;x2+=1;
                    jg-=s*s*50;
                }
            }
            if(h==1)j1+=1;
            else if(h==-1)j2+=1;
        }
    if(!fd)return 1e6*(c1-c2);
    jg+=((1<<j1)-(1<<j2))*3000;
    double tt=((x1+0.5)/(x2+0.5)-(x2+0.5)/(x1+0.5));
    jg+=tt*abs(tt)*xd/10+xd*(x1-x2);
    int b1=0,b2=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(bj[i][j]&&sz[i][j]==1)b1+=1;
            else if(bj[i][j]&&sz[i][j]==2)b2+=1;
    jg+=(double(b2)/c1-double(b1)/c2)*(7-t)*20;
    jg+=(double(x1)/c1-double(x2)/c2)*(7-t)*20;
    //jg+=(c2-c1)*(5-t)*20;
    for(int i=0;i<8;i++)bi1[i]=bi2[i]=bj1[i]=bj2[i]=0;
    int a=0,b=0,c=0,d=0;double d1=0,d2=0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
            if(sz[i][j]==1)bi1[i]=bj1[j]=1,d1+=(i-3.5)*(i-3.5)+(j-3.5)*(j-3.5);
            else if(sz[i][j]==2)bi2[i]=bj2[j]=1,d2+=(i-3.5)*(i-3.5)+(j-3.5)*(j-3.5);
    }
    jg+=(d2/c2-d1/c1)*(5-t)*20;
    for(int i=0;i<8;i++)
        a+=bi1[i],b+=bj1[i],c+=bi2[i],d+=bj2[i];
    jg+=(double(a*b)/c1-double(c*d)/c2)*10;
    for(int i=0;i<8;i+=7)
        for(int j=0;j<8;j+=7)
            if(sz[i][j]==1)
            {
                for(int a=-1;a<=1;a++)
                    for(int b=-1;b<=1;b++)
                        if((a!=0||b!=0)&&inside(i+a,j+b)&&sz[i+a][j+b])jg-=(sz[i+a][j+b]==1?2:-2)*pts[i+a][j+b];
            }
            else if(sz[i][j]==2)
            {
                for(int a=-1;a<=1;a++)
                    for(int b=-1;b<=1;b++)
                        if((a!=0||b!=0)&&inside(i+a,j+b)&&sz[i+a][j+b])jg+=(sz[i+a][j+b]==2?2:-2)*pts[i+a][j+b];
            }
    int wd=t*30+10;st1=st2=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(sz[i][j]==1&&isstable(sz,i,j))jg+=wd;
            else if(sz[i][j]==2&&isstable(sz,i,j))jg-=wd;
    jg+=(st1-st2)*wd*2;
    int s1=0,s2=0;
    for(int i=0;i<8;i++)
    {
        int k=(i==0||i==7?3:1);
        if(!bi3[i])
        {
            int t1=0,t2=0;
            for(int j=0;j<8;j++)(sz[i][j]==1?t1:t2)+=1;
            s1+=2*k*t1*t1;s2+=2*k*t2*t2;
        }
        else
        {
            if(sz[i][0])
            {
                int s=0;
                while(s<8&&sz[i][s]==sz[i][0])s+=1;
                (sz[i][0]==1?s1:s2)+=k*s*s;
            }
            if(sz[i][7])
            {
                int s=0;
                while(s<8&&sz[i][7-s]==sz[i][7])s+=1;
                (sz[i][7]==1?s1:s2)+=k*s*s;
            }
        }
        if(!bj3[i])
        {
            int t1=0,t2=0;
            for(int j=0;j<8;j++)(sz[j][i]==1?t1:t2)+=1;
            s1+=2*k*t1*t1;s2+=2*k*t2*t2;
        }
        else
        {
            if(sz[0][i])
            {
                int s=0;
                while(s<8&&sz[s][i]==sz[0][i])s+=1;
                (sz[0][i]==1?s1:s2)+=k*s*s;
            }
            if(sz[7][i])
            {
                int s=0;
                while(s<8&&sz[7-s][i]==sz[7][i])s+=1;
                (sz[7][i]==1?s1:s2)+=k*s*s;
            }
        }
    }
    jg+=(s1-s2)*(t+1)/5;
    return jg;
}
int ai::min_max(int sz[8][8],int c,int l,int r,long long sd,int fr,int la_pts)
{
    if(clock()-st_tm>CLOCKS_PER_SEC*max_TM||sd>=max_sd)
    {
        int rt=(fr==2?calpts(sz,c,0):la_pts);
        return c==1?max(l,rt):min(r,rt);
    }
    LL h=Hash(sz)*2+(c-1);int u=mp[h],ps=0;
    if(u==0)
    {
        mp[h]=u=++N;
        for(int i=0;i<8;i++)e0[i]=0;
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(sz[i][j]==(c^3))e0[i]|=(1<<j);
        makee1();
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(sz[i][j]==0&&((e1[i]>>j)&1)&&check(sz,i,j,c))
                {
                    int la=tp;mark(sz,i,j,c,1);
                    int t=calpts(sz,c^3,0);
                    while(tp>la)
                    {
                        tp-=1;int x=(st[tp]>>3),y=(st[tp]&7);
                        sz[x][y]^=3;
                    }
                    if(c==1)t=-t;
                    sz[i][j]=0;sn[u][ps++]=make_pair(t,(i<<3)|j);
                }
        sort(sn[u],sn[u]+ps);
        sc[u]=ps;
    }
    else ps=sc[u];
    if(ps==0)
    {
        if(fr==2)return calpts(sz,c,true);
        int rt=min_max(sz,c^3,l,r,sd,2,0);
        if(c==1)l=max(l,rt);
        else r=min(r,rt);
        return c==1?l:r;
    }
    for(int s=0;s<ps;s++)
    {
        int t=sn[u][s].second,p=sn[u][s].first;
        if(c==1)p=-p;
        int x=(t>>3),y=(t&7),la=tp;
        mark(sz,x,y,c,1);
        int rt=min_max(sz,c^3,l,r,sd*ps,0,p);
        while(tp>la)
        {
            tp-=1;int i=(st[tp]>>3),j=(st[tp]&7);
            sz[i][j]^=3;
        }
        sz[x][y]=0;
        if(c==1)
        {
            if(rt>l)
            {
                l=rt;
                if(fr==1)cx=x,cy=y;
            }
        }
        else
        {
            if(rt<r)
            {
                r=rt;
                if(fr==1)cx=x,cy=y;
            }
        }
        if(l>=r)break;
    }
    return c==1?l:r;
}
void ai::min_max(int sz[8][8],int&x,int&y,int c)
{
    st_tm=clock();
    cx=cy=x=y=-1;
    max_sd=MAX_sd;
    while(max_sd<=1e17)
    {
        min_max(sz,c,-inf,inf,1,1,0);
        if(x==-1)x=cx,y=cy;
        if(clock()-st_tm>CLOCKS_PER_SEC*max_TM)break;
        x=cx;y=cy;max_sd+=MAX_sd;
    }
}
LL ai::Hash(int sz[8][8])
{
    LL rt = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            rt = rt * 3 + sz[i][j];
    return rt;
}
