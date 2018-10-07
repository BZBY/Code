#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll; 
#define fors(i,a,b) for(int  i=(a);i<=(b);++i)
const int SIZE=1<<20;
inline char getch(){
    static char buf[SIZE],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2) ? EOF : *p1++;
}
int read(){
    int s=0,f=1;
    char c=getch();
    while(c>'9'||c<'0'){if(c=='-') f=-1;c=getch();}
    while(c>='0'&&c<='9') {s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*=f;
}
const int MaxN = 100010, MaxM = 500010;

struct nodes
{
    int to,dis,next;
};
nodes edge[MaxM];
int head[MaxN], dis[MaxN], cnt;
bool vis[MaxN];
int n, m, s;
void add(int u,int v,int val){
    edge[++cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
    edge[cnt].dis=val;
}

struct node
{
    int dis,pos;
    bool operator <(const node &x) const{
        return x.dis < dis;
    }
};

priority_queue<node> q;
const int inf=2147483647;
void dijkstra(){
    dis[s]=0;
    q.push((node){0,s});
    while(!q.empty()){
        node u=q.top();
        q.pop();
        int x=u.pos;
        if(vis[x])
            continue;
        vis[x]=1;
        for(int i=head[x];i;i=edge[i].next){
            int v=edge[i].to;
            if(dis[v] > dis[x]+edge[i].dis){
                dis[v]=dis[x]+edge[i].dis;
                if(!vis[v])
                    q.push((node){dis[v],v});
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    n=read(),m=read(),s=read();
    fors(i,0,n) dis[i]=inf;
    int u,v,w;
    fors(i,1,m){
        u=read(),v=read(),w=read();
        add(u,v,w);
    }
    dijkstra();
    fors(i,1,n)
        printf("%d ",dis[i]);
    return 0;
}