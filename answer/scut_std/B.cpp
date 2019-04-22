#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const int maxn = 2e5;
const int maxm = 18;
const int maxV = 1<<maxm;
const int INF = 0x3f3f3f3f;
const int P = 19260817;
int cost[maxV][maxm];
int start[maxn], mark[maxV], ans = INF, cc = INF, n;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

void init()
{
    for (int s = 0; s < maxV; ++s) {
        for(int i = 0; i < maxm; ++i)
        {
            cost[s][i] = PowMod( max(s,s^(1<<i))%P, 1<<i ) % P + 1;
        }
    }
}
struct node
{
    int u,dis;
    node(int _u=0, int _dis = 0): u(_u), dis(_dis){}
    bool operator <(const node& nn) const
    {
        return dis > nn.dis;
    }
};
priority_queue<node>que;
int dis[maxV];
void solve(int mask)
{
    while(!que.empty()) que.pop();
    for (int i = 0; i < maxV; ++i) dis[i] = INF;
    for (int i = 0; i < n; ++i)
        if(start[i] >> mask & 1) 
        {
            dis[start[i]] = 0;
            que.push(node(start[i], 0));
        }
    while(!que.empty())
    {
        node tmp = que.top(); que.pop();
        int u = tmp.u, d = tmp.dis;
        if(d >= ans) return;
        if(d != dis[u]) continue;
        if(d && mark[u])
        {
            ans = d;
            return;
        }
        for(int i = 0; i < maxm; ++i)
            if(dis[u^(1<<i)] > d + cost[u][i])
            {
                dis[u^(1<<i)] = d + cost[u][i];
                que.push(node(u^(1<<i), dis[u^(1<<i)]));
            }
    }
}
int main()
{
    init();
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) 
    {
        scanf("%d", &start[i]);
        if(mark[start[i]]==1) exit( puts("0")*0 );
        mark[start[i]] = 1;
    }
    for (int i = 0; i < maxm; ++i) solve(i);
    printf("%d\n",ans);
    return 0;
}
