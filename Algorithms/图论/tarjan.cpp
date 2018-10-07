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
const int maxn=100007;
struct node
{
    int next,to;
}edge[maxn<<1];
int n,m,idx,cnt,tot,head[maxn],dfn[maxn],low[maxn],cut[maxn];
void add(int x,int y){
    edge[++cnt].to=y;
    edge[cnt].next=head[x];
    head[x]=cnt;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++idx;
    int sons=0;
    for(int i=head[u];i;i=edge[i].next){
        int v=edge[i].to;
        if(!dfn[v]){
            tarjan(v,fa);
            low[u]=min(low[u],low[v]);
            if(low[v] >= dfn[u] && u!=fa)
                cut[u]=1;
            if(u==fa) 
                ++sons;
        }
        low[u]=min(low[u],dfn[v]);
    }
    if(u==fa && sons>=2)
        cut[fa]=1;
}

int main(int argc, char const *argv[])
{
    n=read(),m=read();
    fors(i,1,m){
        int a=read(),b=read();
        add(a,b);
        add(b,a);
    }
    fors(i,1,n){
        if(!dfn[i])
            tarjan(i,i);
    }
    fors(i,1,n)
        if(cut[i])
            ++tot;
    printf("%d\n",tot);
    fors(i,1,n)
        if(cut[i])
            printf("%d ",i);
    return 0;
}