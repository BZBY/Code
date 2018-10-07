//给出一个长为n的数列，以及n个操作，操作涉及区间加法，询问区间内小于某个值x的前驱（比其小的最大元素）。
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
const int Size=1<<25;
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
const int maxn=100007;
int n,block,belong[maxn],tag[maxn],val[maxn],m;
set<int> sets[100005];

void add(int x,int y,int k){
	int len=min(belong[x]*block,y);
	fors(i,x,len){
		sets[belong[x]].erase(val[i]);
		val[i]+=k;
		sets[belong[x]].insert(val[i]);
	}
	if(belong[x]!=belong[y])
		fors(i,(belong[y]-1)*block+1,y){
			sets[belong[y]].erase(val[i]);
			val[i]+=k;
			sets[belong[y]].insert(val[i]);
		}
	fors(i,belong[x]+1,belong[y]-1)
		tag[i]+=k;
}

int query(int x,int y,int k){
	int len=min(belong[x]*block,y);
	int ans=-1;
	fors(i,x,len){
		int vals=val[i]+tag[belong[x]];
		if(vals < k) ans=max(vals,ans);
	}
	if(belong[x]!=belong[y])
		fors(i,(belong[y]-1)*block+1,y){
			int vals=val[i]+tag[belong[y]];
			if(vals < k) ans=max(ans,vals);
		}
	fors(i,belong[x]+1,belong[y]-1){
		int x=k-tag[i];
		set<int> :: iterator it=sets[i].lower_bound(x);
		if(it==sets[i].begin()) continue;
		--it;
		ans=max(ans,*it+tag[i]);
	}
	return ans;
}
int main(int argc, char const *argv[])
{
	n=read(),m=n;
	block=sqrt(n);
	fors(i,1,n)
		val[i]=read();
	fors(i,1,n){
		belong[i]=(i-1)/block+1;
		sets[belong[i]].insert(val[i]);
	}
	fors(i,1,m){
		int op=read(),x=read(),y=read(),k=read();
		if(op==0) add(x,y,k);
		else if(op==1) write(query(x,y,k)),putchar(10);
	}
	return 0;
}