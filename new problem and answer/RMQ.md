# RMQ
### 题目背景
这是一道ST表经典题——静态区间最大值<br>
请注意最大数据时限只有0.8s，数据强度不低，请务必保证你的每次查询复杂度为 O(1)<br>
### 题目描述
给定一个长度为N的数列，和M次询问，求出每一次询问的区间内数字的最大值。<br>
### 输入格式
第一行包含两个整数 N, M,分别表示数列的长度和询问的个数。<br>
第二行包含 N个整数（记为a^i），依次表示数列的第i项。<br>
接下来 M行，每行包含两个整数 l_i, r_i，表示查询的区间为[l_i,r_i]<br>
### 输出格式
输出包含M行，每行一个整数，依次表示每一次询问的结果。<br>
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int d[maxn][64];
vector<int> A;
void RMQ_init(const vector<int> & A) {
    int n = A.size();
    for (int i = 0; i < n; i++) d[i][0] = A[i];
    for (int j = 1; (1<<j) <= n; j++)
        for (int i = 0; i + (1<<j)-1 < n; i++)
            d[i][j] = max(d[i][j-1], d[i + (1<<(j-1))][j-1]);
}
int RMQ(int L, int R) {
    int k = 0;
    while ((1<<(k+1)) <= R-L+1) k++;
    return max(d[L][k], d[R-(1<<k)+1][k]);
}
int main() {
    int n, m; scanf("%d%d",&n,&m);
    for (int i = 1; i <= n; i++) {
        int x; scanf("%d",&x);
        A.push_back(x);
    }
    RMQ_init(A);
    while (m--) {
        int l, r; scanf("%d%d",&l,&r);
        int ans = RMQ(l-1,r-1);
        printf("%d\n",ans);
    }
	return 0;
}
```
