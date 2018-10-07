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

const int maxn=200007;
int tree[maxn<<1],n,m,N=1;
void build(){
    n=read(),m=read();
    for(;N<=n+1;N<<=1);
    fors(i,N+1,N+n) 
        tree[i]=read();
    ford(i,N-1,1)
        tree[i]=tree[i<<1]+tree[i<<1|1];
}

void modify(int x,int k){
    for(x+=N ; x ; x>>=1) tree[x]+=k;
}

int query(int s,int r){
    int ans=0;
    for(s= N+s-1 , r= n+r+1; s^r^1 ;s>>=1,r>>=1){
        if(~s&1) ans+=tree[s^1];
        if(r&1) ans+=tree[r^1];
    }
    return ans;
}

int main(int argc, char const *argv[])
{
    build();
    int x,l,r;
    while(m--){
        x=read(),l=read(),r=read();
        if(x==1){modify(l,r);}
        else {printf("%d\n",query(l,r));}
    }
    return 0;
}