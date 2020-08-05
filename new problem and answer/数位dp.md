# 数位dp
题目描述<br>
给定一张 n (n≤20) 个点的带权无向图，点从0∼n−1标号，求起点 0 到终点 n-1 的最短Hamilton路径。 Hamilton路径的定义是从 0 到 n-1 不重不漏地经过每个点恰好一次。<br>

输入格式<br>

第一行一个整数n。<br>
接下来n行每行n个整数，其中第i行第j个整数表示点i到j的距离（一个不超过10^7的正整数，记为a[i,j]）。<br>
对于任意的x,y,z，数据保证 a[x,x]=0，a[x,y]=a[y,x] 并且a[x,y]+a[y,z]≥a[x,z]。<br>

输出格式<br>
一个整数，表示最短Hamilton路径的长度。<br>
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 21;
int dp[1<<maxn][maxn];
int maps[maxn][maxn];
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> maps[i][j];
    memset(dp,0x3f3f3f3f,sizeof(dp));
    dp[0][0] = 0;
    for (int i = 0; i < (1<<n); i++) {
        for (int j = 0; j < n; j++) {
            if ((i>>j)&1) {
                for (int k = 0; k < n; k++) {
                    if ((i>>k)&1)
                        dp[i][j] = min(dp[i][j],dp[i^(1<<j)][k]+maps[k][j]);
                }
            }
        }
    }
    printf("%d\n",dp[(1<<n)-1][n-1]);
    return 0;
}
```
