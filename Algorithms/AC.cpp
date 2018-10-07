#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <ctime>
#include <vector>
#include <cstdlib>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long ll;
const int Size=1<<28;
inline char getch(){
    static char buf[Size],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,Size,stdin),p1==p2) ? EOF : *p1++;
}
int read(){
    int s=0,f=1;
    char c=getch();
    while(c>'9' || c<'0'){if(c=='-') f=-1;c=getch();}
    while(c<='9' && c>='0'){s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))
#define abs(x) (x<=0 ? -x : x)
const int maxn=1e5;
int n,m,x,y,w;
struct  node
{
    int to,val;
};
std::vector<node> v[maxn];
void add(int x,int y,int w){
    v[x].push_back((node){y,w});
}

int dis[maxn],vis[maxn],a[maxn];
void spfa(int k){
    memset(dis,127,sizeof dis);
    queue<int> q;
    vis[k]=1;
    dis[k]=0;
    q.push(k);
    int len;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        len=v[u].size()-1;
        fors(i,0,len){
            int vs=v[u][i].to;
            if(dis[u] + v[u][i].val < dis[vs]){
                dis[vs] = dis[u] + v[u][i].val;
                if(!vis[vs]){
                    vis[vs]=1;
                    q.push(vs);
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    n=read(),m=read();
    int S=n+1;
    fors(i,0,n) add(S,i,0);
    fors(i,1,m){
        x=read(),y=read(),w=read();
        add(y,x-1,-w);
    }
    fors(i,1,n)
        add(i-1,i,1),add(i,i-1,0);
    spfa(S);
    
    int mins=1<<25;
    fors(i,0,n){
        mins=min(mins,dis[i]);
    }
    write(dis[n]-mins),putchar(10);
    return 0;
}