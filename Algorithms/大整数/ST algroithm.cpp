#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
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
int maxs[100001][21];
inline int query(int l,int r){
    int k=log2(r-l+1);
    return max(maxs[l][k],maxs[r-(1<<k)+1][k]);
}
int main(int argc, char const *argv[])
{
    int n=read(),m=read();
    fors(i,1,n)
        maxs[i][0]=read();
    fors(j,1,21)
    for(int i=1;i+(1<<j)-1<=n;++i)
        maxs[i][j]=max(maxs[i][j-1],maxs[i+(1<<(j-1))][j-1]);
    fors(i,1,m){
        register int l=read(),r=read();
        write(query(l,r));
        puts("  ");
    }
    return 0;
}