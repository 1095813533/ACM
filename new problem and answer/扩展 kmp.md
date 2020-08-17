# 扩展 kmp
### 题目描述<br>
有两个字符串a,b,要求输出b与a的每一个后缀的最长公共前缀<br>
### 输入格式<br>
两行,分别为两个字符串a,b<br>
### 输出格式<br>
共两行<br>
第一行有lenb个数,为b的next数组<br>
第二行有lena个数,即答案<br>
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int q, nxt[maxn], extend[maxn];
string a, b;
void getnxt() {
    nxt[0] = b.size();
    int now = 0;
    while (b[now]==b[1+now] && now+1<b.size()) now++;
    nxt[1] = now;
    int p = 1;
    for (int i = 2; i < b.size(); i++) {
        if (i+nxt[i-p] < nxt[p]+p) nxt[i] = nxt[i-p];
        else {
            int now = nxt[p]+p-i;
            now = max(now,0);
            while (b[now]==b[i+now] && i+now<b.size()) now++;
            nxt[i] = now;
            p = i;
        }
    }
}
void exkmp() {
    getnxt();
    int now = 0;
    while (a[now]==b[now] && now < min(a.size(),b.size())) now++;
    extend[0] = now;
    int p = 0;
    for (int i = 1; i < a.size(); i++) {
        if (i+nxt[i-p] < extend[p]+p) extend[i] = nxt[i-p];
        else {
            int now = extend[p]+p-i;
            now = max(now,0);
            while (b[now]==a[i+now] && now<b.size() && now+i<a.size()) now++;
            extend[i] = now;
            p = i;
        }
    }
}

int main() {
    cin >> a >> b;
    exkmp();
    int len = b.size();
    printf("%d",nxt[0]);
    for (int i = 1; i < len; i++) printf(" %d",nxt[i]);
    printf("\n");

    len = a.size();
    printf("%d",extend[0]);
    for (int i = 1; i < len; i++) printf(" %d",extend[i]);
    printf("\n");
    return 0;
}
```
