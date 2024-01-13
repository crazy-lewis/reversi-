#ifndef AI_H
#define AI_H

#include <stdlib.h>
#include <algorithm>
#include <utility>
#include <time.h>
#include <set>
#include <map>
#include <math.h>
#pragma GCC optimize(3)
using namespace std;
#define inf 999999999
#define max_TM 0.98
#define MAX_sd 2500000
#define LL unsigned __int128

class ai
{
public:
    ai();

    long long max_sd;
    int pts[8][8]={
        {7000   ,-200   ,10 ,5  ,5  ,10 ,-200  ,7000},
        {-200   ,-2000   ,1  ,1  ,1  ,1  ,-2000  ,-200},
        {10     ,1      ,3  ,2  ,2  ,3  ,1     ,10},
        {5      ,1      ,2  ,1  ,1  ,2  ,1     ,5},
        {5      ,1      ,2  ,1  ,1  ,2  ,1     ,5},
        {10     ,1      ,3  ,2  ,2  ,3  ,1     ,10},
        {-200   ,-2000   ,1  ,1  ,1  ,1  ,-2000  ,-200},
        {7000   ,-200   ,10 ,5  ,5  ,10 ,-200  ,7000}};
    int st_tm;bool ED=0;
    bool inside(int x,int y);
    bool bj[8][8];
    int check_bj(int sz[8][8],int x,int y,int z);
    bool check(int sz[8][8],int x,int y,int z);
    int st[10000],tp;
    void mark(int sz[8][8],int x,int y,int z,bool tr);
    bool bi1[8],bi2[8],bj1[8],bj2[8],bi3[8],bj3[8];
    int e0[8],e1[8];
    void makee1();
    int ne[8][2]={-1,0,-1,-1,0,-1,1,-1,1,0,1,1,0,1,-1,1},st1,st2;
    bool isstable(int sz[8][8],int x,int y);
    int calpts(int sz[8][8],int cc,bool ed);
    LL Hash(int sz[8][8]);
    map<LL,int> mp;int cx,cy,N;
    pair<int,char> sn[1000000][40];int sc[1000000];
    int min_max(int sz[8][8],int c,int l,int r,long long sd,int fr,int la_pts);
    void min_max(int sz[8][8],int&x,int&y,int c);
};

#endif // AI_H
