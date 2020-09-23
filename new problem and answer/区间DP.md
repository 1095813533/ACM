# 区间DP
题目描述<br>
在一个圆形操场的四周摆放N堆石子,现要将石子有次序地合并成一堆.规定每次只能选相邻的2堆合并成新的一堆，并将新的一堆的石子数，记为该次合并的得分。<br>

试设计出1个算法,计算出将N堆石子合并成1堆的最小得分和最大得分.<br>

输入格式<br>
数据的第1行试正整数N,1≤N≤100,表示有N堆石子.第2行有N个数,分别表示每堆石子的个数.<br>

输出格式<br>
输出共2行,第1行为最小得分,第2行为最大得分.<br>
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 205;
const int inf = 0x3f3f3f3f;
int cost1[maxn][maxn], cost2[maxn][maxn];  //当前合并的代价
int dp1[maxn][maxn], dp2[maxn][maxn];
int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
	    cin >> cost1[i][i];
		cost2[i][i] = cost1[i][i];
	}
    for (int i = 1; i <= n; i++) {
    	cost1[n+i][n+i] = cost1[i][i];
    	cost2[n+i][n+i] = cost2[i][i];
	}
    n <<= 1;
    for (int i = 2; i <= n/2; i++) {
		for (int j = 0; j <= n-i; j++) {
            int x = i+j, y = j+1;
            for (int k = 1; k < i; k++) {
                cost1[x][y] = cost1[x-k][y] + cost1[x][y+i-k];
                cost2[x][y] = cost2[x-k][y] + cost2[x][y+i-k];
                if (dp1[x][y]) dp1[x][y] = min(dp1[x][y],cost1[x][y]+dp1[x-k][y]+dp1[x][y+i-k]);
                else dp1[x][y] = cost1[x][y]+dp1[x-k][y]+dp1[x][y+i-k];
                if (dp2[x][y]) dp2[x][y] = max(dp2[x][y],cost2[x][y]+dp2[x-k][y]+dp2[x][y+i-k]);
                else dp2[x][y] = cost2[x][y]+dp2[x-k][y]+dp2[x][y+i-k];
            }
        }
    }
    int mi = inf, mx = 0;
    n >>= 1;
    for(int j = 0; j <= n; j++) {
        mi = min(mi,dp1[n+j][j+1]);
    }
    for(int j = 0; j <= n; j++) {
        mx = max(mx,dp2[n+j][j+1]);
    }
    cout << mi << endl << mx << endl;
}
```
