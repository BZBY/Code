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
inline int gcd(int x, int y) {
    return y ? gcd(y, x%y) : x;
}

int n;
//斐属定理
int main() {
    n=read();
    int ans = 0, tmp;
    fors(i,1,n) {
        tmp=read();
        if(tmp < 0) tmp = -tmp;
        ans = gcd(ans, tmp);
    }
    printf("%d", ans);
    return 0;
}