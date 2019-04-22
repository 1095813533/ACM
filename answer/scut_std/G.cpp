#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
typedef long long LL;
typedef double DB;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int maxM = 2e4;
const int maxnode = maxn<<2;

int n, m;
int DFN = 0, dfn[maxn+5], fa[maxn+5];
vector<int> vec[maxn+5];
int L1[maxn+5], R1[maxn+5], L2[maxn+5], R2[maxn+5];
int pt[maxM+5], dd[maxM+5];
int cnt[maxM+5];
bool dead[maxM+5];
vector<int> G[maxn+5];
priority_queue<pair<int,int>> q;

int tr[maxnode+5], lz[maxnode+5];
set<int> cov[maxnode+5];

void dfs(int x, int p, int dis) {
    fa[x] = p;
    vec[dis].PB(x);
    for(auto y : G[x]) if(y!=p) {
        dfs(y,x, dis+1);
    }
}

void dfs2(int x, int p) {
    L1[x] = L2[x] = n+1;
    R1[x] = R2[x] = 0;
    for(auto y : G[x]) if(y!=p) {
        dfs2(y,x);
        L1[x] = min(L1[x], dfn[y]);
        R1[x] = max(R1[x], dfn[y]);
        L2[x] = min(L2[x], L1[y]);
        R2[x] = max(R2[x], R1[y]);
    }
}

void reBuild(int x, int l, int r) {
    tr[x] = lz[x] = 0;
    assert(cov[x].size()==0);
    if(l<r) {
        reBuild(lson, l, mid);
        reBuild(rson, mid+1, r);
    }
}

void PushDown(int x) {
    lz[lson]+=lz[x], tr[lson]+=lz[x];
    lz[rson]+=lz[x], tr[rson]+=lz[x];
    lz[x] = 0;
}

void Upd(int x, int l, int r, int v) {
    if(tr[x]>1) return;
    if(cov[x].size()) v = *cov[x].begin();
    if(l==r) {
        if(tr[x]==0) tr[x] = n+10;
        else if(tr[x]==1) {
            assert(1<=v && v<=n);
            ++cnt[v];
            q.push( pair<int,int>(cnt[v],v) );
            tr[x] = n+10;
        }
    }
    else {
        PushDown(x);
        Upd(lson, l, mid, v);
        Upd(rson, mid+1, r, v);
        tr[x] = min(tr[lson], tr[rson]);
    }
}

void Add(int x, int l, int r, int ll, int rr, int v) {
    if(ll<=l && r<=rr) {
        ++tr[x], ++lz[x];
        cov[x].insert(v);
    }
    else {
        PushDown(x);
        if(ll<=mid) Add(lson, l, mid, ll, rr, v);
        if(mid<rr) Add(rson, mid+1, r, ll, rr, v);
        tr[x] = min(tr[lson], tr[rson]);
    }
}

void Sub(int x, int l, int r, int ll, int rr, int v) {
    if(ll<=l && r<=rr) {
        --tr[x], --lz[x];
        auto it = cov[x].find(v);
        assert(it != cov[x].end());
        cov[x].erase(it);
    }
    else {
        PushDown(x);
        if(ll<=mid) Sub(lson,l, mid, ll, rr, v);
        if(mid<rr) Sub(rson, mid+1, r, ll, rr, v);
        tr[x] = min(tr[lson], tr[rson]) + lz[x];
    }
}

void Mod(int l, int r, int v, int o) {
    if(l>r) return;
    if(o==1) Add(1, 1, n, l, r, v);
    else Sub(1, 1, n, l, r, v);
}

void Draw(int id, int o) {
    assert(o==1 || o==-1);
    int x = pt[id], kk = dd[id];
    if(kk==0) Mod(dfn[x], dfn[x], id, o);
    else if(kk==1) {
        Mod(L1[x], R1[x], id, o);
        Mod(dfn[x], dfn[x], id, o);
        if(fa[x]!=0) Mod(dfn[fa[x]], dfn[fa[x]], id, o);
    }
    else {
        Mod(L1[x], R1[x], id, o);
        Mod(L2[x], R2[x], id, o);
        if(fa[x]!=0) {
            int y = fa[x];
            Mod(L1[y], R1[y], id, o);
            Mod(dfn[y], dfn[y], id, o);
            if(fa[y]!=0) Mod(dfn[fa[y]], dfn[fa[y]], id, o);
        }
        else Mod(dfn[x], dfn[x], id, o);
    }
}

priority_queue<int> q2;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u,v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v); G[v].PB(u);
    }
    dfs(1,0,1);
    REP(i,1,n) {
        for(auto x : vec[i]) dfn[x] = ++DFN;
    }
    dfs2(1,0);
    REP(i,1,m) {
        scanf("%d%d", pt+i, dd+i);
        Draw(i,1);
    }
    REP(i,1,m) q.push( pair<int,int>(0,i) );
    Upd(1, 1, n, -1);
    int ans = n+10;
    REP(i,1,m) {
        while(dead[q.top().se] || cnt[q.top().se]!=q.top().fi) q.pop();
        ans = min(ans, q.top().fi);
        int x = q.top().se; q.pop();
        assert(1<=x && x<=m);
        dead[x] = 1;
        Draw(x,-1);
        Upd(1, 1, n, -1);
    }

    reBuild(1,1,n);
    while(!q.empty()) q.pop();
    REP(i,1,m) cnt[i] = 0, dead[i] = 0, Draw(i,1), q.push( pair<int,int>(0,i) );
    Upd(1, 1, n, -1);
    int gao = 0;
    REP(i,1,m) {
        while(gao < m) {
            while(dead[q.top().se] || cnt[q.top().se]!=q.top().fi) q.pop();
            if(q.top().fi < ans) break;
            q2.push( -q.top().se );
            dead[q.top().se] = 1;
            q.pop(); ++gao;
        }
        int x = -q2.top();
        q2.pop();
        Draw(x,-1);
        Upd(1, 1, n, -1);
    }

    printf("%d\n", ans);
    int tmp_sum = 0;
    REP(i,1,m) printf("%d\n", cnt[i]), tmp_sum += cnt[i];

    return 0;
}
