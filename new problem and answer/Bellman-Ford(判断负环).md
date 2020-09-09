# 判断负环
题目描述<br>
寻找一个从顶点1所能到达的负环，负环定义为：一个边权之和为负的环。<br>
输入格式<br>
第一行一个正整数T表示数据组数，对于每组数据：<br>
第一行两个正整数N M，表示图有N个顶点，M条边<br>
接下来M行，每行三个整数a b w，表示a->b有一条权值为w的边（若w<0则为单向，否则双向）<br>
输出格式<br>
共T行。对于每组数据，存在负环则输出一行"YE5"(不含引号)，否则输出一行"N0"(不含引号)。<br>

### Bellman-Ford<br>
```
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2005, maxm = 3005;
const int inf = 0x3f3f3f3f;
struct edge {
    int v, w;
};
vector<edge> maps[maxn];
int dis[maxn], n, m;

bool BellmanFord(int s) {  // s为源点
    fill(dis+1, dis+1+n, inf);
    dis[s] = 0;
    for (int i = 1; i <= n-1; i++) {
        for (int u = 1; u <= n; u++) {
            for (int j = 0; j < maps[u].size(); j++) {
                int v = maps[u][j].v;
                int w = maps[u][j].w;
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                }
            }
        }
    }
    
    if (maps[s].size() == 0) return true;  // 如果s点没有和其他点相连，则没有负环 
    for (int u = 1; u <= n; u++) {
        for (int j = 0; j < maps[u].size(); j++) {
            int v = maps[u][j].v;
            int w = maps[u][j].w;
            if (dis[u] + w < dis[v])
                return false;
        }
    }
    return true;
}
int main() {
    int t; scanf("%d",&t);
    while (t--) {
        scanf("%d%d",&n,&m);
        for (int i = 1; i <= n; i++) maps[i].clear();

        for (int i = 1; i <= m; i++) {
            int u, v, w; scanf("%d%d%d",&u,&v,&w);
            if (w < 0) maps[u].push_back(edge{v,w});
            else {
            	maps[u].push_back(edge{v,w});
            	maps[v].push_back(edge{u,w});
			}
        }
        bool flag = BellmanFord(1);
   	    if (flag) puts("N0");
   	    else puts("YE5");
    }
}

```
