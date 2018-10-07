#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
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
#define lson tree[x].ls
#define rson tree[x].rs
const int maxn=300007;
struct node
{
    int ls,rs;
}tree[maxn];

int f[maxn],vis[maxn],sons[maxn],sta[maxn],tag[maxn];
//判断节点是否为一个Splay的根（与普通Splay的区别1）
int nroot(int x){
    return tree[f[x]].ls==x || tree[f[x]].rs==x;
}
//原理很简单，如果连的是轻边，他的父亲的儿子里没有它
void push_up(int x){
    sons[x]=sons[tree[x].ls] ^ sons[tree[x].rs] ^ vis[x];
}

void push_rotate(int x){
    int t=tree[x].ls;
    tree[x].ls=tree[x].rs;
    tree[x].rs=t;
    tag[x]^=1;
}

void push_down(int x){//判断并释放懒标记
    if(tag[x]){
        if(lson) push_rotate(lson);
        if(rson) push_rotate(rson);
        tag[x]=0;
    }
}

void rotate(int x){
    int y=f[x],z=f[y],k=tree[y].rs==x;
    int w= ((!k)==0) ? lson : rson;
    if(nroot(y))
        (tree[z].rs==y) ? tree[z].rs=x : tree[z].ls=x;//额外注意if(nroot(y))语句，此处不判断会引起致命错误（与普通Splay的区别2）
    ((!k)==0) ? lson=y : rson=y;
    k==0 ? tree[y].ls=w : tree[y].rs=w;
    if(w) f[w]=y;
    f[y]=x,f[x]=z;
    push_up(y);
}

void splay(int x){
    int y=x,z=0;
    sta[++z]=y;//st为栈，暂存当前点到根的整条路径，pushdown时一定要从上往下放标记（与普通Splay的区别4）
    while(nroot(y)) sta[++z]=y=f[y];
    while(z) push_down(sta[z--]);
    while(nroot(x)){
        y=f[x],z=f[y];
        if(nroot(y))
            rotate((tree[y].ls==x) ^ (tree[z].ls==y) ? x : y);
        rotate(x);
    }
    push_up(x);
}

void access(int x){//访问
    for(int i=0;x;x=f[i=x])
        splay(x),rson=i,push_up(x);
}

void maker_root(int x){//换根
    access(x);
    splay(x);
    push_rotate(x);
}

int find_root(int x){//找根（在真实的树中的）
    access(x);
    splay(x);
    while(lson)
        push_down(x),x=lson;
    return x;
}

void spilt(int x,int y){//提取路径
    maker_root(x);
    access(y);
    splay(y);
}

void link(int x,int y){//连边
    maker_root(x);
    if(find_root(y)!=x)
        f[x]=y;
}

void cut_G(int x,int y){
    maker_root(x);
    if(find_root(y)==x && f[x]==y && !rson){
        f[x]=tree[y].ls=0;
        push_up(y);
    }
}

int main(int argc, char const *argv[])
{
    int n=read(),m=read(),op,x,y;
    fors(i,1,n) vis[i]=read();
    while(m--){
        op=read(),x=read(),y=read();
        if(!op) {
            spilt(x,y);
            printf("%d\n",sons[y]);
        }
        else if(op==1) link(x,y);
        else if(op==2) cut_G(x,y);
        else splay(x),vis[x]=y;
    }
    return 0;
}