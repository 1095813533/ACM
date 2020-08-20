# AC自动机（加强版）
题目描述<br>
有N个由小写字母组成的模式串以及一个文本串T。每个模式串可能会在文本串中出现多次。你需要找出哪些模式串在文本串T中出现的次数最多。<br>

### 输入格式<br>
输入含多组数据。<br>
每组数据的第一行为一个正整数N，表示共有N个模式串，1≤N≤150。<br>
接下去N行，每行一个长度小于等于70的模式串。下一行是一个长度小于等于10^6的文本串T。<br>
输入结束标志为N=0。<br>
### 输出格式<br>
对于每组数据，第一行输出模式串最多出现的次数，接下去若干行每行输出一个出现次数最多的模式串，按输入顺序排列。<br>
```
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
struct word {
	string str;
	int num;  // 出现次数
	int pos;  // 出现位置 
}words[maxn];
bool cmp(word x, word y) {
	if (x.num == y.num) return x.pos < y.pos;
	return x.num > y.num;
}
struct Aho_Corasock_Automaton {
	struct node {
		int fail;  // 失配指针
		int son[26];  // 子节点的位置
		int end;  // 标记以该节点结尾的模式串的编号 
	}Trie[maxn];
	int cnt = 0; // Trie指针
	void clear(int x) {  // 清空节点信息 
		memset(Trie[x].son,0,sizeof(Trie[x].son));
		Trie[x].fail = Trie[x].end = 0;
	}
	void insert(char *s, int num) {
		int len = strlen(s);
		int now = 0;  // Trie当前指针 
		for (int i = 0; i < len; ++i) {
			if (Trie[now].son[s[i]-'a'] == 0) { // 如果没有这个子节点 
				Trie[now].son[s[i]-'a'] = ++cnt;  // 构造该节点 
				clear(cnt);  // 清空新构造的节点里面的信息 
			}
			now = Trie[now].son[s[i]-'a']; 
		}
		Trie[now].end = num;  // 标记以该节点结尾是哪个模式串 
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
	void query(char *s) {
		int len = strlen(s);
		int now = 0, ans = 0;  // 当前Trie指针，答案ans
		for (int i = 0; i < len; ++i) {
			now = Trie[now].son[s[i]-'a'];
			for (int t = now; t != 0; t = Trie[t].fail) {  // 暴力搜索 
				words[Trie[t].end].num++;  // 以该节点为结尾的模式串次数加一 
			}
		}
	}
}AC;
char t[maxn], s[maxn];
int main() {
	int n;
	while (scanf("%d",&n) != EOF && n) {
		AC.cnt = 0, AC.clear(0);
		for (int i = 1; i <= n; ++i) {
			cin >> words[i].str;
			strcpy(t,words[i].str.c_str());
			words[i].pos = i;
			words[i].num = 0;
			AC.insert(t,i);		
		}
		AC.Trie[0].fail = 0;
		AC.get_fail();
		scanf("%s",s);
		AC.query(s);
		sort(words+1,words+1+n,cmp);
		printf("%d\n%s\n",words[1].num,words[1].str.c_str());
		for (int i = 2; i <= n; ++i) {
			if (words[i].num == words[1].num) {
				printf("%s\n",words[i].str.c_str());
			}
			else break;
		}
	}
	return 0;
}
```
