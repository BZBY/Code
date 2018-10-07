#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define ll unsigned long long
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
const int Size=1<<20;
#define int ll
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
int n,block,belong[maxn],tag[maxn],val[maxn],m,len,sum[maxn],mtag[maxn],p,tot[maxn];
void reset(int x){
    len=min(x*block,n);
    fors(i,(x-1)*block+1,len)
        val[i]=(val[i]*mtag[x]+tag[x])%p;
    tag[x]=0;
    mtag[x]=1;
}

void add(int x,int y,int k){
    reset(belong[x]);
    len=min(belong[x]*block,y);
    sum[belong[x]]+=(len-x+1)*k;
    sum[belong[x]]%=p;
    fors(i,x,len){
        val[i]+=k;
    }

    if(belong[x]!=belong[y]){
        reset(belong[y]);
        sum[belong[y]]+=(y-(belong[y]-1)*block)*k;
        sum[belong[y]]%=p;
        fors(i,(belong[y]-1)*block+1,y){
            val[i]+=k;
        }
    }
    fors(i,belong[x]+1,belong[y]-1){
        tag[i]+=k;
        (sum[i]+=tot[i]*k)%=p;
    }
}
void mul(int x,int y,int k){
    reset(belong[x]);
    len=min(belong[x]*block,y);
    fors(i,x,len){
        sum[belong[x]]+=val[i]*(k-1);
        val[i]*=k;
        val[i]%=p; 
    }
    sum[belong[x]]%=p;
    if(belong[x]!=belong[y]){
        reset(belong[y]);
        fors(i,(belong[y]-1)*block+1,y){
            sum[belong[y]]+=val[i]*(k-1);
            val[i]*=k;
            val[i]%=p; 
        }
    }
    sum[belong[y]]%=p;
    fors(i,belong[x]+1,belong[y]-1){
        (tag[i]*=k)%=p;
        (mtag[i]*=k)%=p;
        (sum[i]*=k)%=p;
    }
}
int query(int x,int y){
    len=min(belong[x]*block,y);
    int ans=0;
    fors(i,x,len){
        ans+=(val[i]*mtag[belong[x]]%p+tag[belong[x]]);
    }
    
    if(belong[x]!=belong[y]){
        fors(i,(belong[y]-1)*block+1,y){
            ans+=(val[i]*mtag[belong[y]]%p+tag[belong[y]]);
        }
    }
    fors(i,belong[x]+1,belong[y]-1){
        ans+=sum[i];
    }
    return ans%p;
}
int onequery(int x){
    return (val[x]*mtag[belong[x]]+tag[belong[x]])%p;
}
signed main()
{
    n=read(),m=read(),p=read();
    block=sqrt(n);
    fors(i,1,n)
        val[i]=read();
    fors(i,1,n){
        belong[i]=(i-1)/block+1;
        sum[belong[i]]+=val[i];
        tot[belong[i]]++;mtag[i]=1;
    }
    
    fors(i,1,m){
        int op=read();
        if(op==1){
            int x=read(),y=read(),k=read();
            mul(x,y,k);
        }
        else if(op==3){
            int x=read(),y=read();
            write(query(x,y)),putchar(10);
        }
        else if(op==2){
            int x=read(),y=read(),k=read();
            add(x,y,k);
        }
    }
    return 0;
}