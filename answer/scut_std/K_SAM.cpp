#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef double DB;

const int maxn = 1000, c_size = 26;

struct State {
    int val;
    LL sum, occ;
    int par, go[c_size];
    void init() { val = 0, sum = 0, occ = 0, par = -1, mem(go,-1); }
}que[maxn*2+5];
int root, last;
int tot;

void Extend(int w) {
    int p = last, np = tot++;
    que[np].init();
    que[np].val = que[p].val+1;
    que[np].occ = 1;
    while(p!=-1 && que[p].go[w]==-1)
        que[p].go[w] = np, p = que[p].par;
    if(p == -1) que[np].par = root;
    else {
        int q = que[p].go[w];
        if(que[p].val+1 == que[q].val) que[np].par = q;
        else {
            int nq = tot++;
            que[nq] = que[q];
            que[nq].val = que[p].val+1;
            que[nq].occ = 0;
            que[np].par = que[q].par = nq;
            while(p!=-1 && que[p].go[w]==q)
                que[p].go[w] = nq, p = que[p].par;
        }
    }
    last = np;
}


char str[maxn+5];
LL f[maxn+5];
int cont[maxn+5], S[maxn*2+5];

int main() {
    scanf("%s", str+1);
    int n = strlen(str+1);
    for(int kk = 1; kk < n; ++kk) {
        root = last = 0;
        tot = 1, que[0].init();
        for(int i = 1; i <= kk; ++i) Extend(str[i]-'a');
        for(int i=0; i<=kk; ++i) cont[i] = 0;
        for(int i=0; i<tot; ++i) ++cont[que[i].val];
        for(int i=1; i<=kk; ++i) cont[i] += cont[i-1];
        for(int i=tot-1; i>=1; --i) S[--cont[que[i].val]] = i;
        for(int i = tot-1; i >= 1; --i) {
            int x = S[i];
            que[que[x].par].occ += que[x].occ;
        }
        for(int i = 1; i < tot; ++i) {
            int x = S[i];
            que[x].sum = que[que[x].par].sum;
            que[x].sum += LL(que[x].val-que[que[x].par].val) * que[x].occ;
        }
        int p = root;
        int now = 0;
        f[kk] = 0;
        for(int i = kk+1; i <= n; ++i) {
            int w = str[i]-'a';
            if(que[p].go[w] != -1) {
                p = que[p].go[w];
                ++now;
            }
            else {
                while(p!=-1 && que[p].go[w]==-1) p = que[p].par;
                if(p == -1) p = root, now = 0;
                else {
                    now = que[p].val+1;
                    p = que[p].go[w];
                }
            }
            if(now>0) {
                f[kk] += que[que[p].par].sum;
                f[kk] += LL(now - que[que[p].par].val) * que[p].occ;
            }
        }
    }
    int _; scanf("%d", &_);
    while(_--) {
        int kk; scanf("%d", &kk);
        printf("%lld\n", f[kk]);
    }
    return 0;
}
