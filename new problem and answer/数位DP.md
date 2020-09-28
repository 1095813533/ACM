# 数位DP
题目描述<br>
杭州人称那些傻乎乎粘嗒嗒的人为62（音：laoer）。<br>
杭州交通管理局经常会扩充一些的士车牌照，新近出来一个好消息，以后上牌照，不再含有不吉利的数字了，这样一来，就可以消除个别的士司机和乘客的心理障碍，更安全地服务大众。<br>
不吉利的数字为所有含有4或62的号码。例如：<br>
62315 73418 88914<br>
都属于不吉利号码。但是，61152虽然含有6和2，但不是62连号，所以不属于不吉利数字之列。<br>
你的任务是，对于每次给出的一个牌照区间号，推断出交管局今次又要实际上给多少辆新的士车上牌照了。<br>

输入格式<br>
输入的都是整数对n、m（0<n≤m<1000000），如果遇到都是0的整数对，则输入结束。<br>

输出格式<br>
对于每个整数对，输出一个不含有不吉利数字的统计个数，该数值占一行位置。<br>
```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[15][15], d[15];
void init() {
    dp[0][0] = 1;
    for (int i = 1; i <= 7; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                if (j != 4 && !(j == 6 && k == 2)) {
                    dp[i][j] += dp[i-1][k];
                }
            }
        }
    }
}
int solve(int n) {
    int ans = 0, len = 0;
    while (n) {
        ++len;
        d[len] = n%10;
        n /= 10;
    }
    d[len+1] = 0;
    for (int i = len; i >= 1; i--) {
        for (int j = 0; j < d[i]; j++) {
            if (d[i+1] != 6 || j != 2) {
                ans += dp[i][j];
            }
        }
        if (d[i] == 4 || (d[i+1] == 6 && d[i] == 2)) {
            break;
        }
    }
    return ans;
}
int main() {
    init();
    int l, r;
    while (cin >> l >> r && (l||r)) {
        cout << solve(r+1)-solve(l) << endl;
    }
    return 0;
}
```

题目描述<br>
求区间包含“13”这个子串而且能整除13的个数<br>

输入格式<br>
输入n，求区间1-n中包含“13”这个子串而且能整除13的个数<br>
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 15;
int dp[maxn][maxn][maxn][maxn];
// dp[i][j][state][r] i表示位数，j表示开头，state是0或1表示是否已经出现了"13"这个子串
int base[maxn];
void init() {
    base[0] = 1;
    for (int i = 1; i <= 10; i++) {
        base[i] = base[i-1]*10;
    }
    for (int i = 0; i <= 9; i++) {
        dp[1][i][0][i] = 1;
    }
    for (int i = 2; i <= 10; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int x = 0; x <= 9; x++) {
                int t = base[i-1]*j % 13;
                for (int r = 0; r <= 12; r++) {
                    dp[i][j][1][(r+t)%13] += dp[i-1][x][1][r];
                    if (j == 1 && x == 3) {  // 出现了13这个子串
                        dp[i][j][1][(r+t)%13] += dp[i-1][x][0][r];
                    }
                    else {
                        dp[i][j][0][(r+t)%13] += dp[i-1][x][0][r];
                    }
                }
            }
        }
    }
}
int calc(int n) {
    n++;
    int digit[15] = {0};
    int lenstr = 0;
    while (n/10 > 0) {
        digit[++lenstr] = n%10;
        n /= 10;
    }
    digit[++lenstr] = n%10;
    int ans = 0;
    int mod = 0;
    bool flag = false;
    for (int i = lenstr; i >= 1; i--) {
        for (int j = 0; j <= digit[i]-1; j++) {
            ans += dp[i][j][1][(13-mod)%13];
            if (flag || j == 3 && digit[i+1] == 1) {
                ans += dp[i][j][0][(13-mod)%13];
            }
        }
        if (digit[i] == 3 && digit[i+1] == 1) {
            flag = true;
        }
        mod = (mod+digit[i]*base[i-1])%13;
    }
    return ans;
}
int main() {
    int n;
    init();
    while (~scanf("%d",&n)) {
        printf("%d\n",calc(n));
    }
    return 0;
}

```
