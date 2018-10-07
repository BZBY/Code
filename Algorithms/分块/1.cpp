//给出一个长为n的数列，以及n个操作，操作涉及区间加法，单点查值。
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define ll long long
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
const int Size=1<<20;
inline char getch(){
    static char buf[Size],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,Size,stdin),p1==p2) ? EOF : *p1++;
}
int read(){
    int s=0,flag=1;
    char c=getch();
    while(c>'9' || c<'0'){if(c=='-') flag=-1; c=getch();}
    while(c<='9' && c>='0'){s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*flag;
}
void write(int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int maxn=500007;
int n,block,belong[maxn],val[maxn],tag[maxn];
void add(int x,int y,int k){
	int len=min(belong[x]*block,y);
	fors(i,x,len)
		val[i]+=k;
	
	if(belong[x]!=belong[y])
		for(int i=(belong[y]-1)*block+1;i<=y;++i)
			val[i]+=k;
	
	fors(i,belong[x]+1,belong[y]-1)
		tag[i]+=k;
}

int main(int argc, char const *argv[])
{
	n=read();
	block=sqrt(n);
	fors(i,1,n)
		val[i]=read();
	fors(i,1,n)
		belong[i]=(i-1)/block+1;
	fors(i,1,n){
		int op=read(),x=read(),y=read(),k=read();
		if(op==0){
			add(x,y,k);
		}
		if(op==1){
			write(val[y]+tag[belong[y]]),putchar(10);
		}
	}
	return 0;
}