#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll long long
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
const int SIZE=1<<26;
#define int ll
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
struct node
{
	ll v,mul,add;
}st[400003];
ll p;
ll a[100007];
void init(ll root,ll l,ll r){//初始化lazytag
	st[root].mul=1,st[root].add=0;
	if(l==r) st[root].v=a[l];
	else {
		ll mid=(l+r)>>1;
		init(root<<1,l,mid);
		init(root<<1|1,mid+1,r);
		st[root].v=st[root<<1].v+st[root<<1|1].v;
	}
	st[root].v%=p;
	return ;
}
//核心代码，维护lazytag
void push_down(int root,int l,int r){
	int mid=(l+r)>>1;//根据我们规定的优先度，儿子的值=此刻儿子的值*爸爸的乘法lazytag+儿子的区间长度*爸爸的加法lazytag
	st[root<<1].v=(st[root<<1].v * st[root].mul+st[root].add*(mid-l+1))%p;
	st[root<<1|1].v=(st[root<<1|1].v * st[root].mul+st[root].add*(r-mid))%p;
	//很好维护的lazytag
	st[root<<1].mul=(st[root<<1].mul*st[root].mul)%p;
	st[root<<1|1].mul=(st[root<<1|1].mul*st[root].mul)%p;
	st[root<<1].add=(st[root<<1].add * st[root].mul+st[root].add)%p;
	st[root<<1|1].add=(st[root<<1|1].add*st[root].mul+st[root].add)%p;
	//把父节点的值初始化
	st[root].mul=1;
	st[root].add=0;
	return ;	
}
//update1，乘法，stdl此刻区间的左边，stdr此刻区间的右边，l给出的左边，r给出的右边
void updatemul(int root,int lq,int rq,int l,int r,ll k){
	if(r< lq || l>rq) return ;//假如本区间和给出的区间没有交集
	if(l<=lq && rq<=r){//假如给出的区间包含本区间
		st[root].v=(st[root].v*k)%p;
		st[root].mul=(st[root].mul*k)%p;
		st[root].add=(st[root].add*k)%p;
		return ;
	}	
//假如给出的区间和本区间有交集，但是也有不交叉的部分
//先传递lazytag
	push_down(root,lq,rq);
	int mid=(lq+rq)>>1;
	updatemul(root<<1,lq,mid,l,r,k);
	updatemul(root<<1|1,mid+1,rq,l,r,k);
	st[root].v=(st[root<<1].v+st[root<<1|1].v)%p;
	return ;
}

void updateadd(int root,int lq,int rq,int l,int r,ll k){
	if(r<lq || l>rq) return ;
	if(l<=lq && rq<=r){
		st[root].add=(st[root].add+k)%p;
		st[root].v=(st[root].v+k*(rq-lq+1))%p;
		return ;
	}
	push_down(root,lq,rq);
	int mid=(lq+rq)>>1;
	updateadd(root<<1,lq,mid,l,r,k);
	updateadd(root<<1|1,mid+1,rq,l,r,k);
	st[root].v=(st[root<<1].v+st[root<<1|1].v)%p;
	return ;
}

ll query(int root,int lq,int rq,int l,int r){
	if(r<lq || l>rq) return 0;
	if(l<=lq && r>=rq) return st[root].v;
	push_down(root,lq,rq);
	int mid=(lq+rq)>>1;
	return (query(root<<1,lq,mid,l,r)+query(root<<1|1,mid+1,rq,l,r))%p;
}
signed main()
{
	int n=read(),m=read();
	p=read();
	fors(i,1,n) a[i]=read();
	init(1,1,n);
	while(m--){
		int tmp=read(),x,y,k;
		if(tmp==1){
			x=read(),y=read(),k=read();
			updatemul(1,1,n,x,y,k);
		}
		else if(tmp==2){
			x=read(),y=read(),k=read();
			updateadd(1,1,n,x,y,k);
		}
		else if(tmp==3){
			x=read(),y=read();
			printf("%lld\n",query(1,1,n,x,y));
		}
	}
	return 0;
}