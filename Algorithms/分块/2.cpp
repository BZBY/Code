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
const int maxn=1000007;
int n,block,belong[maxn],tag[maxn],val[maxn],m;
std::vector<int> v[10000];

void reset(int x){
	int len=min(x*block,n);
	v[x].clear();
	fors(i,(x-1)*block+1,len)
		v[x].push_back(val[i]);
	sort(v[x].begin(),v[x].end());
}

void add(int x,int y,int k){
	int len=min(belong[x]*block,y);
	fors(i,x,len)
		val[i]+=k;
	reset(belong[x]);
	if(belong[x]!=belong[y]){
		fors(i,(belong[y]-1)*block+1,y)
			val[i]+=k;
		reset(belong[y]);
	}	
	fors(i,belong[x]+1,belong[y]-1)
		tag[i]+=k;
}

int query(int x,int y,int k){
	int len=min(belong[x]*block,y);
	int ans=0;
	fors(i,x,len)
		if(val[i]+tag[belong[x]]>=k) ++ans;
	if(belong[x]!=belong[y])
		fors(i,(belong[y]-1)*block+1,y)
			if(val[i]+tag[belong[y]]>=k) ++ans;
	fors(i,belong[x]+1,belong[y]-1){
		int tmp=k-tag[i];
		ans+=v[i].end()-lower_bound(v[i].begin(),v[i].end(),tmp);
		//最小则v[i].end()-lower_bound(v[i].begin(),v[i].end(),tmp)-v[i].begin(); <k
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
		v[belong[i]].push_back(val[i]);
	}
	fors(i,1,belong[n])
		sort(v[i].begin(),v[i].end());
	fors(i,1,m){
	    char c=getcha();
		int x=read(),y=read(),k=read();
		if(c=='M') add(x,y,k);
		else if(c=='A') write(query(x,y,k)),putchar(10);
	}
	return 0;
}