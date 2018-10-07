//给出一个长为n的数列，以及n个操作，操作涉及区间加法，区间求和。
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
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
#define max(x,y) (x)>(y) ? (x) : (y)
#define min(x,y) (x)>(y) ? (y) : (x) 
const int maxn=1000007;
int n,block,belong[maxn],tag[maxn],val[maxn],m,len,sum[maxn];

void add(int x,int y,int k){
	len=min(belong[x]*block,y);
	fors(i,x,len){
		val[i]+=k;
		sum[belong[x]]+=k;
	}
	if(belong[x]!=belong[y])
		fors(i,(belong[y]-1)*block+1,y){
			val[i]+=k;
			sum[belong[y]]+=k;
		}
	fors(i,belong[x]+1,belong[y]-1)
		tag[i]+=k;
}

int query(int x,int y){
	len=min(belong[x]*block,y);
	int ans=0;
	fors(i,x,len){
		ans+=val[i]+tag[belong[x]];
	}
	if(belong[x]!=belong[y])
		fors(i,(belong[y]-1)*block+1,y)
			ans+=val[i]+tag[belong[y]];
	fors(i,belong[x]+1,belong[y]-1)
		ans+=sum[i]+block*tag[i];
	return ans;
}
int main(int argc, char const *argv[])
{
	n=read(),m=read();
	block=sqrt(n);
	fors(i,1,n) val[i]=read();
	fors(i,1,n){
		belong[i]=(i-1)/block+1;
		sum[belong[i]]+=val[i];
	}
	fors(i,1,m){
		int op=read(),x=read(),y=read();
		if(op==1){
			int k=read();
			add(x,y,k);
		}
		else if(op==2){
			write(query(x,y)),putchar(10);
		}
	}
	return 0;
}