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
const int maxn=10007;

inline int rand ( )  {
    static int seed = 2333;
    return seed = ( int ) seed * 482711LL % 2147483647; 
}

int m,n,a[maxn];

namespace Treap
{
    struct bal_tree
    {
        int w,sz,num,fix,ch[2];
    }tree[maxn*20];
    
    int tot;

    int new_node(int w){
        ++tot;
        tree[tot].w=w,tree[tot].fix=rand(),tree[tot].num=1,tree[tot].ch[0]=tree[tot].ch[1]=0,tree[tot].sz=1;
        return tot;
    }

    void push_up(int x){
        tree[x].sz=tree[tree[x].ch[0]].sz+tree[tree[x].ch[1]].sz+tree[x].num;
    }

    void rotate(int &x,int d){
        int y=tree[x].ch[d];
        tree[x].ch[d]=tree[y].ch[d^1];
        tree[y].ch[d^1]=x;
        push_up(x),push_up(y);
        x=y;        
    }

    void insert(int &x,int w){
        if(!x) 
            x=new_node(w);
        else if(tree[x].w==w)
                ++tree[x].num;
        else {
            if(tree[x].w > w){
                insert(tree[x].ch[0],w);
                if(tree[tree[x].ch[0]].fix > tree[x].fix)
                    rotate(x,0);
            }
            else {
                insert(tree[x].ch[1],w);
                if(tree[tree[x].ch[1]].fix > tree[x].fix)
                    rotate(x,1);
            }
        }
        push_up(x);
    }

    void remove(int &x,int w){
        if(tree[x].w > w) 
            remove(tree[x].ch[0],w);
        else if(tree[x].w < w) 
                remove(tree[x].ch[1],w);
        else {
            if(tree[x].num > 1)
                --tree[x].num;
            else {
                if(!tree[x].ch[0] && !tree[x].ch[1])
                    x=0;
                else if(!tree[x].ch[0]){
                    rotate(x,1);
                    remove(tree[x].ch[0],w);
                }
                else if(!tree[x].ch[1]){
                    rotate(x,0);
                    remove(tree[x].ch[1],w);
                }
                else {
                    if(tree[tree[x].ch[0]].fix > tree[tree[x].ch[1]].fix){
                        rotate(x,0);
                        remove(tree[x].ch[1],w);
                    }
                    else {
                        rotate(x,1);
                        remove(tree[x].ch[0],w);
                    }
                }

            }
        }
        if(x) push_up(x);
    }

    int query_rank(int x,int k){
        if(!x) return 0;
        if(tree[x].w > k)
            return query_rank(tree[x].ch[0],k);
        else if(tree[x].w == k)
            return tree[tree[x].ch[0]].sz;
        else return tree[tree[x].ch[0]].sz+tree[x].num+query_rank(tree[x].ch[1],k);
    }

    int query_num(int x,int k){
        if(tree[tree[x].ch[0]].sz+1 == k)
            return tree[x].w;
        else if(tree[tree[x].ch[0]].sz+1 < k)
            return query_num(tree[x].ch[1],k-1-tree[tree[x].ch[0]].sz);
        else return query_num(tree[x].ch[0],k);
    }

    int query_pre(int x,int k){
        if(!x)
            return -2147483647;
        if(tree[x].w >= k)
            return query_pre(tree[x].ch[0],k);
        else
            return max(tree[x].w,query_pre(tree[x].ch[1],k));
    }

    int query_suf(int x,int k){
        if(!x) 
            return 2147483647;
        if(tree[x].w <= k)
            return query_suf(tree[x].ch[1],k);
        else 
            return min(tree[x].w,query_suf(tree[x].ch[0],k));
    }

}

namespace SEG{
    struct segment
    {
        int ls,rs,root;
    }tree[maxn<<3];

    void build(int x,int l,int r){
        tree[x].ls=l,tree[x].rs=r;
        fors(i,l,r)
            Treap::insert(tree[x].root,a[i]);
        if(l==r) return ;
        int mid=(l+r)>>1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
    }

    void modify(int x,int l,int r){
        Treap::remove(tree[x].root,a[l]);
        Treap::insert(tree[x].root,r);
        if(tree[x].ls==tree[x].rs) return;
        int mid=(tree[x].ls+tree[x].rs)>>1;
        (l>mid) ? modify(x<<1|1,l,r) : modify(x<<1,l,r);
    }

    int query_rank(int x,int l,int r,int k){
        if(tree[x].ls > r || tree[x].rs < l)
            return 0;
        if(tree[x].ls >= l && tree[x].rs <= r)
            return Treap :: query_rank(tree[x].root,k);
        else 
            return query_rank(x<<1,l,r,k)+query_rank(x<<1|1,l,r,k);
    }

    int query_num(int u,int v,int k){
        int l=0,r=1e8,mid;
        while(l<r){
            mid=(l+r+1)>>1;// +1
            (query_rank(1,u,v,mid) < k) ? l=mid : r=mid-1;
        }
        return r;
    }

    int query_pre(int x,int l,int r,int k){
        if(tree[x].ls > r || tree[x].rs < l)
            return -2147483647;
        if(tree[x].ls >= l && tree[x].rs <= r)
            return Treap::query_pre(tree[x].root,k);
        else 
            return max(query_pre(x<<1,l,r,k),query_pre(x<<1|1,l,r,k));
    }

    int query_suf(int x,int l,int r,int k){
        if(tree[x].ls > r || tree[x].rs < l)
            return 2147483647;
        if(tree[x].ls >= l && tree[x].rs <= r)
            return Treap::query_suf(tree[x].root,k);
        else
            return min(query_suf(x<<1,l,r,k),query_suf(x<<1|1,l,r,k));
    }
}
int main(int argc, char const *argv[])
{
    n=read(),m=read();
    fors(i,1,n)
        a[i]=read();
    SEG ::build(1,1,n);
    fors(i,1,m){
        int op=read();
        if(op==3){
            int x=read(),y=read();
            SEG::modify(1,x,y);
            a[x]=y;
        }
        else {
            int l=read(),r=read(),k=read();
            if(op==1)
                printf("%d\n",SEG::query_rank(1,l,r,k)+1);
            else if(op==2)
                printf("%d\n",SEG::query_num(l,r,k));
            else if(op==4)
                printf("%d\n",SEG::query_pre(1,l,r,k));
            else
                printf("%d\n",SEG::query_suf(1,l,r,k));
        }
    }
    return 0;
}