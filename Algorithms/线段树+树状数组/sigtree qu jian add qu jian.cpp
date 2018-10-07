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
#define int ll
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
    n=read(),m=read();
    for(;N<=n+1;N<<=1);
    fors(i,N+1,N+n) 
        tree[i]=read();
    ford(i,N-1,1)
        tree[i]=tree[i<<1]+tree[i<<1|1];
}

void update(int s,int t,int k){
    int lnum=0,rnum=0,nnum=1;
    for(s=N+s-1,t=N+t+1; s^t^1; s>>=1,t>>=1,nnum<<=1){
        tree[s] += k*lnum , tree[t] += k*rnum;
        if(~s&1) {add[s^1] += k , tree[s^1] += k*nnum , lnum+=nnum;}
        if(t&1) {add[t^1] += k , tree[t^1] += k*nnum , rnum+=nnum;}
    }
    for(;s;s>>=1,t>>=1){
        tree[s]+=k*lnum;
        tree[t]+=k*rnum;
    }
}

int query(int s,int t){
    int lnum=0,rnum=0,nnum=1,ans=0;
    for(s=N+s-1,t=N+t+1;s^t^1;s>>=1,t>>=1,nnum<<=1){
        if(add[s]) ans+=add[s]*lnum;
        if(add[t]) ans+=add[t]*rnum;
        if(~s&1) {ans+=tree[s^1];lnum+=nnum;}
        if(t&1) {ans+=tree[t^1];rnum+=nnum;}
    }
    for(;s;s>>=1,t>>=1){
        ans+=add[s]*lnum;
        ans+=add[t]*rnum;
    }
    return ans;
}
signed main()
{
    build();
    int x,l,r,k;
    while(m--){
        x=read();
        if(x==1){
            l=read(),r=read(),k=read();
            update(l,r,k);
            l=n;
            fors(;l;l>>=1) cout<<tree[l]<<" ";
            cout<<endl;
        }
        else {
            l=read(),r=read();
            fors(i,1,n)
            printf("%lld ",query(i,i));
            puts(" ");
        }
    }
    return 0;
}