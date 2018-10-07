//给出一个长为n的数列，以及n个操作，操作涉及单点插入，单点询问，数据随机生成。如果一个块插入的过多，重新分块
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
int top,st[maxn];
std::vector<int> v[1005];
pair<int,int> query(int k){
	int x=1;
	while(k > v[x].size())
		k-=v[x].size(),++x;
	return make_pair(x,k-1);
}

void rebuild(){
	top=0;
	fors(i,1,m){
		for(std::vector<int>::iterator j=v[i].begin();j!=v[i].end();++j)
			st[++top]=*j;
		v[i].clear();
	}
	int tmpblock=sqrt(top);
	fors(i,1,top)
		v[(i-1)/tmpblock+1].push_back(st[i]);
	m=(top-1)/tmpblock+1;
}

void insert(int x,int y){
	pair<int,int> t=query(x);
	v[t.first].insert(v[t.first].begin()+t.second,y);
	if(v[t.first].size() > block*20)
		rebuild();
}
int main(int argc, char const *argv[])
{
	n=read();
	block=sqrt(n);
	m=(n-1)/block+1;
	fors(i,1,n)
		val[i]=read();
	fors(i,1,n){
		v[(i-1)/block+1].push_back(val[i]);
	}
	fors(i,1,n){
		int op=read(),x=read(),y=read(),k=read();
		if(op==0) insert(x,y);
		else if(op==1){
			pair<int,int> t=query(y);
			write(v[t.first][t.second]),putchar(10);
		}
	}
	return 0;
}