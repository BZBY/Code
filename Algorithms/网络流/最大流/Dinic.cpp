#include <iostream>//84mx
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
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
    char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') {s=(s<<1)+(s<<3)+c-'0';c=getchar();}
    return s*=f;
}
int min(int a,int b){
    return a<b ? a:b;
}
struct node
{
    int to,cap,rev;
};
const int maxn=40007;
vector<node> G[maxn];

void add(int from,int to,int val){
    G[from].push_back((node){to,val,G[to].size()});
    G[to].push_back((node){from,0,G[from].size()-1});
}
int level[maxn],iter[maxn];


void bfs(int s){
    memset(level,-1,sizeof(level));
    queue<int>q;
    level[s]=0;
    q.push(s);
    int len;
    while(!q.empty()){
        int v=q.front();q.pop();
        len=G[v].size();
        for(int i=0;i<len;++i){
            node &e=G[v][i];
            if(level[e.to] < 0 && e.cap>0){
                q.push(e.to);
                level[e.to]=level[v]+1;
            }
        }
    }
}
int dfs(int v,int t,int f){
    if(v==t) return f;
    int len = G[v].size();
    for(int &i=iter[v];i<len;++i){
        node &e=G[v][i];
        if(e.cap>0 && level[e.to] > level[v]){
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}

const int inf=1<<29;
int MAX_flow(int s,int t){
    int ans=0;
    for(;;){
        bfs(s);
        if(level[t]<0) return ans;
        memset(iter,0,sizeof(iter));
        int f;
        while((f=dfs(s,t,inf))>0)
            ans+=f;
    }
}
int main(int argc, char const *argv[])
{
    int n=read(),m=read(),s=read(),t=read(),u,v,w;
    fors(i,1,m){
        u=read(),v=read(),w=read();
        add(u,v,w);
    }
    printf("%d\n",MAX_flow(s,t));
    return 0;
}

