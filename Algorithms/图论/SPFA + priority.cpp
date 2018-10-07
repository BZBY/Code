#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll; 
#define fors(i,a,b) for(int  i=(a);i<=(b);++i)
int read(){
    int s=0,f=1;
    register char c=getchar();
    while(c>'9'|| c<'0') { if(c=='-') f=-1;c=getchar();}
    while(c<='9' && c>='0') {s=(s<<3)+(s<<1)+c-'0';c=getchar();}
    return s*=f;
}
struct node
{
    int to,val;
};
int n,m,s,a,b,c;
vector<node> edge[100005];

ll dis[100005];
bool vis[100005];
struct nodes
{
    int x;
};
bool operator < ( const nodes &as,const nodes &sd){
    return dis[as.x]>dis[sd.x];
}
priority_queue<nodes> q;
int cnt;
bool vishud[100005];
inline void spfa(){
    memset(dis,127,sizeof dis);
    q.push((nodes){s});
    vis[s]=1;
    dis[s]=0;
    int u,v,w;
    while(!q.empty()){
        u=q.top().x;
        q.pop();
        if(!vishud[u]) ++cnt;//RP++
        if(cnt==n) return ;
        vishud[u]=1;
        vis[u]=0;
        for(int i=0;i<edge[u].size();++i){
            v=edge[u][i].to;
            w=edge[u][i].val;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!vis[v]){
                    vis[v]=1;
                    q.push((nodes){v});
                }
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    n=read(),m=read(),s=read();
    fors(i,1,m){
        a=read(),b=read(),c=read();
        edge[a].push_back((node){b,c});
    }
    spfa();
    fors(i,1,n){
        printf("%lld ",dis[i]);
    }
    return 0;
}