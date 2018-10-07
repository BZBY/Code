#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
int read(){
    int s=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') {s=(s<<1)+(s<<3)+c-'0';c=getchar();}
    return s*=f;
}

//EK Inter liu
int n,m,s,t;
struct nodes
{
	int v,val,next;
}node[201010];
int tot=1,head[202010];//top必须从一个奇数开始,fubian
inline void add(int x,int y,int val){
	node[++tot].v=y;
	node[tot].next=head[x];
	head[x]=tot;
	node[tot].val=val;
}
int inque[101010];
struct Pre
{
	int v,edge;
}pre[101010];

inline bool bfs(){
	queue<int > q;
	memset(inque,0,sizeof(inque));
	memset(pre,-1,sizeof(pre));
	inque[s]=1;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=node[i].next){
			int to=node[i].v;
			if(!inque[to] && node[i].val){//node[i].val==0则已经该路径满了
				pre[to].v=u;
				pre[to].edge=i;
				if(to==t) return 1;
				inque[to]=1;
				q.push(to);
			}
		}	
	}
	return 0;
}

const int inf=1<<28;
int EK(){
	int ans=0;
	while(bfs()){
		int mi=inf;
		for(int i=t;i!=s;i=pre[i].v)
			mi=min(mi,node[pre[i].edge].val);
		for(int i=t;i!=s;i=pre[i].v){
			node[pre[i].edge].val-=mi;
			node[pre[i].edge^1].val+=mi;
		}
		ans+=mi;
	}
	return ans;
}

int main(int argc, char const *argv[])
{
	n=read(),m=read(),s=read(),t=read();
	int u,v,w;
	fors(i,1,m){
		u=read(),v=read(),w=read();
		add(u,v,w);
		add(v,u,0);
	}
	printf("%d\n",EK());
	return 0;
}












