#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long ll;
const int Size=1<<18;
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
const int maxn=1e5+7;
int fa[maxn],tree[maxn][2],size[maxn],rev[maxn],rt,n,m;
void push_up(int x){
    size[x]=size[tree[x][0]]+size[tree[x][1]]+1;
}
void push_down(int x){
    if(rev[x]){
        swap(tree[x][0],tree[x][1]);
        rev[tree[x][0]]^=1;
        rev[tree[x][1]]^=1;
        rev[x]=0;
    }
}

void rotate(int x,int &k){
    int y=fa[x],z=fa[y],kind;
    kind= (tree[y][0]==x) ? 1:0;
    if(y==k) k=x;
    else {
        (tree[z][0]==y) ? tree[z][0]=x : tree[z][1]=x;
    }
    tree[y][kind^1]=tree[x][kind] , fa[tree[y][kind^1]]=y;
    tree[x][kind]=y , fa[y]=x,fa[x]=z;
    push_up(x);
    push_up(y);
}


void splay(int x,int &k){
    while(x!=k){
        int y=fa[x],z=fa[y];
        if(y!=k){
            if((tree[y][0] == x) ^(tree[z][0] == y)) 
                rotate(x,k);
        }
        rotate(x,k);
    }
}

void build(int l,int r,int f){
    if(l>r) return ;
    int mid=(l+r)>>1;
    (mid < f) ? tree[f][0]=mid : tree[f][1]=mid;
    fa[mid]=f , size[mid]=1;
    if(l==r) return ;
    build(l,mid-1,mid);
    build(mid+1,r,mid);
    push_up(mid);
}

int find(int x,int k){
    push_down(x);
    int s=size[tree[x][0]];
    if(k==s+1)
        return x;
    if(k<=s) return find(tree[x][0],k);
    else return find(tree[x][1],k-s-1);
}

void rever(int l,int r){
    int x=find(rt,l),y=find(rt,r+2);
    splay(x,rt);
    splay(y,tree[x][1]);
    int z=tree[y][0];
    rev[z]^=1;
}
int main(int argc, char const *argv[])
{
    n=read(),m=read();
    rt=(n+3)>>1;
    build(1,n+2,rt);
    fors(i,1,m){
        int l=read(),r=read();
        rever(l,r);
    }
    fors(i,2,n+1)
        printf("%d ",find(rt,i)-1);
    return 0;
}