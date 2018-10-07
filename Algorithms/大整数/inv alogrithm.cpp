#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll; 
#define fors(i,a,b) for(int  i=(a);i<=(b);++i)
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
int l,m,n,s,p;
void exgcd(int a,int b,int &x,int &y){
    if(!b){
        x=1,y=0;
        return ;
    }
    exgcd(b,a%b,x,y);
    int tmp=x;
    x=y;
    y=tmp-a/b*y;
}
int main(int argc, char const *argv[])
{
    int x,b,y;
    n=read(),p=read();
    fors(i,1,n){
        exgcd(i,p,x,y);
        printf("%d\n",(x%p+p)%p);
    }   
    return 0;
}