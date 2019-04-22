#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct node {
    ll x, y;
    int ty, id;
    node() {}
    node(ll _x, ll _y, int _ty, int _id)
        : x(_x), y(_y), ty(_ty), id(_id) {}
    void init(int _ty, int _id) {
        scanf("%lld%lld", &x, &y);
        ty = _ty;
        id = _id;
    }
    node operator-(const node &b) const {
        return node(x - b.x, y - b.y, 0, 0);
    }
    ll operator^(const node &b) const {
        return x * b.y - y * b.x;
    }
    bool operator<(const node &b) const {
        return x == b.x ? y < b.y : x < b.x;
    }
};

const int MAXN = 1e5 + 10;
node a[MAXN], b[MAXN], cc[MAXN << 1];
int ans[MAXN], que[MAXN], lim;

bool judge(node a, node b, node c) {
    ll tmp = (b - a) ^ (a - c);
    return tmp == 0 ? c.id < b.id : tmp > 0;
}

void solve() {
    int las = 0;
    for (int i = 1; i <= lim; i++) {
        if (cc[i].ty == 1) {
            while (las > 1 && ((cc[i] - cc[que[las]]) ^ (cc[que[las]] - cc[que[las - 1]])) > 0)
                las--;
            que[++las] = i;
        } else {
            if (!las)
                continue;
            int l = 1, r = las;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (((cc[i] - cc[que[mid + 1]]) ^ (cc[que[mid + 1]] - cc[que[mid]])) > 0)
                    r = mid;
                else
                    l = mid + 1;
            }
            if (ans[cc[i].id] == -1 || judge(b[cc[i].id], a[ans[cc[i].id]], a[cc[que[l]].id]))
                ans[cc[i].id] = cc[que[l]].id;
        }
    }
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    lim = n + q;
    for (int i = 1; i <= lim; i++) {
        if (i <= n) {
            a[i].init(1, i);
            cc[i] = a[i];
        } else {
            b[i - n].init(2, i - n);
            cc[i] = b[i - n];
        }
    }
    memset(ans, -1, sizeof(ans));
    sort(cc + 1, cc + lim + 1);
    solve();
    reverse(cc + 1, cc + lim + 1);
    for (int i = 1; i <= lim; i++) {
        cc[i].x = -cc[i].x;
        cc[i].y = -cc[i].y;
    }
    solve();
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
}
