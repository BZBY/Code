#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
#define fors(i,s,a) for(int i=(s);i<=(a);++i)
#define ford(i,s,a) for(int i=(s);i>=(a);--i)
typedef long long ll;
const int maxn=4e5+7;
const ll mod=1e9+7;

int dis[maxn],n,m,head[maxn],vis[maxn],tot;
    
struct node
{
    int next,to,val;
}edge[maxn];

void add(int x,int y,int w){
    edge[++tot].to=y,edge[tot].next=head[x],head[x]=tot,edge[tot].val=w;
}

int prim(){
    int ans=0,tot=0,now=1;
    fill(dis+2,dis+maxn,1<<30);
    for(int i=head[1];i;i=edge[i].next){
        dis[edge[i].to]=min(edge[i].val,dis[edge[i].to]);
    }
    while(++tot < n){
        vis[now]=1;
        int mins=1<<30;
        fors(i,1,n)
            if(!vis[i] && mins > dis[i]){
                mins=dis[i];
                now=i;
            }
        ans+=mins;
        for(int i=head[now];i;i=edge[i].next){
            int v=edge[i].to;
            if(!vis[v] && dis[v] > edge[i].val)
                dis[v]=edge[i].val;
        }
    }
    return ans;
}
int main(int argc, char const *argv[])
{
    cin>>n>>m;
    fors(i,1,m){
        int x,y,z;
        cin>>x>>y>>z;
        add(x,y,z);
        add(y,x,z);
    }
    int ans=prim();
    if(!ans) cout<<"orz"<<endl;
    else cout<<ans<<endl;
    return 0;
}