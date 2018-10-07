#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>
using namespace std;
#define ll long long
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
const int Size=1<<20;
inline char getch(){
    static char buf[Size],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,Size,stdin),p1==p2) ? EOF : *p1++;
}
ll read(){
    ll s=0,flag=1;
    char c=getch();
    while(c>'9' || c<'0'){if(c=='-') flag=-1; c=getch();}
    while(c<='9' && c>='0'){s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*flag;
}
const int maxn=200007;
void write(ll x){
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
#define size(x) (r[x]-l[x]+1)
ll a[maxn],n,m,belong[maxn],sum[maxn],l[maxn],r[maxn],block,op,x,y,k,mark[maxn];
int main(int argc, char const *argv[])
{
	n=read(),m=read();
	block=sqrt(n);
	fors(i,1,n){
		a[i]=read();
		belong[i]=i/block,sum[belong[i]]+=a[i];
	}
	fors(i,1,n)
		if(!l[belong[i]])
			l[belong[i]]=i;
	for(int i=n;i>=0;--i)
		if(!r[belong[i]])
			r[belong[i]]=i;
	while(m--){
		op=read();
		if(op==1){
			x=read(),y=read(),k=read();
			int j=x;
			for(;j<=y;++j){
				if(l[belong[j]] == j) break;
				a[j]+=k,sum[belong[j]]+=k;
			}
			for(;j<=y;j+=size(belong[j])){
				if(r[belong[j]] > y) break;
				sum[belong[j]]+=k*size(belong[j]),mark[belong[j]]+=k;
			}
			for(;j<=y;++j)
				a[j]+=k,sum[belong[j]]+=k;
		}
		else {
			x=read(),y=read();
			int ans=0,j=x;
			for(;j<=y;++j){
				if(l[belong[j]] == j) break;
				ans+=a[j]+mark[belong[j]];
			}
			for(;j<=y;j+=size(belong[j])){
				if(r[belong[j]] > y) break;
				ans+=sum[belong[j]];
			}
			for(;j<=y;++j)
				ans+=a[j]+mark[belong[j]];
			write(ans),puts(" ");
		}
	}
	return 0;
}
