#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include <cmath>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
int ai,op,n,m,l,r,k;
const int maxn=1e6;
int prime[maxn+7],vis[maxn+7],tot;

int main()
{
	srand(time(0));
	int t=rand()%1000+45;
	fors(i,1,t){
		int l=rand()%1000000000+13152;
		cout<<l<<" "<<rand()%153340534+l<<endl;
	}
	return 0;
}
