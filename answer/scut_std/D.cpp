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

const int maxn = 1e5;
const int maxa = 1e5;

const LL P = ((7 * 17) << 23) + 1, gg = 3;
const int maxL = 1<<17;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }
LL A[maxL+5], B[maxL+5];
void NTT(LL *a, int len, int type) {
    int i, j, k, l;
    for(i=1, j=len>>1; i<len-1; ++i) {
        if(i<j) swap(a[i], a[j]);
        k = len>>1;
        while(j>=k)
            j -= k, k >>= 1;
        j += k;
    }
    LL var, step, u, v;
    for(l=2; l<=len; l<<=1) {
        step = PowMod(gg, (P-1)/l);
        for(k=0; k<len; k+=l) {
            var = 1;
            for(i=k; i<k+l/2; ++i) {
                u = a[i], v = var*a[i+l/2] % P;
                a[i] = (u+v) % P;
                a[i+l/2] = (u-v+P) % P;
                var = var*step % P;
            }
        }
    }
    if(type == -1) {
        for(i=1; i<len/2; ++i) swap(a[i], a[len-i]);
        LL inv = PowMod(len, P-2);
        for(i=0; i<len; ++i) a[i] = a[i]*inv % P;
    }
}

int n, ai[maxn+5];
LL inv[maxn+5];
LL ans = 0;

vector<int> G[maxn+5];
int que[maxn+5], fa[maxn+5], sz[maxn+5], msz[maxn+5];
bool ban[maxn+5];
int FindRoot(int x) {
    int s = 1, t = 1;
    que[1] = x, fa[x] = 0;
    while(s <= t) {
        x = que[s++], sz[x] = 1, msz[x] = 0;
        for(auto v : G[x])
            if(!ban[v] && v!=fa[x])
                que[++t] = v, fa[v] = x;
    }
    for(int i = t; i >= 1; --i) {
        x = que[i], msz[x] = max(msz[x], t-sz[x]);
        if((msz[x]<<1) <= t) return x;
        sz[fa[x]] += sz[x], msz[fa[x]] = max(msz[fa[x]], sz[x]);
    }
    assert(false);
    return 0;
}

int id[maxn+5];
vector<int> cnt[maxn+5], val[maxn+5];
void Mul(int a, int b) {
    int l1 = cnt[a].size();
    int l2 = val[b].size();
    int len = 1;
    while(len < l1+l2-1) len <<= 1;
    assert(len<=maxL);
    REP(i,0,l1-1) A[i] = cnt[a][i];
    REP(i,l1,len-1) A[i] = 0;
    REP(i,0,l2-1) B[i] = val[b][i];
    REP(i,l2,len-1) B[i] = 0;
    NTT(A,len,1), NTT(B,len,1);
    REP(i,0,len-1) A[i] = A[i]*B[i] % P;
    NTT(A,len,-1);
    REP(i,1,len-1) ans = (ans + A[i] * inv[i]) % P;
}

void dfs(int x, int p, int d, int sum, vector<int> &c, vector<int> &v) {
    sum = (sum + ai[x]) % P;
    for(auto y : G[x]) if(y!=p && !ban[y]) {
        dfs(y, x, d+1, sum, c, v);
    }
    if(d+1 > c.size()) {
        c.resize(d+1);
        v.resize(d+1);
    }
    ++c[d], v[d] = (v[d]+sum) % P;
}

void Solve(int x) {
    x = FindRoot(x);
    int tot = 1;
    cnt[0].resize(1), val[0].resize(1);
    cnt[0][0] = 1, val[0][0] = ai[x];
    id[0] = 0;
    for(auto y : G[x]) if(!ban[y]) {
        cnt[tot].clear(), val[tot].clear();
        dfs(y, x, 1, 0, cnt[tot], val[tot]);
        id[tot] = tot;
        ++tot;
    }
    sort(id, id+tot, [&](const int &a, const int &b){ return cnt[a].size() < cnt[b].size(); });
    for(int i = 0; i+1 < tot; ++i) {
        Mul(id[i], id[i+1]);
        Mul(id[i+1], id[i]);
        for(int k = 0; k < cnt[id[i+1]].size(); ++k)
            val[id[i+1]][k] = (val[id[i+1]][k] + LL(ai[x])*cnt[id[i+1]][k]) % P;
        for(int k = 0; k < cnt[id[i]].size(); ++k) {
            cnt[id[i+1]][k] = (cnt[id[i+1]][k] + cnt[id[i]][k]) % P;
            val[id[i+1]][k] = (val[id[i+1]][k] + val[id[i]][k]) % P;
        }
        cnt[id[i]].clear(), val[id[i]].clear();
    }
    cnt[id[tot-1]].clear(), val[id[tot-1]].clear();
    ban[x] = 1;
    for(auto y : G[x]) if(!ban[y]) Solve(y);
}

int main() {
    inv[1] = 1;
    REP(i,2,maxn) inv[i] = (P - P/i) * inv[P%i] % P;
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", ai+i);
    for(int i = 1, u,v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v);
        G[v].PB(u);
    }
    Solve(1);
    ans = ans*2 % P;
    printf("%lld\n", ans);
    return 0;
}
