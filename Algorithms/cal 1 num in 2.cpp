#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>
#include <deque>
#include <stack>
using namespace std;
#define fors(i,a,b) for(int i=(a);i<=(b);++i)
#define ford(i,a,b) for(int i=(a);i>=(b);--i)
#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) < (y) ? (y) : (x))
#define swap(x,y) ((x)^=(y),(y)^=(x),(x)^=(y))
#define abs(x) ((x) < 0 ? -(x) : (x)) 
#define forvit(i) for(vector<int> :: iterator it=(i).begin();it!=(i).end();++it) 
#define v *it
#define mem(x,i) (memset((x),(i),sizeof (x)))
const int maxn=2e5+7;
typedef long long ll;
const int inf=1<<25;
int read(){
    int s=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0' && c<='9') {s=s*10+c-48;c=getchar();}
    return s*f;
}

void write(int x){
    static int sta[36];
    int top=0;
    if(x < 0) {putchar('-');x=-x;}
    do{
        sta[top++]=x%10;
        x/=10;
    }while(x);
    while(top) putchar(sta[--top]+48);
}
int ans,n,dp[2][maxn],num[maxn];
int count(unsigned int x){
    x= (x & 0x55555555) + ((x>>1) & 0x55555555);
    x= (x & 0x33333333) + ((x>>2) & 0x33333333);
    x= (x & 0x0f0f0f0f) + ((x>>4) & 0x0f0f0f0f);
    x= (x & 0x00ff00ff) + ((x>>8) & 0x00ff00ff);
    x= (x & 0x0000ffff) + ((x>>16) & 0x0000ffff);
    return x;
}
void init(){
    fors(i,0,65535)
        num[i]=count(i);
}
int countx(unsigned int x){
    return (num[x & 65535] + num[(x>>16) & 65535]);
}
int dist(int a,int b){//快速求汉明距离 求两个01字串相同的位的个数
    return countx(a&b);
}
// 1^0 =0 ,1^1 =0 , 0^0 = 0 0^1 =1
// lowbit = the finall 1  1111 & (-15) = 1  10000 & (-16) = 16
int main(int argc, char const *argv[])
{
    init();
    cout<<countx(65535)<<endl<<count(65535)<<endl;
    cout<<" ^ is or not same : 1 ^ 2 : -> "<< (1^2) << " | 1^1 = "<<(1^1)<<endl;
    cout<<" & clear 12123 &= 0 -> "<<(12123 & 0)<<endl;
    cout<<" & find id  x=10010 , 15=1111 , 2= 00010 ==  x=18 , x &= (15) = " <<(18 & 15)<<endl;
    cout<<"| change 1 = 18=10010 , 15= 1111,31 = 11111  , 18 |=15 = "<<(18 | 15)<<endl;
    cout<<"~  ~1=0,~0=1,x=15, 14 = 1110 ,~1 = 1111111110 , x& ~1 == "<<(15 & (~1))<<endl;
    return 0;
}