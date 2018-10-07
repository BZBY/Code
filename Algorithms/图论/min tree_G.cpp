#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
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
const int maxn=10007;
struct node
{
    int u,v,val;
}edge[maxn];
const int inf=1<<28;
int pre[maxn],vis[maxn],id[maxn],n,m,rt,in[maxn];

int G_A(){
    int cnt=0,ans=0,u,v,lazy;
    while(1){
        fors(i,1,n)
            in[i]=inf,id[i]=vis[i]=0;
        fors(i,1,m)
            if(edge[i].u ^ edge[i].v && edge[i].val < in[edge[i].v])
                pre[edge[i].v]=edge[i].u,in[edge[i].v]=edge[i].val;
        in[rt]=0;
        fors(i,1,n){
            if(in[i]==inf) return -1;
            ans+=in[i];
            for(u=i;u^rt && vis[u]^i && !id[u]; u=pre[u])
                vis[u]=i;
            if(u^rt && !id[u]){
                id[u]=++cnt;
                for(v=pre[u];v^u;v=pre[v])
                    id[v]=cnt;
            }
        }
        if(!cnt) return ans;
        fors(i,1,n)
            if(!id[i])
                id[i]=++cnt;
        fors(i,1,m){
            lazy=in[edge[i].v];
            if((edge[i].u=id[edge[i].u]) ^ (edge[i].v=id[edge[i].v]))
                edge[i].val-=lazy;
        }
        n=cnt,rt=id[rt],cnt=0;
    }
}
int main(int argc, char const *argv[])
{
    n=read(),m=read(),rt=read();
    fors(i,1,m)
        edge[i].u=read(),edge[i].v=read(),edge[i].val=read();
    printf("%d\n",G_A());
    return 0;
}