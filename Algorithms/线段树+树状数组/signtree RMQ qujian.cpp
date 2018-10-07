#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll long long
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
#define ford(i,a,b) for(int i=(a);i>=(b);--i)
const int SIZE=1<<20;
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

const int maxn=100007;
int tree[maxn<<1],n,m,N=1,add[maxn<<1];
void build(){
    for(N=1;N<=n+1;N<<=1);
    fors(i,N+1,n+N)
        tree[i]=read();
    ford(i,N-1,1){
        tree[i]=max(tree[i<<1],tree[i<<1|1]);
        tree[i<<1]-=tree[i],tree[i<<1|1]-=tree[i];
    }
}

void update(int s,int t,int k){
    int tmp;
    for(s+= N-1 ,t+=N+1;s^t^1;s>>=1,t>>=1){
        if(~s&1) tree[s^1]+=k;
        if(t&1) tree[t^1]+=k;
        tmp=max(tree[s],tree[s^1]);
        tree[s] -= tmp , tree[s^1] -= tmp , tree[s>>1] +=tmp;
        tmp =max(tree[t] , tree[t^1]);
        tree[t] -= tmp , tree[t^1]-=tmp , tree[t>>1] +=tmp;
    }
    for(;s!=1;s>>=1){
        tmp=max(tree[s],tree[s^1]);
        tree[s] -= tmp,tree[s^1] -= tmp,tree[s>>1] += tmp;
    }
}

int query(int s,int t){
    int sAns=0,tAns=0;
    s+=N,t+=N;
    if(s!=t){
        for(;s^t^1;s>>=1,t>>=1){
            sAns+=tree[s],tAns+=tree[t];
            if(~s&1) sAns=max(sAns,tree[s^1]);
            if(t&1) tAns=max(tAns,tree[t^1]);
        }
    }
    int ans=max(sAns+tree[s],tAns+tree[t]);
    while(s > 1)
        ans+=tree[s>>=1];
    return ans;
}
int main()
{
    n=read(),m=read();
    build();
    int x,l,r,k;
    while(m--){
        l=read(),r=read();
        printf("%d\n",query(l,r));
    }
    return 0;
}