# AC自动机（二次加强版）
题目描述<br>
给你一个文本串 S 和n个模式串T_(1…n) ，<br>

请你分别求出每个模式串T_i 在 S 中出现的次数。<br>

输入格式<br>
第一行包含一个正整数 n 表示模式串的个数。<br>

接下来n行，第 i 行包含一个由小写英文字母构成的字符串 T_i<br>

最后一行包含一个由小写英文字母构成的字符串 S。<br>

输出格式<br>
输出包含 n 行，其中第i行包含一个非负整数表示 T_i <br>

在 S 中出现的次数。<br>
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e6+5;
 
struct Aho_Corasock_Automaton {
	struct node {
		int fail;  // 失配指针
		int son[26];  // 子节点的位置
		int in;  // 该节点的入度 
		int ans;  // 出现次数 
	}Trie[maxn];
	int cnt = 0; // Trie指针
	int ends[maxn];  // 记录该模式串是以哪个节点为结尾
	void insert(char *s, int num) {
		int len = strlen(s);
		int now = 0;  // Trie当前指针 
		for (int i = 0; i < len; ++i) {
			if (Trie[now].son[s[i]-'a'] == 0) { // 如果没有这个子节点 
				Trie[now].son[s[i]-'a'] = ++cnt;  // 构造该节点 
			}
			now = Trie[now].son[s[i]-'a']; 
		}
		ends[num] = now;
	}
	void get_fail() {  // 构造fail指针 
		queue<int> que;
		for (int i = 0; i < 26; ++i) {  // 先提前构造第二层 
			if (Trie[0].son[i] != 0) {  // 如果存在该节点 
				Trie[Trie[0].son[i]].fail = 0;  // fail指向root节点 
				que.push(Trie[0].son[i]);  // 加入队列 
			}
		}
		while (!que.empty()) {  // bfs求fail指针 
			int u = que.front(); que.pop();
			for (int i = 0; i < 26; ++i) {
				if (Trie[u].son[i] != 0) {  // 如果存在该子节点 
					// 子节点的fail指针指向当前节点的fail指针指向内容相同的子节点 
					Trie[Trie[u].son[i]].fail = Trie[Trie[u].fail].son[i];
					que.push(Trie[u].son[i]);  // 加入队列 
				}
				else {  // 如果不存在这个子节点 
					// 当前节点的该子节点指向当前节点的fail指针指向的止隔子节点 
					Trie[u].son[i] = Trie[Trie[u].fail].son[i];
				}
			}
		}
	}
	void topu() {
		queue<int> que;
		for (int i = 1; i <= cnt; ++i) {
			Trie[Trie[i].fail].in++; 
		}
		for (int i = 1; i <= cnt; ++i) {
			if (Trie[i].in == 0) {
				que.push(i);  // 入度为0的加入队列 
			}
		}
		while (!que.empty()) {
			int u = que.front(); que.pop();
			Trie[Trie[u].fail].ans += Trie[u].ans;
			Trie[Trie[u].fail].in--;
			if (Trie[Trie[u].fail].in == 0)
				que.push(Trie[u].fail); 
		}
	}
	void query(char *s) {
		int len = strlen(s);
		int now = 0, ans = 0;  // 当前Trie指针，答案ans
		for (int i = 0; i < len; ++i) {
			now = Trie[now].son[s[i]-'a'];
			Trie[now].ans++;  // 出现次数加一 
		}
	}
}AC;
char t[maxn], s[maxn];
int main() {
	int n; scanf("%d",&n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s",t);
		AC.insert(t,i);		
	}
	AC.Trie[0].fail = 0;
	AC.get_fail();
	scanf("%s",s);
	AC.query(s);
	AC.topu();
	for (int i = 1; i <= n; ++i) {
		printf("%d\n",AC.Trie[AC.ends[i]].ans);
	}
	return 0;
}
```
