#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long ll;
const int Size=1<<18;
inline char getch(){
    static char buf[Size],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,Size,stdin),p1==p2) ? EOF : *p1++;
}
int read(){
    int s=0,flag=1;
    char c=getch();
    while(c>'9' || c<'0'){if(c=='-') flag=-1; c=getch();}
    while(c<='9' && c>='0'){s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*flag;
}
const int maxn=2e6+7;
struct node
{
    int to,next;
}edge[maxn<<1];
int n,times,top,cnt,m,cur,head[maxn],low[maxn],dfn[maxn],sta[maxn],scc[maxn],in[maxn];

void add(int u,int v){
    edge[++cur].to=v,edge[cur].next=head[u],head[u]=cur;
}

void tarjan(int u){
    low[u]=dfn[u]=++times;
    sta[top++]=u,in[u]=1;
    for(int i=head[u];i;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(in[v])
                low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u]){
        int v;
        ++cnt;
        do{
            v=sta[--top],in[v]=0,scc[v]=cnt;
        }while(u!=v);
    }
}

int T_SAT(){
    fors(i,1,n<<1)
        if(!dfn[i])
            tarjan(i);
    fors(i,1,n)
        if(scc[i]==scc[i+n])
            return 0;
    return 1;
}

int main(int argc, char const *argv[])
{
    n=read(),m=read();
    fors(i,1,m){
        int a=read(),vala=read(),b=read(),valb=read();
        int tmp=vala^1,tmp2=valb^1;
        add(a+tmp*n,b+valb*n);
        add(b+tmp2*n,a+vala*n);
    }
    if(T_SAT()){
        printf("POSSIBLE\n");
        fors(i,1,n)
            printf("%d ",scc[i]>scc[i+n]);
    }
    else
        printf("IMPOSSIBLE\n");
    return 0;
}