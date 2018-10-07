#include <iostream>//48ms
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll; 
#define fors(i,a,b) for(int  i=(a);i<=(b);++i)
const int SIZE=1<<15;
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
const int maxne=20007;
const int maxnv=400007;
int n,m,s,t,cnt,maxflow;
int head[maxne],cur[maxne];
int depth[maxne],pre[maxne],num[maxne];
struct node
{
    int next,to,w;
}edge[maxnv];

void add(int x,int y,int z){
    edge[cnt].to=y;
    edge[cnt].next=head[x];
    edge[cnt].w=z;
    head[x]=cnt++;
}
void bfs(int t){
    queue<int> q;
    fors(i,1,n) cur[i]=head[i],depth[i]=n;
    depth[t]=0;
    q.push(t);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i!=-1;i=edge[i].next)
            if(depth[edge[i].to]==n && edge[i^1].w){
                depth[edge[i].to]=depth[u]+1;
                q.push(edge[i].to);
            }
    }
}

int add_flow(int s,int t){
    int ans=1<<28,u=t;
    while(u!=s){
        ans=min(ans,edge[pre[u]].w);
        u=edge[pre[u]^1].to;
    }
    u=t;
    while(u!=s){
        edge[pre[u]].w-=ans;
        edge[pre[u]^1].w+=ans;
        u=edge[pre[u]^1].to;
    }
    return ans;
}


void ISAP(int s,int t){
    int u=s;
    bfs(t);
    fors(i,1,n) ++num[depth[i]];
    while(depth[s] < n){
        if(u==t)
            maxflow+=add_flow(s,t),u=s;
        bool flag=0;
        for(int i=cur[u];i!=-1;i=edge[i].next)
            if(depth[u]==depth[edge[i].to]+1 && edge[i].w){
                flag=1,u=edge[i].to,pre[edge[i].to]=i;
                break;
            }
        if(!flag){
            int mins=n-1;
            for(int i=head[u];i!=-1;i=edge[i].next)
                if(edge[i].w)
                    mins=min(mins,depth[edge[i].to]);
            if((--num[depth[u]])==0) break;
            num[depth[u]=mins+1]++;
            cur[u]=head[u];
            if(u!=s)
                u=edge[pre[u]^1].to;
        }
    }
}

int main(int argc, char const *argv[])
{
    memset(head,-1,sizeof head);
    n=read(),m=read(),s=read(),t=read();
    fors(i,1,m){
        int u=read(),v=read(),w=read();
        add(u,v,w);
        add(v,u,0);
    }
    ISAP(s,t);
    printf("%d\n",maxflow);
    return 0;
}