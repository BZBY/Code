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
const int maxn=1e4+7;
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

int vis[maxn];
int n,cnt,m;
void dfsin(int u){
    vis[u]=1;
    int len=edge[u].size()-1;
    fors(i,0,len){
        if(!vis[edge[u][i]])
            dfsin(edge[u][i]);
    }
    s.push(u);
}

void dfsans(int u){
    vis[u]=1;
    int len=edgeb[u].size()-1;
    fors(i,0,len){
        if(!vis[edgeb[u][i]])
            dfsans(edgeb[u][i]);
    }
}


int main(int argc, char const *argv[])
{
    int n=read(),m=read();
    fors(i,1,n)
        edge[i].clear(),edgeb[i].clear();
    fors(i,1,m){
        int u=read(),v=read();
        edge[u].push_back(v);
        edgeb[v].push_back(u);
    }

    fors(i,1,n){
        if(!vis[i])
            dfsin(i);
    }

    memset(vis,0,sizeof(vis));

    cnt=0;

    while(!s.empty()){
        int t=s.top();
        s.pop();
        if(!vis[t])
            ++cnt,dfsans(t);
    }
    if(cnt > 1)
        puts("No");
    else puts("Yes");
    return 0;
}
