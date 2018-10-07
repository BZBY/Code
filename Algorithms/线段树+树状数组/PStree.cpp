#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
const int Size=1<<17;
inline char getch(){
    static char buf[Size],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,Size,stdin),p1==p2) ? EOF : *p1++;
}
int read(){
    int s=0,f=1;
    char c=getch();
    while(c>'9' || c<'0'){if(c=='-') f=-1; c=getch();}
    while(c<='9' && c>='0'){s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*f;
}
const int maxn=1000007;
int a[maxn],rt[maxn<<4],n,m,q;

struct PSTree
{
    int ls[maxn<<4],rs[maxn<<4],val[maxn<<4],cnt;
    void build(int &cur,int l,int r){
        cur=++cnt;
        if(l==r){
            val[cur]=a[l];
            return ;
        }
        int mid=l+((r-l)>>1);
        build(ls[cur],l,mid);
        build(rs[cur],mid+1,r);
    }

    inline void date(int &cur,int pre,int l,int r,int q,int v){
        cur=++cnt;
        ls[cur]=ls[pre],rs[cur]=rs[pre],val[cur]=val[pre];
        if(l==r){
            val[cur]=v;
            return;
        }
        int mid=l+((r-l)>>1);
        if(q<=mid) date(ls[cur],ls[pre],l,mid,q,v);
        else date(rs[cur],rs[pre],mid+1,r,q,v);
    }

    inline int query(int cur,int l,int r,int q){
        if(l==r) return val[cur];
        int mid=l+((r-l)>>1);
        if(q<=mid) return query(ls[cur],l,mid,q);
        else return query(rs[cur],mid+1,r,q);
    }

}tree;
int main(int argc, char const *argv[])
{
    n=read(),m=read();
    fors(i,1,n)
        a[i]=read();
    tree.build(rt[0],1,n);
    fors(i,1,m){
        int pre=read(),op=read(),x=read();
        if(op==1){
            int v=read();
            tree.date(rt[i],rt[pre],1,n,x,v);
        }
        else {
            printf("%d\n",tree.query(rt[pre],1,n,x));
            rt[i]=rt[pre];
        }
    }
    return 0;
}