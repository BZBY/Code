// luogu-judger-enable-o2
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define int long long
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
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
inline void write(int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int maxn=1000007;
int n,m,tree[maxn<<1],cnt[maxn<<1];
inline void add(int p,int x,int y)
{
    for(;p<=n;p+=p&(-p))
        tree[p]+=x,cnt[p]+=y;
}
inline int sum(int t)
{
    int x=0,y=0;
    for (int p=t;p;p-=p&(-p))
        x+=tree[p],y+=cnt[p];
    return x*t+y;
}
signed main()
{
    n=read(),m=read();
    fors(i,1,n){
        int a=read();
        add(i,0,a);
    }
    fors(i,1,m){
        int a=read(),as=read(),bs=read(),cs;
        if(a==1) {
            cs=read();
            add(as,cs,cs*(1-as));
            add(bs+1,-cs,cs*bs);
        }
        else
            if(a==2){
                write(sum(bs)-sum(as-1));
                puts("  ");
            }
    }
    return 0;
}