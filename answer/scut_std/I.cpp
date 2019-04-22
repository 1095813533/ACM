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
const int maxV = 1e6;

int n, ai[maxn+5];

int main() {
    scanf("%d", &n);
    LL ans = 0;
    REP(i,1,n) scanf("%d", ai+i);
    REP(i,2,n) if(ai[i]>ai[i-1]) ans += ai[i]-ai[i-1];
    printf("%lld\n", ans);
    return 0;
}
