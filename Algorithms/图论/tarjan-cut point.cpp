#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>
#include <deque>
#include <stack>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
#define ford(i,a,b) for(int i=(a);i>=(b);--i)
#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) < (y) ? (y) : (x))
#define swap(x,y) ((x)^=(y),(y)^=(x),(x)^=(y))
#define abs(x) ((x) < 0 ? -(x) : (x)) 
#define forvit(i) for(vector<int> :: iterator it=(i).begin();it!=(i).end();++it) 
#define v *it
const int maxn=2e5+7;
typedef long long ll;
const int inf=1<<25;
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
vector<int> edge[maxn],edgeb[maxn];
stack<int> s;

int n,cnt,m,tot,ans1,ans2,scc[maxn],in[maxn],out[maxn],vis[maxn];
int dfn[maxn],low[maxn];
void tarjan(int u,int fa){
    low[u]=dfn[u]=++cnt;
    int child=0;
    forvit(edge[u]){
        if(!dfn[v]){
            tarjan(v,fa);
            low[u]=min(low[u],low[v]);
            if(low[v] >= dfn[u] && u!=fa && !out[u]){
                out[u]=1;
                ++ans1;
            }
            if(u == fa) ++child;
        }
        low[u]=min(dfn[v],low[u]);
    }
    if(fa==u && child >= 2  && !out[u]){
        out[u]=1;
        ++ans1;
    }
}
int main(int argc, char const *argv[])
{
    n=read(),m=read();
    fors(i,1,m){
        int a=read(),b=read();
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    fors(i,1,n)
        if(!dfn[i])
            cnt=0,tarjan(i,i);

    write(ans1),putchar(10);
    fors(i,1,n)
        if(out[i])
            write(i),putchar(' ');
    return 0;
}