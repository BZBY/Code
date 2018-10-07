#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long ll;
const int Size=1<<28;
inline char getch(){
    static char buf[Size],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,Size,stdin),p1==p2) ? EOF : *p1++;
}
#define int ll
int read(){
    int s=0,f=1;
    char c=getch();
    while(c>'9' || c<'0'){if(c=='-') f=-1;c=getch();}
    while(c<='9' && c>='0'){s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))

int l,r,n,ans,tmpr,tmpl;

signed main()
{
    int t=read();
    while(t--){
        l=read()-1,r=read();
        ans=0;

        if(r % 2 == 1)
            tmpr=(((r+1)/2)%9)*(r%9)%9;
        else 
            tmpr=((r/2)%9)*((r+1)%9)%9;
        
        if(l % 2 == 1){
            tmpl=(((l+1)/2)%9)*(l%9)%9;
        }
        else tmpl=((l/2)%9)*((l+1)%9)%9;
        ans=(tmpr-tmpl+9)%9;        cout<<tmpl<<" < "<<tmpr<<endl;;
        write(ans),putchar(10);
    }
    return 0;
}