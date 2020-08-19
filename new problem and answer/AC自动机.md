# AC自动机
题目描述<br>
给定n个模式串和1个文本串，求有多少个模式串在文本串里出现过<br>
### 输入格式
第一行一个n，表示模式串个数；<br>
下面n行每行一个模式串；<br>
下面一行一个文本串。<br>
### 输出格式
一个数表示答案<br>
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
struct Aho_Corasock_Automaton {
	struct node {
		int fail;  // 失配指针
		int son[26];  // 子节点的位置
		int num;  // 标记有几个单词以这个节点结尾 
	}Trie[maxn];
	int cnt = 0; // Trie指针
	void insert(char *s) {
		int len = strlen(s);
		int now = 0;  // Trie当前指针 
		for (int i = 0; i < len; ++i) {
			if (Trie[now].son[s[i]-'a'] == 0) { // 如果没有这个子节点 
				Trie[now].son[s[i]-'a'] = ++cnt;  // 构造该节点 
			}
			now = Trie[now].son[s[i]-'a']; 
		}
		Trie[now].num += 1;  // 标记单词结尾 
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
	int query(char *s) {  // 匹配共有几个模式串出现过 
		int len = strlen(s);
		int now = 0, ans = 0;  // Trie当前的指针，答案ans
		for (int i = 0; i < len; ++i) {
			now = Trie[now].son[s[i]-'a']; 
			for (int t = now; t != 0 && Trie[now].num != -1; t = Trie[t].fail) {
				ans += Trie[t].num;
				Trie[t].num = -1;  // 标记该节点已经匹配过 
			}
		}
		return ans;
	} 
}AC;
char t[maxn], s[maxn];
int main() {
	int n; scanf("%d",&n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s",t);
		AC.insert(t);		
	}
	AC.get_fail();
	scanf("%s",s);
	int ans = AC.query(s);
	printf("%d\n",ans);
	return 0;
}
```
