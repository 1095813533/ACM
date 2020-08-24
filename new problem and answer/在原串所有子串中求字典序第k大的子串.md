# 在原串所有子串中求字典序第k大的子串
输入格式<br>
第一行是一个仅由小写英文字母构成的字符串s<br>

第二行为两个整数t和k,t为0则表示不同位置的相同子串算作一个,t为1则表示不同位置的相同子串算作多个。k的意义见题目描述。<br>

输出格式<br>
输出数据仅有一行,该行有一个字符串,为第k小的子串。若子串数目不足k个,则输出-1。<br>
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
char s[maxn];
int a[maxn], c[maxn], size[maxn], sum[maxn], k, t;
struct SuffixAutoMaton {
    int last, cnt;
    int ch[maxn*2][26], fa[maxn*2], len[maxn*2];
    void ins(int c) {
        int p = last, np = ++cnt;
        last = np; len[np] = len[p]+1;
        for (;p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
        if (!p) fa[np] = 1;
        else {
            int q = ch[p][c];
            if (len[p]+1 == len[q]) fa[np] = q;
            else {
                int nq = ++cnt;
                len[nq] = len[p]+1;
                memcpy(ch[nq],ch[q],sizeof(ch[q]));
                fa[nq] = fa[q]; fa[q] = fa[np] = nq;
                for (; ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
            }
        }
        size[np] = 1;
    }
    void build() {
        scanf("%s",s+1);
        int lens = strlen(s+1);
        last = cnt = 1;
        for (int i = 1; i <= lens; i++) ins(s[i]-'a');
    }
    void work() {
        for (int i = 1; i <= cnt; i++) c[len[i]]++;
        for (int i = 1; i <= cnt; i++) c[i] += c[i-1];
        for (int i = 1; i <= cnt; i++) a[c[len[i]]--] = i;
        for (int i = cnt; i; i--) {
            int p = a[i];
            if (t == 1) size[fa[p]] += size[p];
            else size[p] = 1;
        }
        size[1] = 0;
        for (int i = cnt; i; i--) {
        	sum[a[i]] = size[a[i]];
        	for (int j = 0; j < 26; j++) {
				if (ch[a[i]][j]) sum[a[i]] += sum[ch[a[i]][j]];
			}
		}
    }
    void solve() {
    	if (k > sum[1]) {
    		puts("-1");
    		return;
		}
		int now = 1;
		k -= size[now];
		while (k > 0) {
			int p = 0;
			while (k > sum[ch[now][p]]) {
				k -= sum[ch[now][p]];
				p++;
			}
			now = ch[now][p];
			putchar('a'+p);
			k -= size[now];
		}
		return;
	}
}sam;
int main() {
    sam.build();
    scanf("%d%d",&t,&k);
    sam.work();
    sam.solve();
    return 0;
}
```
