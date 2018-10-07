#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long ll;
const int Size=1<<28;
inline char getch(){
    static char buf[Size],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,Size,stdin),p1==p2) ? EOF : *p1++;
}
int read(){
    int s=0,f=1;
    char c=getch();
    while(c>'9' || c<'0'){if(c=='-') f=-1;c=getch();}
    while(c<='9' && c>='0'){s=(s<<1)+(s<<3)+c-'0';c=getch();}
    return s*f;
}
void write(int x){
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))
const int maxn=14233337;
#define hash(x) (x%maxn)

const int _end=123804765;
unsigned th_tab[2][maxn];
int _sta;
bool H_tab[2][maxn];
queue<int > q[2];
int move(int key,char c){
	int p0=1,kb=key,_map[3][3],x0,y0;
	while(1){
		if(kb%10==0) break;
		++p0,kb/=10;
	}
	kb=key;x0=(9-p0)/3,y0=(9-p0)%3;
	for(int i=2;i>=0;--i)
		for(int j=2;j>=0;--j)
			_map[i][j]=kb%10,kb/=10;
	switch(c){
		case 'l' :if(!y0) return key;swap(_map[x0][y0],_map[x0][y0-1]);break;
		case 'r' :if(y0==2) return key;swap(_map[x0][y0],_map[x0][y0+1]);break;
		case 'u' :if(!x0) return key;swap(_map[x0][y0],_map[x0-1][y0]);break;
		case 'd' :if(x0==2) return key;swap(_map[x0][y0],_map[x0+1][y0]);break;
		default : break;
	}
	kb=0;
	fors(i,0,2)
	fors(j,0,2)
		kb=kb*10+_map[i][j];
	return kb;
}

int main()
{
    _sta=read();
	if(_sta==_end) putchar('0'),exit(0);
	q[0].push(_sta);q[1].push(_end);
	H_tab[0][hash(_sta)]=H_tab[1][hash(_end)]=1;
	th_tab[0][hash(_sta)]=th_tab[1][hash(_end)]=0;
	while(!q[0].empty() || !q[1].empty()){
		int news;
		if(!q[0].empty()){
			news=move(q[0].front(),'u');
			if(!H_tab[0][hash(news)]){
				H_tab[0][hash(news)]=1,q[0].push(news),th_tab[0][hash(news)]=th_tab[0][hash(q[0].front())]+1;
				if(H_tab[1][hash(news)]) write(th_tab[0][hash(news)]+th_tab[1][hash(news)]),exit(0);
			}
			news=move(q[0].front(),'d');
			if(!H_tab[0][hash(news)]){
				H_tab[0][hash(news)]=1,q[0].push(news),th_tab[0][hash(news)]=th_tab[0][hash(q[0].front())]+1;
				if(H_tab[1][hash(news)]) write(th_tab[0][hash(news)]+th_tab[1][hash(news)]),exit(0);
			}
			news=move(q[0].front(),'l');
			if(!H_tab[0][hash(news)]){
				H_tab[0][hash(news)]=1,q[0].push(news),th_tab[0][hash(news)]=th_tab[0][hash(q[0].front())]+1;
				if(H_tab[1][hash(news)]) write(th_tab[0][hash(news)]+th_tab[1][hash(news)]),exit(0);
			}
			news=move(q[0].front(),'r');
			if(!H_tab[0][hash(news)]){
				H_tab[0][hash(news)]=1,q[0].push(news),th_tab[0][hash(news)]=th_tab[0][hash(q[0].front())]+1;
				if(H_tab[1][hash(news)]) write(th_tab[0][hash(news)]+th_tab[1][hash(news)]),exit(0);
			}
			q[0].pop();
		}
		if(!q[1].empty()){
			news=move(q[1].front(),'u');
			if(!H_tab[1][hash(news)]){
				H_tab[1][hash(news)]=1,q[1].push(news),th_tab[1][hash(news)]=th_tab[1][hash(q[1].front())]+1
				if(H_tab[0][hash(news)]) write(th_tab[1][hash(news)]+th_tab[0][hash(news)]),exit(0);
			}
			news=move(q[1].front(),'d');
			if(!H_tab[1][hash(news)]){
				H_tab[1][hash(news)]=1,q[1].push(news),th_tab[1][hash(news)]=th_tab[1][hash(q[1].front())]+1
				if(H_tab[0][hash(news)]) write(th_tab[1][hash(news)]+th_tab[0][hash(news)]),exit(0);
			}
			news=move(q[1].front(),'l');
			if(!H_tab[1][hash(news)]){
				H_tab[1][hash(news)]=1,q[1].push(news),th_tab[1][hash(news)]=th_tab[1][hash(q[1].front())]+1
				if(H_tab[0][hash(news)]) write(th_tab[1][hash(news)]+th_tab[0][hash(news)]),exit(0);
			}
			news=move(q[1].front(),'r');
			if(!H_tab[1][hash(news)]){
				H_tab[1][hash(news)]=1,q[1].push(news),th_tab[1][hash(news)]=th_tab[1][hash(q[1].front())]+1
				if(H_tab[0][hash(news)]) write(th_tab[1][hash(news)]+th_tab[0][hash(news)]),exit(0);
			}
			q[1].pop();
		}
	}
    return 0;
}