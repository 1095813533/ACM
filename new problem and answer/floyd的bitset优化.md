# floyd的bitset优化
题目描述<br>
农夫有N头牛，他要给牛排名，他已经知道M对牛的相对排名（比如X>Y），求出他还需要知道多少对，就能准确地将所有牛排名<br>
输入格式<br>
输入N,M。接下来的M行每行输入X,Y，代表X>Y<br>
```cpp
#include <iostream>
#include <cstdio>
#include <bitset>
using namespace std;
const int maxn = 1005;
int n, m;
bitset<maxn> maps[maxn];
void floyd() {
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			if (maps[i][k]) maps[i] |= maps[k];
		}
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for (int i = 1; i <= m; i++) {
		int u, v; scanf("%d%d",&u,&v);
		maps[u][v] = true;
	}
	floyd();
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = i+1; j <= n; j++) {
			if (!maps[i][j] && !maps[j][i]) ans++;
		}
	}
	printf("%d\n",ans);
    return 0;
}
```
