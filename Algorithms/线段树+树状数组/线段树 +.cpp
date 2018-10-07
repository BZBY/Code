#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll; 
#define fors(i,a,b) for(int  i=(a);i<=(b);++i)
const int SIZE=1<<28;
inline char getch(){
    static char buf[SIZE],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2) ? EOF : *p1++;
}
ll read(){
    ll s=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') {s=(s<<1)+(s<<3)+c-'0';c=getchar();}
    return s*=f;
}
inline ll max(ll a,ll b){
    return a<b ? b : a;
}

ll n,m,a[800005],ans[800005],tag[800005];

inline ll ls(ll p){
    return p<<1;
}
inline ll rs(ll p){
    return p<<1|1;
}
void push_up(ll p){
    ans[p]=ans[ls(p)]+ans[rs(p)];
}
int t[100000];
void push_up_sum(int p){
    t[p]=t[ls(p)]+t[rs(p)];
}// 向上不断维护区间操作 

void push_up_min(int p){//max and min
    t[p]=min(t[ls(p)],t[rs(p)]);
//t[p]=max(t[lc(p)],t[rc(p)]);             
}

void build(ll p,ll l,ll r){
    tag[p]=0;
    if(l==r){ans[p]=a[l];return ;}
    //如果左右区间相同，那么必然是叶子节点啦，只有叶子节点是被真实赋值的
    ll mid=(l+r)>>1;
    build(ls(p),l,mid);
    build(rs(p),mid+1,r);
//此处由于我们采用的是二叉树，所以对于整个结构来说，可以用二分来降低复杂度，否则树形结构则没有什么明显的优化
    push_up(p);
//此处由于我们是要通过子节点来维护父亲节点，所以pushup的位置应当是在回溯时。
} 
void f(ll p,ll l,ll r,ll k){
    tag[p]+=k;
    ans[p]+=k*(r-l+1);
//由于是这个区间统一改变，所以ans数组要加元素个数次啦 
}
void push_down(ll p,ll l,ll r){
    ll mid=(r+l)>>1;
    f(ls(p),l,mid,tag[p]);
    f(rs(p),mid+1,r,tag[p]);
    tag[p]=0;
}
void update(ll p,ll lt,ll rt,ll l,ll r,ll k){
    if(l>=lt && rt>=r){

        ans[p]+=k*(r-l+1);
        tag[p]+=k;
        return;
    }
    push_down(p,l,r);
    ll mid=(l+r)>>1;
    //回溯之前（也可以说是下一次递归之前，因为没有递归就没有回溯） 
    //由于是在回溯之前不断向下传递，所以自然每个节点都可以更新到 
    if(lt<=mid) update(ls(p),lt,rt,l,mid,k);
    if(rt>mid) update(rs(p),lt,rt,mid+1,r,k);
    push_up(p);
}
ll query(ll p,ll lt,ll rt,ll l,ll r){
    ll ret=0;
    if(rt>=r && l>=lt) return ansk[p];
    ll mid=(r+l)>>1;
    push_down(p,l,r);
    if(lt<=mid) ret+=query(ls(p),lt,rt,l,mid);
    if(rt>mid) ret+=query(rs(p),lt,rt,mid+1,r);
    return ret;
}
int main()
{
    n=read(),m=read();
    fors(i,1,n) a[i]=read();
    build(1,1,n);
    while(m--){
        ll op=read(),x=read(),y=read();
        if(op==1){
            ll k=read();
            update(1,x,y,1,n,k);
        }
        if(op==2){
            printf("%lld\n",query(1,x,y,1,n));
        }
    }
    return 0;
}
