#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>
#include <deque>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
#define ford(i,a,b) for(int i=(a);i>=(b);--i)
#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) < (y) ? (y) : (x))
#define swap(x,y) ((x)^=(y),(y)^=(x),(x)^=(y))
const int maxn=1e6+7;
typedef long long ll;
const int inf=1<<25;

inline char getch(){
    static char buf[inf],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,inf,stdin),p1==p2) ? EOF : *p1++;
}
int read(){
    int s=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0' && c<='9') {s=s*10+c-48;c=getchar();}
    return s*f;
}
void write(int x){
    if(x<0) {putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+48);
}
struct node
{
    ll to,val;
};
std::vector<node> edge[maxn];
ll n,m,p,s,a[maxn],dis[maxn],vis[maxn],ans=1<<30,cnt,cur[maxn];

void spfa(){
    fill(dis,dis+maxn,ans);
    deque<int> q;
    dis[s]=0;
    vis[s]=1;
    q.push_back(s);
    while(!q.empty()){
        int u=q.front();
        q.pop_front();
        vis[u]=0;
        for(int i=0;i<edge[u].size();++i){
            int v=edge[u][i].to,w=edge[u][i].val;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!vis[v]){
                    vis[v]=1;
                    (q.empty() || dis[q.front()] < dis[v]) ? q.push_back(v) : q.push_front(v);
                }
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    n=read(),m=read(),p=read(),s=read();
    int x,y,z;
    fors(i,1,m){
        x=read(),y=read(),z=read();
        edge[x].push_back((node){y,z});
        edge[y].push_back((node){x,z});
    }
    fors(i,1,p){
        x=read(),y=read(),z=read();
        edge[x].push_back((node){y,z});
    }
    spfa();

    fors(i,1,n){
        if(dis[i] == ans ) puts("NO PATH");
        else cout<<dis[i]<<endl;        
    }
    return 0;
}