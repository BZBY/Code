#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <set>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long ll;
const int Size=1<<18;
inline char getch(){
    static char buf[Size],*a1=buf,*a2=buf;
    return a1==a2 && (a2=(a1=buf)+fread(buf,1,Size,stdin),a1==a2) ? EOF : *a1++;
}
int read(){
    int s=0,flag=1;
    char c=getch();
    while(c>'9' || c<'0'){if(c=='-') flag=-1; c=getch();}
    while(c<='9' && c>='0'){s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*flag;
}
const int maxn=1000007;
int n,l,r,k;
string str;
int main(int argc, char const *argv[])
{
    n=read();
    k=n/7;
    for(int i=k;i>=0;--i){
        if((n-i*7)%4==0){l=i;break;}
    }
    r=(n-l*7)/4;
    if((!l && n%4!=0) || (!r && !l)){
        puts("-1");
        return 0;
    }
    fors(i,1,r) str+="4"; 
    fors(i,1,l) str+="7";
    cout<<str;
    return 0;
}