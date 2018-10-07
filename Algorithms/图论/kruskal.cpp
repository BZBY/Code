#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
#define ford(i,a,b) for(int i=(a);i>=(b);--i)
typedef long long ll;
const int maxn=5e5+7;
const int Size=1<<18;
inline char getch(){
    static char buf[Size],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,Size,stdin),p1==p2) ? EOF : *p1++;
}
int read(){
    int s=0,f=1;
    char c=getch();
    while(c>'9' || c<'0'){if(c=='-') f=-1;c=getch();}
    while(c<='9' && c>='0'){s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*f;
}
typedef pair<int,int> mp;
struct node{
    int next,to,val;
    bool operator < (const node & s)const{
        return val < s.val;
    }
};
vector<node> edge;

int f[maxn],n,m,ans,cnt;

int find(int x){
    return f[x]==x ? x : f[x]=find(f[x]);
}

void Kruskal(){
    sort(edge.begin(),edge.end());
    for(int i=0;i<m;++i){
        int a=find(edge[i].next),b=find(edge[i].to);
        if(a!=b){
            ans+=edge[i].val;
            f[b]=a;
            if(++cnt == n-1) break;
        }
    }
}


int main(int argc, char const *argv[])
{
    n=read(),m=read();
    fors(i,1,n) f[i]=i;
    for(int i=0;i<m;++i){
        int x=read(),y=read(),w=read();
        edge.push_back((node){x,y,w});
    }
    Kruskal();
    printf("%d\n",ans);
    return 0;
}