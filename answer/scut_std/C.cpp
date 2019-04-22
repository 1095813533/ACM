// 邵老师牛逼!
#include<bits/stdc++.h>

using namespace std;

const int maxT = 14;
const int maxn = 40;

int cmp(char *s1, int p1, int d1, int n1, char *s2, int p2, int d2, int n2) {
    int n = min(n1,n2);
    for(int i = 1; i <= n; ++i) {
        if(s1[p1] < s2[p2]) return -1;
        if(s1[p1] > s2[p2]) return 1;
        p1+=d1, p2+=d2;
    }
    if(n1 < n2) return -1;
    if(n1 > n2) return 1;
    return 0;
}

int main() {
    int __; scanf("%d", &__);
    assert(1<=__ && __<=maxT);
    char s1[maxn+5], s2[maxn+5];
    char ans[maxn*2+5];
    for(int _ = 1; _ <= __; ++_) {
        scanf("%s%s", s1, s2);
        int l1 = 0, r1 = strlen(s1)-1;
        int l2 = 0, r2 = strlen(s2)-1;
        int n = r1+r2+2;
        for(int i = 0; i < n; ++i) {
            int di1 = 0, di2 = 0;
            if(cmp(s1, l1, 1, r1-l1+1, s1, r1, -1, r1-l1+1) >= 0) di1 = 1;
            else di1 = -1;

            if(cmp(s2, l2, 1, r2-l2+1, s2, r2, -1, r2-l2+1) >= 0) di2 = 1;
            else di2 = -1;

            int pt = 0, di = 0;
            if(cmp(s1, (di1==1)?l1:r1, di1, r1-l1+1, s2, (di2==1)?l2:r2, di2, r2-l2+1) >= 0)
                pt = 1, di = di1;
            else pt = 2, di = di2;
            char c = 0;
            if(pt==1) {
                if(di==1) ans[i] = s1[l1++];
                else ans[i] = s1[r1--];
            }
            else if(pt==2) {
                if(di==1) ans[i] = s2[l2++];
                else ans[i] = s2[r2--];
            }
        }
        ans[n] = '\0';
        printf("Case #%d: %s\n", _, ans);
    }
	return 0;
}
