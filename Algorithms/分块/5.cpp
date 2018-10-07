//给出一个长为n的数列，以及n个操作，操作涉及区间开方，区间求和。
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
const int maxn=50007;
int n,block,belong[maxn],tag[maxn],val[maxn],m,len,sum[maxn];

void slove_sqrt(int x){
	if(tag[x]) return ;
	tag[x]=1;
	sum[x]=0;
	len=x*block;
	fors(i,(x-1)*block+1,len){
		val[i]=sqrt(val[i]);
		sum[x]+=val[i];
		if(val[i]>1) tag[x]=0;
	}
}
void add(int x,int y){
	len=min(belong[x]*block,y);
	fors(i,x,len){
		sum[belong[x]]-=val[i];
		val[i]=sqrt(val[i]);
		sum[belong[x]]+=val[i];
	}
	if(belong[x]!=belong[y])
		fors(i,(belong[y]-1)*block+1,y){
			sum[belong[y]]-=val[i];
			val[i]=sqrt(val[i]);
			sum[belong[y]]+=val[i];
		}
	fors(i,belong[x]+1,belong[y]-1)
		slove_sqrt(i);
}

int query(int x,int y){
	len=min(belong[x]*block,y);
	int ans=0;
	fors(i,x,len)
		ans+=val[i];
	if(belong[x]!=belong[y])
		fors(i,(belong[y]-1)*block+1,y)
			ans+=val[i];
	fors(i,belong[x]+1,belong[y]-1)
		ans+=sum[i];
	return ans;
}

int main()
{
	n=read(),m=n;
	block=sqrt(n);
	fors(i,1,n)
		val[i]=read();
	fors(i,1,n){
		belong[i]=(i-1)/block+1;
		sum[belong[i]]+=val[i];
	}
	fors(i,1,n){
		int op=read(),x=read(),y=read(),k=read();
		if(op==0) {
			add(x,y);
		}
		else if(op==1) write(query(x,y)),putchar(10);
	}
	return 0;
}