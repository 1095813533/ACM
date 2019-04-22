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
typedef unsigned long long ULL;
typedef double DB;

const int maxn = 1000;

typedef unsigned long long Key;
const ULL base = 19260817;

ULL pw[maxn+5], ha[maxn+5];

int n;
char s[maxn+5];
unordered_map<Key,int> MapL[maxn+5], MapR[maxn+5];
LL f[maxn+5];

inline Key GetKey(int l, int r) {
    assert(1<=l && l<=r && r<=n);
    Key tmp1 = ha[r] - ha[l-1]*pw[r-l+1];
    return tmp1;
}

int main() {
    pw[0] = 1;
    REP(i,1,maxn) {
        pw[i] = pw[i-1]*base;
    }
    scanf("%s", s+1);
    n = strlen(s+1);
    REP(i,1,n) {
        ha[i] = ha[i-1] * base + ULL(s[i]-'a');
    }
    for(int i = 1; i <= n; ++i) {
        for(int k = i; k <= n; ++k) {
            ++MapR[k-i+1][ GetKey(i,k) ];
        }
    }
    for(int k = 1; k < n; ++k) {
        f[k] = f[k-1];
        for(int j = k; j <= n; ++j) {
            Key tmp = GetKey(k,j);
            if(MapL[j-k+1].find(tmp) != MapL[j-k+1].end()) {
                f[k] -= MapL[j-k+1][tmp];
            }
            --MapR[j-k+1][tmp];
        }
        for(int i = 1; i <= k; ++i) {
            Key tmp = GetKey(i,k);
            if(MapR[k-i+1].find(tmp) != MapR[k-i+1].end()) {
                f[k] += MapR[k-i+1][tmp];
            }
            ++MapL[k-i+1][tmp];
        }
    }
    int _; scanf("%d", &_);
    while(_--) {
        int kk; scanf("%d", &kk);
        printf("%lld\n", f[kk]);
    }
    return 0;
}
