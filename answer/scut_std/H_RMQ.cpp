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
const int Step = 17;
const int P = 1e9+7;

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

int n, ai[maxn+5];
int st[maxn+5][Step+2];
int len[maxn+5];

int Que(int l, int r) {
    int k = len[r-l+1];
    return Gcd( st[l][k], st[r-(1<<k)+1][k] );
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", ai+i), st[i][0] = ai[i];
    for(int k = 1; (1<<k) <= n; ++k) {
        for(int i = 1; i+(1<<k)-1 <= n; ++i) {
            st[i][k] = Gcd(st[i][k-1], st[i+(1<<(k-1))][k-1]);
        }
    }
    for(int i = 1; i <= n; ++i) {
        len[i] = len[i-1];
        if((1<<(len[i]+1)) < i) ++len[i];
    }
    LL ans = 0;
    REP(i,1,n) {
        int now = 0;
        for(int k = i, nx; k <= n; k = nx+1) {
            now = Gcd(now, ai[k]);
            int l = k+1, r = n;
            nx = k;
            while(l<=r) {
                int mid = (l+r)>>1;
                int tmp = Que(k,mid);
                if(tmp%now==0) nx = mid, l = mid+1;
                else r = mid-1;
            }
            ans = (ans + LL(nx-k+1) * now) % P;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
