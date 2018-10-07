#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<list>;
#include<vector>
#include<limits.h>
const int MAXN = 1507;
const int INF =INT_MAX;
struct Node {
    int v, f, index;
    Node(int v, int f, int index) : v(v), f(f), index(index) {}
};

inline char getcha(){
    static char buf[1<<17],*p1,*p2;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<17,stdin),p1==p2) ? EOF : *p1++;
}
inline int read(){
    int s=0,f=1;
    char c=getcha();
    while(c>'9' || c<'0') {if(c=='-') f=-1;c=getcha();}
    while(c<='9' && c>='0') {s=(s<<1)+(s<<3)+c-48;c=getcha();}
    return s*=f;
}
#define fors(i,a,b) for(int i=(a);i<=(b);++i) 
std::vector<Node> edge[MAXN];

std::vector<int> list[MAXN], height, count, que, excess;

typedef std::list<int> List;

std::vector<List::iterator> iter;

List dlist[MAXN];

int highest, highestActive;
typedef std::vector<Node>::iterator Iterator;

inline void add(int u,int v,int val) {
    edge[u].push_back(Node(v, val, edge[v].size()));
    edge[v].push_back(Node(u, 0, edge[u].size() - 1));
}

inline void globalRelabel(int n, int t) {
    height.assign(n, n);
    height[t] = 0;
    count.assign(n, 0);
    que.clear();
    que.resize(n + 1);
    int qh = 0, qt = 0;
    for (que[qt++] = t; qh < qt;) {
        int u = que[qh++], h = height[u] + 1;
        for (Iterator p = edge[u].begin(); p != edge[u].end(); ++p) {
            if (height[p->v] == n && edge[p->v][p->index].f > 0) {
                count[height[p->v] = h]++;
                que[qt++] = p->v;
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        list[i].clear();
        dlist[i].clear();
    }
    for (int u = 0; u < n; ++u) {
        if (height[u] < n) {
            iter[u] = dlist[height[u]].insert(dlist[height[u]].begin(), u);
            if (excess[u] > 0) list[height[u]].push_back(u);
        }
    }
    highest = (highestActive = height[que[qt - 1]]);
}

inline void push(int u, Node &e) {
    int v = e.v;
    int df = std::min(excess[u], e.f);
    e.f -= df;
    edge[v][e.index].f += df;
    excess[u] -= df;
    excess[v] += df;
    if (0 < excess[v] && excess[v] <= df) list[height[v]].push_back(v);
}

inline void discharge(int n, int u) {
    int nh = n;
    for (Iterator p = edge[u].begin(); p != edge[u].end(); ++p) {
        if (p->f > 0) {
            if (height[u] == height[p->v] + 1) {
                push(u, *p);
                if (excess[u] == 0) return;
            } else {
                nh = std::min(nh, height[p->v] + 1);
            }
        }
    }
    int h = height[u];
    if (count[h] == 1) {
        for (int i = h; i <= highest; ++i) {
            for (List::iterator it = dlist[i].begin(); it != dlist[i].end();
                 ++it) {
                --count[height[*it]];
                height[*it] = n;
            }
            dlist[i].clear();
        }
        highest = h - 1;
    } else {
        count[h]--;
        iter[u] = dlist[h].erase(iter[u]);
        height[u] = nh;
        if (nh == n) return;
        count[nh]++;
        iter[u] = dlist[nh].insert(dlist[nh].begin(), u);
        highest = std::max(highest, highestActive = nh);
        list[nh].push_back(u);
    }
}

inline int hlpp(int n, int s, int t) {
    if (s == t) return 0;
    highestActive = 0;
    highest = 0;
    height.assign(n, 0);
    height[s] = n;
    iter.resize(n);
    for (int i = 0; i < n; ++i)
        if (i != s)
            iter[i] = dlist[height[i]].insert(dlist[height[i]].begin(), i);
    count.assign(n, 0);
    count[0] = n - 1;
    excess.assign(n, 0);
    excess[s] = INF;
    excess[t] = -INF;
    for (int i = 0; i < (int)edge[s].size(); i++) push(s, edge[s][i]);
    globalRelabel(n, t);
    for (int u; highestActive >= 0;) {
        if (list[highestActive].empty()) {
            highestActive--;
            continue;
        }
        u = list[highestActive].back();
        list[highestActive].pop_back();
        discharge(n, u);
    }
    return excess[t] + INF;
}


int main() {
    int n=read(), m=read(), s=read(), t=read(),u, v, val;
    fors(i,1,m){
        u = read(), v = read(), val= read();
        add(u, v, val);
    }
    std::cout << hlpp(n + 1, s, t);
    return 0;
}