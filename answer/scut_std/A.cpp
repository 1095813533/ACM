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

const int maxT = 50;
const int P = 1e9+7;
const LL MaxInt = (1LL<<32) - 1;

LL Fac[100], InvFac[100];
LL C[100][100];
int cnt[20];

LL lim;
LL dfs(LL now, int pt) {
    if(pt<=1) {
        int s = 0;
        LL ret = 1;
        REP(i,2,9) {
            s += cnt[i];
            ret = ret * C[s][cnt[i]] % P;
        }
        if(s==0) return 0LL;
        return ret;
    }
    LL ret = 0;
    cnt[pt] = 0;
    while(now <= lim) {
        ret = (ret + dfs(now, pt-1)) % P;
        now *= pt, ++cnt[pt];
    }
    return ret;
}

int main() {
    C[0][0] = 1;
    for(int i = 1; i <= 50; ++i) {
        C[i][0] = C[i][i] = 1;
        for(int k = 1; k < i; ++k) C[i][k] = (C[i-1][k] + C[i-1][k-1]) % P;
    }
    int _; scanf("%d", &_);
    while(_--) {
        LL a,b;
        scanf("%lld%lld", &a, &b);
        lim = b;
        LL sb = dfs(1,9);
        lim = a-1;
        LL sa = dfs(1,9);
        LL ans = (sb - sa + P) % P;
        printf("%lld\n", ans);
    }
    return 0;
}
