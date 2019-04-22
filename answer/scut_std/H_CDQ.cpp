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

const int maxn = 5e5;
const int maxV = 1e9;
const int P = 1e9+7;

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

map<int,int> s1, s2;
int n, ai[maxn+5];
LL ans = 0;

inline void Add(LL &a, LL b) { a+=b; if(a>=P) a-=P; }

void Solve(int l, int r) {
    if(l==r) { Add(ans, ai[l]); return; }
    int mid = (l+r)>>1;
    s1.clear();
    s2.clear();

    int now = 0;
    for(int i = mid; i >= l; --i) {
        now = Gcd(now, ai[i]);
        ++s1[now];
    }

    now = 0;
    for(int i = mid+1; i <= r; ++i) {
        now = Gcd(now, ai[i]);
        ++s2[now];
    }

    for(auto pp : s1) {
        for(auto qq : s2) {
            Add(ans, Gcd(pp.fi, qq.fi) * pp.se % P * qq.se % P);
        }
    }

    Solve(l, mid);
    Solve(mid+1, r);
}

int main() {
    scanf("%d", &n);
    assert(1<=n && n<=maxn);
    REP(i,1,n) scanf("%d", ai+i);
    Solve(1,n);
    printf("%lld\n", ans);
    return 0;
}
