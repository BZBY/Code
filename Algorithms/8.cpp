//给出一个长为n的数列，以及n个操作，操作涉及区间询问等于一个数c的元素，并将这个区间的所有元素改为c。
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define ll  long long
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
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
#define max(x,y) (x)>(y) ? (x) : (y)
#define min(x,y) (x)>(y) ? (y) : (x) 
const int maxn=1000007;
int n,block,belong[maxn],tag[maxn],val[maxn],m;
void reset(int x){
    if(tag[x]==-1) return ;
    int len=block*x;
    fors(i,(x-1)*block+1,len)
        val[i]=tag[x];
    tag[x]=-1;
}

int solve(int x,int y,int k){
    int len=min(belong[x]*block,y);
    int ans=0;
    reset(belong[x]);
    fors(i,x,len){
        (val[i]!=k) ? val[i]=k : ++ans;
    }
    if(belong[x]!=belong[y]){
        reset(belong[y]);
        fors(i,(belong[y]-1)*block+1,y)
            (val[i]!=k) ? val[i]=k : ++ans;
    }
    fors(i,belong[x]+1,belong[y]-1){
        if(tag[i]!=-1){
            (tag[i]!=k) ? tag[i]=k : ans+=block;
        }
        else {
            len=i*block;
            fors(j,(i-1)*block+1,len)
                (val[j]!=k) ? val[j]=k : ++ans;
            tag[i]=k;
        }
    }
    return ans;
}   
int main(int argc, char const *argv[])
{
    memset(tag,-1,sizeof tag);
    n=read();
    block=sqrt(n);
    fors(i,1,n)
        val[i]=read();
    fors(i,1,n)
        belong[i]=(i-1)/block+1;
    fors(i,1,n){
        int x=read(),y=read(),k=read();
        write(solve(x,y,k)),putchar(10);
    }
    return 0;
}