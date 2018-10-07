#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <set>
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
#define foredge() for(int i=head[x];i;i=edge[i].next)
const int maxn=10007;
struct node
{
    int to,next,val;
}edge[maxn<<1];
const char U[2][8]={"NAY","AYE"};
int n,m,head[maxn],tot,sigma,maxson[maxn],size[maxn],dis[maxn],root,stk[maxn],top,K[maxn];
int vis[maxn],Ans[maxn];

set<int> f;
inline void add(int x,int y,int w){
    edge[++tot].to=y,edge[tot].next=head[x],head[x]=tot,edge[tot].val=w;
}
void get_root(int x,int fa){
    maxson[x]=0,size[x]=1;
    foredge()
        if((fa^edge[i].to) && !vis[edge[i].to]){
            get_root(edge[i].to,x),size[x]+=size[edge[i].to];
            if(size[edge[i].to] > maxson[x])
                maxson[x]=size[edge[i].to];
        }
    maxson[x]=max(maxson[x],sigma-size[x]);
    if(maxson[x] < maxson[root])
        root=x;
}

void dfs(int x,int fa){
    stk[++top]=dis[x];
    foredge()
        if((edge[i].to^fa) && !vis[edge[i].to])
            dis[edge[i].to]=dis[x]+edge[i].val,dfs(edge[i].to,x);
}

inline void query(int x){
    for(int i=m;i;--i)
        Ans[i]|=*f.lower_bound(K[i]-x)==K[i]-x;
}

void solve(int x){
    vis[x]=1,f.clear(),f.insert(0);
    foredge()
        if(!vis[edge[i].to]){
            top=0;
            dis[edge[i].to]=edge[i].val;
            dfs(edge[i].to,x);
            for(int i=top;i;--i)
                query(stk[i]);
            for(int i=top;i;--i)
                f.insert(stk[i]);
        }
    foredge()
        if(!vis[edge[i].to]){
            root=0,sigma=size[edge[i].to];
            get_root(edge[i].to,0),solve(root);
        }
}

int main(int argc, char const *argv[])
{
    n=read(),m=read();
    fors(i,2,n){
        int x=read(),y=read(),w=read();
        add(x,y,w);
        add(y,x,w);
    }
    for(int i=m;i;--i)
        K[i]=read();
    maxson[root=0]=sigma=n;
    get_root(1,0);
    solve(root);
    for(int i=m;i;--i)
        puts(U[Ans[i]]);
    return 0;
}