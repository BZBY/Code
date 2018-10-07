#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#include <queue>
#include <set>
#include <map>
using namespace std;
const int MAXN=100000;


int heaps[MAXN],sz=0;
void push_heap(int x){
    int i=sz++;
    while(i>0){
        int p=(i-1)>>1;
        if(heaps[p]<=x) break;
        heaps[i]=heaps[p];//date update;
        i=p;
    }
    heaps[i]=x;
}

int top_heaps(){//mins
    int ret=heaps[0];
    int x=heaps[--sz];
    int i=0;
    while((i<<1|1) <sz){
        int a=i<<1|1,b=(i<<1)+2;
        if(b<sz && heaps[b]<heaps[a]) a=b;
        if(heaps[a]>x) break;
        heaps[i]=heaps[a];
        i=a;
    }
    heaps[i]=x;
    return ret;
}
int main(int argc, char const *argv[])
{
    stack<int> sta;
    sta.push(1);
    sta.push(2);
    sta.push(3);
    cout<<sta.size()<<endl;
    if(!sta.empty()) puts("OK");
    printf("%d\n",sta.top());
    sta.pop();
    printf("%d\n",sta.top());
    sta.pop();
    printf("%d\n",sta.top());

    puts("-----------------------------");
    puts("-----------------------------");
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    printf("%lld\n",q.size());
    while(!q.empty()){
        printf("%d\n",q.front());
        q.pop();
    }
    puts("-----------------------------");
    puts("-----------------------------");
    push_heap(5);
    push_heap(2);
    push_heap(3);
    printf("%d\n",top_heaps());
    printf("%d\n",top_heaps());
    priority_queue<int> ques;
    ques.push(2);
    ques.push(5);
    ques.push(1);
    printf("%lld\n",ques.size());
    while(!ques.empty()){
        printf("%d\n",ques.top());
        ques.pop();
    }

    puts("-----------------------------");
    puts("-----------------------------");
    
    set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);

    set<int> :: iterator ite;
    ite=s.find(1);
    if(ite==s.end()) puts("NO　FIND");
    else puts("FIND");
    s.erase(3);//delete

    s.insert(123);
    if(s.count(3)!=0) puts("FIND");
    else puts("NO　FIND");

    for(ite= s.begin();ite!=s.end();++ite){
        printf("%d\n",*ite);
    }
    puts("-----------------------------");
    puts("-----------------------------");
    

    map<int , const char*> maps;
    maps.insert(make_pair(1,"ONE"));
    maps.insert(make_pair(10,"TEN"));
    maps[100]="HUNDRED";
    map<int, const char*> :: iterator ites;
    ites=maps.find(1);
    puts(ites->second);
    ites=maps.find(2);
    if(ites==maps.end()) puts("NO　FIND");
    else puts("FIND");
    puts(maps[100]);
    for(ites=maps.begin();ites!=maps.end();++ites){
        printf("%d: %s\n",ites->first,ites->second);
    }

    puts("------------------------------");
    puts("------------------------------");


    return 0;

}
