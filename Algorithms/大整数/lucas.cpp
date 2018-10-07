#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define ll long long
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
int n,m,tree[500005];
inline void add(int x,int k){
    while(x<=n)
        tree[x]+=k,x+=x & -x;
}
inline int search(int x){
    int a=0;
    while(x!=0){
        a+=tree[x];
        x-=x & -x;
    }
    return a;
}
int main(int argc, char const *argv[])
{
    n=read(),m=read();
    int last=0,a,as,bs,cs;
    fors(i,1,n){
        int a=read();
        add(i,a-last);
        last=a;
    }
    while(m--){
        a=read();
        if(a&1) {
            as=read(),bs=read(),cs=read();
            add(as,cs);
            add(bs+1,-cs);
        }
        else
            if(a&0){
                as=read(),bs=read();
                fors(i,as,bs)
                write(search(as)),putchar(' ');
                puts("  ");
            }
    }
    return 0;
}