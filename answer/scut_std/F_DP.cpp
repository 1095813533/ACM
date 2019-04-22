// CC!
#include<bits/stdc++.h>

using namespace std;

typedef double DB;

const int maxn = 5000;

DB f[maxn+5][maxn+5];
bool vi[maxn+5][maxn+5];

DB dfs(int n, int m) {
    if(vi[n][m]) return f[n][m];
    vi[n][m] = 1;
    if(n==0 && m==0) return f[n][m] = 0;

    f[n][m] = 1e9;
    int hd = n*2+m;

    // nn策略
    if(hd>=2) {
        DB tmp = 0;
        if(n>=1) tmp += DB(n*2.0) / (hd*(hd-1.0)) * (dfs(n-1,m)+1); // 2张未知且相同
        if(n>=2) tmp += (2.0*n*(2.0*n-2.0)) / DB(hd*(hd-1.0)) * (dfs(n-2,m+2)+1); // 2张未知但不同
        if(m>=2) tmp += DB(m*(m-1.0)) / DB(hd*(hd-1.0)) * (dfs(n,m-2)+3); // 2张已知
        if(n>=1 && m>=1) tmp += DB(4.0*n*m) / DB(hd*(hd-1.0)) * (dfs(n-1,m)+2); // 1张已知1张未知
        f[n][m] = min(f[n][m], tmp);
    }

    // nm策略
    if(m>0) {
        DB tmp = 0;
        tmp += 1.0 / DB(hd) * (dfs(n,m-1)+1); // 2张已知且相同
        if(m>=2) tmp += (m-1.0) / DB(hd) * (dfs(n,m-1)+2); // 2张已知但不同
        if(n>=1) tmp += (2.0*n) / DB(hd) * (dfs(n-1,m+1)+1); // 1张未知1张已知
        f[n][m] = min(f[n][m], tmp);
    }

    return f[n][m];
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        int n; scanf("%d", &n);
        printf("%.2f\n", dfs(n,0) );
    }
    return 0;
}
