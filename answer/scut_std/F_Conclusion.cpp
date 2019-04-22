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

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        int n; scanf("%d", &n);
        printf("%.2f\n", DB(n*2-1));
    }
    return 0;
}
