#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define ll int
#define fors(i,a,b) for(ll i=(a);i<=(b);++i)
int n,k,lena,lenb,nexts[1000001];
char a[1000001],b[1000001];
inline void g_n(){
    int t=0,t1;
    nexts[0]=t1=-1;
    while(t<lenb)
        if(t1 == -1 || b[t]==b[t1])
            nexts[++t]=++t1;
        else t1=nexts[t1];
}
inline void kmp(){
    int as=0,bs=0;
    while(as<lena){
        if(bs == -1 || a[as]==b[bs])
            ++as,++bs;
        else bs=nexts[bs];
        if(bs==lenb){
            printf("%d\n",as-lenb+1);
            bs=nexts[bs];
        }
    }
}
int main(int argc, char const *argv[])
{
    scanf("%s",a);
    scanf("%s",b);
    lena=strlen(a);
    lenb=strlen(b);
    g_n();
    kmp();
    fors(i,1,lenb)
        printf("%d ",nexts[i]);
    return 0;
}