//给出一个长为n的数列，以及n个操作，操作涉及询问区间的最小众数。
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define ll  long long
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
const int Size=1<<20;
inline char getch(){
    static char buf[Size],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,Size,stdin),p1==p2) ? EOF : *p1++;
}
#define int ll
int read(){
    int s=0,flag=1;
    char c=getch();
    while(c>'9' || c<'0'){if(c=='-') flag=-1; c=getch();}
    while(c<='9' && c>='0'){s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*flag;
}
void write(int x){
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
#define max(x,y) (x)>(y) ? (x) : (y)
#define min(x,y) (x)>(y) ? (y) : (x) 
const int maxn=50007;
int n,block,belong[maxn],id,cnt[maxn],val[maxn],vcnt[maxn],f[1005][1005];
std::vector<int> vs[maxn];
std::map<int,int> maps;

void pre(int x){
    memset(cnt,0,sizeof(cnt));
    int maxs=0,ans=0;
    fors(i,(x-1)*block+1,n){
        ++cnt[val[i]];
        int tmp=belong[i];
        if(cnt[val[i]] > maxs || (cnt[val[i]]==maxs && vcnt[val[i]] < vcnt[ans]))
            ans=val[i],maxs=cnt[val[i]];
        f[x][tmp]=ans;
    }
}

int queryit(int l,int r,int x){
    int t=upper_bound(vs[x].begin(), vs[x].end(),r)-lower_bound(vs[x].begin(), vs[x].end(),l);
    return t;
}

int query(int x,int y){
    int ans=f[belong[x]+1][belong[y]-1],maxs,len=min(y,block*belong[x]);
    maxs=queryit(x,y,ans);
    fors(i,x,len){
        int tmp=queryit(x,y,val[i]);
        if(tmp>maxs || (tmp==maxs && vcnt[val[i]] < vcnt[ans]))
            ans=val[i],maxs=tmp;
    }
    if(belong[x]!=belong[y]){
        fors(i,(belong[y]-1)*block+1,y){
            int tmp=queryit(x,y,val[i]);
            if(tmp>maxs || (tmp==maxs && vcnt[val[i]] < vcnt[ans]))
                ans=val[i],maxs=tmp;
        }
    }
    return ans;
}

signed main()
{
    n=read();
    block=sqrt(n);
    fors(i,1,n){
        val[i]=read();
        if(!maps[val[i]]){
            maps[val[i]]=++id;
            vcnt[id]=val[i];
        }
        val[i]=maps[val[i]];
        vs[val[i]].push_back(i);
        belong[i]=(i-1)/block+1;
    }
    fors(i,1,belong[n]) pre(i);
    fors(i,1,n){
        int x=read(),y=read();
        if(x>y) swap(x,y);
        write(vcnt[query(x,y)]),putchar(10);
    }

    return 0;
}

