#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <cstdlib>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long ll;
const int Size=1<<18;
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
const int maxn=500007;
struct node
{
    int ls,rs,v;
}tree[maxn<<4];
int cnt,rt[maxn],a[maxn],b[maxn],pre;

void bulid(int &cur,int l,int r){
    cur=++cnt;
    if(l==r) return;
    int mid=(l+r)>>1;
    bulid(tree[cur].ls,l,mid);
    bulid(tree[cur].rs,mid+1,r); 
}

int  update(int cur,int l,int r){
    int p=++cnt;
    tree[p].ls=tree[cur].ls,tree[p].rs=tree[cur].rs,tree[p].v=tree[cur].v+1;
    if(l==r) return p;
    int mid=(l+r)>>1;
    (pre <= mid) ? update(tree[cur].ls,l,mid) : update(tree[cur].rs,mid+1,r); 
    return pre;
}

int query(int u,int v,int k,int l,int r){
    int ans=0,mid=(l+r)>>1,x=tree[tree[v].ls].v-tree[tree[u].ls].v;
    if(l==r) return 1;
    (x>=k) ? ans=query(tree[u].ls,tree[v].ls,k,l,mid) : ans=query(tree[u].rs,tree[v].rs,k-x,mid+1,r);
    return ans;
}
int main(int argc, char const *argv[])
{
    int n=read(),m=read();
    fors(i,1,n) a[i]=read(),b[i]=a[i];
    sort(b+1,b+1+n);
    int q=unique(b+1,b+1+n)-b-1;
    bulid(rt[0],1,q);
    fors(i,1,n){
        pre=lower_bound(b+1,b+1+q,a[i])-b;
        rt[i]=update(rt[i-1],1,q);
    }
    fors(i,1,m){
        int l=read(),r=read(),k=read();
        printf("%d\n",b[query(rt[l-1],rt[r],k,1,q)]);
    }
    return 0;
}